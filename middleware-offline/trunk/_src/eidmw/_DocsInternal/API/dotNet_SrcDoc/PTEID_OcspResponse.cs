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

/// <summary>Class that represents one OCSP Response.</summary>
public class PTEID_OcspResponse : PTEID_Object {
  private HandleRef swigCPtr;

  internal PTEID_OcspResponse(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_OcspResponseUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_OcspResponse obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_OcspResponse() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_OcspResponse(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  /// <summary>
  /// Create an OcspResponse object from the URI only and CertID.
  /// </summary>
  /// <remarks>
  /// This OCSP Response is not link to any certificate so some methods could not be used.
  /// these methods throw PTEID_ExBadUsage exception.
  /// </remarks>
  public PTEID_OcspResponse(string uri, PTEID_HashAlgo hashAlgorithm, PTEID_ByteArray issuerNameHash, PTEID_ByteArray issuerKeyHash, PTEID_ByteArray serialNumber)
      : this(pteidlib_dotNetPINVOKE.new_PTEID_OcspResponse(uri, (int)hashAlgorithm, PTEID_ByteArray.getCPtr(issuerNameHash), PTEID_ByteArray.getCPtr(issuerKeyHash), PTEID_ByteArray.getCPtr(serialNumber)), true)
  {
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  /// <summary>Return the uri of the responder.</summary>
  public string getUri()
  {
    string ret = pteidlib_dotNetPINVOKE.PTEID_OcspResponse_getUri(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>Return the response.</summary>
  public PTEID_CertifStatus getResponse(PTEID_ByteArray response)
  {
    PTEID_CertifStatus ret = (PTEID_CertifStatus)pteidlib_dotNetPINVOKE.PTEID_OcspResponse_getResponse(swigCPtr, PTEID_ByteArray.getCPtr(response));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}