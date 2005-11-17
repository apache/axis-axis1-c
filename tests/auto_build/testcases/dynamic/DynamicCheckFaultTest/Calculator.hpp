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
 * This is a manually edited version of the Generated stub code for CaluclatorDoc.wsdl
 * to simplify the code to allow the cpp file to be edited to be used as a dynamic client
 */
#if !defined(__CALCULATOR_CLIENT_H__INCLUDED_)
#define __CALCULATOR_CLIENT_H__INCLUDED_
#include <axis/AxisException.hpp>
#include <axis/client/Call.hpp>
#include <iostream>
#include <string>
#include <exception>
using namespace std;
AXIS_CPP_NAMESPACE_USE 

class Calculator
{
public:
	STORAGE_CLASS_INFO Calculator(const char* pchEndpointUri, AXIS_PROTOCOL_TYPE eProtocol=APTHTTP1_1);
	STORAGE_CLASS_INFO Calculator();
public:
	STORAGE_CLASS_INFO virtual ~Calculator();
public: 
	STORAGE_CLASS_INFO void SetSecure( char *, ...);
	STORAGE_CLASS_INFO xsd__int div(xsd__int Value0,xsd__int Value1);	

private:
	void includeSecure();
	Call *m_pCall;

protected:
	std::string sArguments[8];
};

#endif /* !defined(__CALCULATOR_CLIENT_H__INCLUDED_)*/
