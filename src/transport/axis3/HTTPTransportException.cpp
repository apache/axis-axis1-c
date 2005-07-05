/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

#include "HTTPTransportException.hpp"

HTTPTransportException::HTTPTransportException(const int iExceptionCode, char* pcMessage):AxisException(iExceptionCode)
{
	AxisString sMessage = "";
	if (pcMessage) 
	{
		sMessage = pcMessage;
	}
	m_sMessage = getMessageForExceptionCode(m_iExceptionCode) + " " + sMessage;
}

HTTPTransportException::HTTPTransportException (HTTPTransportException& e):AxisException(e)
{}

HTTPTransportException::~HTTPTransportException() throw ()
{}

const string HTTPTransportException::getMessageForExceptionCode (const int iExceptionCode)
{
    switch(iExceptionCode)
    {
		case SERVER_TRANSPORT_RECEPTION_EXCEPTION:
		{
            m_sMessage = "HTTPTransportException:Problem occured when" \
                " receiving the stream";
            break;
		}

        case SERVER_TRANSPORT_SENDING_EXCEPTION:
		{
            m_sMessage = "HTTPTransportException:Problem occured when sending" \
                " the stream";
            break;
		}

        case SERVER_TRANSPORT_HTTP_EXCEPTION:
		{
            m_sMessage = "HTTPTransportException:HTTP transport error";
            break;
		}

        case SERVER_TRANSPORT_PROCESS_EXCEPTION:
		{
            m_sMessage = "HTTPTransportException:HTTP Error, cannot process" \
                " response message";
            break;
		}

        case SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE:
		{
            m_sMessage = "HTTPTransportException:Unknow HTTP response," \
                " cannot process response message";
            break;
		}

        case SERVER_TRANSPORT_UNEXPECTED_STRING:
		{
            m_sMessage = "HTTPTransportException:Unexpected string " \
                "received. Most probably server " \
                "returned an empty stream";
            break;
		}

        case SERVER_TRANSPORT_CHANNEL_INIT_ERROR:
		{
            m_sMessage = "HTTPTransportException:Cannot initialize a " \
                "channel to the remote end";
            break;
		}

        case SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR:
		{
            m_sMessage = "HTTPTransportException:Output streaming error on" \
                " Channel while writing data";
            break;
		}

        case SERVER_TRANSPORT_INPUT_STREAMING_ERROR:
		{
            m_sMessage = "HTTPTransportException:Input streaming error while" \
                " getting data";
            break;
		}

        case SERVER_TRANSPORT_TIMEOUT_EXCEPTION:
		{
            m_sMessage = "HTTPTransportException:Channel error while waiting" \
                 " for timeout";
            break;
		}

        case SERVER_TRANSPORT_TIMEOUT_EXPIRED:
		{
            m_sMessage = "HTTPTransportException:Channel error connection " \
                "timeout before receving";
            break;
		}

        case SERVER_TRANSPORT_BUFFER_EMPTY:
		{
            m_sMessage = "HTTPTransportException:Transport buffer is empty";
            break;
		}

		case CLIENT_TRANSPORT_EXCEPTION:
		{
				m_sMessage = "HTTPTransportException:Generic client transport exception";
				break;
		}

		case CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED:
		{
				m_sMessage = "HTTPTransportException:Client failed to open";
			break;
		}

		case CLIENT_TRANSPORT_TYPE_MISMATCH:
		{
				m_sMessage = "HTTPTransportException:Client attempted to use SSL functions without the proper prerquistes";
			break;
		}

		case CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER:
		{
				m_sMessage = "HTTPTransportException:Client attempted to use secure transport (https) without an SSL layer";
			break;
		}

        case SERVER_TRANSPORT_LOADING_CHANNEL_FAILED:
        {
            m_sMessage = "DLOPEN FAILED in loading channel library";
            break;
        }

        default:
		{
            m_sMessage = "HTTPTransportException:Unknown Transport Exception"; 
		}
    }
    return m_sMessage;
}

