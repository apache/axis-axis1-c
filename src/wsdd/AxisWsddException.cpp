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

AxisWsddException::AxisWsddException(const int iExceptionCode,const char* pcMessage):AxisException(iExceptionCode)
{
	std::string sMessage = "";
	if (pcMessage) 
	{
		sMessage = string(pcMessage);
		getMessageForExceptionCode(iExceptionCode);
		m_sMessageForExceptionCode = getMessageForExceptionCode(iExceptionCode) + " " + sMessage;
		setMessage(m_sMessageForExceptionCode.c_str());

	}
	else
		setMessage(getMessageForExceptionCode(iExceptionCode).c_str());
}

AxisWsddException::AxisWsddException (const AxisWsddException& e):AxisException(e)
{}

AxisWsddException::~AxisWsddException() throw ()
{}

string AxisWsddException::getMessageForExceptionCode (const int iExceptionCode)
{
    
	switch(iExceptionCode)
    {
        case CLIENT_WSDD_SERVICE_NOT_FOUND:
            m_sMessageForExceptionCode = "AxisWsddException:Requested service not found";
            break;
        case CLIENT_WSDD_METHOD_NOT_ALLOWED:
            m_sMessageForExceptionCode = "AxisWsddException:Requested method is not allowed";
            break;
        case CLIENT_WSDD_PARA_TYPE_MISMATCH:
            m_sMessageForExceptionCode = "AxisWsddException:Parameter type mismatch";
            break;
		case SERVER_WSDD_FILE_NOT_FOUND:
			m_sMessageForExceptionCode = "AxisWsddException:WSDD loading fail";
			break;
        case SERVER_WSDD_NO_HANDLERS_CONFIGURED:
            m_sMessageForExceptionCode = "AxisWsddException:No handlers configured in server.wsdd";
            break;
        case SERVER_WSDD_EXCEPTION:
            m_sMessageForExceptionCode = "AxisWsddException:Unknown wsdd exception";
            break;
        default:
            m_sMessageForExceptionCode = "AxisWsddException:Unknown Wsdd Exception";
    }
    return m_sMessageForExceptionCode;
}

AXIS_CPP_NAMESPACE_END
