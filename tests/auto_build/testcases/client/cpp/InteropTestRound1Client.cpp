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
#include <iostream>
using namespace std;

#include "InteropTestPortType.hpp" 
#include "CommonClientTestCode.hpp"

#define ARRAYSIZE							2
#define macro_ToTwoDecPlaces( value, type)	(type)(((int)(value * (type) 100.0))) / ((type) 100.0)
#define macro_BoolToString( value)			(value == true_ ? "true" : "false")

int main( int argc, char * argv[])
{
	char			buffer1[100];
	char			buffer2[100];
	char			endpoint[256];
	
	if( argc > 1)
	{
		strcpy( endpoint, argv[1]);
	}
	else
	{
		const char *	server = "localhost";
		const char *	port = "80";

		sprintf( endpoint, "http://%s:%s/axis/InteropBase", server, port);
	}
		
	bool	bSuccess = false;
	int		iRetryIterationCount = 3;

	do
	{
		try
        {
			InteropTestPortType	ws( endpoint, APTHTTP1_1);

			ws.setTransportTimeout( 5);
			ws.setTransportProperty( "SOAPAction", "InteropBase#echoString");

			cout << "invoking echoString..." << endl;
//testing echoString 

			string	bigString;

			for (int ii = 0; ii < 2; ii++)
			{
				bigString += "hello world ";
			}

			strcpy( buffer1, bigString.c_str());

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoString");

			cout << ws.echoString( buffer1) << endl;

			xsd__string	retString = ws.echoString( "hello world");
			xsd__string	expString = "hello world";

			if( 0 == strcmp( retString, expString))
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  The returned string (" << retString << ") was not the same as the expected string(" << expString << ")." << endl;
			}

// testing echoStringArray 
			xsd__string_Array	arrstr;
			xsd__string *		sToSend = new xsd__string[ARRAYSIZE];

			sprintf( buffer1, "%dth element of string array", 0);
			sprintf( buffer2, "%dst element of string array", 1);

			sToSend[0]= buffer1;
			sToSend[1]= buffer2;

			arrstr.set( sToSend, ARRAYSIZE);

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoStringArray");

			cout << "invoking echoStringArray..." << endl;

			int					outputSize = 0;
			xsd__string_Array *	outPutStrArray = ws.echoStringArray( &arrstr);

			if( outPutStrArray != NULL &&
				outPutStrArray->get( outputSize) != NULL &&
				outputSize == ARRAYSIZE)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed. outputsize=" << outputSize << endl;
			}

// testing echoInteger 
			ws.setTransportProperty("SOAPAction" , "InteropBase#echoInteger");

			cout << "invoking echoInteger..." << endl;

			xsd__int		expInt = 56;
			xsd__integer	retInt = ws.echoInteger( expInt);


			if( retInt == expInt)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  The returned integer (" << retInt << ") was not the same as the expected integer (" << expInt << ")." << endl;
			}

	// testing echoIntegerArray 
			xsd__int_Array	arrint;
			xsd__int **		iToSend = new xsd__int*[ARRAYSIZE];

			for( int x = 0; x < ARRAYSIZE; x++)
			{
				iToSend[x] = new xsd__int(x);
			}

			arrint.set( iToSend, ARRAYSIZE);

			ws.setTransportProperty( "SOAPAction" , "InteropBase#echoIntegerArray");

			cout << "invoking echoIntegerArray..." << endl;

			outputSize = 0;

			xsd__int_Array *	outPutIntArray = ws.echoIntegerArray( &arrint);

			if( outPutIntArray != NULL &&
				outPutIntArray->get( outputSize) != NULL &&
				outputSize == ARRAYSIZE)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  outputsize=" << outputSize << endl;
			}

	// testing echoFloat 
			cout << "invoking echoFloat..." << endl;

			float		fvalue = (float) 1.4214;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoFloat");

			xsd__float	retFloat = ws.echoFloat( fvalue);
			xsd__float	expFloat = macro_ToTwoDecPlaces( fvalue, float);

			if( retFloat > expFloat)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  The returned float (" << retFloat << ") was not the same as the expected float (" << expFloat << ")." << endl;
			}

	// testing echoFloatArray 
			xsd__float_Array	arrfloat;
			xsd__float **		fToSend = new xsd__float*[ARRAYSIZE];

			for( int x = 0; x < ARRAYSIZE; x++)
			{
				fToSend[x] = new xsd__float( (xsd__float) 1.1111 * (xsd__float) x);
			}

			arrfloat.set( fToSend, ARRAYSIZE);

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoFloatArray");

			cout << "invoking echoFloatArray..." << endl;

			outputSize = 0;

			xsd__float_Array *	outPutFloatArray = ws.echoFloatArray( &arrfloat);

			if( outPutFloatArray != NULL &&
				outPutFloatArray->get( outputSize) != NULL &&
				outputSize == ARRAYSIZE)	
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  outputsize=" << outputSize << endl;
			}

	// testing echo Struct
			SOAPStruct	stct;

			stct.varFloat = new float;
			stct.varInt = new int;

			*(stct.varFloat) = (xsd__float) 12345.7346345;
			*(stct.varInt) = 5000;

			stct.varString = strdup( "This is string in SOAPStruct");

			cout << "invoking echoStruct..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoStruct");

			if( ws.echoStruct( &stct) != NULL)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  The deserialised structure was null." << endl;
			}

	//testing echo Array of Struct
			SOAPStruct_Array	arrstct;
			SOAPStruct **		m_Array4 = new SOAPStruct *[ARRAYSIZE];
			SOAPStruct			ssToSend[ARRAYSIZE];
			xsd__float			myFloat;

			for( int x = 0; x < ARRAYSIZE; x++)
			{
				myFloat = (xsd__float) (1.1111 * x);

				ssToSend[x].setvarFloat( &myFloat);
				ssToSend[x].setvarInt( &x);

				sprintf( buffer1, "varString of %dth element of SOAPStruct array", x);

				ssToSend[x].setvarString( buffer1);

				m_Array4[x] = &ssToSend[x];
			}

			arrstct.set( m_Array4, ARRAYSIZE);

	//testing echo Struct Array
			ws.setTransportProperty( "SOAPAction", "InteropBase#echoStructArray");

			cout << "invoking echoStructArray..." << endl;

			SOAPStruct_Array *	outPutStructArray = ws.echoStructArray( &arrstct);

			if( outPutStructArray != NULL)
			{
				outputSize = 0;

				SOAPStruct ** ppSOAPStruct = outPutStructArray->get( outputSize);

				if( ppSOAPStruct != NULL && outputSize == ARRAYSIZE)
				{
					cout << "successful" << endl;
				}
				else
				{
					cout << "Failed.  outputsize = " << outputSize << endl;

					for( int iIndex = 0; iIndex < outputSize; iIndex++)
					{
						cout << "Failed(" << iIndex << ") varString = \"" << ppSOAPStruct[iIndex]->getvarString() << "\", varInt = " << *ppSOAPStruct[iIndex]->getvarInt() << ", varFloat = " << *ppSOAPStruct[iIndex]->getvarFloat() << endl;
					}
				}
			}
			else
			{
				cout << "Failed.  outPutStructArray = NULL" << endl;
			}

	//testing echo void
			cout << "invoking echoVoid..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoVoid");
			ws.echoVoid();

			cout << "successful" << endl;

	//testing echo base 64 binary
			const char *		bstr = stringToAscii( "some string that is sent encoded to either base64Binary or hexBinary");
			xsd__base64Binary	bb;

			cout << "invoking echoBase64..." << endl;

			bb.set( (unsigned char *) strdup( bstr), (xsd__int) strlen( bstr));

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoBase64");

			xsd__base64Binary			bbResult = ws.echoBase64( bb);
			xsd__int					size = 0;
			const xsd__unsignedByte *	data = bbResult.get( size);

			if( bb.getSize() == size)
			{
				cout << "successful" << endl;
				cout << "Returned String :" << endl << asciiToString( (char *) data) << endl;
			}
			else
			{
				cout << "Failed.  The returned base 64 binary size (" << size << ") was not the same as the expected size (" << bb.getSize() << ")." << endl;
			}

			time_t		timeToTest = 1100246323;
			struct tm *	temp = gmtime( &timeToTest);
			struct tm	time;

			memcpy( &time, temp, sizeof( struct tm));

			cout << "invoking echoDate..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoDate");

			xsd__dateTime	ed_temp = ws.echoDate( time);

			if( memcmp( &ed_temp, &time, sizeof( struct tm)) == 0)
			{
				cout << "successful" << endl;
			}
			else
			{
				char *	pExpectedTime = asctime( &ed_temp);
				int		iETLength = (int) strlen( pExpectedTime);
				char *	pReturnedTime = asctime( temp);
				int		iRTLength = (int) strlen( pReturnedTime);

				if( iETLength > 0)
				{
					pExpectedTime[iETLength - 1] = '\0';
				}
				else
				{
					pExpectedTime = "NULL";
				}

				if( iRTLength > 0)
				{
					pReturnedTime[iRTLength - 1] = '\0';
				}
				else
				{
					pReturnedTime = "NULL";
				}

				cout << "Failed.  The expected time (" << pExpectedTime << ") was not the same as the returned time (" << pReturnedTime << ")." << endl;
			}

	//testing echo hex binary
			cout << "invoking echoHexBinary..." << endl;

			xsd__hexBinary	hb;

			hb.set( (unsigned char *) strdup( bstr), (xsd__int) strlen( bstr));

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoHexBinary");

			xsd__hexBinary	hbResult = ws.echoHexBinary( hb);

			size = 0;
			data = hbResult.get( size);

			if( hb.getSize() == size)
			{
				cout << "successful" << endl;
				cout << "Returned String :" << endl << asciiToString( (char *) data) << endl;
			}
			else
			{
				cout << "Failed.  The returned hex64Binary size (" << size << ") was not the same as the expected hex64Binary size (" << hb.getSize() << ")." << endl;
			}

	//testing echo decimal
			cout << "invoking echoDecimal..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoDecimal");

			xsd__decimal decimalValue = 1234.567890;
			xsd__decimal decimalExpected = macro_ToTwoDecPlaces( decimalValue, xsd__decimal);
			xsd__decimal decimalReturn = ws.echoDecimal( decimalValue);

			if( decimalReturn > decimalExpected)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  The returned value (" << decimalReturn << ") was not the same as the expected value (" << decimalExpected << ")." << endl;
			}

	//testing echo boolean
			cout << "invoking echoBoolean..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoBoolean");

			xsd__boolean	bExpected = true_;
			xsd__boolean	bReturned = ws.echoBoolean( bExpected);

			if( bReturned == bExpected)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "Failed.  The returned value (" << macro_BoolToString( bReturned) << ") was not the same as the expected value (" << macro_BoolToString( bExpected) << ")." << endl;
			}

	bSuccess = true;
	}
	catch(AxisException& e)
	{
			bool bSilent = false;

			if( e.getExceptionCode() == CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED)
			{
				if( iRetryIterationCount > 1)
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
