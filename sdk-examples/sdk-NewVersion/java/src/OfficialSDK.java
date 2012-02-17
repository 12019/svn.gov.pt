import java.io.*;
import javax.rmi.CORBA.Util;
import pteidlib.*;
// Esta classe tera que ser colocada também no nosso codido!
import pteidlib.PteidException;

public class OfficialSDK {

	public static String version="OFFICIAL";

	// Apenas necessário para a versão antiga do MW
	static
	{
		if (version.equals("OFFICIAL")){
			try
			{
				System.out.println("a correr isto");
				System.loadLibrary("pteidlibj");
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
			pteid.Init("");
			Utils.writeReturnValues(methodName, "N/A: void method");
		} catch (PteidException e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}

	public static void test_Exit(){
		String methodName="Exit";

		Utils.writeTestedMethod(methodName);
		try {
			pteid.Exit(0);
			Utils.writeReturnValues(methodName, "N/A: void method");
		} catch (PteidException e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}

	public static void test_GetCardType(){
		String methodName="GetCardType";
		int cardtype;
		
		Utils.writeTestedMethod(methodName);
		try {
			cardtype = pteid.GetCardType();
			Utils.writeReturnValues(methodName, String.valueOf(cardtype) );
		} catch (PteidException e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}

	public static void dumpAddr(PTEID_ADDR addrData){
		
				Utils.writeLog("addrData.addressF " + addrData.addressF+"\n");
				Utils.writeLog("addrData.addrType " + addrData.addrType+"\n");
				Utils.writeLog("addrData.building " + addrData.building+"\n");
				Utils.writeLog("addrData.buildingAbbr " + addrData.buildingAbbr+"\n");
				Utils.writeLog("addrData.cityF " + addrData.cityF+"\n");
				Utils.writeLog("addrData.country " + addrData.country+"\n");
				Utils.writeLog("addrData.countryDescF " + addrData.countryDescF+"\n");
				Utils.writeLog("addrData.cp3 " + addrData.cp3+"\n");
				Utils.writeLog("addrData.cp4 " + addrData.cp4+"\n");
				Utils.writeLog("addrData.district " + addrData.district+"\n");
				Utils.writeLog("addrData.districtDesc " + addrData.districtDesc+"\n");
				Utils.writeLog("addrData.door " + addrData.door+"\n");
				Utils.writeLog("addrData.floor " + addrData.floor+"\n");
				Utils.writeLog("addrData.freguesia " + addrData.freguesia+"\n");
				Utils.writeLog("addrData.freguesiaDesc " + addrData.freguesiaDesc+"\n");
				Utils.writeLog("addrData.locality " + addrData.locality+"\n");
				Utils.writeLog("addrData.localityF " + addrData.localityF+"\n");
				Utils.writeLog("addrData.municipality " + addrData.municipality+"\n");
				Utils.writeLog("addrData.municipalityDesc " + addrData.municipalityDesc+"\n");
				Utils.writeLog("addrData.numMor " + addrData.numMor+"\n");
				Utils.writeLog("addrData.numMorF " + addrData.numMorF+"\n");
				Utils.writeLog("addrData.place " + addrData.place+"\n");
				Utils.writeLog("addrData.postal " + addrData.postal+"\n");
				Utils.writeLog("addrData.postalF " + addrData.postalF+"\n");
				Utils.writeLog("addrData.regioF " + addrData.regioF+"\n");
				Utils.writeLog("addrData.side " + addrData.side+"\n");
				Utils.writeLog("addrData.street " + addrData.street+"\n");
				Utils.writeLog("addrData.streettype " + addrData.streettype+"\n");
				Utils.writeLog("addrData.streettypeAbbr " + addrData.streettypeAbbr+"\n");
				Utils.writeLog("addrData.version " + addrData.version+"\n");
	}

	public static void dumpID(PTEID_ID idData){
		Utils.writeLog("idData.birthDate "+idData.birthDate+"\n");       
		Utils.writeLog("idData.cardNumber " + idData.cardNumber+"\n");
		Utils.writeLog("idData.cardNumberPAN " + idData.cardNumberPAN+"\n");
		Utils.writeLog("idData.cardVersion " + idData.cardVersion+"\n");
		Utils.writeLog("idData.country " + idData.country+"\n");
		Utils.writeLog("idData.deliveryDate " + idData.deliveryDate+"\n");
		Utils.writeLog("idData.deliveryEntity " + idData.deliveryEntity+"\n");
		Utils.writeLog("idData.documentType " + idData.documentType+"\n");
		Utils.writeLog("idData.firstname " + idData.firstname+"\n");
		Utils.writeLog("idData.firstnameFather " + idData.firstnameFather+"\n");
		Utils.writeLog("idData.firstnameMother " + idData.firstnameMother+"\n");
		Utils.writeLog("idData.height " + idData.height+"\n");
		Utils.writeLog("idData.locale " + idData.locale+"\n");
		Utils.writeLog("idData.mrz1 " + idData.mrz1+"\n");
		Utils.writeLog("idData.mrz2 " + idData.mrz2+"\n");
		Utils.writeLog("idData.mrz3 " + idData.mrz3+"\n");
		Utils.writeLog("idData.name " + idData.name+"\n");
		Utils.writeLog("idData.nameFather " + idData.nameFather+"\n");
		Utils.writeLog("idData.nameMother " + idData.nameMother+"\n");
		Utils.writeLog("idData.nationality " + idData.nationality+"\n");
		Utils.writeLog("idData.notes " + idData.notes+"\n");
		Utils.writeLog("idData.numBI " + idData.numBI+"\n");
		Utils.writeLog("idData.numNIF " + idData.numNIF+"\n");
		Utils.writeLog("idData.numSNS " + idData.numSNS+"\n");
		Utils.writeLog("idData.numSS " + idData.numSS+"\n");
		Utils.writeLog("idData.sex " + idData.sex+"\n");
		Utils.writeLog("idData.validityDate " + idData.validityDate+"\n");
		Utils.writeLog("idData.version " + idData.version+"\n");
	}

	
	public static void test_GetAddr(){
		String methodName="GetAddr";
		PTEID_ADDR idAddr;
		
		Utils.writeTestedMethod(methodName);
		try {
			idAddr = pteid.GetAddr();
			dumpAddr(idAddr);
			Utils.writeReturnValues(methodName, "Returns PTEID_ADDR Object" );
		} catch (PteidException e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
		
	}
	

	public static void test_GetID(){
		String methodName="GetID";
		PTEID_ID idData;
		
		Utils.writeTestedMethod(methodName);
		try {
			idData = pteid.GetID();
			dumpID(idData);
			Utils.writeReturnValues(methodName, "Returns PTEID_ID Object" );
		} catch (PteidException e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}

	public static void dumpPic(PTEID_PIC pic){
		try
		{
			Utils.writeLog("pic.cbeff " + pic.cbeff+"\n");
			Utils.writeLog("pic.facialinfo " + pic.facialinfo + "\n"); 
			String photo = "photo.jp2";
			FileOutputStream oFile = new FileOutputStream(photo);
			oFile.write(pic.picture);
			oFile.close();
		}
		catch (FileNotFoundException excep)
		{
			System.out.println(excep.getMessage());
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public static void test_GetPic(){
		String methodName="GetPic";
		PTEID_PIC picData;
		
		Utils.writeTestedMethod(methodName);
		try {
			picData = pteid.GetPic();
			dumpPic(picData);
			Utils.writeReturnValues(methodName, "Returns PTEID_PIC Object" );
		} catch (PteidException e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
	}
	
	
	public static void dumpCerts(PTEID_Certif[] certs){
		for (int i=0; i<certs.length;i++){
			Utils.writeLog("Dumping Certificate " + i + ":\n");
			Utils.writeLog("cert.certifLabel " + certs[i].certifLabel + "\n");
			Utils.writeLog("cert.certif " + certs[i].certif + "\n");
		}
	}
	
	public static void test_GetCertificates(){
		String methodName="GetCertificates";
		PTEID_Certif[] certs;
		
		Utils.writeTestedMethod(methodName);
		try {
			certs = pteid.GetCertificates();
			dumpCerts(certs);
			Utils.writeReturnValues(methodName, "Returns PTEID_Certif[] Array" );
		} catch (PteidException e) {
			e.printStackTrace();
			Utils.writeException(e);
		}
		
	}
	
	


	public static void main(String args[]){
		System.out.println("TESTING SDK VERSION: " + version );

				
		test_Init();
	
		try {
			pteid.SetSODChecking(false);
		} catch (PteidException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		test_GetCardType();
		
		test_GetID();
		
		test_GetAddr();
		
		test_GetPic();
		
		test_GetCertificates();
		
		test_Exit();

		Utils.writeToFile();

	}




}
