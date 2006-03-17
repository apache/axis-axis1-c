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
 
#ifndef __AXISWSDDEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISWSDDEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>
#include <axis/AxisException.hpp>

AXIS_CPP_NAMESPACE_START

using namespace std;

class STORAGE_CLASS_INFO AxisWsddException :public AxisException
{

public:
    AxisWsddException(const int iExceptionCode,const char* pcMessage = NULL);
    AxisWsddException(const AxisWsddException& e);
    virtual ~AxisWsddException() throw();
    
private:
    string getMessageForExceptionCode(const int iExceptionCode);
    const char* what() const throw(){ return m_sMessage; };
    string m_sMessageForExceptionCode;
};

AXIS_CPP_NAMESPACE_END

#endif

