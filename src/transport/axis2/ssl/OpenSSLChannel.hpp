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
 * @author damitha Kumarage (damitha@hsenid.lk, damitha@opensource.lk)
 *
 */

#if !defined(_AXIS_AXIS2_OPENSSLCHANNEL_HPP)
#define _AXIS_AXIS2_OPENSSLCHANNEL_HPP
#include "../../SSLChannel.hpp"
#include "../Channel.h"
#include "AxisSSLChannelException.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>
AXIS_CPP_NAMESPACE_START

class OpenSSLChannel: public SSLChannel
{
public:
   OpenSSLChannel(); 
   ~OpenSSLChannel();
   bool SSLInit();
   bool openSSLConnection(unsigned int* pSock);
   int SSLRead(std::string& msg);
   int SSLWrite(const std::string& msg, unsigned int* pSock);
   void closeSSLChannel();
   void setSSLError(int);
   void setSSLError(char*);
   char* getSSLError();

private:
   char* m_pcError;
   SSL_CTX* m_sslContext;
   SSL* m_sslHandle;
};

AXIS_CPP_NAMESPACE_END

#endif
