//*****************************************************************************
// eID SDK sample code.
// This sample demonstrates how to use the eID SDK to add events on a card reader
//*****************************************************************************
#include <iostream>
#include <map>

#ifdef WIN32
#include <conio.h>
#include <windows.h>
#endif

#include "eidlib.h"
#include "eidlibException.h"

using namespace eIDMW;

//*****************************************************************************
// Main entry point
//*****************************************************************************
int main( int argc, char* argv[] )
{
	std::cout << "eID SDK sample program: get_exception" << std::endl;
	std::cout << std::endl;
	bool bStop = false;

	while(!bStop)
	{
		const char *readerName="test";
		PTEID_ReaderContext *reader=NULL;
		PTEID_SISCard *card=NULL;
		PTEID_XMLDoc *doc=NULL;
		PTEID_SisId *docId=NULL;

		try
		{
			reader = &ReaderSet.getReaderByName(readerName);
		}
		catch(PTEID_ExParamRange &ex)
		{
			std::cout << "SUCCESS => The reader named " << readerName << " does not exist" << std::endl;
		}
		catch(PTEID_Exception &ex)
		{
			std::cout << "FAILS => Other PTEID_Exception (code = " << std::hex << ex.GetError() << ")" << std::endl;
			goto end;
		}
		catch(...)
		{
			std::cout << "FAILS => Other exception" << std::endl;
			goto end;
		}

		try
		{
			reader = &ReaderSet.getReader();
			std::cout << "SUCCESS => Reader found" << std::endl;
		}
		catch(PTEID_ExNoReader &ex)
		{
			std::cout << "FAILS => No reader found" << std::endl;
			goto end;
		}
 		catch(PTEID_Exception &ex)
		{
			std::cout << "FAILS => Other PTEID_Exception (code = " << std::hex << ex.GetError() << ")" << std::endl;
			goto end;
		}
		catch(...)
		{
			std::cout << "FAILS => Other exception" << std::endl;
			goto end;
		}

		try
		{
			card = &reader->getSISCard();
			std::cout << "SUCCESS => SIS card found" << std::endl;
		}
		catch(PTEID_ExNoCardPresent &ex)
		{
			std::cout << "FAILS => No card found" << std::endl;
			goto end;
		}
		catch(PTEID_ExCardBadType &ex)
		{
			std::cout << "FAILS => This is not a SIS card" << std::endl;
			goto end;
		}
		catch(PTEID_Exception &ex)
		{
			std::cout << "FAILS => Other PTEID_Exception (code = " << std::hex << ex.GetError() << ")" << std::endl;
			goto end;
		}
		catch(...)
		{
			std::cout << "FAILS => Other exception" << std::endl;
			goto end;
		}

		try
		{
			doc = &card->getDocument(PTEID_DOCTYPE_PICTURE);
		}
		catch(PTEID_ExDocTypeUnknown &ex)
		{
			std::cout << "SUCCESS => No picture on this card" << std::endl;
		}
 		catch(PTEID_Exception &ex)
		{
			std::cout << "FAILS => Other PTEID_Exception (code = " << std::hex << ex.GetError() << ")" << std::endl;
			goto end;
		}
		catch(...)
		{
			std::cout << "FAILS => Other exception" << std::endl;
			goto end;
		}

		try
		{
			doc = &card->getDocument(PTEID_DOCTYPE_ID);
			docId=dynamic_cast<PTEID_SisId *>(doc);
			std::cout << "SUCCESS => Your name is " << docId->getName() << std::endl;
		}
		catch(PTEID_Exception &ex)
		{
			std::cout << "FAILS => Other PTEID_Exception (code = " << std::hex << ex.GetError() << ")" << std::endl;
			goto end;
		}
		catch(...)
		{
			std::cout << "FAILS => Other exception" << std::endl;
			goto end;
		}

end:
		std::cout << std::endl <<	"Press 'q' to quit" << std::endl;
		std::cout <<				"Another key to start again" << std::endl;
		char c=getchar();
		if(c=='q' || c=='Q')
			bStop = true;
	}

	PTEID_ReleaseSDK();

}


