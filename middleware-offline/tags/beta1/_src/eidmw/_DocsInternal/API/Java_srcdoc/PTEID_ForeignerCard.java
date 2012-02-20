/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * This class represents a Foreigner card which is a particular PTEID_EIDCard
  * \see PTEID_ReaderContext.getForeignerCard()
  *********************************************************************************/
public class PTEID_ForeignerCard extends PTEID_EIDCard {
  private long swigCPtr;

  protected PTEID_ForeignerCard(long cPtr, boolean cMemoryOwn) {
    super(pteidlibJava_WrapperJNI.SWIGPTEID_ForeignerCardUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PTEID_ForeignerCard obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      pteidlibJava_WrapperJNI.delete_PTEID_ForeignerCard(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

}