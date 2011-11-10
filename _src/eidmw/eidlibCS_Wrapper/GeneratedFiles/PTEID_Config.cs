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

public class PTEID_Config : PTEID_Object {
  private HandleRef swigCPtr;

  internal PTEID_Config(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_ConfigUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_Config obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_Config() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_Config(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public PTEID_Config(PTEID_Param Param) : this(pteidlib_dotNetPINVOKE.new_PTEID_Config__SWIG_0((int)Param), true) {
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public PTEID_Config(string csName, string czSection, string csDefaultValue) : this(pteidlib_dotNetPINVOKE.new_PTEID_Config__SWIG_1(csName, czSection, csDefaultValue), true) {
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public PTEID_Config(string csName, string czSection, int lDefaultValue) : this(pteidlib_dotNetPINVOKE.new_PTEID_Config__SWIG_2(csName, czSection, lDefaultValue), true) {
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public string getString() {
    string ret = pteidlib_dotNetPINVOKE.PTEID_Config_getString(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public int getLong() {
    int ret = pteidlib_dotNetPINVOKE.PTEID_Config_getLong(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public void setString(string csValue) {
    pteidlib_dotNetPINVOKE.PTEID_Config_setString(swigCPtr, csValue);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public void setLong(int lValue) {
    pteidlib_dotNetPINVOKE.PTEID_Config_setLong(swigCPtr, lValue);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

}

}
