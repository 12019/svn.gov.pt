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

public class PTEID_EIdFullDoc : PTEID_XMLDoc {
  private HandleRef swigCPtr;

  internal PTEID_EIdFullDoc(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_EIdFullDocUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_EIdFullDoc obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_EIdFullDoc() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_EIdFullDoc(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

}

}
