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

#include "AxisGenException.h"
#include <exception>

AXIS_CPP_NAMESPACE_START

//using namespace std;

AxisGenException::AxisGenException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisGenException::AxisGenException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisGenException::AxisGenException (const exception* e)
{
    m_iExceptionCode = -1;
    processException (e);
}

AxisGenException::AxisGenException (const exception* e, const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisGenException::AxisGenException(const char* pcMessage)
{
    m_sMessage = pcMessage;
/*  if(pcMessage) delete pcMessage; */
}

void AxisGenException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage(iExceptionCode) + ":" + getMessage (e);
}

void AxisGenException::processException (const exception* e, char* pcMessage)
{
    m_sMessage += "AxisGenException:" + string(pcMessage) + ":" + getMessage (e);
}

void AxisGenException::processException (const exception* e)
{
    m_sMessage += "AxisGenException:" + getMessage (e);
}

void AxisGenException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisGenException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = pcMessage;
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
    if(pcMessage)
        delete pcMessage;
}

const string AxisGenException::getMessage (const exception* objException)
{
    return objException->what();
}

const string AxisGenException::getMessage (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case AXISC_SERVICE_THROWN_EXCEPTION:
            m_sMessage = "A service has thrown an exception. see detail";
            break;
        case SERVER_TEST_EXCEPTION:
            m_sMessage = "This is a testing error";
            break;
        case AXISC_NODE_VALUE_MISMATCH_EXCEPTION:
            m_sMessage = "Cannot deserialize the requested element";
            break;
        default:
            m_sMessage = "Unknown Exception has occured";

    }
    return m_sMessage;
}

AxisGenException::~AxisGenException() throw ()
{

}

const char* AxisGenException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisGenException::getExceptionCode()
{
    return m_iExceptionCode; 
}

AXIS_CPP_NAMESPACE_END
