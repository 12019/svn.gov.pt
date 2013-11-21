#ifndef __PTEID_VERSION_H__
#define __PTEID_VERSION_H__

/**
 * Versions for the Windows binaries
 * This versions are the real version of the middleware
 */

#pragma once
#include "../svn_revision.h"

// To specified in the .rc files

#define PTEID_COMPANY_NAME    	"Portuguese Government"
#define PTEID_COPYRIGHT    	"Copyright (C) 2010-2012"
#define PTEID_PRODUCT_NAME    	"Portugal eID MiddleWare"


#define PTEID_PRODUCT_VERSION    "2.2.0"
#define BASE_VERSION_STRING    "2, 2, 0, "
#define BASE_VERSION1          2
#define BASE_VERSION2          2
#define BASE_VERSION3          0


// Common Lib
#define WIN_CL_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_CL_VERSION1          BASE_VERSION1          
#define WIN_CL_VERSION2          BASE_VERSION2          
#define WIN_CL_VERSION3          BASE_VERSION3          
#define WIN_CL_VERSION4          SVN_REVISION

// Card Abstraction
#define WIN_CAL_VERSION_STRING   BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_CAL_VERSION1         BASE_VERSION1          
#define WIN_CAL_VERSION2         BASE_VERSION2          
#define WIN_CAL_VERSION3         BASE_VERSION3          
#define WIN_CAL_VERSION4         SVN_REVISION

// Dialogs
#define WIN_DLG_VERSION_STRING   BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_DLG_VERSION1         BASE_VERSION1          
#define WIN_DLG_VERSION2         BASE_VERSION2          
#define WIN_DLG_VERSION3         BASE_VERSION3          
#define WIN_DLG_VERSION4         SVN_REVISION

// CSP
#define WIN_CSP_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_CSP_VERSION1          BASE_VERSION1          
#define WIN_CSP_VERSION2          BASE_VERSION2          
#define WIN_CSP_VERSION3          BASE_VERSION3          
#define WIN_CSP_VERSION4          SVN_REVISION

// CSP
#define WIN_CSPLIB_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_CSPLIB_VERSION1          BASE_VERSION1          
#define WIN_CSPLIB_VERSION2          BASE_VERSION2          
#define WIN_CSPLIB_VERSION3          BASE_VERSION3          
#define WIN_CSPLIB_VERSION4          SVN_REVISION

// Application layer
#define WIN_APL_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_APL_VERSION1          BASE_VERSION1          
#define WIN_APL_VERSION2          BASE_VERSION2          
#define WIN_APL_VERSION3          BASE_VERSION3          
#define WIN_APL_VERSION4          SVN_REVISION

// SDK
#define WIN_SDK_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_SDK_VERSION1          BASE_VERSION1          
#define WIN_SDK_VERSION2          BASE_VERSION2          
#define WIN_SDK_VERSION3          BASE_VERSION3          
#define WIN_SDK_VERSION4          SVN_REVISION

// SDK_C
#define WIN_SDK_C_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_SDK_C_VERSION1          BASE_VERSION1          
#define WIN_SDK_C_VERSION2          BASE_VERSION2          
#define WIN_SDK_C_VERSION3          BASE_VERSION3          
#define WIN_SDK_C_VERSION4          SVN_REVISION

// SDK_CS
#define WIN_SDK_CS_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_SDK_CS_VERSION1          BASE_VERSION1          
#define WIN_SDK_CS_VERSION2          BASE_VERSION2          
#define WIN_SDK_CS_VERSION3          BASE_VERSION3          
#define WIN_SDK_CS_VERSION4          SVN_REVISION

// SDK_JAVA
#define WIN_SDK_JAVA_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_SDK_JAVA_VERSION1          BASE_VERSION1          
#define WIN_SDK_JAVA_VERSION2          BASE_VERSION2          
#define WIN_SDK_JAVA_VERSION3          BASE_VERSION3          
#define WIN_SDK_JAVA_VERSION4          SVN_REVISION

// GUI
#define WIN_GUI_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_GUI_VERSION1          BASE_VERSION1          
#define WIN_GUI_VERSION2          BASE_VERSION2          
#define WIN_GUI_VERSION3          BASE_VERSION3          
#define WIN_GUI_VERSION4          SVN_REVISION

// cardplugin PTEID
#define WIN_CPPTEID_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_CPPTEID_VERSION1          BASE_VERSION1          
#define WIN_CPPTEID_VERSION2          BASE_VERSION2          
#define WIN_CPPTEID_VERSION3          BASE_VERSION3          
#define WIN_CPPTEID_VERSION4          SVN_REVISION

// cardplugin SIS
#define WIN_CPSIS_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_CPSIS_VERSION1          BASE_VERSION1          
#define WIN_CPSIS_VERSION2          BASE_VERSION2          
#define WIN_CPSIS_VERSION3          BASE_VERSION3          
#define WIN_CPSIS_VERSION4          SVN_REVISION

// cardplugin SIS for ACR38U
#define WIN_CPSIS_ACR38U_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_CPSIS_ACR38U_VERSION1          BASE_VERSION1          
#define WIN_CPSIS_ACR38U_VERSION2          BASE_VERSION2          
#define WIN_CPSIS_ACR38U_VERSION3          BASE_VERSION3          
#define WIN_CPSIS_ACR38U_VERSION4          SVN_REVISION

// PKCS11
#define WIN_PKCS11_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_PKCS11_VERSION1          BASE_VERSION1          
#define WIN_PKCS11_VERSION2          BASE_VERSION2          
#define WIN_PKCS11_VERSION3          BASE_VERSION3          
#define WIN_PKCS11_VERSION4          SVN_REVISION

// XSign
#define WIN_XSIGN_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_XSIGN_VERSION1          BASE_VERSION1
#define WIN_XSIGN_VERSION2          BASE_VERSION2
#define WIN_XSIGN_VERSION3          BASE_VERSION3
#define WIN_XSIGN_VERSION4          SVN_REVISION

// QuickInstaller
#define WIN_QI_VERSION_STRING    BASE_VERSION_STRING SVN_REVISION_STR
#define WIN_QI_VERSION1          BASE_VERSION1          
#define WIN_QI_VERSION2          BASE_VERSION2          
#define WIN_QI_VERSION3          BASE_VERSION3          
#define WIN_QI_VERSION4          SVN_REVISION

#endif //__PTEID_VERSION_H__
