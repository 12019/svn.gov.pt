/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace be.portugal.eid {

using System;
using System.Runtime.InteropServices;

public class pteidlib_dotNet {
  /// <summary>Function for Logging.</summary>
  public static void PTEID_LOG(PTEID_LogLevel level, string module_name, string format) {
    pteidlib_dotNetPINVOKE.PTEID_LOG((int)level, module_name, format);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public static readonly int EIDMW_OK = pteidlib_dotNetPINVOKE.EIDMW_OK_get();
  public static readonly int EIDMW_ERR_PARAM_BAD = pteidlib_dotNetPINVOKE.EIDMW_ERR_PARAM_BAD_get();
  public static readonly int EIDMW_ERR_PARAM_RANGE = pteidlib_dotNetPINVOKE.EIDMW_ERR_PARAM_RANGE_get();
  public static readonly int EIDMW_ERR_BAD_PATH = pteidlib_dotNetPINVOKE.EIDMW_ERR_BAD_PATH_get();
  public static readonly int EIDMW_ERR_ALGO_BAD = pteidlib_dotNetPINVOKE.EIDMW_ERR_ALGO_BAD_get();
  public static readonly int EIDMW_ERR_PIN_OPERATION = pteidlib_dotNetPINVOKE.EIDMW_ERR_PIN_OPERATION_get();
  public static readonly int EIDMW_ERR_PIN_FORMAT = pteidlib_dotNetPINVOKE.EIDMW_ERR_PIN_FORMAT_get();
  public static readonly int EIDMW_ERR_BAD_USAGE = pteidlib_dotNetPINVOKE.EIDMW_ERR_BAD_USAGE_get();
  public static readonly int EIDMW_ERR_CARD = pteidlib_dotNetPINVOKE.EIDMW_ERR_CARD_get();
  public static readonly int EIDMW_ERR_NOT_AUTHENTICATED = pteidlib_dotNetPINVOKE.EIDMW_ERR_NOT_AUTHENTICATED_get();
  public static readonly int EIDMW_ERR_NOT_SUPPORTED = pteidlib_dotNetPINVOKE.EIDMW_ERR_NOT_SUPPORTED_get();
  public static readonly int EIDMW_ERR_PIN_BAD = pteidlib_dotNetPINVOKE.EIDMW_ERR_PIN_BAD_get();
  public static readonly int EIDMW_ERR_PIN_BLOCKED = pteidlib_dotNetPINVOKE.EIDMW_ERR_PIN_BLOCKED_get();
  public static readonly int EIDMW_ERR_NO_CARD = pteidlib_dotNetPINVOKE.EIDMW_ERR_NO_CARD_get();
  public static readonly int EIDMW_ERR_BAD_P1P2 = pteidlib_dotNetPINVOKE.EIDMW_ERR_BAD_P1P2_get();
  public static readonly int EIDMW_ERR_CMD_NOT_ALLOWED = pteidlib_dotNetPINVOKE.EIDMW_ERR_CMD_NOT_ALLOWED_get();
  public static readonly int EIDMW_ERR_FILE_NOT_FOUND = pteidlib_dotNetPINVOKE.EIDMW_ERR_FILE_NOT_FOUND_get();
  public static readonly int EIDMW_ERR_APPLET_VERSION_NOT_FOUND = pteidlib_dotNetPINVOKE.EIDMW_ERR_APPLET_VERSION_NOT_FOUND_get();
  public static readonly int EIDMW_ERR_NOT_ACTIVATED = pteidlib_dotNetPINVOKE.EIDMW_ERR_NOT_ACTIVATED_get();
  public static readonly int EIDMW_ERR_CARD_COMM = pteidlib_dotNetPINVOKE.EIDMW_ERR_CARD_COMM_get();
  public static readonly int EIDMW_ERR_NO_READER = pteidlib_dotNetPINVOKE.EIDMW_ERR_NO_READER_get();
  public static readonly int EIDMW_ERR_PINPAD = pteidlib_dotNetPINVOKE.EIDMW_ERR_PINPAD_get();
  public static readonly int EIDMW_ERR_CANT_CONNECT = pteidlib_dotNetPINVOKE.EIDMW_ERR_CANT_CONNECT_get();
  public static readonly int EIDMW_ERR_CARD_RESET = pteidlib_dotNetPINVOKE.EIDMW_ERR_CARD_RESET_get();
  public static readonly int EIDMW_ERR_CARD_SHARING = pteidlib_dotNetPINVOKE.EIDMW_ERR_CARD_SHARING_get();
  public static readonly int EIDMW_ERR_NOT_TRANSACTED = pteidlib_dotNetPINVOKE.EIDMW_ERR_NOT_TRANSACTED_get();
  public static readonly int EIDMW_ERR_LIMIT = pteidlib_dotNetPINVOKE.EIDMW_ERR_LIMIT_get();
  public static readonly int EIDMW_ERR_CHECK = pteidlib_dotNetPINVOKE.EIDMW_ERR_CHECK_get();
  public static readonly int EIDMW_ERR_PCSC_LIB = pteidlib_dotNetPINVOKE.EIDMW_ERR_PCSC_LIB_get();
  public static readonly int EIDMW_ERR_ZLIB_RESOLVE = pteidlib_dotNetPINVOKE.EIDMW_ERR_ZLIB_RESOLVE_get();
  public static readonly int EIDMW_ERR_UNKNOWN = pteidlib_dotNetPINVOKE.EIDMW_ERR_UNKNOWN_get();
  public static readonly int EIDMW_PINPAD_ERR = pteidlib_dotNetPINVOKE.EIDMW_PINPAD_ERR_get();
  public static readonly int EIDMW_CANT_LOAD_LIB = pteidlib_dotNetPINVOKE.EIDMW_CANT_LOAD_LIB_get();
  public static readonly int EIDMW_ERR_MEMORY = pteidlib_dotNetPINVOKE.EIDMW_ERR_MEMORY_get();
  public static readonly int EIDMW_ERR_DELETE_CACHE = pteidlib_dotNetPINVOKE.EIDMW_ERR_DELETE_CACHE_get();
  public static readonly int EIDMW_CONF = pteidlib_dotNetPINVOKE.EIDMW_CONF_get();
  public static readonly int EIDMW_CACHE_TAMPERED = pteidlib_dotNetPINVOKE.EIDMW_CACHE_TAMPERED_get();
  public static readonly int EIDMW_ERR_SOCKET_CREATE = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_CREATE_get();
  public static readonly int EIDMW_ERR_SOCKET_SEND = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_SEND_get();
  public static readonly int EIDMW_ERR_SOCKET_RECV = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_RECV_get();
  public static readonly int EIDMW_ERR_SOCKET_GETHOST = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_GETHOST_get();
  public static readonly int EIDMW_ERR_SOCKET_CONNECT = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_CONNECT_get();
  public static readonly int EIDMW_ERR_SOCKET_SOCKET = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_SOCKET_get();
  public static readonly int EIDMW_ERR_SOCKET_BIND = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_BIND_get();
  public static readonly int EIDMW_ERR_SOCKET_ACCEPT = pteidlib_dotNetPINVOKE.EIDMW_ERR_SOCKET_ACCEPT_get();
  public static readonly int EIDMW_ERR_PIN_CANCEL = pteidlib_dotNetPINVOKE.EIDMW_ERR_PIN_CANCEL_get();
  public static readonly int EIDMW_ERR_TIMEOUT = pteidlib_dotNetPINVOKE.EIDMW_ERR_TIMEOUT_get();
  public static readonly int EIDMW_NEW_PINS_DIFFER = pteidlib_dotNetPINVOKE.EIDMW_NEW_PINS_DIFFER_get();
  public static readonly int EIDMW_WRONG_PIN_FORMAT = pteidlib_dotNetPINVOKE.EIDMW_WRONG_PIN_FORMAT_get();
  public static readonly int EIDMW_WRONG_ASN1_FORMAT = pteidlib_dotNetPINVOKE.EIDMW_WRONG_ASN1_FORMAT_get();
  public static readonly int EIDMW_FILE_NOT_OPENED = pteidlib_dotNetPINVOKE.EIDMW_FILE_NOT_OPENED_get();
  public static readonly int EIDMW_PERMISSION_DENIED = pteidlib_dotNetPINVOKE.EIDMW_PERMISSION_DENIED_get();
  public static readonly int EIDMW_INVALID_PATH = pteidlib_dotNetPINVOKE.EIDMW_INVALID_PATH_get();
  public static readonly int EIDMW_TOO_MANY_OPENED_FILES = pteidlib_dotNetPINVOKE.EIDMW_TOO_MANY_OPENED_FILES_get();
  public static readonly int EIDMW_DIR_NOT_OPENED = pteidlib_dotNetPINVOKE.EIDMW_DIR_NOT_OPENED_get();
  public static readonly int EIDMW_INTERRUPTION = pteidlib_dotNetPINVOKE.EIDMW_INTERRUPTION_get();
  public static readonly int EIDMW_OVERFLOW = pteidlib_dotNetPINVOKE.EIDMW_OVERFLOW_get();
  public static readonly int EIDMW_ERROR_IO = pteidlib_dotNetPINVOKE.EIDMW_ERROR_IO_get();
  public static readonly int EIDMW_ERR_LOGGER_APPLEAVING = pteidlib_dotNetPINVOKE.EIDMW_ERR_LOGGER_APPLEAVING_get();
  public static readonly int EIDMW_ERR_DOCTYPE_UNKNOWN = pteidlib_dotNetPINVOKE.EIDMW_ERR_DOCTYPE_UNKNOWN_get();
  public static readonly int EIDMW_ERR_CARDTYPE_BAD = pteidlib_dotNetPINVOKE.EIDMW_ERR_CARDTYPE_BAD_get();
  public static readonly int EIDMW_ERR_CARDTYPE_UNKNOWN = pteidlib_dotNetPINVOKE.EIDMW_ERR_CARDTYPE_UNKNOWN_get();
  public static readonly int EIDMW_ERR_CERT_NOISSUER = pteidlib_dotNetPINVOKE.EIDMW_ERR_CERT_NOISSUER_get();
  public static readonly int EIDMW_ERR_RELEASE_NEEDED = pteidlib_dotNetPINVOKE.EIDMW_ERR_RELEASE_NEEDED_get();
  public static readonly int EIDMW_ERR_BAD_TRANSACTION = pteidlib_dotNetPINVOKE.EIDMW_ERR_BAD_TRANSACTION_get();
  public static readonly int EIDMW_ERR_FILETYPE_UNKNOWN = pteidlib_dotNetPINVOKE.EIDMW_ERR_FILETYPE_UNKNOWN_get();
  public static readonly int EIDMW_ERR_CARD_CHANGED = pteidlib_dotNetPINVOKE.EIDMW_ERR_CARD_CHANGED_get();
  public static readonly int EIDMW_ERR_READERSET_CHANGED = pteidlib_dotNetPINVOKE.EIDMW_ERR_READERSET_CHANGED_get();
  public static readonly int EIDMW_ERR_NOT_ALLOW_BY_USER = pteidlib_dotNetPINVOKE.EIDMW_ERR_NOT_ALLOW_BY_USER_get();
  public static readonly int EIDMW_ERR_CERT_NOCRL = pteidlib_dotNetPINVOKE.EIDMW_ERR_CERT_NOCRL_get();
  public static readonly int EIDMW_ERR_CERT_NOOCSP = pteidlib_dotNetPINVOKE.EIDMW_ERR_CERT_NOOCSP_get();
  public static readonly int EIDMW_ERR_CERT_NOROOT = pteidlib_dotNetPINVOKE.EIDMW_ERR_CERT_NOROOT_get();
  public static readonly int EIDMW_ERR_USER_MUST_ANSWER = pteidlib_dotNetPINVOKE.EIDMW_ERR_USER_MUST_ANSWER_get();
  public static readonly int EIDMW_ERR_SYSTEM = pteidlib_dotNetPINVOKE.EIDMW_ERR_SYSTEM_get();
  public static readonly int EIDMW_ERR_SIGNAL = pteidlib_dotNetPINVOKE.EIDMW_ERR_SIGNAL_get();
}

}
