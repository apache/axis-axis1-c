/* InteropGroupBClient.cpp : Defines the entry point for the console application.*/

#include "InteropTestPortTypeB.h"
#include <stdio.h>
#include <string.h>

#define ARRAYSIZE 2

static void
usage (char *programName, char *defaultURL)
{
    printf("\nUsage:\n");
    printf("programName  [-? | service_url] \n");
    printf("    -?             Show this help.\n");
    printf("    service_url    URL of the service.\n");
    printf("    Default service URL is assumed to be %s\n", defaultURL);
    printf("Could use http://localhost:8080/axis/services/echo to test with Axis Java.\n");
}

int main(int argc, char* argv[])
{
	int x;
	void* pstub;
	SOAPArrayStruct sas;
	SOAPStructStruct sss;
	SOAPStruct ss;
	char* outStr;
	int outInt;
	float outFloat;
	char* str;

	char endpoint[256];
    // Set default service URL
    sprintf (endpoint, "http://localhost/axis/cgroupB");
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
    printf(" Using service at %s\n", endpoint);

	pstub = get_InteropTestPortTypeB_stub(endpoint);

	sas.varFloat = 12345.67890;
	sas.varInt = 5000;
	sas.varString = strdup("varString content of SOAPArrayStruct");
	sas.varArray.m_Array = malloc(sizeof(AxisChar*)*ARRAYSIZE);
	sas.varArray.m_Size = ARRAYSIZE;
	for (x=0; x<ARRAYSIZE; x++)
	{
		sas.varArray.m_Array[x] = strdup("content of string array element");
	}
/*	printf("invoking echoNestedArray...\n");
	if (echoNestedArray(pstub, &sas) != NULL)
		printf("successful\n");
	else
		printf("failed\n");
*/
	/*testing Nested Structs*/
	sss.varFloat = 12345.67890;
	sss.varInt = 5000;
	sss.varString = strdup("varString content of SOAPStructStruct");
	sss.varStruct = malloc(sizeof(SOAPStruct));
	sss.varStruct->varFloat = 67890.12345;
	sss.varStruct->varInt = 54321;
	sss.varStruct->varString = strdup("varString content of SOAPStruct");
	printf("invoking echoNestedStruct...\n");
	if (echoNestedStruct(pstub, &sss) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	/*testing echo Simple types as struct*/
	str = strdup("content of string passed");
	printf("invoking echoSimpleTypesAsStruct...\n");
	if (echoSimpleTypesAsStruct(pstub, str, 5000, 12345.67890) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	/*testing echo Struct as simple types.*/
	ss.varFloat = 12345.67890;
	ss.varInt = 5000;
	ss.varString = strdup("content of string passed");
	printf("invoking echoStructAsSimpleTypes...\n");
	echoStructAsSimpleTypes(pstub, &ss, &outStr, &outInt, &outFloat);
	if (outInt == 5000 && (0 == strcmp(outStr,"content of string passed")) && outFloat > 12345.67)
		printf("successful\n");
	else
		printf("failed\n");	
	/*getchar();*/
	return 0;
}
