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
	if (argc == 3)
	{
		server = argv[1];
		port = argv[2];
	}
	printf("Usage :\n %s <server> <port>\n\n", argv[0]);
	//sprintf(endpoint, "http://%s:%s/axis/base", server, port);
	sprintf(endpoint, "http://%s:%s/axis/services/echo", server, port);
	InteropTestPortType ws(endpoint);
	
	//set end point (optional) 
	//ws.setEndPoint( "http://localhost:8080/axis/services/echo" );
	
	//set HTTP headers
	ws.setTransportProperty( "Accept-Language", " da, en-gb;q=0.8, en;q=0.7" );
	ws.setTransportProperty( "Accept-Language2", " my da, en-gb;q=0.8, en;q=0.7" );
	
	//set SOAP headers
	IHeaderBlock* phb = ws.createHeaderBlock( "Trans", "m", "http://ws.apache.org/axisCppTest/" );
	phb = ws.createHeaderBlock( "Trans2", "m2", "http://ws.apache.org/axisCppTest2/" );
	
	//BasicNode* bn = phb->createChild(CHARACTER_NODE);//, NULL, NULL, NULL, "test" );
	//bn->setValue( "1010" );
	//phb->addChild( bn );
	//phb->setLocalName( "newName" );

	printf("Sending Requests to end point %s \n\n", endpoint);
	printf("invoking echoString...\n");
	//testing echoString 
	string bigstring;
	for (int ii=0;ii<2;ii++)
	{
		bigstring += "hello world ";
	}
	strcpy(buffer1, bigstring.c_str());
	//printf(ws.echoString(buffer1));
	if (0 == strcmp(ws.echoString("hello world"), "hello world"))
		printf("successful\n");
	else
		printf("failed\n");
	// testing echoStringArray 
	xsd__string_Array arrstr;
	arrstr.m_Array = new char*[ARRAYSIZE];
	arrstr.m_Size = ARRAYSIZE;
	for(int i=0; i< ARRAYSIZE; i++)
	{
		sprintf(buffer1, "%dth element of string array", i + 1);
		arrstr.m_Array[i] = buffer1;
	}
	printf("invoking echoStringArray...\n");
	if (ws.echoStringArray(arrstr).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	
	printf( "Stub Base class test end\n");
	return 0;
}
