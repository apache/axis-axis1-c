/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 *   @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#if !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)
#define __MATHOPS_CLIENTSTUB_H__INCLUDED_

#include <axis/client/Call.h>
/*include Exception header files here*/
#include "AxisDivByZeroException.h"
#include "DivByZeroStruct.h"

class MathOps 
{
private:
	Call* m_pCall;
public:
	MathOps(const char* pchEndpointUri);
public:
	virtual ~MathOps();
public: 
	int div(int Value0,int Value1);
	int getStatus();
	int getFaultDetail(char** ppcDetail);
};

#endif /* !defined(__MATHOPS_CLIENTSTUB_H__INCLUDED_)*/
