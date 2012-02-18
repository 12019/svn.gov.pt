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
import pt.gov.cartaodecidadao.PTEID_XmlUserRequestedInfo;
import pt.gov.cartaodecidadao.PTEID_ulwrapper;
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
					if (pin.verifyPin("", wrap,true)) {
						System.out.println("PIN OK!!!!\n");
					}
				}
			}
		} catch (PTEID_Exception e) {
			e.printStackTrace();
		}

	}

	private void verifyPins(){

		verifyAddressPIN();




	}




	public static void main(String args[]){
		System.out.println("Testing Java SDK");

		ExampleSDK eSDK = new ExampleSDK(); 


		eSDK.init();

		eSDK.getSmartCardReaders();

		eSDK.dumpID();

		eSDK.verifyPins();


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
