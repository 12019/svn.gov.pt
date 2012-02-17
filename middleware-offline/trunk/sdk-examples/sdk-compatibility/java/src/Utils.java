import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;


public class Utils {

	public static String TestedMethods="TESTED METHODS:\n"; 
	public static String ReturnValues="";
	public static String ErrorValues="";
	public static String Log="";
	public static String Exceptions="";
	
	
	public static void writeLog(String logLine){
		Log+=logLine;
	}
	
	
	public static void writeTestedMethod(String method){
		TestedMethods += method +"\n";
		writeLog("Testing Method:" + method + "\n");
		System.out.println("Testing: " + method );
	}
	
	
	public static void writeReturnValues(String methodName, String value){
		ReturnValues+="Method: " + methodName + "          Returns value: " + value +"\n";
		writeLog("Method: " + methodName + "          Returns value: " + value + "\n") ;
		System.out.println("Method: " + methodName + "          Returns value: " + value);	
	}
	
	
	public static void writeException(Exception e){
		Exceptions+=e.toString();
		PrintWriter pw;
		try {
			pw = new PrintWriter(new FileOutputStream("Exceptions-log"));
			e.printStackTrace(pw);
			pw.close();
			writeLog(e.toString()+"\n");
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}     
	}
	
	
	public static void writeByteArray(String filename, byte[] fileContent){
		
		try{
			FileOutputStream fos = new FileOutputStream(filename);
			fos.write(fileContent);
			fos.close();
			
			
		}catch(Exception e){
			System.out.println("Print By array exception: " + e);
		}
	}
	
	
	
	public static void writeToFile(){
		
		PrintWriter pw;
		
		String fileOutput="";
		
		fileOutput= "******************************\n";
		fileOutput+="TESTING SDK JAVA COMPATIBILITY\n";
		fileOutput+="******************************\n";
		
		fileOutput+=TestedMethods;
		fileOutput+="\nCOMPLETE LOG:\n";
		fileOutput+=Log;
		
		try {
			pw = new PrintWriter(new FileOutputStream("SDK_TESTING"));
			pw.write(fileOutput);
			pw.close();
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}    
		
	}
	
}
