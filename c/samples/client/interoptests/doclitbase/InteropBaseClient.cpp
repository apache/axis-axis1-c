// InteropBaseClient.cpp : Defines the entry point for the console application.
//

#include "InteropTestPortType.h" 

#define ARRAYSIZE 2
#define LOOPFOR 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[1000];
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
	sprintf(endpoint, "http://%s:%s/axis/baseDL", server, port);	
	
	InteropTestPortType ws(endpoint);
	
	printf("invoking echoString...\n");
	//testing echoString 
	AxisChar* pachEchoStringResult = ws.echoString("hello world");
	if ( (pachEchoStringResult != NULL) && (0 == strcmp(pachEchoStringResult, "hello world")) )
		printf("successful\n");
	else
		printf("failed\n");
	
	// testing echoStringArray 
	ArrayOfstring arrstr;
	arrstr.m_Array = new char*[ARRAYSIZE];
	arrstr.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		sprintf(buffer1, "%dth element <@#$%^&*()~`'\"?/><.,-_=+ ][}{|of string array", x);
		arrstr.m_Array[x] = strdup(buffer1);
	}
	printf("invoking echoStringArray...\n");
	for(int ix=0;ix<LOOPFOR; ix++)
	{
		ArrayOfstring retarrstr = ws.echoStringArray(arrstr);
		if ((retarrstr.m_Array != NULL) && (retarrstr.m_Size == ARRAYSIZE)) {
			for (x=0;x<ARRAYSIZE;x++)
			{
			//	printf("%s\n", retarrstr.m_Array[x]);
				free(retarrstr.m_Array[x]);
			}
			free(retarrstr.m_Array);
			printf("successful\n");
		
		}
		else
			printf("failed\n");
	}
	printf("Done\n");
	

	
	// testing echoInteger 
	printf("invoking echoInteger...\n");
	if (ws.echoInteger(56) == 56)
		printf("successful\n");
	else
		printf("failed\n");

	
	
	// testing echoIntegerArray 
	ArrayOfint arrint;
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
	if (ws.echoFloat(1.4214) > 1.42)
		printf("successful\n");
	else
		printf("failed\n");
	
	
	// testing echoFloat 
	ArrayOffloat arrfloat;
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
	stct.varString = "This is string in SOAPStruct";
	printf("invoking echoStruct...\n");
	if (ws.echoStruct(&stct) != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	
	
	//testing echo Array of Struct
	ArrayOfSOAPStruct arrstct;
	arrstct.m_Array = new SOAPStruct[ARRAYSIZE];
	arrstct.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrstct.m_Array[x].varFloat = 1.1111*x;
		arrstct.m_Array[x].varInt = x;
		sprintf(buffer1, "varString of %dth element of SOAPStruct array", x);
		arrstct.m_Array[x].varString = strdup(buffer1);
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
	printf("invoking echoBase64...\n");
	const char* bstr = "some string that is sent encoded to either base64Binary or hexBinary";

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
		
	getchar();
	return 0;
}