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
    m_sMessage = getMessage (iExceptionCode) + ":" + getMessage(e);
}

void AxisTransportException::processException (const exception* e, char* pcMessage)
{
    m_sMessage += "AxisTransportException:" + string(pcMessage) + ":" + getMessage (e);
}

void AxisTransportException::processException (const exception* e)
{
    m_sMessage += "AxisTransportException:" + getMessage (e);
}

void AxisTransportException::processException(const int iExceptionCode)
{
    m_sMessage = getMessage (iExceptionCode);
}

void AxisTransportException::processException(const int iExceptionCode, char* pcMessage)
{
    AxisString sMessage = pcMessage;
    m_sMessage = getMessage(iExceptionCode) + " " + sMessage;
}

const string AxisTransportException::getMessage (const exception* objException)
{
	static string objExDetail = objException->what();

    return objExDetail;
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
            m_sMessage = "AxisTransportException:Unknown HTTP response," \
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
	case CLIENT_TRANSPORT_EXCEPTION:
	{
            m_sMessage = "AxisTransportException:Generic client transport exception";
			break;
	}

	case CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED:
	{
            m_sMessage = "AxisTransportException:Client failed to open";
		break;
	}

	case CLIENT_TRANSPORT_TYPE_MISMATCH:
	{
            m_sMessage = "AxisTransportException:Client attempted to use SSL functions without the proper prerquistes";
		break;
	}

	case CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER:
	{
            m_sMessage = "AxisTransportException:Client attempted to use secure transport (https) without an SSL layer";
		break;
	}

        case SERVER_TRANSPORT_LOADING_SSLCHANNEL_FAILED:
        {
            m_sMessage = "DLOPEN FAILED in loading ssl channel library";
            break;
        }

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

