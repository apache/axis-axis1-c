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

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_WSDD_EXCEPTION is assumed.
*/

AXIS_CPP_NAMESPACE_START

AxisWsddException::AxisWsddException()
{
    processException(SERVER_WSDD_EXCEPTION);
}

AxisWsddException::AxisWsddException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisWsddException::AxisWsddException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisWsddException::AxisWsddException (const exception* e)
{
    processException (e);
}

AxisWsddException::AxisWsddException (const exception* e, const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisWsddException::~AxisWsddException() throw ()
{

}

void AxisWsddException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage(iExceptionCode) + ":" + getMessage (e);
}

void AxisWsddException::processException (const exception* e, char* pcMessage)
{
    m_sMessage += "AxisWsddException:" + string(pcMessage) + ":" + getMessage (e);
}

void AxisWsddException::processException (const exception* e)
{
    m_sMessage += "AxisWsddException:" + getMessage (e);
}

void AxisWsddException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisWsddException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = pcMessage;
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
    if(pcMessage)
        delete pcMessage;
}
const string AxisWsddException::getMessage (const exception* objException)
{
    static string objExDetail = objException->what();

    return objExDetail;
}

const string AxisWsddException::getMessage (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case CLIENT_WSDD_SERVICE_NOT_FOUND:
            m_sMessage = "AxisWsddException:Requested service not found";
            break;
        case CLIENT_WSDD_METHOD_NOT_ALLOWED:
            m_sMessage = "AxisWsddException:Requested method is not allowed";
            break;
        case CLIENT_WSDD_PARA_TYPE_MISMATCH:
            m_sMessage = "AxisWsddException:Parameter type mismatch";
            break;
		case SERVER_WSDD_FILE_NOT_FOUND:
			m_sMessage = "AxisWsddException:WSDD loading fail";
			break;
        case SERVER_WSDD_NO_HANDLERS_CONFIGURED:
            m_sMessage = "AxisWsddException:No handlers configured in server.wsdd";
            break;
        case SERVER_WSDD_EXCEPTION:
            m_sMessage = "AxisWsddException:Unknown wsdd exception";
            break;
        default:
            m_sMessage = "AxisWsddException:Unknown Wsdd Exception";
    }
    return m_sMessage;
}

const char* AxisWsddException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisWsddException::getExceptionCode()
{
    return m_iExceptionCode;
}

AXIS_CPP_NAMESPACE_END
