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

#include <axis/AxisTransportException.h>
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
    m_sMessage = objException->what();

    return m_sMessage;
}

const string AxisTransportException::getMessage (int iExceptionCode)
{
    switch(iExceptionCode)
    {
       case SERVER_TRANSPORT_RECEPTION_EXCEPTION:
            m_sMessage = "Problem occured when receiving the stream";
            break;
        case SERVER_TRANSPORT_SENDING_EXCEPTION:
            m_sMessage = "Problem occured when sending the stream";
            break;
        case SERVER_TRANSPORT_HTTP_EXCEPTION:
            m_sMessage = "HTTP transport error";
            break;
        case SERVER_TRANSPORT_PROCESS_EXCEPTION:
            m_sMessage = "HTTP Error, cannot process response message";
            break;
        case SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE:
            m_sMessage = "Unknow HTTP response, cannot process response message";
            break;
        case SERVER_TRANSPORT_UNEXPECTED_STRING:
            m_sMessage = "Unexpected string";
            break;
        case SERVER_TRANSPORT_CHANNEL_INIT_ERROR:
            m_sMessage = "Cannot initialize a channel to the remote end";
            break;
        case SERVER_TRANSPORT_SOCKET_CREATE_ERROR:
            m_sMessage = "Sockets error Couldn't create socket";
            break;
        case SERVER_TRANSPORT_SOCKET_CONNECT_ERROR:
            m_sMessage = "Cannot open a channel to the remote end, shutting down the channel";
            break;
        case SERVER_TRANSPORT_INVALID_SOCKET:
            m_sMessage = "Invalid socket. Socket may not be open";
            break;
        case SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR:
            m_sMessage = "Output streaming error on Channel while writing data";
            break;
        case SERVER_TRANSPORT_INPUT_STREAMING_ERROR:
            m_sMessage = "Input streaming error while getting data";
            break;
        case SERVER_TRANSPORT_TIMEOUT_EXCEPTION:
            m_sMessage = "Channel error while waiting for timeout";
            break;
        case SERVER_TRANSPORT_TIMEOUT_EXPIRED:
            m_sMessage = "Channel error connection timeout before receving";
            break;
        case SERVER_TRANSPORT_BUFFER_EMPTY:
            m_sMessage = "Transport buffer is empty";
            break;
        default:
            m_sMessage = "Unknown Transport Exception"; 
    }
    return m_sMessage;
}

const char* AxisTransportException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisTransportException::getExceptionCode()
{
    return m_iExceptionCode;
}

