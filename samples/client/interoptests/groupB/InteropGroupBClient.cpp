// InteropGroupBClient.cpp : Defines the entry point for the console application.
//
#include "InteropTestPortTypeB.hpp"
#include <axis/AxisException.hpp>
#include <iostream>

#define ARRAYSIZE 5

static void
usage (char *programName, char *defaultURL)
{
    cout << "\nUsage:\n"
	<< programName << " [-? | service_url] " << endl
	<< "    -?             Show this help.\n"
	<< "    service_url    URL of the service.\n"
	<< "    Default service URL is assumed to be " << defaultURL
	<<
	"\n    Could use http://localhost:8080/axis/services/echo to test with Axis Java."
	<< endl;
}

int main(int argc, char* argv[])
{
	int x;
	char endpoint[256];

    // Set default service URL
    sprintf (endpoint, "http://localhost/axis/groupB");
    // Could use http://localhost:8080/axis/services/echo to test with Axis Java

	if (argc > 1)
	{
	    // Watch for special case help request
	    if (!strncmp (argv[1], "-", 1)) // Check for - only so that it works for 
                                            //-?, -h or --help; -anything 
	    {
		usage (argv[0], endpoint);
		return 2;
	    }
	    sprintf (endpoint, argv[1]);
	}


	cout << endl << " Using service at " << endpoint << endl << endl;
    
    try
	{
	InteropTestPortTypeB ws(endpoint);
	/*we do not support multi-dimensional arrays.*/
	/*ws.echo2DStringArray*/

	/*testing Nested Arrays*/
	SOAPArrayStruct sas;
	sas.varFloat = 12345.67890;
	sas.varInt = 5000;
	sas.varString = strdup("varString content of SOAPArrayStruct");
	sas.varArray.m_Array = new AxisChar*[ARRAYSIZE];
	sas.varArray.m_Size = ARRAYSIZE;
	for (x=0; x<ARRAYSIZE; x++)
	{
		sas.varArray.m_Array[x] = strdup("content of string array element");
	}
	printf("invoking echoNestedArray...\n");
	if (ws.echoNestedArray(&sas) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	/*testing Nested Structs*/
	SOAPStructStruct sss;
	sss.varFloat = 12345.67890;
	sss.varInt = 5000;
	sss.varString = strdup("varString content of SOAPStructStruct");
	sss.varStruct = new SOAPStruct();
	sss.varStruct->varFloat = 67890.12345;
	sss.varStruct->varInt = 54321;
	sss.varStruct->varString = strdup("varString content of SOAPStruct");
	printf("invoking echoNestedStruct...\n");
	if (ws.echoNestedStruct(&sss) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	/*testing echo Simple types as struct*/
	char* str = strdup("content of string passed");
	printf("invoking echoSimpleTypesAsStruct...\n");
	if (ws.echoSimpleTypesAsStruct(str,5000,2345.67890) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	/*testing echo Struct as simple types.*/
	SOAPStruct ss;
	ss.varFloat = 12345.67890;
	ss.varInt = 5000;
	ss.varString = strdup("content of string passed");
	char* outStr;
	int outInt;
	float outFloat;
	printf("invoking echoStructAsSimpleTypes...\n");
	ws.echoStructAsSimpleTypes(&ss,&outStr,&outInt,&outFloat);
	if (outInt == 5000 && (0 == strcmp(outStr,"content of string passed")) && outFloat > 12345.67)
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
