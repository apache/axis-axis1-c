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
	/* testing echoStringArray */
	arrstr.m_Array = malloc(sizeof(char*)*ARRAYSIZE);
	arrstr.m_Size = ARRAYSIZE;
	for(x=0; x< ARRAYSIZE; x++)
	{
		sprintf(buffer1, "%dth element of string array", 0);
		arrstr.m_Array[x] = strdup(buffer1);
	}
	/*arrstr.m_Array[1] = buffer2;*/
	printf("invoking echoStringArray...\n");
	if (echoStringArray(pstub, arrstr).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	/* testing echoInteger */
	printf("invoking echoInteger...\n");
	if (echoInteger(pstub, 56) == 56)
		printf("successful\n");
	else
		printf("failed\n");
	/* testing echoIntegerArray */
	arrint.m_Array = malloc(sizeof(int)*ARRAYSIZE);
	arrint.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrint.m_Array[x] = x;
	}
	printf("invoking echoIntegerArray...\n");
	if (echoIntegerArray(pstub, arrint).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	/* testing echoFloat */
	printf("invoking echoFloat...\n");
	if (echoFloat(pstub, 1.4214) > 1.42)
		printf("successful\n");
	else
		printf("failed\n");
	/* testing echoFloat */
	arrfloat.m_Array = malloc(sizeof(float)*ARRAYSIZE);
	arrfloat.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrfloat.m_Array[x] = 1.1111*x;
	}
	printf("invoking echoFloatArray...\n");
	if (echoFloatArray(pstub, arrfloat).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	/* testing echo Struct*/
	stct.varFloat = 12345.7346345;
	stct.varInt = 5000;
	stct.varString = strdup("This is string in SOAPStruct");
	printf("invoking echoStruct...\n");
	if (echoStruct(pstub, &stct) != NULL)
		printf("successful\n");
	else
		printf("failed\n");
	/*testing echo Array of Struct*/
	arrstct.m_Array = malloc(sizeof(SOAPStruct)*ARRAYSIZE);
	arrstct.m_Size = ARRAYSIZE;
	for (x=0;x<ARRAYSIZE;x++)
	{
		arrstct.m_Array[x].varFloat = 1.1111*x;
		arrstct.m_Array[x].varInt = x;
		sprintf(buffer1, "varString of %dth element of SOAPStruct array", x);
		arrstct.m_Array[x].varString = buffer1;
	}
	
	/*testing echo Struct Array*/
	printf("invoking echoStructArray...\n");
	if (echoStructArray(pstub, arrstct).m_Array != NULL)
		printf("successful\n");
	else
		printf("failed\n");		
	/*testing echo void*/
	
	printf("invoking echoVoid...\n");
	echoVoid(pstub);
	printf("successful\n");
	
	/*testing echo base 64 binary*/
/*	printf("invoking echoBase64...\n");
	if (0 == strcmp(ws.echoBase64(pstub, "BCDF675E234242WHRTKMJDGKGUEJ898636JFJFHEJDGWTDHFJRURYGBCDHTWRSG"),
		"BCDF675E234242WHRTKMJDGKGUEJ898636JFJFHEJDGWTDHFJRURYGBCDHTWRSG"))
		printf("successful\n");
	else
		printf("failed\n");
	time(&tim);
	lt = gmtime(&tim);
	printf("invoking echoDate...\n");
	if (memcmp(&(echoDate(pstub, *lt)), lt, sizeof(tm)) == 0)
		printf("successful\n");
	else
		printf("failed\n");
	//testing echo hex binary
	printf("invoking echoHexBinary...\n");
	if (0 == strcmp(echoHexBinary(pstub, "CCCFFA46552BC7D5A09BC5F23DE9E0FE7862AD45BC87D02FEE"),
		"CCCFFA46552BC7D5A09BC5F23DE9E0FE7862AD45BC87D02FEE"))
		printf("successful\n");
	else
		printf("failed\n");
*/	/*testing echo decimal*/
	printf("invoking echoDecimal...\n");
	if (echoDecimal(pstub, 1234.567890) > 1234.56)
		printf("successful\n");
	else
		printf("failed\n");
		
	/*testing echo boolean*/
	printf("invoking echoBoolean...\n");
	if (echoBoolean(pstub, true_) == true_)
		printf("successful\n");
	else
		printf("failed\n");
		
	getchar();	
	destroy_InteropTestPortType_stub(pstub);
}
