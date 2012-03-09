using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ExampleSDK
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            Console.WriteLine("Testing Java SDK");
            

            Example eSDK = new Example(); 
            

		
		    eSDK.init();
             
		    eSDK.getSmartCardReaders();
            
		eSDK.dumpID();
		eSDK.listPins();
            /*
		// Pins Operations
		//eSDK.verifyPins();
		//eSDK.verifySignPIN();
		
		// Sign Operations  - XADES / XADEST
		//eSDK.verifySignPIN();
		eSDK.verifySignPINNoWindow();
		eSDK.signXadesT();
		eSDK.verifySignatureXadesT();

		// Sign Method - used for Authentication Proccess on mw web 
		eSDK.verifyAuthPINNoWindow();
		eSDK.signData();
		//eSDK.readNotes();

		// Testing Method "WriteFile" 
		System.out.println("Writing Notes");
		eSDK.verifyAuthPINNoWindow();
		eSDK.writeNotes("My new test notes");

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
}
