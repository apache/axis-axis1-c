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

#include "AxisTransportException.h"
#include <exception>
using namespace std;

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_TRANSPORT_EXCEPTION is assumed.
*/
AxisTransportException::AxisTransportException()
{
    processException(SERVER_TRANSPORT_EXCEPTION);
}

AxisTransportException::AxisTransportException (int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisTransportException::AxisTransportException (exception* e)
{
    processException (e);
}

AxisTransportException::AxisTransportException (exception* e, int iExceptionCode)
{
    processException (e, iExceptionCode);
}

AxisTransportException::~AxisTransportException() throw ()
{

}

void AxisTransportException::processException (exception* e, int iExceptionCode)
{
    m_sMessage = getMessage (e) + getMessage (iExceptionCode);
}

void AxisTransportException::processException (exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisTransportException::processException(int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

const string AxisTransportException::getMessage (exception* objException)
{
    string sMessage = objException->what();

    return sMessage;
}

const string AxisTransportException::getMessage (int iExceptionCode)
{
    string sMessage;
    switch(iExceptionCode)
    {
       case SERVER_TRANSPORT_RECEPTIONEXCEPTION:
            sMessage = "Problem occured when receiving the stream";
            break;
        case SERVER_TRANSPORT_SENDINGEXCEPTION:
            sMessage = "Problem occured when sending the stream";
            break;
        case SERVER_TRANSPORT_HTTP_EXCEPTION:
            sMessage = "HTTP transport error";
            break;
        default:
            sMessage = "Unknown Transport Exception"; 
    }
    return sMessage;
}

const char* AxisTransportException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisTransportException::getExceptionCode()
{
    return m_iExceptionCode;
}

