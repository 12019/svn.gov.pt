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
#include <stdlib.h>
#include <string.h>

#include "FileUtil.h"
#include "PrintBasic.h"
#include "PrintStruct.h"

#include "TestRead.h"
#include "TestCert.h"
#include "TestPin.h"
#include "TestOther.h"

#include "TestBasic.h"
#include "TestRawData.h"

static PTEID_Raw	rawData = {0};

void PrintTestRawData1(FILE *f, int Ocsp, int Crl)
{
    PTEID_Status tStatus = {0};
	
	//PTEID_GetRawData
	PrintTestFunction(f,"PTEID_GetRawData");
	tStatus = PTEID_GetRawData(&rawData);
	PrintStatus(f,"PTEID_GetRawData",&tStatus);
	if(PTEID_OK != tStatus.general)
	{
		PrintWARNING(f,"Get Raw Data failed");
	}

	PrintRawData(f,&rawData);
}

void PrintTestRawData2(FILE *f, int Ocsp, int Crl)
{
    PTEID_Status tStatus = {0};

	PrintHeader(f,"VIRTUAL WITH RAW DATA");
	//PTEID_SetRawData
	PrintTestFunction(f,"PTEID_SetRawData");
	tStatus = PTEID_SetRawData(&rawData);
	PrintStatus(f,"PTEID_SetRawData",&tStatus);
	if(PTEID_OK != tStatus.general)
	{
		PrintWARNING(f,"Set Raw Data failed");
	}

	PrintTestRead(f, Ocsp, Crl);
	PrintTestCert(f, Ocsp, Crl);
	PrintTestPin(f, Ocsp, Crl);
	PrintTestOther(f, Ocsp, Crl);
}

int test_RawData(const char *folder, const char *reader, int bVerify, int Ocsp, int Crl)
{
	return test_Basic("rawdata", &PrintTestRawData1, &PrintTestRawData2, folder, reader, bVerify, Ocsp, Crl);	
}
