/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package be.portugal.eid;

/******************************************************************************//**
  * Class to access the configuration parameters
  *********************************************************************************/
public class PTEID_Config extends PTEID_Object {
  private long swigCPtr;

  protected PTEID_Config(long cPtr, boolean cMemoryOwn) {
    super(pteidlibJava_WrapperJNI.SWIGPTEID_ConfigUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PTEID_Config obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if(swigCPtr != 0 && swigCMemOwn) {
      swigCMemOwn = false;
      pteidlibJava_WrapperJNI.delete_PTEID_Config(swigCPtr);
    }
    swigCPtr = 0;
    super.delete();
  }

	/**
	  * ctor
  	  * @param Param configuration parameter \see PTEID_Param
	  */
  public PTEID_Config(PTEID_Param Param) {
    this(pteidlibJava_WrapperJNI.new_PTEID_Config__SWIG_0(Param.swigValue()), true);
  }

	/**
	  * ctor
  	  * @param csName the name of the configuration parameter
  	  * @param czSection the section in the configuration settings
  	  * @param csDefaultValue the default value (string)
	  */
  public PTEID_Config(String csName, String czSection, String csDefaultValue) {
    this(pteidlibJava_WrapperJNI.new_PTEID_Config__SWIG_1(csName, czSection, csDefaultValue), true);
  }

	/**
	  * ctor
  	  * @param csName the name of the configuration parameter
  	  * @param czSection the section in the configuration settings
  	  * @param lDefaultValue the default value (numeric)
	  */
  public PTEID_Config(String csName, String czSection, int lDefaultValue) {
    this(pteidlibJava_WrapperJNI.new_PTEID_Config__SWIG_2(csName, czSection, lDefaultValue), true);
  }

	/**
	  * Get the configuration value (string)
  	  * @return the configuration setting (string)
	  */
  public String getString() throws java.lang.Exception {
    return pteidlibJava_WrapperJNI.PTEID_Config_getString(swigCPtr, this);
  }

	/**
	  * Get the configuration value (numeric)
  	  * @return the configuration setting (numeric)
	  */
  public int getLong() throws java.lang.Exception {
    return pteidlibJava_WrapperJNI.PTEID_Config_getLong(swigCPtr, this);
  }

	/**
	  * Set the configuration value (string)
  	  * @param csValue is the value for the configuration setting
	  */
  public void setString(String csValue) throws java.lang.Exception {
    pteidlibJava_WrapperJNI.PTEID_Config_setString(swigCPtr, this, csValue);
  }

	/**
	  * Set the configuration value (numeric)
  	  * @param lValue is the value for the configuration setting
	  */
  public void setLong(int lValue) throws java.lang.Exception {
    pteidlibJava_WrapperJNI.PTEID_Config_setLong(swigCPtr, this, lValue);
  }

}