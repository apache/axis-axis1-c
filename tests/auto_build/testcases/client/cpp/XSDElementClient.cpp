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

 
/*
 * Supported types are
  1 <element name="getBoolean">
  2 <element name="getByte">
  3 <element name="getUnsignedByte">
  4 <element name="getShort">
  5 <element name="getUnsignedShort">
  6 <element name="getInt">
  7 <element name="getUnsignedInt">
  8 <element name="getLong">
  9 <element name="getUnsignedLong">
 10 <element name="getFloat">
 11 <element name="getDouble">
 12 <element name="getDate">
 13 <element name="getDateTime">
 14 <element name="getTime">
 15 <element name="getDuration">
 16 <element name="getString">
 17 <element name="getInteger">
 18 <element name="getDecimal">
 19 <element name="getBase64Binary">
 20 <element name="getHexBinary">
 *
 */


#include "XSDElement.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	char dateTime[50];

	xsd__boolean boolResult=(xsd__boolean)1;
	xsd__byte bResult=(xsd__byte)0;
	xsd__unsignedByte ubResult=(xsd__unsignedByte)0;
	xsd__short sResult=(xsd__short)0;
	xsd__unsignedShort usResult=(xsd__unsignedShort)0;
	xsd__int iResult=(xsd__int)0;
	xsd__unsignedInt uiResult=(xsd__unsignedInt)0;
	xsd__long lResult=(xsd__long)0;
	xsd__unsignedLong ulResult=(xsd__unsignedLong)0;
	xsd__float fResult=(xsd__float)0;
	xsd__double dResult=(xsd__double)0;
	xsd__date dateResult;			// typedef of struct tm
	xsd__dateTime dateTimeResult;	// typedef of struct tm
	xsd__time timeResult;			// typedef of struct tm
	xsd__duration durationResult = (xsd__duration) 0;
	xsd__string strResult=(xsd__string)0;
	xsd__integer intResult=(xsd__integer)0;
	xsd__decimal decResult=(xsd__decimal)0;
	xsd__base64Binary b64Result;
	xsd__hexBinary hexResult;

	xsd__base64Binary b64Test;
	xsd__hexBinary hexTest;

	//xsd__unsignedByte* testUB = (xsd__unsignedByte*)"never odd or even";

	xsd__unsignedByte* testUB = (xsd__unsignedByte*)stringToAscii("<test><xml>some dod&y string</xml></test>");

	b64Test.set(testUB, 41);
    hexTest.set(testUB, 41);

    time_t timeToTest;
    timeToTest = 1100246323;
    xsd__date *temp = gmtime(&timeToTest);
    xsd__date testDate;
    memcpy(&testDate, temp, sizeof(xsd__date));

	if(argc>1)
		url = argv[1];

		bool bSuccess = false;
		int	iRetryIterationCount = 3;

		do
		{
	try
	{
		sprintf(endpoint, "%s", url);
		XSDElement* ws = new XSDElement(endpoint);

		boolResult = ws->setGetDataBoolean((xsd__boolean)1);
		cout << "bool=" << boolResult << endl;

		bResult = ws->setGetDataByte(31);
		printf("byte=%d\n", bResult);
		ubResult = ws->setGetDataUnsignedByte(32);
		printf("unsigned byte=%d\n", ubResult);

		sResult = ws->setGetDataShort(7);
		printf("short=%d\n", sResult);
		usResult = ws->setGetDataUnsignedShort(14);
		printf("unsigned short=%d\n", usResult);

		iResult = ws->setGetDataInt(21);
		printf("int=%d\n", iResult);
		uiResult = ws->setGetDataUnsignedInt(28);
		printf("unsigned int=%d\n", uiResult);fflush(stdout);

		lResult = ws->setGetDataLong((xsd__long)35);
	    cout << "long=" << lResult << endl;
#ifdef WIN32
        xsd__long longInput     =  10000000000I64;
        xsd__long longMaxInput  =  9223372036854775807I64;
        xsd__long longMinInput  = -9223372036854775808I64 ;
#else
        xsd__long longInput     =  10000000000LL;
        xsd__long longMaxInput  =  9223372036854775807LL;
        xsd__long longMinInput  = -9223372036854775808LL;
#endif
        lResult = ws->setGetDataLong((xsd__long) longInput);
        cout << "long=" << lResult << endl;
        lResult = ws->setGetDataLong((xsd__long) longMaxInput);
        cout << "MaxInclusive long=" << lResult << endl;
        lResult = ws->setGetDataLong((xsd__long) longMinInput);
        cout << "MinInclusive long=" << lResult << endl;

		ulResult = ws->setGetDataUnsignedLong((xsd__unsignedLong)42);
		cout << "unsigned long=" << ulResult << endl;

		fResult = ws->setGetDataFloat((xsd__float)35.3535888888);
		printf("float=%.5f\n", fResult); fflush(stdout);

		dResult = ws->setGetDataDouble((xsd__double)70.7175888888);
		printf("double=%.5f\n", dResult); fflush(stdout);

        durationResult = ws->setGetDataDurationType((xsd__duration)123456789);
        cout << "duration=" << durationResult << endl;

		dateResult = ws->setGetDateType(testDate);
		strftime(dateTime, 50, "%a %b %d %Y", &dateResult);
		cout << "date=" << dateTime << endl;

		dateTimeResult = ws->setGetDateTimeType(testDate);
		strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &dateTimeResult);
		cout << "dateTime=" << dateTime << endl;

//  This is being commented out due to issue on some servers
//  An additional testcase XSDTime has been created to isolate this test.
//		timeResult = ws->setGetTimeType(testDate);
//		strftime(dateTime, 50, "%H:%M:%S", &timeResult);
//		cout << "time=" << dateTime << endl;

		strResult = ws->setGetDataString("never odd or even");
		cout << "string=" << strResult << endl;
		strResult = ws->setGetDataString("m");
		cout << "small string=" << strResult << endl;
        strResult = ws->setGetDataString("");
        if (strResult != NULL)
        {
            if ( *strResult == NULL)
            {
                cout << "empty string = <empty string>" << endl;
            }
            else
            {
                cout << "empty string = " << strResult << endl;
            }
        }
        else
        {
            cout << "empty string = <NULL>" << endl;
        }
        
		intResult = ws->setGetIntegerType(919191919);
		cout << "integer=" << intResult << endl;

		decResult = ws->setGetDecimalType(929292929.5555555555555);
        printf("decimal=%.5f\n", decResult); fflush(stdout);

		b64Result = ws->setGetBase64BinaryType(b64Test);
        int size = 0;
        const xsd__unsignedByte * base64BinaryData = b64Result.get(size);
		cout << "base64Binary size=" << size << endl;
		if( size > 0)
		{
			cout << "base64Binary data=" << asciiToStringOfLength((char *)base64BinaryData, size) << endl;
		}

		hexResult = ws->setGetHexBinary(hexTest);
        size = 0;
        const xsd__unsignedByte * hexBinaryData = hexResult.get(size);
		cout << "hexBinary size=" << size << endl;
		if( size > 0)
		{
			cout << "hexBinary data=" << asciiToStringOfLength((char *)hexBinaryData, size) << endl;
		}

		bSuccess = true;
		delete ws;
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
				cout << "Exception : " << e.what() << endl;
			}
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << endl;
	}
	catch(...)
	{
	    cout << "Unknown exception has occured" << endl;
	}
		iRetryIterationCount--;
		} while( iRetryIterationCount > 0 && !bSuccess);
	cout<< "---------------------- TEST COMPLETE -----------------------------"<< endl;
	
	return 0;
}


