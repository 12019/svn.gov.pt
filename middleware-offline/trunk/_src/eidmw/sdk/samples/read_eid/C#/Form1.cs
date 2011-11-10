using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using be.portugal.eid;

namespace read_eid
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnQuit_Click(object sender, EventArgs e)
        {
            this.Close();
            PTEID_ReaderSet.releaseSDK();

            Application.Exit();

        }

        private void btnLoad_Click(object sender, EventArgs e)
        {
            try
            {

                PTEID_ReaderSet ReaderSet;
                ReaderSet = PTEID_ReaderSet.instance();

                PTEID_ReaderContext Reader; 
                Reader = ReaderSet.getReader();

                this.img.Image = null;

                string sText;
                sText = "Reader = " + Reader.getName() + "\r\n\r\n";
                if(Reader.isCardPresent())
                {
                    if(Reader.getCardType() == PTEID_CardType.PTEID_CARDTYPE_EID 
                        || Reader.getCardType() == PTEID_CardType.PTEID_CARDTYPE_FOREIGNER 
                        || Reader.getCardType() == PTEID_CardType.PTEID_CARDTYPE_KIDS)
                    {

                        sText += Load_eid(Reader);
                    }
                    else if (Reader.getCardType() == PTEID_CardType.PTEID_CARDTYPE_SIS)
                    {

                        sText += Load_sis(Reader);
                    }
                    else
                    {
                        sText += "CARD TYPE UNKNOWN";
                    }
                }

                this.txtInfo.Text = sText;

                PTEID_ReaderSet.releaseSDK();
            }

            catch(PTEID_Exception ex)
            {
                PTEID_ReaderSet.releaseSDK();
            }
            catch(Exception ex)
            {
                PTEID_ReaderSet.releaseSDK();
            }

    }

    private string Load_eid(PTEID_ReaderContext Reader)
    {
        string sText;
        PTEID_EIDCard card;
        card = Reader.getEIDCard();
        if(card.isTestCard())
        {
            card.setAllowTestCard(true);
        }

        PTEID_EId doc;
        doc = card.getID();

        sText = "";
        sText += "PERSONAL DATA" + "\r\n";
        sText += "\r\n";
        sText += "First Name = " + doc.getFirstName() + "\r\n";
        sText += "Last Name = " + doc.getSurname() + "\r\n";
        sText += "Gender = " + doc.getGender() + "\r\n";
        sText += "DateOfBirth = " + doc.getDateOfBirth() + "\r\n";
        sText += "LocationOfBirth = " + doc.getLocationOfBirth() + "\r\n";
        sText += "Nobility = " + doc.getNobility() + "\r\n";
        sText += "Nationality = " + doc.getNationality() + "\r\n";
        sText += "NationalNumber = " + doc.getNationalNumber() + "\r\n";
        sText += "SpecialOrganization = " + doc.getSpecialOrganization() + "\r\n";
        sText += "MemberOfFamily = " + doc.getMemberOfFamily() + "\r\n";
        sText += "AddressVersion = " + doc.getAddressVersion() + "\r\n";
        sText += "Street = " + doc.getStreet() + "\r\n";
        sText += "ZipCode = " + doc.getZipCode() + "\r\n";
        sText += "Municipality = " + doc.getMunicipality() + "\r\n";
        sText += "Country = " + doc.getCountry() + "\r\n";
        sText += "SpecialStatus = " + doc.getSpecialStatus() + "\r\n";

        sText += "\r\n";
        sText += "\r\n";

        sText += @"CARD DATA" + "\r\n";
        sText += "\r\n";
        sText += "LogicalNumber = " + doc.getLogicalNumber() + "\r\n";
        sText += "ChipNumber = " + doc.getChipNumber() + "\r\n";
        sText += "ValidityBeginDate = " + doc.getValidityBeginDate() + "\r\n";
        sText += "ValidityEndDate = " + doc.getValidityEndDate() + "\r\n";
        sText += "IssuingMunicipality = " + doc.getIssuingMunicipality() + "\r\n";

        Image photo;
        PTEID_Picture picture;
        picture = card.getPicture();

        byte[] bytearray;
        bytearray = picture.getData().GetBytes();
        
        MemoryStream ms;
        ms = new MemoryStream();
        ms.Write(bytearray, 0, bytearray.Length);

        photo = Image.FromStream(ms, true);
        this.img.Image = photo;

        return sText;

    }

    private string Load_sis(PTEID_ReaderContext Reader)
    {
        string sText;
        PTEID_SISCard card;
        card = Reader.getSISCard();

        PTEID_SisId doc;
        doc = card.getID();

        sText = "";
        sText += "PERSONNAL DATA" + "\r\n";
        sText += "\r\n";
        sText += "Name = " + doc.getName() + "\r\n";
        sText += "Surname = " + doc.getSurname() + "\r\n";
        sText += "Initials = " + doc.getInitials() + "\r\n";
        sText += "Gender = " + doc.getGender() + "\r\n";
        sText += "DateOfBirth = " + doc.getDateOfBirth() + "\r\n";
        sText += "SocialSecurityNumber = " + doc.getSocialSecurityNumber() + "\r\n";

        sText += "\r\n";;
        sText += "\r\n";;

        sText += "CARD DATA" + "\r\n";
        sText += "\r\n";
        sText += "LogicalNumber = " + doc.getLogicalNumber() + "\r\n";
        sText += "DateOfIssue = " + doc.getDateOfIssue() + "\r\n";
        sText += "ValidityBeginDate = " + doc.getValidityBeginDate() + "\r\n";
        sText += "ValidityEndDate = " + doc.getValidityEndDate() + "\r\n";

        return sText;

        }
    }
}