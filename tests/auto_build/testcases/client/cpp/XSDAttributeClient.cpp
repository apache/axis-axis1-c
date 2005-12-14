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


#include "XSDAttribute.hpp"
#include <axis/AxisException.hpp>
#include <ctype.h>
#include <iostream>
#include "CommonClientTestCode.hpp"

int main(int argc, char* argv[])
{
	char endpoint[256];
	const char* url="http://localhost:80/axis/Calculator";
	char dateTime[50];

	BooleanType* booleanType = new BooleanType();
	BooleanType* booleanTypeReturn = NULL;
	ByteType* byteType = new ByteType();
	ByteType* byteTypeReturn = NULL;
	UnsignedByteType* unsignedByteType = new UnsignedByteType();
	UnsignedByteType* unsignedByteTypeReturn = NULL;
	ShortType* shortType = new ShortType();
	ShortType* shortTypeReturn = NULL;
	UnsignedShortType* unsignedShortType = new UnsignedShortType();
	UnsignedShortType* unsignedShortTypeReturn = NULL;
	IntType* intType = new IntType();
	IntType* intTypeReturn = NULL;
	UnsignedIntType* unsignedIntType = new UnsignedIntType();
	UnsignedIntType* unsignedIntTypeReturn = NULL;
	LongType* longType = new LongType();
	LongType* longTypeReturn = NULL;
	UnsignedLongType* unsignedLongType = new UnsignedLongType();
	UnsignedLongType* unsignedLongTypeReturn = NULL;
	FloatType* floatType = new FloatType();
	FloatType* floatTypeReturn = NULL;
	DoubleType* doubleType = new DoubleType();
	DoubleType* doubleTypeReturn = NULL;
	StringType* stringType = new StringType();
	StringType* stringTypeReturn = NULL;

	DateTimeType* dtt = new DateTimeType();
	DateTimeType* dttReturn = NULL;
	DateType* dt = new DateType();
	DateType* dtReturn = NULL;
	TimeType* tt = new TimeType();
	TimeType* ttReturn = NULL;
	IntegerType* integerType = new IntegerType();
	IntegerType* integerTypeReturn = NULL;
	DecimalType* decimalType = new DecimalType();
	DecimalType* decimalTypeReturn = NULL;
	Base64BinaryType* b64Type = new Base64BinaryType();
	Base64BinaryType* b64TypeReturn = NULL;
	HexBinaryType* hexType = new HexBinaryType();
	HexBinaryType* hexTypeReturn = NULL;
	QNameType* qnameType = new QNameType();
	QNameType* qnameTypeReturn = NULL;
	AnyURIType* anyURI = new AnyURIType();
	AnyURIType* anyURIReturn = NULL;

	xsd__base64Binary b64Test;
	xsd__hexBinary hexTest;
	xsd__unsignedByte* testUB = (xsd__unsignedByte*)"<test><xml>some dod&y string</xml></test>";

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

		XSDAttribute* ws = new XSDAttribute(endpoint);

		booleanType->booleanType = (xsd__boolean)0;
		booleanTypeReturn = ws->getDataBoolean(booleanType);
		cout << "boolean=" << booleanTypeReturn->booleanType << endl;

		byteType->byteType = (xsd__byte)31;
		byteTypeReturn = ws->getDataByte(byteType);
		printf("byte=%d\n", byteTypeReturn->byteType); fflush(stdout);

		unsignedByteType->unsignedByteType = (xsd__unsignedByte)32;
		unsignedByteTypeReturn = ws->getDataUnsignedByte(unsignedByteType);
		printf("unsigned byte=%d\n", unsignedByteTypeReturn->unsignedByteType); fflush(stdout);

		shortType->shortType = 7;
		shortTypeReturn = ws->getDataShort(shortType);
		cout << "short=" << shortTypeReturn->shortType << endl;

		unsignedShortType->unsignedShortType = (xsd__unsignedShort)14;
		unsignedShortTypeReturn = ws->getDataUnsignedShort(unsignedShortType);
		cout << "unsigned short=" << unsignedShortTypeReturn->unsignedShortType << endl;

		intType->intType = (xsd__int)21;
		intTypeReturn = ws->getDataInt(intType);
		cout << "int=" << intTypeReturn->intType << endl;

		unsignedIntType->unsignedIntType = (xsd__unsignedInt)28;
		unsignedIntTypeReturn = ws->getDataUnsignedInt(unsignedIntType);
		cout << "unsigned int=" << unsignedIntTypeReturn->unsignedIntType << endl;

		longType->longType = (xsd__long)35;
		longTypeReturn = ws->getDataLong(longType);
		cout << "long=" << (int)(longTypeReturn->longType) << endl;

		unsignedLongType->unsignedLongType = (xsd__unsignedLong)42;
		unsignedLongTypeReturn = ws->getDataUnsignedLong(unsignedLongType);
		cout << "unsigned long=" << unsignedLongTypeReturn->unsignedLongType << endl;

		floatType->floatType = (xsd__float)70.3535888888;
		floatTypeReturn = ws->getDataFloat(floatType);
		printf("float=%.5f\n", floatTypeReturn->floatType); fflush(stdout);

		doubleType->doubleType = (xsd__double)140.7175888888;
		doubleTypeReturn = ws->getDataDouble(doubleType);
		printf("double=%.5f\n", doubleTypeReturn->doubleType); fflush(stdout);

		stringType->stringType = (xsd__string) "never odd or even";
		stringTypeReturn = ws->getDataString(stringType);
		cout << "string=" << stringTypeReturn->stringType << endl;

		integerType->integerType = (xsd__integer) 919191919;
		integerTypeReturn = ws->getDataInteger(integerType);
		cout << "integer=" << (int)(integerTypeReturn->integerType) << endl;

		decimalType->decimalType = (xsd__decimal)929292929.5555555555555;
		decimalTypeReturn = ws->getDataDecimal(decimalType);
		printf("decimal=%.5f\n", decimalTypeReturn->decimalType); fflush(stdout);

		dtt->dateTimeType = testDate;
		dttReturn = ws->getDataDateTime(dtt);
		strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &dttReturn->dateTimeType);
		cout << "dateTime=" << dateTime << endl;

/* Awaiting Server side implementation
		dt->dateType = testDate;
		dtReturn = ws->getDataDate(dt);
		strftime(dateTime, 50, "%a %b %d %Y", &dtReturn->dateType);
		cout << "date=" << dateTime << endl;

		tt->timeType = testDate;
		ttReturn = ws->getDataTime(tt);
		strftime(dateTime, 50, "%a %b %d %H:%M:%S %Y", &ttReturn->timeType);
		cout << "time=" << dateTime << endl;

		b64Type->base64BinaryType = b64Test;
		b64TypeReturn = ws->getDataBase64Binary(b64Type);
        int size = 0;
        const xsd__unsignedByte * base64BinaryData = b64TypeReturn->base64BinaryType.get(size);
		cout << "base64Binary size=" << size << endl;
		if( size > 0)
		{
			cout << "base64Binary data=" << base64BinaryData << endl;
		}

		hexType->hexBinaryType = hexTest;
		hexTypeReturn = ws->getDataHexBinary(hexType);
        size = 0;
        const xsd__unsignedByte * hexBinaryData = hexTypeReturn->hexBinaryType.get(size);
		cout << "hexBinary size=" << size << endl;
		if( size > 0)
		{
			cout << "hexBinary data=" << hexBinaryData << endl;
		}
*/
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
				cout << "Exception : " << e.what() << endl;
			}
	}
	catch(exception& e)
	{
	    cout << "Unknown exception has occured" << e.what() << endl;
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

