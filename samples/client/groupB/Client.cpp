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
	/*we do not support multi-dimensional arrays.*/
	/*ws.echo2DStringArray*/

	/*testing Nested Arrays*/
	SOAPArrayStruct	sas;

	sas.varFloat = 12345.67890;
	sas.varInt = 5000;
	sas.varString = strdup( "varString content of SOAPArrayStruct");
	sas.varArray.m_Array = new AxisChar*[ARRAYSIZE];
	sas.varArray.m_Size = ARRAYSIZE;

	for( x=0; x < ARRAYSIZE; x++)
	{
		sas.varArray.m_Array[x] = strdup( "content of string array element");
	}

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

	/*testing Nested Structs*/
	SOAPStructStruct sss;
	sss.varFloat = 12345.67890;
	sss.varInt = 5000;
	sss.varString = strdup("varString content of SOAPStructStruct");
	sss.varStruct = new SOAPStruct();
	float ff = 67890.12345;
	int ii = 54321;
	sss.varStruct->varFloat = ff;
	sss.varStruct->varInt = ii;
	sss.varStruct->varString = strdup("varString content of SOAPStruct");
	printf("\n\ninvoking echoNestedStruct...\n");
	ws.setTransportProperty("SOAPAction" , "groupB#echoNestedStruct");
	if (ws.echoNestedStruct(&sss) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	/*testing echo Simple types as struct*/
	char* str = strdup("content of string passed");
	printf("\n\ninvoking echoSimpleTypesAsStruct...\n\n");
	ws.setTransportProperty("SOAPAction" , "groupB#echoSimpleTypesAsStruct");
	SOAPStruct* pRet = ws.echoSimpleTypesAsStruct(str,5000,2345.67890);
	cout << "String = " << pRet->varString << endl;
	cout << "Integer = " << pRet->varInt<< endl;
	cout << "Float = " << pRet->varFloat << endl;

	if (ws.echoSimpleTypesAsStruct(str,5000,2345.67890) != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	delete str;
	delete pRet;
	/*testing echo Struct as simple types.*/
	SOAPStruct ss;
	ss.varFloat = 12345.67890;
	ss.varInt = 5000;
	ss.varString = strdup("content of string passed");
	int OutValue1 =0;
	float OutValue2 = 0;
	printf("\n\ninvoking echoStructAsSimpleTypes...\n");
	ws.setTransportProperty("SOAPAction" , "groupB#echoStructAsSimpleTypes");
	
	ws.echoStructAsSimpleTypes(&ss,&OutValue1,&OutValue2);
	cout << "Integer = " << OutValue1 << endl;
	cout << "Float = " << OutValue2 << endl;

	if (OutValue1 == 5000 && OutValue2 > 12345.67)
		printf("successful\n");
	else
		printf("failed\n");	
	/*getchar();*/
        }
        catch(AxisException& e)
        {
            printf("Exception : %s\n", e.what());
        }
        catch(exception& e)
        {
            printf("Unknown exception has occured\n");
        }
        catch(...)
        {
            printf("Unknown exception has occured\n");
        }
	return 0;
}
