#include <iostream>
#include <assert.h>
#include <cstdio>
#ifdef __GNUC__
#include <cstdlib>
#include <cstring>
#endif
#include "eidlib.h"
#include "eidlibException.h"


//#include "commonTests.h"


#define USAGE_STR "[-vs]\n\t-v: verbose\n\t-s: perform SOD checking"
#define VERBOSE(msg) if (verbose) { printf ( "%s\n", msg );} else {}
#define VERBOSE2(msg1,msg2) if (verbose) { printf ( "%s %s\n", msg1, msg2 );} else {}

static int verbose = 0;
static int SODchecking = 0;

using namespace std;
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


	while ((opt = getopt ( argc, argv, "vs" )) != -1) {
		switch (opt) {
		case 'v':
			verbose = 1;
			break;
		case 's':
			SODchecking = 1;
			break;
		default:
			fprintf ( stderr, "Usage: %s %s\n", argv[0], USAGE_STR );
			return 1;
		}
	}

	PTEID_InitSDK();

	// Get Reader Context
	PTEID_ReaderContext& readerContext = ReaderSet.getReader();
	if (!readerContext.isCardPresent())
	{
		cout << "No card found in the reader!" << endl;
	}else{
		cout << "Using Card Reader: " << readerContext.getName() << endl;
	}


	//Get Card
	PTEID_EIDCard &card = readerContext.getEIDCard();

	//Listing all PINS:
	PTEID_Pins &pins = card.getPins();

	cout << "Listing PINs: "<<endl;
	for (unsigned long PinIdx=0; PinIdx < pins.count(); PinIdx++)
	{
		PTEID_Pin&	Pin	= pins.getPinByNumber(PinIdx);
		cout << "PIN #" << PinIdx << ": " <<Pin.getLabel() << endl;
	}

	//Verify Pins
	unsigned long rem = 0;
	unsigned long &remaining_tries = rem;
	PTEID_Pin &pin_to_verify = pins.getPinByNumber(0);

	if (pin_to_verify.verifyPin("", remaining_tries, false)) {
		cout << pin_to_verify.getLabel() << " PIN verified successfully." << endl;
	} else{
		cout << pin_to_verify.getLabel() << " Wrong PIN Inserted" << endl;
	}




}
