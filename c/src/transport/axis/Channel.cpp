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
 *
 */
#include "Platform.hpp"
#include "Channel.hpp"
#include <iostream>
#include <stdio.h>
#include "Transport.hpp"

using namespace std;
/**
 * Create a Channel & initialize
 * 
 */

Channel::Channel() : m_Sock(INVALID_SOCKET)
{

}

Channel::~Channel()
{
    CloseChannel();
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

bool Channel::Open(std::string& p_RemoteNode, unsigned short p_RemoteEnd) 
              throw (ChannelException)
{
    m_RemoteNode = p_RemoteNode;
    m_RemoteEnd  = p_RemoteEnd;

    if(!Init())
        throw ChannelException("Cannot initialize a channel to the remote \
        end");

    sockaddr_in clAddr, svAddr;              

    if ((m_Sock = socket(PF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET)
    {
        clAddr.sin_family = AF_INET;   /* AF_INET (address family Internet). */
        clAddr.sin_port   = 0;         /* No Specify Port required */
        clAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(m_Sock, (struct sockaddr*) &clAddr, sizeof(clAddr)) == SOCKET_ERROR)
        {
            Error("Error - Binding");
            CloseChannel();
            throw ChannelException("Cannot open a channel to the remote end, \
                shutting down the channel");
        }

        /* Although the above fragment makes use of the bind() API, it would be
         * just as effective to skip over this call as there are no specific
         * local port ID requirements for this client. The only advantage that
         * bind() offers is the accessibility of the port which the system 
         * chose via the .sin_port member of the cli_addr structure which will 
         * be set upon success of the bind() call.
         */

        svAddr.sin_family = AF_INET;
        svAddr.sin_port   = htons(m_RemoteEnd);

        struct hostent*  pHostEntry = NULL;

        /* probably this is the host-name of the server we are connecting to */
        if((pHostEntry = gethostbyname(m_RemoteNode.c_str())))
        {
            svAddr.sin_addr.s_addr = ((struct in_addr *)pHostEntry->h_addr)
                ->s_addr;
        }
        else
        {
            /* no this is the IP address */
            svAddr.sin_addr.s_addr = inet_addr(m_RemoteNode.c_str());    
        }

        /* connect to the remote server. */
        if (connect(m_Sock,(struct sockaddr*)&svAddr, 
            sizeof(svAddr)) == SOCKET_ERROR)
        {
            Error("Sockets error Couldn't connect socket.");
            CloseChannel();
            throw ChannelException("Cannot open a channel to the remote end, \
                shutting down the channel");
        }
    }
    else
    {
        Error("Sockets error Couldn't create socket.");
        CloseChannel();
        throw ChannelException("Cannot open a channel");
    }
    
    return true;
}

/*
 * OS specific initialization should do here
 *
 * @return  true if successfuly initilaize OS specific stuffs. false o/w
 */

bool Channel::Init()
{
#ifdef WIN32

    WSADATA wsaData;     /* contains vendor-specific information, such as the
                          * maximum number of sockets available and the maximum
                          * datagram size.
                          */
    if(WSAStartup(WS_VERSION_REQD, &wsaData))  
    /* Filled by Windows Sockets DLLs */
    {
        m_LastErr = "WinSock DLL not responding.";
        Error((char *)m_LastErr.c_str());
        return false;
    }
    else
    { 
        /* Query to see whether the available version matches what we need */
        if (( LOBYTE (wsaData.wVersion) < WS_VERSION_MAJOR()) ||
             (LOBYTE (wsaData.wVersion) == WS_VERSION_MAJOR() &&
              HIBYTE (wsaData.wVersion) < WS_VERSION_MINOR()))
        {
            char buf[100];
            sprintf(buf,
                "Windows Sockets version %d.%d not supported by winsock2.dll",
                        LOBYTE (wsaData.wVersion), HIBYTE (wsaData.wVersion));
            Error(buf);
            CloseChannel();
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
const Channel& Channel::operator << (const char* msg)
{
    if(INVALID_SOCKET == m_Sock) 
    {
        Error("Writing cannot be done without having a open socket to remote \
            end.");
        throw ChannelException("Output streaming error on undefined channel; \
            please open the channel first");
    }

    int size = strlen(msg), nByteSent;
    
    if((nByteSent = send(m_Sock, msg, size, MSG_DONTROUTE )) == SOCKET_ERROR)
    {
        Error("Output streaming error while writing data.");
        CloseChannel();
        throw ChannelException("Output streaming error on Channel while \
            writing data");
    }

    return *this;
}

/*
 * Read/receive a message from the remote server; reading may be done in 
 * chunks.
 * @param    string to hold the read Message 
 */

const Channel& Channel::operator >> (std::string& msg)
{
    msg = "";
        if(INVALID_SOCKET == m_Sock)
        {
                Error("Reading cannot be done without having a open socket.");
                throw ChannelException("Input streaming error on " \
        "undefined channel; please open the channel first");
        }

        int nByteRecv = 0;
        const int BUF_SIZE = 1024;
        char buf[BUF_SIZE];

        if ((nByteRecv = recv(m_Sock, (char *) &buf, BUF_SIZE - 1, 0)) 
        == SOCKET_ERROR)
        {
            perror("recv SOCKET_ERROR");
                Error("Channel error while getting data.");
                /* CloseChannel(); */
                return *this;
                /* throw ChannelException("Input streaming error on Channel " \
                 * "while getting data"); 
                 */
    }
        if(nByteRecv)
        {
        /* printf("nByteRecv:%d\n", nByteRecv); */
                buf[nByteRecv] = '\0';  
                /* got a part of the message, so add " \        "to form */
                msg = buf;
                /* printf("buf:%s\n", buf); */
    }
        else
            printf("execution break\n");

         return *this;
}
                

/*
 *    Close, and clean-up any OS specific stuff
 *
 */

void Channel::CloseChannel()
{
#ifdef WIN32
    if(INVALID_SOCKET != m_Sock)
        closesocket(m_Sock);
    
    /* Check for any possible error conditions from WSACleanup() and report
     * them before exiting, as this information might indicate a network
     * layer problem in the system.
     */

    WSACleanup();
#else
    if(INVALID_SOCKET != m_Sock)
        close(m_Sock);

#endif
}

/*
 * Log any errors that cause on channel usage/initilaization
 *
 */

void Channel::Error(const char * err)
{
#ifdef _DEBUG
    std::cerr << err << std::endl;
#endif
}




