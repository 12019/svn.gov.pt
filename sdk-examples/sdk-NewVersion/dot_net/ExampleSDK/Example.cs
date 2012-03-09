using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using pt.portugal.eid;
using System.Runtime.InteropServices;



namespace ExampleSDK
{
    class Example
    {
        
        private PTEID_ReaderSet readerSet = null;
        private PTEID_ReaderContext readerContext = null;
        private PTEID_EIDCard idCard = null;


        
        public void init()
        {
            try
            {
                PTEID_ReaderSet.initSDK();
                readerSet = PTEID_ReaderSet.instance();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }


        private void findSmartCardReaderWithCard(String readerName) {
		    try {
			    PTEID_ReaderContext rContext = readerSet.getReaderByName(readerName);

			    Console.WriteLine("Reader: " + readerName);
			    if (rContext.isCardPresent()) {
				    readerContext = rContext;
			    }
                Console.WriteLine("\tCard present: " + (rContext.isCardPresent() ? "yes" : "no") + "\n");

		    } catch (PTEID_Exception ex) {
                Console.WriteLine(ex.ToString());
		    }
	    }

        public void getSmartCardReaders() {
		    try {
			    long nrReaders = readerSet.readerCount();
                Console.WriteLine("Nr of card readers detected: " + nrReaders);

			    for (uint readerIdx = 0; readerIdx < nrReaders; readerIdx++) {
				    String readerName = this.readerSet.getReaderName(readerIdx);
				    findSmartCardReaderWithCard(readerName);
			    }
		    } catch (PTEID_Exception ex) {
                Console.WriteLine(ex.ToString());
		    }
	    }

        public void dumpID(){
		    try {
			    this.idCard = this.readerContext.getEIDCard();

			    Console.WriteLine("\n\nCitizen identification");
			    Console.WriteLine("--------------------------------------");
			    Console.WriteLine("deliveryEntity              " + this.idCard.getID().getIssuingEntity());
			    Console.WriteLine("country                     " + this.idCard.getID().getCountry());
			    Console.WriteLine("documentType                " + this.idCard.getID().getDocumentType());
			    Console.WriteLine("cardNumber                  " + this.idCard.getID().getDocumentNumber());
			    Console.WriteLine("cardNumberPAN               " + this.idCard.getID().getDocumentPAN());
			    Console.WriteLine("cardVersion                 " + this.idCard.getID().getDocumentVersion());
			    Console.WriteLine("deliveryDate                " + this.idCard.getID().getValidityBeginDate());
			    Console.WriteLine("locale                      " + this.idCard.getID().getLocalofRequest());
			    Console.WriteLine("validityDate                " + this.idCard.getID().getValidityEndDate());
			    Console.WriteLine("name                        " + this.idCard.getID().getSurname());
			    //Console.writeline("firstname                   " + id.getGivenName());
			    Console.WriteLine("sex                         " + this.idCard.getID().getGender());
			    Console.WriteLine("nationality                 " + this.idCard.getID().getNationality());
			    Console.WriteLine("birthDate                   " + this.idCard.getID().getDateOfBirth());
			    Console.WriteLine("height                      " + this.idCard.getID().getHeight());
			    Console.WriteLine("numBI                       " + this.idCard.getID().getCivilianIdNumber());
			    Console.WriteLine("nameFather                  " + this.idCard.getID().getSurnameFather());
			    Console.WriteLine("firstnameFather             " + this.idCard.getID().getGivenNameFather());
			    Console.WriteLine("nameMother                  " + this.idCard.getID().getSurnameMother());
			    Console.WriteLine("firstnameMother             " + this.idCard.getID().getGivenNameMother());
			    Console.WriteLine("numNIF                      " + this.idCard.getID().getTaxNo());
			    Console.WriteLine("numSS                       " + this.idCard.getID().getSocialSecurityNumber());
			    Console.WriteLine("numSNS                      " + this.idCard.getID().getHealthNumber());
			    Console.WriteLine("Accidental indications      " + this.idCard.getID().getAccidentalIndications());
			    Console.WriteLine("mrz1                        " + this.idCard.getID().getMRZ1());
			    Console.WriteLine("mrz2                        " + this.idCard.getID().getMRZ2());
			    Console.WriteLine("mrz3                        " + this.idCard.getID().getMRZ3());
			    Console.WriteLine("--------------------------------------");

		    } catch (PTEID_Exception e) {
                Console.WriteLine(e.ToString());
		    }
	    }


        public void verifyAddressPIN(){
		    PTEID_Pins pins;
		    try {
			    pins = this.idCard.getPins();
			    for (uint i = 0; i < pins.count(); i++) {
				    PTEID_Pin pin = pins.getPinByNumber(i);
// FIX				
                    /*if (pin.getLabel().equalsIgnoreCase("PIN da Morada")) {
					    

                        
                        uint tries_left;
                        if (pin.verifyPin("", ref tries_left, false))
                        {
						    Console.WriteLine("PIN OK!!!!\n");
					    }
				    }*/
			    }
		    } catch (PTEID_Exception e) {
                Console.WriteLine(e.ToString());
		    }
	    }

        public void listPins(){
		    PTEID_Pins pins;
		    try {
			    pins = this.idCard.getPins();
			    for (uint i = 0; i < pins.count(); i++) {
				    PTEID_Pin pin = pins.getPinByNumber(i);
				    Console.WriteLine(pin.getLabel());
			    }
		    } catch (PTEID_Exception e) {
                Console.WriteLine(e.ToString());
		    }
	    }

        private void verifySignPIN(){
		    PTEID_Pins pins;
		    try {
			    pins = this.idCard.getPins();
			    for (uint i = 0; i < pins.count(); i++) {
				    PTEID_Pin pin = pins.getPinByNumber(i);
// FIX
                    /*
                    if (pin.getLabel().equalsIgnoreCase("PIN da Assinatura")) {
					    Console.WriteLine("Entrei aqui - assinatura");
                        uint tries_left;
                        if (pin.verifyPin("", ref tries_left,false)) {
						    Console.WriteLine("PIN OK!!!!\n");
					    }
				    }
                     */
			    }
		    } catch (PTEID_Exception e) {
                Console.WriteLine(e.ToString());
		    }
	    }

        private void verifySignPINNoWindow(){
		bool PIN_validated=false;
		String secret;
		PTEID_Pins pins;
		try {
			pins = this.idCard.getPins();
			for (uint i = 0; i < pins.count(); i++) {
				PTEID_Pin pin = pins.getPinByNumber(i);
	// FIX
          /*      
                if (pin.getLabel().equalsIgnoreCase("PIN da Assinatura")) {
                    uint tries_left;
                    while (!PIN_validated){
						secret=readInput("Insira o PIN de assinatura:");
						if (pin.verifyPin(secret, ref tries_left,false)) {
							PIN_validated=true;
							Console.WriteLine("PIN OK!!!!\n");
						}	
					}
				}
           */
			}
		} catch (PTEID_Exception e) {
            Console.WriteLine(e.ToString());
		}
	}

        private void verifyAuthPINNoWindow(){
		    bool PIN_validated=false;
		    String secret;
		    PTEID_Pins pins;
		    try {
			    pins = this.idCard.getPins();
			    for (uint i = 0; i < pins.count(); i++) {
				    PTEID_Pin pin = pins.getPinByNumber(i);
// FIX
                    /*
                    if (pin.getLabel().substring(0, 11).equalsIgnoreCase("PIN da Aute")) {
                        uint tries_left;
                        while (!PIN_validated){
						    secret=readInput("Insira o PIN de Autenticação:");
                            if (pin.verifyPin(secret, ref tries_left, false))
                            {
							    PIN_validated=true;
							    Console.WriteLine("PIN OK!!!!\n");
						    }	
					    }
				    }
                     */
			    }
		    } catch (PTEID_Exception e) {
                Console.WriteLine(e.ToString());
		    }
	    }

        private void verifyAutenticationPin(){
		    PTEID_Pins pins;
		    try {
			    pins = this.idCard.getPins();
			    for (uint i = 0; i < pins.count(); i++) {
				    PTEID_Pin pin = pins.getPinByNumber(i);

				    //String i = pin.getLabel();

				    Console.WriteLine();
// FIX
                    /*
				    if (pin.getLabel().substring(0, 11).equalsIgnoreCase("PIN da Aute")) {
					    Console.WriteLine("Entrei aqui - autenticacao");
                        uint tries_left;
                        if (pin.verifyPin("", ref tries_left,false)) {
						    Console.WriteLine("PIN OK!!!!\n");
					    }
				    }
                     */
			    }
		    } catch (PTEID_Exception e) {
                Console.WriteLine(e.ToString());
		    }
	    }

        private void verifyPins()
            {
                //verifyAddressPIN();
                verifySignPIN();
                verifyAutenticationPin();
            }

        private void signXades()
            {
		        Console.WriteLine("Here");
		        String[] file_list={"teste","teste2"};

                uint list_size = (uint)file_list.Length;
                this.idCard.SignXades(file_list, list_size, "signature.zip");
	        }

        private void signXadesT()
            {
                String[] file_list = { "teste", "teste2" };
                uint list_size = (uint)file_list.Length;
                idCard.SignXadesT(file_list, list_size, "signature-xades-t.zip");
            }

        private void verifySignature()
	        {
		        String errors = "";
                uint error_size;
// FIX
                /*bool result = PTEID_SigVerifier.VerifySignature("signature3.zip", ref errors, ref error_size);
		        if (!result)
			        Console.WriteLine("Validation failed!");
		        else
			        Console.WriteLine("Validation succeeded!");
                 */ 
	        }

        private void verifySignatureXadesT(){
            String errors = "";
            uint error_size;
  
    // FIX
 /*
            bool result = PTEID_SigVerifier.VerifySignature("signature-xadest-2.zip", errors, error_size);
		    if (!result)
			    Console.WriteLine("Validation failed!");
		    else
			    Console.WriteLine("Validation succeeded!");
  */ 
	    }

        private byte[] getFirst256(byte[] content)
        {
            byte[] new_content;
            new_content = new byte[256];

            for (int i = 0; i < 255; i++)
            {
                new_content[i] = content[i];
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
            char[] sa;
            sa = new char[2];
            sa[0] = 'a';
            sa[1] = '2';

            notes_content = content.ToString();
			//notes_content= new String(getFirst256(content)); // yes, this will remove valid white space in the end...
		} catch (Exception e) {
			Console.WriteLine(e.ToString());
		}
		Console.WriteLine(notes_content);
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





        public void signData()
        {

            String str_to_be_signed;
            PTEID_ByteArray content_to_be_signed;
            PTEID_ByteArray content_signed;

            str_to_be_signed = "String a ser assinada";

            try
            {
                this.idCard = this.readerContext.getEIDCard();
    // TO FIX
                //content_to_be_signed = new PTEID_ByteArray(str_to_be_signed.getBytes(), str_to_be_signed.length());
    //            content_signed = this.idCard.Sign(content_to_be_signed);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        /*
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
        */





    }
}
