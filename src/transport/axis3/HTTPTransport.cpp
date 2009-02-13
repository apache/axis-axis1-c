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

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include "HTTPTransport.hpp"

#include "../../platforms/PlatformLanguageUtils.hpp"

// for the basic auth encryption
#include "../../soap/apr_base64.h"

#include <stdio.h>


#include "../../common/AxisTrace.h"

static int axtoi( char *pcHexString);

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

#define ASCII_S_LEFTPAREN      "\x28"   // "("

/*
 * HTTPTransport constuctor
 */
HTTPTransport::
HTTPTransport ():
m_bReopenConnection (false),
m_strHTTPProtocol ("HTTP/1.1"),
m_strHTTPMethod ("POST"),
m_strProxyHost (""), 
m_uiProxyPort (0), 
m_bUseProxy (false),
m_bMaintainSession (false)
{
    logEntryTransport("HTTPTransport::HTTPTransport")

    m_pcEndpointUri = NULL;
    m_pReleaseBufferCallback = 0;
    m_eProtocolType = APTHTTP1_1;
    m_strBytesToSend = "";
    m_strHeaderBytesToSend = "";
    m_bChannelSecure = false;
    m_pNormalChannel = 0;
    m_pSecureChannel = 0;
    m_pActiveChannel = 0;
    m_pChannelFactory = new ChannelFactory();
    m_viCurrentHeader = m_vHTTPHeaders.begin();
    m_viCurrentResponseHeader = m_vResponseHTTPHeaders.begin();
    m_pszRxBuffer = new char [BUF_SIZE];
    m_pcUsername=NULL;
    m_pcPassword=NULL;
#ifdef WIN32
    m_lChannelTimeout = 10;
#else
    m_lChannelTimeout = 0;
#endif
    m_pNormalChannel = m_pChannelFactory->createChannel(UnsecureChannel);
    m_pSecureChannel = m_pChannelFactory->createChannel(SecureChannel);

    resetInputStateMachine();
    
    logExit()
}

/*
 * HTTPTransport destructor
 */
HTTPTransport::
~HTTPTransport()
{
    logEntryTransport("HTTPTransport::~HTTPTransport")

    delete [] m_pcEndpointUri;
    delete m_pChannelFactory; // should also destroy channels
    delete [] m_pszRxBuffer;
    
    logExit()
}

void HTTPTransport::
resetInputStateMachine()
{
    logEntryTransport("HTTPTransport::resetInputStateMachine")

    m_GetBytesState = eWaitingForHTTPHeader;
    
    m_strReceived.erase();
    m_iBytesLeft = 0;
    m_iChunkedDataLeftToConsume = 0;
    m_iNextChunkedDataSize = 0;
    m_iContentLength = 0;
    m_bMimeTrue = false;  
    
    logExit()
}

/*
 * HTTPTransport::setEndpointUri( EndpointURI) sets the URI for the message.
 * Everytime the endpoint changes then currently connected channel is closed
 * and a new channel connection is opened.
 *
 * @param   EndpointURI - char * to a null terminated string that holds the
 *         new URI. 
 */
void HTTPTransport::
setEndpointUri( const char * pcEndpointUri) throw (HTTPTransportException)
{
    logEntryTransport("HTTPTransport::setEndpointUri")

    logDebugArg1("Endpoint is %s", pcEndpointUri ? pcEndpointUri : "NULL")

    // if URI not valid, return
    if (!pcEndpointUri || strlen(pcEndpointUri) < strlen("http://") )
    {
        logExit()
        
        return;  
    }

    // Does the new URI equal the existing channel URI?
    // If there is a new URI, then connection will be closed and a secure or unsecure channel 
    // will be set. If the required channel is not available, an exception will be thrown.    
    if (m_pActiveChannel == NULL || m_pActiveChannel->getURL() == NULL
            || strcmp(m_pActiveChannel->getURL(), pcEndpointUri) != 0)
    {
        if( m_pActiveChannel == NULL)
            m_pActiveChannel = m_pNormalChannel;

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
                logThrowException("HTTPTransportException - CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER")

                throw HTTPTransportException( CLIENT_TRANSPORT_HAS_NO_SECURE_TRANSPORT_LAYER);
            }
        }
        else if (m_bChannelSecure)
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
                logThrowException("HTTPTransportException - CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER")

                throw HTTPTransportException( CLIENT_TRANSPORT_HAS_NO_UNSECURE_TRANSPORT_LAYER);
            }
        }
    }

    // Set the channel timeout.  If the timeout was changed before the 
    // channel was created, then it may not have the correct timeout. By setting it here, 
    // the channel is sure to have the correct timeout value next time the channel is read.
    if( m_pActiveChannel != NULL)
        m_pActiveChannel->setTimeout( m_lChannelTimeout);
    
    logExit()
}

/*
 * HTTPTransport::openConnection().
 */

int HTTPTransport::
openConnection()
{
    logEntryTransport("HTTPTransport::openConnection")

    // If connection not valid or reopen required, open a connection to server.
    if (m_pActiveChannel->reopenRequired() || m_bReopenConnection)
    {
        closeConnection(true);
        if( m_pActiveChannel->open() != AXIS_SUCCESS)
        {
            logThrowExceptionWithData("HTTPTransportException - CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED", 
                                      m_pActiveChannel->GetLastErrorMsg().c_str())

            throw HTTPTransportException( CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED,
                                          m_pActiveChannel->GetLastErrorMsg().c_str());
        }
    }

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

/*
 * HTTPTransport::closeConnection().
 */
void HTTPTransport::
closeConnection(bool forceClose)
{
    logEntryTransport("HTTPTransport::closeConnection")

    resetInputStateMachine();
    
    // We will close the connection if forced close, or if "Connection: close" 
    // header was detected.
    if (forceClose || m_bReopenConnection)
    {
        m_bReopenConnection = false;
        m_pActiveChannel->close();
    }
    
    logExit()
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
AXIS_TRANSPORT_STATUS HTTPTransport::
flushOutput() throw (AxisException, HTTPTransportException)
{
    logEntryTransport("HTTPTransport::flushOutput")

    char *utf8Buf = NULL; // buffer for ebcdic/utf8 conversions.

    // In preperation for sending the message, set Content-Length HTTP header.
    char buff[24];
    sprintf( buff, "%d", m_strBytesToSend.length ());
    this->setTransportProperty ("Content-Length", buff);

    // The header is now complete.  The message header and message can now be transmitted.
    try
    {
        // Generate HTTP header string
        generateHTTPHeaders ();
                
        // Send HTTP headers and body
#ifndef __OS400__
        m_pActiveChannel->writeBytes(m_strHeaderBytesToSend.c_str(), m_strHeaderBytesToSend.length());
        m_pActiveChannel->writeBytes(m_strBytesToSend.c_str(), m_strBytesToSend.length());
#else
        // Ebcdic (OS/400) systems need to convert the data to UTF-8. 
        utf8Buf = PlatformLanguageUtils::toUTF8((const char *)m_strHeaderBytesToSend.c_str(), m_strHeaderBytesToSend.length()+1);
        m_pActiveChannel->writeBytes(utf8Buf, strlen(utf8Buf));
        delete utf8Buf;
        utf8Buf = NULL;
        utf8Buf = PlatformLanguageUtils::toUTF8((const char *)m_strBytesToSend.c_str(), m_strBytesToSend.length()+1);
        m_pActiveChannel->writeBytes(utf8Buf, strlen(utf8Buf));
        delete utf8Buf;
        utf8Buf = NULL;
#endif
    }
    catch(...)
    {
        delete utf8Buf;
        m_strBytesToSend = "";
        m_strHeaderBytesToSend = "";
        
        logRethrowException()
        
        throw;
    }

    // Empty the bytes to send string.
    m_strBytesToSend = "";
    m_strHeaderBytesToSend = "";

    // Also empty the response headers as there aren't any yet until the response comes back !
    m_vResponseHTTPHeaders.clear();
    // TODO: Possible memory leak here - does the clear op clean out the memory too?

    logExit()
    
    return TRANSPORT_FINISHED;
}

/* HTTPTransport::getHTTPHeaders() Called to retrieve the current HTTP header
 * information block that will preceed the SOAP message.
 *
 * @return const char* Pointer to a NULL terminated character string containing
 * the HTTP header block of information.
 */
const char * HTTPTransport::
generateHTTPHeaders()
{
    logEntryTransport("HTTPTransport::generateHTTPHeaders")

    URL & url = m_pActiveChannel->getURLObject();
    unsigned short uiPort;
    char buff[32];

    m_strHeaderBytesToSend = m_strHTTPMethod + " ";

    if (m_bUseProxy)
        m_strHeaderBytesToSend += url.getURL ();
    else
        m_strHeaderBytesToSend += url.getResource ();

    m_strHeaderBytesToSend += " ";
    m_strHeaderBytesToSend += m_strHTTPProtocol;

    // The "Host:" HTTP request header should specify the Internet host and port number of 
    // the resource being requested, as obtained from the original URI given by the user or 
    // referring resource. 
    
    m_strHeaderBytesToSend += "\r\nHost: ";
    m_strHeaderBytesToSend += url.getHostName ();
    uiPort = url.getPort();
    
    sprintf(buff, ":%u\r\n", uiPort);
    m_strHeaderBytesToSend += buff;

    // The Content-Type must be set, but it may already be set.
    bool foundCT = false;
    for (unsigned int j = 0; j < m_vHTTPHeaders.size (); j++)
        if (0==strcmp(AXIS_CONTENT_TYPE,m_vHTTPHeaders[j].first.c_str()))
            foundCT = true;

    if (!foundCT)
        m_strHeaderBytesToSend += AXIS_CONTENT_TYPE ": text/xml; charset=UTF-8\r\n";

    // set basic auth if the username and password are both set
    if(getUsername()!=NULL && getPassword() !=NULL)
    {
        char *cpUsernamePassword = new char[strlen (getUsername()) + strlen (getPassword()) + 2];
        strcpy (cpUsernamePassword, getUsername());
        strcat (cpUsernamePassword, ":");
        strcat (cpUsernamePassword, getPassword());

        // We use apr_base64_encode and NOT apr_base64_encode_binary since this is 
        // textual data that needs to be converted to ascii on ebcdic platforms. 
        // On ascii platforms the data will just get passed to apr_base64_encode_binary().
        int len = apr_base64_encode_len (strlen (cpUsernamePassword));
        AxisChar *base64Value = new AxisChar[len + 1];
        len = apr_base64_encode(base64Value,(const char *) cpUsernamePassword);

        std::string strValue = "Basic ";
        strValue += base64Value;

        setTransportProperty ("Authorization", strValue.c_str ());

        delete[]cpUsernamePassword;
        delete[]base64Value;
    }

    // Set other HTTP headers but not cookies as they are put in afterwards.
    for (unsigned int i = 0; i < m_vHTTPHeaders.size (); i++)
    {
        if( strcmp(m_vHTTPHeaders[i].first.c_str(), "Cookie")!=0)
        {
            m_strHeaderBytesToSend += m_vHTTPHeaders[i].first;
            m_strHeaderBytesToSend += ": ";
            m_strHeaderBytesToSend += m_vHTTPHeaders[i].second;
            m_strHeaderBytesToSend += "\r\n";
            
            if (0==strcmp("Connection",m_vHTTPHeaders[i].first.c_str())
                    && 0==strcmp("close", m_vHTTPHeaders[i].second.c_str()))
                m_bReopenConnection = true;
        }
    }

    // Set cookies
    if (m_bMaintainSession && (m_vCookies.size () > 0))
    {
        string cookieHeader="";

        // Add in all the cookies ar the last one because that shouldn't have a ';' on it
        for (unsigned int var = 0; var < m_vCookies.size()-1; var++)
        {
            cookieHeader += m_vCookies[var].first;
            cookieHeader += "=";
            cookieHeader += m_vCookies[var].second;
            cookieHeader += ";";
        }
        
        // add on the last cookie
        cookieHeader += m_vCookies[m_vCookies.size()-1].first;
        cookieHeader += "=";
        cookieHeader += m_vCookies[m_vCookies.size()-1].second;

        m_strHeaderBytesToSend += "Cookie: ";
        m_strHeaderBytesToSend += cookieHeader;
        m_strHeaderBytesToSend += "\r\n";

        // Now add this header in to the list of sent headers if it's not already been set ! If it has been then
        // override it
        bool b_keyFound=false;
        for (unsigned int i = 0; i < m_vHTTPHeaders.size(); i++)
        {
            if (m_vHTTPHeaders[i].first == (string)"Cookie")
            {
                m_vHTTPHeaders[i].second = (string) cookieHeader;
                b_keyFound = true;

                break;
            }
        }
        if(!b_keyFound)
        {
            m_vHTTPHeaders.push_back( std::make_pair( (string) "Cookie", (string) cookieHeader));
        }
    }

    m_strHeaderBytesToSend += "\r\n";

    logExit()
    
    return m_strHeaderBytesToSend.c_str ();
}

/* HTTPTransport::getHTTPMethod() Is a public method that gets the HTTP method
 * (i.e. GET or POST) that will be part of the HTTP header block.
 *
 * @return const char* Pointer to a NULL terminated character string containing
 * the HTTP method.
 */
const char * HTTPTransport::
getHTTPMethod()
{
    return m_strHTTPMethod.c_str ();
}

/* HTTPTransport::setHTTPMethod( Method) Is a public method that sets the HTTP
 * method (i.e. POST or GET) that will be part of the HTTP header block.
 *
 * @param const char* Pointer to a NULL terminated character string containing
 * the new HTTP method.
 */
void HTTPTransport::
setHTTPMethod( const char *cpMethod)
{
    logEntryTransport("HTTPTransport::setHTTPMethod")
    
    logDebugArg1("HTTP method is %s", cpMethod ? cpMethod : "NULL")

    if (cpMethod)
        m_strHTTPMethod = std::string( cpMethod);
    
    logExit()
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
AXIS_TRANSPORT_STATUS HTTPTransport::
sendBytes( const char *pcSendBuffer, const void *pBufferId)
{
    m_strBytesToSend += std::string (pcSendBuffer);

    return TRANSPORT_IN_PROGRESS;
}

bool HTTPTransport::
isThereResponseData()
{
    logEntryTransport("HTTPTransport::isThereResponseData")

    // We do not want to consume any SOAP data, just find out if there is any data.
    int bufLen = 0;
    getBytes(NULL, &bufLen);
    bool returnValue = (m_GetBytesState != eWaitingForHTTPHeader || m_iBytesLeft != 0);
    
    logExitWithBoolean(returnValue)
    
    return returnValue;
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
AXIS_TRANSPORT_STATUS HTTPTransport::
getBytes( char * pcBuffer, int * piSize) throw (AxisException, HTTPTransportException)
{
    logEntryTransport("HTTPTransport::getBytes")

    // The method getBytes has three distinct states.  These are defined as
    // follows:-
    //   eWaitingForHTTPHeader        - Waiting for HTTP response header. Initiate processing
    //                                  that will read an HTTP header. One caveat. 
    //                                  We can be in this state but still have data
    //                                  to be processed. So if there is data, it will
    //                                  be returned and we will not attempt to read 
    //                                  an HTTP response. 
    //   eSOAPMessageIsChunked        - Keep reading until a zero length chunk is 
    //                                  encountered, signifying end of response.
    //   eSOAPMessageIsNotChunked     - Keep reading until the connection is closed. 
    //   eSOAPMessageHasContentLength - Keep reading until content-length is zero.        

    
    // Read in an HTTP header if we are waiting for one.  Now this is a bit tricky
    // and I was fooled by this when I was fix problems in the code so here is 
    // the tricky part.  If we have data in the buffer then we need to return 
    // the data - i.e. we will skip reading HTTP header until data has been 
    // consumed!  Not the most elegant of designs, but it works.  The reason is 
    // that we read in data later on and then change the state based on whether 
    // there is more data to read or not.  The caller of this routine will have
    // data copied into buffer, but the buffer may not be big enough to consume
    // the data, so that is why we have data in the buffer left and thus must 
    // skip reading HTTP header until data has been consumed. 
    if (m_GetBytesState == eWaitingForHTTPHeader)
        if (m_iBytesLeft == 0)
            readHTTPHeader();

    // Process data based on current state. 
    int iBytesToCopy = m_iBytesLeft;
    
    if (m_GetBytesState == eSOAPMessageHasContentLength)
        iBytesToCopy = getBytes_MessageHasContentLength(pcBuffer, piSize);
    else if (m_GetBytesState == eSOAPMessageIsNotChunked)
        iBytesToCopy = getBytes_MessageIsNotChunked(pcBuffer, piSize);
    else if( m_GetBytesState == eSOAPMessageIsChunked)
        iBytesToCopy = getBytes_MessageIsChunked(pcBuffer, piSize);

    // Copy as much of the message to the parser buffer as possible.
    if (iBytesToCopy > 0 && *piSize > 0)
    {
        int iToCopy = (*piSize < iBytesToCopy) ? *piSize : iBytesToCopy;

        m_strReceived.copy(pcBuffer, iToCopy);
        *piSize = iToCopy;
        m_iBytesLeft -= iToCopy;
        m_strReceived.erase(0, iToCopy);
    }
    else
        *piSize = 0;
    
    logExit()
    
    // Set transport status 
    return (m_iBytesLeft > 0 || (m_GetBytesState != eWaitingForHTTPHeader)) ? 
                TRANSPORT_IN_PROGRESS : TRANSPORT_FINISHED;
}

/**
 * getBytes_MessageHasContentLength() is used when the HTTP response 
 * includes the Content-Length HTTP header. 
 */
int HTTPTransport::
getBytes_MessageHasContentLength(char * pcBuffer, int * piSize)
{
    logEntryTransport("HTTPTransport::getBytes_MessageHasContentLength")

    // If we do not have data to give back, read more.  
    if (m_iContentLength > 0 && m_iBytesLeft == 0)
    {
        getNextDataPacket( "No data available for message.");

        // Check for Mime header
        if( m_bMimeTrue)
        {
            processRootMimeBody();
            m_iBytesLeft = m_strReceived.length();
        }              
    }
    
    // Subtract message length (so far) from expected content length.
    if( m_iContentLength >= m_iBytesLeft)
        m_iContentLength -= m_iBytesLeft;
    else
        m_iContentLength = 0;          
    
    // If all of the message has been received, then reset the process state
    if (0 == m_iContentLength)
        m_GetBytesState = eWaitingForHTTPHeader;
        
    logExitWithInteger(m_iBytesLeft)

    // Return number of bytes that can be copied
    return m_iBytesLeft;
}

/**
 * getBytes_MessageIsNotChunked() is used when the HTTP response 
 * is not chunked and does not include the Content-Length HTTP header.
 * Thus, the only way we know that the data has been read is to read 
 * from the input stream until a zero length read completes. 
 */
int HTTPTransport::
getBytes_MessageIsNotChunked(char * pcBuffer, int * piSize)
{
    logEntryTransport("HTTPTransport::getBytes_MessageIsNotChunked")

    // Keep reading until the connection is closed by the server.
    getNextDataPacket( "Expecting server connection to close.");

    // Check for Mime header
    if( m_bMimeTrue)
    {
        processRootMimeBody();
        m_iBytesLeft = m_strReceived.length();
    }
    
    logExitWithInteger(m_iBytesLeft)

    // Return number of bytes that can be copied
    return m_iBytesLeft;
}

/**
 * getBytes_MessageIsChunked() is used when the HTTP response 
 * is chunked. The chunked encoding modifies the body of a message 
 * in order to transfer it as a series of chunks, each with its own 
 * size indicator, followed by an OPTIONAL trailer containing 
 * entity-header fields. This allows dynamically produced content to 
 * be transferred along with the information necessary for the recipient 
 * to verify that it has received the full message. Format is as follows:
 * 
 *     Chunked-Body   = *chunk
 *                      last-chunk
 *                      trailer
 *                      CRLF
 * 
 *     chunk          = chunk-size [ chunk-extension ] CRLF
 *                      chunk-data CRLF
 *     chunk-size     = 1*HEX
 *     last-chunk     = 1*("0") [ chunk-extension ] CRLF
 * 
 *     chunk-extension= *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
 *     chunk-ext-name = token
 *     chunk-ext-val  = token | quoted-string
 *     chunk-data     = chunk-size(OCTET)
 *     trailer        = *(entity-header CRLF)
 * 
 * The chunk-size field is a string of hex digits indicating the size of the 
 * chunk. The chunked encoding is ended by any chunk whose size is zero, 
 * followed by the trailer, which is terminated by an empty line.  The 
 * trailer is ignored by this routine.
 */
int HTTPTransport::
getBytes_MessageIsChunked(char * pcBuffer, int * piSize)
{
    logEntryTransport("HTTPTransport::getBytes_MessageIsChunked")

    // We only read the next chunk if the chunk we have has been consumed. 
    if (m_iChunkedDataLeftToConsume == 0)
    {
        // First, ensure that we remove any leading CRLF.  This would be the 
        // ending CRLF for a chunk.  A chunk has this form:
        //    chunk-data CRLF
        if (m_iBytesLeft > 1 
                && m_strReceived[0] == ASCII_C_CR && m_strReceived[1] == ASCII_C_LF)
        {
            m_strReceived.erase(0, 2);
            m_iBytesLeft = m_strReceived.length();
        }
        
        // Get chunk size.  We may already have it. It is set to zero only if we have 
        // not obtained it. It is also set to zero for end of chunk size of zero, but we should
        // never be coming down to read it. 
        if (m_iNextChunkedDataSize > 0)
        {
            // Need to remove the chunk-size line since it has been already processed.
            // Should never be the case where we get npos, but we check just in case.
            string::size_type iEndOfChunkSize = m_strReceived.find(ASCII_S_CRLF);
            if (iEndOfChunkSize != std::string::npos)
            {
                m_strReceived.erase(0, iEndOfChunkSize + 2);
                m_iBytesLeft  = m_strReceived.length(); 
            }
            
            m_iChunkedDataLeftToConsume = m_iNextChunkedDataSize;
            m_iNextChunkedDataSize = 0;
        }
        else
            m_iChunkedDataLeftToConsume = getChunkSize(); 
    
        // We should never be in a situation where caller invokes getBytes 
        // and there is no data to read, but just in case...
        if (m_iChunkedDataLeftToConsume > 0)
        {
            // If the chunk size is larger than the available data, then read in more 
            // data until all of the chunk has been read.  We read in the CRLF that
            // ends a chunk and at least one more byte so that later we can read the
            // next chunk size.            
            while ((m_iChunkedDataLeftToConsume + 2) >= m_iBytesLeft)
                getNextDataPacket( "No data available for next chunk.");
        
            // Determine next chunk size, mainly to determine if zero-length, 
            // meaning end-of-chunk processing and thus a state reset. 
            // "+ 2" used in if-check for CRLF since at end of each chunk there should be CRLF.
            if (0 == (m_iNextChunkedDataSize = getChunkSize(m_iChunkedDataLeftToConsume + 2)))
                m_GetBytesState = eWaitingForHTTPHeader;
        
            // The chunk may contain Mime data (this depends on information in the HTTP header).  
            if( m_bMimeTrue)
            {
                processRootMimeBody();
                m_iBytesLeft = m_strReceived.length();
            }
        }
        else
            m_GetBytesState = eWaitingForHTTPHeader;
    }
    
    // OK, now we need to determine how much of the chunk will be left 
    // over depending on the buffer length that is passed in.
    int iDataToCpyLen;
    if (*((unsigned int *)piSize) >= m_iChunkedDataLeftToConsume)
    {
        iDataToCpyLen = m_iChunkedDataLeftToConsume;
        m_iChunkedDataLeftToConsume = 0;
    }
    else
    {
        iDataToCpyLen = *piSize;
        m_iChunkedDataLeftToConsume -= *piSize;
    }
    
    logExitWithInteger(iDataToCpyLen)

    return iDataToCpyLen;
}

/**
 * getChunkSize() is method used to obtain the chunk size. 
 * Once obtained, it may remove the chunksize line from 
 * the data since it is not data to be returned.
 */
int HTTPTransport::
getChunkSize(string::size_type pos)
{
    logEntryTransport("HTTPTransport::getChunkSize")

    string::size_type iEndOfChunkSize;
    string::size_type iEndOfChunkLine;
    
    // Here is what a chunk size line may look like:
    //    chunk-size [ chunk-extension ] CRLF
    // where chunk-extension is defined as:
    //    *( ";" chunk-ext-name [ "=" chunk-ext-val ] )
    
    // Get complete line.
    while( (iEndOfChunkLine = m_strReceived.find(ASCII_S_CRLF, pos)) == std::string::npos )
        getNextDataPacket("Could not find delimiter for end of chunk size.");    

    string chunkSizeLine = m_strReceived.substr( pos, iEndOfChunkLine-pos);
    
    // Look to see if there are any extensions - these are put in brackets.
    if ((iEndOfChunkSize = chunkSizeLine.find(ASCII_S_LEFTPAREN)) != std::string::npos)
        chunkSizeLine.erase(iEndOfChunkSize);
    
    // Convert the hex string into the length of the chunk.
    int chunkSize = axtoi((char *)chunkSizeLine.c_str());  
    
    // A chunk size of -1 means either we received an invalid chunk size 
    // or the code is not parsing chunks correctly.  Whatever the case, 
    // we are hosed and there is no use continuing.
    if (-1 == chunkSize)
    {
        m_bReopenConnection = true;
        
        // We will only dump out just 40 bytes...otherwise we may be 
        // dumping out huge chunks of data
        if (chunkSizeLine.length() > 40)
            chunkSizeLine = chunkSizeLine.substr(0, 40);
        
        PLATFORM_ASCTOSTR(chunkSizeLine.c_str());
        string errorMessage = string("Chunk size (") + chunkSizeLine + string(") not valid.");
        
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_HTTP_EXCEPTION", errorMessage.c_str())
                                         
        throw HTTPTransportException(SERVER_TRANSPORT_HTTP_EXCEPTION, errorMessage.c_str());        
    }

    // If chunksize is zero, remove the line including ending CRLFCRLF. This line
    // will never be consumed so it needs to be removed from the buffer. Otherwise,
    // if chunksize is not zero, we only remove the chunksize line only if offset is 
    // zero, i.e. at the beginning of line. If offset is not zero, it means this 
    // request came down to peek at the next chunksize.     
    if (0 == chunkSize)
    {
        string::size_type iEndOfResponse;
        while ((iEndOfResponse = m_strReceived.find(ASCII_S_CRLFCRLF, pos)) == std::string::npos )
            getNextDataPacket("Could not find delimiter for end of chunked response."); 
        
        m_strReceived.erase(pos, iEndOfResponse + 4); // "+4" for CRLFCRLF
    }
    else if (pos == 0)
        m_strReceived.erase(0, iEndOfChunkLine + 2); // "+2" for CRLF
    m_iBytesLeft  = m_strReceived.length();   
    
    logExitWithInteger(chunkSize)
 
    // return chunksize
    return chunkSize;
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
int HTTPTransport::
setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char *value) throw (HTTPTransportException)
{
    logEntryTransport("HTTPTransport::setTransportProperty")

    const char *key = NULL;
    int   iSuccess = AXIS_SUCCESS;

    switch (type)
    {
        case SOAPACTION_HEADER:
        {
            key = "SOAPAction";
            break;
        }

        case SERVICE_URI:      // need to set ?
        {
            break;
        }

        case OPERATION_NAME:   // need to set ?
        {
            break;
        }

        case SOAP_MESSAGE_LENGTH:
        {
            key = "Content-Length";   // this Axis transport handles only HTTP
            break;
        }

        case TRANSPORT_PROPERTIES:
        {
            if (value && strcmp(value, "Connection: close") == 0)
                setTransportProperty("Connection", "close");
            else if( m_pActiveChannel != NULL)
                m_pActiveChannel->setTransportProperty( type, value);

            break;
        }

        case SECURE_PROPERTIES:
        {
            if( m_pActiveChannel != NULL)
                iSuccess = m_pActiveChannel->setSecureProperties( value);
            
            break;
        }

        case CHANNEL_HTTP_DLL_NAME:
        {
            if( m_pChannelFactory != NULL)
                m_pNormalChannel = m_pChannelFactory->LoadChannelLibrary( UnsecureChannel, value);

            break;
        }

        case CHANNEL_HTTP_SSL_DLL_NAME:
        {
            if( m_pChannelFactory != NULL)
                m_pSecureChannel = m_pChannelFactory->LoadChannelLibrary( SecureChannel, value);

            break;
        }

        default:
        {
            break;
        }
    }

    if( key)
        setTransportProperty( key, value);

    logExitWithReturnCode(iSuccess)
    
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
int HTTPTransport::
setTransportProperty( const char *pcKey, const char *pcValue) throw (HTTPTransportException)
{
    logEntryTransport("HTTPTransport::setTransportProperty")

    int   iSuccess = AXIS_SUCCESS;

    if( pcKey && pcValue) 
    {
        logDebugArg2("Transport property to set: %s=%s", pcKey, pcValue)

        bool b_KeyFound = false;
    
        // Check for well known headers that we add on in every iteration
        if (strcmp( pcKey, "SOAPAction") == 0 
                || strcmp( pcKey, "Content-Length") == 0
                || strcmp( pcKey, "Connection") == 0)
        {
            std::string strKeyToFind = std::string( pcKey);
    
            for (unsigned int i = 0; i < m_vHTTPHeaders.size(); i++)
                if (m_vHTTPHeaders[i].first == strKeyToFind)
                {
                    m_vHTTPHeaders[i].second = (string) pcValue;
                    b_KeyFound = true;
    
                    break;
                }
        }
        else if(strcmp(pcKey, "Cookie")==0)
        {
            iSuccess = addCookie(pcValue);
            b_KeyFound = true;
        }
        
        if( !b_KeyFound)
            m_vHTTPHeaders.push_back( std::make_pair( (string) pcKey, (string) pcValue));
    }
    
    logExitWithReturnCode(iSuccess)

    return iSuccess;
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
const char * HTTPTransport::
getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE eType) throw (HTTPTransportException)
{
    logEntryTransport("HTTPTransport::getTransportProperty")

    const char *pszPropValue = NULL;

    switch( eType)
    {
        case SOAPACTION_HEADER:
        {
            int iIndex = FindTransportPropertyIndex( "SOAPAction");

            if (iIndex > -1)
                pszPropValue = m_vHTTPHeaders[iIndex].second.c_str();

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
                pszPropValue = m_vHTTPHeaders[iIndex].second.c_str();

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

    logExitWithString(pszPropValue)

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
int HTTPTransport::
FindTransportPropertyIndex( string sKey)
{
    bool   bKeyFound = false;
    int      iIndex = 0;

    while( (unsigned int) iIndex < m_vHTTPHeaders.size() && !bKeyFound)
    {
        if (!m_vHTTPHeaders[iIndex].first.compare( sKey))
            bKeyFound = true;
        else
            iIndex++;
    }

    if( !bKeyFound)
        iIndex = -1;

    return iIndex;
}

/* HTTPTransport::getServiceName() Is a public method to return the HTTP
 * Header service name.
 *
 * @return const char* Value is a NULL terminated character string containing
 * the value associated with the service name.
 */
const char * HTTPTransport::
getServiceName()
{
    //Assume SOAPAction header to contain service name
    int iIndex = FindTransportPropertyIndex( "SOAPAction");

    if (iIndex > -1)
      return m_vHTTPHeaders[iIndex].second.c_str();

    return NULL;
}


AXIS_PROTOCOL_TYPE HTTPTransport::
getProtocol()
{
    return m_eProtocolType;
}

int HTTPTransport::
setProtocol( AXIS_PROTOCOL_TYPE eProtocol)
{
    if (eProtocol == APTHTTP1_1 || eProtocol == APTHTTP1_0)
    {
      m_eProtocolType = eProtocol;

      m_strHTTPProtocol = (m_eProtocolType == APTHTTP1_1) ? "HTTP/1.1" : "HTTP/1.0";

      return AXIS_SUCCESS;
    }

    return AXIS_FAIL;
}

/**
 * HTTPTransport::getSubProtocol() is a public method that is supposed to
 * return the sub protocol (currently this method always return POST).
 * This method is supposed to return whether it is http GET or POST
 */
int HTTPTransport::
getSubProtocol()
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
void HTTPTransport::
setProxy( const char *pcProxyHost, unsigned int uiProxyPort)
{
    logEntryTransport("HTTPTransport::setProxy")

    logDebugArg2("Proxy host is %s, proxy port is %d", pcProxyHost ? pcProxyHost : "NULL", uiProxyPort)

    m_pActiveChannel->setProxy(pcProxyHost,uiProxyPort);
    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;
    
    logExit()
}

/* HTTPTransport::setTimeout( Timeout) Is a public method for setting the
 * current maximum timeout period between that can elapse between receiving
 * message parts.
 *
 * @param long Timeout is a long value in seconds.
 */
void HTTPTransport::
setTimeout( long lSeconds)
{
    logEntryTransport("HTTPTransport::setTimeout")

    if( m_pActiveChannel != NULL)
        m_pActiveChannel->setTimeout( lSeconds);

    m_lChannelTimeout = lSeconds;
    
    logExit()
}

/* HTTPTransport::getHTTPProtocol() Is a public method for retrieving the
 * current HTTP protocol settings.
 *
 * @return const char* HTTPProtocol is a NULL terminated character string
 * containing the HTTP protocol.
 */
const char * HTTPTransport::
getHTTPProtocol()
{
    return m_strHTTPProtocol.c_str ();
}

/* axtoi( Hex) Is a private method to convert an ascii hex string to an integer.
 */
static int axtoi( char *pcHexString)
{
    int      iN = 0;         // position in string
    int      iM = 0;         // position in digit[] to shift
    int      iCount;         // loop index
    int      intValue = 0;   // integer value of hex string
    int      iDigit[32];     // hold values to convert

    bool     badChunkSize = false;

    while( iN < 32 && pcHexString[iN] != '\0')
    {
        if( pcHexString[iN] >= ASCII_C_ZERO && pcHexString[iN] <= ASCII_C_NINE)
        {
            iDigit[iN] = pcHexString[iN] & 0x0f;   //convert to int
        }
        else if ((pcHexString[iN] >= ASCII_C_LOWERCASEA &&
                  pcHexString[iN] <= ASCII_C_LOWERCASEF) ||
                 (pcHexString[iN] >= ASCII_C_UPPERCASEA &&
                  pcHexString[iN] <= ASCII_C_UPPERCASEF))
        {
            iDigit[iN] = (pcHexString[iN] & 0x0f) + 9;   //convert to int
        }
        else
        {
            badChunkSize = true;
            break;
        }

        iN++;
    }
    
    if (badChunkSize || pcHexString[0] == '\0')
        return -1;

    iCount = iN;
    iM = iN - 1;
    iN = 0;

    while( iN < iCount)
    {
        // digit[n] is value of hex digit at position n (m << 2) is the 
        // number of positions to shift OR the bits into return value
        intValue = intValue | (iDigit[iN] << (iM << 2));
        iM--;         // adjust the position to set
        iN++;         // next digit to process
    }

    return intValue;
}

/**
 * HTTPTransport::processHTTPHeader() Is a public method used to
 * parse the HTTP header of the response message.
 */
void HTTPTransport::
processHTTPHeader()
{
    logEntryTransport("HTTPTransport::processHTTPHeader")

    // Prior to calling this method, m_strResponseHTTPHeaders should have been 
    // set to the HTTP header in the response, which is in ascii.  For EBCDIC 
    // systems, we need to convert the data from ASCII to EBCDIC.
    // WARNING: Response header processing within here should not be moved 
    //          unless you search for the right string - ascii or ebcdic. 
    //          Since we convert everything to EBCDIC, we can use literal 
    //          strings such as "\r\n" instead of ascii equivalent "\x0d\x0a". 
    PLATFORM_ASCTOSTR(m_strResponseHTTPHeaders.c_str());

    // The first line of a Response message is the Status-Line:
    // 
    //    Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
    // 
    // Parse it to get status code and reason-phrase.
    
    string::size_type iPosition = std::string::npos;
    string::size_type iStartPosition = iPosition;
    
    if( (iPosition = m_strResponseHTTPHeaders.find( "HTTP" )) == std::string::npos)
    {
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE", "Protocol is not HTTP.")

        throw HTTPTransportException( SERVER_TRANSPORT_UNKNOWN_HTTP_RESPONSE,
                                      "Protocol is not HTTP.");
    }
    
    m_strResponseHTTPProtocol = m_strResponseHTTPHeaders.substr( iPosition, strlen("HTTP/1.x"));
    iPosition += strlen("HTTP/1.x");

    while( m_strResponseHTTPHeaders[iPosition] == ' ')
        iPosition++;

    iStartPosition = iPosition;

    while( m_strResponseHTTPHeaders[iPosition] != ' ' )
        iPosition++;

    std::string strResponseHTTPStatusCode =  m_strResponseHTTPHeaders.substr( iStartPosition,iPosition - iStartPosition);
    m_iResponseHTTPStatusCode = atoi(strResponseHTTPStatusCode.c_str());

    iStartPosition = ++iPosition;
    iPosition = m_strResponseHTTPHeaders.find( "\n" );
    m_strResponseHTTPStatusMessage = m_strResponseHTTPHeaders.substr( iStartPosition,iPosition - iStartPosition - 1);

    // reached the end of the first line
    iStartPosition = m_strResponseHTTPHeaders.find( "\n" );
    iStartPosition++;

    // Now read the header fields and add to vector.
    do
    {
        // Remove consumed line from header string.
        m_strResponseHTTPHeaders = m_strResponseHTTPHeaders.substr( iStartPosition);
        
        // now find end of line...if we do not find one, break out.
        iPosition = m_strResponseHTTPHeaders.find( "\n" );
        if( iPosition == std::string::npos)
            break;
        iStartPosition = iPosition + 1;
        
        // store line in work buffer and find seperator ":", if no seperator, 
        // continue on with next line.
        std::string strHeaderLine = m_strResponseHTTPHeaders.substr(0, iPosition);
        
        string::size_type iSeperator = strHeaderLine.find( ":" ); 
        if( iSeperator == std::string::npos)
            continue;

        // Store as key-value pairs 
        string key   = strHeaderLine.substr( 0, iSeperator);
        string value = strHeaderLine.substr( iSeperator + 1, strHeaderLine.length() - iSeperator - 2);
        m_vResponseHTTPHeaders.push_back( std::make_pair( key, value));

        // Content length set? Chunked overrides Content-length. It should be noted
        // that on successful one-way requests Content-Length would be set to zero.
        if (key == "Content-Length")
            if (m_GetBytesState != eSOAPMessageIsChunked)
            {
                m_iContentLength = atoi(value.c_str());
                m_GetBytesState = eSOAPMessageHasContentLength;
            }
            
        // Is chunked? 
        if (key == "Transfer-Encoding" && value == " chunked")
            m_GetBytesState = eSOAPMessageIsChunked;

        // Now handle whether we are going to close connection after processing 
        // request. If HTTP/1.0 we have to always close the connection by default; otherwise,
        // we assume persistant connection by default.
        if( m_eProtocolType == APTHTTP1_0)
            m_bReopenConnection = true;

        // We need to close the connection and open a new one if we have 'Connection: close'
        if( key == "Connection" && (value == " close" || value == " Close"))
        {
            m_bReopenConnection = true;
            m_pActiveChannel->closeQuietly( true);
        }

        // We need to close the connection and open a new one if we have 'Proxy-Connection: close'
        if (key == "Proxy-Connection" && (value == " close" || value == " Close"))
            m_bReopenConnection = true;

        // For both HTTP/1.0 and HTTP/1.1, We need to keep the connection if we have 'Connection: Keep-Alive'
        if( key == "Connection" && value == " Keep-Alive")
            m_bReopenConnection = false;

        // Look for cookies
        if( m_bMaintainSession )
            if( key == "Set-Cookie")
                addCookie(value);

        /* If Content-Type: Multipart/Related; boundary=<MIME_boundary>; type=text/xml; start="<content id>" */
        if( key == "Content-Type")
        {
            m_strContentType = value;

            string::size_type   ulMimePos = m_strContentType.find( ";");
            std::string      strTypePart;

            if( ulMimePos != std::string::npos)
                strTypePart = m_strContentType.substr( 1, ulMimePos - 1);

            if( "Multipart/Related" == strTypePart)
            {
                m_bMimeTrue = true;
                m_strContentType = m_strContentType.substr( ulMimePos + 1, m_strContentType.length());

                ulMimePos = m_strContentType.find( "boundary=");
                m_strMimeBoundary = m_strContentType.substr( ulMimePos);
                ulMimePos = m_strMimeBoundary.find( ";");
                m_strMimeBoundary = m_strMimeBoundary.substr( 9, ulMimePos - 9);

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
    }
    while( iPosition != std::string::npos);
    
    // If 100 Continue is the response header, then we need to ensure we are waiting for 
    // an HTTP header.  Otherwise, HTTP protocol allows body with no Content-Length 
    // and no transfer-encoding! This means that we read from the stream until we are unable 
    // to read anymore. So ensure state is set correctly. In this case we set it to not-chunked.
    if (m_iResponseHTTPStatusCode == 100)
        m_GetBytesState = eWaitingForHTTPHeader;
    else if (m_GetBytesState == eWaitingForHTTPHeader)
        m_GetBytesState = eSOAPMessageIsNotChunked;
    
    logExit()
}

/* HTTPTransport::processRootMimeBody() Is a public method used to
 * parse the mime attachments.
 */
void HTTPTransport::
processRootMimeBody()
{
    logEntryTransport("HTTPTransport::processRootMimeBody")

    int numberOfBytesRead = 0;
    
    if( false == m_bReadPastRootMimeHeader)
    {
        do
        {
            if( m_strReceived.find( ASCII_S_CRLFCRLF ) == std::string::npos)
            {
                numberOfBytesRead = m_pActiveChannel->readBytes(m_pszRxBuffer, BUF_SIZE);
                if (numberOfBytesRead > 0)
                    m_strReceived += m_pszRxBuffer;
            }
        }
        while( m_strReceived.find( ASCII_S_CRLFCRLF ) == std::string::npos);

        //now we have found the end of root mime header
        m_bReadPastRootMimeHeader = true;

        //processMimeHeader(); For the time being we don't process this Done with root mime body headers, get rest of
        // the payload which contain the soap message
        m_strReceived = m_strReceived.substr( m_strReceived.find( ASCII_S_CRLFCRLF ) + 4);

        string::size_type intMimeTemp = m_strReceived.find( m_strMimeBoundary);

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
        string::size_type intMimeTemp = m_strReceived.find( m_strMimeBoundary);

        if( intMimeTemp != std::string::npos)
        {
            m_strReceived = m_strReceived.substr( 0, intMimeTemp);
            m_strMimeReceived = m_strReceived.substr( intMimeTemp);
            PLATFORM_ASCTOSTR(m_strMimeReceived.c_str());

            // Using m_strMimeReceived will be continued when getAttachment is called.
            m_bMimeTrue = false;
        }
    }
    
    logExit()
}

/* HTTPTransport::processMimeHeaders() Is a public method used to
 * parse the Mime headers of the response message.
 */
void HTTPTransport::
processMimeHeader()
{
    logEntryTransport("HTTPTransport::processMimeHeader")

    string::size_type pos = 0;
    string::size_type temppos = 0;

    // Look for content lenght
    if( (pos = m_strMimeReceived.find( "Content-Type: ")) != std::string::npos)
    {
        m_strMimeContentType = m_strMimeReceived.substr( pos + strlen( "Content-Type: "),
                                                         m_strMimeReceived.find( "\n", pos));
        pos = m_strMimeContentType.find( ";");
        temppos = m_strMimeContentType.find( "\r\n");

        if( pos < temppos)
            m_strMimeContentType = m_strMimeContentType.substr( 0, pos);
        else
            m_strMimeContentType = m_strMimeContentType.substr( 0, temppos);
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
    
    logExit()
}

void HTTPTransport::
processMimeBody ()
{
}

void HTTPTransport::
getAttachment( char * pStrAttachment, int * pIntSize, int intAttachmentId)
{
    logEntryTransport("HTTPTransport::getAttachment")

    int numberOfBytesRead = 0;
    
    do
    {
        numberOfBytesRead = m_pActiveChannel->readBytes(m_pszRxBuffer, BUF_SIZE);
        if (numberOfBytesRead > 0)
            m_strMimeReceived += m_pszRxBuffer;
    }
    while( m_strMimeReceived.find( "\r\n\r\n") == std::string::npos );

    //now we have found the end of next mime header
    processMimeHeader();

    m_strMimeReceived = m_strMimeReceived.substr( m_strMimeReceived.find( "\r\n\r\n"));
    processMimeBody();
    
    logExit()
}

void HTTPTransport::
setSocket( unsigned int uiNewSocket)
{
    m_pActiveChannel->setSocket( uiNewSocket);
}

const char * HTTPTransport::
getTransportProperty( const char * pcKey, bool response) throw (HTTPTransportException)
{
    logEntryTransport("HTTPTransport::getTransportProperty")
    
    const char *returnValue = NULL;

    std::string strKeyToFind = std::string( pcKey);
    std::vector < std::pair < std::string, std::string > > *hdrs=NULL;
    
    if (response)
        hdrs = &m_vResponseHTTPHeaders;
    else
        hdrs = &m_vHTTPHeaders;

    for( unsigned int i = 0; i < hdrs->size(); i++)
        if( (*hdrs)[i].first == strKeyToFind)
        {
            returnValue = (*hdrs)[i].second.c_str();
            break;
        }

    logExitWithString(returnValue)

    return returnValue;
}

const char * HTTPTransport::
getFirstTransportPropertyKey(bool response)
{
    if(response)
    {
        m_viCurrentResponseHeader = m_vResponseHTTPHeaders.begin ();

        if( m_viCurrentResponseHeader == m_vResponseHTTPHeaders.end())
            return NULL;
        else
            return (*m_viCurrentResponseHeader).first.c_str();
    }
    else
    {
        m_viCurrentHeader = m_vHTTPHeaders.begin ();

        if( m_viCurrentHeader == m_vHTTPHeaders.end())
            return NULL;
        else
            return (*m_viCurrentHeader).first.c_str();
    }
}

const char * HTTPTransport::
getNextTransportPropertyKey(bool response)
{
    if(response)
    {
        //already at the end?
        if( m_viCurrentResponseHeader == m_vResponseHTTPHeaders.end())
            return NULL;

        m_viCurrentResponseHeader++;

        if( m_viCurrentResponseHeader == m_vResponseHTTPHeaders.end())
            return NULL;
        else
            return (*m_viCurrentResponseHeader).first.c_str();
    }
    else
    {

        //already at the end?
        if( m_viCurrentHeader == m_vResponseHTTPHeaders.end())
            return NULL;

        m_viCurrentHeader++;

        if( m_viCurrentHeader == m_vHTTPHeaders.end())
            return NULL;
        else
            return (*m_viCurrentHeader).first.c_str();
    }
}

const char * HTTPTransport::
getCurrentTransportPropertyKey(bool response)
{
    if (response)
    {
        if( m_viCurrentResponseHeader == m_vResponseHTTPHeaders.end())
            return NULL;
        else
            return (*m_viCurrentResponseHeader).first.c_str();
    }
    else if( m_viCurrentHeader == m_vHTTPHeaders.end())
        return NULL;
    else
        return (*m_viCurrentHeader).first.c_str();
}

const char * HTTPTransport::
getCurrentTransportPropertyValue(bool response)
{
    if(response)
    {
        if( m_viCurrentResponseHeader == m_vResponseHTTPHeaders.end())
            return NULL;
        else
            return (*m_viCurrentResponseHeader).second.c_str();
    }
    else if( m_viCurrentHeader == m_vHTTPHeaders.end())
        return NULL;
    else
        return (*m_viCurrentHeader).second.c_str();
}

void HTTPTransport::
deleteCurrentTransportProperty(bool response)
{
    // response=true by default
    std::vector < std::pair < std::string, std::string > >* headers = &m_vResponseHTTPHeaders;
    vector <std::pair < std::string, std::string > >::iterator* currentHeader = &m_viCurrentResponseHeader;
    if(!response)
    {
        headers = &m_vHTTPHeaders;
        currentHeader = &m_viCurrentHeader;
    }
    
    if( *currentHeader != headers->end())
       headers->erase( *currentHeader);
}

void HTTPTransport::
deleteTransportProperty (char *pcKey, unsigned int uiOccurance)
{
    vector < std::pair < std::string,
    std::string > >::iterator currentHeader = m_vHTTPHeaders.begin();
    unsigned int uiCount = 1;
    bool found=false;
    while( currentHeader != m_vHTTPHeaders.end() && uiCount <= uiOccurance)
    {
        if( strcmp( pcKey, (*currentHeader).first.c_str()) == 0)
        {
            if( uiCount == uiOccurance)
            {
                m_vHTTPHeaders.erase( currentHeader);
                // if this is the special case of cookies then delete them all
                if(strcmp(pcKey, "Cookie")==0)
                    removeAllCookies();
                found=true;
                break;
            }

            uiCount++;
        }

        currentHeader++;
    }
    
    // if the property has not been found then it might be a cookie
    if(!found)
        removeCookie(pcKey);
}

void HTTPTransport::
setMaintainSession( bool bSession)
{
    m_bMaintainSession = bSession;
}

void HTTPTransport::
setSessionId( const char * pcSessionId)
{
    m_strSessionKey = std::string (pcSessionId);
}

const char * HTTPTransport::
getSessionId()
{
    return m_strSessionKey.c_str();
}

const char * HTTPTransport::
getLastChannelError()
{
    if( m_pActiveChannel != NULL)
        return m_pActiveChannel->GetLastErrorMsg().c_str();

    return NULL;
}

void HTTPTransport::
readHTTPHeader()
{    
    logEntryTransport("HTTPTransport::readHTTPHeader")

    m_pActiveChannel->closeQuietly( false);
    
    // The parser is expecting a SOAP message.  Thus, the HTTP header must have
    // been read and processed before control is returned to the parser.  It can
    // not be assumed that the HTTP header will be read in one block, thus there
    // must be processing that first identifies the beginning of the HTTP header
    // block (i.e. looks for 'HTTP') and then additional processing that identifies
    // the end of the HTTP header block (i.e. looks for CR LF CR LF).  
    // Note that for HTTP 100 responses, we consume it and restart the process.
    int numberOfBytesRead;
    string::size_type iHTTPStart;
    string::size_type iHTTPEnd; 
       
    resetInputStateMachine();
    
    do
    {
        while (m_strReceived.find( ASCII_S_HTTP) == std::string::npos 
                || m_strReceived.find( ASCII_S_CRLFCRLF) == std::string::npos)
        {
            numberOfBytesRead = m_pActiveChannel->readBytes(m_pszRxBuffer, BUF_SIZE);
    
            if (numberOfBytesRead > 0)
            {
                m_strReceived += m_pszRxBuffer;
                m_iBytesLeft   = m_strReceived.length();
            }
            else
            {
                m_bReopenConnection = true;
                
                logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_INPUT_STREAMING_ERROR", 
                                           "Socket connection has been closed.")

                throw HTTPTransportException( SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
                                              "Socket connection has been closed.");
            }
        }
    
        // At this point the HTTP header has been found. Seperate the response headers
        // from the payload (i.e. SOAP message). 
        iHTTPStart  = m_strReceived.find( ASCII_S_HTTP);
        iHTTPEnd    = m_strReceived.find( ASCII_S_CRLFCRLF, iHTTPStart);
    
        m_strResponseHTTPHeaders = m_strReceived.substr( iHTTPStart, iHTTPEnd + 4 - iHTTPStart); 
                
        // Process the HTTP header
        processHTTPHeader();
        
        // Remove the HTTP header from the buffer since it has been processed.
        m_strReceived = m_strReceived.substr( iHTTPEnd + 4);
        m_iBytesLeft  = m_strReceived.length(); 
    }
    while( m_iResponseHTTPStatusCode == 100); 
    
    // Now have a valid HTTP header that is not 100. Throw an exception if some unexpected error.
    // Note that error 500 are for for SOAP faults.
    if ( m_iResponseHTTPStatusCode != 500 
            && (m_iResponseHTTPStatusCode < 200 || m_iResponseHTTPStatusCode >= 300))
    {
        m_strResponseHTTPStatusMessage = std::string( "Server sent HTTP error: '") +
          m_strResponseHTTPStatusMessage +  std::string("'\n");

        m_GetBytesState = eWaitingForHTTPHeader;
        
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_HTTP_EXCEPTION", 
                                  m_strResponseHTTPStatusMessage.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_HTTP_EXCEPTION, m_strResponseHTTPStatusMessage.c_str());
    }  
    
    logExit()
}

int HTTPTransport::
getNextDataPacket( const char * pcszExceptionMessage, char *bufferToUse, int *bufferLen)
{
    logEntryTransport("HTTPTransport::getNextDataPacket")

    int numberOfBytesRead;

    // Read whatever part of the response message that has arrived at the active channel socket.
    // The buffer used is dependent on whether one is passed in.  There is an internal buffer
    // associated with the class, m_pszRxBuffer, that will be used if one is not passed in.
    // Currently we do not pass buffers into this routine, but in the future we will as an 
    // optimization step...since if we are reading non-protocol data, we should just 
    // directly plop the data into parser buffer.
    if (bufferToUse && bufferLen)
        numberOfBytesRead = m_pActiveChannel->readBytes(bufferToUse, *bufferLen);
    else
        numberOfBytesRead = m_pActiveChannel->readBytes(m_pszRxBuffer, BUF_SIZE);

    if( numberOfBytesRead > 0)
    {
        if (bufferToUse && bufferLen)
            *bufferLen = numberOfBytesRead;
        else
        {
            m_strReceived += m_pszRxBuffer;
            m_iBytesLeft = m_strReceived.length();
        }
    }
    else if( m_strReceived.length() == 0)
    {
        m_bReopenConnection = true;

        if( pcszExceptionMessage != NULL && strlen( pcszExceptionMessage) > 0)
        {
            logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_HTTP_EXCEPTION", 
                                      pcszExceptionMessage)

            throw HTTPTransportException( SERVER_TRANSPORT_HTTP_EXCEPTION, pcszExceptionMessage);
        }
    }

    logExitWithInteger(numberOfBytesRead)
    
    return numberOfBytesRead;
}

int HTTPTransport::
addCookie(const string name, const string value)
{
    logEntryTransport("HTTPTransport::addCookie")

    // trim the name
    string theName(name);
    trim(theName);
    // Make sure that the cookie is not duplicated. This cookie might be replacing one that's already there
    bool b_keyFound=false;
    for (unsigned int i = 0; i < m_vCookies.size(); i++)
    {
        if (m_vCookies[i].first == theName)
        {
            m_vCookies[i].second = (string) value;
            b_keyFound = true;

            break;
        }
    }

    // if cookie has not already been found add it
    if(!b_keyFound)
        m_vCookies.push_back( std::make_pair( theName, value));
    
    logExit()
    
    return true;
}

int HTTPTransport::
addCookie(const string nameValuePair)
{
    logEntryTransport("HTTPTransport::addCookie")

    // Spec syntax : Set-Cookie: NAME=VALUE; expires=DATE; path=PATH; domain=DOMAIN_NAME; secure
    // This code assumes it to be : Set-Cookie: NAME=VALUE; Anything_else
    // And discards stuff after first ';'
    // This is the same assumption used in Axis Java

    string::size_type ulKeyEndsAt = nameValuePair.find( ";");

    string nameValue;
    if( ulKeyEndsAt != std::string::npos)
        nameValue = nameValuePair.substr( 0, ulKeyEndsAt);

    // Now split the nameValue up
    string::size_type nameEndsAt = nameValue.find("=");
    
    logExit()
    
    return addCookie(nameValue.substr(0, nameEndsAt), nameValue.substr(nameEndsAt+1));
}

int HTTPTransport::
removeCookie(const string name)
{
     vector < std::pair < std::string,
     std::string > >::iterator currentCookie = m_vCookies.begin();

    while( currentCookie != m_vCookies.end())
    {
        if( strcmp( name.c_str(), (*currentCookie).first.c_str()) == 0)
        {
            m_vCookies.erase( currentCookie);
            return AXIS_SUCCESS;
        }
        currentCookie++;
    }
    
    return AXIS_FAIL;
}

int HTTPTransport::
removeAllCookies()
{
    m_vCookies.clear();
    // we also need to remove it from the header properties that we send.
    // This is done from the deleteTransportMethod before this one is called.
    return AXIS_SUCCESS;
}

void HTTPTransport::
trim(string& str)
{
    string::size_type pos = str.find_last_not_of(' ');
    if(pos != string::npos) 
    {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if(pos != string::npos) 
            str.erase(0, pos);
    }
    else 
        str.erase(str.begin(), str.end());
}

void HTTPTransport::
enableTrace(const char* logFilePath, const char *filters)
{
    AxisTrace::setLogFilter(filters);
    AxisTrace::startTrace(logFilePath, false);
    
    if (m_pNormalChannel)
        m_pNormalChannel->enableTrace(logFilePath, filters);
    
    if (m_pSecureChannel)
        m_pSecureChannel->enableTrace(logFilePath, filters);
}