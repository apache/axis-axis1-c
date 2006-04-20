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

HTTPTransportException::HTTPTransportException (const HTTPTransportException& e):AxisException(e)
{}

HTTPTransportException::~HTTPTransportException() throw ()
{}

string HTTPTransportException::getMessageForExceptionCode (const int iExceptionCode)
{
	
    
	switch(iExceptionCode)
    {
		case SERVER_TRANSPORT_RECEPTION_EXCEPTION:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Problem occurred when" \
                " receiving the stream";
            break;
		}

        case SERVER_TRANSPORT_SENDING_EXCEPTION:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Problem occurred when sending" \
                " the stream";
            break;
		}

        case SERVER_TRANSPORT_HTTP_EXCEPTION:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:HTTP transport error";
            break;
		}

        case SERVER_TRANSPORT_PROCESS_EXCEPTION:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:HTTP Error, cannot process" \
                " response message";
            break;
		}

        case SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Unknow HTTP response," \
                " cannot process response message";
            break;
		}

        case SERVER_TRANSPORT_UNEXPECTED_STRING:
		{
           m_sMessageForExceptionCode = "HTTPTransportException:Unexpected string " \
                "received. Most probably server " \
                "returned an empty stream";
            break;
		}

        case SERVER_TRANSPORT_CHANNEL_INIT_ERROR:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Cannot initialize a " \
                "channel to the remote end";
            break;
		}

        case SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Output streaming error on" \
                " Channel while writing data";
            break;
		}

        case SERVER_TRANSPORT_INPUT_STREAMING_ERROR:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Input streaming error while" \
                " getting data";
            break;
		}

        case SERVER_TRANSPORT_TIMEOUT_EXCEPTION:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Channel error while waiting" \
                 " for timeout";
            break;
		}

        case SERVER_TRANSPORT_TIMEOUT_EXPIRED:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Channel error connection " \
                "timeout before receiving";
            break;
		}

        case SERVER_TRANSPORT_BUFFER_EMPTY:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Transport buffer is empty";
            break;
		}

		case CLIENT_TRANSPORT_EXCEPTION:
		{
			m_sMessageForExceptionCode = "HTTPTransportException:Generic client transport exception";
				break;
		}

		case CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED:
		{
			m_sMessageForExceptionCode = "HTTPTransportException:Client failed to open";
			break;
		}

		case CLIENT_TRANSPORT_TYPE_MISMATCH:
		{
			m_sMessageForExceptionCode = "HTTPTransportException:Client attempted to use SSL functions without the proper prerequisites";
			break;
		}

		case CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER:
		{
			m_sMessageForExceptionCode = "HTTPTransportException:Client attempted to use secure transport (https) without an SSL layer";
			break;
		}

        case SERVER_TRANSPORT_LOADING_CHANNEL_FAILED:
        {
            m_sMessageForExceptionCode = "DLOPEN FAILED in loading channel library";
            break;
        }

        default:
		{
            m_sMessageForExceptionCode = "HTTPTransportException:Unknown Transport Exception"; 
		}
    }
    return m_sMessageForExceptionCode;
}

