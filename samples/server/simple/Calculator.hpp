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
 * This is the Service Class genarated by the tool WSDL2Ws
 * Calculator.hpp: interface for the Calculatorclass.
 *
 */
#if !defined(__CALCULATOR_SERVERSKELETON_H__INCLUDED_)
#define __CALCULATOR_SERVERSKELETON_H__INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include "AxisServiceException.hpp" 


class Calculator 
{
	public:
		Calculator();
	public:
		virtual ~Calculator();
	public: 
		void onFault();
		void init();
		void fini();
		xsd__int add(xsd__int Value0,xsd__int Value1);
		xsd__int sub(xsd__int Value0,xsd__int Value1);
		xsd__int mul(xsd__int Value0,xsd__int Value1);
		xsd__int div(xsd__int Value0,xsd__int Value1);
};

#endif /* !defined(__CALCULATOR_SERVERSKELETON_H__INCLUDED_)*/
