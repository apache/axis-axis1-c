// InteropGroupBClient.cpp : Defines the entry point for the console application.
//
#include "InteropTestPortTypeB.h"
#include <axis/AxisGenException.h>

#define ARRAYSIZE 5

int main(int argc, char* argv[])
{
	int x;
	char endpoint[256];
	const char* server="localhost";
	const char* port="80";
	if (argc == 3)
	{
		server = argv[1];
		port = argv[2];
	}
	printf("Usage :\n %s <server> <port>\n\n", argv[0]);
	printf("Sending Requests to Server http://%s:%s ........\n\n", server, port);
	sprintf(endpoint, "http://%s:%s/axis/groupB", server, port);	
        try
	{
	InteropTestPortTypeB ws(endpoint);
	/*we do not support multi-dimensional arrays.*/
	/*ws.echo2DStringArray*/

	/*testing Nested Arrays*/
	SOAPArrayStruct sas;
	sas.SOAPArrayStruct_varFloat = 12345.67890;
	sas.SOAPArrayStruct_varInt = 5000;
	sas.SOAPArrayStruct_varString = strdup("varString content of SOAPArrayStruct");
	sas.SOAPArrayStruct_varArray.m_Array = new AxisChar*[ARRAYSIZE];
	sas.SOAPArrayStruct_varArray.m_Size = ARRAYSIZE;
	for (x=0; x<ARRAYSIZE; x++)
	{
		sas.SOAPArrayStruct_varArray.m_Array[x] = strdup("content of string array element");
	}
	printf("invoking echoNestedArray...\n");
	if (ws.echoNestedArray(&sas) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	/*testing Nested Structs*/
	SOAPStructStruct sss;
	sss.SOAPStructStruct_varFloat = 12345.67890;
	sss.SOAPStructStruct_varInt = 5000;
	sss.SOAPStructStruct_varString = strdup("varString content of SOAPStructStruct");
	sss.SOAPStructStruct_varStruct = new SOAPStruct();
	sss.SOAPStructStruct_varStruct->SOAPStruct_varFloat = 67890.12345;
	sss.SOAPStructStruct_varStruct->SOAPStruct_varInt = 54321;
	sss.SOAPStructStruct_varStruct->SOAPStruct_varString = strdup("varString content of SOAPStruct");
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
	ss.SOAPStruct_varFloat = 12345.67890;
	ss.SOAPStruct_varInt = 5000;
	ss.SOAPStruct_varString = strdup("content of string passed");
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
