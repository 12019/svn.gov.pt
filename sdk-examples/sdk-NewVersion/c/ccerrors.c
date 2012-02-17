/*
* Utility functions for presenting CC API errors
* Author: Andr Zquete (http://www.ieeta.pt/~avz)
* Date: May 2009
*/

#include "ccerrors.h"

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
