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
 * @author 
 */


#if !defined(_AXIS_SECURECHANNEL_HPP)
#define _AXIS_SECURECHANNEL_HPP

#include <axis/server/AxisException.h>
#include "Channel.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>


class SecureChannel : public Channel
{
    public:
    SecureChannel();
    virtual ~SecureChannel();
    bool Open(std::string& p_RemoteNode, unsigned short p_RemoteEnd) 
        throw (ChannelException);
    const Channel& operator << (const std::string& msg);
    const Channel& operator >> (std::string& msg);
        /* Return last error (if any). */
    const std::string& GetLastError(){return m_LastErr;}

    /* Set the SOAP transport handler. */
    void SetTransportHandler(Transport* transport)
    {m_pTransportHandler = transport;}
    void CloseChannel();
    
    private:
    bool Init();
    void Error(const char * err);

    /* unsigned int    m_Sock;           // Socket descriptor
     std::string        m_RemoteNode;    // Remote address could be IP/hostname
     unsigned short    m_RemoteEnd;      // Remote port number
     std::string        m_LastErr;       // Last error as a string
     Transport    * m_pTransportHandler; // Transport handler for validation
    */
    SSL_CTX* m_sslContext;
    SSL* m_sslHandle;

};    

#endif
