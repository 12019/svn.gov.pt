using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OfficialSDK
{
    class Utils
    {

        public static String TestedMethods = "TESTED METHODS:\n";
        public static String ReturnValues = "";
        public static String ErrorValues = "";
        public static String Log = "";
        public static String Exceptions = "";



        public static void writeLog(String logLine)
        {
            Log += logLine;
        }


        public static void writeTestedMethod(String method)
        {
            Console.WriteLine("Estou aki: writeTestedMethod");
            Console.WriteLine("Variavel TestedMethods tem: " + TestedMethods);
            Console.WriteLine("Variavel method tem: " + method);
		    TestedMethods += method +"\n";
		    writeLog("Testing Method:" + method + "\n");
            Console.WriteLine("Variavel TestedMethods tem: " + TestedMethods);
		    //System.out.println("Testing: " + method );
	    }


        public static void writeReturnValues(String methodName, String value)
        {
		    ReturnValues+="Method: " + methodName + "          Returns value: " + value +"\n";
		    writeLog("Method: " + methodName + "          Returns value: " + value + "\n") ;
		    //System.out.println("Method: " + methodName + "          Returns value: " + value);	
	    }


        public static void writeException(Exception e)
        {
            Exceptions += e.ToString();
        }

        public static void writeToFile()
        {

            //PrintWriter pw;

            String fileOutput = "";

            fileOutput = "******************************\n";
            fileOutput += "TESTING SDK JAVA COMPATIBILITY\n";
            fileOutput += "******************************\n";

            fileOutput += TestedMethods;
            fileOutput += "\nCOMPLETE LOG:\n";
            fileOutput += Log;

            Console.WriteLine(fileOutput);
            
            try
            {
                System.IO.File.WriteAllText(@"C:\sdk-tests\Output.log", fileOutput);
                System.IO.File.WriteAllText(@"C:\sdk-tests\Exceptions.log", Exceptions);
            }
            catch (Exception e1)
            {
                Console.WriteLine("Exception on write file method: " + e1.ToString());
            }
        }
    }
}
