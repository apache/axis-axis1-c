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
//#include <iostream>
using namespace std;

#include "InteropTestPortType.hpp"

#define ARRAYSIZE 2

static void usage( char * programName, char * defaultURL)
{
    cout << endl << "Usage:" << endl
		 << programName << " [-? | service_url] " << endl
		 << "    -?              Show this help." << endl
		 << "    service_url     URL of the service." << endl
		 << "    Default service URL is assumed to be " << defaultURL << endl;
}

int main( int argc, char *argv[])
{
    int				x = 0;
    int				i = 0;
    char			buffer1[100];
    char			endpoint[256];
    const char *	server = "localhost";
    const char *	port = "80";

    sprintf( endpoint, "http://%s:%s/axis/base", server, port);

    if( argc > 1)
    {
// Watch for special case help request
// Check for - only so that it works for
//-?, -h or --help; -anything
		if( !strncmp( argv[1], "-", 1))	
		{
			usage( argv[0], endpoint);

			return 2;
		}

		sprintf( endpoint, argv[1]);
	}

    bool	bSuccess = false;
    int		iRetryIterationCount = 3;

    do
    {
        try
        {
			InteropTestPortType ws( endpoint, APTHTTP1_1);

//testing echoString 
			cout << "invoking echoString..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoString");

			string	bigstring;

			for( int ii = 0; ii < 2; ii++)
			{
				bigstring += "hello world ";
			}

			strcpy( buffer1, bigstring.c_str());

			char *	cpResult = ws.echoString( "hello world");

			if( 0 == strcmp( cpResult, "hello world"))
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			delete [] cpResult;

// testing echoStringArray 
			cout << "invoking echoStringArray..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoStringArray");

			xsd__string *		pStringArray = new char *[ARRAYSIZE];
			xsd__string_Array	arrstr;

			sprintf( buffer1, "%dth element of string array", 0);

			for( i = 0; i < ARRAYSIZE; i++)
			{
				pStringArray[i] = buffer1;
			}

			arrstr.set( pStringArray, ARRAYSIZE);

			xsd__string_Array *	arrstrResult = ws.echoStringArray( &arrstr);

			if( arrstrResult != NULL)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			delete [] arrstrResult;

// testing echoInteger 
			cout << "invoking echoInteger..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoInteger");

			if( ws.echoInteger( 56) == 56)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

// testing echoIntegerArray 
			cout << "invoking echoIntegerArray..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoIntegerArray");

			xsd__int **		ppIntArray = new xsd__int *[ARRAYSIZE];
			xsd__int_Array	arrint;
			int				iToSend[ARRAYSIZE];

			for( x = 0; x < ARRAYSIZE; x++)
			{
				iToSend[x] = x;
				ppIntArray[x] = (xsd__int *) &iToSend[x];
			}

			arrint.set( ppIntArray, ARRAYSIZE);

			xsd__int_Array *	arrintResult = ws.echoIntegerArray( &arrint);
			int					iSize;
			const xsd__int **	ppIntOutputArray = arrintResult->get( iSize);

			if( ppIntOutputArray != NULL)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			// Free memory for result
			delete [] arrintResult;

// testing echoFloat 
			cout << "invoking echoFloat..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoFloat");

			xsd__float	fvalue = (xsd__float) 1.4214;

			if (ws.echoFloat (fvalue) > (xsd__float) 1.42)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

// testing echoFloat 
			cout << "invoking echoFloatArray..." << endl;

			ws.setTransportProperty ( "SOAPAction", "InteropBase#echoFloatArray");

			xsd__float_Array	arrfloat;
			xsd__float **		ppFloatArray = new xsd__float *[ARRAYSIZE];
			xsd__float			fToSend[ARRAYSIZE];

			for( x = 0; x < ARRAYSIZE; x++)
			{
				fToSend[x] = (xsd__float) 1.1111 * x;
				ppFloatArray[x] = &fToSend[x];
			}

			arrfloat.set( ppFloatArray, ARRAYSIZE);

			xsd__float_Array *	arrfloatResult = ws.echoFloatArray( &arrfloat);

			if( arrfloatResult != NULL)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			delete [] ppFloatArray;
			delete [] arrfloatResult;

// testing echo Struct
			cout << "invoking echoStruct..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoStruct");

			SOAPStruct	stct;
			xsd__int	integer = 5000;
			xsd__float	floatVal = (xsd__float) 12345.7346345;

			stct.varFloat = &floatVal;
			stct.varInt = &integer;
			stct.varString = strdup( "This is string in SOAPStruct");

			SOAPStruct *stctResult = ws.echoStruct( &stct);

			if (stctResult != NULL)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			// Free result memory
			delete stctResult;

//testing echo Array of Struct
			SOAPStruct_Array	arrstct;
			SOAPStruct **		ppSOAPStruct = new SOAPStruct* [ARRAYSIZE];

			for( x = 0; x < ARRAYSIZE; x++)
			{
				integer = x;
				floatVal = (xsd__float) 1.1111 * x;

				sprintf( buffer1, "varString of %dth element of SOAPStruct array", x);

				ppSOAPStruct[x]->setvarFloat( &floatVal);
				ppSOAPStruct[x]->setvarInt( &integer);
				ppSOAPStruct[x]->setvarString( buffer1);
			}

			arrstct.set( ppSOAPStruct, ARRAYSIZE);

//testing echo Struct Array
			cout << "invoking echoStructArray..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoStructArray");

			SOAPStruct_Array *	arrstctResult = ws.echoStructArray( &arrstct);

			if( arrstctResult != NULL)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			delete ppSOAPStruct;
			delete [] arrstctResult;

//testing echo void
			cout << "invoking echoVoid..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoVoid");

			ws.echoVoid();
			
			cout << "successful" << endl;

//testing echo base 64 binary
			cout << "invoking echoBase64..." << endl;

			ws.setTransportProperty ("SOAPAction", "InteropBase#echoBase64");

			const char *	bstr = "some string that is sent encoded to either base64Binary or hexBinary";

			xsd__base64Binary	bb;

			bb.set( (xsd__unsignedByte *) strdup( bstr), (xsd__int) strlen( bstr));

			xsd__base64Binary bbResult = ws.echoBase64( bb);

			if( (xsd__int) strlen( bstr) == bbResult.getSize())
			{
				xsd__int	iSize;

				cout << "successful" << endl
					 << "Returned String :" << endl
					 << bbResult.get( iSize) << endl;
			}
			else
			{
				printf ("failed\n");
			}

			cout << "invoking echoDate..." << endl;
			ws.setTransportProperty( "SOAPAction", "InteropBase#echoDate");

			time_t	tim;

			time( &tim);

			tm *	lt = gmtime( &tim);

			if( memcmp( &ws.echoDate( *lt), lt, sizeof( tm)) == 0)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

//testing echo hex binary
			cout << "invoking echoHexBinary..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoHexBinary");

			xsd__hexBinary	hb;
			
			iSize = (xsd__int) strlen( bstr);

			hb.set( (xsd__unsignedByte *) strdup( bstr), iSize);

			xsd__hexBinary hbReturn = ws.echoHexBinary( hb);

			if( iSize == hbReturn.getSize())
			{
				cout << "successful" << endl
					 << "Returned String :" << endl
					 << hbReturn.get( iSize) << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

//testing echo decimal
			cout << "invoking echoDecimal..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoDecimal");

            if( ws.echoDecimal( 1234.567890) > 1234.56)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			//testing echo boolean
			cout << "invoking echoBoolean..." << endl;

			ws.setTransportProperty( "SOAPAction", "InteropBase#echoBoolean");

			if( ws.echoBoolean (true_) == true_)
			{
				cout << "successful" << endl;
			}
			else
			{
				cout << "failed" << endl;
			}

			bSuccess = true;
		}
		catch( AxisException & e)
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
				cout << e.what() << endl;
			}
		}
		catch( exception & e)
		{
			cout << e.what() << endl;
		}
		catch( ...)
		{
			cout << "Unknown exception has occured" << endl;
		}

		iRetryIterationCount--;
    } while( iRetryIterationCount > 0 && !bSuccess);

    //getchar();
    return 0;
}
