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
 * RefTestPortType.h: interface for the RefTestPortTypeclass.
 *
 */
#if !defined(__REFTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_)
#define __REFTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_

#include <axis/AxisUserAPI.hpp>
#include "AxisServiceException.h" 

#include "intType.h"

class RefTestPortType 
{
	public:
		RefTestPortType();
	public:
		virtual ~RefTestPortType();
	public: 
		void onFault();
		void init();
		void fini();
		intType* echoInt(intType* Value0);
};

#endif /* !defined(__REFTESTPORTTYPE_SERVERSKELETON_H__INCLUDED_)*/
