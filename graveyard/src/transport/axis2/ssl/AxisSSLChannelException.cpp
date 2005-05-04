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
 * @author  Damitha Kumarage (damitha@hsenid.lk, damitha@opensource.lk)
 *
 */

#include "AxisSSLChannelException.hpp"

/**
 *    Default when no parameter passed. When thrown with no parameter
 *    more general SERVER_TRANSPORT_EXCEPTION is assumed.
*/
AxisSSLChannelException::AxisSSLChannelException()
{
    processException(SERVER_TRANSPORT_EXCEPTION);
}

AxisSSLChannelException::AxisSSLChannelException (const int iExceptionCode)
{
    m_iExceptionCode = iExceptionCode;
    processException (iExceptionCode);
}

AxisSSLChannelException::AxisSSLChannelException(const int iExceptionCode, char* pcMessage)
{
    m_iExceptionCode = iExceptionCode;
    processException(iExceptionCode, pcMessage);
}

AxisSSLChannelException::AxisSSLChannelException (const exception* e)
{
    processException (e);
}

AxisSSLChannelException::AxisSSLChannelException (const exception* e, const int iExceptionCode)
{
    processException (e, iExceptionCode);
}

AxisSSLChannelException::~AxisSSLChannelException() throw ()
{

}

void AxisSSLChannelException::processException (const exception* e, const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode) + ":" + getMessage(e);
}

void AxisSSLChannelException::processException (const exception* e, char* pcMessage)
{
    m_sMessage += "AxisSSLChannelException:" + string(pcMessage) + ":" + getMessage (e);
}

void AxisSSLChannelException::processException (const exception* e)
{
    m_sMessage += "AxisSSLChannelException:" + getMessage (e);
}

void AxisSSLChannelException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisSSLChannelException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = pcMessage;
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
}

const string AxisSSLChannelException::getMessage (const exception* objException)
{
	static string objExDetail = objException->what();

    return objExDetail;
}

const string AxisSSLChannelException::getMessage (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
       case CLIENT_SSLCHANNEL_RECEPTION_EXCEPTION:
            m_sMessage = "AxisSSLChannelException:Problem occured when" \
                " receiving the stream";
            break;
        case CLIENT_SSLCHANNEL_SENDING_EXCEPTION:
            m_sMessage = "AxisSSLChannelException:Problem occured when sending" \
                " the stream";
            break;
        case CLIENT_SSLCHANNEL_CHANNEL_INIT_ERROR:
            m_sMessage = "AxisSSLChannelException:Cannot initialize a " \
                "channel to the remote end";
            break;
        case CLIENT_SSLCHANNEL_SOCKET_CREATE_ERROR:
            m_sMessage = "AxisSSLChannelException:Sockets error Couldn't" \
               " create socket";
            break;
        case CLIENT_SSLCHANNEL_SOCKET_CONNECT_ERROR:
            m_sMessage = "AxisSSLChannelException:Cannot open a channel to the" \
            " remote end, shutting down the channel";
            break;
        case CLIENT_SSLCHANNEL_INVALID_SOCKET_ERROR:
            m_sMessage = "AxisSSLChannelException:Socket used to write is invalid";
            break;
        case CLIENT_SSLCHANNEL_CONTEXT_CREATE_ERROR:
            m_sMessage = "AxisSSLChannelException:Could not create SSL context";
            break;
        case CLIENT_SSLCHANNEL_ERROR:
            m_sMessage = "AxisSSLChannelException:OpenSSL Error code is:";
            break;
        
        default:
            m_sMessage = "AxisSSLChannelException:Unknown SSL Channel Exception"; 
    }
    return m_sMessage;
}

const char* AxisSSLChannelException::what() throw ()
{
    return m_sMessage.c_str ();
}

const int AxisSSLChannelException::getExceptionCode()
{
    return m_iExceptionCode;
}

