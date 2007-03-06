/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 
#ifndef __HTTPTransportEXCEPTION_H_OF_AXIS_INCLUDED_
#define __HTTPTransportEXCEPTION_H_OF_AXIS_INCLUDED_

#include <axis/AxisException.hpp>

using namespace std;

AXIS_CPP_NAMESPACE_USE

class STORAGE_CLASS_INFO HTTPTransportException : public AxisException
{
public:
    // constructor
    HTTPTransportException(int iExceptionCode, const char* pcMessage = NULL): AxisException()
    {
        setMessage(iExceptionCode, "HTTPTransportException:", pcMessage);
    }
    
    // copy constructor
    HTTPTransportException(const HTTPTransportException& e): AxisException((const AxisException)e) { }
    
    // constructor
    HTTPTransportException(const AxisException& e): AxisException (e) { }
    
    // destructor
    virtual ~HTTPTransportException() throw() { }
};

#endif

