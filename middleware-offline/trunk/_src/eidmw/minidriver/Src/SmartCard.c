/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2008-2010 FedICT.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version
 * 3.0 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, see
 * http://www.gnu.org/licenses/.

**************************************************************************** */
/****************************************************************************************************/

#include "globmdrv.h"
#include "log.h"
#include "smartcard.h"
#include "externalpinui.h"
#include "util.h"
#include "cache.h"

#include <commctrl.h>
/****************************************************************************************************/

#define CHALLENGE_DATA_SIZE         16

#define BELPIC_MAX_FILE_SIZE        65535
#define BELPIC_PIN_BUF_SIZE         8
#define BELPIC_MIN_USER_PIN_LEN     4
#define BELPIC_MAX_USER_PIN_LEN     12

#define BELPIC_PAD_CHAR			    0xFF
#define BELPIC_KEY_REF_NONREP		0x83

/****************************************************************************************************/


#define WHERE "PteidDelayAndRecover"
void PteidDelayAndRecover(PCARD_DATA  pCardData,
						 BYTE   SW1, 
						 BYTE   SW2,
						 DWORD  dwReturn)
{
	if( (dwReturn == SCARD_E_COMM_DATA_LOST) || (dwReturn == SCARD_E_NOT_TRANSACTED) )
	{
		DWORD ap = 0;
		int i = 0;

		LogTrace(LOGTYPE_WARNING, WHERE, "Card is confused, trying to recover...");

		for (i = 0; (i < 10) && (dwReturn != SCARD_S_SUCCESS); i++)
		{
			if (i != 0)
				Sleep(1000);

			dwReturn = SCardReconnect(pCardData->hScard, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0, SCARD_RESET_CARD, &ap);
			if ( dwReturn != SCARD_S_SUCCESS )
			{
				LogTrace(LOGTYPE_TRACE, WHERE, "  [%d] SCardReconnect errorcode: [0x%02X]", i, dwReturn);
				continue;
			}
			// transaction is lost after an SCardReconnect()
			dwReturn = SCardBeginTransaction(pCardData->hScard);
			if ( dwReturn != SCARD_S_SUCCESS )
			{
				LogTrace(LOGTYPE_TRACE, WHERE, "  [%d] SCardBeginTransaction errorcode: [0x%02X]", i, dwReturn);
				continue;
			}
			dwReturn = PteidSelectApplet(pCardData);
			if ( dwReturn != SCARD_S_SUCCESS )
			{
				LogTrace(LOGTYPE_TRACE, WHERE, "  [%d] SCardSelectApplet errorcode: [0x%02X]", i, dwReturn);
				continue;
			}

			LogTrace(LOGTYPE_INFO, WHERE, "  Card recovered in loop %d", i);
		}
		if(i >=10)
		{
			LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit errorcode: [0x%02X], Failed to recover", dwReturn);
		}
	}
	if ( (( SW1 == 0x90 ) && ( SW2 == 0x00 )) ||
		 ( SW1 == 0x61 ) ||
		 ( SW1 == 0x6c ) )
	{
		;//no error received, no sleep needed
	}
	else
	{
		Sleep(25);
	}
}
#undef WHERE



#define WHERE "PteidAuthenticate"
DWORD PteidAuthenticate(PCARD_DATA  pCardData, 
                       PBYTE        pbPin, 
                       DWORD        cbPin, 
                       PDWORD       pcAttemptsRemaining,
					   BYTE			pin_id) 
{
   DWORD             dwReturn  = 0;

   SCARD_IO_REQUEST  ioSendPci = {0, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST  ioRecvPci = {0, sizeof(SCARD_IO_REQUEST)};

   unsigned char     Cmd[128];
   unsigned int      uiCmdLg   = 0;
   unsigned char     recvbuf[256];
   unsigned long     recvlen   = sizeof(recvbuf);
   BYTE              SW1, SW2;
   unsigned int              i = 0;
   unsigned int				 j = 0;
   char				paddingChar;

   LogTrace(LOGTYPE_INFO, WHERE, "Enter API...");

   /********************/
   /* Check Parameters */
   /********************/
   if ( pCardData == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [pCardData]");
      CLEANUP(SCARD_E_INVALID_PARAMETER);
   }
   if ( pbPin == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [pbPin]");
      CLEANUP(SCARD_E_INVALID_PARAMETER);
   }

   /* Don't allow zero-length PIN */
   if ( ( cbPin < BELPIC_MIN_USER_PIN_LEN ) ||
        ( cbPin > BELPIC_MAX_USER_PIN_LEN ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [cbPin]");
      CLEANUP(SCARD_W_WRONG_CHV);
   }

   PteidSelectApplet(pCardData);
  //00 20 00 81 08 32 31 34 38 FF FF FF FF
   /**********/
   /* Log On */
   /**********/
   Cmd[0] = 0x00;
   Cmd[1] = 0x20;  /* VERIFY COMMAND */
   Cmd[2] = 0x00;
   if (Is_Gemsafe)
	   Cmd[3] = 0x81 + pin_id; /* PIN ID  */
   else
   {
	   if (pin_id == 0)
		   Cmd[3] = 0x01;  /* Authentication PIN  */
	   else
		   Cmd[3] = 0x82;  /* Signature PIN  */
   }

   Cmd[4] = 0x08;  /* PIN Length (including padding) */

   if (Is_Gemsafe)
	   paddingChar = 0xFF;
   else
	   paddingChar = 0x2F;

   while(i < 0x08)
   {
	   if(i < cbPin)
		   Cmd[i+5] = pbPin[i];
	   else
		   Cmd[i+5] = paddingChar;
	   i++;
   }
	   
   uiCmdLg = 13;
   recvlen = sizeof(recvbuf);

   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];

   if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
   {
      dwReturn = SCARD_W_WRONG_CHV;
      LogTrace(LOGTYPE_ERROR, WHERE, "CardAuthenticatePin Failed: [0x%02X][0x%02X]", SW1, SW2);

      if ( ((SW1 == 0x63) && ((SW2 & 0xF0) == 0xC0)) )
      {
         if ( pcAttemptsRemaining != NULL )
         {
            /* -1: Don't support returning the count of remaining authentication attempts */
            *pcAttemptsRemaining = (SW2 & 0x0F);
         }
      }
      else if ( (SW1 == 0x69) && (SW2 == 0x83) )
      {
         dwReturn = SCARD_W_CHV_BLOCKED;
		 LogTrace(LOGTYPE_ERROR, WHERE, "Card Blocked, watch out!!");
      }
   }
   else
   {
      LogTrace(LOGTYPE_INFO, WHERE, "Logged on...");
   }

cleanup:

   LogTrace(LOGTYPE_INFO, WHERE, "Exit API...");

   return(dwReturn);
}
#undef WHERE

void GemPCLoadStrings(SCARDHANDLE hCard, DWORD pin_id)
{
/*The Following Blob contains the Portuguese strings to show on the Pinpad Display:
		PIN Autent.?   
		Novo PIN?    
		Conf. novo PIN
		OK  
		PIN falhou      
		Tempo expirou   
		* tentiv. restam
		Introduza cartao
		Erro cartao 
		PIN bloqueado   
	*/
	char stringTable[] =
		"\xB2\xA0\x00\x4D\x4C\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x4E\x6F\x76"
		"\x6F\x20\x50\x49\x4E\x3F\x20\x20\x20\x20\x20\x20\x20\x43\x6F\x6E\x66\x2E\x20\x6E\x6F\x76\x6F"
		"\x20\x50\x49\x4E\x20\x20\x50\x49\x4E\x20\x4F\x4B\x2E\x20\x20\x20\x20\x20\x20\x20\x20\x20\x50"
		"\x49\x4E\x20\x66\x61\x6C\x68\x6F\x75\x20\x20\x20\x20\x20\x20\x54\x65\x6D\x70\x6F\x20\x65\x78"
		"\x70\x69\x72\x6F\x75\x20\x20\x20\x2A\x20\x74\x65\x6E\x74\x69\x76\x2E\x20\x72\x65\x73\x74\x61\x6D"
		"\x49\x6E\x74\x72\x6F\x64\x75\x7A\x61\x20\x63\x61\x72\x74\x61\x6F\x45\x72\x72\x6F\x20\x63\x61\x72"
		"\x74\x61\x6F\x20\x20\x20\x20\x20\x50\x49\x4E\x20\x62\x6C\x6F\x71\x75\x65\x61\x64\x6F\x20\x20\x20";

	DWORD ioctl = 0x00312000;
	char recvBuf[200];
	DWORD rv = 0;
	unsigned int STRING_LEN = 16;
	DWORD recvlen = sizeof(recvBuf);

	switch (pin_id)
	{
		case 0:
			memcpy(&stringTable[5], "PIN Autent.?    ", STRING_LEN); 
			break;
		case 1:
			memcpy(&stringTable[5], "PIN Assinatura? ", STRING_LEN); 
			break;

	}
	
	rv = SCardControl(hCard, ioctl, stringTable, sizeof(stringTable)-1,
		recvBuf, recvlen, &recvlen);

	
	if ( rv == SCARD_S_SUCCESS )
	{
		LogTrace(LOGTYPE_INFO, "GemPCLoadStrings()", "Strings Loaded successfully");
	}
	else
		LogTrace(LOGTYPE_INFO, "GemPCLoadStrings()", "Error in LoadStrings: SCardControl() returned: %08x", 
				(unsigned int)rv);

}

/****************************************************************************************************/

#define WHERE "PteidAuthenticateExternal"

//Helper macros to ease the transition to 3 arg version of swprintf
#define WRITE_MAIN_INSTRUCTION(MESSAGE) swprintf(wchMainInstruction, 100, MESSAGE)
#define WRITE_ERROR_MESSAGE(MESSAGE) swprintf(wchErrorMessage, 500, MESSAGE)

DWORD PteidAuthenticateExternal(
	PCARD_DATA   pCardData,
	PDWORD       pcAttemptsRemaining,
	BOOL		 bSilent,
	DWORD		 pin_id )
{
	DWORD						dwReturn  = 0;
	SCARD_IO_REQUEST				ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
	SCARD_IO_REQUEST				ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

	PIN_VERIFY_STRUCTURE			verifyCommand;

	unsigned int				uiCmdLg = 0;
	unsigned int                pin_ref = 0;
	unsigned int				is_gempc = 0;
	unsigned char				recvbuf[256];
	unsigned char				szReaderName[256];
	DWORD						reader_length = sizeof(szReaderName);
	unsigned long				recvlen     = sizeof(recvbuf);
	BYTE							SW1, SW2;
	int							i           = 0;
	int							offset		= 0;
	DWORD						dwDataLen;
	BOOL						bRetry      = TRUE;
	int							nButton;
	LONG						status_rv;

	EXTERNAL_PIN_INFORMATION		externalPinInfo;
	HANDLE						DialogThreadHandle;


	LogTrace(LOGTYPE_INFO, WHERE, "Enter API...");

	/********************/
	/* Check Parameters */
	/********************/
	if ( pCardData == NULL )
	{
		LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [pCardData]");
		CLEANUP(SCARD_E_INVALID_PARAMETER);
	}


	/*********************/
	/* External PIN Info */
	/*********************/
	externalPinInfo.hCardHandle = pCardData->hScard;
	CCIDgetFeatures(&(externalPinInfo.features), externalPinInfo.hCardHandle);

	/*********************/
	/* Get Parent Window */
	/*********************/
	dwReturn = CardGetProperty(pCardData, 
		CP_PARENT_WINDOW, 
		(PBYTE) &(externalPinInfo.hwndParentWindow), 
		sizeof(externalPinInfo.hwndParentWindow), 
		&dwDataLen, 
		0);
	if (dwReturn != 0) {
		LogTrace(LOGTYPE_ERROR, WHERE, "CardGetProperty Failed: %02X", dwReturn);
		externalPinInfo.hwndParentWindow = NULL;
	}


	/*********************/
	/* Get Pin Context String */
	/*********************/		
	dwReturn = CardGetProperty(pCardData, 
		CP_PIN_CONTEXT_STRING, 
		(PBYTE) externalPinInfo.lpstrPinContextString, 
		sizeof(externalPinInfo.lpstrPinContextString), 
		&dwDataLen, 
		0);
	if (dwReturn != 0) {
		LogTrace(LOGTYPE_ERROR, WHERE, "CardGetProperty Failed: %02X", dwReturn);
		wcscpy(externalPinInfo.lpstrPinContextString, L"");
	}

	/**********/
	/* Log On */
	/**********/

	if (Is_Gemsafe == 0 && pin_id == 0)
		pin_ref = 0x01;
	else 
		pin_ref = 0x81 + pin_id;

	//SCardStatus to get the reader name
	status_rv = SCardStatus(pCardData->hScard,  szReaderName, &reader_length,
		NULL, NULL, NULL, NULL);

	if (strstr(szReaderName, "GemPC Pinpad") != 0 
		|| strstr(szReaderName, "GemPCPinpad") != 0)
	{
		createVerifyCommandGemPC(&verifyCommand, pin_ref);
		is_gempc = 1;
	}
	else if (strstr(szReaderName, "ACR83U") != 0)
	{
		createVerifyCommandACR83(&verifyCommand, pin_ref);
	}
	else
		createVerifyCommand(&verifyCommand, pin_ref);

	uiCmdLg = sizeof(verifyCommand);
	recvlen = sizeof(recvbuf);

	PteidSelectApplet(pCardData);

	while (bRetry) {
		bRetry = FALSE;
		nButton = -1;

		// We introduce a short sleep before starting the PIN VERIFY procedure
		// Reason: we do this for users with a combined keyboard/secure PIN pad smartcard reader
		//   "enter" key far right on the keyboard ==  "OK" button of the PIN pad
		//   Problem: key becomes PIN-pad button before key is released. Result: the keyup event is not sent.
		//   This sleep gives the user some time to release the Enter key.

		Sleep(100);

		if(externalPinInfo.features.VERIFY_PIN_DIRECT != 0)
		{
			externalPinInfo.iPinCharacters = 0;
			externalPinInfo.cardState = CS_PINENTRY;
			// show dialog
			if (!bSilent)
				DialogThreadHandle = CreateThread(NULL, 0, DialogThreadPinEntry, &externalPinInfo, 0, NULL);

			LogTrace(LOGTYPE_INFO, WHERE, "Running SCardControl with ioctl=%08x",externalPinInfo.features.VERIFY_PIN_DIRECT );
			LogTrace(LOGTYPE_INFO, WHERE, "PIN_VERIFY_STRUCT: ");
			LogDump(uiCmdLg, (unsigned char*)&verifyCommand);

			if (is_gempc == 1)
				GemPCLoadStrings(pCardData->hScard, pin_id);

			dwReturn = SCardControl(pCardData->hScard, 
				externalPinInfo.features.VERIFY_PIN_DIRECT, 
				&verifyCommand, 
				uiCmdLg,                              
				recvbuf, 
				recvlen,
				&recvlen);
			SW1 = recvbuf[recvlen-2];
		    SW2 = recvbuf[recvlen-1];

			externalPinInfo.cardState = CS_PINENTERED;
			if ( dwReturn != SCARD_S_SUCCESS )
			{
				LogTrace(LOGTYPE_ERROR, WHERE, "SCardControl errorcode: [0x%02X]", dwReturn);
				CLEANUP(dwReturn);
			}
			else
			{
				if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
				{
					
					LogTrace(LOGTYPE_ERROR, WHERE, "CardAuthenticateExternal Failed: [0x%02X][0x%02X]", SW1, SW2);

					if ( ((SW1 == 0x63) && ((SW2 & 0xF0) == 0xC0)) )
					{
						if ( pcAttemptsRemaining != NULL )
						{
							/* -1: Don't support returning the count of remaining authentication attempts */
							*pcAttemptsRemaining = (SW2 & 0x0F);
						}
					}
					else if ( (SW1 == 0x69) && (SW2 == 0x83) )
					{
						LogTrace(LOGTYPE_ERROR, WHERE, "Card Blocked, watch out!!");
					}
				}
				else
					LogTrace(LOGTYPE_INFO, WHERE, "Logged in via Pinpad Reader");

			}
		}
	
	}

cleanup:

	LogTrace(LOGTYPE_INFO, WHERE, "Exit API...");
	return(dwReturn);
}
#undef WHERE

/****************************************************************************************************/

#define WHERE "PteidDeAuthenticate"
DWORD PteidDeAuthenticate(PCARD_DATA    pCardData) 
{
   DWORD             dwReturn  = 0;

   SCARD_IO_REQUEST  ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST  ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char     Cmd[128];
   unsigned int      uiCmdLg   = 0;
   unsigned char     recvbuf[256];
   unsigned long     recvlen   = sizeof(recvbuf);
   BYTE              SW1, SW2;
   int               i         = 0;

   LogTrace(LOGTYPE_INFO, WHERE, "Enter API...");

   /********************/
   /* Check Parameters */
   /********************/
   if ( pCardData == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [pCardData]");
      CLEANUP(SCARD_E_INVALID_PARAMETER);
   }

   /***********/
   /* Log Off */
   /***********/
   Cmd [0] = 0x80;
   Cmd [1] = 0xE6; /* LOG OFF */
   Cmd [2] = 0x00;
   Cmd [3] = 0x00;
   uiCmdLg = 4;
   recvlen = sizeof(recvbuf);

   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
   if ( dwReturn != SCARD_S_SUCCESS )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
   if ( (SW1 != 0x90) || (SW2 != 0x00) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit status bytes: [0x%02X][0x%02X]", SW1, SW2);
      CLEANUP(SCARD_E_UNEXPECTED);
   }

cleanup:
   LogTrace(LOGTYPE_INFO, WHERE, "Exit API...");
   return(dwReturn);
}
#undef WHERE

/****************************************************************************************************/

#define WHERE "PteidMSE"
DWORD PteidMSE(PCARD_DATA   pCardData, 
			     BYTE      key_id) 
{
  
   DWORD             dwReturn = 0;

   SCARD_IO_REQUEST  ioSendPci = {0, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST  ioRecvPci = {0, sizeof(SCARD_IO_REQUEST)};

   unsigned char     Cmd[128];
   unsigned int      uiCmdLg = 0;
   unsigned char     recvbuf[256+2];
   unsigned long     recvlen = sizeof(recvbuf);
   BYTE              SW1, SW2;

   int               i = 0;

   LogTrace(LOGTYPE_INFO, WHERE, "Enter API...");
   /*
    * The MSE: SET Command will fail with error 0x000006f7
    * if the command is executed too fast after an command which resulted in an error condition
    */
   // Sleep(20);
   Cmd [0] = 0x00;
   Cmd [1] = 0x22; //MSE
   Cmd [2] = 0x41;
   if (Is_Gemsafe)
   {
	   Cmd [3] = 0xB6;
	   Cmd [4] = 0x06; //Length of data
	   Cmd [5] = 0x80; //Tag (Algorithm ID)
	   Cmd [6] = 0x01;
	   Cmd [7] = 0x02; 
	   Cmd [8] = 0x84; //Tag (Key Reference) 
	   Cmd [9] = 0x01;
	   if(key_id == 0) 
		Cmd [10] = 0x02; //Auth keyRef
	   else
		Cmd [10] = 0x01; //Sign keyRef
	   uiCmdLg = 11;

   }
   else
   {
	   Cmd [3] = 0xA4;
	   Cmd [4] = 0x09; //Length of data
	   Cmd [5] = 0x95; //Tag (Usage Qualifier)
	   Cmd [6] = 0x01;
	   Cmd [7] = 0x40;
	   Cmd [8] = 0x84; //Tag (Key Reference)
	   Cmd [9] = 0x01;
	   if(key_id == 0)
		Cmd [10] = 0x01;
	   else
		Cmd [10] = 0x82;
	   Cmd [11] = 0x80; //Tag (Algorithm Reference)
	   Cmd [12] = 0x01;
	   Cmd [13] = 0x02; //(RSA-PKCS#1)
	   uiCmdLg = 14;
   }
  
   //Sleep(1000);
   LogTrace(LOGTYPE_INFO, WHERE, "APDU MSE");
   LogDump (uiCmdLg, (char *)Cmd);
  
   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
   if ( dwReturn != SCARD_S_SUCCESS )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit (SET) errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
   
   if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SET Failed: [0x%02X][0x%02X]", SW1, SW2);
      CLEANUP(SCARD_E_UNEXPECTED);
   }

cleanup:
   LogTrace(LOGTYPE_INFO, WHERE, "Exit API...");
   return(dwReturn);
}
#undef WHERE

/****************************************************************************************************/

#define WHERE "PteidChangePIN"
DWORD    PteidChangePIN
         (
            PCARD_DATA  pCardData, 
            PBYTE       pbCurrentAuthenticator,
            DWORD       cbCurrentAuthenticator,
            PBYTE       pbNewAuthenticator,
            DWORD       cbNewAuthenticator,
            PDWORD      pcAttemptsRemaining,
			DWORD		     pin_id
         ) 
{
   DWORD             dwReturn = 0;

   SCARD_IO_REQUEST  ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST  ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char     Cmd[128];
   unsigned int      uiCmdLg = 0;
   unsigned char     recvbuf[256];
   unsigned long     recvlen = sizeof(recvbuf);
   BYTE              SW1, SW2;
   char				 paddingChar;	

   unsigned int      i        = 0;
   int				 j		  = 0;	

   LogTrace(LOGTYPE_INFO, WHERE, "Enter API...");

   /********************/
   /* Check Parameters */
   /********************/
   if ( pCardData == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [pCardData]");
      CLEANUP(SCARD_E_INVALID_PARAMETER);
   }
   if ( pbCurrentAuthenticator == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [pbCurrentAuthenticator]");
      CLEANUP(SCARD_E_INVALID_PARAMETER);
   }
   if ( pbNewAuthenticator == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [pbNewAuthenticator]");
      CLEANUP(SCARD_E_INVALID_PARAMETER);
   }
   if ( ( cbCurrentAuthenticator < BELPIC_MIN_USER_PIN_LEN ) ||
        ( cbCurrentAuthenticator > BELPIC_MAX_USER_PIN_LEN ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [cbCurrentAuthenticator]");
      CLEANUP(SCARD_W_WRONG_CHV);
   }
   if ( ( cbNewAuthenticator < BELPIC_MIN_USER_PIN_LEN ) ||
        ( cbNewAuthenticator > BELPIC_MAX_USER_PIN_LEN ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid parameter [cbCurrentAuthenticator]");
      CLEANUP(SCARD_W_WRONG_CHV);
   }

   if (!Is_Gemsafe)
   {
		dwReturn = PteidAuthenticate(pCardData, pbCurrentAuthenticator, cbCurrentAuthenticator,
			pcAttemptsRemaining, 1);
		if(dwReturn != SCARD_S_SUCCESS)
			CLEANUP(dwReturn);
   }

   if (Is_Gemsafe)
	   paddingChar = 0xFF;
   else
	   paddingChar = 0x2F;
  

   /* TODO: This must be corrected see PkiCard.cpp in cardlayer sub-project
   /* Change PIN code: Old PIN + New PIN + Padding */
   Cmd[0] = 0x00;
   Cmd[1] = 0x24;   /* CHANGE REFERENCE DATA COMMAND    */
   if (Is_Gemsafe)
	   Cmd[2] = 0x00;
   else
	   Cmd[2] = 0x01; 
   if (Is_Gemsafe)
	   Cmd[3] = 0x81;  //PIN Reference
   else
       Cmd[3] = 0x01; 
   if(!Is_Gemsafe)
	Cmd[4] = 0x08; //Just the new PIN
   else
	Cmd[4] = 0x10; // Old and new PIN
	
   if(Is_Gemsafe)
   {
	   while(i < 8)
	   {
		if (i < cbCurrentAuthenticator)
			Cmd[4+i] = pbCurrentAuthenticator[i];
		else
			Cmd[4+i] = paddingChar;
		i++;
	   }
   }

   if (!Is_Gemsafe)
	   j = -8;

   while( i < 16)
   {
	   if (i < cbNewAuthenticator)
		   Cmd[4+i+j] = pbNewAuthenticator[i+j];
	   else
		   Cmd[4+i+j] = paddingChar;
	   i++;
   }
   if(Is_Gemsafe)	 
	   uiCmdLg = 21;
   else
	   uiCmdLg = 13; 
   recvlen = sizeof(recvbuf);

   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
   if ( dwReturn != SCARD_S_SUCCESS )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }

   if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
   {
      dwReturn = SCARD_W_WRONG_CHV;
      LogTrace(LOGTYPE_ERROR, WHERE, "CardChangeAuthenticator Failed: [0x%02X][0x%02X]", SW1, SW2);

      if ( ((SW1 == 0x63) && ((SW2 & 0xF0) == 0xC0)) )
      {
         if ( pcAttemptsRemaining != NULL )
         {
            /* -1: Don't support returning the count of remaining authentication attempts */
            *pcAttemptsRemaining = (SW2 & 0x0F);
         }
      }
      else if ( (SW1 == 0x69) && (SW2 == 0x83) )
      {
         dwReturn = SCARD_W_CHV_BLOCKED;
      }
	  else
		  LogTrace(LOGTYPE_ERROR, WHERE, "Unexpected error reply: [0x%02X][0x%02X]", SW1, SW2);
   }
   else
   {
      LogTrace(LOGTYPE_INFO, WHERE, "Changed PIN...");
   }

cleanup:
   LogTrace(LOGTYPE_INFO, WHERE, "Exit API...");
   return(dwReturn);
}
#undef WHERE

/****************************************************************************************************/

#define WHERE "PteidGetCardSN"
DWORD PteidGetCardSN(PCARD_DATA  pCardData, 
	PBYTE pbSerialNumber, 
	DWORD cbSerialNumber, 
	PDWORD pdwSerialNumber) 
{
   DWORD                   dwReturn = 0;

   SCARD_IO_REQUEST        ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST        ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char           Cmd[128];
   unsigned int            uiCmdLg = 0;

   unsigned char           recvbuf[256];
   unsigned long           recvlen = sizeof(recvbuf);
   BYTE                    SW1, SW2;

   int                     i = 0;
   int                     iWaitApdu = 100;
   int   				      bRetry = 0;

   if (cbSerialNumber < 16) {
		CLEANUP(ERROR_INSUFFICIENT_BUFFER);
   }

   PteidSelectApplet(pCardData);

   *pdwSerialNumber = 0;
   Cmd [0] = 0x00;
   Cmd [1] = 0xCA;
   if (Is_Gemsafe)
   {
   Cmd [2] = 0xDF;
   Cmd [3] = 0x30;
   Cmd [4] = 0x08;
   }
   else
   {
   Cmd [2] = 0x02;
   Cmd [3] = 0x5A;
   Cmd [4] = 0x0D;
   }
   uiCmdLg = 5;

	do {

		Sleep(iWaitApdu);
		recvlen = sizeof(recvbuf);
        dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
		SW1 = recvbuf[recvlen-2];
		SW2 = recvbuf[recvlen-1];
		PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
		i = i + 1;
		bRetry = 0;
		if (dwReturn == SCARD_E_COMM_DATA_LOST)
		{
			bRetry++;
			LogTrace(LOGTYPE_TRACE, WHERE, "SCardTransmit failed with SCARD_E_COMM_DATA_LOST. Sleep %d ms and try again", iWaitApdu);
		}
		if (dwReturn == SCARD_S_SUCCESS)
		{
			// 6d = "command not available in current life cycle"
			if ( SW1 == 0x6d )
			{
				LogTrace(LOGTYPE_TRACE, WHERE, "SCardTransmit returned SW1 = 6d. Sleep %d ms and try again", iWaitApdu);
				bRetry++;
			}
		}
	} while (bRetry != 0 && i < 10);

   if ( dwReturn != SCARD_S_SUCCESS )
   {
		LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit (GET_CARD_DATA) errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];

  
   if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Bad status bytes: [0x%02X][0x%02X]", SW1, SW2);
		CLEANUP(SCARD_E_UNEXPECTED);
   }
   if (Is_Gemsafe)
   {
	*pdwSerialNumber = 8;
   memcpy(pbSerialNumber, recvbuf, 8);
   }
   else
   {
   *pdwSerialNumber = 13; //For IAS: length(SerialNumber) = 13
   memcpy(pbSerialNumber, recvbuf, 13);
   }

cleanup:
   return (dwReturn);
}

#undef WHERE

/****************************************************************************************************/

#define WHERE "PteidSignData"
DWORD PteidSignData(PCARD_DATA pCardData, BYTE pin_id, DWORD cbToBeSigned, PBYTE pbToBeSigned, DWORD *pcbSignature, PBYTE *ppbSignature)
{

   DWORD                   dwReturn = 0;

   SCARD_IO_REQUEST        ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST        ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char           Cmd[128];
   unsigned int            uiCmdLg = 0;

   unsigned char           recvbuf[1024];
   unsigned long           recvlen = sizeof(recvbuf);
   BYTE                    SW1, SW2;

   unsigned int            i          = 0;
   unsigned int            cbHdrHash  = 0;
   const unsigned char     *pbHdrHash = NULL;
	
   PteidSelectApplet(pCardData);
   dwReturn = PteidMSE(pCardData, pin_id);

   if (dwReturn != SCARD_S_SUCCESS)
   {
	CLEANUP(dwReturn);
   }

   /* Sign Command for IAS*/
   /* 00 88 02 00 24 EC 61 B0 5B 70 33 78 39 F0 C8 C5 EB 79 64 */
   Cmd [0] = 0x00; //0x88, 0x02, 0x00
   Cmd [1] = 0x88;   /* PSO: Compute Digital Signature COMMAND */
   Cmd [2] = 0x02;
   Cmd [3] = 0x00; 
   Cmd [4] = (BYTE)(cbToBeSigned);
   memcpy(Cmd + 5, pbToBeSigned, cbToBeSigned);
   uiCmdLg = 5 + cbToBeSigned;
   
#ifdef _DEBUG
   LogDumpBin("C:\\SmartCardMinidriverTest\\signdata.bin", cbHdrHash + cbToBeSigned, (char *)&Cmd[5]);
#endif
   
   //printByteArray(Cmd, uiCmdLg);
   recvlen = sizeof(recvbuf);
   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
   if ( dwReturn != SCARD_S_SUCCESS )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit (SIGN) errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }

   if ( ( SW1 != 0x61 ) || ( SW2 != 0x80 ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Sign Failed: [0x%02X][0x%02X]", SW1, SW2);

      if ( SW1 == 0x69 )
      {
         CLEANUP(SCARD_W_SECURITY_VIOLATION);
      }
      else
      {
         CLEANUP(SCARD_E_UNEXPECTED);
      }
   }

   /* Retrieve signature Command */
   Cmd [0] = 0x00;
   Cmd [1] = 0xC0;   /* PSO: GET RESPONSE COMMAND */
   Cmd [2] = 0x00;
   Cmd [3] = 0x00;
   Cmd [4] = 0x80;   /* Length of response */
   uiCmdLg = 5;

   recvlen = sizeof(recvbuf);
   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
   if ( dwReturn != SCARD_S_SUCCESS )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit (Get Response) errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
   if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Get Response Failed: [0x%02X][0x%02X]", SW1, SW2);
      CLEANUP(SCARD_E_UNEXPECTED);
   }

   if ( (recvlen - 2) != 0x80 )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid length received: [0x%02X][0x%02X]", recvlen - 2, 0x80);
      CLEANUP(SCARD_E_UNEXPECTED);
   }

   *pcbSignature = 0x80;

   /* Allocate memory for the target buffer */
   *ppbSignature = pCardData->pfnCspAlloc(*pcbSignature);

   if ( *ppbSignature == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Error allocating memory for [*ppbSignature]");
      CLEANUP(SCARD_E_NO_MEMORY);
   }
   /* Copy the signature */
   for ( i = 0 ; i < *pcbSignature ; i++ )
   {
      (*ppbSignature)[i] = recvbuf[*pcbSignature - i - 1];
   }

cleanup:
   return (dwReturn);
}
#undef WHERE

#define WHERE "PteidSignDataGemsafe"
DWORD PteidSignDataGemsafe(PCARD_DATA pCardData, BYTE pin_id, DWORD cbToBeSigned, PBYTE pbToBeSigned, DWORD *pcbSignature, PBYTE *ppbSignature)
{

   DWORD                   dwReturn = 0;

   SCARD_IO_REQUEST        ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST        ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char           Cmd[128];
   unsigned int            uiCmdLg = 0;

   unsigned char           recvbuf[1024];
   unsigned long           recvlen = sizeof(recvbuf);
   BYTE                    SW1, SW2;

   unsigned int            i          = 0;
   unsigned int            cbHdrHash  = 0;
   const unsigned char     *pbHdrHash = NULL;
	
   dwReturn = PteidMSE(pCardData, pin_id);

   if (dwReturn != SCARD_S_SUCCESS)
   {
	CLEANUP(dwReturn);
   }

   /* Sign Command for GEMSAFE*/
   Cmd [0] = 0x00;
   Cmd [1] = 0x2A;   /* PSO: Hash COMMAND */
   Cmd [2] = 0x90;
   Cmd [3] = 0xA0; 
   Cmd [4] = cbToBeSigned+2; // The value of cbToBeSigned should always fit a single byte so this cast is safe 
   Cmd [5] = 0x90;
   Cmd [6] = (BYTE)(cbToBeSigned);
   memcpy(Cmd + 7, pbToBeSigned, cbToBeSigned);
   uiCmdLg = 7 + cbToBeSigned;
   
#ifdef _DEBUG
   LogDumpBin("C:\\SmartCardMinidriverTest\\signdata.bin", cbHdrHash + cbToBeSigned, (char *)&Cmd[5]);
   
   LogTrace(LOGTYPE_INFO, WHERE, "APDU PSO Hash");
   LogDump (uiCmdLg, (char *)Cmd);

#endif
   
   //printByteArray(Cmd, uiCmdLg);
   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   //PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
   if ( dwReturn != SCARD_S_SUCCESS )
   {
	   LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit (PSO: Hash) errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
   LogTrace(LOGTYPE_INFO, WHERE, "Return: APDU PSO Hash");
   LogDump (recvlen, (char *)recvbuf);
  
   Cmd [0] = 0x00;
   Cmd [1] = 0x2A;   /* PSO: Compute Digital Signature COMMAND */
   Cmd [2] = 0x9E;
   Cmd [3] = 0x9A; 
   Cmd [4] = 0x80;  /* Length of expected signature */
   
   uiCmdLg = 5;

   LogTrace(LOGTYPE_INFO, WHERE, "APDU PSO CDS");
   LogDump (uiCmdLg, (char *)Cmd);
   
   recvlen = sizeof(recvbuf);
   dwReturn = SCardTransmit(pCardData->hScard,
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   
   if ( dwReturn != SCARD_S_SUCCESS )
   {
	   LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit (PSO: CDS) errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
   LogTrace(LOGTYPE_INFO, WHERE, "Return: APDU PSO CDS");
   LogDump (recvlen, (char *)recvbuf);

   if ( (recvlen - 2) != 0x80 )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Invalid length received: [0x%02X][0x%02X]", recvlen - 2, 0x80);
      CLEANUP(SCARD_E_UNEXPECTED);
   }

   *pcbSignature = 0x80;

   /* Allocate memory for the target buffer */
   *ppbSignature = pCardData->pfnCspAlloc(*pcbSignature); //pfnCspAlloc � o Memory allocator fornecido pelo CSP

   if ( *ppbSignature == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Error allocating memory for [*ppbSignature]");
      CLEANUP(SCARD_E_NO_MEMORY);
   }
   /* Copy the signature to output buffer */
   for ( i = 0 ; i < *pcbSignature ; i++ )
   {
      (*ppbSignature)[i] = recvbuf[*pcbSignature - i - 1];
   }

cleanup:
   return (dwReturn);
}

#undef WHERE

/****************************************************************************************************/

#define WHERE "PteidReadFile"
DWORD PteidReadFile(PCARD_DATA  pCardData, DWORD dwOffset, DWORD *cbStream, PBYTE pbStream)
{
   DWORD             dwReturn = 0;

   SCARD_IO_REQUEST  ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST  ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char     Cmd[128];
   unsigned int      uiCmdLg = 0;

   unsigned char     recvbuf[256];
   unsigned long     recvlen = sizeof(recvbuf);
   BYTE              SW1, SW2;

   DWORD             cbRead      = 0;
   DWORD             cbPartRead  = 0;

   /***************/
   /* Read File */
   /***************/
   Cmd [0] = 0x00;
   Cmd [1] = 0xB0; /* READ BINARY COMMAND */
   Cmd [2] = 0x00;
   Cmd [3] = 0x00;
   Cmd [4] = 0x00;
   uiCmdLg = 5;

   while ( ( *cbStream - cbRead ) > 0 )
   {
        Cmd[2] = (BYTE)((dwOffset + cbRead) >> 8);   /* set reading startpoint     */
        Cmd[3] = (BYTE)(dwOffset + cbRead);

      cbPartRead = *cbStream - cbRead;
      if(cbPartRead > PTEID_READ_BINARY_MAX_LEN)    /*if more than maximum length */
      {
         Cmd[4] = PTEID_READ_BINARY_MAX_LEN;        /* is requested, than read    */
      }
      else                                         /* maximum length             */
      {
         Cmd[4] = (BYTE)(cbPartRead);
      }
	  recvlen = sizeof(recvbuf);
      dwReturn = SCardTransmit(pCardData->hScard, 
                               &ioSendPci, 
                               Cmd, 
                               uiCmdLg, 
                               &ioRecvPci, 
                               recvbuf, 
                               &recvlen);
		SW1 = recvbuf[recvlen-2];
		SW2 = recvbuf[recvlen-1];
		PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
      if ( dwReturn != SCARD_S_SUCCESS )
      {
         LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit errorcode: [0x%02X]", dwReturn);
         CLEANUP(dwReturn);
      }

		/* Special case: when SW1 == 0x6C (=incorrect value of Le), we will
		retransmit with SW2 as Le, if SW2 is smaller then the 
		PTEID_READ_BINARY_MAX_LEN */
		if ( ( SW1 == 0x6c ) && ( SW2 <= PTEID_READ_BINARY_MAX_LEN ) ) 
		{
			Cmd[4] = SW2;
			recvlen = sizeof(recvbuf);
			dwReturn = SCardTransmit(pCardData->hScard, 
				&ioSendPci, 
				Cmd, 
				uiCmdLg, 
				&ioRecvPci, 
				recvbuf, 
				&recvlen);
			if ( dwReturn != SCARD_S_SUCCESS )
			{
				LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit errorcode: [0x%02X]", dwReturn);
				CLEANUP(dwReturn);
			}
			SW1 = recvbuf[recvlen - 2];
			SW2 = recvbuf[recvlen - 1];

		}

      if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
      {

         LogTrace(LOGTYPE_ERROR, WHERE, "Read Binary Failed: [0x%02X][0x%02X]", SW1, SW2);
         CLEANUP(dwReturn);
      }

      memcpy (pbStream + cbRead, recvbuf, recvlen - 2);
      cbRead += recvlen - 2;
   }
	*cbStream = cbRead;
cleanup:
   return (dwReturn);
}
#undef WHERE

/****************************************************************************************************/

#define WHERE "PteidSelectAndReadFile"
DWORD PteidSelectAndReadFile(PCARD_DATA  pCardData, DWORD dwOffset, BYTE cbFileID, PBYTE pbFileID, DWORD *cbStream, PBYTE * ppbStream)
{
   DWORD             dwReturn = 0;

   SCARD_IO_REQUEST  ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST  ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char     Cmd[128];
   unsigned int      uiCmdLg = 0;

   unsigned char     recvbuf[256];
   unsigned long     recvlen = sizeof(recvbuf);
   BYTE              SW1, SW2;

	DWORD             cbReadBuf;


//   BYTE              bRead [255];
//   DWORD             cbRead;

//   DWORD             cbCertif;

   /***************/
   /* Select File */
   /***************/
   Cmd [0] = 0x00;
   Cmd [1] = 0xA4; /* SELECT COMMAND */
   Cmd [2] = 0x08;
   Cmd [3] = 0x0C;
   Cmd [4] = cbFileID;
   uiCmdLg = 5;

   memcpy(&Cmd[5], pbFileID, cbFileID);
   uiCmdLg += cbFileID;

   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
   if ( dwReturn != SCARD_S_SUCCESS )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
   if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Select Failed: [0x%02X][0x%02X]", SW1, SW2);
      CLEANUP(dwReturn);
   }

	*cbStream = 0;
	*ppbStream = NULL;
	cbReadBuf = 1024;
	while (cbReadBuf == 1024) {
		if (*ppbStream == NULL)
			*ppbStream = (PBYTE) pCardData->pfnCspAlloc(*cbStream + cbReadBuf);
		else
			*ppbStream = (PBYTE) pCardData->pfnCspReAlloc(*ppbStream, *cbStream + cbReadBuf);
		
		if (*ppbStream == NULL) {
			LogTrace(LOGTYPE_ERROR, WHERE, "pfnCsp(Re)Alloc failed");
			CLEANUP(dwReturn);
		}

		dwReturn = PteidReadFile(pCardData, dwOffset, &cbReadBuf, *ppbStream + *cbStream * sizeof(BYTE));
		if ( dwReturn != SCARD_S_SUCCESS )
		{
			LogTrace(LOGTYPE_ERROR, WHERE, "PteidReadFile errorcode: [0x%02X]", dwReturn);
			pCardData->pfnCspFree(*ppbStream);
			CLEANUP(dwReturn);
		}
		*cbStream = *cbStream + cbReadBuf;
	}
cleanup:
   return (dwReturn);
}

BOOL checkStatusCode(const char * context, DWORD dwReturn, BYTE SW1, BYTE SW2)
{

   if ( dwReturn != SCARD_S_SUCCESS )
   {
      LogTrace(LOGTYPE_ERROR, context, "SCardTransmit errorcode: [0x%02X]", dwReturn);
      return FALSE;
   }
   if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
   {
      LogTrace(LOGTYPE_ERROR, context, "Select Failed: [0x%02X][0x%02X]", SW1, SW2);
      return FALSE;
   }

   return TRUE;
}


#undef WHERE
/****************************************************************************************************/

/*
/**/
#define WHERE "PteidReadCert"
DWORD PteidReadCert(PCARD_DATA  pCardData, DWORD dwCertSpec, DWORD *pcbCertif, PBYTE *ppbCertif)
{
   DWORD             dwReturn = 0;

   SCARD_IO_REQUEST  ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
   SCARD_IO_REQUEST  ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

   unsigned char     Cmd[128];
   unsigned int      uiCmdLg = 0;

   unsigned char     recvbuf[256];
   unsigned long     recvlen = sizeof(recvbuf);
   char certPath[25];
   const int		 max_path = 512;
   BYTE              SW1, SW2;

   DWORD             cbCertif;
   
   VENDOR_SPECIFIC * vs;
   int serial_len = 16;
   char * filename;

   cbCertif = 2500; //More than enough for any certificate lmedinas dixit...
   *ppbCertif = pCardData->pfnCspAlloc(cbCertif);
   
   
   vs = (VENDOR_SPECIFIC*)pCardData->pvVendorSpecific;

   if (!runningUnderService())
   {
	   memcpy(certPath, vs->szSerialNumber, serial_len);
	   certPath[serial_len] = translateCertType(dwCertSpec);

	   //More than enough for long file paths...
	   filename = pCardData->pfnCspAlloc(max_path);

	   getCacheFilePath(certPath, filename, max_path);

	   if (readFromCache(filename, *ppbCertif))
	   {
		   *pcbCertif = cbCertif;
		   pCardData->pfnCspFree(filename);
		   return SCARD_S_SUCCESS;
	   }
   }

   // Certificate Not Cached

   PteidSelectApplet(pCardData);
   memset(recvbuf, 0, sizeof(recvbuf));
   /***************/
   /* Select File */
   /***************/
   Cmd [0] = 0x00;
   Cmd [1] = 0xA4; /* SELECT COMMAND */
   Cmd [2] = 0x00;
   Cmd [3] = 0x0C;
   Cmd [4] = 0x02; 
   Cmd [5] = 0x3F; //5F, (EF, 0C), ReadBinary(), (02, CertID)  
   Cmd [6] = 0x00;
   uiCmdLg = 7;

   // 00 A4 09 00 02 EF 09

   dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
                            &recvlen);
   SW1 = recvbuf[recvlen-2];
   SW2 = recvbuf[recvlen-1];
   
   if (!checkStatusCode(WHERE" -> select Dir Root", dwReturn, SW1, SW2))
		CLEANUP(dwReturn);

	Cmd[5] = 0x5F;
	memset(recvbuf, 0, sizeof(recvbuf));
	dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
		                    &recvlen);
	if (!checkStatusCode(WHERE" -> select Specific Dir", dwReturn, SW1, SW2))
		CLEANUP(dwReturn);
	
	if (!Is_Gemsafe)
	{
	Cmd[2] = 0x09; 
    Cmd[3] = 0x00;
	}
	Cmd[4] = 0x02;
	Cmd[5] = 0xEF;
    Cmd[6] = translateCertType(dwCertSpec);

    memset(recvbuf, 0, sizeof(recvbuf));
	dwReturn = SCardTransmit(pCardData->hScard, 
                            &ioSendPci, 
                            Cmd, 
                            uiCmdLg, 
                            &ioRecvPci, 
                            recvbuf, 
		                    &recvlen);
	if (!checkStatusCode(WHERE" -> select CertFile", dwReturn, SW1, SW2))
		CLEANUP(dwReturn);

   
   if ( *ppbCertif == NULL )
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "Error allocating memory for [*ppbCertif]");
      CLEANUP(SCARD_E_NO_MEMORY);
   }

   dwReturn = PteidReadFile(pCardData, 0, &cbCertif, *ppbCertif);
   if (dwReturn != SCARD_S_SUCCESS)
   {
      LogTrace(LOGTYPE_ERROR, WHERE, "PteidReadFile errorcode: [0x%02X]", dwReturn);
      CLEANUP(dwReturn);
   }
  
	/* Skip caching if running under the Certificate Propagation Service 
	   It would be painful to grab the cachedir because the relevant
	   environment variables APPLOCALDATA will point to somewhere under
	   %WINDIR% (i.e. not to user-writable directories)
	*/
  if (!runningUnderService())
  {
	   LogTrace(LOGTYPE_INFO, WHERE, "certPath: %s", filename);
	   CacheCertificate(filename, *ppbCertif, cbCertif);
	   pCardData->pfnCspFree(filename);
  }

   /* Certificate Length */
   *pcbCertif = cbCertif;

cleanup:
   return (dwReturn);
}
#undef WHERE


#define WHERE "PteidSelectApplet"
/**/
DWORD PteidSelectApplet(PCARD_DATA  pCardData)
{
	DWORD             dwReturn = 0;

	SCARD_IO_REQUEST  ioSendPci = {1, sizeof(SCARD_IO_REQUEST)};
	SCARD_IO_REQUEST  ioRecvPci = {1, sizeof(SCARD_IO_REQUEST)};

	unsigned char     Cmd[128];
	unsigned int      uiCmdLg = 0;

	unsigned char     recvbuf[256];
	unsigned long     recvlen = sizeof(recvbuf);
	BYTE              SW1, SW2;
	BYTE IAS_PTEID_APPLET_AID[] = {0x60, 0x46, 0x32, 0xFF, 0x00, 0x01, 0x02};
	BYTE GEMSAFE_APPLET_AID[] = {0x60, 0x46, 0x32, 0xFF, 0x00, 0x00, 0x02};
	BYTE              cAppletID = sizeof(IAS_PTEID_APPLET_AID);
	
	int               i = 0;

	/***************/
	/* Select File */
	/***************/
	Cmd [0] = 0x00;
	Cmd [1] = 0xA4; /* SELECT COMMAND 00 A4 04 0C 07 */
	Cmd [2] = 0x04;
	if (Is_Gemsafe)
		Cmd [3] = 0x00;
	else 
		Cmd [3] = 0x0C;
	Cmd [4] = 0x07;
	if (Is_Gemsafe)
		memcpy(&Cmd[5], GEMSAFE_APPLET_AID, sizeof(GEMSAFE_APPLET_AID));
	else
		memcpy(&Cmd[5], IAS_PTEID_APPLET_AID, cAppletID);

	uiCmdLg = 5 + cAppletID;

	dwReturn = SCardTransmit(pCardData->hScard, 
		&ioSendPci, 
		Cmd, 
		uiCmdLg, 
		&ioRecvPci, 
		recvbuf, 
		&recvlen);
	SW1 = recvbuf[recvlen-2];
	SW2 = recvbuf[recvlen-1];
	PteidDelayAndRecover(pCardData, SW1, SW2, dwReturn);
	if ( dwReturn != SCARD_S_SUCCESS )
	{
		LogTrace(LOGTYPE_ERROR, WHERE, "SCardTransmit errorcode: [0x%02X]", dwReturn);
		CLEANUP(dwReturn);
    }

	if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
	{
		LogTrace(LOGTYPE_ERROR, WHERE, "Select Applet Failed (wrong smartcard type?): [0x%02X][0x%02X]", SW1, SW2);
    
		if ( ( SW1 != 0x90 ) || ( SW2 != 0x00 ) )
		{
			LogTrace(LOGTYPE_ERROR, WHERE, "Select Applet Failed (wrong smartcard type?): [0x%02X][0x%02X]", SW1, SW2);
			CLEANUP(dwReturn);
		}
	}


cleanup:
	return (dwReturn);
}
#undef WHERE



/****************************************************************************************************/

/* CCID Features */
#define WHERE "CCIDfindFeature"
DWORD CCIDfindFeature(BYTE featureTag, BYTE* features, DWORD featuresLength) {
    DWORD idx = 0;
    int count;
    while (idx < featuresLength) {
        BYTE tag = features[idx];
        idx++;
        idx++;
        if (featureTag == tag) {
            DWORD feature = 0;
            for (count = 0; count < 3; count++) {
                feature |= features[idx] & 0xff;
                idx++;
                feature <<= 8;
            }
            feature |= features[idx] & 0xff;
            return feature;
        }
        idx += 4;
    }
    return 0;
}
#undef WHERE

/****************************************************************************************************/

#define WHERE "CCIDgetFeatures"
DWORD CCIDgetFeatures(PFEATURES pFeatures, SCARDHANDLE hCard) {
	BYTE pbRecvBuffer[200];
	DWORD dwRecvLength, dwReturn;
	pFeatures->VERIFY_PIN_START = 0;
	pFeatures->VERIFY_PIN_FINISH = 0;
	pFeatures->VERIFY_PIN_DIRECT = 0;
	pFeatures->MODIFY_PIN_START = 0;
	pFeatures->MODIFY_PIN_FINISH = 0;
	pFeatures->MODIFY_PIN_DIRECT = 0;
	pFeatures->GET_KEY_PRESSED = 0;
	pFeatures->ABORT = 0;

	dwReturn = SCardControl(hCard, 
		SCARD_CTL_CODE(3400),
		NULL,
		0,
		pbRecvBuffer,
		sizeof(pbRecvBuffer),
		&dwRecvLength);
	if ( SCARD_S_SUCCESS != dwReturn ) {
		LogTrace(LOGTYPE_ERROR, WHERE, "CCIDgetFeatures errorcode: [0x%02X]", dwReturn);
        CLEANUP(dwReturn);
	}
	pFeatures->VERIFY_PIN_START = CCIDfindFeature(FEATURE_VERIFY_PIN_START, pbRecvBuffer, dwRecvLength);
	pFeatures->VERIFY_PIN_FINISH = CCIDfindFeature(FEATURE_VERIFY_PIN_FINISH, pbRecvBuffer, dwRecvLength);
	pFeatures->VERIFY_PIN_DIRECT = CCIDfindFeature(FEATURE_VERIFY_PIN_DIRECT, pbRecvBuffer, dwRecvLength);
	pFeatures->MODIFY_PIN_START = CCIDfindFeature(FEATURE_MODIFY_PIN_START, pbRecvBuffer, dwRecvLength);
	pFeatures->MODIFY_PIN_FINISH = CCIDfindFeature(FEATURE_MODIFY_PIN_FINISH, pbRecvBuffer, dwRecvLength);
	pFeatures->MODIFY_PIN_DIRECT = CCIDfindFeature(FEATURE_MODIFY_PIN_DIRECT, pbRecvBuffer, dwRecvLength);
	pFeatures->GET_KEY_PRESSED = CCIDfindFeature(FEATURE_GET_KEY_PRESSED, pbRecvBuffer, dwRecvLength);
	pFeatures->ABORT = CCIDfindFeature(FEATURE_ABORT, pbRecvBuffer, dwRecvLength);
cleanup:
   return (dwReturn);
}

#undef WHERE

#define WHERE "createVerifyCommandGemPC"
DWORD createVerifyCommandGemPC(PPIN_VERIFY_STRUCTURE pVerifyCommand, unsigned int pin_ref) {
	char padding = 0;

	LogTrace(LOGTYPE_INFO, WHERE, "createVerifyCommandGemPC(): pinRef = %d", pin_ref);
    pVerifyCommand->bTimeOut = 30;
    pVerifyCommand->bTimeOut2 = 30;
    pVerifyCommand->bmFormatString = 0x82;
	pVerifyCommand -> bmPINBlockString = 0x00;
	pVerifyCommand -> bmPINLengthFormat = 0x00;
	pVerifyCommand -> wPINMaxExtraDigit= 0x0408; /* Min Max */
	
	pVerifyCommand -> bEntryValidationCondition = 0x02;
	/* validation key pressed */
	pVerifyCommand -> bNumberMessage = 0x01;
	 
	pVerifyCommand -> wLangId = 0x0816;  //Code smell #2
	pVerifyCommand -> bMsgIndex = 0x00;
	(pVerifyCommand -> bTeoPrologue)[0] = 0x00;
	pVerifyCommand -> bTeoPrologue[1] = 0x00;
	pVerifyCommand -> bTeoPrologue[2] = 0x00;

	pVerifyCommand->abData[0] = 0x00; // CLA
    pVerifyCommand->abData[1] = 0x20; // INS Verify
    pVerifyCommand->abData[2] = 0x00; // P1
    pVerifyCommand->abData[3] = pin_ref; // P2
    pVerifyCommand->abData[4] = 0x08; // Lc = 8 bytes in command data
	padding = Is_Gemsafe != 0 ? 0xFF: 0x2F;
	pVerifyCommand->abData[5] = padding;
    pVerifyCommand->abData[6] = padding; // Pin[1]
    pVerifyCommand->abData[7] = padding; // Pin[2]
    pVerifyCommand->abData[8] = padding; // Pin[3]
    pVerifyCommand->abData[9] = padding; // Pin[4]
    pVerifyCommand->abData[10] = padding; // Pin[5]
    pVerifyCommand->abData[11] = padding; // Pin[6]
    pVerifyCommand->abData[12] = padding; // Pin[7]

    pVerifyCommand->ulDataLength = 13;

	return 0;
}


#undef WHERE

#define WHERE "createVerifyCommand"
DWORD createVerifyCommandACR83(PPIN_VERIFY_STRUCTURE pVerifyCommand, unsigned int pin_ref) {
	char padding = 0;

	LogTrace(LOGTYPE_INFO, WHERE, "createVerifyCommandACR83(): pinRef = %d", pin_ref);
    pVerifyCommand->bTimeOut = 0x00;
    pVerifyCommand->bTimeOut2 = 0x00;
    pVerifyCommand->bmFormatString = 0x82;
	pVerifyCommand -> bmPINBlockString = 0x08;
	pVerifyCommand -> bmPINLengthFormat = 0x00;
	pVerifyCommand -> wPINMaxExtraDigit= 0x0408; /* Min Max */
	
	pVerifyCommand -> bEntryValidationCondition = 0x02;
	/* validation key pressed */
	pVerifyCommand -> bNumberMessage = 0x01;
	 
	pVerifyCommand -> wLangId = 0x0409;  //Code smell #2
	pVerifyCommand -> bMsgIndex = 0x00;
	(pVerifyCommand -> bTeoPrologue)[0] = 0x00;
	pVerifyCommand -> bTeoPrologue[1] = 0x00;
	pVerifyCommand -> bTeoPrologue[2] = 0x00;

	pVerifyCommand->abData[0] = 0x00; // CLA
    pVerifyCommand->abData[1] = 0x20; // INS Verify
    pVerifyCommand->abData[2] = 0x00; // P1
    pVerifyCommand->abData[3] = pin_ref; // P2
    pVerifyCommand->abData[4] = 0x08; // Lc = 8 bytes in command data
	padding = Is_Gemsafe != 0 ? 0xFF: 0x2F;
	pVerifyCommand->abData[5] = padding;
    pVerifyCommand->abData[6] = padding; // Pin[1]
    pVerifyCommand->abData[7] = padding; // Pin[2]
    pVerifyCommand->abData[8] = padding; // Pin[3]
    pVerifyCommand->abData[9] = padding; // Pin[4]
    pVerifyCommand->abData[10] = padding; // Pin[5]
    pVerifyCommand->abData[11] = padding; // Pin[6]
    pVerifyCommand->abData[12] = padding; // Pin[7]

    pVerifyCommand->ulDataLength = 13;

	return 0;



}
#undef WHERE



#define WHERE "createVerifyCommand"
DWORD createVerifyCommand(PPIN_VERIFY_STRUCTURE pVerifyCommand, unsigned int pin_ref) {
	char padding;
	LogTrace(LOGTYPE_INFO, WHERE, "createVerifyCommand(): pinRef = %d", pin_ref);
    pVerifyCommand->bTimeOut = 30;
    pVerifyCommand->bTimeOut2 = 30;
    pVerifyCommand->bmFormatString = 0x80 | 0x08 | 0x00 | 0x01;
    /*
     * bmFormatString. 
     *  01234567
     *  10001001
     *
     * bit 7: 1 = system units are bytes
     *
     * bit 6-3: 1 = PIN position in APDU command after Lc, so just after the
     * 0x20 | pinSize.
     * 
     * bit 2: 0 = left justify data
     * 
     * bit 1-0: 01 = BCD
     */

    pVerifyCommand->bmPINBlockString = 0x47;
    /*
     * bmPINBlockString
     * 
     * bit 7-4: 4 = PIN length
     * 
     * bit 3-0: 7 = PIN block size (7 times 0xff)
     */

    pVerifyCommand->bmPINLengthFormat = 0x04;
    /*
     * bmPINLengthFormat. weird... the values do not make any sense to me.
     * 
     * bit 7-5: 0 = RFU
     * 
     * bit 4: 0 = system units are bits
     * 
     * bit 3-0: 4 = PIN length position in APDU
     */


    pVerifyCommand->wPINMaxExtraDigit = BELPIC_MIN_USER_PIN_LEN << 8 | BELPIC_MAX_USER_PIN_LEN ;
    /*
     * First byte:  maximum PIN size in digit
     * 
     * Second byte: minimum PIN size in digit
     */

    pVerifyCommand->bEntryValidationCondition = 0x02;
    /*
     * 0x02 = validation key pressed. So the user must press the green
     * button on his pinpad.
     */

    pVerifyCommand->bNumberMessage = 0x01;
    /*
     * 0x01 = message with index in bMsgIndex
     */

    pVerifyCommand->wLangId = 0x1308;
    /*
     * We should support multiple languages for CCID devices with LCD screen
     */

    pVerifyCommand->bMsgIndex = 0x00;
    /*
     * 0x00 = PIN insertion prompt
     */

    pVerifyCommand->bTeoPrologue[0] = 0x00;
    pVerifyCommand->bTeoPrologue[1] = 0x00;
    pVerifyCommand->bTeoPrologue[2] = 0x00;
    /*
     * bTeoPrologue : only significant for T=1 protocol.
     */

    pVerifyCommand->abData[0] = 0x00; // CLA
    pVerifyCommand->abData[1] = 0x20; // INS Verify
    pVerifyCommand->abData[2] = 0x00; // P1
    pVerifyCommand->abData[3] = pin_ref; // P2
    pVerifyCommand->abData[4] = 0x08; // Lc = 8 bytes in command data
	padding = Is_Gemsafe != 0 ? 0xFF: 0x2F;
	
    pVerifyCommand->abData[5] = padding; // Pin[1]
    pVerifyCommand->abData[6] = padding; // Pin[2]
    pVerifyCommand->abData[7] = padding; // Pin[3]
    pVerifyCommand->abData[8] = padding; // Pin[4]
    pVerifyCommand->abData[9] = padding; // Pin[5]
    pVerifyCommand->abData[10] = padding; // Pin[6]
    pVerifyCommand->abData[11] = padding; // Pin[7]
	pVerifyCommand->abData[12] = padding; // Pin[8]

    pVerifyCommand->ulDataLength = 13;

    return 0;
}
/****************************************************************************************************/
