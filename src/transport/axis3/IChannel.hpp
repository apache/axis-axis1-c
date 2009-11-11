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

#if !defined(_AXIS_ICHANNEL_HPP)
#define _AXIS_ICHANNEL_HPP

#include <string>
#include <axis/GDefine.hpp>
#include "URL.hpp"
#include "HTTPTransportException.hpp"

// Need to revisit this, but for now ifdef for OS/400
#ifndef __OS400__
  const int BUF_SIZE = 1024 * 8;
#else
  const int BUF_SIZE = 1024 * 32;
#endif

using namespace std;

AXIS_CPP_NAMESPACE_USE

// =================================================================
// In order to parse the HTTP protocol data on an ebcdic system, we
// need to ensure that the various tokens we are looking for to distinguish
// between the HTTP headers and payload are in ASCII.  So the following 
// defines for carriage return-line feed, etc. are ensured to be in ascii
// by using ascii hexadecimal representation of the tokens.
// =================================================================

// Ascii character defines                   
#define ASCII_C_EQUAL         '\x3D'    // '='  
#define ASCII_C_DASH          '\x2D'    // '-'  
#define ASCII_C_LF            '\x0A'    // '\n'
#define ASCII_C_CR            '\x0D'    // '\r' 
#define ASCII_C_SPACE         '\x20'    // ' ' 
#define ASCII_C_SEMI          '\x3B'    // ';' 

#define ASCII_C_LOWERCASEA    '\x61'    // 'a'
#define ASCII_C_LOWERCASEF    '\x66'    // 'f'
#define ASCII_C_UPPERCASEA    '\x41'    // 'A'
#define ASCII_C_UPPERCASEF    '\x46'    // 'F'

#define ASCII_C_ZERO          '\x30'    // '0'
#define ASCII_C_NINE          '\x39'    // '9'

// Ascii string defines
#define ASCII_S_LF             "\x0a"               // "\n"     
#define ASCII_S_CRLF           "\x0d\x0a"           // "\r\n"     
#define ASCII_S_CRLFCRLF       "\x0d\x0a\x0d\x0a"   // "\r\n\r\n"

#define ASCII_S_HTTP           "\x48\x54\x54\x50"   // "HTTP"

#define ASCII_S_LEFTPAREN      "\x28"               // "("

enum g_ChannelType 
{
    UnsecureChannel,
    SecureChannel,
    MaxChannelCount
};

class IChannel
{
public:
    virtual                    ~IChannel() {};
    virtual const char*         getURL()=0;
    virtual void                setURL( const char* cpURL)=0;
    virtual URL &               getURLObject()=0;
    virtual bool                open()=0;
    virtual bool                close()=0;
    virtual const std::string&  GetLastErrorMsg()=0;
    virtual int                 readBytes(char *buf, int bufLen)=0;
    virtual int                 writeBytes(const char *buf, int numBytes)=0;
    virtual int                 setSecureProperties( const char *) {return true;};
    virtual const char *        getSecureProperties() {return NULL;};
    virtual void                setTimeout( long lSeconds)=0;
    virtual void                setSocket( unsigned int uiNewSocket)=0;
    virtual int                 getSocket()=0;
    virtual bool                setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value)=0;
    virtual const char *        getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE type)=0;
    virtual void                setProxy(const char *pcProxyHost,unsigned int uiProxyPort)=0;
    virtual bool                reopenRequired()=0;
    virtual void                closeQuietly( bool bNoExceptionOnForceClose) = 0;
    virtual void                enableTrace(const char* logFilePath, const char *filters) { }
};

#endif

