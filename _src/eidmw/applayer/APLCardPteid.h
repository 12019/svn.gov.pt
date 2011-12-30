/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2008-2009 FedICT.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version
 * 3.0 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, see
 * http://www.gnu.org/licenses/.

**************************************************************************** */
#pragma once

#ifndef __APLCARDEID_H__
#define __APLCARDEID_H__

#include <string>
#include <set>
#include "Export.h"
#include "APLReader.h"
#include "APLCertif.h"
#include "APLCard.h"
#include "APLDoc.h"
#include "ByteArray.h"
#include "../common/xmlUserDataEnum.h"

namespace eIDMW
{

class APL_Certifs;
class APL_ReaderContext;
class APL_EidFile_Trace;
class APL_EidFile_ID;
class APL_EidFile_IDSign;
class APL_EidFile_Address;
class APL_EidFile_AddressSign;
class APL_EidFile_Sod;
class APL_EidFile_PersoData;
class APL_EidFile_TokenInfo;
class APL_CardFile_Certificate;

class APL_EIdFullDoc;
class APL_CCXML_Doc;
class APL_DocEId;
class APL_AddrEId;
class APL_SodEid;
class APL_DocVersionInfo;

enum APL_AccessWarningLevel
{
	APL_ACCESSWARNINGLEVEL_BEING_ASKED=-2,
	APL_ACCESSWARNINGLEVEL_REFUSED=-1,
	APL_ACCESSWARNINGLEVEL_TO_ASK=0,
	APL_ACCESSWARNINGLEVEL_ACCEPTED=1,
};

class APL_CCXML_Doc;
class APL_XmlUserRequestedInfo;
/******************************************************************************//**
  * Class that represent a PTEID card
  *
  * To get APL_EIDCard object, we have to ask it from APL_ReaderContext 
  *********************************************************************************/
class APL_EIDCard : public APL_SmartCard
{
public:
	/**
	  * Destructor
	  *
	  * Destroy all the pointer create (files, docs,...)
	  */
	EIDMW_APL_API virtual ~APL_EIDCard();

	/**
	  * Return the type of the card (PTEID_CARDTYPE_EID)
	  */
	EIDMW_APL_API virtual APL_CardType getType() const;

	/**
	  * Return true this is a test card.
	  * This is a test card if one of the certificate is a test one
	  */
	EIDMW_APL_API virtual bool isTestCard();

	/**
	  * Read a file on the card 
	  *
	  * @param csPath is the path of the file to be read
	  * @param bytearray will contain the content of the file 
	  */
 	EIDMW_APL_API virtual unsigned long readFile(const char *csPath, CByteArray &oData, unsigned long  ulOffset=0, unsigned long  ulMaxLength=0);

	/**
	  * Return the number of certificate on the card
	  */
	EIDMW_APL_API virtual unsigned long certificateCount();

	/** 
	 * Return a document from the card
	 */
	EIDMW_APL_API virtual APL_XMLDoc& getDocument(APL_DocumentType type);

	/**
	  * Return a pointer to the document FULL
	  */
	EIDMW_APL_API APL_EIdFullDoc& getFullDoc();

	EIDMW_APL_API APL_CCXML_Doc& getXmlCCDoc(APL_XmlUserRequestedInfo& userRequestedInfo);


	/**
	  * Return a pointer to the document Address
	  *
	  * It is based upon the Address file
	  */
	EIDMW_APL_API APL_AddrEId& getAddr();

	/**
	  * Return a pointer to the document ID
	  *
	  * It is based upon the ID file
	  */
	EIDMW_APL_API APL_DocEId& getID();

	/**
	  * Return a pointer to the document SOD
	  *
	  * It is based upon the SOD file (and hash in ID file)
	  */
	EIDMW_APL_API APL_SodEid& getSod();

	/**
	  * Return a pointer to the document Info
	  *
	  * It is based upon the APL_CardFile_Info and APL_CardFile_TokenInfo file
	  */
	EIDMW_APL_API APL_DocVersionInfo& getDocInfo();	

	EIDMW_APL_API const CByteArray &getCardInfoSignature();			/**< Return the signature of the card info */

	EIDMW_APL_API static bool isApplicationAllowed();					/**< Return true if the user allow the application */

 	/** 
	 * Return rawdata from the card
	 */
	EIDMW_APL_API virtual const CByteArray& getRawData(APL_RawDataType type);

 	EIDMW_APL_API const CByteArray& getRawData_Id();			/**< Get the id RawData */
	EIDMW_APL_API const CByteArray& getRawData_IdSig();			/**< Get the IdSig RawData */
	EIDMW_APL_API const CByteArray& getRawData_Trace();			/**< Get the IdSig RawData */
 	EIDMW_APL_API const CByteArray& getRawData_Addr();			/**< Get the Addr RawData */
 	EIDMW_APL_API const CByteArray& getRawData_AddrSig();		/**< Get the AddrSig RawData */
 	EIDMW_APL_API const CByteArray& getRawData_Sod();			/**< Get the Sod RawData */
 	EIDMW_APL_API const CByteArray& getRawData_CardInfo();		/**< Get the Card Info RawData */
 	EIDMW_APL_API const CByteArray& getRawData_TokenInfo();		/**< Get the Token Info RawData */
 	EIDMW_APL_API const CByteArray& getRawData_Challenge();		/**< Get the challenge RawData */
 	EIDMW_APL_API const CByteArray& getRawData_Response();		/**< Get the response RawData */
 	EIDMW_APL_API const CByteArray& getRawData_PersoData();		/**< Get the response RawData */

 	APL_EidFile_Trace *getFileTrace();					/**< Return a pointer to the file Trace (NOT EXPORTED) */
	APL_EidFile_ID *getFileID();					/**< Return a pointer to the file ID (NOT EXPORTED) */
	APL_EidFile_IDSign *getFileIDSign();			/**< Return a pointer to the file ID signature (NOT EXPORTED) */
	APL_EidFile_Address *getFileAddress();			/**< Return a pointer to the file Address (NOT EXPORTED) */
	APL_EidFile_AddressSign *getFileAddressSign();	/**< Return a pointer to the file Address signature (NOT EXPORTED) */
	APL_EidFile_Sod *getFileSod();				/**< Return a pointer to the file Photo (NOT EXPORTED) */
	APL_EidFile_PersoData *getFilePersoData();				/**< Return a pointer to the file PersoData (NOT EXPORTED) */
	APL_EidFile_TokenInfo *getFileTokenInfo();		/**< Return a pointer to the file Token Info (NOT EXPORTED) */

	static void askWarningLevel();
	static void setWarningLevel(APL_AccessWarningLevel lWarningLevel);
	static APL_AccessWarningLevel getWarningLevel();

protected:
	/**
	  * Constructor
	  *		Used only in APL_ReaderContext::connectCard
	  */    
	APL_EIDCard(APL_ReaderContext *reader);

	virtual bool initVirtualReader();
	virtual bool isCardForbidden();

	/**
	  * Read a file from a virtual reader
	  *
	  * @param fileID : is the name/path of the file
	  * @param in : will return the content of the file
	  */
	static unsigned long readVirtualFileRAW(APL_SuperParser *parser,const char *fileID, CByteArray &in,unsigned long idx);
	static unsigned long readVirtualFileTLV(APL_SuperParser *parser,const char *fileID, CByteArray &in,unsigned long idx);
	static unsigned long readVirtualFileCSV(APL_SuperParser *parser,const char *fileID, CByteArray &in,unsigned long idx);
	static unsigned long readVirtualFileXML(APL_SuperParser *parser,const char *fileID, CByteArray &in,unsigned long idx);

private:
	APL_EIDCard(const APL_EIDCard& card);				/**< Copy not allowed - not implemented */
	APL_EIDCard &operator= (const APL_EIDCard& card);	/**< Copy not allowed - not implemented */

	CByteArray *m_cardinfosign;

	APL_EIdFullDoc *m_docfull;							/**< Pointer to the document FULL */
	APL_CCXML_Doc *m_CCcustomDoc;						/**< Pointer to the custom document */
	APL_DocEId *m_docid;								/**< Pointer to the document ID */
	APL_AddrEId *m_address;								/**< Pointer to the document Address */
	APL_SodEid *m_sod;								/**< Pointer to the document sod */
	APL_DocVersionInfo *m_docinfo;						/**< Pointer to the document Info */

	APL_EidFile_Trace *m_FileTrace;						/**< Pointer to the file Trace */
	APL_EidFile_ID *m_FileID;							/**< Pointer to the file ID */
	APL_EidFile_IDSign *m_FileIDSign;					/**< Pointer to the file ID signature */
	APL_EidFile_Address *m_FileAddress;					/**< Pointer to the file Address */
	APL_EidFile_AddressSign *m_FileAddressSign;			/**< Pointer to the file Address signature */
	APL_EidFile_Sod *m_FileSod;							/**< Pointer to the file Sod */
	APL_EidFile_TokenInfo *m_FileTokenInfo;				/**< Pointer to the file Token Info */
	APL_EidFile_PersoData *m_FilePersoData;				/**< Pointer to the file Perso Data */

	APL_CardFile_Certificate *m_fileCertAuthentication;
	APL_CardFile_Certificate *m_fileCertSignature;
	APL_CardFile_Certificate *m_fileCertCA;
	APL_CardFile_Certificate *m_fileCertRoot;
	APL_CardFile_Certificate *m_fileCertRootAuth;
	APL_CardFile_Certificate *m_fileCertRootSign;

	static APL_AccessWarningLevel m_lWarningLevel;

friend bool APL_ReaderContext::connectCard();	/**< This method must access protected constructor */
};

/******************************************************************************//**
  * Class that represent a PTEID Kids card
  *
  * To get APL_KidsCard object, we have to ask it from APL_ReaderContext 
  *********************************************************************************/
class APL_KidsCard : public APL_EIDCard
{
public:
	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_KidsCard();

	/**
	  * Return the type of the card (PTEID_CARDTYPE_KIDS)
	  */
	EIDMW_APL_API virtual APL_CardType getType() const;

protected:
	/**
	  * Constructor
	  *		Used only in APL_ReaderContext::connectCard
	  */    
	APL_KidsCard(APL_ReaderContext *reader);

private:
	APL_KidsCard(const APL_KidsCard& card);				/**< Copy not allowed - not implemented */
	APL_KidsCard &operator= (const APL_KidsCard& card);	/**< Copy not allowed - not implemented */

friend bool APL_ReaderContext::connectCard();	/**< This method must access protected constructor */
};

/******************************************************************************//**
  * Class that represent a PTEID Foreigner card (
  *
  * To get APL_ForeignerCard object, we have to ask it from APL_ReaderContext 
  *********************************************************************************/
class APL_ForeignerCard : public APL_EIDCard
{
public:
	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_ForeignerCard();

	/**
	  * Return the type of the card (PTEID_CARDTYPE_FOREIGNER)
	  */
	EIDMW_APL_API virtual APL_CardType getType() const;

protected:
	/**
	  * Constructor
	  *		Used only in APL_ReaderContext::connectCard
	  */    
	APL_ForeignerCard(APL_ReaderContext *reader);

private:
	APL_ForeignerCard(const APL_ForeignerCard& card);				/**< Copy not allowed - not implemented */
	APL_ForeignerCard &operator= (const APL_ForeignerCard& card);	/**< Copy not allowed - not implemented */

friend bool APL_ReaderContext::connectCard();	/**< This method must access protected constructor */
};

/******************************************************************************//**
  * Class that represent the FULL document on a PTEID card
  * To get APL_DocEIdFull object, we have to ask it from APL_EIDCard 
  *********************************************************************************/
class APL_EIdFullDoc : public APL_XMLDoc
{
public:
	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_EIdFullDoc();

	EIDMW_APL_API virtual bool isAllowed();							/**< The document is allowed*/

	EIDMW_APL_API virtual CByteArray getXML(bool bNoHeader=false);	/**< Build the XML document */
	EIDMW_APL_API virtual CByteArray getCSV();						/**< Build the CSV document */
	EIDMW_APL_API virtual CByteArray getTLV();						/**< Build the TLV document */

protected:
	/**
	  * Constructor
	  *		Used only in APL_EIDCard::getDocFull()
	  */    
	APL_EIdFullDoc(APL_EIDCard *card);

private:
	APL_EIdFullDoc(const APL_EIdFullDoc& doc);				/**< Copy not allowed - not implemented */
	APL_EIdFullDoc &operator= (const APL_EIdFullDoc& doc);	/**< Copy not allowed - not implemented */

	APL_EIDCard *m_card;							/**< Pointer to the card that construct this object*/

friend APL_EIdFullDoc& APL_EIDCard::getFullDoc();	/**< This method must access protected constructor */
};

class APL_XmlUserRequestedInfo;
/******************************************************************************//**
  * Class that represent the custom XML document on a PTEID card as requested
  * To get APL_CCXML_Doc object, we have to ask it from APL_EIDCard
  *********************************************************************************/
class APL_CCXML_Doc : public APL_XMLDoc
{
public:
	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_CCXML_Doc();

	EIDMW_APL_API virtual bool isAllowed();							/**< The document is allowed*/

	EIDMW_APL_API virtual CByteArray getXML(bool bNoHeader=false);	/**< Build the XML document */


protected:
	/**
	  * Constructor
	  *		Used only in APL_EIDCard::getXmlCCDoc()
	  */
	APL_CCXML_Doc(APL_EIDCard *card, APL_XmlUserRequestedInfo&  xmlUserRequestedInfo);

private:
	APL_CCXML_Doc(const APL_CCXML_Doc& doc);				/**< Copy not allowed - not implemented */
	APL_CCXML_Doc &operator= (const APL_CCXML_Doc& doc);	/**< Copy not allowed - not implemented */
	APL_EIDCard *m_card;									/**< Pointer to the card that construct this object*/
	APL_XmlUserRequestedInfo *m_xmlUserRequestedInfo;		/**< Pointer to the data parameters to generate the xml*/
	CByteArray getCSV();									/**< Build the CSV document - not implemented*/
	CByteArray getTLV();									/**< Build the TLV document - not implemented*/
friend APL_CCXML_Doc& APL_EIDCard::getXmlCCDoc(APL_XmlUserRequestedInfo& userRequestedInfo);	/**< This method must access protected constructor */
};


class APL_XmlUserRequestedInfo
{
public:
	EIDMW_APL_API APL_XmlUserRequestedInfo();
	EIDMW_APL_API ~APL_XmlUserRequestedInfo();
	EIDMW_APL_API void add(XMLUserData xmlUData);

protected:
	bool contains(XMLUserData xmlUData);
	void remove(XMLUserData xmlUData);
	bool checkAndRemove(XMLUserData xmlUData);
	bool isEmpty();
friend CByteArray APL_CCXML_Doc::getXML(bool bNoHeader);

private:
	std::set<enum XMLUserData> *xmlSet;
};


/******************************************************************************//**
  * Class that represent the document ID on a PTEID card
  *
  * This class show id informations to APL_EIDCard user
  * (These informations comes from the ID file)
  *
  * To get APL_DocEId object, we have to ask it from APL_EIDCard 
  *********************************************************************************/
class APL_DocEId : public APL_XMLDoc
{
public:
	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_DocEId();

	EIDMW_APL_API virtual bool isAllowed();							/**< The document is allowed*/

	EIDMW_APL_API virtual CByteArray getXML(bool bNoHeader=false);	/**< Build the XML document */
	EIDMW_APL_API virtual CByteArray getCSV();						/**< Build the CSV document */
	EIDMW_APL_API virtual CByteArray getTLV();						/**< Build the TLV document */

	EIDMW_APL_API const char *getDocumentVersion();		/**< Return field DocumentVersion from the ID file */
	EIDMW_APL_API const char *getDocumentType();		/**< Return field DocumentType from the ID file */
	EIDMW_APL_API const char *getCountry();				/**< Return field Country from the ID file */
	EIDMW_APL_API const char *getFirstName1();			/**< Return field FirstName1 from the ID file */
	EIDMW_APL_API const char *getSurname();				/**< Return field Surname from the ID file */
	EIDMW_APL_API const char *getGender();				/**< Return field Gender from the ID file */
	EIDMW_APL_API const char *getDateOfBirth();			/**< Return field DateOfBirth from the ID file */
	EIDMW_APL_API const char *getLocationOfBirth();		/**< Return field LocationOfBirth from the ID file */
	EIDMW_APL_API const char *getNationality();			/**< Return field Nationality from the ID file */
	EIDMW_APL_API const char *getDuplicata();			/**< Return field Duplicata from the ID file */
	EIDMW_APL_API const char *getSpecialOrganization();	/**< Return field SpecialOrganization from the ID file */
	EIDMW_APL_API const char *getMemberOfFamily();		/**< Return field MemberOfFamily from the ID file */
	EIDMW_APL_API const char *getLogicalNumber();		/**< Return field LogicalNumber from the ID file */
	EIDMW_APL_API const char *getDocumentPAN();			/**< Return field Document PAN from the ID file */
	EIDMW_APL_API const char *getValidityBeginDate();	/**< Return field ValidityBeginDate from the ID file */
	EIDMW_APL_API const char *getValidityEndDate();		/**< Return field ValidityEndDate from the ID file */
	EIDMW_APL_API const char *getLocalofRequest();		/**< Return field LocalofRequest from the ID file */
	EIDMW_APL_API const char *getSpecialStatus();		/**< Return field SpecialStatus from the ID file */
	/*New status for PTeid-ng */
	EIDMW_APL_API const char *getHeight();				/**< Return field Height */
	EIDMW_APL_API const char *getDocumentNumber();		/**< Return field DocumentNumber */
	EIDMW_APL_API const char *getCivilianIdNumber();	/**< Return field CivilianIdNumber */
	EIDMW_APL_API const char *getTaxNo();				/**< Return field TaxNo */
	EIDMW_APL_API const char *getSocialSecurityNumber();/**< Return field SocialSecurityNumber */
	EIDMW_APL_API const char *getHealthNumber();		/**< Return field HealthNumber */
	EIDMW_APL_API const char *getIssuingEntity();	 	/**< Return field IssuingEntity */
	EIDMW_APL_API const char *getGivenNameFather();		/**< Return field GivenNameFather */
	EIDMW_APL_API const char *getSurnameFather();		/**< Return field SurnameFather */
	EIDMW_APL_API const char *getGivenNameMother();		/**< Return field GivenNameMother */
	EIDMW_APL_API const char *getSurnameMother();		/**< Return field SurnameMother */
	EIDMW_APL_API const char *getParents();				/**< Return field Parents */
	EIDMW_APL_API const char *getPhoto();				/**< Return field Photo */
	EIDMW_APL_API const char *getMRZ1();				/**< Return field MRZ block 1 */
	EIDMW_APL_API const char *getMRZ2();				/**< Return field MRZ block 2 */
	EIDMW_APL_API const char *getMRZ3();				/**< Return field MRZ block 3 */
	EIDMW_APL_API const char *getAccidentalIndications();	/**< Return field AccidentalIndications */
	EIDMW_APL_API const char *getValidation();		/**< Return field Validation from the Trace file */

	EIDMW_APL_API const char *getPersoData();

protected:
	/**
	  * Constructor
	  *		Used only in APL_EIDCard::getID()
	  */    
	APL_DocEId(APL_EIDCard *card);
	CByteArray getXML(bool bNoHeader, APL_XmlUserRequestedInfo &xmlUInfo);

private:
	APL_DocEId(const APL_DocEId& doc);				/**< Copy not allowed - not implemented */
	APL_DocEId &operator= (const APL_DocEId& doc);	/**< Copy not allowed - not implemented */

	APL_EIDCard *m_card;							/**< Pointer to the card that construct this object*/
	
	std::string m_FirstName;						/**< Field FirstName1 follow by FirstName2 */
	APL_XmlUserRequestedInfo *_xmlUInfo;

friend APL_DocEId& APL_EIDCard::getID();	/**< This method must access protected constructor */
friend CByteArray APL_CCXML_Doc::getXML(bool bNoHeader); /* this method accesses getxml(,) */
};

/******************************************************************************//**
  * Class that represent the document Address on a PTEID card
  *
  * This class show id informations to APL_EIDCard user
  * (These informations comes from the Address file)
  *
  * To get APL_AddrEId object, we have to ask it from APL_EIDCard
  *********************************************************************************/
class APL_AddrEId : public APL_XMLDoc
{
public:
	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_AddrEId();

	EIDMW_APL_API virtual bool isAllowed();							/**< The document is allowed*/

	EIDMW_APL_API virtual CByteArray getXML(bool bNoHeader=false);	/**< Build the XML document */
	EIDMW_APL_API virtual CByteArray getCSV();						/**< Build the CSV document */
	EIDMW_APL_API virtual CByteArray getTLV();						/**< Build the TLV document */

	EIDMW_APL_API const char *getAddressVersion();		/**< Return field AddressVersion from the Address file */
	EIDMW_APL_API const char *getStreet();				/**< Return field Street from the Address file */
	EIDMW_APL_API const char *getZipCode();				/**< Return field ZipCode from the Address file */
	EIDMW_APL_API const char *getMunicipality();		/**< Return field Municipality from the Address file */
	EIDMW_APL_API const char *getCivilParish();			/**< Return field CivilParish from the Address file */
	EIDMW_APL_API const char *getStreetName();			/**< Return field StreetName from the Address file */
	EIDMW_APL_API const char *getStreetType1();			/**< Return field StreetType1 from the Address file */
	EIDMW_APL_API const char *getStreetType2();			/**< Return field StreetType2 from the Address file */
	EIDMW_APL_API const char *getBuildingType1();		/**< Return field BuildingType1 from the Address file */
	EIDMW_APL_API const char *getBuildingType2();		/**< Return field BuildingType2 from the Address file */
	EIDMW_APL_API const char *getDoorNo();				/**< Return field DoorNo from the Address file */
	EIDMW_APL_API const char *getFloor();				/**< Return field Floor from the Address file */
	EIDMW_APL_API const char *getSide();				/**< Return field Side from the Address file */
	EIDMW_APL_API const char *getLocality();			/**< Return field Locality from the Address file */
	EIDMW_APL_API const char *getPlace();			/**< Return field Locality from the Address file */
	EIDMW_APL_API const char *getZip4();				/**< Return field Zip4 from the Address file */
	EIDMW_APL_API const char *getZip3();				/**< Return field Zip3 from the Address file */
	EIDMW_APL_API const char *getPostalLocality();		/**< Return field PostalLocality from the Address file */
	EIDMW_APL_API const char *getDistrict();			/**< Return field District from the Address file */

protected:
	/**
	  * Constructor
	  *		Used only in APL_EIDCard::getID()
	  */
	APL_AddrEId(APL_EIDCard *card);
	CByteArray getXML(bool bNoHeader, APL_XmlUserRequestedInfo &xmlUInfo);

private:
	APL_AddrEId(const APL_AddrEId& doc);				/**< Copy not allowed - not implemented */
	APL_AddrEId &operator= (const APL_AddrEId& doc);	/**< Copy not allowed - not implemented */

	APL_EIDCard *m_card;							/**< Pointer to the card that construct this object*/

	//std::string m_FirstName;						/**< Field FirstName1 follow by FirstName2 */
	APL_XmlUserRequestedInfo *_xmlUInfo;

friend APL_AddrEId& APL_EIDCard::getAddr();	/**< This method must access protected constructor */
friend CByteArray APL_CCXML_Doc::getXML(bool bNoHeader); /* this method accesses getxml(,) */
};

/******************************************************************************//**
  * Class that represent the document SOD on a PTEID card
  *
  * This class show the SOD to APL_EIDCard user
  *
  * To get APL_SodEid object, we have to ask it from APL_EIDCard
  *********************************************************************************/
class APL_SodEid : public APL_Biometric
{
public:
	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_SodEid();

	EIDMW_APL_API virtual bool isAllowed();							/**< The document is allowed*/

	EIDMW_APL_API virtual CByteArray getXML(bool bNoHeader=false);	/**< Build the XML document */
	EIDMW_APL_API virtual CByteArray getCSV();						/**< Build the CSV document */
	EIDMW_APL_API virtual CByteArray getTLV();						/**< Build the TLV document */

	EIDMW_APL_API const CByteArray& getData();				/**< Return field Data from the file */
	//EIDMW_APL_API const CByteArray& getHash();				/**< Return field Hash from the ID file */

protected:
	/**
	  * Constructor
	  *		Used only in APL_EIDCard::getSod()
	  */    
	APL_SodEid(APL_EIDCard *card);

private:
	APL_SodEid(const APL_SodEid& doc);				/**< Copy not allowed - not implemented */
	APL_SodEid &operator= (const APL_SodEid& doc);	/**< Copy not allowed - not implemented */

	APL_EIDCard *m_card;									/**< Pointer to the card that construct this object*/

friend APL_SodEid& APL_EIDCard::getSod();	/**< This method must access protected constructor */
};

/******************************************************************************//**
  * Class for VersionInfo document
  *********************************************************************************/
class APL_DocVersionInfo : public APL_XMLDoc
{
public: 

	/**
	  * Destructor
	  */
	EIDMW_APL_API virtual ~APL_DocVersionInfo();

	EIDMW_APL_API virtual bool isAllowed();							/**< The document is allowed*/

	EIDMW_APL_API virtual CByteArray getXML(bool bNoHeader=false);	/**< Build the XML document */
	EIDMW_APL_API virtual CByteArray getCSV();						/**< Build the CSV document */
	EIDMW_APL_API virtual CByteArray getTLV();						/**< Build the TLV document */

	EIDMW_APL_API const char *getSerialNumber();		/**< Return field SerialNumber from the Info file */
	EIDMW_APL_API const char *getComponentCode();		/**< Return field ComponentCode from the Info file */
	EIDMW_APL_API const char *getOsNumber();			/**< Return field OsNumber from the Info file */
	EIDMW_APL_API const char *getOsVersion();			/**< Return field OsVersion from the Info file */
	EIDMW_APL_API const char *getSoftmaskNumber();		/**< Return field SoftmaskNumber from the Info file */
	EIDMW_APL_API const char *getSoftmaskVersion();		/**< Return field SoftmaskVersion from the Info file */
	EIDMW_APL_API const char *getAppletVersion();		/**< Return field AppletVersion from the Info file */
	EIDMW_APL_API const char *getGlobalOsVersion();		/**< Return field GlobalOsVersion from the Info file */
	EIDMW_APL_API const char *getAppletInterfaceVersion();/**< Return field AppletInterfaceVersion from the Info file */
	EIDMW_APL_API const char *getPKCS1Support();		/**< Return field PKCS1Support from the Info file */
	EIDMW_APL_API const char *getKeyExchangeVersion();	/**< Return field KeyExchangeVersion from the Info file */
	EIDMW_APL_API const char *getAppletLifeCicle();		/**< Return field AppletLifeCicle from the Info file */

	EIDMW_APL_API const CByteArray &getSignature();		/**< Return the signature of the card info */

	EIDMW_APL_API const char *getGraphicalPersonalisation();			/**< Return field GraphicalPersonalisation from the TokenInfo file */
	EIDMW_APL_API const char *getElectricalPersonalisation();			/**< Return field ElectricalPersonalisation from the TokenInfo file */
	EIDMW_APL_API const char *getElectricalPersonalisationInterface();	/**< Return field ElectricalPersonalisationInterface from the TokenInfo file */

protected:
	/**
	  * Constructor
	  *		Used only in APL_EIDCard::getVersionInfo()
	  */    
	APL_DocVersionInfo(APL_EIDCard *card);

private:
	APL_EIDCard *m_card;							/**< Pointer to the card that construct this object*/

friend APL_DocVersionInfo& APL_EIDCard::getDocInfo();	/**< This method must access protected constructor */
};

}

#endif //__APLCARDEID_H__
