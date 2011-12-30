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
#include "eidlib.h"

#include "eidlibException.h"
#include "MWException.h"
#include "eidErrors.h"

#include "InternalUtil.h"

#include "APLDoc.h"
#include "APLCrypto.h"
#include "APLCardSIS.h"
#include "APLCardPteid.h"

#include <string.h>

//UNIQUE INDEX FOR RETRIEVING OBJECT
#define INCLUDE_OBJECT_SODEID_DATA	1
#define INCLUDE_OBJECT_SODEID_HASH	2
#define INCLUDE_OBJECT_INFOEID_SIGN		3

namespace eIDMW
{

/*****************************************************************************************
---------------------------------------- PTEID_ByteArray --------------------------------------
*****************************************************************************************/
PTEID_ByteArray::PTEID_ByteArray():PTEID_Object(NULL,new CByteArray())
{
	m_delimpl=true;
}
	
PTEID_ByteArray::PTEID_ByteArray(const unsigned char * pucData, unsigned long ulSize):PTEID_Object(NULL,new CByteArray(pucData,ulSize))
{
	m_delimpl=true;
}

PTEID_ByteArray::PTEID_ByteArray(const PTEID_ByteArray &bytearray):PTEID_Object(bytearray.m_context,new CByteArray(*(CByteArray*)bytearray.m_impl))
{
	m_delimpl=true;
}

PTEID_ByteArray::PTEID_ByteArray(const SDK_Context *context,const CByteArray &impl):PTEID_Object(context,(void *)&impl)
{
}

PTEID_ByteArray::~PTEID_ByteArray()
{
	if(m_delimpl)
	{
		CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
		delete pimpl;
		m_impl=NULL;
	}
}

PTEID_ByteArray & PTEID_ByteArray::operator=(const CByteArray &bytearray)
{
	if(m_delimpl)
	{
		CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
		delete pimpl;
		m_impl=NULL;
	}

	m_impl=new CByteArray(bytearray.GetBytes(),bytearray.Size());
	m_delimpl=true;

	return *this;
}

PTEID_ByteArray & PTEID_ByteArray::operator=(const PTEID_ByteArray &bytearray)
{
	if(m_delimpl)
	{
		CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
		delete pimpl;
		m_impl=NULL;
	}

	m_impl=new CByteArray(bytearray.GetBytes(),bytearray.Size());
	m_delimpl=true;

	return *this;
}

unsigned long PTEID_ByteArray::Size() const
{
	unsigned long out = 0;

	CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
	out = pimpl->Size();

	return out;
}

const unsigned char *PTEID_ByteArray::GetBytes() const
{
	const unsigned char *out = NULL;

	CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
	out = pimpl->GetBytes();

	return out;
}

void PTEID_ByteArray::Append(const unsigned char * pucData, unsigned long ulSize)
{
	if(!m_delimpl)	//If the CByteArray has not been created, it can't be changed
		throw PTEID_ExBadUsage();

	BEGIN_TRY_CATCH

	CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
	pimpl->Append(pucData,ulSize);

	END_TRY_CATCH
}

void PTEID_ByteArray::Append(const PTEID_ByteArray &data)
{
	if(!m_delimpl)	//If the CByteArray has not been created, it can't be changed
		throw PTEID_ExBadUsage();

	BEGIN_TRY_CATCH

	CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
	CByteArray *apl_data=static_cast<CByteArray *>(data.m_impl);
	pimpl->Append(*apl_data);

	END_TRY_CATCH
}

void PTEID_ByteArray::Clear()
{
	if(!m_delimpl)	//If the CByteArray has not been created, it can't be changed
		throw PTEID_ExBadUsage();

	BEGIN_TRY_CATCH

	CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
	pimpl->ClearContents();

	END_TRY_CATCH
}

bool PTEID_ByteArray::Equals(const PTEID_ByteArray &data) const
{
	bool out = false;

	CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
	CByteArray *data_pimpl=static_cast<CByteArray *>(data.m_impl);

	out = pimpl->Equals(*data_pimpl);

	return out;
}

bool PTEID_ByteArray::writeToFile(const char * csFilePath)
{
	bool out=false;

	BEGIN_TRY_CATCH

	CByteArray *pimpl=static_cast<CByteArray *>(m_impl);
	out=APL_XMLDoc::writeToFile(*pimpl,csFilePath);

	END_TRY_CATCH

	return out;
}

/*****************************************************************************************
---------------------------------------- PTEID_XMLDoc -------------------------------------------
*****************************************************************************************/
PTEID_XMLDoc::PTEID_XMLDoc(const SDK_Context *context,APL_XMLDoc *impl):PTEID_Object(context,impl)
{
}

PTEID_XMLDoc::~PTEID_XMLDoc()
{
	if(m_delimpl && m_impl)
	{
		APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);
		delete pimpl;
		m_impl=NULL;
	}
}

bool PTEID_XMLDoc::isAllowed()
{
	bool out;

	BEGIN_TRY_CATCH

	APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);

	out=pimpl->isAllowed();
	
	END_TRY_CATCH

	return out;
}

PTEID_ByteArray PTEID_XMLDoc::getXML()
{
	PTEID_ByteArray out;

	BEGIN_TRY_CATCH

	APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);

	CByteArray result=pimpl->getXML();
	out.Append(result.GetBytes(),result.Size());
	
	END_TRY_CATCH

	return out;
}

PTEID_ByteArray PTEID_XMLDoc::getCSV()
{
	PTEID_ByteArray out;

	BEGIN_TRY_CATCH

	APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);

	CByteArray result=pimpl->getCSV();
	out.Append(result.GetBytes(),result.Size());
	
	END_TRY_CATCH

	return out;
}

PTEID_ByteArray PTEID_XMLDoc::getTLV()
{
	PTEID_ByteArray out;

	BEGIN_TRY_CATCH

	APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);

	CByteArray result=pimpl->getTLV();
	out.Append(result.GetBytes(),result.Size());
	
	END_TRY_CATCH

	return out;
}

bool PTEID_XMLDoc::writeXmlToFile(const char * csFilePath)
{
	bool out = false;

	BEGIN_TRY_CATCH

	APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);
	out = pimpl->writeXmlToFile(csFilePath);
	
	END_TRY_CATCH

	return out;
}

bool PTEID_XMLDoc::writeCsvToFile(const char * csFilePath)
{
	bool out = false;

	BEGIN_TRY_CATCH

	APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);
	out = pimpl->writeCsvToFile(csFilePath);
	
	END_TRY_CATCH

	return out;
}

bool PTEID_XMLDoc::writeTlvToFile(const char * csFilePath)
{
	bool out = false;

	BEGIN_TRY_CATCH

	APL_XMLDoc *pimpl=static_cast<APL_XMLDoc *>(m_impl);
	out = pimpl->writeTlvToFile(csFilePath);
	
	END_TRY_CATCH

	return out;
}

/*****************************************************************************************
---------------------------------------- PTEID_Biometric -------------------------------------------
*****************************************************************************************/
PTEID_Biometric::PTEID_Biometric(const SDK_Context *context,APL_Biometric *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_Biometric::~PTEID_Biometric()
{
}

/*****************************************************************************************
---------------------------------------- PTEID_Crypto -------------------------------------------
*****************************************************************************************/
PTEID_Crypto::PTEID_Crypto(const SDK_Context *context,APL_Crypto *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_Crypto::~PTEID_Crypto()
{
}

/*****************************************************************************************
---------------------------------------- PTEID_SisFullDoc -------------------------------------------
*****************************************************************************************/
PTEID_SisFullDoc::PTEID_SisFullDoc(const SDK_Context *context,APL_SisFullDoc *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_SisFullDoc::~PTEID_SisFullDoc()
{
}

/*****************************************************************************************
---------------------------------------- PTEID_EIdFullDoc -------------------------------------------
*****************************************************************************************/
PTEID_EIdFullDoc::PTEID_EIdFullDoc(const SDK_Context *context,APL_EIdFullDoc *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_EIdFullDoc::~PTEID_EIdFullDoc()
{
}


/*****************************************************************************************
---------------------------------------- PTEID_CCXML_Doc -------------------------------------------
*****************************************************************************************/
PTEID_CCXML_Doc::PTEID_CCXML_Doc(const SDK_Context *context,APL_CCXML_Doc *impl):PTEID_XMLDoc(context,impl)
{
	xmltemp = NULL;
}

PTEID_CCXML_Doc::~PTEID_CCXML_Doc(){
	if (xmltemp)
		delete xmltemp;
}

const char *PTEID_CCXML_Doc::getCCXML(){

	CByteArray cArray;


	BEGIN_TRY_CATCH

	APL_CCXML_Doc *pimpl=static_cast<APL_CCXML_Doc *>(m_impl);
	cArray = pimpl->getXML();
	if (xmltemp)
		delete xmltemp;
	xmltemp = new string((char*)(cArray.GetBytes()),cArray.Size());
	END_TRY_CATCH

	return xmltemp->c_str();
}


/*****************************************************************************************
---------------------------------------- PTEID_CardVersionInfo --------------------------------------
*****************************************************************************************/
PTEID_CardVersionInfo::PTEID_CardVersionInfo(const SDK_Context *context,APL_DocVersionInfo *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_CardVersionInfo::~PTEID_CardVersionInfo()
{
}

const char *PTEID_CardVersionInfo::getSerialNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getSerialNumber();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getComponentCode()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getComponentCode();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getOsNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getOsNumber();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getOsVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getOsVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getSoftmaskNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getSoftmaskNumber();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getSoftmaskVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getSoftmaskVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getAppletVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getAppletVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getGlobalOsVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getGlobalOsVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getAppletInterfaceVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getAppletInterfaceVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getPKCS1Support()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getPKCS1Support();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getKeyExchangeVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getKeyExchangeVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getAppletLifeCycle()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getAppletLifeCicle();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getGraphicalPersonalisation()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getGraphicalPersonalisation();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getElectricalPersonalisation()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getElectricalPersonalisation();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_CardVersionInfo::getElectricalPersonalisationInterface()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);
	out = pimpl->getElectricalPersonalisationInterface();
	
	END_TRY_CATCH

	return out;
}

const PTEID_ByteArray &PTEID_CardVersionInfo::getSignature()
{
	PTEID_ByteArray *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocVersionInfo *pimpl=static_cast<APL_DocVersionInfo *>(m_impl);

	out = dynamic_cast<PTEID_ByteArray *>(getObject(INCLUDE_OBJECT_INFOEID_SIGN));

	if(!out)
	{
		//CAutoMutex autoMutex(m_mutex);

		//pbytearray=dynamic_cast<PTEID_ByteArray *>(getObject(INCLUDE_OBJECT_INFOEID_SIGN));
		//if(!pbytearray)
		//{
			out = new PTEID_ByteArray(m_context,pimpl->getSignature());
			if(out)
				m_objects[INCLUDE_OBJECT_INFOEID_SIGN]=out;
			else
				throw PTEID_ExUnknown();
		//}
	}
	
	END_TRY_CATCH

	return *out;
}
/*****************************************************************************************
---------------------------------------- SisId -------------------------------------------
*****************************************************************************************/
PTEID_SisId::PTEID_SisId(const SDK_Context *context,APL_DocSisId *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_SisId::~PTEID_SisId()
{
}

const char *PTEID_SisId::getName()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getName();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getSurname()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getSurname();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getInitials()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getInitials();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getGender()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getGender();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getDateOfBirth()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getDateOfBirth();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getSocialSecurityNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getSocialSecurityNumber();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getLogicalNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getLogicalNumber();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getDateOfIssue()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getDateOfIssue();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getValidityBeginDate()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getValidityBeginDate();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_SisId::getValidityEndDate()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocSisId *pimpl=static_cast<APL_DocSisId *>(m_impl);
	out = pimpl->getValidityEndDate();
	
	END_TRY_CATCH

	return out;
}



/*****************************************************************************************
---------------------------------------- PTEID_EId ---------------------------------------------
*****************************************************************************************/
PTEID_EId::PTEID_EId(const SDK_Context *context,APL_DocEId *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_EId::~PTEID_EId()
{
}

const char *PTEID_EId::getDocumentVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getDocumentVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getDocumentType()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getDocumentType();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getCountry()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getCountry();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getFirstName1()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getFirstName1();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getSurname()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getSurname();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getGender()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getGender();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getDateOfBirth()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getDateOfBirth();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getLocationOfBirth()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getLocationOfBirth();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getNationality()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getNationality();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getDuplicata()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getDuplicata();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getSpecialOrganization()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getSpecialOrganization();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getMemberOfFamily()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getMemberOfFamily();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getLogicalNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getLogicalNumber();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getDocumentPAN()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getDocumentPAN();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getValidityBeginDate()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getValidityBeginDate();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getValidityEndDate()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getValidityEndDate();
	
	END_TRY_CATCH

	return out;
}
/*
const char *PTEID_EId::getIssuingMunicipality()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getIssuingMunicipality();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getAddressVersion()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getAddressVersion();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getStreet()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getStreet();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getZipCode()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getZipCode();
	
	END_TRY_CATCH

	return out;
}

*/
const char *PTEID_EId::getSpecialStatus()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getSpecialStatus();
	
	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getHeight()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getHeight();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getDocumentNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getDocumentNumber();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getTaxNo()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getTaxNo();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getSocialSecurityNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getSocialSecurityNumber();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getHealthNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getHealthNumber();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getIssuingEntity()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getIssuingEntity();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getGivenNameFather()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getGivenNameFather();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getSurnameFather()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getSurnameFather();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getGivenNameMother()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getGivenNameMother();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getSurnameMother()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getSurnameMother();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getParents()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getParents();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getLocalofRequest()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getLocalofRequest();

	END_TRY_CATCH

	return out;
}

const PTEID_ByteArray& PTEID_EId::getPhoto()
{
	PTEID_ByteArray *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);

	out = new PTEID_ByteArray((const unsigned char*)pimpl->getPhoto(), 14128);

	END_TRY_CATCH

	return *out;
}

const char *PTEID_EId::getMRZ1()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getMRZ1();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getMRZ2()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getMRZ2();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getMRZ3()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getMRZ3();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getAccidentalIndications()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getAccidentalIndications();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getCivilianIdNumber()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getCivilianIdNumber();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getPersoData()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getPersoData();

	END_TRY_CATCH

	return out;
}

const char *PTEID_EId::getValidation()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_DocEId *pimpl=static_cast<APL_DocEId *>(m_impl);
	out = pimpl->getValidation();

	END_TRY_CATCH

	return out;
}

/*****************************************************************************************
---------------------------------------- PTEID_EIdAdress ---------------------------------------------
*****************************************************************************************/
PTEID_Address::PTEID_Address(const SDK_Context *context,APL_AddrEId *impl):PTEID_XMLDoc(context,impl)
{
}

PTEID_Address::~PTEID_Address()
{
}

const char *PTEID_Address::getCivilParish()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getCivilParish();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getStreetName()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getStreetName();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getStreetType1()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getStreetType1();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getStreetType2()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getStreetType2();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getBuildingType1()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getBuildingType1();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getBuildingType2()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getBuildingType2();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getDoorNo()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getDoorNo();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getFloor()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getFloor();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getSide()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getSide();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getLocality()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getLocality();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getZip4()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getZip4();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getZip3()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getZip3();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getPostalLocality()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getPostalLocality();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getDistrict()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getDistrict();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getMunicipality()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getMunicipality();

	END_TRY_CATCH

	return out;
}

const char *PTEID_Address::getPlace()
{
	const char *out = NULL;

	BEGIN_TRY_CATCH

	APL_AddrEId *pimpl=static_cast<APL_AddrEId *>(m_impl);
	out = pimpl->getPlace();

	END_TRY_CATCH

	return out;
}

/*****************************************************************************************
---------------------------------------- PTEID_Picture -----------------------------------------
*****************************************************************************************/
PTEID_Sod::PTEID_Sod(const SDK_Context *context,APL_SodEid *impl):PTEID_Biometric(context,impl)
{
}

PTEID_Sod::~PTEID_Sod()
{
}

const PTEID_ByteArray& PTEID_Sod::getData()
{
	PTEID_ByteArray *out = NULL;

	BEGIN_TRY_CATCH

	APL_SodEid *psod=static_cast<APL_SodEid *>(m_impl);

	out = dynamic_cast<PTEID_ByteArray *>(getObject(INCLUDE_OBJECT_SODEID_DATA));

	if(!out)
	{
		//CAutoMutex autoMutex(m_mutex);

		//pbytearray=dynamic_cast<PTEID_ByteArray *>(getObject(INCLUDE_OBJECT_PICTUREEID_DATA));
		//if(!pbytearray)
		//{
			out = new PTEID_ByteArray(m_context,psod->getData());
			if(out)
				m_objects[INCLUDE_OBJECT_SODEID_DATA]=out;
			else
				throw PTEID_ExUnknown();
		//}
	}
	
	END_TRY_CATCH

	return *out;
}

const PTEID_ByteArray& PTEID_Sod::getHash()
{
	PTEID_ByteArray *out = NULL;

	/*BEGIN_TRY_CATCH

	APL_SodEid *psod=static_cast<APL_SodEid *>(m_impl);

	out = dynamic_cast<PTEID_ByteArray *>(getObject(INCLUDE_OBJECT_SODEID_HASH));

	if(!out)
	{
		CAutoMutex autoMutex(m_mutex);

		pbytearray=dynamic_cast<PTEID_ByteArray *>(getObject(INCLUDE_OBJECT_PICTUREEID_HASH));
		if(!pbytearray)
		{
	    		out = new PTEID_ByteArray(m_context,psod->getHash());
			if(out)
				m_objects[INCLUDE_OBJECT_SODEID_HASH]=out;
			else
				throw PTEID_ExUnknown();
		}
	}
	
	END_TRY_CATCH
	*/
	return *out;
}
	
}
