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
Axis2Transport::Axis2Transport ():m_bReopenConnection (false),
        m_strHTTPProtocol ("HTTP/1.1"),
        m_strHTTPMethod ("POST"),
        m_bChunked (false),
        m_bReadPastHTTPHeaders (false),
        m_strProxyHost (""), m_uiProxyPort (0), m_bUseProxy (false), m_bMaintainSession(false)
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
    m_pFactory = new ChannelFactory();
    m_bChannelSecure = false;
	m_bMimeTrue = false;
    m_viCurrentHeader = m_vHTTPHeaders.begin();
}

/*
 * Axis2Transport destuctor
 */
Axis2Transport::~Axis2Transport ()
{
    if (m_pcEndpointUri)
    {
        delete [] m_pcEndpointUri;
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

        m_bReopenConnection = true;

        // Check if the new URI requires SSL (denoted by the https prefix).
        if ((m_pChannel->getURLObject ()).getProtocol () == URL::https)
        {
            m_bChannelSecure = false;

            // URI requires a secure channel.  Delete the existing channel
            // (as it may not be secure) and create a new secure channel.
            delete m_pChannel;

            //m_pChannel = (Channel *) new SecureChannel ();
            m_pChannel = m_pFactory->getSecureChannelObject();

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
            // channel if it is secure and create a new unsecure
            // channel.
            if (m_bChannelSecure)
            {
                delete m_pChannel;

                m_pChannel = new Channel ();
                m_pChannel->setURL (pcEndpointUri);
                m_bChannelSecure = false;
            }
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
    //It should not be the job of the upper layers to tell the transport
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
    if (m_bReopenConnection)
    {
        m_bReopenConnection = false;
        if (!m_pChannel->open ())
        {
            int iStringLength = m_pChannel->GetLastError ().length () + 1;
            const char *pszLastError = new char[iStringLength];

            memcpy ((void *) pszLastError,
                    m_pChannel->GetLastError ().c_str (), iStringLength);
            ;

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
    
    // Set session cookie
    if (m_bMaintainSession && (m_strSessionKey.size() > 0) )
    {
        m_strHeaderBytesToSend += "Cookie";
        m_strHeaderBytesToSend += ": ";
        m_strHeaderBytesToSend += m_strSessionKey;
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

                if (m_strReceived.find ("HTTP") == std::string::npos)
                { 
                    // Most probably what we read was left overs from earlier reads
                    // Skip this \r\n\r\n
                    m_strReceived = m_strReceived.substr (m_strReceived.find ("\r\n\r\n") + 4);
                    do
                    {
                        if (m_strReceived.find ("\r\n\r\n") == std::string::npos)
                        {
                            std::string strTempReceived = "";
                            *m_pChannel >> strTempReceived; // Assume non blocking here
                            m_strReceived += strTempReceived;
                        }
                    }
                    while (m_strReceived.find ("\r\n\r\n") == std::string::npos);
                    // now this must contain HTTP. Else there is a conent error.
                }

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

                // check if there is HTTP header. If not, there must be an error and 
                // will be detected by processResponseHTTPHeaders()
                // However, must make sure that the left overs from eatlier reads
                // do not appear before HTTP/1.x
                unsigned int start = m_strReceived.find ("HTTP"); 
                if(start == std::string::npos)
                    start = 0;
                // Extract HTTP headers and process them
                m_strResponseHTTPHeaders = m_strReceived.substr (start,
                                           m_strReceived.
                                           find
                                           ("\r\n\r\n")
                                           + 2 - start);
                processResponseHTTPHeaders ();

                if (m_iResponseHTTPStatusCode != 200 && m_iResponseHTTPStatusCode != 500)
                {
                    throw
                    AxisTransportException
                    (SERVER_TRANSPORT_HTTP_EXCEPTION,
                     const_cast <
                     char *>(m_strResponseHTTPStatusMessage.c_str ()));
                }

                // Done with HTTP headers, get payload
                m_strReceived =
                    m_strReceived.substr (m_strReceived.find ("\r\n\r\n", start) +
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
                    /* We have received part of chunk data. If received payload
                     *  is a mime struct, process it
                     */
                    if(m_bMimeTrue)
                        processRootMimeBody();
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
                        /* We have received part of chunk data. If received payload
                         *  is a mime struct, process it
                         */
                        if(m_bMimeTrue)
                            processRootMimeBody();
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
                /* We have received part of chunk data. If received payload
                 *  is a mime struct, process it
                 */
                 if(m_bMimeTrue)
                    processRootMimeBody();
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

    case DLL_NAME:
    {
        if (m_bChannelSecure)
        {
             //((SecureChannel *) m_pChannel)->setTransportProperty (type, value);
             m_pFactory->initialize(value);
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
    if ( !pcKey || !pcValue ) // Samisa - fix for AXISCPP-295. We must check for valid values here.
        return;

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

            string key = strHeaderLine.substr (0, iSeperator);
            string value = strHeaderLine.substr (iSeperator + 1,
                                                 strHeaderLine.
                                                 length () -
                                                 iSeperator - 1 -
                                                 1);
            m_vResponseHTTPHeaders.push_back (std::make_pair (key, value));

            // if HTTP/1.0 we have to always close the connection by default
            if (m_eProtocolType == APTHTTP1_0)
                m_bReopenConnection = true;

            // if HTTP/1.1 we have to assume persistant connection by default

            // We need to close the connection and open a new one if we have 'Connection: close'
            if (key == "Connection" && value == " close" )
                m_bReopenConnection = true;

            // For both HTTP/1.0 and HTTP/1.1,
            // We need to keep the connection if we have 'Connection: Keep-Alive'
            if (key == "Connection" && value == " Keep-Alive" )
                m_bReopenConnection = false;

            // Look for cookies
            if(m_bMaintainSession && !(m_strSessionKey.size() > 0) )
            {                
                if (key == "Set-Cookie")
                {
                    m_strSessionKey = value;

                    // Spec syntax : Set-Cookie: NAME=VALUE; expires=DATE; path=PATH; domain=DOMAIN_NAME; secure
                    // This code assumes it to be : Set-Cookie: NAME=VALUE; Anything_else
                    // And discards stuff after first ';'
                    // This is the same assumption used in Axis Java
                    unsigned long ulKeyEndsAt = m_strSessionKey.find(";");
                    if (ulKeyEndsAt != std::string::npos)
                    {
                        m_strSessionKey = m_strSessionKey.substr(0, ulKeyEndsAt);
                    }
                }

            }

            /* If Content-Type: Multipart/Related; boundary=<MIME_boundary>; type=text/xml;
                   start="<content id>"*/
            if (key == "Content-Type")
            {
                m_strContentType = value;
                unsigned long ulMimePos = m_strContentType.find(";");
                std::string strTypePart;
                if (ulMimePos != std::string::npos)
                {
                    strTypePart = m_strContentType.substr(1, ulMimePos - 1);
                }
                if("Multipart/Related" == strTypePart)  
                {
                    m_bMimeTrue = true;
                    m_strContentType = m_strContentType.substr(ulMimePos + 1,
                        m_strContentType.length());

                    ulMimePos = m_strContentType.find("boundary=");
                    m_strMimeBoundary = m_strContentType.substr(ulMimePos);
                    ulMimePos = m_strMimeBoundary.find(";");
                    m_strMimeBoundary = m_strMimeBoundary.substr(9, ulMimePos - 9);
 
                    ulMimePos = m_strContentType.find("type=");
                    m_strMimeType = m_strContentType.substr(ulMimePos);
                    ulMimePos = m_strMimeType.find(";");
                    m_strMimeType = m_strMimeType.substr(5, ulMimePos - 5);

                    ulMimePos = m_strContentType.find("start=");
                    m_strMimeStart = m_strContentType.substr(ulMimePos);
                    ulMimePos = m_strMimeStart.find(";");
                    m_strMimeStart = m_strMimeStart.substr(6, ulMimePos - 6);
                }
            }
        }
        while (iPosition != std::string::npos);
    }
    else
    {
        throw AxisTransportException (SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
                                      "Protocol is not HTTP.");
    }
}

/* Axis2Transport::processRootMimeBody() Is a public method used to
 * parse the mime attachments.
 */
void
Axis2Transport::processRootMimeBody ()
{
    if (false == m_bReadPastRootMimeHeader)
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

        //now we have found the end of root mime header
        m_bReadPastRootMimeHeader = true;
        //processMimeHeader(); For the time being we don't process this
        // Done with root mime body headers, get rest of the payload 
        // which contain the soap message
        m_strReceived =
            m_strReceived.substr (m_strReceived.find ("\r\n\r\n") +
                                          4);
        unsigned int intMimeTemp = m_strReceived.find(m_strMimeBoundary);
        if (intMimeTemp != std::string::npos)
        {
             m_strReceived = m_strReceived.substr(0, intMimeTemp); 
             m_strMimeReceived = m_strReceived.substr(intMimeTemp);
             /* Using m_strMimeReceived will be 
              * continued when getAttachment is called.
              */
             m_bMimeTrue = false;
        }
    }
    else
    {
        unsigned int intMimeTemp = m_strReceived.find(m_strMimeBoundary);
        if (intMimeTemp != std::string::npos)
        {
             m_strReceived = m_strReceived.substr(0, intMimeTemp); 
             m_strMimeReceived = m_strReceived.substr(intMimeTemp);
             /* Using m_strMimeReceived will be 
              * continued when getAttachment is called.
              */
             m_bMimeTrue = false;
        }
        return;
    }
}

/* Axis2Transport::processMimeHeaders() Is a public method used to
 * parse the Mime headers of the response message.
 */
void
Axis2Transport::processMimeHeader ()
{
    unsigned int pos = 0;
    unsigned int temppos = 0;

    // Look for content lenght
    if ((pos =
        m_strMimeReceived.find ("Content-Type: ")) !=
        std::string::npos)
    {
        m_strMimeContentType =
        m_strMimeReceived.
        substr (pos + strlen ("Content-Type: "),
            m_strMimeReceived.find ("\n",
            pos));
        pos = m_strMimeContentType.find(";");
        temppos = m_strMimeContentType.find("\r\n");
        if(pos < temppos)
            m_strMimeContentType = m_strMimeContentType.substr(0, pos);
        else
            m_strMimeContentType = m_strMimeContentType.substr(0, temppos);
    }

    // Look for mime root body's content transfer encoding
    if ((pos =
        m_strMimeReceived.find ("Content-Transfer-Encoding: ")) !=
        std::string::npos)
    {
        m_strMimeContentTransferEncoding =
            m_strMimeReceived.
            substr (pos + strlen ("Content-Transfer-Encoding: "),
            m_strMimeReceived.find ("\n",
            pos));
        temppos = m_strMimeContentTransferEncoding.find("\r\n");
        m_strMimeContentTransferEncoding = m_strMimeContentTransferEncoding.substr(0, temppos);
    }

    // Look for mime root body's content id
    if ((pos =
         m_strMimeReceived.find ("Content-ID: ")) !=
         std::string::npos)
     {
         m_strMimeContentID =
         m_strMimeReceived.
         substr (pos + strlen ("Content-ID: "),
         m_strMimeReceived.find ("\n",
         pos));
        temppos = m_strMimeContentID.find("\r\n");
        m_strMimeContentID = m_strMimeContentID.substr(0, temppos);
     }
              
     // Look for mime root body's content location
     if ((pos =
         m_strMimeReceived.find ("Content-Location: ")) !=
         std::string::npos)
     {
         m_strMimeContentLocation =
         atoi (m_strMimeReceived.
         substr (pos + strlen ("Content-Location: "),
         m_strMimeReceived.find ("\n",
         pos)).c_str ());
        temppos = m_strMimeContentLocation.find("\r\n");
        m_strMimeContentLocation = m_strMimeContentLocation.substr(0, temppos);
     }
}

void
Axis2Transport::processMimeBody()
{
}

void
Axis2Transport::getAttachment(char* pStrAttachment, int* pIntSize,
    int intAttachmentId)
{
    std::string strTempReceived = "";
    *m_pChannel >> strTempReceived;	// Assume non blocking here
    m_strMimeReceived += strTempReceived;
    do
    {
         if (m_strMimeReceived.find ("\r\n\r\n") == std::string::npos)
         {
              strTempReceived = "";
              *m_pChannel >> strTempReceived;	// Assume non blocking here
              m_strMimeReceived += strTempReceived;
         }
    }
    while (m_strMimeReceived.find ("\r\n\r\n") == std::string::npos);
    //now we have found the end of next mime header
    processMimeHeader();
    m_strMimeReceived = m_strMimeReceived.substr(m_strMimeReceived.
        find("\r\n\r\n"));
    processMimeBody();
}

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

const char* Axis2Transport::getFirstTransportPropertyKey()
{
    m_viCurrentHeader = m_vHTTPHeaders.begin();

    if (m_viCurrentHeader == m_vHTTPHeaders.end())
        return NULL;
    else
        return (*m_viCurrentHeader).first.c_str();
}

const char* Axis2Transport::getNextTransportPropertyKey()
{
    //already at the end?
    if (m_viCurrentHeader == m_vHTTPHeaders.end())
        return NULL;

    m_viCurrentHeader++;

    if (m_viCurrentHeader == m_vHTTPHeaders.end())
        return NULL;
    else
        return (*m_viCurrentHeader).first.c_str();

}

const char* Axis2Transport::getCurrentTransportPropertyKey()
{
    if (m_viCurrentHeader == m_vHTTPHeaders.end())
        return NULL;
    else
        return (*m_viCurrentHeader).first.c_str();
}

const char* Axis2Transport::getCurrentTransportPropertyValue()
{
    if (m_viCurrentHeader == m_vHTTPHeaders.end())
        return NULL;
    else
        return (*m_viCurrentHeader).second.c_str();
}

void Axis2Transport::deleteCurrentTransportProperty()
{
    if (m_viCurrentHeader != m_vHTTPHeaders.end())
    {
        m_vHTTPHeaders.erase(m_viCurrentHeader);
    }
}

void Axis2Transport::deleteTransportProperty(char* pcKey, unsigned int uiOccurance)
{
    vector <std::pair < std::string, std::string > >::iterator currentHeader = m_vHTTPHeaders.begin();
    unsigned int uiCount = 1;

    while(currentHeader != m_vHTTPHeaders.end() && uiCount <= uiOccurance)
    {
        if(strcmp(pcKey, (*currentHeader).first.c_str() ) == 0)
        {
            if(uiCount == uiOccurance)
            {
                m_vHTTPHeaders.erase(currentHeader);
                break;
            }
            uiCount++;
        }
        currentHeader++;

    }
}

void Axis2Transport::setMaintainSession(bool bSession)
{
    m_bMaintainSession = bSession;
}

void Axis2Transport::setSessionId (const char *pcSessionId)
{
    m_strSessionKey = std::string(pcSessionId);
}

const char* Axis2Transport::getSessionId ()
{
	return m_strSessionKey.c_str();
}

