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
#include <exception>
using namespace std;

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_ENGINE_EXCEPTION is assumed.
*/
AxisEngineException::AxisEngineException()
{
    processException(SERVER_ENGINE_EXCEPTION);
}

AxisEngineException::AxisEngineException (int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisEngineException::AxisEngineException (exception* e)
{
    processException (e);
}

AxisEngineException::AxisEngineException (exception* e, int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisEngineException::~AxisEngineException() throw ()
{

}

void AxisEngineException::processException (exception* e, int iExceptionCode)
{
    m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisEngineException::processException (exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisEngineException::processException(int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

const string AxisEngineException::getMessage (exception* objException)
{
    string sMessage = objException->what();

    return sMessage;
}

const string AxisEngineException::getMessage (int iExceptionCode)
{
    string sMessage;
    switch(iExceptionCode)
    {
        case SERVER_ENGINE_COULD_NOT_LOAD_SRV:
            sMessage = "Could not load service";
            break;
        case SERVER_ENGINE_COULD_NOT_LOAD_HDL:
            sMessage = "Could not load handler";
            break;
        case SERVER_ENGINE_HANDLER_FAILED:
            sMessage = "Handler failed";
            break;
        case SERVER_ENGINE_WEBSERVICE_FAILED:
            sMessage = "Web Service failed";
            break;
        case SERVER_ENGINE_HANDLER_INIT_FAILED:
            sMessage = "Handler initialization failed";
            break;
        case SERVER_ENGINE_HANDLER_CREATION_FAILED:
            sMessage = "Handler creation failed";
            break;
        case SERVER_ENGINE_LIBRARY_LOADING_FAILED:
            sMessage = "Library loading failed";
            break;
        case SERVER_ENGINE_HANDLER_NOT_LOADED:
            sMessage = "Handler is not loaded";
            break;
        case SERVER_ENGINE_HANDLER_BEING_USED:
            sMessage = "Handler is being used";
            break;
        case SERVER_ENGINE_GET_HANDLER_FAILED:
            sMessage = "Get handler failed";
            break;
        case SERVER_ENGINE_WRONG_HANDLER_TYPE:
            sMessage = "Wrong handler type";
            break;
        default:
            sMessage = "Unknown Axis C++ Engine Exception";
    }
    return sMessage;
}

const char* AxisEngineException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisEngineException::getExceptionCode()
{
    return m_iExceptionCode;
}

