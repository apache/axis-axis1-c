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
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

#include "Platform.h"
#include "Channel.h"
#include "../../platforms/PlatformAutoSense.hpp"
#include <iostream>
#include <stdio.h>


using namespace std;
/**
 * Create a Channel & initialize
 * 
 */

/** Channel::Channel() Constructor
 */
Channel::Channel ():m_Sock (INVALID_SOCKET), m_iMsgLength( 0), m_sMsg(NULL), m_lTimeoutSeconds(0), m_bUseProxy(false)
{
	
#ifdef WIN32
	m_lTimeoutSeconds = 10;
#endif

}

/** Channel::~Channel() Destructor
 */
Channel::~Channel ()
{

	// If the socket value is not invalid, then close the socket before
	// deleting the Channel object.
	if( m_Sock != INVALID_SOCKET)
	{
		closeChannel();
	}

        if (m_sMsg)
            delete [] m_sMsg;

}

/** Channel::setURL( URL) sets the URL for the channel.
 *
 * @param const char* URL pointer to a NULL terminated character string that
 * contains the new URL for the channel.
 */
void Channel::setURL(const char* cpURL)
{

	// Set the Channel URL to the new value.
	// NB: This will cause problems if the new URL is diferent in type from the
	//     old URL. e.g. if the new URL is https and the old URL was http, then
	//     problems will occur because each type operates differently.
    m_URL.setURL( cpURL);

}
    
/** Channel::getURL() gets the URL for the channel.
 *
 * @return const char* URL pointer to a NULL terminated character string that
 * contains the URL for the channel.
 */
const char* Channel::getURL() 
{

	// Return the URL currently assicated with the channel object.
    return m_URL.getURL();
}


/**
 * This channel open INET channel for the time being using primitive sockets
 * Do we need any other type of channel; like shared memory, pipes etc. ????
 * 
 * @param    p_RemoteNode    End point address as hostname/IP
 * @param    p_RemoteEnd        Port #
 *
 * @return  true if successfuly open a soket to the endpoint. o/w exception is 
 * thrown
 */

bool
Channel::open () //std::string & p_RemoteNode, unsigned short p_RemoteEnd)
throw (AxisTransportException&)
{
    // if there is an open socket already, close it first
    if (m_Sock != INVALID_SOCKET)
        closeChannel();

	// If the underlying socket transport has not been initialised properly,
	// then thrown an exeption.
    if( !Init())
	{

		throw AxisTransportException( SERVER_TRANSPORT_CHANNEL_INIT_ERROR);
	}

	// If the transport was initilised, then create client and server sockets.
    sockaddr_in clAddr;

	// Create the Client (Rx) side first.
    if( (m_Sock = socket( PF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET)
    {
		clAddr.sin_family = AF_INET;	// AF_INET (address family Internet).
		clAddr.sin_port = 0;			// No Specify Port required.
		clAddr.sin_addr.s_addr = INADDR_ANY;

		// Attempt to bind the client to the client socket.
		if( bind( m_Sock, (struct sockaddr *) &clAddr, sizeof( clAddr)) == SOCKET_ERROR)
		{
			// Error whilst binding. Cannot open a channel to the remote end,
			// shutting down the channel and then throw an exception.
			closeChannel();


			throw AxisTransportException( SERVER_TRANSPORT_SOCKET_CONNECT_ERROR);
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

                const char* host = m_URL.getHostName();
                unsigned int port = m_URL.getPort();
                if (m_bUseProxy)
                {
                    port = m_uiProxyPort;
                    host = m_strProxyHost.c_str();
                }
		svAddr.sin_family = AF_INET;
		svAddr.sin_port = htons (port);

		// Probably this is the host-name of the server we are connecting to...
		if( (pHostEntry = gethostbyname(host)))
		{
			svAddr.sin_addr.s_addr = ((struct in_addr *) pHostEntry->h_addr)->s_addr;
		}
		else
		{
			// No this is the IP address
			svAddr.sin_addr.s_addr = inet_addr (host);
		}

		// Attempt to connect to the remote server.
		if( connect( m_Sock, (struct sockaddr *) &svAddr, sizeof (svAddr)) == SOCKET_ERROR)
		{
			// Cannot open a channel to the remote end, shutting down the
			// channel and then throw an exception.

			// Before we do anything else get the last error message;
			long dw = GETLASTERROR

			closeChannel();
			
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

			throw AxisTransportException( CLIENT_TRANSPORT_OPEN_CONNECTION_FAILED, fullMessage);
		}

    }
    else
    {
		// Sockets error Couldn't create socket.  Close the channel and throw
		// an exception.
		closeChannel();


		throw AxisTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR);
    }


    /* Turn off the Nagle algorithm - Patch by Steve Hardy */

    /* This is needed, because our TCP stack would otherwise wait at most
     * 200 ms before actually sending data to the server (while waiting for
     * a full packet). This limits performance to around 5 requests per
     * second, which is not acceptable. Turning off the Nagle algorithm
     * allows for much faster transmission of small packets, but may
     * degrade high-bandwidth transmissions.
     */

    int one = 1;
    setsockopt(m_Sock, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof(int));

    return true;
}

/**
 * Channel::Init() Operating System specific initialization for sockets
 *
 * @return  bool True if successfully initialised the OS specifics.
 *				 False if unsuccessful
 */

bool Channel::Init ()
{

#ifdef WIN32
    WSADATA wsaData;	// Contains vendor-specific information, such as the
						// maximum number of sockets available and the maximum
						// datagram size.

	// wsaData filled by Windows Sockets DLLs.
    if( WSAStartup( WS_VERSION_REQD, &wsaData))
    {
		// Error - Could not setup underlying Windows socket transport
		//         mechanism.
		m_LastErr = "WinSock DLL not responding.";

		return false;
    }
    else
    {
		// Query to see whether the available version matches what is required
		if ((LOBYTE( wsaData.wVersion) <  WS_VERSION_MAJOR()) ||
			(LOBYTE( wsaData.wVersion) == WS_VERSION_MAJOR() &&
			 HIBYTE( wsaData.wVersion) <  WS_VERSION_MINOR()))
		{
			// Error - Underlying Windows socket transport version is not
			//         compatible with what is required.
			char buf[100];

			sprintf( buf,
				 "Windows Sockets version %d.%d not supported by winsock2.dll",
				 LOBYTE (wsaData.wVersion), HIBYTE (wsaData.wVersion));

			Error( buf);

			closeChannel();


			return false;
		}
    }
#else
    /* cout << "no need for linux" << endl; */
    /* other OS specific Intitialization goes here */
#endif


    return true;
}

/**
 * Channel::operator << (Msg) Write (send) a message to the remote server.
 * Sending a message will block the application (i.e. synchronous communication).
 * NB: We may need to do this asynchronizely; preferably either non-blocking
 * send or pthread.
 *
 * @param    const char * Msg NULL terminated character string containing the
 * message to be written to the open channel.
 * NB: For GSKit SSL, the message has been encoded and may contain embedded
 * null characters.  To overcome this problem, the m_iMsgLength value must be
 * set to the message length before calling this method.  If m_iMsgLength is
 * not 0, this method will assume the the value is the message length.
 * m_iMsgLength is set to 0 in the constructor, so unless it is intentionally
 * changed, it will not have any effect on this method.
 *
 * @return const Channel & is the address of the Channel object (the 'this'
 * pointer).
 */
const Channel &Channel::operator << (const char *msg)
{
	// Check that the Tx/Rx sockets are valid (this will have been done if the
	// application has called the open method first.
    if( INVALID_SOCKET == m_Sock)
    {
		// Error - Writing cannot be done without having a open socket to
		//         remote end.  Throw an exception.

		throw AxisTransportException( SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int size = strlen( msg);
	int nByteSent;

	if( m_iMsgLength)
	{
		size = m_iMsgLength;
	}


    if( (nByteSent = send( m_Sock, msg, size, MSG_DONTROUTE)) == SOCKET_ERROR)
    {
		// Output streaming error while writing data.  Close the channel and
		// throw an exception.
		closeChannel();


		throw AxisTransportException(SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR);
    }


    return *this;
}

/**
 * Channel::operator >> (Msg) Read (receive) a message from the remote server;
 * Reading may be done in 'chunks'.
 *
 * @param    std::string & Msg is string that will receive the message.
 * NB: For GSKit SSL, the message has been encoded and may contain embedded
 * null characters.  To overcome this problem, the m_iMsgLength value must be
 * set to the negative of the message length before calling this method.  If
 * m_iMsgLength is not negative, this method will assume the BUF_SIZE value is
 * the message length.  m_iMsgLength is set to 0 in the constructor, so unless
 * it is intentionally changed, it will not have any effect on this method.
 *
 * @return const Channel & is the address of the Channel object (the 'this'
 * pointer).
 */
const Channel &Channel::operator >> (std::string & msg)
{

    msg = "";

    if (INVALID_SOCKET == m_Sock)
    {
		// Error - Reading cannot be done without having a open socket Input
		//         streaming error on undefined channel; please open the
		//		   channel first


		throw AxisTransportException( SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int nByteRecv = 0;
    char buf[BUF_SIZE];
	int	iBufSize = BUF_SIZE;

	if( m_iMsgLength < 0)
	{
		iBufSize = -m_iMsgLength;
	}
	else
	{
		iBufSize--;
	}

    //assume timeout not set; set default tatus to OK
    int iTimeoutStatus = 1;

    //check if timeout set
    if(m_lTimeoutSeconds)
	{
        iTimeoutStatus = applyTimeout();
	}

    // Handle timeout outcome
    if( iTimeoutStatus < 0)
    {
		// Error


        // Select SOCKET_ERROR. Channel error while waiting for timeout
        throw AxisTransportException( SERVER_TRANSPORT_TIMEOUT_EXCEPTION, 
                                     "Channel error while waiting for timeout");        
    }

    if( iTimeoutStatus == 0)
    {
		// Timeout expired - select timeout expired.
        // Channel error connection timeout before receving


        throw AxisTransportException( SERVER_TRANSPORT_TIMEOUT_EXPIRED, 
                                     "Channel error: connection timed out before receving");
    }

    // Either timeout was not set or data available before timeout; so read

    if( (nByteRecv = recv( m_Sock, (char *) &buf, iBufSize, 0)) == SOCKET_ERROR)
    {
		// Recv SOCKET_ERROR, Channel error while getting data
		/* closeChannel(); */


		throw AxisTransportException( SERVER_TRANSPORT_INPUT_STREAMING_ERROR, 
									  "Channel error while getting data");
    }

    if( nByteRecv)
    {
		/* printf("nByteRecv:%d\n", nByteRecv); */
		buf[nByteRecv] = '\0';
		/* got a part of the message, so add " \        "to form */
		msg = buf;

		if( m_iMsgLength < 0)
		{
			m_iMsgLength = nByteRecv;

                        if (m_sMsg) 
                        {
                            delete [] m_sMsg;
                            m_sMsg = NULL;
                        }
			m_sMsg = new char[nByteRecv];

			memcpy( m_sMsg, buf, nByteRecv);
		}
    }
    else
	{
		if( m_iMsgLength < 0)
		{
			m_iMsgLength = nByteRecv;
		}
	;//printf ("execution break\n");
    }

    return *this;
}

/**
 * Channel::readNonBlocking( Msg, BlockingRequired) Read (receive) a message
 * from the remote server; Reading may be done in 'chunks'?
 *
 * @param string & Msg
 * @param bool BlockingRequired
 *
 * @return const Channel & is the address of the Channel object (the 'this'
 * pointer).
 */
const Channel &Channel::readNonBlocking( std::string & msg, bool bBlockingRequired)
{
    msg = "";
    if (INVALID_SOCKET == m_Sock)
    {
	/*Reading cannot be done without having a open socket*/
	throw AxisTransportException(SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int nByteRecv = 0;
    char buf[BUF_SIZE];

    //Samisa: I want to set the socket to non blocking mode here
    //for Winsock there is no simple way to do this but for Linux I used MSG_DONTWAIT
    //there is no MSG_DONTWAIT defined in Winsock
    int flags = 0;

#if defined WIN32
      // Set the socket I/O mode; iMode = 0 for blocking; iMode != 0 for non-blocking
      int iMode = 1;
 
 	if( bBlockingRequired)
 	{
 		iMode = 0;
 	}
 
     ioctlsocket( m_Sock, FIONBIO, (u_long FAR*) &iMode);
 
      flags = 0;
#elif defined AIX
	flags=MSG_WAITALL;
	if (!bBlockingRequired)
	{
        flags=MSG_NONBLOCK;
	}
#elif defined( __OS400__ )
   fcntl(m_Sock, F_SETFL, (int)O_NONBLOCK);
   flags = 0;
#else
    //for linux
 	if( !bBlockingRequired)
 	{
 	    flags = MSG_DONTWAIT;
 	}
 
    //TODO: define flags (or other means) to enable non blocking for other operating systems
#endif

    if ((nByteRecv = recv (m_Sock, (char *) &buf, BUF_SIZE - 1, flags))
	== SOCKET_ERROR)
    {
	/*Channel error while getting data*/
	return *this;
    }
    if (nByteRecv)
    {
	buf[nByteRecv] = '\0';
	msg = buf;
    }
    else
	Error( "Channel::readNonBlocking: execution break");

    return *this;
}

/**
 * Channel::closeChannel() Close and clean-up using specific Operating System
 * calls.
 */
void Channel::closeChannel ()
{

    if( INVALID_SOCKET == m_Sock) // Check if socket already closed : AXISCPP-185
	{
        return;
	}

#ifdef WIN32
    closesocket( m_Sock);

    // Check for any possible error conditions from WSACleanup() and report
    // them before exiting, as this information might indicate a network
    // layer problem in the system.

    WSACleanup ();
#else
    ::close( m_Sock);

#endif
    m_Sock = INVALID_SOCKET; // fix for AXISCPP-185

}

/**
 * Channel::Error( Error) Log any errors that cause on channel usage or
 * initilaization.
 */
void Channel::Error( const char *err)
{
#ifdef _DEBUG
    std::cerr << err << std::endl;
#endif
}

/**
 * Channel::setTimeout( Seconds)
 *
 * @param const long Seconds
 */
void Channel::setTimeout(const long lSeconds)
{

    m_lTimeoutSeconds = lSeconds;

}

/**
 * Channel::applyTimeout()
 *
 * @return int 
 */
int Channel::applyTimeout()
{

    fd_set set;
    struct timeval timeout;

    // Initialize the file descriptor set.
    FD_ZERO( &set);
    FD_SET( m_Sock, &set);

    /* Initialize the timeout data structure. */
    timeout.tv_sec = m_lTimeoutSeconds;
    timeout.tv_usec = 0;

    /* select returns 0 if timeout, 1 if input available, -1 if error. */
    return select( FD_SETSIZE, &set, NULL, NULL, &timeout);
}

// This is used by SimpleAxisServer
void Channel::setSocket(unsigned int uiNewSocket)
{
    m_Sock = uiNewSocket;
}

/**
 * Debug routine will be deleted.
 */
void Channel::hexOutput( char * psData, int iDataLength)
{
	unsigned char *	pByte = (unsigned char *) psData;
	string			sLineHex;
	string			sLineChar;
	int				iByteCount = 0;
	int				iLineCount;
	char			szDigits[6];

	while( iByteCount < iDataLength)
	{
		sprintf( szDigits, "%04X ", iByteCount);

		sLineHex = szDigits;
		sLineChar = "";
		iLineCount = 0;

		while( iLineCount < 16 && iByteCount < iDataLength)
		{
			unsigned char Char = *pByte;

			if( Char < 32 || Char > 127)
			{
				Char = '.';
			}

			sprintf( szDigits, "%02X ", *pByte);

			sLineHex = sLineHex + szDigits;
			sLineChar = sLineChar + (char) Char;

			pByte++;
			iByteCount++;
			iLineCount++;
		}

		for( int iCount = iLineCount; iCount < 16; iCount++)
		{
			sLineHex = sLineHex + "   ";
		}

		printf( "%s %s\n", sLineHex.c_str(), sLineChar.c_str());
	}
}

void Channel::setProxy (const char *pcProxyHost, unsigned int uiProxyPort)
{
    m_strProxyHost = pcProxyHost;
   m_uiProxyPort = uiProxyPort;
    m_bUseProxy = true;
}
