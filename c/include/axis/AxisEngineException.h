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
 
#ifndef __AXISENGINEEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISENGINEEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>
#include <exception>
#include <axis/server/AxisException.h>
using namespace std;

class STORAGE_CLASS_INFO AxisEngineException :public AxisException
{

public:
    AxisEngineException();
    AxisEngineException(const int iExceptionCode);
    AxisEngineException(const int iExceptionCode, char* pcMessage);
    AxisEngineException(const exception* e);
    AxisEngineException(const exception* e, const int iExceptionCode);
    virtual ~AxisEngineException() throw();
    const char* what() throw();
    const int getExceptionCode();
                                                                                                                             
private:
    const string getMessage(const exception* e);
    const string getMessage(const int iExceptionCode);
    void processException(const exception* e);
    void processException(const exception* e, const int iExceptionCode);
    void processException(const int iExceptionCode);
    void processException(const int iExceptionCode, char* pcMessage);                                                                                                                           
    string m_sMessage;
    int m_iExceptionCode;
};

#endif

