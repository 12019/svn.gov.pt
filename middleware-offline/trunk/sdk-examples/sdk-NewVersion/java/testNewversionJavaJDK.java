/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

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

/**
 * how to execute: java -Djava.library.path=/usr/local/lib/ -jar "PTEID Sample.jar"
 * @author ruim
 */
public class testNewversionJavaJDK {

    PTEID_ReaderSet readerSet = null;
    PTEID_ReaderContext readerContext = null;
    PTEID_EIDCard idCard = null;

    private void getSmartCardReaders() {
        try {
            long nrReaders = readerSet.readerCount();
            System.out.println("Nr of card readers detected: " + nrReaders);

            for (int readerIdx = 0; readerIdx < nrReaders; readerIdx++) {
                String readerName = readerSet.getReaderName(readerIdx);
                findSmartCardReaderWithCard(readerName);
            }
        } catch (PTEID_Exception ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
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
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void getIDCard() {
        try {
            idCard = readerContext.getEIDCard();
        } catch (PTEID_Exception ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    private String generateXML(){
        String s = null;
        try {
            PTEID_XmlUserRequestedInfo info = new PTEID_XmlUserRequestedInfo();
            /*
            info.add(XMLUserData.XML_NAME);
            info.add(XMLUserData.XML_MRZ1);
            info.add(XMLUserData.XML_MRZ2);
            info.add(XMLUserData.XML_MRZ3);*/
            PTEID_Pins pins = idCard.getPins();
            for (int i = 0; i < pins.count(); i++) {
                PTEID_Pin pin = pins.getPinByNumber(i);
                if (pin.getLabel().equalsIgnoreCase("PIN da Morada")) {
                    PTEID_ulwrapper wrap = new PTEID_ulwrapper(-1);
                    if (pin.verifyPin("", wrap)) {
                        System.out.println("PIN OK!!!!\n");
                    }
                }
            }
            PTEID_CCXML_Doc ccxml = idCard.getXmlCCDoc(info);
            s = ccxml.getCCXML();
        } catch (PTEID_Exception ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        }
        return s;
    }

    private void printCitizenID(PTEID_EId id) {
        try {
            System.out.println("\n\nCitizen identification");
            System.out.println("--------------------------------------");
            System.out.println("deliveryEntity              " + id.getIssuingEntity());
            System.out.println("country                     " + id.getCountry());
            System.out.println("documentType                " + id.getDocumentType());
            System.out.println("cardNumber                  " + id.getDocumentNumber());
            System.out.println("cardNumberPAN               " + id.getDocumentPAN());
            System.out.println("cardVersion                 " + id.getDocumentVersion());
            System.out.println("deliveryDate                " + id.getValidityBeginDate());
            System.out.println("locale                      " + id.getLocalofRequest());
            System.out.println("validityDate                " + id.getValidityEndDate());
            System.out.println("name                        " + id.getSurname());
            //System.out.println("firstname                   " + id.getGivenName());
            System.out.println("sex                         " + id.getGender());
            System.out.println("nationality                 " + id.getNationality());
            System.out.println("birthDate                   " + id.getDateOfBirth());
            System.out.println("height                      " + id.getHeight());
            System.out.println("numBI                       " + id.getCivilianIdNumber());
            System.out.println("nameFather                  " + id.getSurnameFather());
            System.out.println("firstnameFather             " + id.getGivenNameFather());
            System.out.println("nameMother                  " + id.getSurnameMother());
            System.out.println("firstnameMother             " + id.getGivenNameMother());
            System.out.println("numNIF                      " + id.getTaxNo());
            System.out.println("numSS                       " + id.getSocialSecurityNumber());
            System.out.println("numSNS                      " + id.getHealthNumber());
            System.out.println("Accidental indications      " + id.getAccidentalIndications());
            System.out.println("mrz1                        " + id.getMRZ1());
            System.out.println("mrz2                        " + id.getMRZ2());
            System.out.println("mrz3                        " + id.getMRZ3());
            System.out.println("--------------------------------------");
        } catch (PTEID_Exception ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    private void printCitizenPersonalNotes(PTEID_EId id){
        try {
            System.out.println("\n\nCitizen personal notes  (1000 char max)");
            System.out.println("--------------------------------------");
            System.out.println(id.getPersoData());
            System.out.println("--------------------------------------");
        } catch (PTEID_Exception ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    private void saveCitizenPic(PTEID_ByteArray pic, File file){
        FileOutputStream foutput = null;
        DataOutputStream doutput = null;
        byte[] picData;
        
        try {
            foutput = new FileOutputStream(file);
            doutput = new DataOutputStream(foutput);
            
            picData = pic.GetBytes();
            doutput.write(picData, 0, picData.length);
            doutput.flush();
            doutput.close();
            foutput.close();
        } catch (IOException ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                foutput.close();
            } catch (IOException ex) {
                Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    private void saveXml(String xml, File file) {
        try {
            FileWriter outFile = new FileWriter(file);
            PrintWriter out = new PrintWriter(outFile);

            out.print(xml);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    
    private void init() {
        try {
            PTEID_ReaderSet.initSDK();
            readerSet = PTEID_ReaderSet.instance();
        } catch (PTEID_Exception ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    
    private void release() {
        try {
            PTEID_ReaderSet.releaseSDK();
        } catch (PTEID_Exception ex) {
            Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    
    public void start() {
       try {         
            init();
            
            getSmartCardReaders();
            /*
	    idCard = readerContext.getEIDCard();
            
            printCitizenID(idCard.getID());
            
            saveCitizenPic(idCard.getID().getPhoto(),new File(idCard.getID().getDocumentPAN()+".png"));
            
            printCitizenPersonalNotes(idCard.getID());
            
            System.out.println("Saving xml...");
            saveXml(generateXML(), new File(idCard.getID().getDocumentPAN()+".xml"));
            */
            release();
        } catch (Exception ex) {	
	    //Logger.getLogger(testNewversionJavaJDK.class.getName()).log(Level.SEVERE, null, ex);
            release();
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new testNewversionJavaJDK().start();
    }
}
