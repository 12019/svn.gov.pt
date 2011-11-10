/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * Exception class Release Needed (error code = EIDMW_ERR_RELEASE_NEEDED)
  *
  *	Thrown when the application closes without calling PTEID_RealeaseSDK()
  *********************************************************************************/
public class PTEID_ExReleaseNeeded extends PTEID_Exception {
  private long swigCPtr;

  protected PTEID_ExReleaseNeeded(long cPtr, boolean cMemoryOwn) {
    super(pteidlibJava_WrapperJNI.SWIGPTEID_ExReleaseNeededUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PTEID_ExReleaseNeeded obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      pteidlibJava_WrapperJNI.delete_PTEID_ExReleaseNeeded(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

	/** Constructor */
  public PTEID_ExReleaseNeeded() {
    this(pteidlibJava_WrapperJNI.new_PTEID_ExReleaseNeeded(), true);
  }

}
