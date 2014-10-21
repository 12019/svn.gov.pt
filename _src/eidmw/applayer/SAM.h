#ifndef SAMMY_H_
#define SAMMY_H_

#include <vector>


namespace eIDMW
{

struct DHParams
{

char *dh_p;
char *dh_q;
char *dh_g;
char *cvc_ca_public_key;
char *card_auth_public_key;
char *certificateChain;
unsigned int version;

};

struct StartWriteResponse
{
	std::vector<char *> apdu_write_address;
	std::vector<char *> apdu_write_sod;
};

struct DHParamsResponse
{
	char *kifd;
	char *cv_ifd_aut;

};

struct SignedChallengeResponse
{
	char *signed_challenge;
	char *internal_auth;
	char *set_se_command;
};

class SAM
{

public:
	SAM(APL_Card *card);

	bool getDHParams(DHParams *otp_struct);
	bool verifyCVCCertificate(const char *cvc_certificate_hex);
	bool verifySignedChallenge(char *signed_challenge);
	bool sendKIFD(char *kifd);
	char *getKICC();
	bool verifyCert_CV_IFD(char * cv_cert);
	char *generateChallenge();
	char *getSerialNumberIAS101();
	char *sendPrebuiltAPDU(char *apdu_string);
	std::vector<char *> sendSequenceOfPrebuiltAPDUs(std::vector<char *> &apdu_array);

private:
	char * _getDH_Param(char specific_byte, unsigned long offset);
	char *_getCVCPublicKey();
	char *_getCardAuthPublicKey();
	char * _getSODCert();
    APL_Card *m_card;
};


}

#endif