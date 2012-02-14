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

/// <summary>
/// Exception class Bad Parameter Range (error code = EIDMW_ERR_PARAM_RANGE).
/// Throw when the element ask is out of range.
/// Used in : 
/// - PTEID_ReaderSet::getReaderName(unsigned long ulIndex) 
/// - PTEID_ReaderSet::getReaderByNum(unsigned long ulIndex) 
/// - PTEID_Certificate::getChildren(unsigned long ulIndex)
/// - PTEID_Certificates::getCertByNumber(unsigned long ulIndex)
/// - PTEID_Pins::getPinByNumber(unsigned long ulIndex)
/// </summary>
public class PTEID_ExParamRange : PTEID_Exception {
  private HandleRef swigCPtr;

  internal PTEID_ExParamRange(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_ExParamRangeUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_ExParamRange obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_ExParamRange() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_ExParamRange(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public PTEID_ExParamRange() : this(pteidlib_dotNetPINVOKE.new_PTEID_ExParamRange(), true) {
  }

}

}