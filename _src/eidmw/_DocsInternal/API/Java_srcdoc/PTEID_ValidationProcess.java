/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * Class that holds the possible validation processes to be used
  *********************************************************************************/
public final class PTEID_ValidationProcess {
	/**
	* no validation process
	*/
  public final static PTEID_ValidationProcess PTEID_VALIDATION_PROCESS_NONE = new PTEID_ValidationProcess("PTEID_VALIDATION_PROCESS_NONE", pteidlibJava_WrapperJNI.PTEID_VALIDATION_PROCESS_NONE_get());
	/**
	* CRL validation
	*/
  public final static PTEID_ValidationProcess PTEID_VALIDATION_PROCESS_CRL = new PTEID_ValidationProcess("PTEID_VALIDATION_PROCESS_CRL");
	/**
	* OCSP validation
	*/
  public final static PTEID_ValidationProcess PTEID_VALIDATION_PROCESS_OCSP = new PTEID_ValidationProcess("PTEID_VALIDATION_PROCESS_OCSP");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static PTEID_ValidationProcess swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + PTEID_ValidationProcess.class + " with value " + swigValue);
  }

  private PTEID_ValidationProcess(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private PTEID_ValidationProcess(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private PTEID_ValidationProcess(String swigName, PTEID_ValidationProcess swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static PTEID_ValidationProcess[] swigValues = { PTEID_VALIDATION_PROCESS_NONE, PTEID_VALIDATION_PROCESS_CRL, PTEID_VALIDATION_PROCESS_OCSP };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}

