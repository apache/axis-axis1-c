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

/////////////////////////////////////////////////////////////////////////////
// This is the Client Stub Class genarated by the tool WSDL2Ws
// InteropTestPortType.h: interface for the InteropTestPortTypeclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_

#include <axis/client/Stub.hpp>
#include "SOAPStruct.h"
#include "ArrayOffloat.h"
#include "ArrayOfSOAPStruct.h"
#include "ArrayOfint.h"
#include "ArrayOfstring.h"

class InteropTestPortType 
{
private:
	Call* m_pCall;
public:
	InteropTestPortType(const char* pchEndPointUri);
public:
	virtual ~InteropTestPortType();
public: 
	AxisChar* echoString(AxisChar* Value0);
	ArrayOfstring echoStringArray(ArrayOfstring Value0);
	int echoInteger(int Value0);
	ArrayOfint echoIntegerArray(ArrayOfint Value0);
	float echoFloat(float Value0);
	ArrayOffloat echoFloatArray(ArrayOffloat Value0);
	SOAPStruct* echoStruct(SOAPStruct* Value0);
	ArrayOfSOAPStruct echoStructArray(ArrayOfSOAPStruct Value0);
	void echoVoid();
	xsd__base64Binary echoBase64(xsd__base64Binary Value0);
	xsd__dateTime echoDate(xsd__dateTime Value0);
	xsd__hexBinary echoHexBinary(xsd__hexBinary Value0);
	xsd__decimal echoDecimal(xsd__decimal Value0);
	xsd__boolean echoBoolean(xsd__boolean Value0);
};

#endif // !defined(__INTEROPTESTPORTTYPE_CLIENTSTUB_H__OF_AXIS_INCLUDED_)
