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

public class PTEID_Card : PTEID_Object {
  private HandleRef swigCPtr;

  internal PTEID_Card(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_CardUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_Card obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_Card() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_Card(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public virtual PTEID_CardType getType() {
    PTEID_CardType ret = (PTEID_CardType)pteidlib_dotNetPINVOKE.PTEID_Card_getType(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_XMLDoc getDocument(PTEID_DocumentType type) {
    PTEID_XMLDoc ret = new PTEID_XMLDoc(pteidlib_dotNetPINVOKE.PTEID_Card_getDocument(swigCPtr, (int)type), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray getRawData(PTEID_RawDataType type) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_Card_getRawData(swigCPtr, (int)type), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray sendAPDU(PTEID_ByteArray cmd) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_Card_sendAPDU(swigCPtr, PTEID_ByteArray.getCPtr(cmd)), true);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray readFile(string fileID, uint ulOffset, uint ulMaxLength) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_Card_readFile__SWIG_0(swigCPtr, fileID, ulOffset, ulMaxLength), true);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray readFile(string fileID, uint ulOffset) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_Card_readFile__SWIG_1(swigCPtr, fileID, ulOffset), true);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual PTEID_ByteArray readFile(string fileID) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_Card_readFile__SWIG_2(swigCPtr, fileID), true);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool writeFile(string fileID, PTEID_ByteArray oData, uint ulOffset) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_Card_writeFile__SWIG_0(swigCPtr, fileID, PTEID_ByteArray.getCPtr(oData), ulOffset);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public virtual bool writeFile(string fileID, PTEID_ByteArray oData) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_Card_writeFile__SWIG_1(swigCPtr, fileID, PTEID_ByteArray.getCPtr(oData));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
