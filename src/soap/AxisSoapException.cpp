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

AxisSoapException::AxisSoapException(const int iExceptionCode, char* pcMessage):AxisException(iExceptionCode)
{
   AxisString sMessage = "";
	if (pcMessage) 
	{
		sMessage = pcMessage;
	}
	m_sMessage = getMessageForExceptionCode(m_iExceptionCode) + " " + sMessage;
}

AxisSoapException::AxisSoapException (const AxisSoapException& e):AxisException (e)
{}

AxisSoapException::~AxisSoapException() throw ()
{}

const string AxisSoapException::getMessageForExceptionCode (const int iExceptionCode)
{
    switch(iExceptionCode)
    {

        case SOAP_VERSION_MISMATCH :
            m_sMessage = "AxisSoapException:Soap Version mismatch fault occured";
            break;
        case SOAP_MUST_UNDERSTAND:
            m_sMessage = "AxisSoapException:Soap Must understand fault occured";
            break;
        case CLIENT_SOAP_MESSAGE_INCOMPLETE:
            m_sMessage = "AxisSoapException:Received message is incomplete";
            break;
        case CLIENT_SOAP_SOAP_ACTION_EMTPY:
            m_sMessage = "AxisSoapException:Soap action is empty";
            break;
        case CLIENT_SOAP_SOAP_CONTENT_ERROR:
            m_sMessage = "AxisSoapException:Received content is faulty";
            break;
        case CLIENT_SOAP_NO_SOAP_METHOD:
            m_sMessage = "AxisSoapException:Request method is not a soap method";
            break;
        case CLIENT_SOAP_CONTENT_NOT_SOAP:
            m_sMessage = "AxisSoapException:Content is not a valid soap message";
            break;
        case CLIENT_MIME_CONTENT_ID_NOT_UNIQUE:
            m_sMessage = "AxisSoapException:Content is not unique within the MIME message";
            break;
        default:
            m_sMessage = "AxisSoapException:Unknown Soap Exception";
    }
    return m_sMessage;
}

AXIS_CPP_NAMESPACE_END
