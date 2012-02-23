import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
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
import pt.gov.cartaodecidadao.SWIGTYPE_p_unsigned_long;
import pt.gov.cartaodecidadao.XMLUserData;



public class ExampleSDK {

	PTEID_ReaderSet readerSet = null;
	PTEID_ReaderContext readerContext = null;
	PTEID_EIDCard idCard = null;

	public PTEID_ReaderSet readerSet(){return readerSet;}
	public PTEID_ReaderContext readerContext(){return readerContext;}
	public PTEID_EIDCard idCard(){return idCard;}





	static { 
		try { 
			System.loadLibrary("pteidlibJava_Wrapper"); 
		} catch (UnsatisfiedLinkError e) { 
			System.err.println("Native code library failed to load. \n" + e); 
			System.exit(1); 
		} 
	} 




	private void init() {
		try {
			PTEID_ReaderSet.initSDK();
			readerSet = PTEID_ReaderSet.instance();
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

	private void verifyAddressPIN(){
		PTEID_Pins pins;
		try {
			pins = this.idCard.getPins();
			for (int i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);
				if (pin.getLabel().equalsIgnoreCase("PIN da Morada")) {
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
		System.out.println("Here");
		String[] file_list={"teste","teste2"};
		idCard.SignXades(file_list,file_list.length,"signature2.zip");

	}

	private void verifySignature()
	{
		String errors = new String();  
		PTEID_ulwrapper error_size = new PTEID_ulwrapper(0);
		boolean result = PTEID_SigVerifier.VerifySignature("signature2.zip", errors, error_size);
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






	public void writeNotes(String strNotes) {
		int MAX_NOTES_SIZE=256;
		byte NOTES_PADDING_BYTE = 0;
		String NOTES_FILE_ID = "3f005f00ef07";

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



	public static void main(String args[]){
		System.out.println("Testing Java SDK");

		ExampleSDK eSDK = new ExampleSDK(); 

		eSDK.init();

		eSDK.getSmartCardReaders();

		eSDK.dumpID();

		eSDK.listPins();

		//eSDK.verifyPins();

		//eSDK.verifySignPIN();
		//eSDK.signXades();

		//eSDK.verifySignature();

		eSDK.readNotes();
		
		eSDK.verifyAutenticationPin();
		eSDK.writeNotes("1233");


		/*
		test_GetCardType();

		test_GetID();

		test_GetAddr();

		test_GetPic();

		test_GetCertificates();

		test_Exit();

		Utils.writeToFile();
		 */
	}




}
