// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// !!! Must be first thing in file !!!
#include "../../../platforms/PlatformAutoSense.hpp"

#include <ctype.h>

#include "HTTPChannel.hpp"

#include "../../../common/AxisTrace.h"

/**
 * HTTPChannel::HTTPChannel()
 *
 * HTTPChannel constuctor
 */

HTTPChannel::
HTTPChannel()
{
    logEntryTransport("HTTPChannel::HTTPChannel")

    m_LastError = "No Errors";

    m_Sock = INVALID_SOCKET;

    m_bUseProxy = false;
    m_strProxyHost = "";
    m_uiProxyPort = 0;

#ifdef WIN32
    m_lTimeoutSeconds = 10;
#else
    m_lTimeoutSeconds = 0;
#endif
    m_lConnectTimeoutSeconds = 0;
    
    bNoExceptionOnForceClose = false;

    if( !StartSockets())
    {
        logThrowException("HTTPTransportException - SERVER_TRANSPORT_CHANNEL_INIT_ERROR")

        throw HTTPTransportException( SERVER_TRANSPORT_CHANNEL_INIT_ERROR);
    }
    
    logExit()
}

/**
 * HTTPChannel::~HTTPChannel()
 *
 * HTTPChannel destuctor
 *
 */

HTTPChannel::
~HTTPChannel()
{
    logEntryTransport("HTTPChannel::~HTTPChannel")

    CloseChannel();
    StopSockets();
    
    logExit()
}

/**
 * HTTPChannel::getURL()
 *
 * Return the URL currently assicated with the channel object.
 *
 * @return char * containing the URL associated with the open socket
 */

const char * HTTPChannel::
getURL()
{
    return m_URL.getURL();
}

/**
 * HTTPChannel::setURL( const char * cpURL)
 *
 * Set the Channel URL to the new value.
 *
 * @param const char * containing the new URL
 */

void HTTPChannel::
setURL( const char * cpURL)
{
    logEntryTransport("HTTPChannel::setURL")

    m_URL.setURL( cpURL);
    
    logExit()
}

/**
 * HTTPChannel::getURLObject()
 *
 * Return the current URL object
 *
 * @return URL & current URL object
 */

URL & HTTPChannel::
getURLObject()
{
    return m_URL;
}

/**
 * HTTPChannel::open()
 *
 * Main method for opening a HTTP channel.  If a channel is already open, it is
 * closed before attempting to open a new channel.  If the method fails to open
 * a new channel then an exception will be thrown.
 *
 * @return boolean flag set to AXIS_FAIL or AXIS_SUCCESS depending on outcome
 * of opening a channel (Since an exception is always thrown on failure, the
 * returned flag will only be returned on a successful outcome).
 */

bool HTTPChannel::
open()
{
    logEntryTransport("HTTPChannel::open")

    CloseChannel();

    m_LastError = "No Errors";

    OpenChannel();

    logExit()
    
    return AXIS_SUCCESS;
}

/**
 * HTTPChannel::close()
 *
 * Main method for closing a HTTP channel.
 *
 * @return boolean flag set to AXIS_FAIL or AXIS_SUCCESS depending on outcome
 * of closing the channel.
 */

bool HTTPChannel::
close()
{
    logEntryTransport("HTTPChannel::close")

    CloseChannel();
    
    logExit()
    
    return AXIS_SUCCESS;
}

/**
 * HTTPChannel::GetLastErrorMsg()
 *
 * Returns the last reported error on the channel.
 *
 * @return string containing last error.
 */

const std::string & HTTPChannel::
GetLastErrorMsg()
{
    return m_LastError;
}

/**
 * HTTPChannel::readBytes()
 *
 * This method attempts to read a message from the currently open channel.  If
 * there is no currently open channel, then the method throws an exception.  If
 * there is an open channel, but nothing to receive, then then method will
 * timeout and throw an exception.  If the message is interrupted or the
 * transmitting side closes then an exception is thrown.
 *
 * @param character pointer containing an array of character that can be filled
 * by the received message (NB: The maximum message length is BUF_SIZE).
 * @return character pointer pointing to the array of character containing the
 * received message.
 */

int HTTPChannel::
readBytes(char *buf, int bufLen)
{
    logEntryTransport("HTTPChannel::readBytes")

    if (INVALID_SOCKET == m_Sock)
    {
        m_LastError = "Unable to perform read operation.";
        
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_INVALID_SOCKET", m_LastError.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_INVALID_SOCKET, m_LastError.c_str());
    }

    int     nByteRecv = 0;
    int     iBufSize = bufLen - 10;

    // If timeout set then wait for maximum amount of time for data
    if( m_lTimeoutSeconds > 0)
    {
        int iTimeoutStatus = applyTimeout(m_lTimeoutSeconds, true);

        // Handle timeout outcome
        if( iTimeoutStatus < 0)
        {
            logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_TIMEOUT_EXCEPTION", m_LastError.c_str())

            throw HTTPTransportException( SERVER_TRANSPORT_TIMEOUT_EXCEPTION, m_LastError.c_str());
        }
    
        if( iTimeoutStatus == 0)
        {
            m_LastError = "Read operation timed-out while waiting for data.";
            
            logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_TIMEOUT_EXPIRED", m_LastError.c_str())

            throw HTTPTransportException( SERVER_TRANSPORT_TIMEOUT_EXPIRED, m_LastError.c_str() );
        }
    }

    // Either timeout was not set or data available before timeout; so read
    nByteRecv = recv( m_Sock, buf, iBufSize, 0);
    if (nByteRecv == SOCKET_ERROR)
    {
        // error on read operation
        ReportError();
        CloseChannel();

        if( !bNoExceptionOnForceClose)
        {
            logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_INPUT_STREAMING_ERROR", m_LastError.c_str())

            throw HTTPTransportException( SERVER_TRANSPORT_INPUT_STREAMING_ERROR, m_LastError.c_str());
        }
    }
    else if ( 0 == nByteRecv )
    {
        logDebug("Read-side of socket has been closed.")

        // read-side of socket is closed.
    }
    else if( nByteRecv)
        buf[nByteRecv] = '\0';

    logDebugBuffer(buf, nByteRecv)

    logExitWithInteger(nByteRecv)

    return nByteRecv;
}

/**
 * HTTPChannel::writeBytes()
 *
 * This method attempts to write a message to the curently open channel.  If
 * there is no currently open channel, then the method throws an exception.  If
 * there is an open channel, but the mesage is interrupted or the recieving
 * side closes then an exception is thrown.
 *
 * @param character pointer pointing to the array of character containing the
 * message to be transmitted.
 */
int HTTPChannel::
writeBytes(const char *buf, int numBytes)
{
    logEntryTransport("HTTPChannel::writeBytes")

    logDebugBuffer(buf, numBytes)

    if( INVALID_SOCKET == m_Sock)
    {
        m_LastError = "No valid socket to perform write operation.";
        
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_INVALID_SOCKET", m_LastError.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_INVALID_SOCKET, m_LastError.c_str());
    }

    int nByteSent;

#ifdef __OS400__
    if( (nByteSent = send( m_Sock, (char *)buf, numBytes, 0)) == SOCKET_ERROR)
#else
    if( (nByteSent = send( m_Sock, buf, numBytes, 0)) == SOCKET_ERROR)
#endif
    {
        // This must be done first before closing channel in order to get actual error.
        ReportError(); 
               
        // Close the channel and throw an exception.
        CloseChannel();

        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR", m_LastError.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR, m_LastError.c_str());
    }

    logExitWithInteger(nByteSent)

    return nByteSent;
}

/**
 * HTTPChannel::setTimeout( const long lSeconds)
 *
 * Set the Rx message timeout (in seconds)
 *
 * @param long containing timeout value in seconds
 */

void HTTPChannel::
setTimeout( long lSeconds)
{
    logEntryTransport("HTTPChannel::setTimeout")

    m_lTimeoutSeconds = lSeconds;
    
    logExit()
}

/**
 * HTTPChannel::setConnectTimeout( const long lSeconds)
 *
 * Set the connect timeout (in seconds)
 *
 * @param long containing timeout value in seconds
 */

void HTTPChannel::
setConnectTimeout( long lSeconds)
{
    logEntryTransport("HTTPChannel::setConnectTimeout")

    m_lConnectTimeoutSeconds = lSeconds;
    
    logExit()
}

/**
 * HTTPChannel::setSocket( unsigned int uiNewSocket)
 *
 * This is used by the server side to change the server socket.
 *
 * @param unsigned int containing the new server socket.
 */

void HTTPChannel::
setSocket( unsigned int uiNewSocket)
{
    m_Sock = uiNewSocket;
}

/**
 * HTTPChannel::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type,
 *                                    const char * value)
 *
 * The following list can be set using this property:-
 * SOAPACTION_HEADER            - No action
 * SERVICE_URI                  - No action
 * OPERATION_NAME               - No action
 * SOAP_MESSAGE_LENGTH          - No action
 * TRANSPORT_PROPERTIES         - No action
 * SECURE_PROPERTIES            - No action
 * DLL_NAME                     - No action
 * CHANNEL_HTTP_SSL_DLL_NAME    - No action
 * CHANNEL_HTTP_DLL_NAME        - No action
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE contains the type of property to be
 *        set.
 *        const char * contains the value for the type to be set to.
 * @return boolean flag indicating success of the alteration. 
 */

bool HTTPChannel::
setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char * value)
{
    bool    bSuccess = false;

    return bSuccess;
}

/**
 * HTTPChannel::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
 *
 * The following list can be retrieved using this property:-
 * SOAPACTION_HEADER            - No action
 * SERVICE_URI                  - No action
 * OPERATION_NAME               - No action
 * SOAP_MESSAGE_LENGTH          - No action
 * TRANSPORT_PROPERTIES         - No action
 * SECURE_PROPERTIES            - No action
 * DLL_NAME                     - No action
 * CHANNEL_HTTP_SSL_DLL_NAME    - No action
 * CHANNEL_HTTP_DLL_NAME        - No action
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE contains the type of property to be
 *        recovered.
 * @return const char * contains the value for the requested type.
 */

const char * HTTPChannel::
getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
{
    return NULL;
}

/**
 * HTTPChannel::setProxy( const char * pcProxyHost, unsigned int uiProxyPort)
 *
 * Setup he proxy values to be used by the channel.
 *
 * @param const char * containing the name of the proxy host.
 *        unsigned int containing the proxy port value.
 */

void HTTPChannel::
setProxy( const char * pcProxyHost, unsigned int uiProxyPort)
{
    logEntryTransport("HTTPChannel::setProxy")

    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;
    
    logExit()
}

// +--------------------------------------------------------------------------+
// | Protected methods                                                        |
// | -----------------                                                        |
// +--------------------------------------------------------------------------+

/**
 * HTTPChannel::OpenChannel()
 *
 * Protected function
 *
 * @param
 * @return 
 */

bool HTTPChannel::
OpenChannel()
{
    logEntryTransport("HTTPChannel::OpenChannel")

    int     rc = 0;

#ifdef IPV6
    struct addrinfo     aiHints;
    struct addrinfo *   paiAddrInfo;
    struct addrinfo *   paiAddrInfo0;

    // hints is used after zero cleared
    memset( &aiHints, 0, sizeof( aiHints));

    aiHints.ai_family = PF_UNSPEC;      // This allows the sockets code to use
                                        // whatever socket family is available.
    aiHints.ai_socktype = SOCK_STREAM;

    char szPort[7];
   
    const char  *   pszHost = m_URL.getHostName();
    unsigned int    uiPort = m_URL.getPort();

    if( m_bUseProxy)
    {
        uiPort = m_uiProxyPort;
        pszHost = m_strProxyHost.c_str();
    }
 
    sprintf( szPort, "%u", uiPort);

    if( getaddrinfo( pszHost, szPort, &aiHints, &paiAddrInfo0))
    {
        m_LastError = "Unable to get address information.";
        
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_SOCKET_CREATE_ERROR", m_LastError.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR, m_LastError.c_str());
    }

    for( paiAddrInfo = paiAddrInfo0; paiAddrInfo; paiAddrInfo = paiAddrInfo->ai_next)
    {
        m_Sock = socket( paiAddrInfo->ai_family,
                         paiAddrInfo->ai_socktype,
                         paiAddrInfo->ai_protocol);

        if( m_Sock < 0)
            continue;

        if( connect( m_Sock, paiAddrInfo->ai_addr, paiAddrInfo->ai_addrlen) < 0)
        {
            // This must be done first thing to get proper error. Generate full message.
            ReportError(true);
            CloseChannel();

            freeaddrinfo( paiAddrInfo0);

            logThrowExceptionWithData("HTTPTransportException - CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED", m_LastError.c_str())

            throw HTTPTransportException( CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED, m_LastError.c_str());
        }

        break;
    }

    freeaddrinfo( paiAddrInfo0);

    // If couldn't create socket, close the channel and throw an exception.
    if( m_Sock < 0)
    {
        ReportError();        
        CloseChannel();
        
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_SOCKET_CREATE_ERROR", m_LastError.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR, m_LastError.c_str());
    }
    
#else // IPV6 not defined

    if( (m_Sock = socket( PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        ReportError();
        CloseChannel();
          
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_SOCKET_CREATE_ERROR", m_LastError.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR, m_LastError.c_str());
    }

    // Connect to server.
    sockaddr_in         svAddr;
    struct hostent *    pHostEntry = NULL;
    const char *        host = m_URL.getHostName();
    unsigned int        port = m_URL.getPort();

    memset(&svAddr, 0, sizeof(sockaddr_in));
    if( m_bUseProxy)
    {
        port = m_uiProxyPort;
        host = m_strProxyHost.c_str();
    }

    svAddr.sin_family = AF_INET;
    svAddr.sin_port = htons( port);

    // Host names must start with a character (RFC1035)...so if it starts with a number, let us first
    // assume it is dotted decimal format...and if it fails, we will then assume it is a host name.
    // We do this so that we avoid long DNS timeouts if we use gethostbyname() first.
    svAddr.sin_addr.s_addr = -1;
    if (isdigit(host[0]))
    {
#ifdef __OS400__
        svAddr.sin_addr.s_addr = inet_addr( (char *)host);
#else
        svAddr.sin_addr.s_addr = inet_addr( host);
#endif
    }

    if (svAddr.sin_addr.s_addr == -1)
    {
#ifdef __OS400__
        if( (pHostEntry = gethostbyname( (char *)host)))
#else
        if( (pHostEntry = gethostbyname( host)))
#endif
            svAddr.sin_addr.s_addr = ((struct in_addr *) pHostEntry->h_addr)->s_addr;
    }
        
    // If connect timeout specified do non-blocking connect.
    if (m_lConnectTimeoutSeconds > 0)
    {
       // Make socket non-blocking
       PLATFORM_SET_SOCKET_NONBLOCKING(m_Sock);

       rc = connect( m_Sock, (struct sockaddr *) &svAddr, sizeof (svAddr));
       
       if (rc == SOCKET_ERROR && GETLASTERROR == EINPROGRESS)
       { 
            int iTimeoutStatus = applyTimeout(m_lConnectTimeoutSeconds, false);

            // Set to blocking mode again... 
            PLATFORM_SET_SOCKET_BLOCKING(m_Sock);
            
            // Handle timeout outcome
            if( iTimeoutStatus < 0)
            {
                CloseChannel();
            
                logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_TIMEOUT_EXCEPTION", m_LastError.c_str())

                throw HTTPTransportException( SERVER_TRANSPORT_TIMEOUT_EXCEPTION, m_LastError.c_str());
            }
            else if( iTimeoutStatus == 0)
            {
                CloseChannel();
                char buffer[100];
                sprintf(buffer, "%d", m_URL.getPort());
                m_LastError = 
                  "Failed to open connection to server at host " +
                   string(m_URL.getHostName()) + " and port " +  string(buffer) + ".\nConnect operation timed-out.";
        
                logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_TIMEOUT_EXPIRED", m_LastError.c_str())

                throw HTTPTransportException( SERVER_TRANSPORT_TIMEOUT_EXPIRED, m_LastError.c_str() );
            }
            else
            {
                // Otherwise, the socket either connected or there is an error.  If there is an error, we will
                // get the error when we write to the socket so assume everything is OK.
            
                rc = 0;
            }
       }
       else if (rc == SOCKET_ERROR)
       {
            // This must be done first thing to get proper error. Generate full message.
            ReportError(true);
            PLATFORM_SET_SOCKET_BLOCKING(m_Sock);
            CloseChannel();
       }
       else
       {
            // Connected...
            // Set to blocking mode again... 
            PLATFORM_SET_SOCKET_BLOCKING(m_Sock);
       }
    }
    else
    {
        rc = connect( m_Sock, (struct sockaddr *) &svAddr, sizeof (svAddr));

        // This must be done first thing to get proper error. Generate full message.
        if (rc  == SOCKET_ERROR)
        {
            ReportError(true);  
            CloseChannel();
        }      
    }

    // If errors on connect, throw an exception.
    if (rc == SOCKET_ERROR)
    {
        logThrowExceptionWithData("HTTPTransportException - SERVER_TRANSPORT_SOCKET_CONNECT_ERROR", m_LastError.c_str())

        throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CONNECT_ERROR, m_LastError.c_str());
    }

#endif // IPV6

    /* Turn off the Nagle algorithm
     *
     * This is needed, because our TCP stack would otherwise wait at most
     * 200 ms before actually sending data to the server (while waiting for
     * a full packet). This limits performance to around 5 requests per
     * second, which is not acceptable. Turning off the Nagle algorithm
     * allows for much faster transmission of small packets, but may
     * degrade high-bandwidth transmissions.
     */

    int one = 1;
    setsockopt( m_Sock, IPPROTO_TCP, TCP_NODELAY, (char *) &one, sizeof( int));

    logExitWithBoolean(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

/**
 * HTTPChannel::CloseChannel()
 *
 * Protected function
 *
 * @param
 * @return 
 */

void HTTPChannel::
CloseChannel()
{
    logEntryTransport("HTTPChannel::CloseChannel")

    if( INVALID_SOCKET != m_Sock)
    {
#ifdef WIN32
        closesocket( m_Sock);
#else
        ::close( m_Sock);
#endif
        m_Sock = INVALID_SOCKET;
    }
    
    logExit()
}

/**
 * HTTPChannel::StartSockets()
 *
 * Protected function
 *
 * @param
 * @return 
 */

bool HTTPChannel::
StartSockets()
{
    bool    bSuccess = false;
#ifdef WIN32
    WSADATA wsaData;    // Contains vendor-specific information, such as the
                        // maximum number of sockets available and the maximum
                        // datagram size.

    // wsaData filled by Windows Sockets DLLs.
    if( WSAStartup( WS_VERSION_REQD, &wsaData))
    {
        // Error - Could not setup underlying Windows socket transport mechanism.
        m_LastError = "WinSock DLL not responding.";
    }
    else
    {
        // Query to see whether the available version matches what is required
        if ((LOBYTE( wsaData.wVersion) <  WS_VERSION_MAJOR()) ||
            (LOBYTE( wsaData.wVersion) == WS_VERSION_MAJOR() &&
             HIBYTE( wsaData.wVersion) <  WS_VERSION_MINOR()))
        {
            // Error - Underlying Windows socket transport version is not compatible with
            //         what is required.
            char    szErrorBuffer[100];

            sprintf( szErrorBuffer,
                     "Windows Sockets version %d.%d is not supported by winsock2.dll",
                     LOBYTE( wsaData.wVersion),
                     HIBYTE( wsaData.wVersion));

            m_LastError = szErrorBuffer;

            StopSockets();
        }
        else
        {
            bSuccess = true;
        }
    }
#else
    // Other OS specific Intitialization goes here

    bSuccess = true;
#endif

    return bSuccess;
}

/**
 * HTTPChannel::StopSockets()
 *
 * Protected function
 *
 * @param
 * @return 
 */

void HTTPChannel::
StopSockets()
{
#ifdef WIN32
    WSACleanup();
#endif // WIN32
}

/**
 * HTTPChannel::applyTimeout()
 *
 * Protected function
 *
 * @return int 
 */

int HTTPChannel::
applyTimeout(long seconds, bool isRead)
{
    logEntryTransport("HTTPChannel::applyTimeout")

    fd_set          set;
    fd_set          eset;
    struct timeval  timeout;

    // Initialize the file descriptor set.
    FD_ZERO( &set);
    FD_ZERO( &eset);
    FD_SET( m_Sock, &set);
    FD_SET( m_Sock, &eset);

    /* Initialize the timeout data structure. */
    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;

    /* select returns 0 if timeout, 1 if input available, -1 if error. */
    int rc;
    if (isRead)
        rc = select( FD_SETSIZE, &set, NULL, &eset, &timeout);
    else
        rc = select( FD_SETSIZE, NULL, &set, &eset, &timeout);
    
    if (rc < 0)
        ReportError();
        
    logExitWithInteger(rc)

    return rc;
}

void HTTPChannel::
ReportError(bool isConnectError)
{
    long dwError = GETLASTERROR;
    char pcErr[100];
    sprintf(pcErr,"Error is %d - ",(int)dwError);
    m_LastError = string(pcErr) + PLATFORM_GET_ERROR_MESSAGE(dwError);
    
    if (isConnectError)
    {
        char buffer[100];
        sprintf(buffer, "%d", m_URL.getPort());
        string fullMessage = 
                "Failed to open connection to server at host " +
                string(m_URL.getHostName()) + " and port " +  string(buffer) + ".\n" + m_LastError;            
        m_LastError = fullMessage;
    }
}

void HTTPChannel::
closeQuietly( bool bNoExceptionOnForceClose_Update)
{
    bNoExceptionOnForceClose = bNoExceptionOnForceClose_Update;
}

void HTTPChannel::
enableTrace(const char* logFilePath, const char *filters)
{
    AxisTrace::setLogFilter(filters);
    AxisTrace::startTrace(logFilePath, false);
}
