/* -*- C++ -*- */
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
 *
 */
 
#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#if !defined(__HANDLER_OF_AXIS_INCLUDED__)
#define __HANDLER_OF_AXIS_INCLUDED__

#include "BasicHandler.h"
#include <map>
/*
#ifdef _DEBUG
#include "AxisTrace.h"
#endif 
*/
using namespace std;
/**
    @class Handler
    @brief interface for handlers
    @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
*/
class Handler : public HandlerBase
{
public:
	Handler(){};
	virtual ~Handler(){};
	virtual const string& getOption(const string& sArg)=0;
	virtual void setOptionList(const map<string, string>* OptionList)=0;
	int AXISCALL getType(){return NORMAL_HANDLER;};

protected:
  const map<string, string>* m_pOption;
};

#endif /*__HANDLER_OF_AXIS_INCLUDED__*/
