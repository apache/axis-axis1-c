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

#include "AxisEngineException.h"

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_ENGINE_EXCEPTION is assumed.
*/

AXIS_CPP_NAMESPACE_START

AxisEngineException::AxisEngineException(const int iExceptionCode, const char* pcMessage ):AxisException(iExceptionCode)
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
	

AxisEngineException::AxisEngineException (const AxisEngineException& e):AxisException(e)
{}

AxisEngineException::~AxisEngineException() throw ()
{}

string AxisEngineException::getMessageForExceptionCode (const int iExceptionCode)
{
    
	switch(iExceptionCode)
    {
        case SERVER_ENGINE_COULD_NOT_LOAD_SRV:
			m_sMessageForExceptionCode = "AxisEngineException:Could not load service";
            break;
        case SERVER_ENGINE_COULD_NOT_LOAD_HDL:
            m_sMessageForExceptionCode = "AxisEngineException:Could not load handler";
            break;
        case SERVER_ENGINE_LOADING_TRANSPORT_FAILED:
            m_sMessageForExceptionCode = "DLOPEN FAILED in loading transport library";
            break;
        case SERVER_ENGINE_LOADING_PARSER_FAILED:
            m_sMessageForExceptionCode = "DLOPEN FAILED in loading parser library";
            break;
        case SERVER_ENGINE_HANDLER_FAILED:
            m_sMessageForExceptionCode = "AxisEngineException:Handler failed";
            break;
        case SERVER_ENGINE_WEBSERVICE_FAILED:
            m_sMessageForExceptionCode = "AxisEngineException:Web Service failed";
            break;
        case SERVER_ENGINE_HANDLER_INIT_FAILED:
            m_sMessageForExceptionCode = "AxisEngineException:Handler initialization failed";
            break;
        case SERVER_ENGINE_HANDLER_CREATION_FAILED:
            m_sMessageForExceptionCode = "AxisEngineException:Handler creation failed";
            break;
        case SERVER_ENGINE_LIBRARY_LOADING_FAILED:
            m_sMessageForExceptionCode = "AxisEngineException:Library loading failed";
            break;
        case SERVER_ENGINE_HANDLER_NOT_LOADED:
            m_sMessageForExceptionCode = "AxisEngineException:Handler is not loaded";
            break;
        case SERVER_ENGINE_HANDLER_BEING_USED:
            m_sMessageForExceptionCode = "AxisEngineException:Handler is being used";
            break;
        case SERVER_ENGINE_GET_HANDLER_FAILED:
            m_sMessageForExceptionCode = "AxisEngineException:Get handler failed";
            break;
        case SERVER_ENGINE_WRONG_HANDLER_TYPE:
            m_sMessageForExceptionCode = "AxisEngineException:Wrong handler type";
            break;
        case SERVER_CLIENT_ENGINE_MISMATCH:
            m_sMessageForExceptionCode = "AxisEngineException:Engine cannot be initialized as both client and server";
            break;
        default:
            m_sMessageForExceptionCode = "AxisEngineException:Unknown Axis C++ Engine Exception";
    }
    return m_sMessageForExceptionCode;
}

AXIS_CPP_NAMESPACE_END
