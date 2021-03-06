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

public class PTEID_SmartCard : PTEID_Card {
  private HandleRef swigCPtr;

  internal PTEID_SmartCard(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_SmartCardUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_SmartCard obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_SmartCard() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_SmartCard(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public void selectApplication(PTEID_ByteArray applicationId) {
    pteidlib_dotNetPINVOKE.PTEID_SmartCard_selectApplication(swigCPtr, PTEID_ByteArray.getCPtr(applicationId));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public virtual PTEID_ByteArray sendAPDU(PTEID_ByteArray cmd, PTEID_Pin pin, string csPinCode) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_SmartCard_sendAPDU__SWIG_0(swigCPtr, PTEID_ByteArray.getCPtr(cmd), PTEID_Pin.getCPtr(pin), csPinCode), true);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray sendAPDU(PTEID_ByteArray cmd, PTEID_Pin pin) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_SmartCard_sendAPDU__SWIG_1(swigCPtr, PTEID_ByteArray.getCPtr(cmd), PTEID_Pin.getCPtr(pin)), true);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public override PTEID_ByteArray sendAPDU(PTEID_ByteArray cmd) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_SmartCard_sendAPDU__SWIG_2(swigCPtr, PTEID_ByteArray.getCPtr(cmd)), true);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual int readFile(string fileID, PTEID_ByteArray arg1, PTEID_Pin pin, string csPinCode) {
    int ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_readFile__SWIG_0(swigCPtr, fileID, PTEID_ByteArray.getCPtr(arg1), PTEID_Pin.getCPtr(pin), csPinCode);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual int readFile(string fileID, PTEID_ByteArray arg1, PTEID_Pin pin) {
    int ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_readFile__SWIG_1(swigCPtr, fileID, PTEID_ByteArray.getCPtr(arg1), PTEID_Pin.getCPtr(pin));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual int readFile(string fileID, PTEID_ByteArray arg1) {
    int ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_readFile__SWIG_2(swigCPtr, fileID, PTEID_ByteArray.getCPtr(arg1));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool writeFile(string fileID, PTEID_ByteArray arg1, PTEID_Pin pin, string csPinCode) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_writeFile__SWIG_0(swigCPtr, fileID, PTEID_ByteArray.getCPtr(arg1), PTEID_Pin.getCPtr(pin), csPinCode);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool writeFile(string fileID, PTEID_ByteArray arg1, PTEID_Pin pin) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_writeFile__SWIG_1(swigCPtr, fileID, PTEID_ByteArray.getCPtr(arg1), PTEID_Pin.getCPtr(pin));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public override bool writeFile(string fileID, PTEID_ByteArray arg1) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_writeFile__SWIG_2(swigCPtr, fileID, PTEID_ByteArray.getCPtr(arg1));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual uint pinCount() {
    uint ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_pinCount(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_Pins getPins() {
    PTEID_Pins ret = new PTEID_Pins(pteidlib_dotNetPINVOKE.PTEID_SmartCard_getPins(swigCPtr), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual uint certificateCount() {
    uint ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_certificateCount(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_Certificates getCertificates() {
    PTEID_Certificates ret = new PTEID_Certificates(pteidlib_dotNetPINVOKE.PTEID_SmartCard_getCertificates(swigCPtr), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray getChallenge(bool bForceNewInit) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_SmartCard_getChallenge__SWIG_0(swigCPtr, bForceNewInit), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray getChallenge() {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_SmartCard_getChallenge__SWIG_1(swigCPtr), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray getChallengeResponse() {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_SmartCard_getChallengeResponse(swigCPtr), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool verifyChallengeResponse(PTEID_ByteArray challenge, PTEID_ByteArray response) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_SmartCard_verifyChallengeResponse(swigCPtr, PTEID_ByteArray.getCPtr(challenge), PTEID_ByteArray.getCPtr(response));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
