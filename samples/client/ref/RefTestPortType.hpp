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
 * This file was auto-generated by the Axis C++ Web Service Generator (WSDL2Ws)
 * This file contains Client Stub Class for remote web service 
 */

#if !defined(__REFTESTPORTTYPE_CLIENTSTUB_H__INCLUDED_)
#define __REFTESTPORTTYPE_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Stub.hpp>
#include <axis/SoapFaultException.hpp>
#include <axis/ISoapFault.hpp>
AXIS_CPP_NAMESPACE_USE
#include "intType.hpp"

class RefTestPortType :public Stub
{
public:
	STORAGE_CLASS_INFO RefTestPortType(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol=APTHTTP1_1);
	STORAGE_CLASS_INFO RefTestPortType();
public:
	STORAGE_CLASS_INFO virtual ~RefTestPortType();
public: 
	STORAGE_CLASS_INFO intType* echoInt(intType* Value0);
};

#endif /* !defined(__REFTESTPORTTYPE_CLIENTSTUB_H__INCLUDED_)*/
