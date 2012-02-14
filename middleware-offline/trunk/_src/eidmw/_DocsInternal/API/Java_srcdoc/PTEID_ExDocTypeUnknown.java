/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * Exception class Document Type Unknown (error code = EIDMW_ERR_DOCTYPE_UNKNOWN)
  *
  *	Thrown when the document type doesn't exist for this card
  * Used in : - PTEID_Card.getDocument(PTEID_DocumentType type)
  *********************************************************************************/
public class PTEID_ExDocTypeUnknown extends PTEID_Exception {
  private long swigCPtr;

  protected PTEID_ExDocTypeUnknown(long cPtr, boolean cMemoryOwn) {
    super(pteidlibJava_WrapperJNI.SWIGPTEID_ExDocTypeUnknownUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PTEID_ExDocTypeUnknown obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      pteidlibJava_WrapperJNI.delete_PTEID_ExDocTypeUnknown(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

	/** Constructor */
  public PTEID_ExDocTypeUnknown() {
    this(pteidlibJava_WrapperJNI.new_PTEID_ExDocTypeUnknown(), true);
  }

}