import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import pt.gov.cartaodecidadao.PTEID_ByteArray;
import pt.gov.cartaodecidadao.PTEID_CCXML_Doc;
import pt.gov.cartaodecidadao.PTEID_EIDCard;
import pt.gov.cartaodecidadao.PTEID_EId;
import pt.gov.cartaodecidadao.PTEID_Exception;
import pt.gov.cartaodecidadao.PTEID_Pin;
import pt.gov.cartaodecidadao.PTEID_Pins;
import pt.gov.cartaodecidadao.PTEID_ReaderContext;
import pt.gov.cartaodecidadao.PTEID_ReaderSet;
import pt.gov.cartaodecidadao.PTEID_SigVerifier;
import pt.gov.cartaodecidadao.PTEID_XmlUserRequestedInfo;
import pt.gov.cartaodecidadao.PTEID_ulwrapper;
import pt.gov.cartaodecidadao.PTEID_Address;

import pt.gov.cartaodecidadao.SWIGTYPE_p_unsigned_long;
import pt.gov.cartaodecidadao.XMLUserData;



public class ExampleSDK {

	PTEID_ReaderSet readerSet = null;
	PTEID_ReaderContext readerContext = null;
	PTEID_EIDCard idCard = null;

	public PTEID_ReaderSet readerSet(){return readerSet;}
	public PTEID_ReaderContext readerContext(){return readerContext;}
	public PTEID_EIDCard idCard(){return idCard;}




	private static final String FREE_IMAGE = "FreeImage";
	private static final String X_SEC = "xsec_1_6";
	private static final String PTEID_APPLAYER = "pteid35applayer";
	private static final String PTEID_CARDLAYER = "pteid35cardlayer";
	private static final String PTEID_DLGS = "pteid35DlgsWin32";
	private static final String PTEID_COMMON = "pteid35common";
	private static final String XERCES_C_3_1 = "xerces-c_3_1";
	private static final String SSLEAY_32 = "ssleay32";
	private static final String LIBEAY_32 = "libeay32";
	private static final String LIBCURL = "libcurl";
	private static final String ZLIB = "zlib1";
	private static final String CC_JAVA_WRAPPER_WINDOWS = "pteidlibJava_Wrapper";
	private static final String CC_JAVA_WRAPPER_LINUX_MACOS = "pteidlibJava_Wrapper";



	private static final String[] WINDOWS_X86_LIBS = { ZLIB, LIBCURL, LIBEAY_32, SSLEAY_32, XERCES_C_3_1, PTEID_COMMON, PTEID_DLGS, PTEID_CARDLAYER,
		FREE_IMAGE, X_SEC, PTEID_APPLAYER, CC_JAVA_WRAPPER_WINDOWS };

	private static final String[] WINDOWS_AMD64_LIBS ={};

	static { 
		try { 

			final String osName = System.getProperty("os.name");
			final String osArch = System.getProperty("os.arch");


			if (osName.contains("Linux")) {
				System.loadLibrary(CC_JAVA_WRAPPER_LINUX_MACOS);
			} else if (osName.contains("Mac OS X")) {
				System.loadLibrary(CC_JAVA_WRAPPER_LINUX_MACOS);
			} else if (osName.contains("Windows")) {
				// windows acts "peculiar" when it comes to dependent libraries so we have to load all of them, one at a time, in order.
				for (final String library : osArch.equals("x86") ? WINDOWS_X86_LIBS : WINDOWS_AMD64_LIBS) {
					System.loadLibrary(library);
				}
			} else {
				// If it's not a Linux or a mac or a windows it must be a *nix =) we hope
				System.loadLibrary(CC_JAVA_WRAPPER_LINUX_MACOS);
			}
		}catch (Exception e){
			e.printStackTrace();
		}
	} 


	// UTILS
	private String readInput(String prompt_msg){
		String answer="";
		System.out.println(prompt_msg);
		try {
			InputStreamReader isr = new InputStreamReader(System.in);
			BufferedReader br = new BufferedReader(isr);
			answer = br.readLine();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return answer;
	}


	private void init() {
		try {
			PTEID_ReaderSet.initSDK();
			readerSet = PTEID_ReaderSet.instance();
		} catch (PTEID_Exception ex) {
			ex.printStackTrace();
		}
	}
	
	private void InitializeCard() {
		try {
			this.idCard = this.readerContext.getEIDCard();
		} catch (PTEID_Exception ex) {
			ex.printStackTrace();
		}
	}
	
	


	private void findSmartCardReaderWithCard(String readerName) {
		try {
			PTEID_ReaderContext rContext = readerSet.getReaderByName(readerName);

			System.out.println("Reader: " + readerName);
			if (rContext.isCardPresent()) {
				readerContext = rContext;
			}
			System.out.println("\tCard present: " + (rContext.isCardPresent() ? "yes" : "no") + "\n");

		} catch (PTEID_Exception ex) {
			ex.printStackTrace();
		}
	}

	private void getSmartCardReaders() {
		try {
			long nrReaders = readerSet.readerCount();
			System.out.println("Nr of card readers detected: " + nrReaders);

			for (int readerIdx = 0; readerIdx < nrReaders; readerIdx++) {
				String readerName = readerSet.getReaderName(readerIdx);
				findSmartCardReaderWithCard(readerName);
			}
		} catch (PTEID_Exception ex) {
			ex.printStackTrace();
		}
	}

	/*
	private void dumpNotes(){
		this.idCard = this.readerContext.getEIDCard();

		this.idCard.getID().getN

	}
	 */

	private void dumpID(){
		try {
			this.idCard = this.readerContext.getEIDCard();

			System.out.println("\n\nCitizen identification");
			System.out.println("--------------------------------------");
			System.out.println("deliveryEntity              " + this.idCard.getID().getIssuingEntity());
			System.out.println("country                     " + this.idCard.getID().getCountry());
			System.out.println("documentType                " + this.idCard.getID().getDocumentType());
			System.out.println("cardNumber                  " + this.idCard.getID().getDocumentNumber());
			System.out.println("cardNumberPAN               " + this.idCard.getID().getDocumentPAN());
			System.out.println("cardVersion                 " + this.idCard.getID().getDocumentVersion());
			System.out.println("deliveryDate                " + this.idCard.getID().getValidityBeginDate());
			System.out.println("locale                      " + this.idCard.getID().getLocalofRequest());
			System.out.println("validityDate                " + this.idCard.getID().getValidityEndDate());
			System.out.println("name                        " + this.idCard.getID().getSurname());
			//System.out.println("firstname                   " + id.getGivenName());
			System.out.println("sex                         " + this.idCard.getID().getGender());
			System.out.println("nationality                 " + this.idCard.getID().getNationality());
			System.out.println("birthDate                   " + this.idCard.getID().getDateOfBirth());
			System.out.println("height                      " + this.idCard.getID().getHeight());
			System.out.println("numBI                       " + this.idCard.getID().getCivilianIdNumber());
			System.out.println("nameFather                  " + this.idCard.getID().getSurnameFather());
			System.out.println("firstnameFather             " + this.idCard.getID().getGivenNameFather());
			System.out.println("nameMother                  " + this.idCard.getID().getSurnameMother());
			System.out.println("firstnameMother             " + this.idCard.getID().getGivenNameMother());
			System.out.println("numNIF                      " + this.idCard.getID().getTaxNo());
			System.out.println("numSS                       " + this.idCard.getID().getSocialSecurityNumber());
			System.out.println("numSNS                      " + this.idCard.getID().getHealthNumber());
			System.out.println("Accidental indications      " + this.idCard.getID().getAccidentalIndications());
			System.out.println("mrz1                        " + this.idCard.getID().getMRZ1());
			System.out.println("mrz2                        " + this.idCard.getID().getMRZ2());
			System.out.println("mrz3                        " + this.idCard.getID().getMRZ3());
			System.out.println("--------------------------------------");

		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}
	}

	private void dumpAddress(){
		System.out.println("dumping address");
		try{
			this.idCard = this.readerContext.getEIDCard();
			PTEID_Address adr = this.idCard.getAddr();
			System.out.println(adr.getDistrict());
		}catch (Exception e){
			System.out.println("dumping address- Exception");
			e.printStackTrace();
		}
	}

	/**
	 * @return the PTEID_ADDR object with all the address information

    public PTEID_ADDR getPteidAddr() {
	try {
	    return new PTEID_ADDR(card.getAddr());
	} catch (Throwable ex) {
	    LOGGER.log(Level.SEVERE, "Error retrieving address info", ex);
	    return null;
	}
    }
	 */



	private void verifyAddressPIN(){
		PTEID_Pins pins;
		String secret;
		try {
			pins = this.idCard.getPins();
			for (int i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);
				if (pin.getLabel().equalsIgnoreCase("PIN da Morada")) {
					secret=readInput("Insira o PIN de Morada:");
					PTEID_ulwrapper wrap = new PTEID_ulwrapper(-1);
					if (pin.verifyPin(secret, wrap,false)) {
						System.out.println("PIN OK!!!!\n");
					}
				}
			}
		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}

	}

	private void listPins(){
		PTEID_Pins pins;
		try {
			pins = this.idCard.getPins();
			for (int i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);
				System.out.println(pin.getLabel());
			}
		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}
	}



	private void verifySignPIN(){
		PTEID_Pins pins;
		try {
			pins = this.idCard.getPins();
			for (int i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);
				if (pin.getLabel().equalsIgnoreCase("PIN da Assinatura")) {
					System.out.println("Entrei aqui - assinatura");
					PTEID_ulwrapper wrap = new PTEID_ulwrapper(-1);
					if (pin.verifyPin("", wrap,false)) {
						System.out.println("PIN OK!!!!\n");
					}
				}
			}
		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}
	}


	private void verifySignPINNoWindow(){
		System.out.println("verifySignPINNoWindow()");
		boolean PIN_validated=false;
		String secret;
		PTEID_Pins pins;

		try {
			this.idCard = this.readerContext.getEIDCard();
			pins = this.idCard.getPins();
			System.out.println("this.idCard.getPins()");
			for (int i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);
				if (pin.getLabel().equalsIgnoreCase("PIN da Assinatura")) {
					PTEID_ulwrapper wrap = new PTEID_ulwrapper(-1);
					while (!PIN_validated){
						secret=readInput("Insira o PIN de assinatura:");
						if (pin.verifyPin(secret, wrap,false)) {
							PIN_validated=true;
							System.out.println("PIN OK!!!!\n");
						}	
					}
				}
			}
		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}
	}

	private void verifyAuthPINNoWindow(){
		boolean PIN_validated=false;
		String secret;
		PTEID_Pins pins;
		try {
			pins = this.idCard.getPins();
			for (int i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);
				if (pin.getLabel().substring(0, 11).equalsIgnoreCase("PIN da Aute")) {
					PTEID_ulwrapper wrap = new PTEID_ulwrapper(-1);
					while (!PIN_validated){
						secret=readInput("Insira o PIN de Autenticação:");
						if (pin.verifyPin(secret, wrap,false)) {
							PIN_validated=true;
							System.out.println("PIN OK!!!!\n");
						}	
					}
				}
			}
		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}
	}

	private void verifyAutenticationPin(){
		PTEID_Pins pins;
		try {
			pins = this.idCard.getPins();
			for (int i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);

				//String i = pin.getLabel();

				System.out.println();


				if (pin.getLabel().substring(0, 11).equalsIgnoreCase("PIN da Aute")) {
					System.out.println("Entrei aqui - autenticacao");
					PTEID_ulwrapper wrap = new PTEID_ulwrapper(-1);
					if (pin.verifyPin("", wrap,false)) {
						System.out.println("PIN OK!!!!\n");
					}
				}
			}
		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}

	}





	private void verifyPins(){
		//verifyAddressPIN();
		verifySignPIN();
		verifyAutenticationPin();
	}

	private void signXades(){
		try{
			System.out.println("Here");
			String[] file_list={"teste.txt","teste2.txt"};
			idCard.SignXades(file_list,file_list.length,"signature3.zip");
			System.out.println("ASSINEI!!");
		}catch (Exception e){
			e.printStackTrace();
		}

	}

	private void signXadesT(){
		try{
			String[] file_list={"teste","teste2"};
			idCard.SignXadesT(file_list,file_list.length,"signature-xadest-2.zip");
		}catch (Exception e){
			e.printStackTrace();
		}
	}

	private void verifySignature()
	{
		String errors = new String();  
		PTEID_ulwrapper error_size = new PTEID_ulwrapper(0);
		boolean result = PTEID_SigVerifier.VerifySignature("signature3.zip", errors, error_size);
		if (!result)
			System.out.println("Validation failed!");
		else
			System.out.println("Validation succeeded!");			
	}

	private void verifySignatureXadesT()
	{
		String errors = new String();  
		PTEID_ulwrapper error_size = new PTEID_ulwrapper(0);
		boolean result = PTEID_SigVerifier.VerifySignature("signature-xadest-2.zip", errors, error_size);
		if (!result)
			System.out.println("Validation failed!");
		else
			System.out.println("Validation succeeded!");			
	}



	private byte[] getFirst256(byte[] content){
		byte[] new_content;
		new_content = new byte[256];

		for (int i=0;i<255;i++)
		{
			new_content[i]=content[i];
		}
		return new_content;
	}

	private void readNotes()
	{
		byte[] content;
		String NOTES_FILE_ID = "3f005f00ef07";
		String notes_content="";

		try {
			this.idCard = this.readerContext.getEIDCard();
			PTEID_ByteArray bytesRead = idCard.readFile(NOTES_FILE_ID, 0);
			//Get Only 256 bytes
			content =  getFirst256(bytesRead.GetBytes());
			notes_content= new String(getFirst256(content)).trim(); // yes, this will remove valid white space in the end...
		} catch (Throwable ex) {
			ex.printStackTrace();
		}
		System.out.println(notes_content);
	}



	/*
	 * Sign a given data with the SHA-1 algorithm. This process required the Authentication PIN
	 * 
	 * @param inputData
	 *            the data to be signed
	 * @return the byte[] correspondent to what was given but signed
	 * 
	 * @throws CCError
	 */
	/*
	public byte[] signData(final byte[] inputData) throws CCError {
	// we shouldn't use a byte[] from parameter instead we should use a copy of the data.
	final byte[] dataToBeSigned = inputData.clone();
	try {
	    MessageDigest md = MessageDigest.getInstance("SHA-1");
	    final byte[] digest = md.digest(dataToBeSigned);

	    final byte[] SHA1_MAGIC_STRING = new byte[] { 0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a, 0x05, 0x00, 0x04, 0x14 };

	    final byte[] hashMagicString = SHA1_MAGIC_STRING;

	    final byte[] fullDigest = Arrays.copyOf(hashMagicString, hashMagicString.length + digest.length);
	    System.arraycopy(digest, 0, fullDigest, hashMagicString.length, digest.length);

	    final PTEID_PIN PIN = new PTEID_PIN(PINUtils.getAuthenticationPin(card));
	    pinCallback.verifyPIN(PIN, PIN.getLabel(), bundle.getString("request.authentication.pin.msg"),
				  bundle.getString("request.authentication.pin.msgForPINPad"));

	    final PTEID_ByteArray outputData = card.Sign(new PTEID_ByteArray(fullDigest, fullDigest.length));

	    return outputData.GetBytes();
	} catch (PTEID_Exception ex) {
	    throw new CCError(ex);
	} catch (NoSuchAlgorithmException ex) {
	    throw new CCError(ex);
	}
    }

	 */	





	public void signData(){

		String 			str_to_be_signed;
		PTEID_ByteArray content_to_be_signed;
		PTEID_ByteArray content_signed;

		str_to_be_signed="String a serassinada";

		try {
			this.idCard = this.readerContext.getEIDCard();

			content_to_be_signed = new PTEID_ByteArray(str_to_be_signed.getBytes(),str_to_be_signed.length());
			content_signed = this.idCard.Sign(content_to_be_signed);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}


	public void writeNotes(String strNotes) {
		int MAX_NOTES_SIZE=256;
		byte NOTES_PADDING_BYTE = 0;
		String NOTES_FILE_ID = "3f005f00ef07";

		this.verifyAuthPINNoWindow();

		try {

			byte[] out = new byte[MAX_NOTES_SIZE];
			byte[] notes = strNotes.getBytes();
			int i = 0;
			while ((i < notes.length) && (i < MAX_NOTES_SIZE)) {
				out[i] = notes[i];
				i++;
			}
			while (i < MAX_NOTES_SIZE) {
				out[i++] = NOTES_PADDING_BYTE;
			}


			this.idCard = this.readerContext.getEIDCard();
			this.idCard.writeFile(NOTES_FILE_ID, new PTEID_ByteArray(out, out.length-1));
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	private void generateXML(){

		try{	

			
			
			verifyAddressPIN();
			PTEID_XmlUserRequestedInfo req3 = new PTEID_XmlUserRequestedInfo();
	        	PTEID_CCXML_Doc result3 = this.idCard.getXmlCCDoc(req3);
	        	System.out.println("----------> "+ result3.getCCXML());
			
			
			
			System.out.println("gerar morada");
			PTEID_XmlUserRequestedInfo req1 = new PTEID_XmlUserRequestedInfo();
			req1.add(XMLUserData.XML_DISTRICT);
			//req1.add(XMLUserData.XML_PHOTO);
			PTEID_CCXML_Doc result1 = this.idCard.getXmlCCDoc(req1);
			System.out.println("resultado = "+ result1.getCCXML());

			
			System.out.println("gerar xml NIC");
			PTEID_XmlUserRequestedInfo req2 = new PTEID_XmlUserRequestedInfo();
			req2.add(XMLUserData.XML_NIC);
			//req1.add(XMLUserData.XML_PHOTO);
			PTEID_CCXML_Doc result2 = this.idCard.getXmlCCDoc(req2);
			System.out.println("resultado = "+ result2.getCCXML());

/*			System.out.println("gerar xml só com foto");
			PTEID_XmlUserRequestedInfo req2 = new PTEID_XmlUserRequestedInfo();
			req2.add(XMLUserData.XML_PHOTO);
			PTEID_CCXML_Doc result2 = this.idCard.getXmlCCDoc(req2);	

			System.out.println("resultado2 = "+ result2.getCCXML());
			
			*/
		} catch (Exception e){
			e.printStackTrace();
		}
		
		
	}




	public static void main(String args[]){
		System.out.println("Testing Java SDK");

		ExampleSDK eSDK = new ExampleSDK(); 

		eSDK.init();
		eSDK.getSmartCardReaders();
		eSDK.InitializeCard();
		
		eSDK.generateXML();
		
		/*

		eSDK.dumpID();

		eSDK.verifyAddressPIN();
		eSDK.dumpAddress();
		eSDK.listPins();

		// Pins Operations
		//eSDK.verifyPins();
		//eSDK.verifySignPIN();

		// Sign Operations  - XADES / XADEST
		//eSDK.verifySignPIN();
		eSDK.verifySignPINNoWindow();
		eSDK.signXades();

		 */
		

	
		
		
		
		
		
		
		
		//eSDK.signXadesT();
		//eSDK.verifySignatureXadesT();

		// Sign Method - used for Authentication Proccess on mw web 
		//eSDK.verifyAuthPINNoWindow();
		//eSDK.signData();
		//eSDK.readNotes();

		// Testing Method "WriteFile" 
		//System.out.println("Writing Notes");
		//eSDK.verifyAuthPINNoWindow();
		//eSDK.writeNotes("My new test notes");


		//test_GetAddr();

		/*
		test_GetCardType();

		test_GetID();


		test_GetPic();

		test_GetCertificates();

		test_Exit();

		Utils.writeToFile();
		 */
	}




}
