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
#include <iostream>
#include <stdio.h>

using namespace std;
/**
 * Create a Channel & initialize
 * 
 */

Channel::Channel ():m_Sock (INVALID_SOCKET), m_lTimeoutSeconds(0)
{

}

Channel::~Channel ()
{
    closeChannel ();
}

void Channel::setURL(const char* cpURL)
{
    m_URL.setURL(cpURL);
}
    
const char* Channel::getURL() 
{
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
    if (!Init ())
	throw AxisTransportException(SERVER_TRANSPORT_CHANNEL_INIT_ERROR);

    sockaddr_in clAddr, svAddr;

    if ((m_Sock = socket (PF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET)
    {
	clAddr.sin_family = AF_INET;	/* AF_INET (address family Internet). */
	clAddr.sin_port = 0;	/* No Specify Port required */
	clAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind (m_Sock, (struct sockaddr *) &clAddr, sizeof (clAddr)) ==
	    SOCKET_ERROR)
	{
	    /* Error - Binding. Cannot open a channel to the remote end, 
               shutting down the channel
            */
	    closeChannel ();
	    throw AxisTransportException(SERVER_TRANSPORT_SOCKET_CONNECT_ERROR);
	}

	/* Although the above fragment makes use of the bind() API, it would be
	 * just as effective to skip over this call as there are no specific
	 * local port ID requirements for this client. The only advantage that
	 * bind() offers is the accessibility of the port which the system 
	 * chose via the .sin_port member of the cli_addr structure which will 
	 * be set upon success of the bind() call.
	 */

	svAddr.sin_family = AF_INET;
	svAddr.sin_port = htons (m_URL.getPort());

	struct hostent *pHostEntry = NULL;

	/* probably this is the host-name of the server we are connecting to */
	if ((pHostEntry = gethostbyname (m_URL.getHostName())))
	{
	    svAddr.sin_addr.s_addr =
		((struct in_addr *) pHostEntry->h_addr)->s_addr;
	}
	else
	{
	    /* no this is the IP address */
	    svAddr.sin_addr.s_addr = inet_addr (m_URL.getHostName());
	}

	/* connect to the remote server. */
	if (connect (m_Sock, (struct sockaddr *) &svAddr,
		     sizeof (svAddr)) == SOCKET_ERROR)
	{
	    closeChannel ();
            /*Cannot open a channel to the remote end, shutting down the channel*/
	    throw AxisTransportException(SERVER_TRANSPORT_SOCKET_CONNECT_ERROR);
	}
    }
    else
    {
	closeChannel ();
        /* Sockets error Couldn't create socket*/
	throw AxisTransportException(SERVER_TRANSPORT_SOCKET_CREATE_ERROR);
    }

    return true;
}

/*
 * OS specific initialization should do here
 *
 * @return  true if successfuly initilaize OS specific stuffs. false o/w
 */

bool
Channel::Init ()
{
#ifdef WIN32

    WSADATA wsaData;		/* contains vendor-specific information, such as the
				 * maximum number of sockets available and the maximum
				 * datagram size.
				 */
    if (WSAStartup (WS_VERSION_REQD, &wsaData))
	/* Filled by Windows Sockets DLLs */
    {
	m_LastErr = "WinSock DLL not responding.";
	//Error ((char *) m_LastErr.c_str ());
	return false;
    }
    else
    {
	/* Query to see whether the available version matches what we need */
	if ((LOBYTE (wsaData.wVersion) < WS_VERSION_MAJOR ()) ||
	    (LOBYTE (wsaData.wVersion) == WS_VERSION_MAJOR () &&
	     HIBYTE (wsaData.wVersion) < WS_VERSION_MINOR ()))
	{
	    char buf[100];
	    sprintf (buf,
		     "Windows Sockets version %d.%d not supported by winsock2.dll",
		     LOBYTE (wsaData.wVersion), HIBYTE (wsaData.wVersion));
	    Error (buf);
	    closeChannel ();
	    return false;
	}
    }
#else
    /* cout << "no need for linux" << endl; */
    /* other OS specific Intitialization goes here */
#endif

    return true;
}

/*
 * Write/send a message to the remote server; sending blocks the app.
 * we may need to do this asynchronizely; preferably either non-blocking
 * send or pthread.
 *
 * @param    Message to be written to the open channel
 */
const Channel &
Channel::operator << (const char *msg)
{
    if (INVALID_SOCKET == m_Sock)
    {
	
	/*Writing cannot be done without having a open socket to remote end*/
	throw AxisTransportException(SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int size = strlen (msg), nByteSent;

    if ((nByteSent = send (m_Sock, msg, size, MSG_DONTROUTE)) == SOCKET_ERROR)
    {
	/*Output streaming error while writing data*/
	closeChannel ();
	throw AxisTransportException(SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR);
    }

    return *this;
}

/*
 * Read/receive a message from the remote server; reading may be done in 
 * chunks.
 * @param    string to hold the read Message 
 */

const Channel &
Channel::operator >> (std::string & msg)
{
    msg = "";
    if (INVALID_SOCKET == m_Sock)
    {
	/* Reading cannot be done without having a open socket
           Input streaming error on undefined channel; please open the channel first
         */
	throw AxisTransportException (SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int nByteRecv = 0;
    const int BUF_SIZE = 1024;
    char buf[BUF_SIZE];

    //assume timeout not set; set default tatus to OK
    int iTimeoutStatus = 1;

    //check if timeout set
    if(m_lTimeoutSeconds)
        iTimeoutStatus = applyTimeout();

    //handle timeout outcome
    if(iTimeoutStatus < 0)//error
    {
        //select SOCKET_ERROR. Channel error while waiting for timeout
        throw AxisTransportException(SERVER_TRANSPORT_TIMEOUT_EXCEPTION, 
                                     "Channel error while waiting for timeout");        
        
    }

    if(iTimeoutStatus == 0)//timeout expired
    {
        /*"select timeout expired.
         *Channel error connection timeout before receving
        */
        throw AxisTransportException(SERVER_TRANSPORT_TIMEOUT_EXPIRED, 
                                     "Channel error: connection timed out before receving");
    }

    //either timeout was not set or data available before timeout; so read

    if ((nByteRecv = recv (m_Sock, (char *) &buf, BUF_SIZE - 1, 0))
	== SOCKET_ERROR)
    {
	/*recv SOCKET_ERROR, Channel error while getting data*/
	/* closeChannel(); */
	throw AxisTransportException(SERVER_TRANSPORT_INPUT_STREAMING_ERROR, 
                                     "Channel error while getting data");
	/* throw AxisTransportException(SERVER_TRANSPORT_INPUT_STREAMING_ERROR); 
	 */
    }
    if (nByteRecv)
    {
	/* printf("nByteRecv:%d\n", nByteRecv); */
	buf[nByteRecv] = '\0';
	/* got a part of the message, so add " \        "to form */
	msg = buf;
	/* printf("buf:%s\n", buf); */
    }
    else
	;//printf ("execution break\n");
    
    return *this;
}

const Channel &
Channel::readNonBlocking( std::string & msg, bool bBlockingRequired)
{
    msg = "";
    if (INVALID_SOCKET == m_Sock)
    {
	/*Reading cannot be done without having a open socket*/
	throw AxisTransportException(SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int nByteRecv = 0;
    const int BUF_SIZE = 1024;
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

//samisa

/*
 *    Close, and clean-up any OS specific stuff
 *
 */

void
Channel::closeChannel ()
{
    if (INVALID_SOCKET == m_Sock) // Check if socket already closed : AXISCPP-185
        return;
#ifdef WIN32
    closesocket (m_Sock);

    /* Check for any possible error conditions from WSACleanup() and report
     * them before exiting, as this information might indicate a network
     * layer problem in the system.
     */

    WSACleanup ();
#else
    ::close (m_Sock);

#endif
    m_Sock = INVALID_SOCKET; // fix for AXISCPP-185
}

/*
 * Log any errors that cause on channel usage/initilaization
 *
 */

void
Channel::Error (const char *err)
{
#ifdef _DEBUG
    std::cerr << err << std::endl;
#endif
}

void Channel::setTimeout(const long lSeconds)
{
    m_lTimeoutSeconds = lSeconds;
}

int Channel::applyTimeout()
{
    fd_set set;
    struct timeval timeout;

    /* Initialize the file descriptor set. */
    FD_ZERO(&set);
    FD_SET(m_Sock, &set);

    /* Initialize the timeout data structure. */
    timeout.tv_sec = m_lTimeoutSeconds;
    timeout.tv_usec = 0;

    /* select returns 0 if timeout, 1 if input available, -1 if error. */
    return select(FD_SETSIZE, &set, NULL, NULL, &timeout);
}

// This is used by SimpleAxisServer
void Channel::setSocket(unsigned int uiNewSocket)
{
    m_Sock = uiNewSocket;
}
