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
//		InteropTestPortTypeB.h: interface for the InteropTestPortTypeBclass.
//
//////////////////////////////////////////////////////////////////////
#if !defined(__INTEROPTESTPORTTYPEB_SERVERSKELETON_H__OF_AXIS_INCLUDED_)
#define __INTEROPTESTPORTTYPEB_SERVERSKELETON_H__OF_AXIS_INCLUDED_

#include <axis/AxisUserAPI.hpp>

#include "SOAPArrayStruct.h"
#include "SOAPStruct.h"
#include "ArrayOffloat.h"
#include "ArrayOfSOAPStruct.h"
#include "ArrayOfint.h"
#include "ArrayOfString2D.h"
#include "SOAPStructStruct.h"
#include "ArrayOfstring.h"

class InteropTestPortTypeB 
{
	public:
		InteropTestPortTypeB();
	public:
		virtual ~InteropTestPortTypeB();
	public: 
		void echoStructAsSimpleTypes(SOAPStruct* Value0, AXIS_OUT_PARAM AxisChar** outValue0, AXIS_OUT_PARAM int* outValue1, AXIS_OUT_PARAM float* outValue2);
		SOAPStruct* echoSimpleTypesAsStruct(float Value0,int Value1,AxisChar* Value2);
		ArrayOfString2D echo2DStringArray(ArrayOfString2D Value0);
		SOAPStructStruct* echoNestedStruct(SOAPStructStruct* Value0);
		SOAPArrayStruct* echoNestedArray(SOAPArrayStruct* Value0);
};

#endif // !defined(__INTEROPTESTPORTTYPEB_SERVERSKELETON_H__OF_AXIS_INCLUDED_)
