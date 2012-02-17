/*
 * commonTests.h
 *
 *  Created on: 24 de Jan de 2012
 *      Author: vsilva
 */
#ifndef COMMONTESTS_H_
#define COMMONTESTS_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <fcntl.h>

#include <openssl/x509.h>

//Biblioteca do professor Zuquete que incluem os codigos de erros devolvidos pelo MW
#include "ccerrors.h"


//Guarda os outputs dos metodos e escreve em ficheiro no final
#include "outputResult.h"



#ifdef TEST_OFICIAL_SDK
	#include <pteid/pteidlib.h>
#endif
#ifdef TEST_NEWVERSION_SDK
	#include "eidlib.h"
	#include "eidlibException.h"
	using namespace std;
	using namespace eIDMW;
#endif

#define USAGE_STR "[-vs]\n\t-v: verbose\n\t-s: perform SOD checking"
#define VERBOSE(msg) if (verbose) { printf ( "%s\n", msg );} else {}
#define VERBOSE2(msg1,msg2) if (verbose) { printf ( "%s %s\n", msg1, msg2 );} else {}

void
PTEID_error ( char * msg, long code )
{
	fprintf ( stderr, "Error code in \"%s\": %s\n", msg,
			PTEID_errorString ( code ) );
	//exit ( 1 );
}

void
dumpCertificates ( PTEID_Certifs * certs )
{
	int i;
	int fd;
	unsigned char * asn1cert;
	X509 * cert;
	RSA * rsaKey;

	char varOutput[2000];

	for (i = 0; i < certs->certificatesLength; i++) {
		sprintf (varOutput, "Certificate %d:\n\tLabel = %s\n\tBytes = %ld\n", i,
				certs->certificates[i].certifLabel,
				certs->certificates[i].certifLength );
		writeLog(varOutput);
		memset(varOutput,0,1000);

		cert = 0;
		asn1cert = certs->certificates[i].certif;
		cert = d2i_X509 ( &cert, (const unsigned char **) &asn1cert,
				certs->certificates[i].certifLength );
		assert (cert != 0);
		sprintf (varOutput, "\tX.509 fields:\n" );
		writeLog(varOutput);
		memset(varOutput,0,1000);
		sprintf (varOutput, "\t\tVersion: %ld\n", ASN1_INTEGER_get ( cert->cert_info->version ) );
		writeLog(varOutput);
		memset(varOutput,0,1000);
		sprintf (varOutput, "\t\tIssuer: %s\n", X509_NAME_oneline ( cert->cert_info->issuer, 0, 0 ) );
		writeLog(varOutput);
		memset(varOutput,0,1000);
		sprintf (varOutput, "\t\tSubject: %s\n", X509_NAME_oneline ( cert->cert_info->subject, 0, 0 ) );
		writeLog(varOutput);
		memset(varOutput,0,1000);
		sprintf (varOutput, "\t\tName: %s\n", cert->name );
		writeLog(varOutput);
		memset(varOutput,0,1000);
		rsaKey = EVP_PKEY_get1_RSA ( X509_PUBKEY_get ( cert->cert_info->key ) );
		assert (rsaKey != 0);
		sprintf (varOutput, "\t\tPublic key:\n" );
		writeLog(varOutput);
				memset(varOutput,0,1000);
		sprintf (varOutput, "\t\t\tModulus (n): %s (%d bits)\n", BN_bn2hex ( rsaKey->n ),
				BN_num_bits ( rsaKey->n ) );
		writeLog(varOutput);
				memset(varOutput,0,1000);
		sprintf (varOutput, "\t\t\tPublic exponent (e): %s (%d bits)\n", BN_bn2hex ( rsaKey->e ),
				BN_num_bits ( rsaKey->e ) );
		writeLog(varOutput);
	}
}

void
dumpRsaPK( PTEID_RSAPublicKey * rsaPK  ){

	dumpBinary ( "RSA Public Key - Exponent", rsaPK->exponent, rsaPK->exponentLength  );
	dumpBinary ( "RSA Public Key - Modulus", rsaPK->modulus, rsaPK->modulusLength  );

}



void
#ifdef TEST_OFICIAL_SDK
dumpPins ( PTEID_Pins * pins ){
	PTEID_Pin *pin;
#else
dumpPins ( PTEIDPins * pins ){
	PTEIDPin *pin;
#endif
	int i;
	int f;

	char varOutput[2000];
	for (i = 0; i < pins->pinsLength; i++) {
		pin= &pins->pins[i];
		sprintf (varOutput,  "pinType: %li\n", pin->pinType ); writeLog(varOutput); memset(varOutput,0,1000);
		sprintf (varOutput,  "id: %u\n", pin->id );writeLog(varOutput); memset(varOutput,0,1000);
		sprintf (varOutput,  "usageCode: %u\n", pin->usageCode );writeLog(varOutput); memset(varOutput,0,1000);
		sprintf (varOutput,  "triesLeft: %u\n", pin->triesLeft );writeLog(varOutput); memset(varOutput,0,1000);
		sprintf (varOutput,  "flags: %u\n", pin->flags );writeLog(varOutput); memset(varOutput,0,1000);
		sprintf (varOutput,  "label: %s\n", pin->label );writeLog(varOutput); memset(varOutput,0,1000);
		sprintf (varOutput,  "shortUsage: %s\n", pin->shortUsage );writeLog(varOutput); memset(varOutput,0,1000);
		sprintf (varOutput,  "longUsage: %s\n", pin->longUsage );writeLog(varOutput); memset(varOutput,0,1000);
	}
}




void
dumpAddress ( PTEID_ADDR * address )
{
	char varOutput[1000];
	sprintf (varOutput, "Version: %hd\n", address->version );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "addrType: %s\n", address->addrType );
	writeLog(varOutput);memset(varOutput,0,1000);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "country: %s\n", address->country );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "district: %s\n", address->district );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "districtDesc: %s\n", address->districtDesc );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "municipality: %s\n", address->municipality );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "municipalityDesc: %s\n", address->municipalityDesc );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "freguesia: %s\n", address->freguesia );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "freguesiaDesc: %s\n", address->freguesiaDesc );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "streettypeAbbr: %s\n", address->streettypeAbbr );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "streettype: %s\n", address->streettype );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "street: %s\n", address->street );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "buildingAbbr: %s\n", address->buildingAbbr );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "building: %s\n", address->building );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "door: %s\n", address->door );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "floor: %s\n", address->floor );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "side: %s\n", address->side );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "place: %s\n", address->place );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "locality: %s\n", address->locality );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "cp4: %s\n", address->cp4 );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "cp3: %s\n", address->cp3 );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "postal: %s\n", address->postal );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "numMor: %s\n", address->numMor );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "countryDescF: %s\n", address->countryDescF );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "addressF: %s\n", address->addressF );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "cityF: %s\n", address->cityF );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "regioF: %s\n", address->regioF );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "localityF: %s\n", address->localityF );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "postalF: %s\n", address->postalF );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput,  "numMorF: %s\n", address->numMorF );
}




void
test_PTEID_Init()
{
	long ret;
	writeTestedMethod("PTEID_Init");
	ret = PTEID_Init ( 0 );
	writeReturnValues("PTEID_Init", ret);
}

void
test_PTEID_Exit()
{
	long ret;
	writeTestedMethod("PTEID_Exit");
	ret = PTEID_Exit ( 0 );
	writeReturnValues("PTEID_Exit", ret);
}


void
test_PTEID_GetCardType()
{
	// Esta declaraçao devera ser apenas:
	//tCardType ctype;
#ifdef TEST_OFICIAL_SDK
	tCardType ctype;
#else
	tCompCardType ctype;
#endif
	int verbose=1;
	writeTestedMethod("PTEID_GetCardType");
	ctype = PTEID_GetCardType ();
#ifdef TEST_OFICIAL_SDK
	if (ctype == CARD_TYPE_ERR) {
#else
	if (ctype == COMP_CARD_TYPE_ERR) {
#endif
			fprintf ( stderr, "PTEID_GetCardType error: %s\n",PTEID_errorString ( ctype ) );
			exit ( 1 );
	}
	else {
#ifdef TEST_OFICIAL_SDK
		if (ctype == CARD_TYPE_ERR) {
#else
		if (ctype == COMP_CARD_TYPE_ERR) {
#endif
			VERBOSE ( "IAS 0.7 card" );
		}
		else {
			VERBOSE ( "IAS 1.01 card" );
		}
	}
}

void
dumpToken ( PTEID_TokenInfo * token ){
	char varOutput[256];

	sprintf (varOutput, "Label: %s\n", token->label);
	writeLog(varOutput); memset(varOutput,0,256);

	sprintf (varOutput, "Serial: %s\n", token->serial);
	writeLog(varOutput); memset(varOutput,0,256);

}



void
dumpId ( PTEID_ID * id )
{
	char varOutput[1000];

	sprintf (varOutput, "Version: %hd\n", id->version );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Delivery Entity: %s\n", id->deliveryEntity );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Country: %s\n", id->country );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Document type: %s\n", id->documentType );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Card number: %s\n", id->cardNumber );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Card number PAN: %s\n", id->cardNumberPAN );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Card version: %s\n", id->cardVersion );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Delivery date: %s\n", id->deliveryDate );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Locale: %s\n", id->locale );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "validity date: %s\n", id->validityDate );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Name: %s\n", id->name );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "First name: %s\n", id->firstname );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Sex: %s\n", id->sex );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Nationality: %s\n", id->nationality );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Birth date: %s\n", id->birthDate );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Height: %s\n", id->height );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "BI: %s\n", id->numBI );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Father name: %s\n", id->nameFather );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Father first name: %s\n", id->firstnameFather );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Mother name: %s\n", id->nameMother );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "Mother first name: %s\n", id->firstnameMother );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "NIF: %s\n", id->numNIF );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "SS: %s\n", id->numSS );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "SNS: %s\n", id->numSNS );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "MRZ1: %s\n", id->mrz1 );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "MRZ2: %s\n", id->mrz2 );
	writeLog(varOutput);
	memset(varOutput,0,1000);
	sprintf (varOutput, "MRZ3: %s\n", id->mrz3 );
	writeLog(varOutput);
}


void
test_PTEID_GetID(){
	int verbose=1;
	long ret;

	PTEID_ID id;

#ifdef TEST_OFICIAL_SDK
	PTEID_SetSODChecking (0);
#endif

	writeTestedMethod("PTEID_GetID");
	ret = PTEID_GetID ( &id );

	fprintf ( stdout, "PTEID_GetID Result:: %li\n",ret);
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_GetID", ret );
	}
	dumpId ( &id );
}

void
test_UnblockPIN(){

	long ret;
	unsigned char PinId;
	char* Pin;
	char varOutput[1000];
	long triesLeft;

	// Autenticacao teste
	PinId=1;
	writeTestedMethod("PTEID_UnblockPIN");
	ret = PTEID_UnblockPIN(PinId , NULL, NULL, &triesLeft );
	writeReturnValues("PTEID_UnblockPIN", ret);
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_UnblockPIN", ret );
	}
	sprintf ( varOutput, "PTEID_UnblockPIN triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);
}

void
test_UnblockPIN_Ext(){

	long ret;
	unsigned char PinId;
	char* Pin;
	char varOutput[1000];
	long triesLeft;

	// Autenticacao teste
	PinId=1;
	writeTestedMethod("PTEID_UnblockPIN_Ext");
	ret = PTEID_UnblockPIN_Ext(PinId , NULL, NULL, &triesLeft,0 );
	writeReturnValues("PTEID_UnblockPIN_Ext", ret);
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_UnblockPIN_Ext", ret );
	}
	sprintf ( varOutput, "PTEID_UnblockPIN_Ext triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);
}







void
test_PTEID_GetAddr(){
	long ret;
	PTEID_ADDR address;

	writeTestedMethod("PTEID_GetAddr");
	ret = PTEID_GetAddr ( &address );
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_GetID", ret );
	}
	dumpAddress ( &address );
}

void
test_PTEID_GetCertificates(){
	long ret;
	PTEID_Certifs certs;

	writeTestedMethod("PTEID_GetCertificates");
	ret = PTEID_GetCertificates ( &certs );
	writeReturnValues("PTEID_GetCertificates", ret);

	dumpCertificates ( &certs );
}


void
test_PTEID_GetPINs(){
	long ret;

#ifdef TEST_OFICIAL_SDK
	PTEID_Pins pins;
#else
	PTEIDPins pins;
#endif
	char logoMsg[1000];

	writeTestedMethod("PTEID_GetPINs");
	ret = PTEID_GetPINs ( &pins );
	writeReturnValues("PTEID_GetPINs", ret);

	dumpPins( &pins );
}


void
test_VerifyPINs(){
	unsigned char PinId;
	long triesLeft;
	long ret;
	char* Pin;
	char varOutput[1000];

	Pin ="1234";

	// Autenticacao
	PinId= 129;
	writeTestedMethod("PTEID_VerifyPIN (Pin de autenticação e a passar o Pin por Argumento)");
	ret = PTEID_VerifyPIN ( PinId , Pin , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);

	writeTestedMethod("PTEID_VerifyPIN (Pin de autenticação PIN a NULL)");
	ret = PTEID_VerifyPIN ( PinId , NULL , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);

	// Morada
	PinId= 131;
	writeTestedMethod("PTEID_VerifyPIN (Pin de Morada e a passar o Pin por Argumento)");
	ret = PTEID_VerifyPIN ( PinId , Pin , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);

	writeTestedMethod("PTEID_VerifyPIN (Pin de Morada PIN a NULL)");
	ret = PTEID_VerifyPIN ( PinId , NULL , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);

	// Assinatura
	PinId= 130;
	writeTestedMethod("PTEID_VerifyPIN (Pin de assinatura e a passar o Pin por Argumento)");
	ret = PTEID_VerifyPIN ( PinId , Pin , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);

	writeTestedMethod("PTEID_VerifyPIN (Pin de assinatura PIN a NULL)");
	ret = PTEID_VerifyPIN ( PinId , NULL , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);

	// Assinatura - Verify Pin No Alert
	PinId= 130;
	writeTestedMethod("PTEID_VerifyPIN_No_Alert (Pin de assinatura e a passar o Pin por Argumento)");
	ret = PTEID_VerifyPIN_No_Alert ( PinId , Pin , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN_No_Alert", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN_No_Alert triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);

	writeTestedMethod("PTEID_VerifyPIN_No_Alert (Pin de assinatura PIN a NULL)");
	ret = PTEID_VerifyPIN_No_Alert ( PinId , NULL , &triesLeft );
	writeReturnValues("PTEID_VerifyPIN_No_Alert", ret);
	sprintf ( varOutput, "PTEID_VerifyPIN_No_Alert triesLeft: %u\n",triesLeft);writeLog(varOutput);memset(varOutput,0,1000);
}



void
test_PTEID_GetTokenInfo(){

	long ret;
	PTEID_TokenInfo token;

	writeTestedMethod("PTEID_GetTokenInfo");
	ret = PTEID_GetTokenInfo ( &token );
	writeReturnValues("PTEID_GetTokenInfo", ret);

	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_GetTokenInfo", ret );
	}
	dumpToken ( &token );
}


void
test_PTEID_ReadSOD(){

	long ret;
	unsigned long size_to_read=3000;
	unsigned char sod_content[3000];


	writeTestedMethod("PTEID_ReadSOD");
	ret = PTEID_ReadSOD ( sod_content, &size_to_read );
	writeReturnValues("PTEID_ReadSOD", ret);

	char *filename="SOD";

	writeByteArray(filename,sod_content, size_to_read);


	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_ReadSOD", ret );
	}
}

void
test_PTEID_IsActivated(){
	long ret;
	long unsigned isActivaded;
	char varOutput[100];

	writeTestedMethod("PTEID_IsActivated");
	ret = PTEID_IsActivated ( &isActivaded );
	writeReturnValues("PTEID_IsActivated", ret);
	sprintf (varOutput, "Is activated: %li\n",isActivaded);
	writeLog(varOutput);
	if (ret != PTEID_OK)
		PTEID_error ( "PTEID_IsActivated", ret );
}

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

void
test_PTEID_GetPic(){
	long ret;
	PTEID_PIC pic;

	writeTestedMethod("PTEID_GetPic");
	ret = PTEID_GetPic ( &pic );
	writeReturnValues("PTEID_GetPic", ret);
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_GetPic", ret );
	}
	dumpPic ( &pic );
}

void
test_GetCardAuthenticationKey(){

	long ret;
	unsigned char modulus[128];
	unsigned char exponent[3];

	PTEID_RSAPublicKey rsaPK = {modulus, sizeof(modulus), exponent,sizeof(exponent)} ;

	writeTestedMethod("PTEID_GetCardAuthenticationKey");
	ret = PTEID_GetCardAuthenticationKey ( &rsaPK );
	//PTEID_GetCardAuthenticationKey ( &rsaPK );
	writeReturnValues("PTEID_GetCardAuthenticationKey", ret);
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_GetCardAuthenticationKey", ret );
	}
	dumpRsaPK ( &rsaPK );
}

void
test_PTEID_GetCVCRoot(){

	long ret;
	unsigned char modulus[128];
	unsigned char exponent[3];

	PTEID_RSAPublicKey rsaPK = {modulus, sizeof(modulus), exponent,sizeof(exponent)} ;

	writeTestedMethod("PTEID_GetCVCRoot");
	ret = PTEID_GetCVCRoot ( &rsaPK );
	//PTEID_GetCardAuthenticationKey ( &rsaPK );
	writeReturnValues("PTEID_GetCVCRoot", ret);
	if (ret != PTEID_OK) {
		PTEID_error ( "PTEID_GetCVCRoot", ret );
	}
	dumpRsaPK ( &rsaPK );
}

void
test_PTEID_selectADF(){

	long ret;
	//unsigned char adf[2] = {0x41, 0x00};  // AID Invalido - Apenas para testar o caso de erro
	unsigned char adf[2] = {0x4F, 0x00};

	writeTestedMethod("PTEID_SelectADF");
	ret = PTEID_SelectADF(adf,2);
	writeReturnValues("PTEID_SelectADF", ret);
	if (ret != PTEID_OK)
		PTEID_error ( "PTEID_SelectADF", ret );
}

void
test_PTEID_ReadFile(){

	long ret;

	unsigned long address_len=6;
	unsigned long out_len=16000;
	unsigned char file_content[16000]; // 16000 -> Tamanho máximo : Foto
	unsigned char file_address[6] = {0x3F, 0x00, 0x5F, 0x00, 0xEF, 0x05}; // Endereço da morada

	writeTestedMethod("PTEID_ReadFile");
	ret = PTEID_ReadFile(file_address,address_len,file_content,&out_len,131);
	writeReturnValues("PTEID_ReadFile", ret);
	if (ret != PTEID_OK)
		PTEID_error ( "PTEID_ReadFile", ret );
	//printf("filecontent: %x%x%x%x%x%x%x",file_content[0],file_content[1],file_content[2],file_content[3],file_content[4],file_content[5],file_content[6]);
	//	printByteArray(std::cout,file_content,out_len);
	//printByteArray(std::ostream &stream, unsigned char * arr, unsigned int len)

	char *file_to_write="EF05-Address";
	writeByteArray(file_to_write,file_content, out_len);

}






#endif /* COMMONTESTS_H_ */
