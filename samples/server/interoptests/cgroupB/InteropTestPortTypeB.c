/*
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains definitions of the web service
 */

#include <axis/server/AxisUserAPI.h>
#include "SOAPArrayStruct.h"
#include "SOAPStruct.h"
#include "SOAPStructStruct.h"


void echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM xsd__string *OutValue0, AXIS_OUT_PARAM int *OutValue1, AXIS_OUT_PARAM float *OutValue2)
{	*OutValue0 = Value0->SOAPStruct_varString;
	*OutValue1 = Value0->SOAPStruct_varInt;
	*OutValue2 = Value0->SOAPStruct_varFloat;
}
SOAPStruct* echoSimpleTypesAsStruct(xsd__string Value0,int Value1,float Value2)
{	SOAPStruct* pRet = (SOAPStruct*) malloc(sizeof(SOAPStruct));
	pRet->SOAPStruct_varString = Value0;
	pRet->SOAPStruct_varInt = Value1;
	pRet->SOAPStruct_varFloat = Value2;
	return pRet;
}
SOAPStructStruct* echoNestedStruct(SOAPStructStruct* Value0)
{	return Value0;
}
SOAPArrayStruct* echoNestedArray(SOAPArrayStruct* Value0)
{	return Value0;
}
