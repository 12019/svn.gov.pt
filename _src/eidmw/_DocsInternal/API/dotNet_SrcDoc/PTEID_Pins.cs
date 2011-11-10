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

/// <summary>Container class for all pins on the card.</summary> 
public class PTEID_Pins : PTEID_Crypto {
  private HandleRef swigCPtr;

  internal PTEID_Pins(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_PinsUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_Pins obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_Pins() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_Pins(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  /// <summary>The number of pins on the card.</summary>
  public uint count() {
    uint ret = pteidlib_dotNetPINVOKE.PTEID_Pins_count(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  /// <summary>
  /// Get the pin by its Index.
  /// </summary>
  /// <remarks>
  /// Throw PTEID_ExParamRange exception if the index is out of range.
  /// </remarks>
  public PTEID_Pin getPinByNumber(uint ulIndex) {
    PTEID_Pin ret = new PTEID_Pin(pteidlib_dotNetPINVOKE.PTEID_Pins_getPinByNumber(swigCPtr, ulIndex), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
