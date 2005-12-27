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

#include "AxisSoapException.h"

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_SOAP_EXCEPTION is assumed.
*/

AXIS_CPP_NAMESPACE_START

AxisSoapException::AxisSoapException(const int iExceptionCode, const char* pcMessage):AxisException(iExceptionCode)
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

AxisSoapException::AxisSoapException (const AxisSoapException& e):AxisException (e)
{}

AxisSoapException::~AxisSoapException() throw ()
{}

string AxisSoapException::getMessageForExceptionCode (const int iExceptionCode)
{
    
	switch(iExceptionCode)
    {

        case SOAP_VERSION_MISMATCH :
            m_sMessageForExceptionCode = "AxisSoapException:Soap Version mismatch fault occurred";
            break;
        case SOAP_MUST_UNDERSTAND:
			m_sMessageForExceptionCode = "AxisSoapException:Soap Must understand fault occurred";
            break;
        case CLIENT_SOAP_MESSAGE_INCOMPLETE:
			m_sMessageForExceptionCode = "AxisSoapException:Received message is incomplete";
            break;
        case CLIENT_SOAP_SOAP_ACTION_EMTPY:
			m_sMessageForExceptionCode = "AxisSoapException:Soap action is empty";
            break;
        case CLIENT_SOAP_SOAP_CONTENT_ERROR:
			m_sMessageForExceptionCode = "AxisSoapException:Received content is faulty";
            break;
        case CLIENT_SOAP_NO_SOAP_METHOD:
			m_sMessageForExceptionCode = "AxisSoapException:Request method is not a soap method";
            break;
        case CLIENT_SOAP_CONTENT_NOT_SOAP:
			m_sMessageForExceptionCode = "AxisSoapException:Content is not a valid soap message";
            break;
        case CLIENT_MIME_CONTENT_ID_NOT_UNIQUE:
			m_sMessageForExceptionCode = "AxisSoapException:Content is not unique within the MIME message";
            break;
        default:
			m_sMessageForExceptionCode = "AxisSoapException:Unknown Soap Exception";
    }
    return m_sMessageForExceptionCode;
}

AXIS_CPP_NAMESPACE_END
