///////////////////////////////////////////////////////////////////////
//This is the Service implementation CPP file genarated by theWSDL2Ws.
//		InteropTestPortTypeB.cpp: implemtation for the InteropTestPortTypeB.
//
//////////////////////////////////////////////////////////////////////
#include "InteropTestPortTypeB.h"


InteropTestPortTypeB::InteropTestPortTypeB()
{
}

InteropTestPortTypeB::~InteropTestPortTypeB()
{
}

void InteropTestPortTypeB::echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM AxisChar** outValue0, AXIS_OUT_PARAM int* outValue1, AXIS_OUT_PARAM float* outValue2)
{
	*outValue0 = Value0->varString;
	*outValue1 = Value0->varInt;
	*outValue2 = Value0->varFloat;
}
SOAPStruct* InteropTestPortTypeB::echoSimpleTypesAsStruct(float Value0, int Value1, AxisChar* Value2)
{
	SOAPStruct* pRet = new SOAPStruct();
	pRet->varFloat = Value0;
	pRet->varInt = Value1;
	pRet->varString = Value2;
	return pRet;
}
ArrayOfString2D InteropTestPortTypeB::echo2DStringArray(ArrayOfString2D Value0)
{
	return Value0;
}
SOAPStructStruct* InteropTestPortTypeB::echoNestedStruct(SOAPStructStruct* Value0)
{
	return Value0;
}
SOAPArrayStruct* InteropTestPortTypeB::echoNestedArray(SOAPArrayStruct* Value0)
{
	return Value0;
}
