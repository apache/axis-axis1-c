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
*/

/*
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */


#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4101)
#endif

#include "Axis2Transport.h"

#include <stdio.h>
#include <iostream>

/*
 * Axis2Transport constuctor
 */
Axis2Transport::Axis2Transport ():m_bURIChanged (false),
m_strHTTPProtocol ("HTTP/1.1"),
m_strHTTPMethod ("POST"),
m_bChunked (false),
m_bReadPastHTTPHeaders (false),
m_strProxyHost (""), m_uiProxyPort (0), m_bUseProxy (false)
{
    m_pcEndpointUri = NULL;
    m_pReleaseBufferCallback = 0;
    m_eProtocolType = APTHTTP1_1;
    m_strBytesToSend = "";
    m_strHeaderBytesToSend = "";
    m_iBytesLeft = 0;
    m_iContentLength = 0;
    m_pcReceived = 0;
    m_pChannel = new Channel ();
    m_bChannelSecure = false;
}

/*
 * Axis2Transport destuctor
 */
Axis2Transport::~Axis2Transport ()
{
    if (m_pcEndpointUri)
    {
	free (m_pcEndpointUri);
    }

    delete m_pChannel;
}

/*
 * Axis2Transport::setEndpointUri( EndpointURI) sets the URI for the message.
 * Everytime the endpoint changes then currently connected channel is closed
 * and a new channel connection is opened.
 *
 * @param	EndpointURI - char * to a null terminated string that holds the
 *			new URI. 
 */
void
Axis2Transport::setEndpointUri (const char *pcEndpointUri)
throw (AxisTransportException)
{
    bool bUpdateURL = false;

    // Get the current channel URI
    if (m_pChannel->getURL ())
    {
	// Does the new URI equal the existing channel URI?
	if (strcmp (m_pChannel->getURL (), pcEndpointUri) != 0)
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
    // GSKit is available, if the new URI is a secure connection, a secure
    // channel will be opened.  If GSKit is not available and the URL requires
    // a secure connection then an exeption will be thrown.
    if (bUpdateURL)
    {
	m_pChannel->setURL (pcEndpointUri);

	m_bURIChanged = true;

	// Check if the new URI requires SSL (denoted by the https prefix).
	if ((m_pChannel->getURLObject ()).getProtocol () == URL::https)
	{
	    m_bChannelSecure = false;

	    // URI requires a secure channel.  Delete the existing channel
	    // (as it may not be secure) and create a new secure channel.
	    delete m_pChannel;

	    m_pChannel = (Channel *) new SecureChannel ();

	    m_pChannel->setURL (pcEndpointUri);

	    m_bChannelSecure = true;

	    if (!m_bChannelSecure)
	    {
		throw
		    AxisTransportException
		    (CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER);
	    }
	}
	else
	{
	    // URI does not require a secure channel.  Delete the existing
	    // channel (as it may be secure) and create a new unsecure
	    // channel.
	    delete m_pChannel;

	    m_pChannel = new Channel ();
	    m_pChannel->setURL (pcEndpointUri);
	    m_bChannelSecure = false;
	}
    }
}

/*
 * Axis2Transport::openConnection().
 */

int
Axis2Transport::openConnection ()
{
    //Samisa: I wonder whether this should be a SOAPTransport API call.
    //It should not be the job of the upper layers to tell the trasport
    //to open and close connections. Rather the transport should determine
    //when to do that, when sendBytes is called.

    return AXIS_SUCCESS;

}

/*
 * Axis2Transport::closeConnection().
 */
void
Axis2Transport::closeConnection ()
{
    // get ready for a new message.
    m_bReadPastHTTPHeaders = false;

    //clear the message buffer in preperation of the next read.
    m_strReceived = "";

    m_iContentLength = 0;
}

/*
 * Axis2Transport::flushOutput() Is called when the message construction is
 * complete.  The message is ready to be 'flushed out' onto the network.  
 * Check if the URI has changed.  If it has, then need to open a new Channel
 * instance before transmitting the message.
 *
 * @return AXIS_TRANSPORT_STATUS If the method completes successfully, then
 * this will be set to TRANSPORT_FINISHED.  Otherwise, an exception will have
 * been thrown.
 */
AXIS_TRANSPORT_STATUS
Axis2Transport::flushOutput ()
throw (AxisTransportException)
{
    if (m_bURIChanged)
    {
	if (!m_pChannel->open ())
	{
	    int iStringLength = m_pChannel->GetLastError ().length () + 1;
	    const char *pszLastError = new char[iStringLength];

	    memcpy ((void *) pszLastError,
		    m_pChannel->GetLastError ().c_str (), iStringLength);;

	    throw
		AxisTransportException
		(CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED,
		 (char *) pszLastError);
	}
    }

    // In preperation for sending the message, calculate the size of the message
    // by using the string length method.
    // NB: This calculation may not necessarily be correct when dealing with SSL
    //     messages as the length of the encoded message is not necessarily the
    //         same as the length of the uncoded message.
    char buff[8];

    sprintf (buff, "%d", m_strBytesToSend.length ());

    this->setTransportProperty ("Content-Length", buff);

    // The header is now complete.  The message header and message can now be
    // transmitted.
    try
    {
	*m_pChannel << this->getHTTPHeaders ();
	*m_pChannel << this->m_strBytesToSend.c_str ();
    }
    catch (AxisTransportException & e)
    {
	throw;
    }
    catch (AxisException & e)
    {
	throw;
    }
    catch (...)
    {
	throw;
    }

    // Empty the bytes to send string.
    m_strBytesToSend = "";
    m_strHeaderBytesToSend = "";

    return TRANSPORT_FINISHED;
}

/* Axis2Transport::getHTTPHeaders() Called to retreive the current HTTP header
 * information block that will preceed the SOAP message.
 *
 * @return const char* Pointer to a NULL terminated character string containing
 * the HTTP header block of information.
 */
const char *
Axis2Transport::getHTTPHeaders ()
{
    URL & url = m_pChannel->getURLObject ();

    m_strHeaderBytesToSend = m_strHTTPMethod + " ";
    m_strHeaderBytesToSend += std::string (url.getResource ()) + " ";
    m_strHeaderBytesToSend += m_strHTTPProtocol + "\r\n";
    m_strHeaderBytesToSend += std::string ("Host: ") + url.getHostName ();

    unsigned short uiPort = url.getPort ();
    char buff[8];

    sprintf (buff, "%u", uiPort);

    m_strHeaderBytesToSend += ":";
    m_strHeaderBytesToSend += buff;
    m_strHeaderBytesToSend += "\r\n";
    m_strHeaderBytesToSend += "Content-Type: text/xml; charset=UTF-8\r\n";

    // Set other HTTP headers
    for (unsigned int i = 0; i < m_vHTTPHeaders.size (); i++)
    {
	m_strHeaderBytesToSend += m_vHTTPHeaders[i].first;
	m_strHeaderBytesToSend += ": ";
	m_strHeaderBytesToSend += m_vHTTPHeaders[i].second;
	m_strHeaderBytesToSend += "\r\n";
    }

    m_strHeaderBytesToSend += "\r\n";

    return m_strHeaderBytesToSend.c_str ();
}

/* Axis2Transport::getHTTPMethod() Is a public method that gets the HTTP method
 * (i.e. GET or POST) that will be part of the HTTP header block.
 *
 * @return const char* Pointer to a NULL terminated character string containing
 * the HTTP method.
 */
const char *
Axis2Transport::getHTTPMethod ()
{
    return m_strHTTPMethod.c_str ();
}

/* Axis2Transport::setHTTPMethod( Method) Is a public method that sets the HTTP
 * method (i.e. POST or GET) that will be part of the HTTP header block.
 *
 * @param const char* Pointer to a NULL terminated character string containing
 * the new HTTP method.
 */
void
Axis2Transport::setHTTPMethod (const char *cpMethod)
{
    m_strHTTPMethod = std::string (cpMethod);
}

/* Axis2Transport::sendBytes( SendBuffer, BufferId) Is a public method that
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
AXIS_TRANSPORT_STATUS
Axis2Transport::sendBytes (const char *pcSendBuffer, const void *pBufferId)
{
    m_strBytesToSend += std::string (pcSendBuffer);

    return TRANSPORT_IN_PROGRESS;
}

/* Axis2Transport::getBytes( ReceiveBuffer, Size) Is a public method that will
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
AXIS_TRANSPORT_STATUS
Axis2Transport::getBytes (char *pcBuffer, int *pSize)
throw (AxisException, AxisTransportException)
{
    if (0 <= m_iBytesLeft)
    {
	try
	{
	    *m_pChannel >> m_strReceived;

	    if (!m_bReadPastHTTPHeaders)
	    {
		do
		{
		    if (m_strReceived.find ("\r\n\r\n") == std::string::npos)
		    {
			std::string strTempReceived = "";
			*m_pChannel >> strTempReceived;	// Assume non blocking here
			m_strReceived += strTempReceived;
		    }
		}
		while (m_strReceived.find ("\r\n\r\n") == std::string::npos);

		//now we have found the end of headers
		m_bReadPastHTTPHeaders = true;

		unsigned int pos = 0;

		// Look for content lenght
		if ((pos =
		     m_strReceived.find ("Content-Length: ")) !=
		    std::string::npos)
		{
		    m_iContentLength =
			atoi (m_strReceived.
			      substr (pos + strlen ("Content-Length: "),
				      m_strReceived.find ("\n",
							  pos)).c_str ());
		}

		// Check if the message is chunked
		if ((pos =
		     m_strReceived.find ("Transfer-Encoding: chunked")) !=
		    std::string::npos)
		{
		    m_bChunked = true;
		}
		else
		{
		    m_bChunked = false;
		}

		// Extract HTTP headers and process them
		m_strResponseHTTPHeaders = m_strReceived.substr (0,
								 m_strReceived.
								 find
								 ("\r\n\r\n")
								 + 2);
		processResponseHTTPHeaders ();

		if (m_iResponseHTTPStatusCode != 200)
		{
		    throw
			AxisTransportException
			(SERVER_TRANSPORT_HTTP_EXCEPTION,
			 const_cast <
			 char *>(m_strResponseHTTPStatusMessage.c_str ()));
		}

		// Done with HTTP headers, get payload
		m_strReceived =
		    m_strReceived.substr (m_strReceived.find ("\r\n\r\n") +
					  4);
	    }

	    // Read past headers. Deal with payload

	    // make sure we have a message with some content
	    if (m_strReceived.length () == 0)
	    {
		*m_pChannel >> m_strReceived;
	    }

	    if (m_bChunked && m_iContentLength < 1)	// Read first chunk
	    {
		/*
		 *Chunked data looks like ->
		 *      Chunked-Body   = *chunk
		 *                       "0" CRLF
		 *                       footer
		 *                       CRLF
		 *
		 *      chunk          = chunk-size [ chunk-ext ] CRLF
		 *                         chunk-data CRLF
		 *
		 *      hex-no-zero    = <HEX excluding "0">
		 *
		 *      chunk-size     = hex-no-zero *HEX
		 *      chunk-ext      = *( ";" chunk-ext-name [ "=" chunk-ext-value ] )
		 *      chunk-ext-name = token
		 *      chunk-ext-val  = token | quoted-string
		 *      chunk-data     = chunk-size(OCTET)
		 *
		 *      footer         = *entity-header
		 */
		// firstly read in the chunk size line.
		//There might be chunk extensions in there too but we may not need them
		unsigned int endOfChunkData = m_strReceived.find ("\r\n");

		// make sure we have read at least some part of the message
		if (endOfChunkData == std::string::npos)
		{
		    do
		    {
			*m_pChannel >> m_strReceived;
			endOfChunkData = m_strReceived.find ("\r\n");
		    }
		    while (endOfChunkData == std::string::npos);
		}

		int endOfChunkSize = endOfChunkData;

		// now get the size of the chunk from the data
		// look to see if there are any extensions - these are put in brackets so look for those
		if (m_strReceived.substr (0, endOfChunkData).find ("(") !=
		    string::npos)
		{
		    endOfChunkSize = m_strReceived.find ("(");
		}

		// convert the hex String into the length of the chunk
		m_iContentLength = axtoi ((char *) m_strReceived.substr (0,
									 endOfChunkSize).
					  c_str ());
		// if the chunk size is zero then we have reached the footer
		// If we have reached the footer then we can throw it away because we don't need it
		if (m_iContentLength > 0)
		{
		    // now get the chunk without the CRLF
		    // check if we have read past chunk length
		    if (m_strReceived.length () >=
			(endOfChunkData + 2 + m_iContentLength))
		    {
			m_strReceived =
			    m_strReceived.substr (endOfChunkData + 2,
						  m_iContentLength);
		    }
		    else	// we have read lesser than chunk length
		    {
			m_strReceived =
			    m_strReceived.substr (endOfChunkData + 2);
		    }
		}
		else
		{
		    m_strReceived = "";
		}
	    }
	    else if (m_bChunked)	// read continued portions of a chunk
	    {
		// Samisa - NOTE: It looks as if there is some logic duplication 
		// in this block, where we read continued chunks and the block 
		// above, where we read the first chunk. However, there are slight
		// logical differences here, and that is necessary to enable the 
		// pull model used by the parser - this logic makes pulling more
		// efficient (30th Sept 2004)
		if (m_strReceived.length () >= m_iContentLength)	// We have reached end of current chunk
		{
		    // Get remainder of current chunk
		    std::string strTemp =
			m_strReceived.substr (0, m_iContentLength);

		    // Start looking for the next chunk
		    unsigned int endOfChunkData = m_strReceived.find ("\r\n");	// Skip end of previous chunk
		    m_strReceived = m_strReceived.substr (endOfChunkData + 2);

		    endOfChunkData = m_strReceived.find ("\r\n");	// Locate start of next chunk

		    // Make sure we have the starting line of next chunk
		    while (endOfChunkData == std::string::npos)
		    {
			std::string strTempRecv = "";
			*m_pChannel >> strTempRecv;
			m_strReceived += strTempRecv;
			endOfChunkData = m_strReceived.find ("\r\n");
		    }

		    int endOfChunkSize = endOfChunkData;

		    // look to see if there are any extensions - these are put in brackets so look for those
		    if (m_strReceived.substr (0, endOfChunkData).find ("(") !=
			string::npos)
		    {
			endOfChunkSize = m_strReceived.find ("(");
		    }

		    // convert the hex String into the length of the chunk
		    int iTempContentLength =
			axtoi ((char *) m_strReceived.substr (0,
							      endOfChunkSize).
			       c_str ());

		    // if the chunk size is zero then we have reached the footer
		    // If we have reached the footer then we can throw it away because we don't need it
		    if (iTempContentLength > 0)
		    {
			// Update the content lenght to be remainde of previous chunk and lenght of new chunk
			m_iContentLength += iTempContentLength;

			// now get the chunk without the CRLF
			// check if we have read past chunk length
			if (m_strReceived.length () >=
			    (endOfChunkData + 2 + iTempContentLength))
			{
			    m_strReceived =
				m_strReceived.substr (endOfChunkData + 2,
						      iTempContentLength);
			}
			else
			{
			    m_strReceived =
				m_strReceived.substr (endOfChunkData + 2);
			}
		    }
		    else
		    {
			m_strReceived = "";
		    }

		    // Append the data of new chunk to data from previous chunk
		    m_strReceived = strTemp + m_strReceived;

		}		// End of if (m_strReceived.length() >= m_iContentLength) 
		// If we have not reached end of current chunk, nothing to be done
	    }
	    else		// Not chunked
	    {
		//nothing to do here
	    }

	    m_pcReceived = m_strReceived.c_str ();

	    if (m_pcReceived)
	    {
		m_iBytesLeft = strlen (m_pcReceived);
	    }
	    else
	    {
		throw AxisTransportException (SERVER_TRANSPORT_BUFFER_EMPTY,
					      "Reveved null");
	    }

	    m_iContentLength -= m_iBytesLeft;
	}
	catch (AxisTransportException & e)
	{
	    throw;
	}
	catch (AxisException & e)
	{
	    throw;
	}
	catch (...)
	{
	    throw;
	}
    }
    if (m_pcReceived)
    {
	int iToCopy = (*pSize < m_iBytesLeft) ? *pSize : m_iBytesLeft;

	strncpy (pcBuffer, m_pcReceived, iToCopy);

	m_iBytesLeft -= iToCopy;
	m_pcReceived += iToCopy;
	*pSize = iToCopy;

	return TRANSPORT_IN_PROGRESS;
    }
    else
    {
	m_bReadPastHTTPHeaders = false;	// get ready for a new message
	m_strReceived = "";	//clear the message buffer in preperation of the next read

	return TRANSPORT_FINISHED;
    }
}

/* Axis2Transport::setTransportProperty( Type, Value) Is an overloaded public
 * method used to set a HTTP transport or GSKit property.
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE Type is an enumerated type containing
 * the type of information to be stored in either the HTTP Header or GSKit
 * settings.
 * @param const char* Value is a NULL terminated character string containing
 * the value associated with the type.
 */
void
Axis2Transport::setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE type,
				      const char *value)
throw (AxisTransportException)
{
    const char *key = NULL;

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

    case SECURE_PROPERTIES:
	{
	    if (m_bChannelSecure)
	    {
		((SecureChannel *) m_pChannel)->setSecureProperties (value);
	    }
	    break;
	}

    default:
	{
	    break;
	}
    }

    if (key)
    {
	setTransportProperty (key, value);
    }
}

/* Axis2Transport::setTransportProperty( Key, Value) Is an overloaded public
 * method used to set a HTTP transport or GSKit property.
 *
 * @param const char* Key is a NULL terminated character string containing
 * the type of information to be stored in either the HTTP Header or GSKit
 * settings.
 * @param const char* Value is a NULL terminated character string containing
 * the value associated with the type.
 */
void
Axis2Transport::setTransportProperty (const char *pcKey, const char *pcValue)
throw (AxisTransportException)
{
    bool b_KeyFound = false;

    if (strcmp (pcKey, "SOAPAction") == 0
	|| strcmp (pcKey, "Content-Length") == 0)
    {
	std::string strKeyToFind = std::string (pcKey);

	for (unsigned int i = 0; i < m_vHTTPHeaders.size (); i++)
	{
	    if (m_vHTTPHeaders[i].first == strKeyToFind)
	    {
		m_vHTTPHeaders[i].second = (string) pcValue;

		b_KeyFound = true;

		break;
	    }
	}
    }

    if (!b_KeyFound)
    {
	m_vHTTPHeaders.
	    push_back (std::make_pair ((string) pcKey, (string) pcValue));
    }
}

/* Axis2Transport::getTransportProperty( Type) Is a public method that will
 * return the HTTP Header/GSKit value associated with type.
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE Type is an enumerated type containing
 * the type of information to be retrieved in either the HTTP Header or GSKit
 * settings.
 *
 * @return const char* Value is a NULL terminated character string containing
 * the value associated with the type.
 */
const char *
Axis2Transport::getTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType)
throw (AxisTransportException)
{
    const char *pszPropValue = NULL;

    switch (eType)
    {
    case SOAPACTION_HEADER:
	{
	    int iIndex = FindTransportPropertyIndex ("SOAPAction");

	    if (iIndex > -1)
	    {
		pszPropValue = m_vHTTPHeaders[iIndex].second.c_str ();
	    }

	    break;
	}

    case SERVICE_URI:
	break;

    case OPERATION_NAME:
	break;

    case SOAP_MESSAGE_LENGTH:
	{
	    int iIndex = FindTransportPropertyIndex ("Content-Length");

	    if (iIndex > -1)
	    {
		pszPropValue = m_vHTTPHeaders[iIndex].second.c_str ();
	    }
	    break;
	}

    case SECURE_PROPERTIES:
	{
	    if (m_bChannelSecure)
	    {
		pszPropValue =
		    ((SecureChannel *) m_pChannel)->getSecureProperties ();
	    }
	    break;
	}
    }

    return pszPropValue;
}

/* Axis2Transport::FindTransportPropertyIndex( Key) Is a private method that will
 * return the HTTP Header index associated with Key.
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE Key is an enumerated type containing
 * the type of information to be retrieved in either the HTTP Header settings.
 *
 * @return int Index is an index to the key within the HTTP Header list.  If
 * the return value is -1, then the key was not found.
 */
int
Axis2Transport::FindTransportPropertyIndex (string sKey)
{
    bool bKeyFound = false;
    int iIndex = 0;

    do
    {
	if (!m_vHTTPHeaders[iIndex].first.compare (sKey))
	{
	    bKeyFound = true;
	}
	else
	{
	    iIndex++;
	}
    }
    while ((unsigned int) iIndex < m_vHTTPHeaders.size () && !bKeyFound);

    if (!bKeyFound)
    {
	iIndex = -1;
    }

    return iIndex;
}

/* Axis2Transport::getServiceName() Is a public method to return the HTTP
 * Header service name.
 *
 * @return const char* Value is a NULL terminated character string containing
 * the value associated with the service name.
 */
const char *
Axis2Transport::getServiceName ()
{
    //Assume SOAPAction header to contain service name
    int iIndex = FindTransportPropertyIndex ("SOAPAction");

    if (iIndex > -1)
    {
	return m_vHTTPHeaders[iIndex].second.c_str ();
    }

    return NULL;
}

/* Axis2Transport::getProtocol() Is a public method to return the HTTP protocol
 * type.
 *
 * @return AXIS_PROTOCOL_TYPE Type is an enumerated type for valid HTTP
 * protocols (currently this method will always return APTHTTP1_1).
 */
AXIS_PROTOCOL_TYPE
Axis2Transport::getProtocol ()
{
    return m_eProtocolType;
}

int Axis2Transport::setProtocol(AXIS_PROTOCOL_TYPE eProtocol)
{
    if( eProtocol == APTHTTP1_1 || eProtocol == APTHTTP1_0 )
    {
       m_eProtocolType = eProtocol;
       m_strHTTPProtocol = (m_eProtocolType == APTHTTP1_1 )? "HTTP/1.1": "HTTP/1.0";
       return AXIS_SUCCESS; 
    }
    else 
        return AXIS_FAIL;
}

/**
 * Axis2Transport::getSubProtocol() is a public method that is supposed to
 * return the sub protocol (currently this method always return 0).
 * This method is supposed to return whether it is http GET or POST
 */
int
Axis2Transport::getSubProtocol ()
{
    //TODO
    // for SimpleAxisServer assume POST
    return AXIS_HTTP_POST;
    //return 0;
}

/* Axis2Transport::setProxy( Host, Port) Is a public method for setting or
 * updating the proxy for the connection.
 *
 * @param const char* Host is a NULL terminated character string containing the new
 * proxy host.
 * @param unsigned int Port is the new proxy port number.
 */
void
Axis2Transport::setProxy (const char *pcProxyHost, unsigned int uiProxyPort)
{
    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;
}

/* Axis2Transport::setTimeout( Timeout) Is a public method for setting the
 * current maximum timeout period between that can elapse between receiving
 * message parts.
 *
 * @param const long Timeout is a long value in seconds.
 */
void
Axis2Transport::setTimeout (const long lSeconds)
{
    m_pChannel->setTimeout (lSeconds);
}

/* Axis2Transport::getHTTPProtocol() Is a public method for retrieving the
 * current HTTP protocol settings.
 *
 * @return const char* HTTPProtocol is a NULL terminated character string
 * containing the HTTP protocol.
 */
const char *
Axis2Transport::getHTTPProtocol ()
{
    return m_strHTTPProtocol.c_str ();
}

/* Axis2Transport::setHTTPProtocol( Version) Is a public method for setting the
 * current HTTP protocol.
 *
 * @param int Version is an integer value used to select which HTTP protocol
 * should be used. 0=HTTP v1.0 and 1(or any other value than 0)=HTTP v1.1
 */
void
Axis2Transport::setHTTPProtocol (int iVersion)
{
    switch (iVersion)
    {
    case 0:
	m_strHTTPProtocol = "HTTP/1.0";
	break;

    case 1:
    default:
	m_strHTTPProtocol = "HTTP/1.1";
	break;
    }
}

extern "C"
{
/* CreateInstance() Is a C interface.
 */
    STORAGE_CLASS_INFO int CreateInstance (SOAPTransport ** inst)
    {
	*inst = new Axis2Transport ();
	if (*inst)
	{
	    return AXIS_SUCCESS;
	}
	return AXIS_FAIL;
    }

/* DestroyInstance() Is a C interface.
 */
    STORAGE_CLASS_INFO int DestroyInstance (SOAPTransport * inst)
    {
	if (inst)
	{
	    delete inst;

	    return AXIS_SUCCESS;
	}
	return AXIS_FAIL;
    }

/*  initializeLibrary() Is a C interface.
 */
    STORAGE_CLASS_INFO void initializeLibrary (void)
    {
	// Do init actions
    }

/*  uninitializeLibrary() Is a C interface. 
 */
    STORAGE_CLASS_INFO void uninitializeLibrary (void)
    {
	// Do uninit actions
    }
}

/* axtoi( Hex) Is a private method to convert an ascii hex string to an integer.
 */
int
axtoi (char *hexStg)
{
    int n = 0;			// position in string
    int m = 0;			// position in digit[] to shift
    int count;			// loop index
    int intValue = 0;		// integer value of hex string
    int digit[32];		// hold values to convert
    while (n < 32)
    {
	if (hexStg[n] == '\0')
	    break;
	if (hexStg[n] > 0x29 && hexStg[n] < 0x40)	//if 0 to 9
	    digit[n] = hexStg[n] & 0x0f;	//convert to int
	else if (hexStg[n] >= 'a' && hexStg[n] <= 'f')	//if a to f
	    digit[n] = (hexStg[n] & 0x0f) + 9;	//convert to int
	else if (hexStg[n] >= 'A' && hexStg[n] <= 'F')	//if A to F
	    digit[n] = (hexStg[n] & 0x0f) + 9;	//convert to int
	else
	    break;
	n++;
    }
    count = n;
    m = n - 1;
    n = 0;
    while (n < count)
    {
	// digit[n] is value of hex digit at position n
	// (m << 2) is the number of positions to shift
	// OR the bits into return value
	intValue = intValue | (digit[n] << (m << 2));
	m--;			// adjust the position to set
	n++;			// next digit to process
    }
    return (intValue);
}

/* Axis2Transport::processResponseHTTPHeaders() Is a public method used to
 * parse the HTTP header of the response message.
 */
void
Axis2Transport::processResponseHTTPHeaders ()
{
    unsigned int iPosition = std::string::npos;
    unsigned int iStartPosition = iPosition;

    if ((iPosition =
	 m_strResponseHTTPHeaders.find ("HTTP")) != std::string::npos)
    {
	m_strResponseHTTPProtocol =
	    m_strResponseHTTPHeaders.substr (iPosition, strlen ("HTTP/1.x"));
	iPosition += strlen ("HTTP/1.x");

	while (m_strResponseHTTPHeaders.substr ()[iPosition] == ' ')
	{
	    iPosition++;
	}

	iStartPosition = iPosition;

	while (m_strResponseHTTPHeaders.substr ()[iPosition] != ' ')
	{
	    iPosition++;
	}

	std::string strResponseHTTPStatusCode =
	    m_strResponseHTTPHeaders.substr (iStartPosition,
					     iPosition - iStartPosition);
	m_iResponseHTTPStatusCode = atoi (strResponseHTTPStatusCode.c_str ());

	iStartPosition = ++iPosition;
	iPosition = m_strResponseHTTPHeaders.find ("\n");
	m_strResponseHTTPStatusMessage =
	    m_strResponseHTTPHeaders.substr (iStartPosition,
					     iPosition - iStartPosition - 1);

	// reached the end of the first line
	iStartPosition = m_strResponseHTTPHeaders.find ("\n");

	iStartPosition++;

	// read header fields and add to vector
	do
	{
	    m_strResponseHTTPHeaders =
		m_strResponseHTTPHeaders.substr (iStartPosition);
	    iPosition = m_strResponseHTTPHeaders.find ("\n");

	    if (iPosition == std::string::npos)
	    {
		break;
	    }

	    std::string strHeaderLine =
		m_strResponseHTTPHeaders.substr (0, iPosition);
	    unsigned int iSeperator = strHeaderLine.find (":");

	    if (iSeperator == std::string::npos)
	    {
		break;
	    }

	    iStartPosition = iPosition + 1;

	    m_vResponseHTTPHeaders.
		push_back (std::
			   make_pair (strHeaderLine.substr (0, iSeperator),
				      strHeaderLine.substr (iSeperator + 1,
							    strHeaderLine.
							    length () -
							    iSeperator - 1 -
							    1)));
	}
	while (iPosition != std::string::npos);
    }
    else
    {
	throw AxisTransportException (SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
				      "Protocol is not HTTP.");
    }
}

// This is used by SimpleAxisServer
void
Axis2Transport::setSocket (unsigned int uiNewSocket)
{
    m_pChannel->setSocket (uiNewSocket);
}

const char *
Axis2Transport::getTransportProperty (const char *pcKey)
throw (AxisTransportException)
{

    std::string strKeyToFind = std::string (pcKey);

    for (unsigned int i = 0; i < m_vResponseHTTPHeaders.size (); i++)
    {
        if (m_vResponseHTTPHeaders[i].first == strKeyToFind)
        {
            return ((string) m_vResponseHTTPHeaders[i].second).c_str ();
        }
    }

    return NULL;
}

