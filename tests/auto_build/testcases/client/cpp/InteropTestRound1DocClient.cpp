// InteropBaseClient.cpp : Defines the entry point for the console application.
//
#include <string>
using namespace std;

#include "InteropTestPortType.h" 

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char endpoint[256];
	const char* server="localhost";
	const char* port="80";
	sprintf(endpoint, "http://%s:%s/axis/base", server, port);
	try
	{
	   InteropTestPortType ws(endpoint, APTHTTP);


	ws.setTransportTimeout(5);
	
	printf("invoking echoString...\n");
	//testing echoString 
	string bigstring;
	for (int ii=0;ii<2;ii++)
	{
		bigstring += "hello world ";
	}
	strcpy(buffer1, bigstring.c_str());
	printf(ws.echoString(buffer1));
	if (0 == strcmp(ws.echoString("hello world"), "hello world"))
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoStringArray 
	xsd__string_Array arrstr;
	arrstr.m_Array = new char*[ARRAYSIZE];
	arrstr.m_Size = ARRAYSIZE;
	sprintf(buffer1, "%dth element of string array", 0);
	//sprintf(buffer2, "%dth element of string array", 1);
	for(int i=0; i< ARRAYSIZE; i++)
	{
		arrstr.m_Array[i] = buffer1;
	}
	//arrstr.m_Array[1] = buffer2;
	printf("invoking echoStringArray...\n");
	if (ws.echoStringArray(arrstr).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoInteger 
	printf("invoking echoInteger...\n");
	if (ws.echoInteger(56) == 56)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoIntegerArray 
	xsd__int_Array arrint;
	arrint.m_Array = new int[ARRAYSIZE];
	arrint.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrint.m_Array[x] = x;
	}
	printf("invoking echoIntegerArray...\n");
	if (ws.echoIntegerArray(arrint).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoFloat 
	printf("invoking echoFloat...\n");
	float fvalue = 1.4214;
	if (ws.echoFloat(fvalue) > 1.42)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoFloat 
	xsd__float_Array arrfloat;
	arrfloat.m_Array = new float[ARRAYSIZE];
	arrfloat.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrfloat.m_Array[x] = 1.1111*x;
	}
	printf("invoking echoFloatArray...\n");
	if (ws.echoFloatArray(arrfloat).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	// testing echo Struct
	SOAPStruct stct;
	stct.varFloat = 12345.7346345;
	stct.varInt = 5000;
	stct.varString = strdup("This is string in SOAPStruct");
	printf("invoking echoStruct...\n");
	if (ws.echoStruct(&stct) != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo Array of Struct
	SOAPStruct_Array arrstct;
	arrstct.m_Array = new SOAPStruct[ARRAYSIZE];
	arrstct.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrstct.m_Array[x].varFloat = 1.1111*x;
		arrstct.m_Array[x].varInt = x;
		sprintf(buffer1, "varString of %dth element of SOAPStruct array", x);
		arrstct.m_Array[x].varString = buffer1;
	}
	//testing echo Struct Array
	printf("invoking echoStructArray...\n");
	if (ws.echoStructArray(arrstct).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo void
	printf("invoking echoVoid...\n");
	ws.echoVoid();
	printf("successful\n");
	//testing echo base 64 binary

	const char* bstr = "some string that is sent encoded to either base64Binary or hexBinary";

	printf("invoking echoBase64...\n");
	xsd__base64Binary bb;
	bb.__ptr = (unsigned char*)strdup(bstr);
	bb.__size = strlen(bstr);
	if (bb.__size == ws.echoBase64(bb).__size)
	{
		printf("successful\n");
		printf("Returned String :\n%s\n", bb.__ptr);
	}
	else
		printf("failed\n");

	time_t tim;
	time(&tim);
	tm* lt = gmtime(&tim);
	printf("invoking echoDate...\n");
	if (memcmp(&ws.echoDate(*lt), lt, sizeof(tm)) == 0)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo hex binary

	printf("invoking echoHexBinary...\n");
	xsd__hexBinary hb;
	hb.__ptr = (unsigned char*)strdup(bstr);
	hb.__size = strlen(bstr);
	if (hb.__size == ws.echoHexBinary(hb).__size)
	{
		printf("successful\n");
		printf("Returned String :\n%s\n", hb.__ptr);
	}
	else
		printf("failed\n");
	//testing echo decimal
	printf("invoking echoDecimal...\n");
	if (ws.echoDecimal(1234.567890) > 1234.56)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo boolean
	printf("invoking echoBoolean...\n");
	if (ws.echoBoolean(true_) == true_)
		printf("successful\n");
	else
		printf("failed\n");
	}
	catch(AxisException& e)
	{
		printf("%s\n", e.what());
	}
	catch(exception& e)
	{
		printf("%s\n", e.what());
	}
	catch(...)
	{
		printf("Unknown exception has occured\n");
	}
	//getchar();
	return 0;
}
