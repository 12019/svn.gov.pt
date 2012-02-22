#include <iostream>
#include <assert.h>
#include <cstdio>
#include <fstream>
#ifdef __GNUC__
#include <cstdlib>
#include <cstring>
#endif
#include "eidlib.h"
#include "eidlibException.h"

#define USAGE_STR "[-vspfjxh]\n\t-v: verbose\n\t-s: perform SOD checking\n\t-p: verify pins\n\t-f: get picture (png format)\n\t-j: get picture (jpeg2000 format)\n\t-x: get ID in XML format\n\t-h: display help"
#define VERBOSE(msg) if (verbose) { printf ( "%s\n", msg );} else {}
#define VERBOSE2(msg1,msg2) if (verbose) { printf ( "%s %s\n", msg1, msg2 );} else {}

static int verbose = 0;
static int SODchecking = 0;
static int verpins = 0;
static int showpicturepng = 0;
static int showpicturejp2000 = 0;
static int xmldoc = 1;

using namespace eIDMW;

/*

// Compatibility Method
long PTEID_Init(int i){
	try{
		PTEID_InitSDK();
		PTEID_ReaderContext &reader = ReaderSet.getReader();
		PTEID_EIDCard &card = reader.getEIDCard();
	}
	catch(PTEID_ExCardBadType &ex)
	{
		std::cout << "This is not an eid card" << std::endl;

	}
	catch(PTEID_ExNoCardPresent &ex)
	{
		std::cout << "No card present" << std::endl;
		return -1104;
	}
	catch(PTEID_ExNoReader &ex)
	{
		std::cout << "No reader found" << std::endl;
		return -1101;
	}
	catch(PTEID_Exception &ex)
	{
		std::cout << "PTEID_Exception exception" << std::endl;
	}
	catch(...)
	{
		std::cout << "Other exception" << std::endl;
		return -1;
	}
	return 0;
}
*/



int main(int argc, char **argv)
{
	int opt;
	int optind;
	int error;
//	tCardType ctype;
//	PTEID_Pins pins;


	while ((opt = getopt ( argc, argv, "vspfjxh" )) != -1) {
		switch (opt) {
		case 'v':
			verbose = 1;
			break;
		case 's':
			SODchecking = 1;
			break;
		case 'p':
			verpins = 1;
			break;
		case 'f':
			showpicturepng = 1;
			break;
		case 'j':
			showpicturejp2000 = 1;
			break;
		case 'x':
			xmldoc = 1;
			break;
		case 'h':
		  	fprintf ( stderr, "Usage: %s %s\n", argv[0], USAGE_STR );
			return 0;
		default:
			fprintf ( stderr, "Usage: %s %s\n", argv[0], USAGE_STR );
			return 0;
		}
	}

	PTEID_InitSDK();

	// Get Reader Context
	PTEID_ReaderContext& readerContext = ReaderSet.getReader();
	if (!readerContext.isCardPresent())
	{
		std::cout << "No card found in the reader!" << std::endl;
	}else{
		std::cout << "Using Card Reader: " << readerContext.getName() << std::endl;
	}


	//Get Card
	PTEID_EIDCard &card = readerContext.getEIDCard();


	//Listing all PINS:
	if (verpins == 1)
	{
		PTEID_Pins &pins = card.getPins();

		std::cout << "Listing PINs: "<< std::endl;
		for (unsigned long PinIdx=0; PinIdx < pins.count(); PinIdx++)
		{
			PTEID_Pin&	Pin	= pins.getPinByNumber(PinIdx);
			std::cout << "PIN #" << PinIdx << ": " <<Pin.getLabel() << std::endl;
		}

		//Verify Pins
		unsigned long rem = 0;
		unsigned long &remaining_tries = rem;
		PTEID_Pin &pin_to_verify = pins.getPinByNumber(0);

		if (pin_to_verify.verifyPin("", remaining_tries, false)) {
			std::cout << pin_to_verify.getLabel() << " PIN verified successfully." << std::endl;
		} else{
			std::cout << pin_to_verify.getLabel() << " Wrong PIN Inserted" << std::endl;
		}
	}
	
	//Get Picture in png format
	if (showpicturepng == 1)
	{
		PTEID_EId& pteid_eid    = card.getID();
		PTEID_ByteArray &pic = pteid_eid.getPhotoObj().getphoto();
		pic.writeToFile("idpicture.png");
	}

	//Get Picture in jpeg2000 format
	if (showpicturejp2000 == 1)
	{
		PTEID_EId& pteid_eid    = card.getID();
		PTEID_ByteArray &pic = pteid_eid.getPhotoObj().getphotoRAW();
		pic.writeToFile("idpicture.jp2");
	}
	
	//Get xml from card Fields
	if (xmldoc == 1)
	{
		PTEID_XmlUserRequestedInfo *info = new PTEID_XmlUserRequestedInfo();
		
		//Adding XML Fields
		info->add(XML_PHOTO);
        info->add(XML_NAME);
        info->add(XML_MRZ1);
        info->add(XML_MRZ2);
        info->add(XML_MRZ3);

		PTEID_CCXML_Doc &ccxml = card.getXmlCCDoc(*info);
		
		std::string s = ccxml.getCCXML();
		
		std::ofstream mynfile;
		mynfile.open("xmlidtest.xml");
		mynfile << s;
		mynfile.close();
	}

	//Always release the SDK before exit application.
	PTEID_ReleaseSDK();
	exit(0);
}
