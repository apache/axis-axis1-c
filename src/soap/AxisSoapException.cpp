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

#include <axis/AxisSoapException.h>
#include <exception>
using namespace std;

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_SOAP_EXCEPTION is assumed.
*/
AxisSoapException::AxisSoapException()
{
    processException(SERVER_SOAP_EXCEPTION);
}

AxisSoapException::AxisSoapException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisSoapException::AxisSoapException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisSoapException::AxisSoapException (const exception* e)
{
    processException (e);
}

AxisSoapException::AxisSoapException (const exception* e, const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisSoapException::~AxisSoapException() throw ()
{

}

void AxisSoapException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage (e) + " " + getMessage (iExceptionCode);
}

void AxisSoapException::processException (const exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisSoapException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisSoapException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = strdup(pcMessage);
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
    if(pcMessage)
        delete pcMessage;
}
const string AxisSoapException::getMessage (const exception* objException)
{
    m_sMessage = objException->what();

    return m_sMessage;
}

const string AxisSoapException::getMessage (const int iExceptionCode)
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
        default:
            m_sMessage = "AxisSoapException:Unknown Soap Exception";
    }
    return m_sMessage;
}

const char* AxisSoapException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisSoapException::getExceptionCode()
{
    return m_iExceptionCode;
}

