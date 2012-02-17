using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using eidpt;
using System.IO;
using OfficialSDK;

namespace Trynight
{
    public partial class Form1 : Form
    {
        public class CardData
        {
            public PteidId IdInformation { get; set;}
            public Bitmap Image { get; set; }

        }


        public CardData getCardData()
        {
            CardData result = null;
            try 
            {
                Pteid.Init(null);
                Pteid.SetSODChecking(0);
                PteidId id = Pteid.GetID();
                if (id == null){
                    return null;
                }
                
                //File.WriteAllBytes("C:\\Users\\Teste\\Fotos1.JP2", Pteid.GetPic().picture);
                //FIBITMAP bit = FreeImage.LoadEx ("C:\\Users\\Teste\\Fotos1.JP2");
               // Bitmap bmp = FreeImage.GetBitmap(bit);
               // FreeImage.UnloadEx(ref bit);
                
                 result = new CardData {IdInformation = id};
                 Pteid.Exit(2);
            }
            catch(Exception e)
            {
            }
            return result;
        }




        
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            CardData i = getCardData();

            textBox1.Text = i.IdInformation.birthDate.ToString();
            textBox2.Text = i.IdInformation.cardNumber.ToString();
            textBox3.Text = i.IdInformation.cardNumberPAN.ToString();
            textBox4.Text = i.IdInformation.cardVersion.ToString();
            textBox5.Text = i.IdInformation.country.ToString();
            textBox6.Text = i.IdInformation.deliveryDate.ToString();
            textBox7.Text = i.IdInformation.deliveryEntity.ToString();
            textBox8.Text = i.IdInformation.documentType.ToString();
            textBox9.Text = i.IdInformation.firstname.ToString();
            textBox10.Text = i.IdInformation.firstnameFather.ToString();
            textBox11.Text = i.IdInformation.firstnameMother.ToString();
            textBox12.Text = i.IdInformation.height.ToString();
            textBox13.Text = i.IdInformation.locale.ToString();
            textBox14.Text = i.IdInformation.mrz1.ToString();
            textBox15.Text = i.IdInformation.mrz2.ToString();
            textBox16.Text = i.IdInformation.mrz3.ToString();
            textBox17.Text = i.IdInformation.name.ToString();
            textBox18.Text = i.IdInformation.nameFather.ToString();
            textBox19.Text = i.IdInformation.nameMother.ToString();
            textBox20.Text = i.IdInformation.nationality.ToString();
            textBox21.Text = i.IdInformation.notes.ToString();
            textBox22.Text = i.IdInformation.numBI.ToString();
            textBox23.Text = i.IdInformation.numNIF.ToString();
            textBox24.Text = i.IdInformation.numSNS.ToString();
            textBox25.Text = i.IdInformation.numSS.ToString();
            textBox26.Text = i.IdInformation.sex.ToString();
            textBox27.Text = i.IdInformation.validityDate.ToString();
            textBox28.Text = i.IdInformation.version.ToString();

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label16_Click(object sender, EventArgs e)
        {

        }

        private void btnRunTests_Click(object sender, EventArgs e)
        {
            TestsSDK ts = new TestsSDK();


            ts.runTests();

            

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

      
    }




}
