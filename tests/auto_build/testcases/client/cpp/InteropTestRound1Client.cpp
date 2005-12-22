// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
using namespace std;

#include "InteropTestPortType.hpp" 
#include "CommonClientTestCode.hpp"

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];
	const char* server="localhost";
	const char* port="80";
	sprintf(endpoint, "http://%s:%s/axis/InteropBase", server, port);
		
	if (argc > 1)
		strcpy(endpoint, argv[1]);
	
	
	bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
        {
	   InteropTestPortType ws(endpoint, APTHTTP1_1);


	ws.setTransportTimeout(5);
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoString");
	printf("invoking echoString...\n");
	//testing echoString 
	string bigstring;
	for (int ii=0;ii<2;ii++)
	{
		bigstring += "hello world ";
	}
	strcpy(buffer1, bigstring.c_str());
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoString");
	printf(ws.echoString(buffer1));
	if (0 == strcmp(ws.echoString("hello world"), "hello world"))
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoStringArray 
	xsd__string_Array arrstr;
	arrstr.m_Array = new char*[ARRAYSIZE];
	arrstr.m_Size = ARRAYSIZE;
	sprintf(buffer1, "%dth element of string array", 0);
	//sprintf(buffer2, "%dth element of string array", 1);
	for(int i=0; i< ARRAYSIZE; i++)
	{
		arrstr.m_Array[i] = buffer1;
	}
	//arrstr.m_Array[1] = buffer2;
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoStringArray");
	printf("invoking echoStringArray...\n");
	if (ws.echoStringArray(arrstr).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoInteger 
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoInteger");
	printf("invoking echoInteger...\n");
	if (ws.echoInteger(56) == 56)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoIntegerArray 
	xsd__int_Array arrint;
	arrint.m_Array = new int*[ARRAYSIZE];
    arrint.m_Size = ARRAYSIZE;
	int iToSend[ARRAYSIZE];

	for (x=0;x<ARRAYSIZE;x++)
	{
		iToSend[x] = x;
		 arrint.m_Array[x] = &iToSend[x];
	}
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoIntegerArray");
	printf("invoking echoIntegerArray...\n");
	if (ws.echoIntegerArray(arrint).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoFloat 
	printf("invoking echoFloat...\n");
	float fvalue = 1.4214;
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoFloat");
	if (ws.echoFloat(fvalue) > 1.42)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoFloat 
	xsd__float_Array arrfloat;
	 arrfloat.m_Array = new float*[ARRAYSIZE];
	arrfloat.m_Size = ARRAYSIZE;
	float fToSend[ARRAYSIZE];
	for (x=0;x<ARRAYSIZE;x++)
	{
		fToSend[x] = 1.1111*x;
		arrfloat.m_Array[x] = &fToSend[x];
	}
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoFloatArray");
	printf("invoking echoFloatArray...\n");
	if (ws.echoFloatArray(arrfloat).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echo Struct
	SOAPStruct stct;
	stct.varFloat = new float;
	stct.varInt = new int;
	*(stct.varFloat) = 12345.7346345;
	*(stct.varInt) = 5000;
	stct.varString = strdup("This is string in SOAPStruct");
	printf("invoking echoStruct...\n");
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoStruct");
	if (ws.echoStruct(&stct) != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo Array of Struct
	SOAPStruct_Array arrstct;
	arrstct.m_Array = new SOAPStruct[ARRAYSIZE];
	arrstct.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrstct.m_Array[x].varFloat = new float;
		arrstct.m_Array[x].varInt = new int;
		*(arrstct.m_Array[x].varFloat) = 1.1111*x;
		*(arrstct.m_Array[x].varInt) = x;
		sprintf(buffer1, "varString of %dth element of SOAPStruct array", x);
		arrstct.m_Array[x].varString = buffer1;
	}
	//testing echo Struct Array
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoStructArray");
	printf("invoking echoStructArray...\n");
	if (ws.echoStructArray(arrstct).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo void
	printf("invoking echoVoid...\n");
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoVoid");
	ws.echoVoid();
	printf("successful\n");
	//testing echo base 64 binary

	const char* bstr = stringToAscii("some string that is sent encoded to either base64Binary or hexBinary");

	printf("invoking echoBase64...\n");
	xsd__base64Binary bb;
    bb.set((unsigned char *) strdup(bstr), strlen(bstr));
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoBase64");
    xsd__base64Binary bbResult = ws.echoBase64(bb);
    int size = 0;
    const xsd__unsignedByte * data = bbResult.get(size);
	if (bb.getSize() == size)
	{
		printf("successful\n");
		printf("Returned String :\n%s\n", asciiToString((char *)data));
	}
	else
		printf("failed\n");

    time_t timeToTest = 1100246323;
    struct tm *temp = gmtime(&timeToTest);
    struct tm time;
    memcpy(&time, temp, sizeof(struct tm));
   
	printf("invoking echoDate...\n");
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoDate");
      
      xsd__dateTime ed_temp = ws.echoDate(time);
	if (memcmp(&ed_temp, &time, sizeof(tm)) == 0)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo hex binary

	printf("invoking echoHexBinary...\n");
	xsd__hexBinary hb;
    hb.set((unsigned char*)strdup(bstr), strlen(bstr));
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoHexBinary");
    xsd__hexBinary hbResult = ws.echoHexBinary(hb);
    size = 0;
    data = hbResult.get(size);
	if (hb.getSize() == size)
	{
		printf("successful\n");
		printf("Returned String :\n%s\n", asciiToString((char *)data));
	}
	else
		printf("failed\n");
	//testing echo decimal
	printf("invoking echoDecimal...\n");
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoDecimal");
	if (ws.echoDecimal(1234.567890) > 1234.56)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo boolean
	printf("invoking echoBoolean...\n");
	ws.setTransportProperty("SOAPAction" , "InteropBase#echoBoolean");
	if (ws.echoBoolean(true_) == true_)
		printf("successful\n");
	else
		printf("failed\n");

	bSuccess = true;
	}
	catch(AxisException& e)
	{
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 0)
				{
					bSilent = true;
				}
			}
			else
			{
				iRetryIterationCount = 0;
			}

            if( !bSilent)
			{
		printf("%s\n", e.what());
			}
	}
	catch(exception& e)
	{
		printf("%s\n", e.what());
	}
	catch(...)
	{
		printf("Unknown exception has occured\n");
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	//getchar();
	return 0;
}
