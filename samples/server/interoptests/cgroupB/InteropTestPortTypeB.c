/*
 * This is the Service implementation C file genarated by WSDL2Ws tool.
 * InteropTestPortTypeB.c
 *
 */
#include <axis/server/AxisUserAPI.h>
#include "SOAPArrayStruct.h"
#include "SOAPStruct.h"
#include "SOAPStructStruct.h"


void echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM float *OutValue0, AXIS_OUT_PARAM int *OutValue1, AXIS_OUT_PARAM xsd__string *OutValue2)
{
	*OutValue0 = Value0->varFloat;
	*OutValue1 = Value0->varInt;
	*OutValue2 = Value0->varString;
}
SOAPStruct* echoSimpleTypesAsStruct(float Value0,int Value1,xsd__string Value2)
{
	SOAPStruct* pRet = (SOAPStruct*) malloc(sizeof(SOAPStruct));
	pRet->varFloat = Value0;
	pRet->varInt = Value1;
	pRet->varString = Value2;
	return pRet;
}
SOAPStructStruct* echoNestedStruct(SOAPStructStruct* Value0)
{
	return Value0;
}
SOAPArrayStruct* echoNestedArray(SOAPArrayStruct* Value0)
{
	return Value0;
}
