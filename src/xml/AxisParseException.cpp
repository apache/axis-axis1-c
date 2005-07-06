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

AxisParseException::AxisParseException(const int iExceptionCode,const char* pcMessage):AxisException(iExceptionCode)
{
	AxisString sMessage = "";
	if (pcMessage) 
	{
		sMessage = pcMessage;
	}
	m_sMessage = getMessageForExceptionCode(m_iExceptionCode) + " " + sMessage;
}

AxisParseException::AxisParseException (const AxisParseException& e):AxisException (e)
{}

AxisParseException::~AxisParseException() throw ()
{}

const string AxisParseException::getMessageForExceptionCode (const int iExceptionCode)
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

