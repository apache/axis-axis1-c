// InteropGroupBClient.cpp : Defines the entry point for the console application.
//
#include "InteropTestPortTypeB.h"

#define ARRAYSIZE 5

int main(int argc, char* argv[])
{
	int x;
	InteropTestPortTypeB ws;
	//we do not support multi-dimensional arrays.
	//ws.echo2DStringArray

	//testing Nested Arrays
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

	//testing Nested Structs
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

	//testing echo Simple types as struct
	char* str = strdup("content of string passed");
	printf("invoking echoSimpleTypesAsStruct...\n");
	if (ws.echoSimpleTypesAsStruct(12345.67890, 5000, str) != NULL)
		printf("successful\n");
	else
		printf("failed\n");

	//testing echo Struct as simple types.
	SOAPStruct ss;
	ss.varFloat = 12345.67890;
	ss.varInt = 5000;
	ss.varString = strdup("content of string passed");
	char* outStr;
	int outInt;
	float outFloat;
	printf("invoking echoStructAsSimpleTypes...\n");
	ws.echoStructAsSimpleTypes(&ss, &outStr, &outInt, &outFloat);
	if (outInt == 5000 && (0 == strcmp(outStr,"content of string passed")) && outFloat > 12345.67)
		printf("successful\n");
	else
		printf("failed\n");	
	getchar();
	return 0;
}
