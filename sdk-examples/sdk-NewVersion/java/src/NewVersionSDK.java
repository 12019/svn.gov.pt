import java.io.*;
import javax.rmi.CORBA.Util;
import pt.gov.cartaodecidadao.*;
// Esta classe tera que ser colocada também no nosso codido!
import pteidlib.PteidException;

public class NewVersionSDK {

	public static String version="NEW-VERSION";

	// Apenas necessário para a versão antiga do MW
	static
	{
		if (version.equals("OFFICIAL")){
			try
			{
				System.out.println("a correr isto");
				System.loadLibrary("pteidlibJava_Wrapper.ibj");
			}
			catch (UnsatisfiedLinkError e)
			{
				System.err.println("Native code library failed to load.\n" + e);
				System.exit(1);
			}
		}
	}


	public static void test_Init(){
		String methodName="Init";

		Utils.writeTestedMethod(methodName);
		try {
			pteidlibJava_Wrapper.PTEID_Init("");
			Utils.writeReturnValues(methodName, "N/A: void method");
		} catch (Exception e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}

	public static void test_Exit(){
		String methodName="Exit";

		Utils.writeTestedMethod(methodName);
		try {
			pteidlibJava_Wrapper.PTEID_Exit(0);
			Utils.writeReturnValues(methodName, "N/A: void method");
		} catch (Exception e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}

	public static void test_GetCardType(){
		String methodName="GetCardType";
		tCompCardType cardtype;
		
		
		
		Utils.writeTestedMethod(methodName);
		try {
			cardtype = pteidlibJava_Wrapper.PTEID_GetCardType();
			Utils.writeReturnValues(methodName, String.valueOf(cardtype) );
		} catch (Exception e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}






	public static void main(String args[]){
		System.out.println("TESTING SDK VERSION: " + version );


		test_Init();
		
		test_GetCardType();
		
		test_Exit();

		Utils.writeToFile();

	}




}
