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

/**
 * This class 
 *
 * @author damitha kumarage (damitha@hsenid.lk, damitha@opensource.lk)
 *
 */

#if !defined(_AXIS_SSLCHANNEL_HPP)
#define _AXIS_SSLCHANNEL_HPP
//#include <axis/server/Packet.hpp>
#include "SOAPTransport.h"
#include <string>
AXIS_CPP_NAMESPACE_USE
class SSLChannel
{
public:
    virtual ~SSLChannel(){};
    virtual bool SSLInit() = 0;
    virtual bool openSSLConnection(unsigned int* pSock) = 0;
    virtual int SSLRead(std::string& msg) = 0;
    virtual int SSLWrite(const std::string& msg, unsigned int* pSock) = 0; 
    virtual void closeSSLChannel() = 0;
    virtual void setSSLError(int) = 0;
    virtual void setSSLError(char*) = 0;
    virtual char* getSSLError() = 0;
 
};
#endif

