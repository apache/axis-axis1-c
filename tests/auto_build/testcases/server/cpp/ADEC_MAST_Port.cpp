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

#include "ADEC_MAST_Port.hpp"


ADEC_MAST_Port::ADEC_MAST_Port()
{
}

ADEC_MAST_Port::~ADEC_MAST_Port()
{
}

/* This function is called by the AxisEngine when something went wrong
 with the current web service request processing. Appropriate actions should
 be taken here.*/
void ADEC_MAST_Port::onFault()
{
}

SummaryResult* ADEC_MAST_Port::doGetSummary(xsd__string Value0, xsd__int Value1, xsd__double Value2, xsd__int Value3)  
{
	SummaryResult* outParam = new SummaryResult();
	int square = 0;
	double cal = 0;
	square = (Value1 * Value3);
	cal = (Value1 * Value2 * Value3);
	outParam->NonAllIntValue = square;
	outParam->NonAllDoubleValue = cal;
	outParam->length = new int;
	*(outParam->length) = Value1;
	outParam->depth = new double;
	*(outParam->depth) = Value2;
	outParam->color = Value0;

	if(cal != 0)
		outParam->NonAllStringValue = "Success";
	else
		outParam->NonAllStringValue = "Failed";

	return outParam;

}
