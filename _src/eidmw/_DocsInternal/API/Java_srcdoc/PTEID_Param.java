/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * Class that holds the different configuration setting definitions
  *********************************************************************************/
public final class PTEID_Param {

	/** directory of the basic eid software installation
	*/
  public final static PTEID_Param PTEID_PARAM_GENERAL_INSTALLDIR = new PTEID_Param("PTEID_PARAM_GENERAL_INSTALLDIR");

	/** directory of the pro eid software
	*/
  public final static PTEID_Param PTEID_PARAM_GENERAL_INSTALL_PRO_DIR = new PTEID_Param("PTEID_PARAM_GENERAL_INSTALL_PRO_DIR");

	/** directory of the sdk eid software
	*/
  public final static PTEID_Param PTEID_PARAM_GENERAL_INSTALL_SDK_DIR = new PTEID_Param("PTEID_PARAM_GENERAL_INSTALL_SDK_DIR");

	/** cache directory for card-file
	*/
  public final static PTEID_Param PTEID_PARAM_GENERAL_CACHEDIR = new PTEID_Param("PTEID_PARAM_GENERAL_CACHEDIR");

	/** user language: [fr,nl,en,de]
	*/
  public final static PTEID_Param PTEID_PARAM_GENERAL_LANGUAGE = new PTEID_Param("PTEID_PARAM_GENERAL_LANGUAGE");

	/** location of the log-file
	*/
  public final static PTEID_Param PTEID_PARAM_LOGGING_DIRNAME = new PTEID_Param("PTEID_PARAM_LOGGING_DIRNAME");

	/** prefix of the log files
	*/
  public final static PTEID_Param PTEID_PARAM_LOGGING_PREFIX = new PTEID_Param("PTEID_PARAM_LOGGING_PREFIX");

	/** Maximum number of log-files (default = 3)
	*/
  public final static PTEID_Param PTEID_PARAM_LOGGING_FILENUMBER = new PTEID_Param("PTEID_PARAM_LOGGING_FILENUMBER");

	/** maximum log file size
	*/
  public final static PTEID_Param PTEID_PARAM_LOGGING_FILESIZE = new PTEID_Param("PTEID_PARAM_LOGGING_FILESIZE");

	/** log level [critical,error,warning,info,debug]
	*/
  public final static PTEID_Param PTEID_PARAM_LOGGING_LEVEL = new PTEID_Param("PTEID_PARAM_LOGGING_LEVEL");

	/** create on log file by module [0=no (default), 1=yes]
	*/
  public final static PTEID_Param PTEID_PARAM_LOGGING_GROUP = new PTEID_Param("PTEID_PARAM_LOGGING_GROUP");

	/**
	*/
  public final static PTEID_Param PTEID_PARAM_CRL_SERVDOWNLOADNR = new PTEID_Param("PTEID_PARAM_CRL_SERVDOWNLOADNR");

	/** CRL timeout in seconds
	*/
  public final static PTEID_Param PTEID_PARAM_CRL_TIMEOUT = new PTEID_Param("PTEID_PARAM_CRL_TIMEOUT");

	/** CRL caching directory
	*/
  public final static PTEID_Param PTEID_PARAM_CRL_CACHEDIR = new PTEID_Param("PTEID_PARAM_CRL_CACHEDIR");

	/** CRL cache file
	*/
  public final static PTEID_Param PTEID_PARAM_CRL_CACHEFILE = new PTEID_Param("PTEID_PARAM_CRL_CACHEFILE");

	/** CRL lock file
	*/
  public final static PTEID_Param PTEID_PARAM_CRL_LOCKFILE = new PTEID_Param("PTEID_PARAM_CRL_LOCKFILE");

	/** allow test certificate [0=no,1=yes]
	*/
  public final static PTEID_Param PTEID_PARAM_CERTVALID_ALLOWTESTC = new PTEID_Param("PTEID_PARAM_CERTVALID_ALLOWTESTC");

	/** validate using CRL [0=no, 1=optional, 2=always]
	*/
  public final static PTEID_Param PTEID_PARAM_CERTVALID_CRL = new PTEID_Param("PTEID_PARAM_CERTVALID_CRL");

	/** validate using OCSP [0=no, 1=optional, 2=always]
	*/
  public final static PTEID_Param PTEID_PARAM_CERTVALID_OCSP = new PTEID_Param("PTEID_PARAM_CERTVALID_OCSP");

	/** certificate cache file
	*/
  public final static PTEID_Param PTEID_PARAM_CERTCACHE_CACHEFILE = new PTEID_Param("PTEID_PARAM_CERTCACHE_CACHEFILE");

	/**
	*/
  public final static PTEID_Param PTEID_PARAM_CERTCACHE_LINENUMB = new PTEID_Param("PTEID_PARAM_CERTCACHE_LINENUMB");

	/** certificate cache file validity
	*/
  public final static PTEID_Param PTEID_PARAM_CERTCACHE_VALIDITY = new PTEID_Param("PTEID_PARAM_CERTCACHE_VALIDITY");

	/** certificate cache file wait delay
	*/
  public final static PTEID_Param PTEID_PARAM_CERTCACHE_WAITDELAY = new PTEID_Param("PTEID_PARAM_CERTCACHE_WAITDELAY");

	/** proxy host address
	*/
  public final static PTEID_Param PTEID_PARAM_PROXY_HOST = new PTEID_Param("PTEID_PARAM_PROXY_HOST");

	/** proxy port nr
	*/
  public final static PTEID_Param PTEID_PARAM_PROXY_PORT = new PTEID_Param("PTEID_PARAM_PROXY_PORT");

	/** proxy PAC file
	*/
  public final static PTEID_Param PTEID_PARAM_PROXY_PACFILE = new PTEID_Param("PTEID_PARAM_PROXY_PACFILE");

	/** 0=no, 1=yes; If yes, the PIN is requested by the driver and asked only once with multiple applications
	*/
  public final static PTEID_Param PTEID_PARAM_SECURITY_SINGLESIGNON = new PTEID_Param("PTEID_PARAM_SECURITY_SINGLESIGNON");

	/** start GUI when windows starts [0=no(default), 1=yes]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_STARTWIN = new PTEID_Param("PTEID_PARAM_GUITOOL_STARTWIN");

	/** start GUI minimized [0=no(default), 1=yes]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_STARTMINI = new PTEID_Param("PTEID_PARAM_GUITOOL_STARTMINI");

	/** show picture when card inserted [0=no, 1=yes(default)]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_SHOWPIC = new PTEID_Param("PTEID_PARAM_GUITOOL_SHOWPIC");

	/** show toolbar (not used)
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_SHOWTBAR = new PTEID_Param("PTEID_PARAM_GUITOOL_SHOWTBAR");

	/** use virtual keyboard [0=no, 1=yes]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_VIRTUALKBD = new PTEID_Param("PTEID_PARAM_GUITOOL_VIRTUALKBD");

	/** automatic card reading when card inserted [0=no, 1=yes(default)]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_AUTOCARDREAD = new PTEID_Param("PTEID_PARAM_GUITOOL_AUTOCARDREAD");

	/** card reader selected [-1(not specified), 0..10]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_CARDREADNUMB = new PTEID_Param("PTEID_PARAM_GUITOOL_CARDREADNUMB");

	/** register certificates when card inserted [0=no, 1=yes(default)]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_REGCERTIF = new PTEID_Param("PTEID_PARAM_GUITOOL_REGCERTIF");

	/** remove certificates when card removed [0=no, 1=yes(default)]
	*/
  public final static PTEID_Param PTEID_PARAM_GUITOOL_REMOVECERTIF = new PTEID_Param("PTEID_PARAM_GUITOOL_REMOVECERTIF");

	/**
	*/
  public final static PTEID_Param PTEID_PARAM_XSIGN_TSAURL = new PTEID_Param("PTEID_PARAM_XSIGN_TSAURL");

	/**
	*/
  public final static PTEID_Param PTEID_PARAM_XSIGN_ONLINE = new PTEID_Param("PTEID_PARAM_XSIGN_ONLINE");

	/**
	*/
  public final static PTEID_Param PTEID_PARAM_XSIGN_WORKINGDIR = new PTEID_Param("PTEID_PARAM_XSIGN_WORKINGDIR");

	/**
	*/
  public final static PTEID_Param PTEID_PARAM_XSIGN_TIMEOUT = new PTEID_Param("PTEID_PARAM_XSIGN_TIMEOUT");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static PTEID_Param swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + PTEID_Param.class + " with value " + swigValue);
  }

  private PTEID_Param(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private PTEID_Param(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private PTEID_Param(String swigName, PTEID_Param swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static PTEID_Param[] swigValues = { PTEID_PARAM_GENERAL_INSTALLDIR, PTEID_PARAM_GENERAL_INSTALL_PRO_DIR, PTEID_PARAM_GENERAL_INSTALL_SDK_DIR, PTEID_PARAM_GENERAL_CACHEDIR, PTEID_PARAM_GENERAL_LANGUAGE, PTEID_PARAM_LOGGING_DIRNAME, PTEID_PARAM_LOGGING_PREFIX, PTEID_PARAM_LOGGING_FILENUMBER, PTEID_PARAM_LOGGING_FILESIZE, PTEID_PARAM_LOGGING_LEVEL, PTEID_PARAM_LOGGING_GROUP, PTEID_PARAM_CRL_SERVDOWNLOADNR, PTEID_PARAM_CRL_TIMEOUT, PTEID_PARAM_CRL_CACHEDIR, PTEID_PARAM_CRL_CACHEFILE, PTEID_PARAM_CRL_LOCKFILE, PTEID_PARAM_CERTVALID_ALLOWTESTC, PTEID_PARAM_CERTVALID_CRL, PTEID_PARAM_CERTVALID_OCSP, PTEID_PARAM_CERTCACHE_CACHEFILE, PTEID_PARAM_CERTCACHE_LINENUMB, PTEID_PARAM_CERTCACHE_VALIDITY, PTEID_PARAM_CERTCACHE_WAITDELAY, PTEID_PARAM_PROXY_HOST, PTEID_PARAM_PROXY_PORT, PTEID_PARAM_PROXY_PACFILE, PTEID_PARAM_SECURITY_SINGLESIGNON, PTEID_PARAM_GUITOOL_STARTWIN, PTEID_PARAM_GUITOOL_STARTMINI, PTEID_PARAM_GUITOOL_SHOWPIC, PTEID_PARAM_GUITOOL_SHOWTBAR, PTEID_PARAM_GUITOOL_VIRTUALKBD, PTEID_PARAM_GUITOOL_AUTOCARDREAD, PTEID_PARAM_GUITOOL_CARDREADNUMB, PTEID_PARAM_GUITOOL_REGCERTIF, PTEID_PARAM_GUITOOL_REMOVECERTIF, PTEID_PARAM_XSIGN_TSAURL, PTEID_PARAM_XSIGN_ONLINE, PTEID_PARAM_XSIGN_WORKINGDIR, PTEID_PARAM_XSIGN_TIMEOUT };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

