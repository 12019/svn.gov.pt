#include <iostream>
#include <assert.h>
#include <cstdio>
#ifdef __GNUC__
#include <cstdlib>
#include <cstring>
#endif
#include "eidlib.h"
#include "eidlibException.h"


#define TEST_NEWVERSION_SDK
#include "commonTests.h"


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


	test_PTEID_Init();
	test_PTEID_GetCardType();
	//test_PTEID_GetID();
	//test_PTEID_GetPic();
	//test_UnblockPIN();
	//test_UnblockPIN_Ext();

	//test_PTEID_GetAddr();
	//test_PTEID_GetCertificates();
	//test_VerifyPINs();
	//test_PTEID_GetPINs();

	//test_PTEID_ReadSOD();
	//test_PTEID_GetTokenInfo();
	//test_PTEID_IsActivated();
	//test_PTEID_selectADF();
	test_PTEID_ReadFile();

	//test_GetCardAuthenticationKey();
	//test_PTEID_GetCVCRoot();

	test_PTEID_Exit();

	writeToFile();


/*
	// PTEID_Init
	VERBOSE("*****PTEID_Init");
	error = PTEID_Init ( 0 );
	fprintf ( stdout, "PTEID_Init Result: %d\n",error);
	if (error != 0) {
		fprintf ( stderr, "PTEID_Init error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}
*/


	//PTEID_InitSDK();

	//	PTEID_ReleaseSDK();

	/*
	PTEID_ReaderContext& readerContext = ReaderSet.getReader();
	PTEID_InitSDK();
	 */
}
