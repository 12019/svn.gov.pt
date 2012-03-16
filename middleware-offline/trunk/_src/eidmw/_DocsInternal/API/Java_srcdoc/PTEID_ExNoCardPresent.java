/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * Exception class No Card Present (error code = EIDMW_ERR_NO_CARD)
  *
  *	Thrown when no card is present
  * Used in : - PTEID_ReaderContext.getCardType()
  *           - PTEID_ReaderContext.getCard()
  *           - PTEID_ReaderContext.getEIDCard()
  *           - PTEID_ReaderContext.getKidsCard()
  *           - PTEID_ReaderContext.getForeignerCard()
  *           - PTEID_ReaderContext.getSISCard()
  *********************************************************************************/
public class PTEID_ExNoCardPresent extends PTEID_Exception {
  private long swigCPtr;

  protected PTEID_ExNoCardPresent(long cPtr, boolean cMemoryOwn) {
    super(pteidlibJava_WrapperJNI.SWIGPTEID_ExNoCardPresentUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PTEID_ExNoCardPresent obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      pteidlibJava_WrapperJNI.delete_PTEID_ExNoCardPresent(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

	/** Constructor */
  public PTEID_ExNoCardPresent() {
    this(pteidlibJava_WrapperJNI.new_PTEID_ExNoCardPresent(), true);
  }

}