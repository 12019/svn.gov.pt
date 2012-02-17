using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using eidpt;

namespace OfficialSDK
{
    class TestsSDK
    {


        private void test_initializeSDK(){
            Console.WriteLine("Initializing SDK method");
            try
            {
                Pteid.Init(null);
                Pteid.SetSODChecking(0);
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception on initializeSDK method");
            }
        }


        public void test_GetCardType(){
            String methodName = "GetCardType";
            PteidCardType cardtype;

            Utils.writeTestedMethod(methodName);
            try
            {
                cardtype = Pteid.GetCardType();                
                Utils.writeReturnValues(methodName, cardtype.ToString());
            }
            catch (PteidException e)
            {
                Console.WriteLine("Exception on test_GetCardType method");
                //e.printStackTrace();
                Utils.writeException(e);
            }
        }

        public void dumpID(PteidId idData)
        {
            Utils.writeLog("idData.birthDate " + idData.birthDate + "\n");
            Utils.writeLog("idData.cardNumber " + idData.cardNumber + "\n");
            Utils.writeLog("idData.cardNumberPAN " + idData.cardNumberPAN + "\n");
            Utils.writeLog("idData.cardVersion " + idData.cardVersion + "\n");
            Utils.writeLog("idData.country " + idData.country + "\n");
            Utils.writeLog("idData.deliveryDate " + idData.deliveryDate + "\n");
            Utils.writeLog("idData.deliveryEntity " + idData.deliveryEntity + "\n");
            Utils.writeLog("idData.documentType " + idData.documentType + "\n");
            Utils.writeLog("idData.firstname " + idData.firstname + "\n");
            Utils.writeLog("idData.firstnameFather " + idData.firstnameFather + "\n");
            Utils.writeLog("idData.firstnameMother " + idData.firstnameMother + "\n");
            Utils.writeLog("idData.height " + idData.height + "\n");
            Utils.writeLog("idData.locale " + idData.locale + "\n");
            Utils.writeLog("idData.mrz1 " + idData.mrz1 + "\n");
            Utils.writeLog("idData.mrz2 " + idData.mrz2 + "\n");
            Utils.writeLog("idData.mrz3 " + idData.mrz3 + "\n");
            Utils.writeLog("idData.name " + idData.name + "\n");
            Utils.writeLog("idData.nameFather " + idData.nameFather + "\n");
            Utils.writeLog("idData.nameMother " + idData.nameMother + "\n");
            Utils.writeLog("idData.nationality " + idData.nationality + "\n");
            Utils.writeLog("idData.notes " + idData.notes + "\n");
            Utils.writeLog("idData.numBI " + idData.numBI + "\n");
            Utils.writeLog("idData.numNIF " + idData.numNIF + "\n");
            Utils.writeLog("idData.numSNS " + idData.numSNS + "\n");
            Utils.writeLog("idData.numSS " + idData.numSS + "\n");
            Utils.writeLog("idData.sex " + idData.sex + "\n");
            Utils.writeLog("idData.validityDate " + idData.validityDate + "\n");
            Utils.writeLog("idData.version " + idData.version + "\n");
        }


        public void test_GetID()
        {
            String methodName = "GetID";
            PteidId idData;
            
            Utils.writeTestedMethod(methodName);
            try
            {
                idData = Pteid.GetID();
                dumpID(idData);
                Utils.writeReturnValues(methodName, "Returns PTEID_ID Object");
            }
            catch (PteidException e)
            {
                Utils.writeException(e);
            }
        }

        public void dumpAddr(PteidAddr addrData)
        {
            Utils.writeLog("addrData.addressF " + addrData.addressF + "\n");
            Utils.writeLog("addrData.addrType " + addrData.addrType + "\n");
            Utils.writeLog("addrData.building " + addrData.building + "\n");
            Utils.writeLog("addrData.buildingAbbr " + addrData.buildingAbbr + "\n");
            Utils.writeLog("addrData.cityF " + addrData.cityF + "\n");
            Utils.writeLog("addrData.country " + addrData.country + "\n");
            Utils.writeLog("addrData.countryDescF " + addrData.countryDescF + "\n");
            Utils.writeLog("addrData.cp3 " + addrData.cp3 + "\n");
            Utils.writeLog("addrData.cp4 " + addrData.cp4 + "\n");
            Utils.writeLog("addrData.district " + addrData.district + "\n");
            Utils.writeLog("addrData.districtDesc " + addrData.districtDesc + "\n");
            Utils.writeLog("addrData.door " + addrData.door + "\n");
            Utils.writeLog("addrData.floor " + addrData.floor + "\n");
            Utils.writeLog("addrData.freguesia " + addrData.freguesia + "\n");
            Utils.writeLog("addrData.freguesiaDesc " + addrData.freguesiaDesc + "\n");
            Utils.writeLog("addrData.locality " + addrData.locality + "\n");
            Utils.writeLog("addrData.localityF " + addrData.localityF + "\n");
            Utils.writeLog("addrData.municipality " + addrData.municipality + "\n");
            Utils.writeLog("addrData.municipalityDesc " + addrData.municipalityDesc + "\n");
            Utils.writeLog("addrData.numMor " + addrData.numMor + "\n");
            Utils.writeLog("addrData.numMorF " + addrData.numMorF + "\n");
            Utils.writeLog("addrData.place " + addrData.place + "\n");
            Utils.writeLog("addrData.postal " + addrData.postal + "\n");
            Utils.writeLog("addrData.postalF " + addrData.postalF + "\n");
            Utils.writeLog("addrData.regioF " + addrData.regioF + "\n");
            Utils.writeLog("addrData.side " + addrData.side + "\n");
            Utils.writeLog("addrData.street " + addrData.street + "\n");
            Utils.writeLog("addrData.streettype " + addrData.streettype + "\n");
            Utils.writeLog("addrData.streettypeAbbr " + addrData.streettypeAbbr + "\n");
            Utils.writeLog("addrData.version " + addrData.version + "\n");
        }


        public void test_GetAddr()
        {
            String methodName = "GetAddr";
            PteidAddr idAddr;

            Utils.writeTestedMethod(methodName);
            try
            {
                idAddr = Pteid.GetAddr();
                dumpAddr(idAddr);
                Utils.writeReturnValues(methodName, "Returns PTEID_ADDR Object");
            }
            catch (PteidException e)
            {
                Console.WriteLine("Entrei na excepção");
                Utils.writeException(e);
            }
        }


        public void dumpCerts(PteidCertif[] certs)
        {
            for (int i = 0; i < certs.Length; i++)
            {
                Utils.writeLog("Dumping Certificate " + i + ":\n");
                Utils.writeLog("cert.certifLabel " + certs[i].certifLabel + "\n");
                Utils.writeLog("cert.certif " + certs[i].certif.ToString() + "\n");
            }
        }


        public void test_GetCertificates()
        {
            String methodName = "GetCertificates";
            PteidCertif[] certs;

            Utils.writeTestedMethod(methodName);
            try
            {
                certs = Pteid.GetCertificates();
                dumpCerts(certs);
                Utils.writeReturnValues(methodName, "Returns PteidCertif[] Array");
            }
            catch (PteidException e)
            {
                Utils.writeException(e);
            }
        }



        public static void test_Exit()
        {
            String methodName = "Exit";

            Utils.writeTestedMethod(methodName);
            try
            {
                Pteid.Exit(0);
                Utils.writeReturnValues(methodName, "N/A: void method");
            }
            catch (PteidException e)
            {
                Utils.writeException(e);
            }
        }


        public void runTests()
        {
            test_initializeSDK();

            test_GetCardType();

            test_GetID();

            test_GetAddr();

            //test_GetPic();

            test_GetCertificates();

            test_Exit();

            Utils.writeToFile();
        }
    }
}
