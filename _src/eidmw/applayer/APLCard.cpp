/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2008-2009 FedICT.
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
#include "APLReader.h"
#include "APLCard.h"
#include "APLCrypto.h"
#include "APLCertif.h"
#include "APLConfig.h"
#include "CardFile.h"
#include "CardLayer.h"
#include "cryptoFwkPteid.h"
#include "CardPteidDef.h"
#include "XadesSignature.h"
#include "SigContainer.h"
#include "MiscUtil.h"

#include <time.h>
#include <sys/types.h>

namespace eIDMW
{

#define CHALLENGE_LEN                  20

/*****************************************************************************************
---------------------------------------- APL_Card --------------------------------------------
*****************************************************************************************/
APL_CryptoFwk *APL_Card::m_cryptoFwk=NULL;

APL_Card::APL_Card(APL_ReaderContext *reader)
{
	if(!m_cryptoFwk)
		m_cryptoFwk=AppLayer.getCryptoFwk();

	m_reader=reader;
}

APL_Card::~APL_Card()
{
}

bool APL_Card::isVirtualCard() const
{
	return m_reader->isVirtualReader();
}

CReader *APL_Card::getCalReader() const
{
	return m_reader->getCalReader();
}

APL_CardType APL_Card::getType() const
{
	return APL_CARDTYPE_UNKNOWN;
}

void APL_Card::CalLock()
{
	return m_reader->CalLock();
}

void APL_Card::CalUnlock()
{
	return m_reader->CalUnlock();
}

unsigned long APL_Card::readFile(const char *csPath, CByteArray &oData, unsigned long  ulOffset, unsigned long  ulMaxLength)
{
	if(m_reader->isVirtualReader())
		return m_reader->getSuperParser()->readData(csPath,oData);

	BEGIN_CAL_OPERATION(m_reader)
	oData = m_reader->getCalReader()->ReadFile(csPath,ulOffset,(ulMaxLength==0 ? FULL_FILE : ulMaxLength));
	END_CAL_OPERATION(m_reader)

	return oData.Size();
}

bool APL_Card::writeFile(const char *csPath, const CByteArray& oData,unsigned long ulOffset)
{
	if(m_reader->isVirtualReader()) //Virtual Reader
		return false;

	BEGIN_CAL_OPERATION(m_reader)
	m_reader->getCalReader()->WriteFile(csPath,ulOffset,oData);
	END_CAL_OPERATION(m_reader)

	return true; //Otherwise, there is exception
}

CByteArray APL_Card::sendAPDU(const CByteArray& cmd)
{
	if(m_reader->isVirtualReader()) //Virtual Reader
		return CByteArray();

	CByteArray out;

	BEGIN_CAL_OPERATION(m_reader)
	out = m_reader->getCalReader()->SendAPDU(cmd);
	END_CAL_OPERATION(m_reader)

	return out;
}

CByteArray APL_Card::Sign(const CByteArray & oData, bool signatureKey)
{
	if(m_reader->isVirtualReader()) //Virtual Reader
		return CByteArray();

	CByteArray out;
	BEGIN_CAL_OPERATION(m_reader)
	tPrivKey signing_key;
    //Private key IDs can be found with pkcs15-tool --list-keys from OpenSC package
	if (signatureKey)
		signing_key = m_reader->getCalReader()->GetPrivKeyByID(0x46); 
	else
		signing_key = m_reader->getCalReader()->GetPrivKeyByID(0x45);

	out = m_reader->getCalReader()->Sign(signing_key, SIGN_ALGO_RSA_PKCS, oData);
	END_CAL_OPERATION(m_reader)

	return out;
}

bool checkExistingFiles(const char **files, unsigned int n_paths)
{
	for(unsigned int i=0; i != n_paths; i++)
	{
		if (!CPathUtil::existFile(files[i]))	
			return false;
	}

	return true;
}


CByteArray &APL_Card::SignXades(const char ** paths, unsigned int n_paths, const char *output_path)
{
	if (paths == NULL || n_paths < 1 || !checkExistingFiles(paths, n_paths))
	   throw CMWEXCEPTION(EIDMW_ERR_CHECK);
	
	XadesSignature sig(this);

	CByteArray &signature = sig.SignXades(paths, n_paths, false);
	StoreSignatureToDisk (signature, paths, n_paths,output_path);

	//Write zip container signature and referenced files in zip container

	return signature;
}

void replace_lastdot_inplace(char* str_in)
{
	// We can only search forward because memrchr and strrchr 
	// are not available on Windows *sigh*
	char ch = '.';
	char * pdest = str_in, *last_dot= NULL;
       	while ((pdest = strchr(pdest, ch)) != NULL)
	{
	     last_dot = pdest;
	     pdest++;
	}

	// Don't replace '.' if its a UNIX dotfile
	if (last_dot != NULL && *(last_dot-1) != '/')
		*last_dot = '_';
}

#ifdef WIN32
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

char *generateFinalPath(const char *output_dir, const char *path)
{

	char * zip_filename = Basename((char*)path);
	//We need a local copy of basename(path) because basename may return a pointer to some part
	//of its argument and we don't want to change the input by replacing the last dot
	char * tmp_path = new char[strlen(zip_filename)+1];
	strcpy(tmp_path, zip_filename);

	replace_lastdot_inplace(tmp_path);

	//Buffer for the filename components plus ".zip" and terminating NULL
	char *final_path = new char[strlen(output_dir)+strlen(tmp_path)+6];
	sprintf(final_path, "%s" PATH_SEP "%s.zip", output_dir, tmp_path);
	delete []tmp_path;

	return final_path;
}

void APL_Card::SignXadesIndividual(const char ** paths, unsigned int n_paths, const char *output_dir)
{
	SignIndividual(paths, n_paths, output_dir, false);
}

void APL_Card::SignXadesTIndividual(const char ** paths, unsigned int n_paths, const char *output_dir)
{
	SignIndividual(paths, n_paths, output_dir, true);
}

// Implementation of the PIN-caching version of Xades-T
// It signs each input file seperately and creates a .zip container for each
void APL_Card::SignIndividual(const char ** paths, unsigned int n_paths, const char *output_dir, bool timestamp)
{

	if (paths == NULL || n_paths < 1 || !checkExistingFiles(paths, n_paths))
	   throw CMWEXCEPTION(EIDMW_ERR_CHECK);

	XadesSignature sig(this);
        const char **files_to_sign = new const char*[1];

	for (unsigned int i=0; i!= n_paths; i++)
	{

		files_to_sign[0] = paths[i];
		CByteArray &signature = sig.SignXades(files_to_sign, 1, timestamp);
		
		const char *output_file = generateFinalPath(output_dir, paths[i]);
		StoreSignatureToDisk (signature, files_to_sign, 1, output_file);
		delete []output_file;

		//Set SSO on after first iteration to avoid more PinCmd() user interaction for the remaining 
		// iterations
		if (i==0)
			getCalReader()->setSSO(true);
	}

	getCalReader()->setSSO(false);

}

CByteArray &APL_Card::SignXadesT(const char ** paths, unsigned int n_paths, const char *output_file)
{
	if (paths == NULL || n_paths < 1 || !checkExistingFiles(paths, n_paths))
	   throw CMWEXCEPTION(EIDMW_ERR_CHECK);
	XadesSignature sig(this);

	CByteArray &signature = sig.SignXades(paths, n_paths, true);
	StoreSignatureToDisk (signature, paths, n_paths, output_file);

	//Write zip container signature and referenced files in zip container

	return signature;
}

bool APLVerifySignature(const char *container_path, char * errors, unsigned long* error_len)
{

	if (strlen(container_path) == 0)
		throw CMWEXCEPTION(EIDMW_ERR_CHECK);

	tHashedFile **hashes = NULL;
	int i = 0;
	Container *container = new Container(container_path);
	int n_files = 0;

	hashes = container->getHashes(&n_files);

	CByteArray *sig_content = container->ExtractSignature();

	delete container;
	if (sig_content == NULL)
		throw CMWEXCEPTION(EIDMW_ERR_CHECK);
	
	return XadesSignature::ValidateXades(*sig_content, hashes, errors, error_len);
}


/*****************************************************************************************
---------------------------------------- APL_MemoryCard ----------------------------------
*****************************************************************************************/
APL_MemoryCard::APL_MemoryCard(APL_ReaderContext *reader):APL_Card(reader)
{
}

APL_MemoryCard::~APL_MemoryCard()
{
}

/*****************************************************************************************
---------------------------------------- APL_SmartCard -----------------------------------
*****************************************************************************************/
APL_SmartCard::APL_SmartCard(APL_ReaderContext *reader):APL_Card(reader)
{
	m_pins=NULL;
	m_certs=NULL;
	m_fileinfo=NULL;

	APL_Config conf_allowTest(CConfig::EIDMW_CONFIG_PARAM_CERTVALID_ALLOWTESTC);     
	m_allowTestParam = conf_allowTest.getLong()?true:false;

	m_allowTestAsked=false;
	m_allowTestAnswer=false;
	m_allowBadDate=true;

	m_challenge=NULL;
	m_challengeResponse=NULL;
	m_RootCAPubKey = NULL;

	m_certificateCount=COUNT_UNDEF;
	m_pinCount=COUNT_UNDEF;
}

APL_SmartCard::~APL_SmartCard()
{
	if(m_pins)
	{
		delete m_pins;
		m_pins=NULL;
	}

	if(m_certs)
	{
		delete m_certs;
		m_certs=NULL;
	}

	if(m_fileinfo)
	{
		delete m_fileinfo;
		m_fileinfo=NULL;
	}

	if(m_challenge)
	{
		delete m_challenge;
		m_challenge=NULL;
	}

	if(m_challengeResponse)
	{
		delete m_challengeResponse;
		m_challengeResponse=NULL;
	}

	if (m_RootCAPubKey)
	{
		delete m_RootCAPubKey;
		m_RootCAPubKey = NULL;
	}

}

APL_CardFile_Info *APL_SmartCard::getFileInfo()
{
	if(!m_fileinfo)
	{
		CAutoMutex autoMutex(&m_Mutex);		//We lock for unly one instanciation
		if (!m_fileinfo)						//We test again to be sure it isn't instanciated between the first if and the lock
		{
			m_fileinfo=new APL_CardFile_Info(this);
		}
	}

	return m_fileinfo;
}

void APL_SmartCard::getInfo(CByteArray &info)
{
	if(m_reader->isVirtualReader()) //Virtual Reader
	{
		m_reader->getSuperParser()->readData(PTEID_FILE_CARDINFO,info);
	}
	else
	{
		BEGIN_CAL_OPERATION(m_reader)
		info=m_reader->getCalReader()->GetInfo();
		END_CAL_OPERATION(m_reader)
	}
}

void APL_SmartCard::selectApplication(const CByteArray &applicationId) const
{
	if(m_reader->isVirtualReader()) //Virtual Reader
		return;

	BEGIN_CAL_OPERATION(m_reader)
	m_reader->getCalReader()->SelectApplication(applicationId);
	END_CAL_OPERATION(m_reader)
}

CByteArray APL_SmartCard::sendAPDU(const CByteArray& cmd,APL_Pin *pin,const char *csPinCode)
{
	if(m_reader->isVirtualReader()) //Virtual Reader
		return CByteArray();

	unsigned long lRemaining=0;
	if(pin)
		if(csPinCode != NULL)
			pin->verifyPin(csPinCode,lRemaining);

	return APL_Card::sendAPDU(cmd);
}

unsigned long APL_SmartCard::readFile(const char *csPath, CByteArray &oData, unsigned long  ulOffset, unsigned long  ulMaxLength)
{
	return APL_Card::readFile(csPath,oData,ulOffset,ulMaxLength);
}

unsigned long APL_SmartCard::readFile(const char *fileID, CByteArray &in,APL_Pin *pin,const char *csPinCode)
{
	unsigned long lRemaining=0;
	if(pin)
		if(csPinCode != NULL)
			pin->verifyPin(csPinCode,lRemaining);


	return readFile(fileID,in,0UL,0UL);
}

bool APL_SmartCard::writeFile(const char *fileID,const CByteArray &out,APL_Pin *pin,const char *csPinCode)
{
	unsigned long lRemaining=0;

	if(pin)
		if(csPinCode != NULL)
			pin->verifyPin(csPinCode,lRemaining);

	return APL_Card::writeFile(fileID,out);
}

unsigned long APL_SmartCard::pinCount() 
{ 
	if(m_reader->isVirtualReader()) //Virtual Reader
		return 0;

	if(m_pinCount==COUNT_UNDEF)
	{
		try
		{
			BEGIN_CAL_OPERATION(m_reader)
			m_pinCount =  m_reader->getCalReader()->PinCount();
			END_CAL_OPERATION(m_reader)
		}
		catch(...)
		{
			m_pinCount = 0;
		}
	}

	return m_pinCount;
}

APL_Pins *APL_SmartCard::getPins()
{
	if(!m_pins)
	{
		CAutoMutex autoMutex(&m_Mutex);		//We lock for unly one instanciation
		if (!m_pins)				//We test again to be sure it isn't instanciated between the first if and the lock
		{
			m_pins=new APL_Pins(this);
		}
	}

	return m_pins;
}

tPin APL_SmartCard::getPin(unsigned long ulIndex)
{
	
	if(ulIndex<0 || ulIndex>=pinCount())
		throw CMWEXCEPTION(EIDMW_ERR_CHECK);
	
	tPin out;

	BEGIN_CAL_OPERATION(m_reader)
	out = m_reader->getCalReader()->GetPin(ulIndex);
	END_CAL_OPERATION(m_reader)

	return out;
}

unsigned long APL_SmartCard::pinStatus(const tPin &Pin)
{	
	if(m_reader->isVirtualReader()) //Virtual Reader
		return 0;

	unsigned long out=0;

	BEGIN_CAL_OPERATION(m_reader)
	out = m_reader->getCalReader()->PinStatus(Pin);
	END_CAL_OPERATION(m_reader)

	return out;
}

bool APL_SmartCard::pinCmd(tPinOperation operation, const tPin &Pin,
		const char *csPin1In, const char *csPin2In,
		unsigned long &ulRemaining, bool bShowDlg)
{
	if(m_reader->isVirtualReader()) //Virtual Reader
		return false;

	bool ret=false;

	const char *csPin1=csPin1In;
	if(!csPin1)
		csPin1="";

	const char *csPin2=csPin2In;
	if(!csPin2)
		csPin2="";

	BEGIN_CAL_OPERATION(m_reader)
	ret=m_reader->getCalReader()->PinCmd(operation,Pin,csPin1,csPin2,ulRemaining,bShowDlg);
	END_CAL_OPERATION(m_reader)

	return ret;
}

unsigned long APL_SmartCard::certificateCount()
{
	if(m_reader->isVirtualReader()) //Virtual Reader
		return 0;

	if(m_certificateCount==COUNT_UNDEF)
	{
		BEGIN_CAL_OPERATION(m_reader)
		m_certificateCount = m_reader->getCalReader()->CertCount();
		END_CAL_OPERATION(m_reader)
	}

	return m_certificateCount;
}

APL_Certifs *APL_SmartCard::getCertificates()
{
	if(!m_certs)
	{
		CAutoMutex autoMutex(&m_Mutex);		//We lock for only one instantiation
		if (!m_certs)						//We test again to be sure it isn't instantiated between the first if and the lock
		{
			m_certs=new APL_Certifs(this);
			for(unsigned long ulIndex=0;ulIndex<certificateCount();ulIndex++)
			{
				APL_Certif *cert=NULL;
				cert=m_certs->getCertFromCard(ulIndex);
			}
		}
	}

	return m_certs;
}

tCert APL_SmartCard::getP15Cert(unsigned long ulIndex)
{
	if(ulIndex<0 || ulIndex>=certificateCount())
		throw CMWEXCEPTION(EIDMW_ERR_CHECK);

	tCert out;

	BEGIN_CAL_OPERATION(m_reader)
	out = m_reader->getCalReader()->GetCert(ulIndex);
	END_CAL_OPERATION(m_reader)

	return out;
}

bool APL_SmartCard::isTestCard()
{
	return false;
}

bool APL_SmartCard::getAllowTestCard()
{

	return true;
}

void APL_SmartCard::setAllowTestCard(bool allow)
{
	m_allowTestAnswer=allow;

	m_allowTestAsked=true;
}

bool APL_SmartCard::getAllowBadDate()
{
	return m_allowBadDate;
}

void APL_SmartCard::setAllowBadDate(bool allow)
{
	m_allowBadDate=allow;
}

void APL_SmartCard::initChallengeResponse()
{
	CAutoMutex autoMutex(&m_Mutex);		//We lock for unly one instanciation

	if(!m_challenge)
	{
		m_challenge=new CByteArray(CHALLENGE_LEN);
		srand((int)clock());
	}
	m_challenge->ClearContents();

	if(!m_challengeResponse)
	{
		m_challengeResponse=new CByteArray;
	}
	m_challengeResponse->ClearContents();

	if(m_reader->isVirtualReader()) //Virtual Reader
	{
		m_reader->getSuperParser()->readData(PTEID_FILE_CHALLENGE,*m_challenge);
		m_reader->getSuperParser()->readData(PTEID_FILE_CHALLENGE_RESPONSE,*m_challengeResponse);
	}
	else
	{
		//The challenge MUST NOT COME from the card
		//*m_challenge=m_calreader->GetRandom(CHALLENGE_LEN);
		unsigned char byte;
		for(int i=0;i<CHALLENGE_LEN;i++)
		{
			byte=(unsigned char)((double)0x100*(double)rand()/(double)RAND_MAX);
			m_challenge->Append(byte);
		}

		*m_challengeResponse=getChallengeResponse(*m_challenge);
	}
}

const CByteArray &APL_SmartCard::getChallenge(bool bForceNewInit)
{
	if(!m_challenge || bForceNewInit)
		initChallengeResponse();

	return *m_challenge;
}

const CByteArray &APL_SmartCard::getChallengeResponse()
{
	if(!m_challengeResponse)
		initChallengeResponse();

	return *m_challengeResponse;
}

CByteArray APL_SmartCard::getChallengeResponse(const CByteArray &challenge) const
{
	CByteArray request;
	request.Append(0x81);
	request.Append(challenge);

	CByteArray out;

	BEGIN_CAL_OPERATION(m_reader)
	out = m_reader->getCalReader()->Ctrl(CTRL_PTEID_INTERNAL_AUTH,request);
	END_CAL_OPERATION(m_reader)

	return out;
}

bool APL_SmartCard::verifyChallengeResponse(const CByteArray &challenge, const CByteArray &response) const
{
	if(m_reader->isVirtualReader())
		return false;

	CByteArray newResponse=getChallengeResponse(challenge);
	return newResponse.Equals(response);
}

}
