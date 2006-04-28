// Copyright 2003-2004 The Apache Software Foundation.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*
 *This is the Service implementation CPP file genarated by theWSDL2Ws.
 *		Calculator.cpp: implemtation for the Calculator.
 *
 */
#include "Calculator.hpp"

void Calculator::onFault(){}

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

xsd__int Calculator::add( xsd__int Value0, xsd__int Value1)
{
	return Value0 + Value1;
}
xsd__int Calculator::sub( xsd__int Value0, xsd__int Value1)
{
	return Value0 - Value1;
}
xsd__int Calculator::mul( xsd__int Value0, xsd__int Value1)
{
	return Value0 * Value1;
}
xsd__int Calculator::div( xsd__int Value0, xsd__int Value1)
{
	if( Value1 == 0)
	{
		return (xsd__int) -1;
	}

	return Value0 / Value1;
}
