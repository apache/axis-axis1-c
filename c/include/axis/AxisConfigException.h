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
 
#ifndef __AXISCONFIGEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISCONFIGEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>
#include <axis/server/AxisException.h>
using namespace std;

class STORAGE_CLASS_INFO AxisConfigException :public AxisException
{

public:
    AxisConfigException();
    AxisConfigException(const int iExceptionCode);
    AxisConfigException(const int iExceptionCode, char* pcMessage);
    AxisConfigException(const exception* e);
    AxisConfigException(const exception* e, const int iExceptionCode);
    virtual ~AxisConfigException() throw();
    const char* what() throw();
    const int getExceptionCode();
    const string& getMessage(const exception* e);
    const string& getMessage(const int iExceptionCode);
private:
    void processException(const exception* e);
    void processException(const exception* e, const int iExceptionCode);
    void processException(const int iExceptionCode);
    void processException(const int iExceptionCode, char* pcMessage); 
    string m_sMessage;
    int m_iExceptionCode;
};

#endif

