// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 *		CalculatorWrapper.h: interface for the CalculatorWrapperclass.
 *
 */
#if !defined(__CALCULATORWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
#define __CALCULATORWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_

#include "Calculator.h"
#include <axis/server/WrapperClassHandler.hpp>
#include <axis/IMessageData.hpp>
#include <axis/GDefine.hpp>
#include <axis/AxisWrapperAPI.hpp>
AXIS_CPP_NAMESPACE_USE

class CalculatorWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	Calculator *pWs;
public:
	CalculatorWrapper();
public:
	virtual ~CalculatorWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL invoke(void* pMsg);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int add(void* pMsg);
	int sub(void* pMsg);
	int mul(void* pMsg);
	int div(void* pMsg);
};

#endif /* !defined(__CALCULATORWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)*/
