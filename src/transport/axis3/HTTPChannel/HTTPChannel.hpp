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

#if !defined(_AXIS_AXIS_CHANNEL_HPP)
#define _AXIS_AXIS_CHANNEL_HPP

#include <stdio.h>
#include <string>

// Platform specific stuff
#ifdef WIN32
#include "..\IChannel.hpp"
#include "..\URL.hpp"
#include "..\HTTPTransportException.hpp"
#include <winsock2.h>

#ifdef IPV6
#include <ws2tcpip.h>
#endif

#ifndef EINPROGRESS
#define EINPROGRESS WSAEINPROGRESS
#endif

// What version of WinSock is required
const int    WS_VERSION_REQD    = 0x0101;

// Macros to get version major & minor
inline int WS_VERSION_MAJOR() {return HIBYTE(WS_VERSION_REQD);}
inline int WS_VERSION_MINOR() {return LOBYTE(WS_VERSION_REQD);}

#else
#include "../IChannel.hpp"
#include "../URL.hpp"
#include "../HTTPTransportException.hpp"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int          INVALID_SOCKET = -1;
const int          SOCKET_ERROR   = -1;

// Other OS specific stuff goes here
#endif

AXIS_CPP_NAMESPACE_USE using namespace std;

class HTTPChannel:public IChannel
{
public:
    HTTPChannel();
    virtual ~HTTPChannel();

    const char *        getURL();
    virtual void        setURL( const char * cpURL);
    virtual URL &       getURLObject();
    bool                open();
    bool                close();
    const std::string & GetLastErrorMsg();
    int                 readBytes(char *buf, int bufLen);
    int                 writeBytes(const char *buf, int numBytes);
    void                setTimeout( long lSeconds);
    void                setConnectTimeout( long lSeconds);
    void                setSocket( unsigned int uiNewSocket);
    int                 getSocket() {return m_Sock;}
    bool                setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char * value);
    const char *        getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type);
    void                setProxy( const char * pcProxyHost, unsigned int uiProxyPort);
    bool                reopenRequired() { return (INVALID_SOCKET == m_Sock); }
    void                closeQuietly( bool bNoExceptionOnForceClose);
    void                enableTrace(const char* logFilePath, const char *filters);


protected:
    bool                OpenChannel();
    void                CloseChannel();
    bool                StartSockets();
    void                StopSockets();
    int                 applyTimeout(long seconds, bool isRead);
    void                ReportError(bool isConnectError=false);

private:
    URL             m_URL;                      // URL
    string          m_LastError;                // Last error
#ifdef WIN32
    unsigned 
#endif
    int             m_Sock;                     // Socket descriptor
    bool            m_bUseProxy;                // Use a Proxy?
    std::string     m_strProxyHost;             // Proxy server name.
    unsigned int    m_uiProxyPort;              // Proxy server port.
    long            m_lTimeoutSeconds;          // Timeout in seconds
    long            m_lConnectTimeoutSeconds;   // Connect timeout in seconds
    bool            bNoExceptionOnForceClose;   // If the socket is forcably closed, usually an
                                                // exception is thrown.  When this flag is set,
                                                // nothing happens (but the m_Sock is set to 0).
};

#endif
