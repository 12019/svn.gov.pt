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

public class PTEID_CardVersionInfo : PTEID_XMLDoc {
  private HandleRef swigCPtr;

  internal PTEID_CardVersionInfo(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_CardVersionInfoUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_CardVersionInfo obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_CardVersionInfo() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_CardVersionInfo(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public string getSerialNumber() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getSerialNumber(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getComponentCode() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getComponentCode(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getOsNumber() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getOsNumber(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getOsVersion() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getOsVersion(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getSoftmaskNumber() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getSoftmaskNumber(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getSoftmaskVersion() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getSoftmaskVersion(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getAppletVersion() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getAppletVersion(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getGlobalOsVersion() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getGlobalOsVersion(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getAppletInterfaceVersion() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getAppletInterfaceVersion(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getPKCS1Support() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getPKCS1Support(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getKeyExchangeVersion() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getKeyExchangeVersion(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getAppletLifeCycle() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getAppletLifeCycle(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getGraphicalPersonalisation() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getGraphicalPersonalisation(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getElectricalPersonalisation() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getElectricalPersonalisation(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public string getElectricalPersonalisationInterface() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getElectricalPersonalisationInterface(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PTEID_ByteArray getSignature() {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_CardVersionInfo_getSignature(swigCPtr), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}