// Copyright 2003-2004 The Apache Software Foundation.
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

// InteropGroupBClient.cpp : Defines the entry point for the console application.
//
#include "InteropTestPortTypeB.hpp"
#include <axis/AxisException.hpp>
#include <iostream>
#include <string>

#define ARRAYSIZE 5
#define WSDL_DEFAULT_ENDPOINT "http://localhost:80/axis/groupB"


static void usage( char * programName, char * defaultURL)
{
    cout << "Usage:" << endl
		 << programName << " [-? | service_url] " << endl
		 << "    -?             Show this help." << endl
		 << "    service_url    URL of the service." << endl
		 << "    Default service URL is assumed to be " << defaultURL << endl
		 <<	"    Could use http://localhost:80/axis/groupB" << endl;
}

int main( int argc, char * argv[])
{
	int		x;
	char	endpoint[256];

    // Set default service URL
    sprintf( endpoint, "%s", WSDL_DEFAULT_ENDPOINT);

    // Could use http://localhost:8080/axis/services/echo to test with Axis Java

	if( argc > 1)
	{
// Watch for special case help request
// Check for - only so that it works for 
// -?, -h or --help; -anything 
		if( !strncmp( argv[1], "-", 1))
	    {
			usage( argv[0], endpoint);

            return 2;
	    }
	    
		sprintf( endpoint, argv[1]);
	}

	cout << endl << " Using service at " << endpoint << endl << endl;
    
    try
	{
		InteropTestPortTypeB	ws( endpoint);

// testing Nested Arrays
		SOAPArrayStruct	sas;

		sas.setvarFloat( (xsd__float) 12345.67890);
		sas.setvarInt( 5000);
		sas.setvarString( strdup( "varString content of SOAPArrayStruct"));

		xsd__string *		pArray = new xsd__string [ARRAYSIZE];
		xsd__string_Array 	sArray;

		for( x = 0; x < ARRAYSIZE; x++)
		{
			pArray[x] = (xsd__string) strdup( "content of string array element");
		}

		sArray.set( pArray, ARRAYSIZE);

		sas.setvarArray( &sArray);

		cout << "invoking echoNestedArray..." << endl;

		ws.setTransportProperty( "SOAPAction" , "groupB#echoNestedArray");

		if( ws.echoNestedArray( &sas) != NULL)
		{
			cout << "successful" << endl;
		}
		else
		{
			cout << "failed" << endl;
		}

// testing Nested Structs
		cout << endl << "invoking echoNestedStruct..." << endl;

		ws.setTransportProperty( "SOAPAction", "groupB#echoNestedStruct");

		SOAPStruct			sSOAPStruct;
		SOAPStructStruct	sss;

		sss.setvarFloat( (xsd__float) 12345.67890);
		sss.setvarInt( 5000);
		sss.setvarString( (xsd__string) strdup("varString content of SOAPStructStruct"));

		sSOAPStruct.setvarFloat( (xsd__float) 67890.12345);
		sSOAPStruct.setvarInt( (xsd__int) 54321);
		sSOAPStruct.setvarString( (xsd__string) strdup("varString content of SOAPStruct"));

		sss.setvarStruct( &sSOAPStruct);

		if( ws.echoNestedStruct( &sss) != NULL)
		{
			cout << "successful" << endl;
		}
		else
		{
			cout << "failed" << endl;
		}

// testing echo Simple types as struct
		cout << endl << "invoking echoSimpleTypesAsStruct..." << endl;

		ws.setTransportProperty( "SOAPAction", "groupB#echoSimpleTypesAsStruct");

		xsd__string	str = (xsd__string) strdup( "content of string passed");

		SOAPStruct *	pRet = ws.echoSimpleTypesAsStruct( str,
														   (xsd__int) 5000,
														   (xsd__float) 2345.67890);

		cout << "String = " << pRet->getvarString() << endl;
		cout << "Integer = " << pRet->getvarInt() << endl;
		cout << "Float = " << pRet->getvarFloat() << endl;

		if( ws.echoSimpleTypesAsStruct( str,
										(xsd__int) 5000,
										(xsd__float) 2345.67890) != NULL)
		{
			cout << "successful" << endl;
		}
		else
		{
			cout << "failed" << endl;
		}

		delete str;
		delete pRet;

// testing echo Struct as simple types.
		cout << endl << "invoking echoStructAsSimpleTypes..." << endl;

		ws.setTransportProperty( "SOAPAction", "groupB#echoStructAsSimpleTypes");

		SOAPStruct ss;

		ss.setvarFloat( (xsd__float) 12345.67890);
		ss.setvarInt( (xsd__int) 5000);
		ss.setvarString( (xsd__string) strdup("content of string passed"));

		xsd__int	iOutValue1 = 0;
		xsd__float	fOutValue2 = 0;

		ws.echoStructAsSimpleTypes( &ss, &iOutValue1, &fOutValue2);

		cout << "Integer = " << iOutValue1 << endl;
		cout << "Float = " << fOutValue2 << endl;

		if( iOutValue1 == (xsd__int) 5000 && fOutValue2 > (xsd__float) 12345.67)
		{
			cout << "successful" << endl;
		}
		else
		{
			cout << "failed" << endl;
		}
	}
	catch( AxisException& e)
	{
		cout << "Exception : " << e.what() << endl;
	}
	catch( exception& e)
	{
		cout << "Unknown exception has occurred" << e.what() << endl;
	}
	catch( ...)
	{
		cout << "Unknown exception has occurred" << endl;
	}

	return 0;
}
