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
    //hints.ai_family = PF_INET6;
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    char port[7];
    sprintf(port, "%hd", m_URL.getPort());
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

