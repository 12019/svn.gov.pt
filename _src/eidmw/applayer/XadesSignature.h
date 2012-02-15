#ifndef XADESSIG_H
#define XADESSIG_H
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XercesDefs.hpp>
#include <xsec/dsig/DSIGSignature.hpp>

#include <string>
#include <openssl/evp.h>
#include <openssl/x509.h>

#include "Export.h" 
#include "APLCard.h"
#include "MiscUtil.h"

#define ASN1_LEN 43
#define SHA1_OFFSET 20

#define XERCES_NS XERCES_CPP_NAMESPACE_QUALIFIER

#ifndef WIN32
#define _strdup strdup
#endif


XERCES_CPP_NAMESPACE_USE

namespace eIDMW
{

	class CByteArray;
	static unsigned char timestamp_asn1_request[ASN1_LEN] =
	{
	0x30, 0x29, 0x02, 0x01, 0x01, 0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a,
	0x05, 0x00, 0x04, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xff
	};

	class XadesSignature
	{
		public:

		XadesSignature(APL_Card *card): mp_card(card), mp_cert(NULL)
		{

		};
		
		~XadesSignature()
		{
		   X509_free(mp_cert);
		};

		CByteArray &SignXades(CByteArray ba, const char *URL);
		CByteArray &SignXades(const char ** paths, unsigned int n_paths, bool do_timestamp);

		static bool checkExternalRefs(DSIGReferenceList *refs, tHashedFile **hashes);
		static bool ValidateXades(CByteArray signature, tHashedFile **hashes, char *errors, unsigned long *error_length);
		

		private:
		
		CByteArray HashFile(const char *file_path);
		DOMNode * addSignatureProperties(DSIGSignature *sig);
		CByteArray *WriteToByteArray(XERCES_NS DOMDocument *doc); 
		//Utility methods for signature
		void loadCert(CByteArray &ba, EVP_PKEY *pub_key);
		
		int appendOID(XMLByte *toFill);

		void addTimestampNode(XERCES_NS DOMNode *node, unsigned char *timestamp);
		XMLCh* createURI(const char *path);


		//Utility methods for timestamping
		
		//Curl write_function callback: it writes the data to the static array mp_timestamp_data
		static size_t curl_write_data(char *ptr, size_t size, size_t nmemb, void * stream); 

		void timestamp_data(const unsigned char *input, unsigned int data_len);
		void generate_asn1_request_struct(unsigned char *sha_1);

		static void initXerces();

		
		X509 * mp_cert;
		APL_Card *mp_card;
		static CByteArray mp_timestamp_data;


	};
}

#endif 

