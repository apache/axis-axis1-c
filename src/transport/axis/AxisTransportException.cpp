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

AxisTransportException::AxisTransportException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisTransportException::AxisTransportException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisTransportException::AxisTransportException (const exception* e)
{
    processException (e);
}

AxisTransportException::AxisTransportException (const exception* e, const int iExceptionCode)
{
    processException (e, iExceptionCode);
}

AxisTransportException::~AxisTransportException() throw ()
{

}

void AxisTransportException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage (e) + " " + getMessage (iExceptionCode);
}

void AxisTransportException::processException (const exception* e)
{
    m_sMessage = getMessage (e);
}

void AxisTransportException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisTransportException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = strdup(pcMessage);
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
    //m_sMessage = getMessage(iExceptionCode);
    if(pcMessage)
        delete pcMessage;
}
const string AxisTransportException::getMessage (const exception* objException)
{
    m_sMessage = objException->what();

    return m_sMessage;
}

const string AxisTransportException::getMessage (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
       case SERVER_TRANSPORT_RECEPTION_EXCEPTION:
            m_sMessage = "AxisTransportException:Problem occured when" \
                " receiving the stream";
            break;
        case SERVER_TRANSPORT_SENDING_EXCEPTION:
            m_sMessage = "AxisTransportException:Problem occured when sending" \
                " the stream";
            break;
        case SERVER_TRANSPORT_HTTP_EXCEPTION:
            m_sMessage = "AxisTransportException:HTTP transport error";
            break;
        case SERVER_TRANSPORT_PROCESS_EXCEPTION:
            m_sMessage = "AxisTransportException:HTTP Error, cannot process" \
                " response message";
            break;
        case SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE:
            m_sMessage = "AxisTransportException:Unknow HTTP response," \
                " cannot process response message";
            break;
        case SERVER_TRANSPORT_UNEXPECTED_STRING:
            m_sMessage = "AxisTransportException:Unexpected string " \
                "received. Most probably server " \
                "returned an empty stream";
            break;
        case SERVER_TRANSPORT_CHANNEL_INIT_ERROR:
            m_sMessage = "AxisTransportException:Cannot initialize a " \
                "channel to the remote end";
            break;
        case SERVER_TRANSPORT_SOCKET_CREATE_ERROR:
            m_sMessage = "AxisTransportException:Sockets error Couldn't" \
               " create socket";
            break;
        case SERVER_TRANSPORT_SOCKET_CONNECT_ERROR:
            m_sMessage = "AxisTransportException:Cannot open a channel to the" \
            " remote end, shutting down the channel";
            break;
        case SERVER_TRANSPORT_INVALID_SOCKET:
            m_sMessage = "AxisTransportException:Invalid socket. Socket may" \
                " not be open";
            break;
        case SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR:
            m_sMessage = "AxisTransportException:Output streaming error on" \
                " Channel while writing data";
            break;
        case SERVER_TRANSPORT_INPUT_STREAMING_ERROR:
            m_sMessage = "AxisTransportException:Input streaming error while" \
                " getting data";
            break;
        case SERVER_TRANSPORT_TIMEOUT_EXCEPTION:
            m_sMessage = "AxisTransportException:Channel error while waiting" \
                 " for timeout";
            break;
        case SERVER_TRANSPORT_TIMEOUT_EXPIRED:
            m_sMessage = "AxisTransportException:Channel error connection " \
                "timeout before receving";
            break;
        case SERVER_TRANSPORT_BUFFER_EMPTY:
            m_sMessage = "AxisTransportException:Transport buffer is empty";
            break;
        default:
            m_sMessage = "AxisTransportException:Unknown Transport Exception"; 
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

