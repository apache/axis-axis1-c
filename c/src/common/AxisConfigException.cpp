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

#include <axis/AxisConfigException.h>
#include <exception>
using namespace std;

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_CONFIG_EXCEPTION is assumed.
*/
AxisConfigException::AxisConfigException()
{
    processException(SERVER_CONFIG_EXCEPTION);
}

AxisConfigException::AxisConfigException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisConfigException::AxisConfigException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisConfigException::AxisConfigException (const exception* e)
{
    m_iExceptionCode = -1;
    processException (e);
}

AxisConfigException::AxisConfigException (const exception* e, const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisConfigException::~AxisConfigException() throw ()
{

}

void AxisConfigException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage (e) + " " + getMessage (iExceptionCode);
}

void AxisConfigException::processException (const exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisConfigException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisConfigException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = strdup(pcMessage);
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
    if(pcMessage)
        delete pcMessage;
}

const string AxisConfigException::getMessage (const exception* objException)
{
    m_sMessage = objException->what();

    return m_sMessage;
}

const string AxisConfigException::getMessage (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case SERVER_CONFIG_TRANSPORT_CONF_FAILED:
            m_sMessage = "AxisConfigException:Transport layer is not" \
                " configured properly";
            break;
        case SERVER_CONFIG_LIBRARY_PATH_EMPTY:
            m_sMessage = "AxisConfigException:Library path is empty(Not in" \
                " server.wsdd file)";
            break;
        default:
            m_sMessage = "AxisConfigException:Unknown Axis C++" \
                " Configuration Exception";
    }
    return m_sMessage;
}

const char* AxisConfigException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisConfigException::getExceptionCode()
{
    return m_iExceptionCode;
}
