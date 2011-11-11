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

#include "CardInformation.h"

CardInformation::CardInformation()
	: m_pCard(NULL)
	, m_cardReader("")
{
	Reset();
}

CardInformation::~CardInformation()
{
}

void CardInformation::Reset()
{
	m_CardInfo.Reset();
	m_PersonInfo.Reset();
	m_MiscInfo.Reset();
	m_AddressInfo.Reset();
	m_pCard = NULL;
	m_cardReader = "";
}

bool CardInformation::LoadData(PTEID_MemoryCard& Card, QString const& cardReader)
{
	bool bRetVal = false;

	Reset();

	switch(Card.getType())
	{
	case PTEID_CARDTYPE_SIS:
		bRetVal = RetrieveData(dynamic_cast<PTEID_SISCard&>(Card));
		m_cardReader = cardReader;
		break;
	default:
		break;
	}

	return bRetVal;
}

bool CardInformation::LoadData(PTEID_EIDCard& Card, QString const& cardReader)
{
	bool bRetVal = false;

	Reset();

	switch(Card.getType())
	{
	case PTEID_CARDTYPE_KIDS:
	case PTEID_CARDTYPE_FOREIGNER:
	case PTEID_CARDTYPE_EID:
		bRetVal |= RetrieveData(Card);
		m_cardReader = cardReader;
		bRetVal = true;
		break;
	default:
		break;

	}
	return bRetVal;
}

bool CardInformation::LoadDataAddress(PTEID_EIDCard& Card, QString const& cardReader)
{
	bool bRetVal = false;

	Reset();

	switch(Card.getType())
	{
	case PTEID_CARDTYPE_KIDS:
	case PTEID_CARDTYPE_FOREIGNER:
	case PTEID_CARDTYPE_EID:
		bRetVal |= RetrieveDataAddress(Card);
		m_cardReader = cardReader;
		bRetVal = true;
		break;
	default:
		break;

	}
	return bRetVal;
}

bool CardInformation::LoadDataPersoData(PTEID_EIDCard& Card, QString const& cardReader)
{
	bool bRetVal = false;

	Reset();

	switch(Card.getType())
	{
	case PTEID_CARDTYPE_KIDS:
	case PTEID_CARDTYPE_FOREIGNER:
	case PTEID_CARDTYPE_EID:
		bRetVal |= RetrieveDataPersoData(Card);
		m_cardReader = cardReader;
		bRetVal = true;
		break;
	default:
		break;

	}
	return bRetVal;
}

bool CardInformation::LoadDataCertificates(PTEID_EIDCard& Card, QString const& cardReader)
{
	bool bRetVal = false;

	Reset();

	switch(Card.getType())
	{
	case PTEID_CARDTYPE_KIDS:
	case PTEID_CARDTYPE_FOREIGNER:
	case PTEID_CARDTYPE_EID:
		bRetVal |= RetrieveDataCertificates(Card);
		m_cardReader = cardReader;
		bRetVal = true;
		break;
	default:
		break;

	}
	return bRetVal;
}

