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

AxisEngineException::AxisEngineException()
{
    processException(SERVER_ENGINE_EXCEPTION);
}

AxisEngineException::AxisEngineException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisEngineException::AxisEngineException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisEngineException::AxisEngineException (const exception* e)
{
    processException (e);
}

AxisEngineException::AxisEngineException (const exception* e, const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisEngineException::~AxisEngineException() throw ()
{

}

void AxisEngineException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode) + ":" + getMessage(e);
}

void AxisEngineException::processException (const exception* e, char* pcMessage)
{
    m_sMessage += "AxisEngineException:" + string(pcMessage) + ":" + getMessage (e);
}

void AxisEngineException::processException (const exception* e)
{
    m_sMessage += "AxisEngineException:" + getMessage (e);
}

void AxisEngineException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisEngineException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = pcMessage;
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
    if(pcMessage)
        delete pcMessage;
}
const string AxisEngineException::getMessage (const exception* objException)
{
    static string objExDetail = objException->what();

    return objExDetail;
}

const string AxisEngineException::getMessage (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case SERVER_ENGINE_COULD_NOT_LOAD_SRV:
            m_sMessage = "AxisEngineException:Could not load service";
            break;
        case SERVER_ENGINE_COULD_NOT_LOAD_HDL:
            m_sMessage = "AxisEngineException:Could not load handler";
            break;
        case SERVER_ENGINE_LOADING_TRANSPORT_FAILED:
            m_sMessage = "DLOPEN FAILED in loading transport library";
            break;
        case SERVER_ENGINE_LOADING_PARSER_FAILED:
            m_sMessage = "DLOPEN FAILED in loading parser library";
            break;
        case SERVER_ENGINE_HANDLER_FAILED:
            m_sMessage = "AxisEngineException:Handler failed";
            break;
        case SERVER_ENGINE_WEBSERVICE_FAILED:
            m_sMessage = "AxisEngineException:Web Service failed";
            break;
        case SERVER_ENGINE_HANDLER_INIT_FAILED:
            m_sMessage = "AxisEngineException:Handler initialization failed";
            break;
        case SERVER_ENGINE_HANDLER_CREATION_FAILED:
            m_sMessage = "AxisEngineException:Handler creation failed";
            break;
        case SERVER_ENGINE_LIBRARY_LOADING_FAILED:
            m_sMessage = "AxisEngineException:Library loading failed";
            break;
        case SERVER_ENGINE_HANDLER_NOT_LOADED:
            m_sMessage = "AxisEngineException:Handler is not loaded";
            break;
        case SERVER_ENGINE_HANDLER_BEING_USED:
            m_sMessage = "AxisEngineException:Handler is being used";
            break;
        case SERVER_ENGINE_GET_HANDLER_FAILED:
            m_sMessage = "AxisEngineException:Get handler failed";
            break;
        case SERVER_ENGINE_WRONG_HANDLER_TYPE:
            m_sMessage = "AxisEngineException:Wrong handler type";
            break;
        default:
            m_sMessage = "AxisEngineException:Unknown Axis C++ Engine Exception";
    }
    return m_sMessage;
}

const char* AxisEngineException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisEngineException::getExceptionCode()
{
    return m_iExceptionCode;
}

AXIS_CPP_NAMESPACE_END
