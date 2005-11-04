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
*/

/*
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4101)
#endif

#include "HTTPTransport.hpp"
#include "../../platforms/PlatformAutoSense.hpp"

#include <stdio.h>
#include <iostream>

// =================================================================
// In order to parse the HTTP protocol data on an ebcdic system, we
// need to ensure that the various tokens we are looking for to distinguish
// between the HTTP headers and payload are in ASCII.  So the following 
// defines for carriage return-line feed, etc. are ensured to be in ascii
// by using ascii hexadecimal representation of the tokens.
// =================================================================

// Ascii character defines                   
#define ASCII_C_EQUAL         '\x3D'    // '='  
#define ASCII_C_DASH          '\x2D'    // '-'  
#define ASCII_C_LF            '\x0A'    // '\n'
#define ASCII_C_CR            '\x0D'    // '\r' 
#define ASCII_C_SPACE         '\x20'    // ' ' 
#define ASCII_C_SEMI          '\x3B'    // ';' 

#define ASCII_C_LOWERCASEA    '\x61'    // 'a'
#define ASCII_C_LOWERCASEF    '\x66'    // 'f'
#define ASCII_C_UPPERCASEA    '\x41'    // 'A'
#define ASCII_C_UPPERCASEF    '\x46'    // 'F'

#define ASCII_C_ZERO          '\x30'    // '0'
#define ASCII_C_NINE          '\x39'    // '9'

// Ascii string defines
#define ASCII_S_LF             "\x0a"                 // "\n"     
#define ASCII_S_CRLF           "\x0d\x0a"             // "\r\n"     
#define ASCII_S_CRLFCRLF       "\x0d\x0a\x0d\x0a"     // "\r\n\r\n"  

#define ASCII_S_HTTP           "\x48\x54\x54\x50"     // "HTTP"
#define ASCII_S_CONTENT_LENGTH "\x43\x6F\x6E\x74\x65\x6E\x74\x2D\x4c\x65\x6e\x67\x74\x68\x3a\x20" // "Content-Length: " 
#define ASCII_S_TRANSFERENCODING_CHUNKED "\x54\x72\x61\x6E\x73\x66\x65\x72\x2D\x45\x6E\x63\x6F\x64\x69\x6E\x67\x3A\x20\x63\x68\x75\x6e\x6b\x65\x64" // "Transfer-Encoding: chunked"

#define ASCII_S_LEFTPAREN      "\x28"   // "("
#define ASCII_S_COLON          "\x3A"   // ":" 

/*
 * HTTPTransport constuctor
 */
HTTPTransport::HTTPTransport ():m_bReopenConnection (false),
m_strHTTPProtocol ("HTTP/1.1"),
m_strHTTPMethod ("POST"),
m_strProxyHost (""), m_uiProxyPort (0), m_bUseProxy (false),
m_bMaintainSession (false)
{
    m_pcEndpointUri = NULL;
    m_pReleaseBufferCallback = 0;
    m_eProtocolType = APTHTTP1_1;
    m_strBytesToSend = "";
    m_strHeaderBytesToSend = "";
    m_iBytesLeft = 0;
    m_iContentLength = 0;
	m_bChannelSecure = false;
    m_pNormalChannel = 0;
    m_pSecureChannel = 0;
	m_pActiveChannel = 0;
    m_pChannelFactory = new ChannelFactory();
    m_bMimeTrue = false;
    m_viCurrentHeader = m_vHTTPHeaders.begin();
	m_pszRxBuffer = new char [BUF_SIZE];
#ifdef WIN32
	m_lChannelTimeout = 10;
#else
	m_lChannelTimeout = 0;
#endif
	m_pNormalChannel = m_pChannelFactory->createChannel(UnsecureChannel);
	m_pSecureChannel = m_pChannelFactory->createChannel(SecureChannel);

	m_GetBytesState = eWaitingForHTTPHeader;
}

/*
 * HTTPTransport destructor
 */
HTTPTransport::~HTTPTransport()
{
    if( m_pcEndpointUri)
    {
		delete[] m_pcEndpointUri;
    }

    if( m_pChannelFactory)
	{
		delete m_pChannelFactory;
		m_pChannelFactory = 0;
	}

	delete [] m_pszRxBuffer;
}

/*
 * HTTPTransport::setEndpointUri( EndpointURI) sets the URI for the message.
 * Everytime the endpoint changes then currently connected channel is closed
 * and a new channel connection is opened.
 *
 * @param	EndpointURI - char * to a null terminated string that holds the
 *			new URI. 
 */
void HTTPTransport::setEndpointUri( const char * pcEndpointUri) throw (HTTPTransportException)
{
    bool bUpdateURL = false;

    if (!pcEndpointUri) // We have NULL so cannot proceed
        return;

    // Samisa:We have to have at lest "http://" in the URL
    // We also need to handle passing " " as URL which 
    // is done by some auto generated code
    if ( strlen(pcEndpointUri) < strlen("http://") ) 
        return;
                                                  

    // Get the current channel URI
    if( m_pActiveChannel != NULL && m_pActiveChannel->getURL())
    {
		// Does the new URI equal the existing channel URI?
		if( strcmp (m_pActiveChannel->getURL (), pcEndpointUri) != 0)
		{
	    	// There is a new URI.
			bUpdateURL = true;
		}
    }
    else
    {
		bUpdateURL = true;
    }


    // If there is a new URI, then this flag will be set.  Depending on whether
    // there is an SSL implementation available, if the new URI is a secure
	// connection, a secure channel will be opened.  If an SSL implementation
	// is not available and the URL requires a secure connection then an
	// exception will be thrown.
    if( bUpdateURL)
    {
		if( m_pActiveChannel == NULL)
		{
			m_pActiveChannel = m_pNormalChannel;
		}

		m_pActiveChannel->setURL( pcEndpointUri);

		m_bReopenConnection = true;

		// Check if the new URI requires SSL (denoted by the https prefix).
		if( (m_pActiveChannel->getURLObject()).getProtocol() == URL::https)
		{
			if( m_pSecureChannel != NULL)
			{
				m_pNormalChannel->close();

				m_pActiveChannel = m_pSecureChannel;

				m_pActiveChannel->setURL( pcEndpointUri);

				m_bChannelSecure = true;
			}

			if( !m_bChannelSecure)
			{
				throw HTTPTransportException( CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER);
			}
		}
		else
		{
	    	// URI does not require a secure channel.  Delete the existing
	    	// channel if it is secure and create a new unsecure
	    	// channel.
			if (m_bChannelSecure)
			{
				if( m_pNormalChannel != NULL)
				{
					m_pSecureChannel->close();

					m_pActiveChannel = m_pNormalChannel;
					m_pActiveChannel->setURL( pcEndpointUri);
					m_bChannelSecure = false;
				}

				if( m_bChannelSecure)
				{
					throw HTTPTransportException( CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER);
				}
			}
		}
    }

	// Need this code to set the channel timeout.  If the timeout was changed
	// before the channel was created, then it may not have the correct timeout.
	// By setting it here, the channel is sure to have the correct timeout value
	// next time the channel is read.
	if( m_pActiveChannel != NULL)
	{
		m_pActiveChannel->setTimeout( m_lChannelTimeout);
	}
}

/*
 * HTTPTransport::openConnection().
 */

int HTTPTransport::openConnection()
{
    if( m_bReopenConnection)
    {
		m_bReopenConnection = false;

		if( m_pActiveChannel->open() != AXIS_SUCCESS)
		{
		    int	iStringLength = m_pActiveChannel->GetLastErrorMsg().length() + 1;
			const char * pszLastError = new char[iStringLength];

		    memcpy( (void *) pszLastError,
					m_pActiveChannel->GetLastErrorMsg().c_str(),
					iStringLength);

		    throw HTTPTransportException( CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED,
										  (char *) pszLastError);
		}
	}
    return AXIS_SUCCESS;
}

/*
 * HTTPTransport::closeConnection().
 */
void HTTPTransport::closeConnection()
{
    // get ready for a new message.
	m_GetBytesState = eWaitingForHTTPHeader;

    //clear the message buffer in preperation of the next read.
    m_strReceived = "";

    m_iContentLength = 0;

    // Samisa : closing the connection is done in setEndpointUri
    // no need to close here
    // Fix for AXISCPP-481
}

/*
 * HTTPTransport::flushOutput() Is called when the message construction is
 * complete.  The message is ready to be 'flushed out' onto the network.  
 * Check if the URI has changed.  If it has, then need to open a new Channel
 * instance before transmitting the message.
 *
 * @return AXIS_TRANSPORT_STATUS If the method completes successfully, then
 * this will be set to TRANSPORT_FINISHED.  Otherwise, an exception will have
 * been thrown.
 */
AXIS_TRANSPORT_STATUS HTTPTransport::flushOutput() throw (AxisException, HTTPTransportException)
{
	char *utf8Buf = NULL; // buffer for ebcdic/utf8 conversions.
	
    // In preperation for sending the message, calculate the size of the message
    // by using the string length method.
    char buff[24];
	sprintf( buff, "%d", m_strBytesToSend.length ());
    this->setTransportProperty ("Content-Length", buff);

    // The header is now complete.  The message header and message can now be
    // transmitted.
	try
	{
#ifndef __OS400__
		*m_pActiveChannel << this->getHTTPHeaders ();
		*m_pActiveChannel << this->m_strBytesToSend.c_str ();
#else
        // Ebcdic (OS/400) systems need to convert the data to UTF-8. Note that free() is 
        // correctly used and should not be changed to delete().		
        const char *buf = this->getHTTPHeaders ();
        utf8Buf = toUTF8((char *)buf, strlen(buf)+1);
		*m_pActiveChannel << utf8Buf;
        free(utf8Buf);
        utf8Buf = NULL;
        utf8Buf = toUTF8((char *)this->m_strBytesToSend.c_str(), this->m_strBytesToSend.length()+1);
		*m_pActiveChannel << utf8Buf;
        free(utf8Buf);
        utf8Buf = NULL;
#endif
	}
	catch( HTTPTransportException & e)
	{
		if (utf8Buf) free(utf8Buf);
        m_strBytesToSend = "";
        m_strHeaderBytesToSend = "";
		throw;
	}
	catch( AxisException & e)
	{
		if (utf8Buf) free(utf8Buf);
        m_strBytesToSend = "";
        m_strHeaderBytesToSend = "";
		throw;
	}
	catch(...)
	{
		if (utf8Buf) free(utf8Buf);
        m_strBytesToSend = "";
        m_strHeaderBytesToSend = "";
		throw;
	}

    // Empty the bytes to send string.
	m_strBytesToSend = "";
	m_strHeaderBytesToSend = "";

	return TRANSPORT_FINISHED;
}

/* HTTPTransport::getHTTPHeaders() Called to retreive the current HTTP header
 * information block that will preceed the SOAP message.
 *
 * @return const char* Pointer to a NULL terminated character string containing
 * the HTTP header block of information.
 */
const char * HTTPTransport::getHTTPHeaders()
{
    URL &           url = m_pActiveChannel->getURLObject(); 
    unsigned short	uiPort;
    char			buff[32];

    m_strHeaderBytesToSend = m_strHTTPMethod + " ";

    if (m_bUseProxy)
    {
        m_strHeaderBytesToSend += url.getURL ();
        m_strHeaderBytesToSend += " ";
        m_strHeaderBytesToSend += m_strHTTPProtocol;
        m_strHeaderBytesToSend += "\r\nHost: ";
        m_strHeaderBytesToSend += m_strProxyHost;
        uiPort = m_uiProxyPort;
    }
    else
    {
		m_strHeaderBytesToSend += url.getResource ();
        m_strHeaderBytesToSend += " ";
        m_strHeaderBytesToSend += m_strHTTPProtocol;
		m_strHeaderBytesToSend += "\r\nHost: ";
		m_strHeaderBytesToSend += url.getHostName ();
        uiPort = url.getPort();
    }  

    sprintf(buff, ":%u\r\n", uiPort);
    m_strHeaderBytesToSend += buff; 

	bool foundCT = false;
    for (unsigned int j = 0; j < m_vHTTPHeaders.size (); j++)
    {
		if (0==strcmp(AXIS_CONTENT_TYPE,m_vHTTPHeaders[j].first.c_str())) foundCT = true;
    }

	// The Content-Type must be set, but it may already be set in m_strHeaderBytesToSend
	// if we're using attachments, for example.
	if (!foundCT)
		m_strHeaderBytesToSend += AXIS_CONTENT_TYPE ": text/xml; charset=UTF-8\r\n";

    // Set other HTTP headers
    for (unsigned int i = 0; i < m_vHTTPHeaders.size (); i++)
    {
		m_strHeaderBytesToSend += m_vHTTPHeaders[i].first;
		m_strHeaderBytesToSend += ": ";
		m_strHeaderBytesToSend += m_vHTTPHeaders[i].second;
		m_strHeaderBytesToSend += "\r\n";
    }

    // Set session cookie
    if (m_bMaintainSession && (m_strSessionKey.size () > 0))
    {
		m_strHeaderBytesToSend += "Cookie";
		m_strHeaderBytesToSend += ": ";
		m_strHeaderBytesToSend += m_strSessionKey;
		m_strHeaderBytesToSend += "\r\n";
    }

    m_strHeaderBytesToSend += "\r\n";

    return m_strHeaderBytesToSend.c_str ();
}

/* HTTPTransport::getHTTPMethod() Is a public method that gets the HTTP method
 * (i.e. GET or POST) that will be part of the HTTP header block.
 *
 * @return const char* Pointer to a NULL terminated character string containing
 * the HTTP method.
 */
const char * HTTPTransport::getHTTPMethod()
{
    return m_strHTTPMethod.c_str ();
}

/* HTTPTransport::setHTTPMethod( Method) Is a public method that sets the HTTP
 * method (i.e. POST or GET) that will be part of the HTTP header block.
 *
 * @param const char* Pointer to a NULL terminated character string containing
 * the new HTTP method.
 */
void HTTPTransport::setHTTPMethod( const char *cpMethod)
{
    m_strHTTPMethod = std::string( cpMethod);
}

/* HTTPTransport::sendBytes( SendBuffer, BufferId) Is a public method that
 * concatinates the new send buffer to the bytes to send string.  This message
 * will only be sent when a flush buffer is received.
 *
 * @param const char* SendBufer - Pointer to a NULL terminated character string
 * containing all or some of the transmission message.
 * @param const void* BufferId - Pointer.  This parameter is ignored.
 *
 * @return AXIS_TRANSPORT_STATUS Value to a status value (currently it will
 * always be TRANSPORT_IN_PROGRESS).
 */
AXIS_TRANSPORT_STATUS HTTPTransport::sendBytes( const char *pcSendBuffer, const void *pBufferId)
{
    m_strBytesToSend += std::string (pcSendBuffer);

    return TRANSPORT_IN_PROGRESS;
}

/* HTTPTransport::getBytes( ReceiveBuffer, Size) Is a public method that will
 * receive the synchronous reply to the sent message.
 *
 * @param const char* ReceiveBuffer - Pointer to a character string that on
 * return will containing all or part of the received message.
 * @param int* Size - Pointer to an integer value that on return will contain
 * the length of the received message.
 *
 * @return AXIS_TRANSPORT_STATUS Value to the status o message reception
 * (TRANSPORT_FINISHED or TRANSPORT_IN_PROGRESS).
 */
AXIS_TRANSPORT_STATUS HTTPTransport::getBytes( char * pcBuffer, int * piSize) throw (AxisException, HTTPTransportException)
{
	std::string	nextChunk = "";

// It is assumed that the constructor has initialised the following variables:-
// Type			Label			Initial Value		Description
// enum			m_eMsgState		eHTTP_Header		Message decode state.
// int			m_iBytesLeft	0					Size of string held in m_strReceived.
// char *		m_pszRxBuffer	new char [BUF_SIZE]	Local buffer with message read from channel.
// std::string	m_strReceived   <uninitialised>		Contains the concatination of all unprocessed message string parts.

// The method getBytes has three distinct states.  These are defined as
// follows:-
//   eWaitingForHTTPHeader    - Waiting for a 'valid' HTTP header.  A header is
//                              is valid when a 'HTTP' string is found that is
//                              subsequently followed by a CRLFCRLF sequence.
//                              The HTTP header is then read and if the message
//                              number is incorrect an exception is thrown.
//                              The header also contains information on whether
//                              the accompanying message is or is not chunked.
//   eSOAPMessageIsChunked    - When a message is chunked, it has been broken
//                              into a number of blocks.  Each block is
//                              preceeded by a hex number.  The number is the
//                              chunk length.  A zero length chunk represents
//                              the end of the message.
//                              NB: because AXIS uses a 'pull' parser, the last
//                                  chunk size should never be read as the
//                                  parser will return once it has encountered
//                                  '</envelope>'.  If it does read the last
//                                  '0', this could indicate that there is a
//                                  problem in the message.
//   eSOAPMessageIsNotChunked - The message is read until the number of message
//                              bytes read equals the HTTP header content
//                              length value.
	switch( m_GetBytesState)
	{
		case eWaitingForHTTPHeader:
		{
		// Wait for a HTTP header to be located on the input stream.
			do
			{
		// From the input stream, wait for a 'valid' HTTP header.
				readHTTPHeader();

		// From the header,extract such things as chunking, message length, etc.
				processHTTPHeader();

			} while( m_iResponseHTTPStatusCode == 100);

		// Check that the HTTP status code is valid.
			checkHTTPStatusCode();

		// Done with HTTP headers, get SOAP message.
			int iHTTPStart = m_strReceived.find( ASCII_S_HTTP);
			int iHTTPEnd = m_strReceived.find( ASCII_S_CRLFCRLF, iHTTPStart);

			m_strReceived = m_strReceived.substr( iHTTPEnd + strlen( ASCII_S_CRLFCRLF));

			m_iBytesLeft = m_strReceived.length();

		// This bit of code should not be necessary, but just in case...
			if( m_GetBytesState == eWaitingForHTTPHeader)
			{
				break;
			}
		}

		// At this point it is assumed that m_strReceived contains the block of
		// unprocessed data.  m_iBytesLeft is the length of text/data in m_strReceived
		// is a 'char *' type copy of the m_strReceived string.
		// NB: It is assumed that all of these variables ARE in sync at this point.
		case eSOAPMessageIsChunked:
			{
				if( m_GetBytesState == eSOAPMessageIsChunked)
				{
					if( m_iBytesLeft == 0)
					{
						getNextDataPacket( "No data available for next chunk size.");
					}

					m_iContentLength = getChunkSize();

		// If the chunk size is larger than the available data, then read in more data
		// until all of the chunk has been read.
					while( m_iContentLength > m_iBytesLeft)
					{
						getNextDataPacket( "No data available for next chunk.");
					}

		// If data read is longer than chunk size, then copy the extra data to a
		// temporary variable and process data just belonging to this chunk.
					if( m_iBytesLeft > m_iContentLength)
					{
						nextChunk = m_strReceived.substr( m_iContentLength + strlen( ASCII_S_CRLF));
						m_strReceived = m_strReceived.substr( 0, m_iContentLength);
						m_iBytesLeft = m_iContentLength;

		// Check to see if the next chunk size is zero.  If it is then change the state.
						if( peekChunkLength( nextChunk) == 0)
						{
							m_GetBytesState = eWaitingForHTTPHeader;
						}
					}
					else
					{
						nextChunk = "";
					}

		// Now have at least chunk size worth of data.  The chunk may contain Mime data
		// (this depends on information in the HTTP header).  If Mime data is expected,
		// process it first.
					if( m_bMimeTrue)
					{
						processRootMimeBody();

						m_iBytesLeft = m_strReceived.length();
					}

					break;
				}
			}

		case eSOAPMessageIsNotChunked:
		{
		// Check that there is more message to read.
			if( m_iContentLength > 0)
			{
				getNextDataPacket( "No data available for message.");

		// Check for Mime header
				if( m_bMimeTrue)
				{
					processRootMimeBody();

					m_iBytesLeft = m_strReceived.length();
				}

		// Subtract message length (so far) from expcted content length.
				m_iContentLength -= m_iBytesLeft;

		// If all of the message has been received, then reset the process state.
				if( m_iContentLength <= 0)
				{
					m_GetBytesState = eWaitingForHTTPHeader;
				}
			}
			else
			{

		// Reset the process state.
				m_GetBytesState = eWaitingForHTTPHeader;
			}

		break;
		}
	}

// Copy as much of the message to the parser buffer as possible.
	if( copyDataToParserBuffer( pcBuffer, piSize, m_iBytesLeft))
	{
		m_strReceived += nextChunk;
		m_iBytesLeft = m_strReceived.length();

		return TRANSPORT_IN_PROGRESS;
	}

	return TRANSPORT_FINISHED;
}

/* HTTPTransport::setTransportProperty( Type, Value) Is an overloaded public
 * method used to set a HTTP transport or SSL implementation property.
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE Type is an enumerated type containing
 * the type of information to be stored in either the HTTP Header or SSL
 * implementation settings.
 * @param const char* Value is a NULL terminated character string containing
 * the value associated with the type.
 */
int HTTPTransport::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char *value) throw (HTTPTransportException)
{
    const char *key = NULL;
	int			iSuccess = AXIS_SUCCESS;

    switch (type)
    {
	    case SOAPACTION_HEADER:
		{
			key = "SOAPAction";
		    break;
		}

		case SERVICE_URI:		// need to set ?
		{
			break;
		}

		case OPERATION_NAME:	// need to set ?
		{
			break;
		}

		case SOAP_MESSAGE_LENGTH:
		{
			key = "Content-Length";	// this Axis transport handles only HTTP
			break;
		}

		case TRANSPORT_PROPERTIES:
		{
			if( m_pActiveChannel != NULL)
			{
				m_pActiveChannel->setTransportProperty( type, value);
			}

			break;
		}

		case SECURE_PROPERTIES:
		{
			if( m_pActiveChannel != NULL)
			{
				iSuccess = m_pActiveChannel->setSecureProperties( value);
			}
			break;
		}

		case CHANNEL_HTTP_DLL_NAME:
		{
			if( m_pChannelFactory != NULL)
			{
				m_pNormalChannel = m_pChannelFactory->LoadChannelLibrary( UnsecureChannel, value);
			}
			break;
		}

		case CHANNEL_HTTP_SSL_DLL_NAME:
		{
			if( m_pChannelFactory != NULL)
			{
				m_pSecureChannel = m_pChannelFactory->LoadChannelLibrary( SecureChannel, value);
			}
			break;
		}

		default:
		{
			break;
		}
    }

    if( key)
    {
		setTransportProperty( key, value);
    }

	return iSuccess;
}

/* HTTPTransport::setTransportProperty( Key, Value) Is an overloaded public
 * method used to set a HTTP transport or SSL implementation property.
 *
 * @param const char* Key is a NULL terminated character string containing
 * the type of information to be stored in either the HTTP Header or SSL
 * implementation settings.
 * @param const char* Value is a NULL terminated character string containing
 * the value associated with the type.
 */
int HTTPTransport::setTransportProperty( const char *pcKey, const char *pcValue) throw (HTTPTransportException)
{
    if( !pcKey || !pcValue)	// Samisa - fix for AXISCPP-295. We must check for valid values here.
	{
		return AXIS_SUCCESS;
	}

    bool b_KeyFound = false;

    if( strcmp( pcKey, "SOAPAction") == 0 || strcmp( pcKey, "Content-Length") == 0)
    {
		std::string strKeyToFind = std::string( pcKey);

		for (unsigned int i = 0; i < m_vHTTPHeaders.size(); i++)
		{
		    if (m_vHTTPHeaders[i].first == strKeyToFind)
			{
				m_vHTTPHeaders[i].second = (string) pcValue;

				b_KeyFound = true;

				break;
		    }
		}
    }

    if( !b_KeyFound)
    {
		m_vHTTPHeaders.push_back( std::make_pair( (string) pcKey, (string) pcValue));
    }

	return AXIS_SUCCESS;
}

/* HTTPTransport::getTransportProperty( Type) Is a public method that will
 * return the HTTP Header/SSL implementation value associated with type.
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE Type is an enumerated type containing
 * the type of information to be retrieved in either the HTTP Header or SSL
 * implementation settings.
 *
 * @return const char* Value is a NULL terminated character string containing
 * the value associated with the type.
 */
const char * HTTPTransport::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE eType) throw (HTTPTransportException)
{
    const char *pszPropValue = NULL;

    switch( eType)
    {
	    case SOAPACTION_HEADER:
		{
			int iIndex = FindTransportPropertyIndex( "SOAPAction");

		    if (iIndex > -1)
		    {
				pszPropValue = m_vHTTPHeaders[iIndex].second.c_str();
		    }

		    break;
		}

	    case SERVICE_URI:
		{
			break;
		}

	    case OPERATION_NAME:
		{
			break;
		}

	    case SOAP_MESSAGE_LENGTH:
		{
			int iIndex = FindTransportPropertyIndex( "Content-Length");

		    if (iIndex > -1)
		    {
				pszPropValue = m_vHTTPHeaders[iIndex].second.c_str();
		    }

		    break;
		}

	case TRANSPORT_PROPERTIES:
    case SECURE_PROPERTIES:
		{
			pszPropValue = m_pActiveChannel->getTransportProperty( eType);
			break;
		}

	case CHANNEL_HTTP_SSL_DLL_NAME:
	case CHANNEL_HTTP_DLL_NAME:
    case CONTENT_TYPE:
		{
			break;
		}
    }

    return pszPropValue;
}

/* HTTPTransport::FindTransportPropertyIndex( Key) Is a private method that will
 * return the HTTP Header index associated with Key.
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE Key is an enumerated type containing
 * the type of information to be retrieved in either the HTTP Header settings.
 *
 * @return int Index is an index to the key within the HTTP Header list.  If
 * the return value is -1, then the key was not found.
 */
int HTTPTransport::FindTransportPropertyIndex( string sKey)
{
    bool	bKeyFound = false;
    int		iIndex = 0;

    while( (unsigned int) iIndex < m_vHTTPHeaders.size() && !bKeyFound)
    {
		if (!m_vHTTPHeaders[iIndex].first.compare( sKey))
		{
			bKeyFound = true;
		}
		else
		{
			iIndex++;
		}
    } 

    if( !bKeyFound)
    {
		iIndex = -1;
    }

    return iIndex;
}

/* HTTPTransport::getServiceName() Is a public method to return the HTTP
 * Header service name.
 *
 * @return const char* Value is a NULL terminated character string containing
 * the value associated with the service name.
 */
const char * HTTPTransport::getServiceName()
{
    //Assume SOAPAction header to contain service name
    int		iIndex = FindTransportPropertyIndex( "SOAPAction");

    if (iIndex > -1)
    {
		return m_vHTTPHeaders[iIndex].second.c_str();
    }

    return NULL;
}


AXIS_PROTOCOL_TYPE HTTPTransport::getProtocol()
{
    return m_eProtocolType;
}

int HTTPTransport::setProtocol( AXIS_PROTOCOL_TYPE eProtocol)
{
    if (eProtocol == APTHTTP1_1 || eProtocol == APTHTTP1_0)
    {
		m_eProtocolType = eProtocol;

		m_strHTTPProtocol = (m_eProtocolType == APTHTTP1_1) ? "HTTP/1.1" : "HTTP/1.0";

		return AXIS_SUCCESS;
    }
    else
	{
		return AXIS_FAIL;
	}
}

/**
 * HTTPTransport::getSubProtocol() is a public method that is supposed to
 * return the sub protocol (currently this method always return 0).
 * This method is supposed to return whether it is http GET or POST
 */
int HTTPTransport::getSubProtocol()
{
    //TODO
    // for SimpleAxisServer assume POST
    return AXIS_HTTP_POST;
    //return 0;
}

/* HTTPTransport::setProxy( Host, Port) Is a public method for setting or
 * updating the proxy for the connection.
 *
 * @param const char* Host is a NULL terminated character string containing the new
 * proxy host.
 * @param unsigned int Port is the new proxy port number.
 */
void HTTPTransport::setProxy( const char *pcProxyHost, unsigned int uiProxyPort)
{
    m_pActiveChannel->setProxy(pcProxyHost,uiProxyPort);
	m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;
}

/* HTTPTransport::setTimeout( Timeout) Is a public method for setting the
 * current maximum timeout period between that can elapse between receiving
 * message parts.
 *
 * @param const long Timeout is a long value in seconds.
 */
void HTTPTransport::setTimeout( const long lSeconds)
{
	if( m_pActiveChannel != NULL)
	{
		m_pActiveChannel->setTimeout( lSeconds);
	}

	m_lChannelTimeout = lSeconds;
}

/* HTTPTransport::getHTTPProtocol() Is a public method for retrieving the
 * current HTTP protocol settings.
 *
 * @return const char* HTTPProtocol is a NULL terminated character string
 * containing the HTTP protocol.
 */
const char * HTTPTransport::getHTTPProtocol()
{
    return m_strHTTPProtocol.c_str ();
}

/* axtoi( Hex) Is a private method to convert an ascii hex string to an integer.
 */
int axtoi( char *pcHexStg)
{
    int		iN = 0;			// position in string
    int		iM = 0;			// position in digit[] to shift
    int		iCount;			// loop index
    int		intValue = 0;	// integer value of hex string
    int		iDigit[32];		// hold values to convert

    while( iN < 32)
    {
		if( pcHexStg[iN] == '\0')
		{
			break;
		}
	
		if( pcHexStg[iN] >= ASCII_C_ZERO && 
			pcHexStg[iN] <= ASCII_C_NINE)
		{
			iDigit[iN] = pcHexStg[iN] & 0x0f;	//convert to int
		}
		else if ((pcHexStg[iN] >= ASCII_C_LOWERCASEA && 
		          pcHexStg[iN] <= ASCII_C_LOWERCASEF) ||
		         (pcHexStg[iN] >= ASCII_C_UPPERCASEA && 
		          pcHexStg[iN] <= ASCII_C_UPPERCASEF))
		{
			iDigit[iN] = (pcHexStg[iN] & 0x0f) + 9;	//convert to int
		}
		else
		{
			break;
		}

		iN++;
    }

    iCount = iN;
    iM = iN - 1;
    iN = 0;

    while( iN < iCount)
    {
		// digit[n] is value of hex digit at position n
		// (m << 2) is the number of positions to shift
		// OR the bits into return value
		intValue = intValue | (iDigit[iN] << (iM << 2));
		iM--;			// adjust the position to set
		iN++;			// next digit to process
    }

    return intValue;
}

/* HTTPTransport::processResponseHTTPHeaders() Is a public method used to
 * parse the HTTP header of the response message.
 */
void HTTPTransport::processResponseHTTPHeaders() throw (HTTPTransportException)
{
    unsigned long iPosition = std::string::npos;
    unsigned long iStartPosition = iPosition;

    if( (iPosition = m_strResponseHTTPHeaders.find( ASCII_S_HTTP )) != std::string::npos)
    {
		m_strResponseHTTPProtocol = m_strResponseHTTPHeaders.substr( iPosition, strlen( "HTTP/1.x"));
		iPosition += strlen( "HTTP/1.x");

		while( m_strResponseHTTPHeaders.substr()[iPosition] == ASCII_C_SPACE)
		{
			iPosition++;
		}

		iStartPosition = iPosition;

		while( m_strResponseHTTPHeaders.substr()[iPosition] != ASCII_C_SPACE )
		{
			iPosition++;
		}

		std::string strResponseHTTPStatusCode = 
               m_strResponseHTTPHeaders.substr( iStartPosition,iPosition - iStartPosition);
		m_iResponseHTTPStatusCode = atoi( PLATFORM_ASCTOSTR(strResponseHTTPStatusCode.c_str()));

		iStartPosition = ++iPosition;
		iPosition = m_strResponseHTTPHeaders.find( ASCII_S_LF );
		m_strResponseHTTPStatusMessage = 
              m_strResponseHTTPHeaders.substr( iStartPosition,iPosition - iStartPosition - 1);
        PLATFORM_ASCTOSTR(m_strResponseHTTPStatusMessage.c_str());

		// reached the end of the first line
		iStartPosition = m_strResponseHTTPHeaders.find( ASCII_S_LF );

		iStartPosition++;

		// read header fields and add to vector
		do
		{
		    m_strResponseHTTPHeaders = m_strResponseHTTPHeaders.substr( iStartPosition);
			iPosition = m_strResponseHTTPHeaders.find( ASCII_S_LF );

		    if( iPosition == std::string::npos)
		    {
				break;
			}

			std::string		strHeaderLine = m_strResponseHTTPHeaders.substr( 0, iPosition);
			unsigned long	iSeperator = strHeaderLine.find( ASCII_S_COLON );

		    if( iSeperator == std::string::npos)
			{
				break;
			}

			iStartPosition = iPosition + 1;

			string	key = strHeaderLine.substr( 0, iSeperator);
			string	value = strHeaderLine.substr( iSeperator + 1,
												  strHeaderLine.length () - iSeperator - 1 - 1);
            PLATFORM_ASCTOSTR(key.c_str());
            PLATFORM_ASCTOSTR(value.c_str());

			m_vResponseHTTPHeaders.push_back( std::make_pair( key, value));

	   	 	// if HTTP/1.0 we have to always close the connection by default
		    if( m_eProtocolType == APTHTTP1_0)
			{
				m_bReopenConnection = true;
			}

	    	// if HTTP/1.1 we have to assume persistant connection by default

	    	// We need to close the connection and open a new one if we have 'Connection: close'
			if( key == "Connection" && value == " close")
			{
				m_bReopenConnection = true;
			}

            // We need to close the connection and open a new one if we have 'Proxy-Connection: close'
            if (key == "Proxy-Connection" && value == " close")
                m_bReopenConnection = true;

	    	// For both HTTP/1.0 and HTTP/1.1,
	    	// We need to keep the connection if we have 'Connection: Keep-Alive'
			if( key == "Connection" && value == " Keep-Alive")
			{
				m_bReopenConnection = false;
			}

	    	// Look for cookies
			if( m_bMaintainSession && !(m_strSessionKey.size() > 0))
		    {
				if( key == "Set-Cookie")
				{
					m_strSessionKey = value;

		    		// Spec syntax : Set-Cookie: NAME=VALUE; expires=DATE; path=PATH; domain=DOMAIN_NAME; secure
		    		// This code assumes it to be : Set-Cookie: NAME=VALUE; Anything_else
		    		// And discards stuff after first ';'
		    		// This is the same assumption used in Axis Java
					unsigned long ulKeyEndsAt = m_strSessionKey.find( ";");
		    
					if( ulKeyEndsAt != std::string::npos)
				    {
						m_strSessionKey = m_strSessionKey.substr( 0, ulKeyEndsAt);
				    }
				}
		    }

	    	/* If Content-Type: Multipart/Related; boundary=<MIME_boundary>; type=text/xml;
	       start="<content id>" */
			if( key == "Content-Type")
			{
				m_strContentType = value;
		
				unsigned long	ulMimePos = m_strContentType.find( ";");
				std::string		strTypePart;

				if( ulMimePos != std::string::npos)
				{
					strTypePart = m_strContentType.substr( 1, ulMimePos - 1);
				}
		
				if( "Multipart/Related" == strTypePart)
				{
					m_bMimeTrue = true;
					m_strContentType = m_strContentType.substr( ulMimePos + 1, m_strContentType.length());

				    ulMimePos = m_strContentType.find( "boundary=");
					m_strMimeBoundary = m_strContentType.substr( ulMimePos);
					ulMimePos = m_strMimeBoundary.find( ";");
					m_strMimeBoundary = m_strMimeBoundary.substr( 9, ulMimePos - 9);
                    PLATFORM_STRTOASC(m_strMimeBoundary.c_str());

					ulMimePos = m_strContentType.find( "type=");
					m_strMimeType = m_strContentType.substr( ulMimePos);
					ulMimePos = m_strMimeType.find( ";");
					m_strMimeType = m_strMimeType.substr( 5, ulMimePos - 5);

				    ulMimePos = m_strContentType.find( "start=");
					m_strMimeStart = m_strContentType.substr( ulMimePos);
					ulMimePos = m_strMimeStart.find( ";");
					m_strMimeStart = m_strMimeStart.substr( 6, ulMimePos - 6);
				}
			}
		} while( iPosition != std::string::npos);
    }
    else
    {
		throw HTTPTransportException( SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
									  "Protocol is not HTTP.");
    }
}

/* HTTPTransport::processRootMimeBody() Is a public method used to
 * parse the mime attachments.
 */
void HTTPTransport::processRootMimeBody()
{
    if( false == m_bReadPastRootMimeHeader)
    {
		do
		{
			if( m_strReceived.find( ASCII_S_CRLFCRLF ) == std::string::npos)
			{
				m_pszRxBuffer [0] = '\0';
				*m_pActiveChannel >> m_pszRxBuffer;
				m_strReceived += m_pszRxBuffer;
			}
		} while( m_strReceived.find( ASCII_S_CRLFCRLF ) == std::string::npos);

		//now we have found the end of root mime header
		m_bReadPastRootMimeHeader = true;

		//processMimeHeader(); For the time being we don't process this
		// Done with root mime body headers, get rest of the payload 
		// which contain the soap message
		m_strReceived = m_strReceived.substr( m_strReceived.find( ASCII_S_CRLFCRLF ) + 4);
	
		unsigned long intMimeTemp = m_strReceived.find( m_strMimeBoundary);

		if (intMimeTemp != std::string::npos)
		{
			m_strReceived = m_strReceived.substr( 0, intMimeTemp);
			m_strMimeReceived = m_strReceived.substr( intMimeTemp);
            PLATFORM_ASCTOSTR(m_strMimeReceived.c_str());

	    	// Using m_strMimeReceived will be continued when getAttachment is called.
			m_bMimeTrue = false;
		}
    }
    else
    {
		unsigned long intMimeTemp = m_strReceived.find( m_strMimeBoundary);
		
		if( intMimeTemp != std::string::npos)
		{
			m_strReceived = m_strReceived.substr( 0, intMimeTemp);
			m_strMimeReceived = m_strReceived.substr( intMimeTemp);
            PLATFORM_ASCTOSTR(m_strMimeReceived.c_str());

	    	// Using m_strMimeReceived will be continued when getAttachment is called.
			m_bMimeTrue = false;
		}

	return;
    }
}

/* HTTPTransport::processMimeHeaders() Is a public method used to
 * parse the Mime headers of the response message.
 */
void HTTPTransport::processMimeHeader()
{
    unsigned long pos = 0;
    unsigned long temppos = 0;

    // Look for content lenght
    if( (pos = m_strMimeReceived.find( "Content-Type: ")) != std::string::npos)
	{
		m_strMimeContentType = m_strMimeReceived.substr( pos + strlen( "Content-Type: "),
														 m_strMimeReceived.find( "\n", pos));
		pos = m_strMimeContentType.find( ";");
		temppos = m_strMimeContentType.find( "\r\n");

		if( pos < temppos)
		{
			m_strMimeContentType = m_strMimeContentType.substr( 0, pos);
		}
		else
		{
			m_strMimeContentType = m_strMimeContentType.substr( 0, temppos);
		}
    }

    // Look for mime root body's content transfer encoding
    if( (pos = m_strMimeReceived.find( "Content-Transfer-Encoding: ")) != std::string::npos)
	{
		m_strMimeContentTransferEncoding = m_strMimeReceived.substr( pos + strlen( "Content-Transfer-Encoding: "),
																     m_strMimeReceived.find( "\n", pos));
		temppos = m_strMimeContentTransferEncoding.find( "\r\n");
		m_strMimeContentTransferEncoding = m_strMimeContentTransferEncoding.substr( 0, temppos);
    }

    // Look for mime root body's content id
    if( (pos = m_strMimeReceived.find( "Content-ID: ")) != std::string::npos)
	{
		m_strMimeContentID = m_strMimeReceived.substr( pos + strlen( "Content-ID: "),
													   m_strMimeReceived.find( "\n", pos));
		temppos = m_strMimeContentID.find( "\r\n");
		m_strMimeContentID = m_strMimeContentID.substr( 0, temppos);
    }

    // Look for mime root body's content location
    if( (pos = m_strMimeReceived.find( "Content-Location: ")) != std::string::npos)
    {
		m_strMimeContentLocation = atoi( m_strMimeReceived.substr( pos + strlen( "Content-Location: "),
																   m_strMimeReceived.find( "\n", pos)).c_str());
		temppos = m_strMimeContentLocation.find( "\r\n");
		m_strMimeContentLocation = m_strMimeContentLocation.substr( 0, temppos);
    }
}

void HTTPTransport::processMimeBody ()
{
}

void HTTPTransport::getAttachment( char * pStrAttachment, int * pIntSize, int intAttachmentId)
{
	m_pszRxBuffer [0] = '\0';
	*m_pActiveChannel >> m_pszRxBuffer;
    m_strMimeReceived += m_pszRxBuffer;

    do
    {
		if( m_strMimeReceived.find( "\r\n\r\n") == std::string::npos)
		{
			m_pszRxBuffer [0] = '\0';
			*m_pActiveChannel >> m_pszRxBuffer;
		    m_strMimeReceived += m_pszRxBuffer;
		}
    } while( m_strMimeReceived.find( "\r\n\r\n") == std::string::npos);

    //now we have found the end of next mime header
    processMimeHeader();

    m_strMimeReceived = m_strMimeReceived.substr( m_strMimeReceived.find( "\r\n\r\n"));
    processMimeBody();
}

void HTTPTransport::setSocket( unsigned int uiNewSocket)
{
    m_pActiveChannel->setSocket( uiNewSocket);
}

const char * HTTPTransport::getTransportProperty( const char * pcKey, bool response) throw (HTTPTransportException)
{
    std::string strKeyToFind = std::string( pcKey);
	std::vector < std::pair < std::string, std::string > > *hdrs=NULL;
	if (response) hdrs = &m_vResponseHTTPHeaders;
	else hdrs = &m_vHTTPHeaders;

    for( unsigned int i = 0; i < hdrs->size(); i++)
	{
		if( (*hdrs)[i].first == strKeyToFind)
		{
			return (*hdrs)[i].second.c_str();
		}
    }

    return NULL;
}

const char * HTTPTransport::getFirstTransportPropertyKey()
{
    m_viCurrentHeader = m_vHTTPHeaders.begin ();

    if( m_viCurrentHeader == m_vHTTPHeaders.end())
	{
		return NULL;
	}
    else
	{
		return (*m_viCurrentHeader).first.c_str();
	}
}

const char * HTTPTransport::getNextTransportPropertyKey()
{
    //already at the end?
    if( m_viCurrentHeader == m_vHTTPHeaders.end())
	{
		return NULL;
	}

    m_viCurrentHeader++;

    if( m_viCurrentHeader == m_vHTTPHeaders.end())
	{
		return NULL;
	}
    else
	{
		return (*m_viCurrentHeader).first.c_str();
	}
}

const char * HTTPTransport::getCurrentTransportPropertyKey()
{
    if( m_viCurrentHeader == m_vHTTPHeaders.end())
	{
		return NULL;
	}
    else
	{
		return (*m_viCurrentHeader).first.c_str();
	}
}

const char * HTTPTransport::getCurrentTransportPropertyValue()
{
    if( m_viCurrentHeader == m_vHTTPHeaders.end())
	{
		return NULL;
	}
    else
	{
		return (*m_viCurrentHeader).second.c_str();
	}
}

void HTTPTransport::deleteCurrentTransportProperty()
{
    if( m_viCurrentHeader != m_vHTTPHeaders.end())
    {
		m_vHTTPHeaders.erase( m_viCurrentHeader);
    }
}

void HTTPTransport::deleteTransportProperty (char *pcKey, unsigned int uiOccurance)
{
    vector < std::pair < std::string,
	std::string > >::iterator currentHeader = m_vHTTPHeaders.begin();
    unsigned int uiCount = 1;

    while( currentHeader != m_vHTTPHeaders.end() && uiCount <= uiOccurance)
    {
		if( strcmp( pcKey, (*currentHeader).first.c_str()) == 0)
		{
			if( uiCount == uiOccurance)
			{
				m_vHTTPHeaders.erase( currentHeader);
				break;
			}
	    
			uiCount++;
		}
	
		currentHeader++;
    }
}

void HTTPTransport::setMaintainSession( bool bSession)
{
    m_bMaintainSession = bSession;
}

void HTTPTransport::setSessionId( const char * pcSessionId)
{
    m_strSessionKey = std::string (pcSessionId);
}

const char * HTTPTransport::getSessionId()
{
    return m_strSessionKey.c_str();
}

const char * HTTPTransport::getLastChannelError()
{
	if( m_pActiveChannel != NULL)
	{
		return m_pActiveChannel->GetLastErrorMsg().c_str();
	}

	return NULL;
}

void HTTPTransport::readHTTPHeader()
{
// The parser is expecting a SOAP message.  Thus, the HTTP header must have
// been read and processed before control is returned to the parser.  It can
// not be assumed that the HTTP header will be read in one block, thus there
// must be processing that first identifies the beginning of the HTTP header
// block (i.e. looks for 'HTTP') and then additional processing that identifies
// the end of the HTTP header block (i.e. looks for CR LF CR LF).  To stop the
// search becoming 'stuck' because of an incomplete, corrupt or unexpected
// message an iteration count has been added (this could become configurable if
// the user needs to remove this feature if the server is particularily slow,
// etc.).
	bool	bHTTPHeaderFound = false;
	int		iIterationCount = 100;

	m_strReceived = "";

	do
	{
// Read whatever part of the response message that has arrived at the active
// channel socket.
		m_pszRxBuffer[0] = '\0';
		*m_pActiveChannel >> m_pszRxBuffer;

// Add the new message part to the received string.
		m_strReceived += m_pszRxBuffer;

// Do iteration processing.
		if( strlen( m_pszRxBuffer) > 0)
		{
			iIterationCount = 100;
		}
		else
		{
			iIterationCount--;
		}

// Check for beginning and end of HTTP header.
		if( m_strReceived.find( ASCII_S_HTTP) != std::string::npos &&
			m_strReceived.find( ASCII_S_CRLFCRLF) != std::string::npos)
		{
			bHTTPHeaderFound = true;
		}
	} while( !bHTTPHeaderFound && iIterationCount > 0);

// If the HTTP header was not found in the given number of iterations then
// throw an exception.
	if( iIterationCount == 0)
	{
		throw HTTPTransportException( SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
									  "Timed out waiting for HTTP header message.");
	}
}

void HTTPTransport::processHTTPHeader()
{
// At this point the HTTP header has been found.  It now needs to be processed.
	int	iPosContentLength = m_strReceived.find( ASCII_S_CONTENT_LENGTH);

	if( iPosContentLength != std::string::npos)
	{
		int	iEOL = m_strReceived.find( ASCII_S_LF, iPosContentLength);

		iPosContentLength += strlen( ASCII_S_CONTENT_LENGTH);

		m_iContentLength = atoi( m_strReceived.substr( iPosContentLength, iEOL).c_str());

		m_GetBytesState = eSOAPMessageIsNotChunked;
	}

// Check if the message is chunked
	int	iPosChunked = m_strReceived.find( ASCII_S_TRANSFERENCODING_CHUNKED);
	int iHTTPStart = m_strReceived.find( ASCII_S_HTTP);
	int iHTTPEnd = m_strReceived.find( ASCII_S_CRLFCRLF);

	if( iPosChunked != std::string::npos)
	{
//Chunked data looks like ->
//      Chunked-Body   = *chunk
//                       "0" CRLF
//                       footer
//                       CRLF
//
//      chunk          = chunk-size [ chunk-ext ] CRLF
//                         chunk-data CRLF
//
//      hex-no-zero    = <HEX excluding "0">
//
//      chunk-size     = hex-no-zero *HEX
//      chunk-ext      = *( ";" chunk-ext-name [ "=" chunk-ext-value ] )
//      chunk-ext-name = token
//      chunk-ext-val  = token | quoted-string
//      chunk-data     = chunk-size(OCTET)
//
//      footer         = *entity-header

		m_GetBytesState = eSOAPMessageIsChunked;
	}
	else
	{
		if( (m_eProtocolType == APTHTTP1_0) || (m_eProtocolType == APTHTTP1_1) )
		{
			m_GetBytesState = eSOAPMessageIsNotChunked;
			m_iBytesLeft = m_strReceived.substr( iHTTPEnd + 2).length();

// Check if all the message has already been recieved.  If not, then subtract
// that bit that has been from the total length.  If so, then make the content
// length equal to zero.
			if( m_iContentLength >= m_iBytesLeft)
			{
				m_iContentLength -= m_iBytesLeft;
			}
			else
			{
				m_iContentLength = 0;
			}
		}
		else
		{
			m_GetBytesState = eWaitingForHTTPHeader;

			throw HTTPTransportException( SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
										  "HTTP header message must be chunked or have a content length.");
		}
	}

// Extract HTTP header and process it
	m_strResponseHTTPHeaders = m_strReceived.substr( iHTTPStart, iHTTPEnd + 2 - iHTTPStart);

	processResponseHTTPHeaders();

// If the HTTP message is a 'continue' message then remove the HTTP header and
// then repeat HTTP header processing.
	if( m_iResponseHTTPStatusCode == 100)
	{
		m_strReceived = m_strReceived.substr( iHTTPEnd + 2);
	}
}

void HTTPTransport::checkHTTPStatusCode()
{
// Now have a valid HTTP header that is not 100.  Check that the status
// returned by the HTTP response status code indicates a valid message.  If some
// type of fault message (i.e. 404, 500, etc.), then throw an exception.
	if ( (m_iResponseHTTPStatusCode < 200 ||
		  m_iResponseHTTPStatusCode >= 300))
	{
		m_GetBytesState = eWaitingForHTTPHeader;

		m_strResponseHTTPStatusMessage = std::string( "\n Server sent HTTP error: '") +
										 m_strResponseHTTPStatusMessage +
										 std::string("'\n");

		throw HTTPTransportException( SERVER_TRANSPORT_HTTP_EXCEPTION,
								  const_cast <char *> (m_strResponseHTTPStatusMessage.c_str()));
	}
}

bool HTTPTransport::getNextDataPacket( const char * pcszExceptionMessage)
{
	int		iIterationCount = 100;
	bool	bDataRead = false;

	do
	{
// Read whatever part of the response message that has arrived at the active
// channel socket.
		m_pszRxBuffer[0] = '\0';
		*m_pActiveChannel >> m_pszRxBuffer;

// Do iteration processing.
		if( strlen( m_pszRxBuffer) == 0)
		{
			iIterationCount--;
		}
		else
		{
			bDataRead = true;
		}

	} while( !bDataRead && iIterationCount > 0);

	if( bDataRead)
	{
		m_strReceived += m_pszRxBuffer;

		m_iBytesLeft = m_strReceived.length();
	}
	else
	{
		if( m_strReceived.length() == 0)
		{
			m_GetBytesState = eWaitingForHTTPHeader;

			if( pcszExceptionMessage != NULL && strlen( pcszExceptionMessage) > 0)
			{
				int	iStringLength = strlen( pcszExceptionMessage) + 1;
				const char * pszLastError = new char[iStringLength];

				memcpy( (void *) pszLastError, pcszExceptionMessage, iStringLength);

				throw HTTPTransportException( SERVER_TRANSPORT_HTTP_EXCEPTION,
											  (char *) pszLastError);
			}
		}
	}

	return bDataRead;
}

int HTTPTransport::getChunkSize()
{
	int	iChunkSize;

	while( m_strReceived.find( ASCII_S_CRLF) == std::string::npos)
	{
		getNextDataPacket( "Could not find delimiter for end of chunk size.");
	}

	int iEndOfChunkData = m_strReceived.find( ASCII_S_CRLF) + strlen( ASCII_S_CRLF);
	int iEndOfChunkSize = m_strReceived.find( ASCII_S_CRLF);

// Now get the size of the chunk from the data.  Look to see if there are any
// extensions - these are put in brackets so look for those.
	if( m_strReceived.substr( 0, iEndOfChunkSize).find( ASCII_S_LEFTPAREN) != string::npos)
	{
		iEndOfChunkSize = m_strReceived.find( ASCII_S_LEFTPAREN);
	}

// Convert the hex string into the length of the chunk.
	iChunkSize = axtoi( (char *) m_strReceived.substr( 0, iEndOfChunkSize).c_str());

	m_strReceived = m_strReceived.substr( iEndOfChunkData);

	m_iBytesLeft = m_strReceived.length();

	return iChunkSize;
}

bool HTTPTransport::copyDataToParserBuffer( char * pcBuffer, int * piSize, int iBytesToCopy)
{
	bool	bTransportInProgress = false;

	if( iBytesToCopy > 0)
	{
		int iToCopy = (*piSize < iBytesToCopy) ? *piSize : iBytesToCopy;

		strncpy( pcBuffer, m_strReceived.c_str(), iToCopy);

		m_iBytesLeft -= iToCopy;
		*piSize = iToCopy;

		if( m_iBytesLeft > 0)
		{
			m_strReceived = m_strReceived.substr( iToCopy);
		}
		else
		{
			m_strReceived = "";
		}

		bTransportInProgress = true;
	}

	return bTransportInProgress;
}

int HTTPTransport::peekChunkLength( std::string& strNextChunk)
{
	if( strNextChunk.length() == 0)
	{
		return -1;
	}

	int iEndOfChunkSize = strNextChunk.find( ASCII_S_CRLF);

	if( iEndOfChunkSize == std::string::npos)
	{
		return -1;
	}

// Now get the size of the chunk from the data.  Look to see if there are any
// extensions - these are put in brackets so look for those.
	if( strNextChunk.substr( iEndOfChunkSize).find( ASCII_S_LEFTPAREN) != std::string::npos)
	{
		iEndOfChunkSize = strNextChunk.find( ASCII_S_LEFTPAREN);
	}

// Convert the hex string into the length of the chunk.
	return axtoi( (char *) strNextChunk.substr( 0, iEndOfChunkSize).c_str());
}
