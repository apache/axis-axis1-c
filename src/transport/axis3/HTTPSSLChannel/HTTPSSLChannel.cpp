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

#include "HTTPSSLChannel.hpp"
#include "../../../platforms/PlatformAutoSense.hpp"

/**
 * cert_verify_callback( int ok, X509_STORE_CTX * ctx)
 *
 * cert_verify_callback callback
 *
 */

static int cert_verify_callback( int ok, X509_STORE_CTX * ctx)
{
  X509 *	err_cert;
  char		buf[256];

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

HTTPSSLChannel::HTTPSSLChannel()
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

HTTPSSLChannel::~HTTPSSLChannel()
{
	OpenSSL_Close();

// If the socket value is not invalid, then close the socket before
// deleting the Channel object.
	if( m_Sock != INVALID_SOCKET)
	{
		CloseChannel();
	}

	StopSockets();
}

/**
 * HTTPSSLChannel::getURL()
 *
 * Return the URL currently assicated with the channel object.
 *
 * @return char * containing the URL associated with the open socket
 */

const char * HTTPSSLChannel::getURL()
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

void HTTPSSLChannel::setURL( const char * cpURL)
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

URL & HTTPSSLChannel::getURLObject()
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

bool HTTPSSLChannel::open() throw (HTTPTransportException&)
{
	bool	bSuccess = (bool) AXIS_FAIL;

    if( m_Sock != INVALID_SOCKET)
	{
		CloseChannel();
	}

	m_LastError = "No Errors";

	if( (bSuccess = OpenChannel()) != AXIS_SUCCESS)
	{
		throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CONNECT_ERROR,
									  (char *) m_LastError.c_str());
	}

	bSuccess = OpenSSL_Open();

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

bool HTTPSSLChannel::close()
{
    if( m_Sock != INVALID_SOCKET)
	{
		CloseChannel();
	}

	m_Sock = INVALID_SOCKET;

	return AXIS_SUCCESS;
}

/**
 * HTTPSSLChannel::GetLastErrorMsg()
 *
 * Returns the last reported error on the channel.
 *
 * @return string containing last error.
 */

const std::string & HTTPSSLChannel::GetLastErrorMsg()
{
	return m_LastError;
}

/**
 * HTTPSSLChannel::operator >> (const char * msg)
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

const IChannel & HTTPSSLChannel::operator >> (const char * msg)
{
    if (INVALID_SOCKET == m_Sock)
    {
// Error - Reading cannot be done without having a open socket Input
//         streaming error on undefined channel; please open the
//		   channel first

		m_LastError = "No open socket to read from.";

		throw HTTPTransportException( SERVER_TRANSPORT_INVALID_SOCKET,
									  (char *) m_LastError.c_str());
    }

    ReadFromSocket( msg);

	return *this;
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

const IChannel & HTTPSSLChannel::operator << (const char * msg)
{
// Check that the Tx/Rx sockets are valid (this will have been done if the
// application has called the open method first.
    if( INVALID_SOCKET == m_Sock)
    {
// Error - Writing cannot be done without having a open socket to
//         remote end.  Throw an exception.

		m_LastError = "No valid socket open";

		throw HTTPTransportException( SERVER_TRANSPORT_INVALID_SOCKET,
									  (char *) m_LastError.c_str());
    }

	WriteToSocket( msg, strlen( msg));

	return *this;
}

/**
 * HTTPSSLChannel::setTimeout( const long lSeconds)
 *
 * Set the Rx message timeout (in seconds)
 *
 * @param long containing timeout value in seconds
 */

void HTTPSSLChannel::setTimeout( long lSeconds)
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

void HTTPSSLChannel::setSocket( unsigned int uiNewSocket)
{
    m_Sock = uiNewSocket;
}

/**
 * HTTPSSLChannel::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type,
 *										 const char * value)
 *
 * The following list can be set using this property:-
 * SOAPACTION_HEADER			- No action
 * SERVICE_URI					- No action
 * OPERATION_NAME				- No action
 * SOAP_MESSAGE_LENGTH			- No action
 * TRANSPORT_PROPERTIES			- No action
 * SECURE_PROPERTIES			- No action
 * DLL_NAME						- No action
 * CHANNEL_HTTP_SSL_DLL_NAME	- No action
 * CHANNEL_HTTP_DLL_NAME		- No action
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE contains the type of property to be
 *        set.
 *        const char * contains the value for the type to be set to.
 * @return boolean flag indicating success of the alteration. 
 */

bool HTTPSSLChannel::setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)
{
	bool	bSuccess = false;

	return bSuccess;
}

/**
 * HTTPSSLChannel::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
 *
 * The following list can be retrieved using this property:-
 * SOAPACTION_HEADER			- No action
 * SERVICE_URI					- No action
 * OPERATION_NAME				- No action
 * SOAP_MESSAGE_LENGTH			- No action
 * TRANSPORT_PROPERTIES			- No action
 * SECURE_PROPERTIES			- No action
 * DLL_NAME						- No action
 * CHANNEL_HTTP_SSL_DLL_NAME	- No action
 * CHANNEL_HTTP_DLL_NAME		- No action
 *
 * @param AXIS_TRANSPORT_INFORMATION_TYPE contains the type of property to be
 *        recovered.
 * @return const char * contains the value for the requested type.
 */

const char * HTTPSSLChannel::getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)
{
	return NULL;
}

/**
 * HTTPSSLChannel::setProxy( const char * pcProxyHost, unsigned int uiProxyPort)
 *
 * Setup he proxy values to be used by the channel.
 *
 * @param const char * containing the name of the proxy host.
 *		  unsigned int containing the proxy port value.
 */

void HTTPSSLChannel::setProxy (const char *pcProxyHost, unsigned int uiProxyPort)
{
    m_strProxyHost = pcProxyHost;
    m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;
}

// +--------------------------------------------------------------------------+
// | Protected methods														  |
// | -----------------														  |
// +--------------------------------------------------------------------------+

/**
 * HTTPSSLChannel::OpenChannel()
 *
 * Protected function
 *
 * @param
 * @return 
 */

bool HTTPSSLChannel::OpenChannel()
{
// This method is common to all channel implementations
	bool	bSuccess = (bool) AXIS_FAIL;

// Create the Client (Rx) side first.
#ifdef IPV6
    struct addrinfo		aiHints;
	struct addrinfo *	paiAddrInfo;
	struct addrinfo *	paiAddrInfo0;

    // hints is used after zero cleared
    memset( &aiHints, 0, sizeof( aiHints));

    aiHints.ai_family = PF_UNSPEC;		// This allows the sockets code to use
										// whatever socket family is available.
    aiHints.ai_socktype = SOCK_STREAM;

    char szPort[7];
   
    const char	*	pszHost = m_URL.getHostName();
    unsigned int	uiPort = m_URL.getPort();

    if( m_bUseProxy)
    {
        uiPort = m_uiProxyPort;
        pszHost = m_strProxyHost.c_str();
    }
 
    sprintf( szPort, "%hd", uiPort);

    if( getaddrinfo( pszHost, szPort, &aiHints, &paiAddrInfo0))
    {
        throw HTTPTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR);
    }

    for( paiAddrInfo = paiAddrInfo0; paiAddrInfo; paiAddrInfo = paiAddrInfo->ai_next)
    {
        m_Sock = socket( paiAddrInfo->ai_family,
						 paiAddrInfo->ai_socktype,
						 paiAddrInfo->ai_protocol);

        if( m_Sock < 0)
        {
            continue;
        }

        if( connect( m_Sock, paiAddrInfo->ai_addr, paiAddrInfo->ai_addrlen) < 0)
        {
            // Cannot open a channel to the remote end, shutting down the
            // channel and then throw an exception.
            // Before we do anything else get the last error message;
			long dw = GETLASTERROR

			CloseChannel();

            freeaddrinfo( paiAddrInfo0);
			
			string *	message = PLATFORM_GET_ERROR_MESSAGE( dw);
			char		fullMessage[600];

			sprintf( fullMessage,
					 "Failed to open connection to server: \n \
					 hostname='%s'\n\
					 port='%d'\n\
					 Error Message='%s'\
					 Error Code='%d'\n",
					 m_URL.getHostName(), m_URL.getPort(), message->c_str(), (int) dw);
				
			delete( message);

			throw HTTPTransportException( CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED,
										  fullMessage);
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
    sockaddr_in	clAddr;

	clAddr.sin_family = AF_INET;	// AF_INET (address family Internet).
	clAddr.sin_port = 0;			// No Specify Port required.
	clAddr.sin_addr.s_addr = INADDR_ANY;

// Attempt to bind the client to the client socket.
	if( bind( m_Sock, (struct sockaddr *) &clAddr, sizeof( clAddr)) == SOCKET_ERROR)
	{
// Error whilst binding. Cannot open a channel to the remote end,
// shutting down the channel and then throw an exception.
		CloseChannel();

		m_LastError = "Error whilst binding. Cannot open a channel to the remote end,";

		return bSuccess;
	}

// Although the above fragment makes use of the bind() API, it would be
// just as effective to skip over this call as there are no specific
// local port ID requirements for this client. The only advantage that
// bind() offers is the accessibility of the port which the system 
// chose via the .sin_port member of the cli_addr structure which will 
// be set upon success of the bind() call.

// Create the Server (Tx) side.

	sockaddr_in			svAddr;
	struct hostent *	pHostEntry = NULL;
	const char *		host = m_URL.getHostName();
	unsigned int		port = m_URL.getPort();

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
// Cannot open a channel to the remote end, shutting down the
// channel and then throw an exception.

// Before we do anything else get the last error message;
			long dw = GETLASTERROR
			CloseChannel();

			
			string* message = PLATFORM_GET_ERROR_MESSAGE(dw);

			char fullMessage[600];
			sprintf(fullMessage,
				"Failed to open connection to server: \n \
				hostname='%s'\n\
				port='%d'\n\
				Error Message='%s'\
				Error Code='%d'\n",
				m_URL.getHostName(), m_URL.getPort(), message->c_str(), dw);
				
			delete(message);

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

void HTTPSSLChannel::CloseChannel()
{
    if( INVALID_SOCKET != m_Sock) // Check if socket already closed : AXISCPP-185
	{
#ifdef WIN32
		closesocket( m_Sock);
#else
		::close( m_Sock);
#endif
		m_Sock = INVALID_SOCKET; // fix for AXISCPP-185
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

bool HTTPSSLChannel::StartSockets()
{
	bool	bSuccess = false;
#ifdef WIN32
    WSADATA wsaData;	// Contains vendor-specific information, such as the
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
// Error - Underlying Windows socket transport version is not compatible with what is required.
			char 	szErrorBuffer[100];

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
    /* cout << "no need for linux" << endl; */
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

void HTTPSSLChannel::StopSockets()
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

int HTTPSSLChannel::applyTimeout()
{
    fd_set			set;
    struct timeval	timeout;

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
 * HTTPSSLChannel::ReadFromSocket( const char * pszRxBuffer)
 *
 * Protected function
 *
 * @return int 
 */

int HTTPSSLChannel::ReadFromSocket( const char * pszRxBuffer)
{
    int nByteRecv = 0;

    nByteRecv = SSL_read( m_sslHandle, (void *) pszRxBuffer, BUF_SIZE - 1);

    if(nByteRecv < 0)
    {
// failed SSL_read
		if( !bNoExceptionOnForceClose)
		{
	        OpenSSL_SetSecureError( SSL_get_error( m_sslHandle, nByteRecv));
		}

        OpenSSL_Close();

		::close();

		m_Sock = INVALID_SOCKET; // fix for AXISCPP-185
    }
	else
    {
       *(((char *)pszRxBuffer) + nByteRecv) = '\0';  
    }

	return nByteRecv;
}

/**
 * HTTPSSLChannel::WriteToSocket( const char * psTxBuffer, int iSize)
 *
 * Protected function
 *
 * @return int 
 */

int HTTPSSLChannel::WriteToSocket( const char * psTxBuffer, int iSize)
{
	int nByteSent;

    nByteSent = SSL_write( m_sslHandle, (char *) psTxBuffer, iSize);

    if(nByteSent < 0)
    {
// failed SSL write
        OpenSSL_SetSecureError( SSL_get_error( m_sslHandle, nByteSent));

        OpenSSL_Close();
    }

	return nByteSent;
}

/**
 * HTTPSSLChannel::OpenSSL_Initialise()
 *
 * Protected function
 *
 * @return int 
 */

void HTTPSSLChannel::OpenSSL_Initialise()
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

bool HTTPSSLChannel::OpenSSL_Open()
{
    SSL_METHOD *	req_method = SSLv23_client_method();
	bool			bSuccess = (bool) AXIS_FAIL;
	int				iSSLErrorIndex = 0;

    m_sslContext = SSL_CTX_new( req_method);

    if( !m_sslContext)
    {
        iSSLErrorIndex = ERR_get_error();

// OpenSSL documents that this must be at least 120 bytes long.
        char	szSSLErrorBuffer[120];

        ERR_error_string( iSSLErrorIndex, szSSLErrorBuffer);

		m_LastError = szSSLErrorBuffer;

        OpenSSL_Close();

        throw HTTPTransportException( CLIENT_SSLCHANNEL_CONTEXT_CREATE_ERROR,
									  szSSLErrorBuffer);
    }

    SSL_CTX_set_verify( m_sslContext,
						SSL_VERIFY_NONE, // SSL_VERIFY_PEER 
						cert_verify_callback);

// Lets make an SSL structure
    m_sslHandle = SSL_new( m_sslContext);
    SSL_set_connect_state( m_sslHandle);

// pass the raw socket into the SSL layers
    SSL_set_fd( m_sslHandle, m_Sock);

    iSSLErrorIndex = SSL_connect( m_sslHandle);

//   1  is fine
//   0  is "not successful but was shut down controlled"
//  <0  is "handshake was not successful, because a fatal error occurred"
	if( iSSLErrorIndex <= 0)
	{
		OpenSSL_SetSecureError( iSSLErrorIndex);
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

int HTTPSSLChannel::OpenSSL_Close()
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

void HTTPSSLChannel::OpenSSL_SetSecureError( int iError)
{
    switch( iError)
    {
        case SSL_ERROR_NONE:		// this is not an error
        case SSL_ERROR_ZERO_RETURN:	// no more data
            break;

        case SSL_ERROR_WANT_READ:
        case SSL_ERROR_WANT_WRITE:
        case SSL_ERROR_SYSCALL:
        {
            #ifdef WIN32
                iError = ::GetLastError();
            #else
                iError =  errno;
            #endif

            OpenSSL_Close();

			m_LastError = "SSL_ERROR_SYSCALL";

            throw HTTPTransportException( CLIENT_SSLCHANNEL_ERROR,
										  (char *) m_LastError.c_str());

			break;
        }

        case SSL_ERROR_SSL:
        {
// A failure in the SSL library occurred, usually a protocol error.  The
// OpenSSL error queue contains more information on the error.
			int sslerror = ERR_get_error();

// OpenSSL documents that this must be at least 120 bytes long.
            char error_buffer[120];

            ERR_error_string( sslerror, error_buffer);

            OpenSSL_Close();

			m_LastError = error_buffer;

            throw HTTPTransportException( CLIENT_SSLCHANNEL_ERROR, error_buffer);

			break;
        }

        default: 
// openssl/ssl.h says "look at error stack/return value/errno"
        {
// A failure in the SSL library occurred, usually a protocol error.  The
// OpenSSL error queue contains more information on the error.
            int sslerror = ERR_get_error();

// OpenSSL documents that this must be at least 120 bytes long.
            char error_buffer[120];

            ERR_error_string( sslerror, error_buffer);

            OpenSSL_Close();

			m_LastError = error_buffer;

            throw HTTPTransportException( CLIENT_SSLCHANNEL_ERROR, error_buffer);
        }
    }
}

void HTTPSSLChannel::closeQuietly( bool bNoExceptionOnForceClose_Update)
{
	bNoExceptionOnForceClose = bNoExceptionOnForceClose_Update;
}
