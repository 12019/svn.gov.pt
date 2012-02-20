/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * Exception class User must answer (error code = EIDMW_ERR_USER_MUST_ANSWER)
  *
  *	Thrown when the user did not answer yet to allow or disallow reading the data from the card
  *********************************************************************************/
public class PTEID_ExUserMustAnswer extends PTEID_Exception {
  private long swigCPtr;

  protected PTEID_ExUserMustAnswer(long cPtr, boolean cMemoryOwn) {
    super(pteidlibJava_WrapperJNI.SWIGPTEID_ExUserMustAnswerUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PTEID_ExUserMustAnswer obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      pteidlibJava_WrapperJNI.delete_PTEID_ExUserMustAnswer(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

	/** Constructor */
  public PTEID_ExUserMustAnswer() {
    this(pteidlibJava_WrapperJNI.new_PTEID_ExUserMustAnswer(), true);
  }

}