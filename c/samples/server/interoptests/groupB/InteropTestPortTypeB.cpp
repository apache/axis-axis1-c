/*
 *This is the Service implementation CPP file genarated by theWSDL2Ws.
 *		InteropTestPortTypeB.cpp: implemtation for the InteropTestPortTypeB.
 *
 */
#include "InteropTestPortTypeB.h"


InteropTestPortTypeB::InteropTestPortTypeB()
{
}

InteropTestPortTypeB::~InteropTestPortTypeB()
{
}

void InteropTestPortTypeB::echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM float *OutValue0, AXIS_OUT_PARAM int *OutValue1, AXIS_OUT_PARAM xsd__string *OutValue2)
{
	*OutValue0 = Value0->varFloat;
	*OutValue1 = Value0->varInt;
	*OutValue2 = Value0->varString;
}
SOAPStruct* InteropTestPortTypeB::echoSimpleTypesAsStruct(float Value0, int Value1, xsd__string Value2)
{
	SOAPStruct* pRet = new SOAPStruct();
	pRet->varFloat = Value0;
	pRet->varInt = Value1;
	pRet->varString = Value2;
	return pRet;
}
SOAPStructStruct* InteropTestPortTypeB::echoNestedStruct(SOAPStructStruct* Value0)
{
	return Value0;
}
SOAPArrayStruct* InteropTestPortTypeB::echoNestedArray(SOAPArrayStruct* Value0)
{
	return Value0;
}
