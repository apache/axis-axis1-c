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
 * @author  Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include "AxisWsddException.h"
#include <exception>
using namespace std;

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_WSDD_EXCEPTION is assumed.
*/
AxisWsddException::AxisWsddException()
{
    processException(SERVER_WSDD_EXCEPTION);
}

AxisWsddException::AxisWsddException (int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisWsddException::AxisWsddException (exception* e)
{
    processException (e);
}

AxisWsddException::AxisWsddException (exception* e, int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisWsddException::~AxisWsddException() throw ()
{

}

void AxisWsddException::processException (exception* e, int iExceptionCode)
{
    m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisWsddException::processException (exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisWsddException::processException(int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

const string AxisWsddException::getMessage (exception* objException)
{
    string sMessage = objException->what();

    return sMessage;
}

const string AxisWsddException::getMessage (int iExceptionCode)
{
    string sMessage;
    switch(iExceptionCode)
    {
        case CLIENT_WSDD_SERVICE_NOT_FOUND:
            sMessage = "Requested service not found";
            break;
        case CLIENT_WSDD_METHOD_NOT_ALLOWED:
            sMessage = "Requested method is not allowed";
            break;
        case CLIENT_WSDD_PARA_TYPE_MISMATCH:
            sMessage = "Parameter type mismatch";
            break; 
        case SERVER_WSDD_NO_HANDLERS_CONFIGURED:
            sMessage = "No handlers configured in server.wsdd";
            break;
        default:
            sMessage = "Unknown Wsdd Exception";
    }
    return sMessage;
}

const char* AxisWsddException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisWsddException::getExceptionCode()
{
    return m_iExceptionCode;
}

