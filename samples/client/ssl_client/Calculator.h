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
 * This is the Client Stub Class genarated by the tool WSDL2Ws
 * Calculator.h: interface for the Calculatorclass.
 *
 */
#if !defined(__CALCULATOR_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
#define __CALCULATOR_CLIENTSTUB_H__OF_AXIS_INCLUDED_

#include <axis/client/Stub.hpp>
#include <axis/client/Call.hpp>
#include <ctype.h>

AXIS_CPP_NAMESPACE_USE

class Calculator 
{
private:
	Call* m_pCall;
public:
	Calculator(const char* pchEndpointUri);
public:
	virtual ~Calculator();
public: 
	int add(int Value0,int Value1);
	int sub(int Value0,int Value1);
	int mul(int Value0,int Value1);
	int div(int Value0,int Value1);
        int getFaultDetail(char** ppcDetail);
};

#endif /* !defined(__CALCULATOR_CLIENTSTUB_H__OF_AXIS_INCLUDED_)*/
