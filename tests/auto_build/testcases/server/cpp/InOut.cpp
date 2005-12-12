/*
 * Copyright 2003-2004 The Apache Software Foundation.

 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains definitions of the web service
 */

#include "InOut.hpp"


InOut::InOut()
{
}

InOut::~InOut()
{
}

/* This function is called by the AxisEngine when something went wrong
 with the current web service request processing. Appropriate actions should
 be taken here.*/
void InOut::onFault()
{
}

void InOut::noParametersNoReturn()  
{
}
xsd__int InOut::noParametersIntReturn()  
{
	return 27;
}
void InOut::multiParametersNoReturn(xsd__string Value0, xsd__int Value1, xsd__double Value2)  
{
}
void InOut::multiParametersMultiReturn(xsd__string Value0,xsd__int Value1,xsd__double Value2, AXIS_OUT_PARAM xsd__string *OutValue0, AXIS_OUT_PARAM xsd__int *OutValue1, AXIS_OUT_PARAM xsd__double *OutValue2)  
{
	*OutValue0 = Value0;
	*OutValue1 = Value1;
	*OutValue2 = Value2;
}

ComplexType2* InOut::complexParameterComplexReturn(ComplexType2* Value0)  
{
	ComplexType2* outParam = new ComplexType2();
	outParam = Value0;
	return outParam;
}
xsd__int InOut::multiComplexParametersIntReturn(xsd__string Value0, ComplexType1* Value1, xsd__int Value2, xsd__double Value3, xsd__string_Array * Value4)  
{
	return (Value3 + Value2 +1);
}

void InOut::multiComplexParametersMultiComplexReturn(xsd__string Value0,ComplexType1* Value1,xsd__int Value2,xsd__double Value3,xsd__string_Array * Value4, AXIS_OUT_PARAM xsd__string *OutValue0, AXIS_OUT_PARAM ComplexType1* *OutValue1, AXIS_OUT_PARAM xsd__int *OutValue2, AXIS_OUT_PARAM xsd__double *OutValue3)  
{
	*OutValue0 = Value0;
	*OutValue1 = Value1;
	*OutValue2 = Value2;
	*OutValue3 = Value3;

}

xsd__int InOut::multiComplexParametersNilIntReturn(xsd__string Value0, ComplexNilType1* Value1, xsd__int * Value2, xsd__double * Value3, xsd__string_Array * Value4)  
{
	return 42;
}
xsd__int InOut::multiArrayParametersIntReturn(xsd__int_Array * Value0, xsd__double_Array * Value1, xsd__string_Array * Value2)  
{
	return 43;
}
