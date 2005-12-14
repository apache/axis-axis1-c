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


#include "XSDElementNil.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	char dateTime[50];

	xsd__boolean* boolResult;
	xsd__byte* bResult;
	xsd__unsignedByte* ubResult;
	xsd__short* sResult;
	xsd__unsignedShort* usResult;
	xsd__int* iResult;
	xsd__unsignedInt* uiResult;
	xsd__long* lResult;
	xsd__unsignedLong* ulResult;
	xsd__float* fResult;
	xsd__double* dResult;
	xsd__date* dateResult;			// typedef of struct tm
	xsd__dateTime* dateTimeResult;	// typedef of struct tm
	xsd__time* timeResult;			// typedef of struct tm
	xsd__duration* durationResult;
	xsd__string strResult;
	xsd__integer* intResult;
	xsd__decimal* decResult;
	xsd__base64Binary* b64Result;
	xsd__hexBinary* hexResult;

	xsd__boolean boolInput=(xsd__boolean)1;
	xsd__byte bInput=(xsd__byte)31;
	xsd__unsignedByte ubInput=(xsd__unsignedByte)32;
	xsd__short sInput=(xsd__short)7;
	xsd__unsignedShort usInput=(xsd__unsignedShort)14;
	xsd__int iInput=(xsd__int)21;
	xsd__unsignedInt uiInput=(xsd__unsignedInt)28;
	xsd__long lInput=(xsd__long)35;
	xsd__unsignedLong ulInput=(xsd__unsignedLong)42;
	xsd__float fInput=(xsd__float)35.3535888888;
	xsd__double dInput=(xsd__double)70.7175888888;
	xsd__date dateInput;			// typedef of struct tm
	xsd__dateTime dateTimeInput;	// typedef of struct tm
	xsd__time timeInput;			// typedef of struct tm
	xsd__duration durationInput = (xsd__duration) 123456789;
 	xsd__string strInput=(xsd__string)"never odd or even";
	xsd__integer intInput=(xsd__integer)919191919;
	xsd__decimal decInput=(xsd__decimal)929292929.5555555555555;
	xsd__base64Binary b64Input;
	xsd__hexBinary hexInput;

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
		XSDElementNil* ws = new XSDElementNil(endpoint);

		boolResult = ws->setGetDataBoolean(&boolInput);
		cout << "bool=" << *boolResult << endl;
		boolResult = ws->setGetDataBoolean(NULL);
		if(boolResult)
			cout << "bool nil=" << *boolResult << endl;
		else
			cout << "bool nil=NULL" << endl;

		bResult = ws->setGetDataByte(&bInput);
		printf("byte=%d\n", *bResult); fflush(stdout);
		bResult = ws->setGetDataByte(NULL);
		if(bResult) {
			printf("byte nil=%d\n", *bResult); fflush(stdout);
		}
		else
			cout << "byte nil=NULL" << endl;


		ubResult = ws->setGetDataUnsignedByte(&ubInput);
		printf("unsigned byte=%d\n", *ubResult); fflush(stdout);
		ubResult = ws->setGetDataUnsignedByte(NULL);
		if(ubResult) {
			printf("unsigned byte nil=%d\n", *ubResult); fflush(stdout);
		}
		else
			cout << "unsigned byte nil=NULL" << endl;

		sResult = ws->setGetDataShort(&sInput);
		cout << "short=" << *sResult << endl;
		sResult = ws->setGetDataShort(NULL);
		if(sResult)
			cout << "short nil=" << *sResult << endl;
		else
			cout << "short nil=NULL" << endl;

		usResult = ws->setGetDataUnsignedShort(&usInput);
		cout << "unsigned short=" << *usResult << endl;
		usResult = ws->setGetDataUnsignedShort(NULL);
		if(usResult)
			cout << "unsigned short nil=" << *usResult << endl;
		else
			cout << "unsigned short nil=NULL" << endl;

		iResult = ws->setGetDataInt(&iInput);
		cout << "int=" << *iResult << endl;
		iResult = ws->setGetDataInt(NULL);
		if(iResult)
			cout << "int nil=" << *iResult << endl;
		else
			cout << "int nil=NULL" << endl;

		uiResult = ws->setGetDataUnsignedInt(&uiInput);
		cout << "unsigned int=" << *uiResult << endl;
		uiResult = ws->setGetDataUnsignedInt(NULL);
		if(uiResult)
			cout << "unsigned int nil=" << *uiResult << endl;
		else
			cout << "unsigned int nil=NULL" << endl;

		lResult = ws->setGetDataLong(&lInput);
		cout << "long=" << *lResult << endl;
		lResult = ws->setGetDataLong(NULL);
		if(lResult)
			cout << "long nil=" << *lResult << endl;
		else
			cout << "long nil=NULL" << endl;

		ulResult = ws->setGetDataUnsignedLong(&ulInput);
		cout << "unsigned long=" << *ulResult << endl;
		ulResult = ws->setGetDataUnsignedLong(NULL);
		if(ulResult)
			cout << "unsigned long nil=" << *ulResult << endl;
		else
			cout << "unsigned long nil=NULL" << endl;

		fResult = ws->setGetDataFloat(&fInput);
		printf("float=%.5f\n", *fResult); fflush(stdout);
		fResult = ws->setGetDataFloat(NULL);
		if(fResult) {
			printf("float nil=%.5f\n", *fResult); fflush(stdout);
		} else
			cout << "float nil=NULL" << endl;

		dResult = ws->setGetDataDouble(&dInput);
		printf("double=%.5f\n", *dResult); fflush(stdout);
		dResult = ws->setGetDataDouble(NULL);
		if(dResult) {
			printf("double nil=%.5f\n", *dResult); fflush(stdout);
		} else
			cout << "double nil=NULL" << endl;

        durationResult = ws->setGetDataDurationType(&durationInput);
        cout << "duration=" << *durationResult << endl;

		dateResult = ws->setGetDateType(&testDate);
		strftime(dateTime, 50, "%a %b %d %Y", dateResult);
		cout << "date=" << dateTime << endl;
		dateResult = ws->setGetDateType(NULL);
		if(dateResult) {
			strftime(dateTime, 50, "%a %b %d %Y", dateResult);
			cout << "date nil=" << dateTime << endl;
		}
		else
			cout << "date nil=NULL" << endl;

		dateTimeResult = ws->setGetDateTimeType(&testDate);
		strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", dateTimeResult);
		cout << "dateTime=" << dateTime << endl;
		dateTimeResult = ws->setGetDateTimeType(NULL);
		if(dateTimeResult) {
			strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", dateTimeResult);
			cout << "dateTime nil=" << dateTime << endl;
		}
		else
			cout << "dateTime nil=NULL" << endl;

//  This is being commented out due to issue on some servers
//  An additional testcase XSDTimeNil has been created to isolate this test.
//		timeResult = ws->setGetTimeType(&testDate);
//		strftime(dateTime, 50, "%H:%M:%S", timeResult);
//		cout << "time=" << dateTime << endl;

		strResult = ws->setGetDataString("never odd or even");
		cout << "string=" << strResult << endl;
		strResult = ws->setGetDataString("m");
		cout << "small string=" << strResult << endl;
		strResult = ws->setGetDataString(NULL);
		if(strResult)
			cout << "string nil=" << strResult << endl;
		else
			cout << "string nil=NULL" << endl;

		intResult = ws->setGetIntegerType(&intInput);
		cout << "integer=" << *intResult << endl;
		intResult = ws->setGetIntegerType(NULL);
		if(intResult)
			cout << "integer nil=" << *intResult << endl;
		else
			cout << "integer nil=NULL" << endl;

		decResult = ws->setGetDecimalType(&decInput);
        printf("decimal=%.5f\n", *decResult); fflush(stdout);
		decResult = ws->setGetDecimalType(NULL);
        if(decResult) {
			printf("decimal nil=%.5f\n", *decResult); fflush(stdout);
		} else
			cout << "decimal nil=NULL" << endl;

		b64Result = ws->setGetBase64BinaryType(&b64Test);
        int size = 0;
        const xsd__unsignedByte * base64BinaryData = b64Result->get(size);
		cout << "base64Binary size=" << size << endl;
		if( size > 0)
		{
			cout << "base64Binary data=" << asciiToStringOfLength((char *)base64BinaryData, size) << endl;
		}
		b64Result = ws->setGetBase64BinaryType(NULL);
		if(b64Result)
			cout << "base64Binary nil size=" << b64Result->getSize() << endl;
		else
			cout << "base64Binary nil=NULL" << endl;

		hexResult = ws->setGetHexBinary(&hexTest);
        size = 0;
        const xsd__unsignedByte * hexBinaryData = hexResult->get(size);
		cout << "hexBinary size=" << size << endl;
		if( size > 0)
		{
			cout << "hexBinary data=" << asciiToStringOfLength((char *)hexBinaryData, size) << endl;
		}
		hexResult = ws->setGetHexBinary(&hexTest);
		if(hexResult)
			cout << "hexBinary nil size=" << hexResult->getSize() << endl;
		else
			cout << "hexBinary nil=NULL" << endl;

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
