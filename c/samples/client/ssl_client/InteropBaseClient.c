/* InteropBaseClient.cpp : Defines the entry point for the console application.*/


#include "InteropTestPortType.h" 
#include <stdio.h>
#include <string.h>

#define ARRAYSIZE 2

int main(int argc, char* argv[])
{
	int x;
	char buffer1[100];
	char buffer2[100];
	xsd__string_Array arrstr;
	xsd__int_Array arrint;
	xsd__float_Array arrfloat;
	SOAPStruct_Array arrstct;
	SOAPStruct stct;
	time_t tim;
	struct tm* lt;
	void* pstub = get_InteropTestPortType_stub();
	printf("invoking echoString...\n");
	/*testing echoString */
	if (0 == strcmp(echoString(pstub, "hello world"), "hello world"))
		printf("successful\n");
	else
		printf("failed\n");

	destroy_InteropTestPortType_stub(pstub);
}
