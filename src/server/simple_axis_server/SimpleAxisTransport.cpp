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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

#include "SimpleAxisTransport.h"

#define AXIS_URI_EXTENSION "/axis"

/* Following is the character that should be used to separate the method name in
 * the SOAPAction header value. Ex: "http://localhost:80/axis/Calculator#Add"
 */
#define SOAPACTION_METHODNAME_SEPARATOR "#"

SimpleAxisTransport::SimpleAxisTransport( int iSocket)
{
    m_eProtocolType = APTHTTP1_1;
    m_iSocket = iSocket;
    m_bReadPastHeaders = false;
    m_strPayloadToSend = "";
    m_strServiceURI = "base";
    m_strReceived = "";
    m_strSOAPAction = "";
}

SimpleAxisTransport::~SimpleAxisTransport()
{
	int	iShutDownRes = shutdown( m_iSocket, SD_BOTH);

	int iCloseSockRes = 0;

#ifdef WIN32
	iCloseSockRes = closesocket( m_iSocket);
#else //Linux
	iCloseSockRes = close( m_iSocket);
#endif
}

AXIS_TRANSPORT_STATUS SimpleAxisTransport::sendBytes( const char *pcSendBuffer, const void *pBufferId)
{
    m_strPayloadToSend += pcSendBuffer;

    return TRANSPORT_FINISHED;
/*
    if (!pBufferId)		// temporary buffers should always sent immediately 
    {
	if ((send (m_iSocket, pcSendBuffer, (int) strlen( pcSendBuffer), MSG_DONTROUTE)) == -1)
	    return TRANSPORT_FAILED;
	return TRANSPORT_FINISHED;
    }

    for (int index = 0; index < NO_OF_SERIALIZE_BUFFERS; index++)
    {
	if (!m_pBuffers[index].pcBuffer)
	{
	    m_pBuffers[index].pcBuffer = pcSendBuffer;
	    m_pBuffers[index].pBufferId = pBufferId;
	    break;
	}
    }
    return TRANSPORT_IN_PROGRESS;
*/
}

int SimpleAxisTransport::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char * value)
{
	const char *	key = NULL;
	int				iSuccess = AXIS_FAIL;

	switch( type)
	{
		case SOAPACTION_HEADER:	/* needed only in the client side ? */
			break;
	
		case SERVICE_URI:		/* need to set ? */
			break;

		case OPERATION_NAME:	/* need to set ? */
			break;

		case SOAP_MESSAGE_LENGTH: /* This is apache module and transport is http so the key */
			key = "Content-Length";
			break;

		default:
			;
	}

	if( key)
	{
		iSuccess = setTransportProperty( key, value);
	}

	return AXIS_SUCCESS;
}

AXIS_TRANSPORT_STATUS SimpleAxisTransport::flushOutput()
{
    int		contentLength = (int) m_strPayloadToSend.length();
    char	strtonum[8];

	if( contentLength != 0)	// do only if the http body is not empty. 
    {
		sprintf( strtonum, "%d", contentLength); // This assumes that the content length will be less that 8 digits (9,999,999 bytes).

		setTransportProperty( SOAP_MESSAGE_LENGTH, strtonum);

		m_strHTTPHeaders = std::string( "HTTP/1.1 200 OK\r\n") +
						   std::string( "Server: Apache Axis C++/1.6.a\r\n") +
						   std::string( "Connection: close\r\n") +
						   m_strHTTPHeaders +
						   std::string( "Content-Type: text/xml\r\n\r\n");

		if( (send( m_iSocket,
				   m_strHTTPHeaders.c_str(),
				   (int) m_strHTTPHeaders.size(),
				   MSG_DONTROUTE)) == -1)
		{
			return TRANSPORT_FAILED;
		}

        if( (send( m_iSocket,
				   m_strPayloadToSend.c_str(),
				   (int) m_strPayloadToSend.length(),
				   MSG_DONTROUTE)) == -1)
		{
			return TRANSPORT_FAILED;
		}
    }


	return TRANSPORT_FINISHED;
}

AXIS_TRANSPORT_STATUS SimpleAxisTransport::getBytes( char * pBuffer, int * piSize)
{
    if( m_strReceived.length () <= 0)
    {
		pBuffer[0] = '\0';
		*piSize = 0;

		return TRANSPORT_FINISHED;
    }

    if( (int) m_strReceived.length() < *piSize)
    {
		pBuffer[0] = '\0';

		strcat( pBuffer, m_strReceived.c_str());

		*piSize = (int) m_strReceived.length();

		m_strReceived = "";

		return TRANSPORT_FINISHED;
    }
    else
    {
		pBuffer[0] = '\0';

		std::string strToSend = m_strReceived.substr( *piSize - 1);

		strcat( pBuffer, strToSend.c_str());

		*piSize = (int) strToSend.length();

		m_strReceived = m_strReceived.substr( (*piSize),
											  m_strReceived.length() - *piSize);

		return TRANSPORT_IN_PROGRESS;
    }
}

void SimpleAxisTransport::readFromClient()
{
    int					len_read = 0;
    const unsigned int	BUF_SIZE = 48000;
    char				arr[BUF_SIZE];
    unsigned int		iStartPos = (int) std::string::npos;

    std::string strReceived = "";

    do
    {
		len_read = recv( m_iSocket, arr, BUF_SIZE - 1, 0);

		if( len_read < 0)
		{
			return;
		}

		arr[len_read] = '\0';

		strReceived += arr;

		iStartPos = (int) strReceived.find( "\r\n\r\n");
	} while( iStartPos == std::string::npos);

    iStartPos += 4;

	unsigned int uiServiceStartPos = (unsigned int) (strReceived.find( "POST ") + strlen( "POST "));
    unsigned int uiServiceEndPos = (unsigned int) strReceived.find( " ", uiServiceStartPos);

    m_strServiceURI = strReceived.substr( uiServiceStartPos, uiServiceEndPos - uiServiceStartPos);

	unsigned int uiActionStartPos =(unsigned int) (strReceived.find( "SOAPAction: \"") + strlen( "SOAPAction: \""));
    unsigned int uiActionEndPos = (unsigned int) strReceived.find( "\"", uiActionStartPos);

	m_strSOAPAction = strReceived.substr (uiActionStartPos, uiActionEndPos - uiActionStartPos);

    unsigned int uiEnvelopePos = (unsigned int) strReceived.find( "Envelope");

	// Find the beginning of the SOAP message by finding the opening 'Envelope' tag.
	while( uiEnvelopePos == std::string::npos)
	{
		len_read = recv (m_iSocket, arr, BUF_SIZE - 1, 0);

		arr[len_read] = '\0';

		strReceived += arr;

		uiEnvelopePos = (unsigned int) strReceived.find( "Envelope");
	}

    uiEnvelopePos += (unsigned int) strlen( "Envelope");

    unsigned int uiEnvelopeEndPos = (unsigned int) strReceived.find( "Envelope", uiEnvelopePos);

	// Find the end of the SOAP message by finding the matching closing 'Envelope' tag.
    while( uiEnvelopeEndPos == std::string::npos)
    {
		len_read = recv( m_iSocket, arr, BUF_SIZE - 1, 0);

		arr[len_read] = '\0';

		strReceived += arr;

		uiEnvelopeEndPos = (unsigned int) strReceived.find( "Envelope", uiEnvelopePos);
    }

    m_strReceived = strReceived.substr( iStartPos, strReceived.length () - iStartPos);

}

const char * SimpleAxisTransport::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE eType)
{
	switch( eType)
	{
		case SOAPACTION_HEADER:
		{
			return getTransportProperty( "SOAPAction");
		}

		case SERVICE_URI:
		{
			readFromClient();

			if( m_strServiceURI.find( AXIS_URI_EXTENSION) != std::string::npos)
			{
				unsigned int uiStartPos = (unsigned int) (m_strServiceURI.find( AXIS_URI_EXTENSION) +
														  strlen( AXIS_URI_EXTENSION) +
														  1);

				m_strTransportPropertyURI = m_strServiceURI.substr( uiStartPos,
																	m_strServiceURI.length() - uiStartPos);

				return m_strTransportPropertyURI.c_str();
			}

			return m_strServiceURI.c_str();
		}

		case OPERATION_NAME:
		{
			unsigned int uiOpStart = (unsigned int) m_strSOAPAction.find( SOAPACTION_METHODNAME_SEPARATOR);

			if( uiOpStart != std::string::npos)
			{
				uiOpStart += (unsigned int) strlen( SOAPACTION_METHODNAME_SEPARATOR);

				m_strTransportPropertyOperation = m_strSOAPAction.substr( uiOpStart,
																		  m_strSOAPAction.length() - uiOpStart);

				return m_strTransportPropertyOperation.c_str();
			}

			return m_strSOAPAction.c_str();
		}

		case SOAP_MESSAGE_LENGTH:
		{
			return getTransportProperty( "Content-Length");
		}

		default:
		{
			;
		}
	}
    
	return NULL;
}

int SimpleAxisTransport::setTransportProperty( const char * pcKey, const char * pcValue)
{
    m_strHTTPHeaders += std::string( pcKey) +
						std::string( ": ") +
						std::string( pcValue) +
						std::string( "\r\n");

    return 0;
}

const char * SimpleAxisTransport::getTransportProperty( const char * pcKey, bool response)
{
    return 0;
}

void SimpleAxisTransport::setSessionId( const char * pcSessionId)
{
}

const char * SimpleAxisTransport::getSessionId()
{
    return "this is temporary session id";	//TODO
}

const char * SimpleAxisTransport::getServiceName()
{
    return 0;			//TODO
}

AXIS_PROTOCOL_TYPE SimpleAxisTransport::getProtocol()
{
    return APTHTTP1_1;
}

int SimpleAxisTransport::setProtocol(AXIS_PROTOCOL_TYPE eProtocol)
{
    if( eProtocol == APTHTTP1_1 || eProtocol == APTHTTP1_0)
    {
       m_eProtocolType = eProtocol;

       return AXIS_SUCCESS;
    }

	return AXIS_FAIL;
}


int SimpleAxisTransport::getSubProtocol()
{
    return AXIS_HTTP_POST;
}
