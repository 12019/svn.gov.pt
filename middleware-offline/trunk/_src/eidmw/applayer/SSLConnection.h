#ifndef SSLCONNECTION_H_
#define SSLCONNECTION_H_

#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <curl/curl.h>

#include "APLCard.h"
#include "APLReader.h"
#include "EMV-Cap-Helper.h"
#include "Export.h"

namespace eIDMW
{

// This callback will get passed to OpenSSL and it can't be a member function of SSLConnection because
// it will be called by C code which is not expecting the additional "this" pointer 
// as first argument

int rsa_sign(int type, const unsigned char *m, unsigned int m_len,
	                unsigned char *sigret, unsigned int *siglen, const RSA * rsa);
class SSLConnection
{
	public:

		EIDMW_APL_API SSLConnection()
		{
		InitConnection();
		};
		EIDMW_APL_API ~SSLConnection() 
		{
		CloseConnection();
		};
		
		//The following functions implement the communication protocol with the OTP server
		char * do_OTP_1stpost();
		char * do_OTP_2ndpost(char * cookie, OTPParams *params);
		void do_OTP_3rdpost(char *cookie, const char *change_pin_response);
		char * do_OTP_4thpost(char *cookie, OTPParams *params);
		void do_OTP_5thpost(char *cookie, const char *reset_scriptcounter_response);

	private:
		void ReadUserCert();
		//Generic POST routine that actually writes and reads from the SSL connection
		char * Post(char *cookie, char *url_path, char *body);

		unsigned int write_to_stream(SSL* bio, char* req_string);
		unsigned int read_from_stream(SSL* bio, char* buffer, unsigned int length);
		SSL *connect_encrypted(char *host_and_port);
		bool InitConnection();
		void CloseConnection();
		void loadUserCert(SSL_CTX *ctx);
		void loadCertChain(X509_STORE *store);


		RSA *current_private_key;
		//BIO *m_bio;
		SSL * m_ssl_connection;
		//Hostname of our OTP server
		char * m_otp_host;
		//APL_Card card_handle;


};

}

#endif //Include guard
