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

AxisSoapException::AxisSoapException (int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisSoapException::AxisSoapException (exception* e)
{
    processException (e);
}

AxisSoapException::AxisSoapException (exception* e, int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (e, iExceptionCode);
}

AxisSoapException::~AxisSoapException() throw ()
{

}

void AxisSoapException::processException (exception* e, int iExceptionCode)
{
    m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisSoapException::processException (exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisSoapException::processException(int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

const string AxisSoapException::getMessage (exception* objException)
{
    string sMessage = objException->what();

    return sMessage;
}

const string AxisSoapException::getMessage (int iExceptionCode)
{
    string sMessage;
    switch(iExceptionCode)
    {

        case SOAP_VERSION_MISMATCH :
            sMessage = "Soap Version mismatch fault occured";
            break;
        case SOAP_MUST_UNDERSTAND:
            sMessage = "Soap Must understand fault occured";
            break;
        case CLIENT_SOAP_MESSAGE_INCOMPLETE:
            sMessage = "Received message is incomplete";
            break;
        case CLIENT_SOAP_SOAP_ACTION_EMTPY:
            sMessage = "Soap action is empty";
            break;
        case CLIENT_SOAP_SOAP_CONTENT_ERROR:
            sMessage = "Received content is faulty";
            break;
        case CLIENT_SOAP_NO_SOAP_METHOD:
            sMessage = "Request method is not a soap method";
            break;
        default:
            sMessage = "Unknown Soap Exception";
    }
    return sMessage;
}

const char* AxisSoapException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisSoapException::getExceptionCode()
{
    return m_iExceptionCode;
}

