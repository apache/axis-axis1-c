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
 
#ifndef __AXISTRANSPORTEXCEPTION_H_OF_AXIS_INCLUDED_
#define __AXISTRANSPORTEXCEPTION_H_OF_AXIS_INCLUDED_

#include <string>
#include <exception>
#include <axis/server/AxisException.h>
using namespace std;

class AxisTransportException :public AxisException
{

public:
    AxisTransportException();
    AxisTransportException(int iExceptionCode);
    AxisTransportException(exception* e);
    AxisTransportException(exception* e, int iExceptionCode);
    virtual ~AxisTransportException() throw();
    const char* what() throw();
    const int getExceptionCode();
    const string getMessage(exception* e);
    const string getMessage(int iExceptionCode);
                                                                                                                             
private:
    void processException(exception* e);
    void processException(exception* e, int iExceptionCode);
    void processException(int iExceptionCode);
    string m_sMessage;
    int m_iExceptionCode;
};

#endif

