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

#include "../Platform.h"
#include "IPV6Channel.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;

IPV6Channel::IPV6Channel ()
{
#ifdef FJPDebug
    printf( ">IPV6Channel::IPV6Channel()\n");
#endif

#ifdef WIN32

    m_lTimeoutSeconds = 10;
#endif

#ifdef FJPDebug
    printf( "<IPV6Channel::IPV6Channel()\n");
#endif
}

IPV6Channel::~IPV6Channel ()
{
#ifdef FJPDebug
    printf( ">IPV6Channel::~IPV6Channel()\n");
#endif

    // If the socket value is not invalid, then close the socket before
    // deleting the IPV6Channel object.
    if( m_Sock != INVALID_SOCKET)
    {
        closeChannel();
    }

#ifdef FJPDebug
    printf( "<IPV6Channel::~IPV6Channel()\n");
#endif
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
IPV6Channel::open () //std::string & p_RemoteNode, unsigned short p_RemoteEnd)
throw (AxisTransportException&)
{
#ifdef FJPDebug
    printf( ">IPV6Channel::open()\n");
#endif
    // if there is an open socket already, close it first
    if (m_Sock != INVALID_SOCKET)
        closeChannel();

    // If the underlying socket transport has not been initialised properly,
    // then thrown an exeption.
    if( !init())
    {
#ifdef FJPDebug
        printf( "<IPV6Channel::open()=exception\n");
#endif

        throw AxisTransportException( SERVER_TRANSPORT_CHANNEL_INIT_ERROR);
    }

    struct addrinfo hints, *addrInfo, *addrInfo0;

    // hints is used after zero cleared
    memset(&hints, 0, sizeof(hints));
    //hints.ai_family = PF_INET;
    hints.ai_family = PF_INET6;
    hints.ai_socktype = SOCK_STREAM;

    char port[7];
    sprintf(port, "%ld", m_URL.getPort());
    int err = getaddrinfo(m_URL.getHostName(), port, &hints, &addrInfo0);
    if (err)
    {
#ifdef FJPDebug
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
#endif

        throw AxisTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR);
    }

    for (addrInfo = addrInfo0 ; addrInfo ;  addrInfo = addrInfo->ai_next)
    {
        m_Sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);
        if (m_Sock < 0)
        {
#ifdef FJPDebug
            fprintf(stderr, "socket() faild: %d\n", m_Sock);
#endif
            continue;
        }

        if (connect(m_Sock, addrInfo->ai_addr, addrInfo->ai_addrlen) < 0)
        {
            // Cannot open a channel to the remote end, shutting down the
            // channel and then throw an exception.
            closeChannel();

#ifdef FJPDebug
            printf( "<IPV6Channel::open()=exception\n");
#endif

            throw AxisTransportException( SERVER_TRANSPORT_SOCKET_CONNECT_ERROR);
            continue;
        }
        break;
    }

    if (m_Sock < 0)
    {
        // Sockets error Couldn't create socket.  Close the channel and throw
        // an exception.
        closeChannel();

#ifdef FJPDebug
        printf( "<IPV6Channel::open()=exeption\n");
        fprintf(stderr, "can't connect %s\n", m_URL.getHostName() );
#endif

        throw AxisTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR);
    }
 
#ifdef FJPDebug
    printf( "<IPV6Channel::open()=true, m_Sock=%d\n", m_Sock);
#endif

    return true;
}

/**
 * IPV6Channel::init() Operating System specific initialization for sockets
 *
 * @return  bool True if successfully initialised the OS specifics.
 *				 False if unsuccessful
 */

bool IPV6Channel::init ()
{
#ifdef FJPDebug
    printf( ">IPV6Channel::init()\n");
#endif

#ifdef WIN32

    WSADATA wsaData;	// Contains vendor-specific information, such as the
    // maximum number of sockets available and the maximum
    // datagram size.

    // wsaData filled by Windows Sockets DLLs.
    if( WSAStartup( WS_VERSION_REQD, &wsaData))
    {
        // Error - Could not setup underlying Windows socket transport
        //         mechanism.
        m_LastErr = "WinSock DLL not addrInfoponding.";

#ifdef FJPDebug
        printf( "<IPV6Channel::init()=false\n");
#endif

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

#ifdef FJPDebug
            printf( "<IPV6Channel::init()=false\n");
#endif

            return false;
        }
    }
#else
    /* cout << "no need for linux" << endl; */
    /* other OS specific Intitialization goes here */
#endif

#ifdef FJPDebug
    printf( "<IPV6Channel::init()=true\n");
#endif

    return true;
}

/**
 * IPV6Channel::operator << (Msg) Write (send) a message to the remote server.
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
 * @return const IPV6Channel & is the addaddrInfos of the IPV6Channel object (the 'this'
 * pointer).
 */
/*const Channel &IPV6Channel::operator << (const char *msg)
{
#ifdef FJPDebug
    printf( ">IPV6Channel::operator << msg=%s, ", msg);
#endif

    // Check that the Tx/Rx sockets are valid (this will have been done if the
    // application has called the open method first.
    if( INVALID_SOCKET == m_Sock)
    {
        // Error - Writing cannot be done without having a open socket to
        //         remote end.  Throw an exception.
#ifdef FJPDebug
        printf( "<IPV6Channel::operator << exception\n");
#endif

        throw AxisTransportException( SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int size = strlen( msg);
    int nByteSent;

    if( m_iMsgLength)
    {
        size = m_iMsgLength;
    }

#ifdef FJPDebug
    printf( "size=%d, m_Sock=%d\n", size, m_Sock);

    hexOutput( (char *) msg, size);
#endif

    if( (nByteSent = send( m_Sock, msg, size, MSG_DONTROUTE)) == SOCKET_ERROR)
    {
        // Output streaming error while writing data.  Close the channel and
        // throw an exception.
        closeChannel();

#ifdef FJPDebug
        printf( "<IPV6Channel::operator << exception\n");
#endif

        throw AxisTransportException(SERVER_TRANSPORT_OUTPUT_STREAMING_ERROR);
    }

#ifdef FJPDebug
    printf( "<IPV6Channel::operator <<\n");
#endif

    return *this;
}
*/

/**
 * IPV6Channel::operator >> (Msg) Read (receive) a message from the remote server;
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
 * @return const IPV6Channel & is the addaddrInfos of the IPV6Channel object (the 'this'
 * pointer).
 */
/*const Channel &IPV6Channel::operator >> (std::string & msg)
{
#ifdef FJPDebug
    printf( ">IPV6Channel::operator >> m_Sock=%d\n", m_Sock);
#endif

    msg = "";

    if (INVALID_SOCKET == m_Sock)
    {
        // Error - Reading cannot be done without having a open socket Input
        //         streaming error on undefined channel; please open the
        //		   channel first

#ifdef FJPDebug
        printf( "<IPV6Channel::operator >> exception=SERVER_TRANSPORT_INVALID_SOCKET\n");
#endif

        throw AxisTransportException( SERVER_TRANSPORT_INVALID_SOCKET);
    }

    int nByteRecv = 0;
    const int BUF_SIZE = 1024;
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

#ifdef FJPDebug
        printf( "<IPV6Channel::operator >> exception=SERVER_TRANSPORT_TIMEOUT_EXCEPTION\n");
#endif

        // Select SOCKET_ERROR. IPV6Channel error while waiting for timeout
        throw AxisTransportException( SERVER_TRANSPORT_TIMEOUT_EXCEPTION,
                                      "IPV6Channel error while waiting for timeout");
    }

    if( iTimeoutStatus == 0)
    {
        // Timeout expired - select timeout expired.
        // IPV6Channel error connection timeout before receving

#ifdef FJPDebug
        printf( "<IPV6Channel::operator >> exception=SERVER_TRANSPORT_TIMEOUT_EXPIRED\n");
#endif

        throw AxisTransportException( SERVER_TRANSPORT_TIMEOUT_EXPIRED,
                                      "IPV6Channel error: connection timed out before receving");
    }

    // Either timeout was not set or data available before timeout; so read

    if( (nByteRecv = recv( m_Sock, (char *) &buf, iBufSize, 0)) == SOCKET_ERROR)
    {
        // Recv SOCKET_ERROR, IPV6Channel error while getting data


#ifdef FJPDebug
        printf( "<IPV6Channel::operator >> exception=SERVER_TRANSPORT_INPUT_STREAMING_ERROR\n");
#endif

        throw AxisTransportException( SERVER_TRANSPORT_INPUT_STREAMING_ERROR,
                                      "IPV6Channel error while getting data");
    }

    if( nByteRecv)
    {
        // printf("nByteRecv:%d\n", nByteRecv); 
        buf[nByteRecv] = '\0';
        // got a part of the message, so add " \        "to form 
        msg = buf;

        if( m_iMsgLength < 0)
        {
            m_iMsgLength = nByteRecv;

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

#ifdef FJPDebug
    hexOutput( m_sMsg, m_iMsgLength);

    printf( "m_iMsgLength=%d\n", m_iMsgLength);
    printf( "<IPV6Channel::operator >> msg = %s\n", buf);
#endif

    return *this;
}
*/

/**
 * IPV6Channel::readNonBlocking( Msg, BlockingRequired) Read (receive) a message
 * from the remote server; Reading may be done in 'chunks'?
 *
 * @param string & Msg
 * @param bool BlockingRequired
 *
 * @return const IPV6Channel & is the addaddrInfos of the IPV6Channel object (the 'this'
 * pointer).
 */
/*const Channel &IPV6Channel::readNonBlocking( std::string & msg, bool bBlockingRequired)
{
    msg = "";
    if (INVALID_SOCKET == m_Sock)
    {
        //Reading cannot be done without having a open socket
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
        //IPV6Channel error while getting data
        return *this;
    }
    if (nByteRecv)
    {
        buf[nByteRecv] = '\0';
        msg = buf;
    }
    else
        Error( "IPV6Channel::readNonBlocking: execution break");

    return *this;
}
*/

/**
 * IPV6Channel::closeChannel() Close and clean-up using specific Operating System
 * calls.
 */
void IPV6Channel::closeChannel ()
{
#ifdef FJPDebug
    printf( ">IPV6Channel::closeChannel()\n");
#endif

    if( INVALID_SOCKET == m_Sock) // Check if socket already closed : AXISCPP-185
    {
#ifdef FJPDebug
        printf( "<IPV6Channel::closeChannel()\n");
#endif

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

#ifdef FJPDebug
    printf( "<IPV6Channel::closeChannel()\n");
#endif
}

/**
 * IPV6Channel::applyTimeout()
 *
 * @return int 
 */
int IPV6Channel::applyTimeout()
{
#ifdef FJPDebug
    printf( ">IPV6Channel::applyTimeout()\n");
#endif

    fd_set set
        ;
    struct timeval timeout;

    // Initialize the file descriptor set.
    FD_ZERO( &set
           );
    FD_SET( m_Sock, &set
          );

    /* Initialize the timeout data structure. */
    timeout.tv_sec = m_lTimeoutSeconds;
    timeout.tv_usec = 0;

    /* select returns 0 if timeout, 1 if input available, -1 if error. */
#ifdef FJPDebug
    printf( "<IPV6Channel::applyTimeout()\n");
#endif

    return select( FD_SETSIZE, &set
                   , NULL, NULL, &timeout);
}

/**
 * Debug routine will be deleted.
 */
void IPV6Channel::hexOutput( char * psData, int iDataLength)
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
