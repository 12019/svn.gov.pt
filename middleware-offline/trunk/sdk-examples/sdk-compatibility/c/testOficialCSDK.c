#include <pteid/pteidlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <openssl/x509.h>
#include <fcntl.h>

#include <string.h>

#include "ccerrors.h"


#define TEST_OFICIAL_SDK
#include "commonTests.h"




#define USAGE_STR "[-vs]\n\t-v: verbose\n\t-s: perform SOD checking"
#define VERBOSE(msg) if (verbose) { printf ( "%s\n", msg );} else {}
#define VERBOSE2(msg1,msg2) if (verbose) { printf ( "%s %s\n", msg1, msg2 );} else {}




static int verbose = 1;
static int SODchecking = 0;




/*
//
// AUXILIAR ERROR CODES
//
static char * PTEID_errors[] = {
		"",
		"Invalid parameter (NULL pointer, out of bound, etc.)",
		"An internal consistency check failed",
		"The data buffer to receive returned data is too small",
		"Input on pinpad cancelled",
		"Timout returned from pinpad",
		"The two PINs did not match",
		"Message too long on pinpad",
		"Invalid PIN length",
		"Library not initialized",
		"An internal error has been detected, but the source is unknown",
};

static char * PTEID_OPENSC_errors_1100 [] = {
		"Reader error",
		"No readers found",
		"Slot not found",
		"Slot already connected",
		"Card not present",
		"Card removed",
		"Card reset",
		"Transmit failed",
		"Timout returned from pinpad",
		"Pinp+ad cancelled",
		"The two PINs did not match",
		"Message too long on pinpad",
		"Event timeout",
		"Card unresponsive",
		"Reader detached",
		"Reader reattached"
};

static char * PTEID_OPENSC_errors_1200 [] = {
		"Card command failed",
		"Card file not found",
		"Card file record not found",
		"Card object class not supported",
		"Card insertion not supported",
		"Card command incorrect parameters",
		"Card command wrong length",
		"Card memory failure",
		"No card support",
		"Card command not allowed",
		"Invalid card",
		"Card security status not satisfied",
		"Card authentication method blocked",
		"Unknown data received by card",
		"Card PIN incorrect",
		"Card file already exists"
};

static char * PTEID_OPENSC_errors_1300 [] = {
		"OpenSC invalid arguments",
		"OpenSC command too short",
		"OpenSC command too long",
		"OpenSC buffer too small",
		"OpenSC invalid PIN length"
};

static char * PTEID_OPENSC_errors_1400 [] = {
		"OpenSC internal error",
		"OpenSC invalid ASN.1 object",
		"OpenSC ASN.1 object not found",
		"OpenSC ASN.1 end of contents",
		"OpenSC out of memory",
		"OpenSC too many objects",
		"OpenSC object not valid",
		"OpenSC object not found",
		"OpenSC not supported",
		"OpenSC passphrase required",
		"OpenSC extractable key",
		"OpenSC decryption failed",
		"OpenSC worng padding",
		"OpenSC wrong card"
};

static char * PTEID_OPENSC_errors_1500 [] = {
		"PKCS #15 init",
		"PKCS #15 syntax error",
		"PKCS #15 inconsistent profile",
		"PKCS #15 incompatible key",
		"PKCS #15 no default key",
		"PKCS #15 ID not unique",
		"PKCS #15 cannot load key"
};

static char * PTEID_OPENSC_errors_1900 [] = {
		"Unknown error",
		"PKCS #15 application not found"
};

char *
PTEID_errorString ( long code )
{

	if (code > 0)
		return PTEID_errors[code];
	else if (code <= -1900)
		return PTEID_OPENSC_errors_1900[-code-1900];
	else if (code <= -1500)
		return PTEID_OPENSC_errors_1500[-code-1500];
	else if (code <= -1400)
		return PTEID_OPENSC_errors_1400[-code-1400];
	else if (code <= -1300)
		return PTEID_OPENSC_errors_1300[-code-1300];
	else if (code <= -1200)
		return PTEID_OPENSC_errors_1300[-code-1200];
	else
		return PTEID_OPENSC_errors_1100[-code-1100];
}


void
PTEID_error ( char * msg, long code )
{
	fprintf ( stderr, "Error code in \"%s\": %s\n", msg,
			PTEID_errorString ( code ) );
	exit ( 1 );
}
*/

/*
void
dumpId ( PTEID_ID * id )
{
	printf ( "Version: %hd\n", id->version );
	printf ( "Delivery Entity: %s\n", id->deliveryEntity );
	printf ( "Country: %s\n", id->country );
	printf ( "Document type: %s\n", id->documentType );
	printf ( "Card number: %s\n", id->cardNumber );
	printf ( "Card number PAN: %s\n", id->cardNumberPAN );
	printf ( "Card version: %s\n", id->cardVersion );
	printf ( "Delivery date: %s\n", id->deliveryDate );
	printf ( "Locale: %s\n", id->locale );
	printf ( "validity date: %s\n", id->validityDate );
	printf ( "Name: %s\n", id->name );
	printf ( "First name: %s\n", id->firstname );
	printf ( "Sex: %s\n", id->sex );
	printf ( "Nationality: %s\n", id->nationality );
	printf ( "Birth date: %s\n", id->birthDate );
	printf ( "Height: %s\n", id->height );
	printf ( "BI: %s\n", id->numBI );
	printf ( "Father name: %s\n", id->nameFather );
	printf ( "Father first name: %s\n", id->firstnameFather );
	printf ( "Mother name: %s\n", id->nameMother );
	printf ( "Mother first name: %s\n", id->firstnameMother );
	printf ( "NIF: %s\n", id->numNIF );
	printf ( "SS: %s\n", id->numSS );
	printf ( "SNS: %s\n", id->numSNS );
	printf ( "MRZ1: %s\n", id->mrz1 );
	printf ( "MRZ2: %s\n", id->mrz2 );
	printf ( "MRZ3: %s\n", id->mrz3 );
}
*/

/*
void
dumpCertificates ( PTEID_Certifs * certs )
{
	int i;
	int fd;
	unsigned char * asn1cert;
	X509 * cert;
	RSA * rsaKey;

	for (i = 0; i < certs->certificatesLength; i++) {
		printf ( "Certificate %d:\n\tLabel = %s\n\tBytes = %ld\n", i,
				certs->certificates[i].certifLabel,
				certs->certificates[i].certifLength );
		cert = 0;
		asn1cert = certs->certificates[i].certif;
		cert = d2i_X509 ( &cert, (const unsigned char **) &asn1cert,
				certs->certificates[i].certifLength );
		assert (cert != 0);
		printf ( "\tX.509 fields:\n" );
		printf ( "\t\tVersion: %ld\n", ASN1_INTEGER_get ( cert->cert_info->version ) );
		printf ( "\t\tIssuer: %s\n", X509_NAME_oneline ( cert->cert_info->issuer, 0, 0 ) );
		printf ( "\t\tSubject: %s\n", X509_NAME_oneline ( cert->cert_info->subject, 0, 0 ) );
		printf ( "\t\tName: %s\n", cert->name );
		rsaKey = EVP_PKEY_get1_RSA ( X509_PUBKEY_get ( cert->cert_info->key ) );
		assert (rsaKey != 0);
		printf ( "\t\tPublic key:\n" );
		printf ( "\t\t\tModulus (n): %s (%d bits)\n", BN_bn2hex ( rsaKey->n ),
				BN_num_bits ( rsaKey->n ) );
		printf ( "\t\t\tPublic exponent (e): %s (%d bits)\n", BN_bn2hex ( rsaKey->e ),
				BN_num_bits ( rsaKey->e ) );
	}
}
*/

/*
void
dumpPic ( PTEID_PIC * pic )
{
	int fd;
//	dumpBinary ( "PIC cbeff", pic->cbeff, sizeof(pic->cbeff) );
//	dumpBinary ( "PIC facialrechdr", pic->facialrechdr, sizeof(pic->facialrechdr) );
//	dumpBinary ( "PIC facialinfo", pic->facialinfo, sizeof(pic->facialinfo) );
//	dumpBinary ( "PIC imageinfo", pic->imageinfo, sizeof(pic->imageinfo) );
//	dumpBinary ( "PIC picture", pic->picture, sizeof(pic->picture) );
	printf ( "PIC piclength: %lu\n", pic->piclength );

	fd = open ( "pic.cbeff", O_WRONLY | O_CREAT, 0777 );
	write ( fd, pic->cbeff, sizeof(pic->cbeff) );
	close ( fd );

	fd = open ( "pic.jp2", O_WRONLY | O_CREAT, 0777 );
	write ( fd, pic->picture, pic->piclength );
	close ( fd );
}
*/



/*
void
dumpBinary ( char * msg, unsigned char * data, unsigned int len )
{
	int i;

	printf ( "%s\n\t", msg );
	for (i = 0; i < len; i++) {
		printf ( "%2.2x ", data[i] );
		if (i && i % 16 == 0) printf ( "\n\t" );
	}
	if (i % 16 != 1) printf ( "\n" );
}
*/


void
dumpPTEID ()
{
	long ret;
	PTEID_ID id;
	PTEID_Certifs certs;
	PTEID_ADDR address;

	PTEID_PIC pic;

	// PTEID_GetID
	VERBOSE("*****PTEID_GetID");
	ret = PTEID_GetID ( &id );
	fprintf ( stdout, "PTEID_GetID Result: %li\n",ret);
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_GetID", ret );
	}

	dumpId ( &id );

	// PTEID_GetCertificates
	VERBOSE("*****PTEID_GetCertificates");
	ret = PTEID_GetCertificates ( &certs );
	fprintf ( stdout, "PTEID_GetCertificates Result: %li\n",ret);
	dumpCertificates ( &certs );

	// PTEID_GetPic
	VERBOSE("*****PTEID_GetPic");
	ret = PTEID_GetPic ( &pic );
	fprintf ( stdout, "PTEID_GetPic Result: %li\n",ret);
	dumpPic ( &pic );

	// PTEID_GetAddr
	VERBOSE("*****PTEID_GetAddr");
	ret = PTEID_GetAddr ( &address );
	fprintf ( stdout, "PTEID_PTEID_GetAddr Result: %li\n",ret);
//	dumpAddress ( &address );
}


/*
void
dumpAddress ( PTEID_ADDR * address )
{
	printf ( "Version: %hd\n", address->version );
	printf ( "addrType: %s\n", address->addrType );
	printf ( "country: %s\n", address->country );
	printf ( "district: %s\n", address->district );
	printf ( "districtDesc: %s\n", address->districtDesc );
	printf ( "municipality: %s\n", address->municipality );
	printf ( "municipalityDesc: %s\n", address->municipalityDesc );
	printf ( "freguesia: %s\n", address->freguesia );
	printf ( "freguesiaDesc: %s\n", address->freguesiaDesc );
	printf ( "streettypeAbbr: %s\n", address->streettypeAbbr );
	printf ( "streettype: %s\n", address->streettype );
	printf ( "street: %s\n", address->street );
	printf ( "buildingAbbr: %s\n", address->buildingAbbr );
	printf ( "building: %s\n", address->building );
	printf ( "door: %s\n", address->door );
	printf ( "floor: %s\n", address->floor );
	printf ( "side: %s\n", address->side );
	printf ( "place: %s\n", address->place );
	printf ( "locality: %s\n", address->locality );
	printf ( "cp4: %s\n", address->cp4 );
	printf ( "cp3: %s\n", address->cp3 );
	printf ( "postal: %s\n", address->postal );
	printf ( "numMor: %s\n", address->numMor );
	printf ( "countryDescF: %s\n", address->countryDescF );
	printf ( "addressF: %s\n", address->addressF );
	printf ( "cityF: %s\n", address->cityF );
	printf ( "regioF: %s\n", address->regioF );
	printf ( "localityF: %s\n", address->localityF );
	printf ( "postalF: %s\n", address->postalF );
	printf ( "numMorF: %s\n", address->numMorF );
}
*/

/*
void
dumpPins ( PTEID_Pins * pins ){

	int i;
	int f;
	PTEID_Pin *pin;
	for (i = 0; i < pins->pinsLength; i++) {
		pin= &pins->pins[i];
		printf ( "pinType: %li\n", pin->pinType );
		printf ( "id: %u\n", pin->id );
		printf ( "usageCode: %u\n", pin->usageCode );
		printf ( "triesLeft: %u\n", pin->triesLeft );
		printf ( "flags: %u\n", pin->flags );
		printf ( "label: %s\n", pin->label );
		printf ( "shortUsage: %s\n", pin->shortUsage );
		printf ( "longUsage: %s\n", pin->longUsage );
	}
}
*/


/*
void
verifyPinsNoAlert(){

	unsigned char PinId;
	long triesLeft;
	int error;
	char* Pin;


	// PTEID_VerifyPIN
	// Signature PIN
	PinId= 130;
	Pin=NULL;

	VERBOSE("*****PTEID_VerifyPIN");
	VERBOSE("*****PTEID_VerifyPIN - PIN ID 130 - Pin da Assinatura");
	error = PTEID_VerifyPIN ( 130 , Pin , &triesLeft );
	fprintf ( stdout, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);
	fprintf ( stdout, "PTEID_VerifyPIN Result: %d\n",error);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_VerifyPIN error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}

	// PTEID_VerifyPIN
	// Signature PIN

	VERBOSE("*****PTEID_VerifyPIN_No_Alert");
	VERBOSE("*****PTEID_VerifyPIN_No_Alert - PIN ID 130 - Pin da Assinatura");
	error = PTEID_VerifyPIN_No_Alert ( 130 , Pin , &triesLeft );
	fprintf ( stdout, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);
	fprintf ( stdout, "PTEID_VerifyPIN Result: %d\n",error);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_VerifyPIN error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}
}
*/

/*
void
changePins(){
	unsigned char PinId;
	long triesLeft;
	int error;
	char* Pin;

	Pin="1234";

	VERBOSE("*****PTEID_ChangePIN");
	VERBOSE("*****PTEID_ChangePIN - PIN ID 1 - Pin da Assinatura");
	error = PTEID_ChangePIN( 130 , NULL , Pin , &triesLeft );
	fprintf ( stdout, "PTEID_ChangePIN triesLeft: %u\n",triesLeft);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_ChangePIN error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}
}
*/


/*
void
verifyPins(){
	unsigned char PinId;
	long triesLeft;
	int error;
	char* Pin;

	// PTEID_VerifyPIN
	// Authentication PIN
	PinId= 129;
	Pin ="1234";

	/*
	VERBOSE("*****PTEID_VerifyPIN");
	VERBOSE("*****PTEID_VerifyPIN - PIN ID 1 - Pin da Autenticação");
	error = PTEID_VerifyPIN ( 1 , Pin , &triesLeft );
	fprintf ( stdout, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);
	fprintf ( stdout, "PTEID_VerifyPIN Result: %d\n",error);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_VerifyPIN error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}
	*/
/*
	// PTEID_VerifyPIN
	// Signature PIN
	PinId= 130;
	Pin ="1234";

	VERBOSE("*****PTEID_VerifyPIN");
	VERBOSE("*****PTEID_VerifyPIN - PIN ID 130 - Pin da Assinatura");
	error = PTEID_VerifyPIN ( 130 , Pin , &triesLeft );
	fprintf ( stdout, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);
	fprintf ( stdout, "PTEID_VerifyPIN Result: %d\n",error);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_VerifyPIN error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}

	// PTEID_VerifyPIN
	// Address PIN
	PinId= 131;
	Pin ="1234";

	VERBOSE("*****PTEID_VerifyPIN");
	VERBOSE("*****PTEID_VerifyPIN - PIN ID 131 - Pin da Morada");
	error = PTEID_VerifyPIN ( 131 , NULL , &triesLeft );
	fprintf ( stdout, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);
	fprintf ( stdout, "PTEID_VerifyPIN Result: %d\n",error);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_VerifyPIN error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}
}
*/



int main(int argc, char ** argv ){
	int opt;
	int optind;
	int error;
	tCardType ctype;
	PTEID_Pins pins;

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
	PTEID_Init ( 0 );

	// PTEID_SetSODChecking
	VERBOSE2("PTEID_SetSODChecking", SODchecking ? "true" : "false" );
	error = PTEID_SetSODChecking ( SODchecking );
	fprintf ( stdout, "PTEID_SetSODChecking Result: %d\n",error);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_SetSODChecking error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}

	dumpPTEID();

	/*


	VERBOSE("*****PTEID_GetPINs");
	error = PTEID_GetPINs ( &pins );
	fprintf ( stdout, "PTEID_GetPINs Result: %d\n",error);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_GetPINs error: %s\n",
				PTEID_errorString ( error ) );
		exit ( 1 );
	}

	dumpPins( &pins );

	verifyPins();
	//verifyPinsNoAlert();

	//changePins();





	// PTEID_Exit
	VERBOSE("*****PTEID_Exit");
	error = PTEID_Exit(0);
	fprintf ( stdout, "PTEID_Exit Result: %d\n",error);




*/



	/*	long error;
	unsigned char modulus[128];
 	unsigned char exponent[3];
 	PTEID_RSAPublicKey pk = {modulus, sizeof(modulus), exponent, sizeof(exponent)};
 	FILE *out_file_exponent;
 	FILE *out_file_modulus;


	error = PTEID_Init(0);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_Init error\n");
	    	exit(1);
	}

	error = PTEID_SetSODChecking ( SODchecking );
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_SetSODChecking error: \n");
	       	exit (1);
	}
	printf("ahahah\n");
	error =  PTEID_GetCardAuthenticationKey(&pk);
	if (error != PTEID_OK) {
		fprintf ( stderr, "PTEID_GetCardAuthenticationKey error: \n");
	       	exit (1);
	}

	out_file_exponent = fopen("exponent.out", "w");
	out_file_modulus = fopen("modulus.out", "w");

	fwrite ( pk.exponent, sizeof(exponent), sizeof(unsigned char), out_file_exponent );
	fwrite ( pk.modulus, sizeof(modulus), sizeof(unsigned char), out_file_modulus );
	fclose(out_file_exponent);
	fclose(out_file_modulus);

	PTEID_Exit(0);
	 */
}
