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

#ifdef WIN32
    m_lTimeoutSeconds = 10;
#endif
}

IPV6Channel::~IPV6Channel ()
{
    // If the socket value is not invalid, then close the socket before
    // deleting the IPV6Channel object.
    if( m_Sock != INVALID_SOCKET)
    {
        closeChannel();
    }

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
    // if there is an open socket already, close it first
    if (m_Sock != INVALID_SOCKET)
        closeChannel();

    // If the underlying socket transport has not been initialised properly,
    // then thrown an exeption.
    if( !init())
    {
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
   
    const char* host = m_URL.getHostName();
    unsigned int uiPort = m_URL.getPort();
    if (m_bUseProxy)
    {
        uiPort = m_uiProxyPort;
        host = m_strProxyHost.c_str();
    }
 
    sprintf(port, "%hd", uiPort);
    int err = getaddrinfo(host, port, &hints, &addrInfo0);
    if (err)
    {

        throw AxisTransportException( SERVER_TRANSPORT_SOCKET_CREATE_ERROR);
    }

    for (addrInfo = addrInfo0 ; addrInfo ;  addrInfo = addrInfo->ai_next)
    {
        m_Sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, addrInfo->ai_protocol);
        if (m_Sock < 0)
        {
            continue;
        }

        if (connect(m_Sock, addrInfo->ai_addr, addrInfo->ai_addrlen) < 0)
        {
            // Cannot open a channel to the remote end, shutting down the
            // channel and then throw an exception.
            closeChannel();

            free (addrInfo0);
            throw AxisTransportException( SERVER_TRANSPORT_SOCKET_CONNECT_ERROR);
            continue;
        }
        break;
    }

    // Samisa: free addrInfo0 - no longer needed
    free (addrInfo0);

    if (m_Sock < 0)
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
 * IPV6Channel::init() Operating System specific initialization for sockets
 *
 * @return  bool True if successfully initialised the OS specifics.
 *				 False if unsuccessful
 */

bool IPV6Channel::init ()
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
        m_LastErr = "WinSock DLL not addrInfoponding.";


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

