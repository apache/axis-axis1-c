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

#if !defined(__MATHOPSWRAPPER_SERVERWRAPPER_H__INCLUDED_)
#define __MATHOPSWRAPPER_SERVERWRAPPER_H__INCLUDED_

#include "MathOps.h"
#include <axis/server/WrapperClassHandler.hpp>
#include <axis/server/IMessageData.hpp>
#include <axis/server/GDefine.hpp>
#include <axis/server/AxisWrapperAPI.hpp>
#include "AxisServiceException.h"

class MathOpsWrapper : public WrapperClassHandler
{
private:/* Actual web service object*/
	MathOps *pWs;
public:
	MathOpsWrapper();
public:
	virtual ~MathOpsWrapper();
public:/*implementation of WrapperClassHandler interface*/
	int AXISCALL invoke(void* pMsg);
	void AXISCALL onFault(void* pMsg);
	int AXISCALL init();
	int AXISCALL fini();
	AXIS_BINDING_STYLE AXISCALL getBindingStyle(){return RPC_ENCODED;};
private:/*Methods corresponding to the web service methods*/
	int div(void* pMsg);
};

#endif /* !defined(__MATHOPSWRAPPER_SERVERWRAPPER_H__INCLUDED_)*/
