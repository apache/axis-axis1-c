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

#include "AxisParseException.h"

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_TRANSPORT_EXCEPTION is assumed.
*/
AxisParseException::AxisParseException()
{
    processException(SERVER_TRANSPORT_EXCEPTION);
}

AxisParseException::AxisParseException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisParseException::AxisParseException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisParseException::AxisParseException (const exception* e)
{
    processException (e);
}

AxisParseException::AxisParseException (const exception* e, const int iExceptionCode)
{
    processException (e, iExceptionCode);
}

AxisParseException::~AxisParseException() throw ()
{

}

void AxisParseException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode) + ":" + getMessage(e);
}

void AxisParseException::processException (const exception* e, char* pcMessage)
{
    m_sMessage += "AxisParseException:" + string(pcMessage) + ":" + getMessage (e);
}

void AxisParseException::processException (const exception* e)
{
    m_sMessage = "AxisParseException:" + getMessage (e);
}

void AxisParseException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisParseException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = pcMessage;
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
    if(pcMessage)
        delete pcMessage;
}
const string AxisParseException::getMessage (const exception* objException)
{
	static string objExDetail = objException->what();

    return objExDetail;
}

const string AxisParseException::getMessage (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
        case SERVER_PARSE_BUFFER_EMPTY:
            m_sMessage = "AxisParseException:Buffer received from the parser is empty";
            break;
        case SERVER_PARSE_PARSER_FAILED:
            m_sMessage = "AxisParseException:XML_STATUS_ERROR thrown from parser";
            break;
        case SERVER_PARSE_TRANSPORT_FAILED:
            m_sMessage = "AxisParseException:Error when getting the byte stream from the transport";
            break;
        default:
            m_sMessage = "AxisParseException:Unknown Parse Exception"; 
    }
    return m_sMessage;
}

const char* AxisParseException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisParseException::getExceptionCode()
{
    return m_iExceptionCode;
}

