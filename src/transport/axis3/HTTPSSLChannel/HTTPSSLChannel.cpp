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

#include "HTTPSSLChannel.hpp"

/**
 * cert_verify_callback( int ok, X509_STORE_CTX * ctx)
 *
 * cert_verify_callback callback
 *
 */

static int cert_verify_callback( int ok, X509_STORE_CTX * ctx)
{
  X509 *    err_cert;
  char        buf[256];

  err_cert = X509_STORE_CTX_get_current_cert( ctx);
  X509_NAME_oneline( X509_get_subject_name( err_cert), buf, 256);

  return ok;
}

/**
 * HTTPSSLChannel::HTTPSSLChannel()
 *
 * HTTPSSLChannel constuctor
 *
 */

HTTPSSLChannel::
HTTPSSLChannel()
{
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

    bNoExceptionOnForceClose = false;

    if( !StartSockets())
    {
        throw HTTPTransportException( SERVER_TRANSPORT_CHANNEL_INIT_ERROR);
    }

    OpenSSL_Initialise();

    m_sslContext = NULL;
    m_sslHandle = NULL;
}

/**
 * HTTPSSLChannel::~HTTPSSLChannel()
 *
 * HTTPSSLChannel destuctor
 *
 */

HTTPSSLChannel::
~HTTPSSLChannel()
{
    CloseChannel();
    StopSockets();
}

/**
 * HTTPSSLChannel::getURL()
 *
 * Return the URL currently assicated with the channel object.
 *
 * @return char * containing the URL associated with the open socket
 */

const char * HTTPSSLChannel::
getURL()
{
    return m_URL.getURL();
}

/**
 * HTTPSSLChannel::setURL( const char * cpURL)
 *
 * Set the Channel URL to the new value.
 *
 * @param const char * containing the new URL
 */

void HTTPSSLChannel::
setURL( const char * cpURL)
{
    m_URL.setURL( cpURL);
}

/**
 * HTTPSSLChannel::getURLObject()
 *
 * Return the current URL object
 *
 * @return URL & current URL object
 */

URL & HTTPSSLChannel::
getURLObject()
{
    return m_URL;
}

/**
 * HTTPSSLChannel::open()
 *
 * Main method for opening a HTTP channel.  If a channel is already open, it is
 * closed before attempting to open a new channel.  If the method fails to open
 * a new channel then an exception will be thrown.
 *
 * @return boolean flag set to AXIS_FAIL or AXIS_SUCCESS depending on outcome
 * of opening a channel (Since an exception is always thrown on failure, the
 * returned flag will only be returned on a successful outcome).
 */

bool HTTPSSLChannel::
open() throw (HTTPTransportException&)
{
    bool    bSuccess = (bool) AXIS_FAIL;

    CloseChannel();

    m_LastError = "No Errors";

    if( (bSuccess = OpenChannel()) != AXIS_SUCCESS)
    {
        throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CONNECT_ERROR,m_LastError.c_str());
    }

    return bSuccess;
}

/**
 * HTTPSSLChannel::close()
 *
 * Main method for closing a HTTP channel.
 *
 * @return boolean flag set to AXIS_FAIL or AXIS_SUCCESS depending on outcome
 * of closing the channel.
 */

bool HTTPSSLChannel::
close()
{
    CloseChannel();
    return AXIS_SUCCESS;
}

/**
 * HTTPSSLChannel::GetLastErrorMsg()
 *
 * Returns the last reported error on the channel.
 *
 * @return string containing last error.
 */

const std::string & HTTPSSLChannel::
GetLastErrorMsg()
{
    return m_LastError;
}

/**
 * HTTPSSLChannel::operator >> (char * msg)
 *
 * This method attempts to read a message from the curently open channel.  If
 * there is no currently open channel, then the method throws an exception.  If
 * there is an open channel, but nothing to recieve, then then method will
 * timeout and throw an exception.  If the mesage is interrupted or the
 * transmitting side closes then an exception is thrown.
 *
 * @param character pointer containing an array of character that can be filled
 * by the reieved message (NB: The maximum message length is BUF_SIZE).
 * @return character pointer pointing to the array of character containing the
 * recieved message.
 */

int HTTPSSLChannel::
readBytes(char *buf, int bufLen)
{
    if (INVALID_SOCKET == m_Sock)
    {
        m_LastError = "Unable to perform read operation.";
        throw HTTPTransportException( SERVER_TRANSPORT_INVALID_SOCKET, m_LastError.c_str());
    }

    int nByteRecv = 0;

    nByteRecv = SSL_read( m_sslHandle, buf, bufLen - 1);

    if(nByteRecv < 0)
    {
        OpenSSL_SetSecureError( SSL_get_error( m_sslHandle, nByteRecv));
        CloseChannel();
        
        if( !bNoExceptionOnForceClose)
        {
           throw HTTPTransportException( SERVER_TRANSPORT_INPUT_STREAMING_ERROR, m_LastError.c_str());   
        }     
    }
    else if ( 0 == nByteRecv )
    {
        // read-side of socket is closed 
        *(buf + nByteRecv) = '\0';
    }
    else
    {
       *(buf + nByteRecv) = '\0';  
    }

    return nByteRecv;
}

/**
 * HTTPSSLChannel::operator << (const char * msg)
 *
 * This method attempts to write a message to the curently open channel.  If
 * there is no currently open channel, then the method throws an exception.  If
 * there is an open channel, but the mesage is interrupted or the recieving
 * side closes then an exception is thrown.
 *
 * @param character pointer pointing to the array of character containing the
 * message to be transmitted.
 */

int HTTPSSLChannel::
writeBytes(const char *buf, int numBytes)
{
    if( INVALID_SOCKET == m_Sock)
    {
        m_LastError = "Unable to perform write operation.";
        throw HTTPTransportException( SERVER_TRANSPORT_INVALID_SOCKET, m_LastError.c_str());
    }

    int nByteSent;

    nByteSent = SSL_write( m_sslHandle, (char *) buf, numBytes);

    if(nByteSent < 0)
    {
        OpenSSL_SetSecureError( SSL_get_error( m_sslHandle, nByteSent));
        CloseChannel();
        throw HTTPTransportException( SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR, m_LastError.c_str());
    }

    return nByteSent;
}

/**
 * HTTPSSLChannel::setTimeout( const long lSeconds)
 *
 * Set the Rx message timeout (in seconds)
 *
 * @param long containing timeout value in seconds
 */

void HTTPSSLChannel::
setTimeout( long lSeconds)
{
    m_lTimeoutSeconds = lSeconds;
}

/**
 * HTTPSSLChannel::setSocket( unsigned int uiNewSocket)
 *
 * This is used by the server side to change the server socket.
 *
 * @param unsigned int containing the new server socket.
 */

void HTTPSSLChannel::
setSocket( unsigned int uiNewSocket)
{
    m_Sock = uiNewSocket;
}

/**
 * HTTPSSLChannel::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type,
 *                                         const char * value)
 *
 * The following list can be set using this property:-
 * SOAPACTION_HEADER            - No action
 * SERVICE_URI                    - No action
 * OPERATION_NAME                - No action
 * SOAP_MESSAGE_LENGTH            - No action
 * TRANSPORT_PROPERTIES            - No action
 * SECURE_PROPERTIES            - No action
 * DLL_NAME                        - No action
 * CHANNEL_HTTP_SSL_DLL_NAME    - No action
 * CHANNEL_HTTP_DLL_NAME        - No action
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE contains the type of property to be
 *        set.
 *        const char * contains the value for the type to be set to.
 * @return boolean flag indicating success of the alteration. 
 */

bool HTTPSSLChannel::
setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
{
    bool    bSuccess = false;

    return bSuccess;
}

/**
 * HTTPSSLChannel::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
 *
 * The following list can be retrieved using this property:-
 * SOAPACTION_HEADER            - No action
 * SERVICE_URI                    - No action
 * OPERATION_NAME                - No action
 * SOAP_MESSAGE_LENGTH            - No action
 * TRANSPORT_PROPERTIES            - No action
 * SECURE_PROPERTIES            - No action
 * DLL_NAME                        - No action
 * CHANNEL_HTTP_SSL_DLL_NAME    - No action
 * CHANNEL_HTTP_DLL_NAME        - No action
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE contains the type of property to be
 *        recovered.
 * @return const char * contains the value for the requested type.
 */

const char * HTTPSSLChannel::
getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
{
    return NULL;
}

/**
 * HTTPSSLChannel::setProxy( const char * pcProxyHost, unsigned int uiProxyPort)
 *
 * Setup he proxy values to be used by the channel.
 *
 * @param const char * containing the name of the proxy host.
 *          unsigned int containing the proxy port value.
 */

void HTTPSSLChannel::
setProxy (const char *pcProxyHost, unsigned int uiProxyPort)
{
    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;
}

// +--------------------------------------------------------------------------+
// | Protected methods                                                          |
// | -----------------                                                          |
// +--------------------------------------------------------------------------+

/**
 * HTTPSSLChannel::OpenChannel()
 *
 * Protected function
 *
 * @param
 * @return 
 */

bool HTTPSSLChannel::
OpenChannel()
{
    bool    bSuccess = (bool) AXIS_FAIL;

    // Create the Client (Rx) side first.
#ifdef IPV6
    struct addrinfo        aiHints;
    struct addrinfo *    paiAddrInfo;
    struct addrinfo *    paiAddrInfo0;

    // hints is used after zero cleared
    memset( &aiHints, 0, sizeof( aiHints));

    aiHints.ai_family = PF_UNSPEC;        // This allows the sockets code to use
                                        // whatever socket family is available.
    aiHints.ai_socktype = SOCK_STREAM;

    char szPort[7];
   
    const char    *    pszHost = m_URL.getHostName();
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
            // Cannot open a channel to the remote end, shutting down the
            // channel and then throw an exception.
            // Before we do anything else get the last error message;
            long dwError = GETLASTERROR;

            CloseChannel();

            freeaddrinfo( paiAddrInfo0);

            char pcErr[64], pcPort[64];
            sprintf(pcErr,"%d - ",(int)dwError);
            sprintf(pcPort,"%d",(int)m_URL.getPort());
            
            string fullMessage = "Failed to open connection to server " + 
                   string(m_URL.getHostName()) + " at port " + string(pcPort) +
                   ".\nError " + string(pcErr) + PLATFORM_GET_ERROR_MESSAGE( dwError );

            throw HTTPTransportException( CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED, fullMessage.c_str());
        }

        break;
    }

    // Samisa: free addrInfo0 - no longer needed
    freeaddrinfo( paiAddrInfo0);

    if( m_Sock < 0)
    {
        // Sockets error Couldn't create socket.  Close the channel and throw
        // an exception.
        CloseChannel();

        throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR);
    }

    bSuccess = AXIS_SUCCESS;

#else // IPV6 not defined
    if( (m_Sock = socket( PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        m_LastError = "Could not Create a socket.";

        return bSuccess;
    }

    // If the transport was initilised, then create client and server sockets.
    sockaddr_in    clAddr;

    clAddr.sin_family = AF_INET;    // AF_INET (address family Internet).
    clAddr.sin_port = 0;            // No Specify Port required.
    clAddr.sin_addr.s_addr = INADDR_ANY;

    // Attempt to bind the client to the client socket.
    if( bind( m_Sock, (struct sockaddr *) &clAddr, sizeof( clAddr)) == SOCKET_ERROR)
    {
        CloseChannel();
        m_LastError = "Error whilst binding. Cannot open a channel to the remote end.";
        return bSuccess;
    }

    // Although the above fragment makes use of the bind() API, it would be
    // just as effective to skip over this call as there are no specific
    // local port ID requirements for this client. The only advantage that
    // bind() offers is the accessibility of the port which the system 
    // chose via the .sin_port member of the cli_addr structure which will 
    // be set upon success of the bind() call.
    
    // Create the Server (Tx) side.

    sockaddr_in            svAddr;
    struct hostent *    pHostEntry = NULL;
    const char *        host = m_URL.getHostName();
    unsigned int        port = m_URL.getPort();

    if( m_bUseProxy)
    {
        port = m_uiProxyPort;
        host = m_strProxyHost.c_str();
    }

    svAddr.sin_family = AF_INET;
    svAddr.sin_port = htons( port);

    // Probably this is the host-name of the server we are connecting to...
    if( (pHostEntry = gethostbyname( host)))
    {
        svAddr.sin_addr.s_addr = ((struct in_addr *) pHostEntry->h_addr)->s_addr;
    }
    else
    {
        // No this is the IP address
        svAddr.sin_addr.s_addr = inet_addr( host);
    }

    // Attempt to connect to the remote server.
    if( connect( m_Sock, (struct sockaddr *) &svAddr, sizeof (svAddr)) == SOCKET_ERROR)
    {
        long dwError = GETLASTERROR;
        CloseChannel();

        char pcErr[64], pcPort[64];
        sprintf(pcErr,"%d - ",(int)dwError);
        sprintf(pcPort,"%d",(int)m_URL.getPort());
        
        string fullMessage = "Failed to open connection to server " + 
               string(m_URL.getHostName()) + " at port " + string(pcPort) +
               ".\nError " + string(pcErr) + PLATFORM_GET_ERROR_MESSAGE( dwError );

        m_LastError = fullMessage;

        return bSuccess;
    }
    else
    {
        bSuccess = AXIS_SUCCESS;
    }

#endif // IPV6

    /* Turn off the Nagle algorithm - Patch by Steve Hardy */

    /* This is needed, because our TCP stack would otherwise wait at most
     * 200 ms before actually sending data to the server (while waiting for
     * a full packet). This limits performance to around 5 requests per
     * second, which is not acceptable. Turning off the Nagle algorithm
     * allows for much faster transmission of small packets, but may
     * degrade high-bandwidth transmissions.
     */

    int one = 1;

    setsockopt( m_Sock, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof(int));

    bSuccess = OpenSSL_Open();

    return bSuccess;
}

/**
 * HTTPSSLChannel::CloseChannel()
 *
 * Protected function
 *
 * @param
 * @return 
 */

void HTTPSSLChannel::
CloseChannel()
{
    OpenSSL_Close();
        
    if( INVALID_SOCKET != m_Sock) 
    {
#ifdef WIN32
        closesocket( m_Sock);
#else
        ::close( m_Sock);
#endif
        m_Sock = INVALID_SOCKET; 
    }
}

/**
 * HTTPSSLChannel::StartSockets()
 *
 * Protected function
 *
 * @param
 * @return 
 */

bool HTTPSSLChannel::
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
        m_LastError = "WinSock DLL not responding.";
    }
    else
    {
        // Query to see whether the available version matches what is required
        if ((LOBYTE( wsaData.wVersion) <  WS_VERSION_MAJOR()) ||
            (LOBYTE( wsaData.wVersion) == WS_VERSION_MAJOR() &&
             HIBYTE( wsaData.wVersion) <  WS_VERSION_MINOR()))
        {
            // Error - Underlying Windows socket transport version is not compatible with what is required.
            char     szErrorBuffer[100];

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
    /* other OS specific Intitialization goes here */
    bSuccess = true;
#endif

    return bSuccess;
}

/**
 * HTTPSSLChannel::StopSockets()
 *
 * Protected function
 *
 * @param
 * @return 
 */

void HTTPSSLChannel::
StopSockets()
{
#ifdef WIN32
    WSACleanup();
#endif // WIN32
}

/**
 * HTTPSSLChannel::applyTimeout()
 *
 * @return int 
 */

int HTTPSSLChannel::
applyTimeout()
{
    fd_set            set;
    struct timeval    timeout;

    // Initialize the file descriptor set.
    FD_ZERO( &set);
    FD_SET( m_Sock, &set);

    /* Initialize the timeout data structure. */
    timeout.tv_sec = m_lTimeoutSeconds;
    timeout.tv_usec = 0;

    /* select returns 0 if timeout, 1 if input available, -1 if error. */
    return select( FD_SETSIZE, &set, NULL, NULL, &timeout);
}

/**
 * HTTPSSLChannel::OpenSSL_Initialise()
 *
 * Protected function
 *
 * @return int 
 */

void HTTPSSLChannel::
OpenSSL_Initialise()
{
    // Lets get nice error messages
    SSL_load_error_strings();

    // Setup all the global SSL stuff
    SSLeay_add_ssl_algorithms();
}

/**
 * HTTPSSLChannel::OpenSSL_Open()
 *
 * Protected function
 *
 * @return int 
 */

bool HTTPSSLChannel::
OpenSSL_Open()
{
    SSL_METHOD *    req_method = SSLv23_client_method();
    bool            bSuccess = (bool) AXIS_FAIL;
    unsigned long   iSSLErrorIndex = 0;

    m_sslContext = SSL_CTX_new( req_method);

    if( !m_sslContext)
    {
        iSSLErrorIndex = ERR_get_error();

        // OpenSSL documents that this must be at least 120 bytes long.
        char    szSSLErrorBuffer[120];
        ERR_error_string( iSSLErrorIndex, szSSLErrorBuffer);
        m_LastError = szSSLErrorBuffer;

        CloseChannel();       
        return bSuccess;
    }

    SSL_CTX_set_verify( m_sslContext,
                        SSL_VERIFY_NONE, // SSL_VERIFY_PEER 
                        cert_verify_callback);

    // Lets make an SSL structure
    m_sslHandle = SSL_new( m_sslContext);
    SSL_set_connect_state( m_sslHandle);

    // pass the raw socket into the SSL layers
    SSL_set_fd( m_sslHandle, m_Sock);

    ERR_clear_error();
    int ret = SSL_connect( m_sslHandle);

    //   1  is fine
    //   0  is "not successful but was shut down controlled"
    //  <0  is "handshake was not successful, because a fatal error occurred"
    if( ret <= 0)
    {
        OpenSSL_SetSecureError(ret);
        CloseChannel();
    }
    else
    {
        bSuccess = (bool) AXIS_SUCCESS;
    }

    return bSuccess;
}

/**
 * HTTPSSLChannel::OpenSSL_Close()
 *
 * Protected function
 *
 * @return int 
 */

int HTTPSSLChannel::
OpenSSL_Close()
{
    if( m_sslHandle)
    {
        SSL_shutdown( m_sslHandle);
        SSL_set_connect_state( m_sslHandle);

        SSL_free( m_sslHandle);
        m_sslHandle = NULL;
    }

    if( m_sslContext)
    {
        SSL_CTX_free( m_sslContext);
        m_sslContext = NULL;
    }

    return 0;
}

/**
 * HTTPSSLChannel::OpenSSL_SetSecureError( int iError)
 *
 * Protected function
 *
 * @return int 
 */

void HTTPSSLChannel::
OpenSSL_SetSecureError( int iError)
{
    // OpenSSL documents that this must be at least 120 bytes long.
    char error_buffer[120];   
    char szError[100];
    unsigned long sslerror;
    
    sprintf( szError, "%d", iError);      
    
    switch( iError)
    {
        case SSL_ERROR_NONE:        // this is not an error
        case SSL_ERROR_ZERO_RETURN:    // no more data
            return;

        case SSL_ERROR_WANT_READ:
        case SSL_ERROR_WANT_WRITE:
        case SSL_ERROR_SYSCALL:
        {
            iError = GETLASTERROR;
            sprintf( szError, "%d", iError);
            m_LastError = "OpenSSL socket error is " + std::string(szError) 
                            + " - " + PLATFORM_GET_ERROR_MESSAGE(iError);
            break;
        }

        case SSL_ERROR_SSL:
        // A failure in the SSL library occurred, usually a protocol error.  The
        // OpenSSL error queue contains more information on the error.
        default: 
        // openssl/ssl.h says "look at error stack/return value/errno"
        {
            // A failure in the SSL library occurred, usually a protocol error.  The
            // OpenSSL error queue contains more information on the error.
            m_LastError = "OpenSSL error is " + std::string(szError) + ". Error stack:\n";
            while ((sslerror = ERR_get_error()) != 0)
            {
                ERR_error_string( sslerror, error_buffer);
                m_LastError += std::string(error_buffer) + "\n";
            }
        }
    }
}

void HTTPSSLChannel::
closeQuietly( bool bNoExceptionOnForceClose_Update)
{
    bNoExceptionOnForceClose = bNoExceptionOnForceClose_Update;
}
