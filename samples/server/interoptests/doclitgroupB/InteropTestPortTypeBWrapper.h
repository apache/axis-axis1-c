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

/////////////////////////////////////////////////////////////////////////////
// This is the Service Class genarated by the tool WSDL2Ws
//		InteropTestPortTypeBWrapper.h: interface for the InteropTestPortTypeBWrapperclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_

#include "InteropTestPortTypeB.h"
#include <axis/server/WrapperClassHandler.hpp>
#include <axis/IMessageData.hpp>
#include <axis/GDefine.hpp>
#include <axis/IWrapperSoapDeSerializer.hpp>
#include <axis/IWrapperSoapSerializer.hpp>

AXIS_CPP_NAMESPACE_USE

class InteropTestPortTypeBWrapper : public WrapperClassHandler
{
private:// Actual web service object
	InteropTestPortTypeB *pWs;
public:
	InteropTestPortTypeBWrapper();
public:
	virtual ~InteropTestPortTypeBWrapper();
public://implementation of WrapperClassHandler interface
	int AXISCALL invoke(void* mc);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return DOC_LITERAL;};
private://Methods corresponding to the web service methods
	int echoStructAsSimpleTypes(IMessageData* mc);
	int echoSimpleTypesAsStruct(IMessageData* mc);
	int echo2DStringArray(IMessageData* mc);
	int echoNestedStruct(IMessageData* mc);
	int echoNestedArray(IMessageData* mc);
};

#endif // !defined(__INTEROPTESTPORTTYPEBWRAPPER_SERVERWRAPPER_H__OF_AXIS_INCLUDED_)
