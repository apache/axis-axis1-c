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
 * @author Damitha Kumarage (damitha@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

/*
 * Revision 1.2  2004/06/08 samisa
 * Added setTimeout
 */

#if !defined(_AXIS_AXIS_TRANSPORT_HPP)
#define _AXIS_AXIS_TRANSPORT_HPP

#include "../SOAPTransport.h"
#include "Sender.hpp"
#include "Receiver.hpp"
#include <string>

class AxisTransport : public SOAPTransport
{
public:
    AxisTransport();
    virtual ~AxisTransport();
    int openConnection();
    void closeConnection();
    AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, const void* pBufferId);
	void registerReleaseBufferCallback(AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pFunct)
	{ m_pReleaseBufferCallback = pFunct; };
    AXIS_TRANSPORT_STATUS getBytes(char* pcBuffer, int* piSize);
    void setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType, const char* pcValue);
    const char* getTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType);
    void setTransportProperty(const char* pcKey, const char* pcValue);
    const char* getTransportProperty(const char* pcKey){return "value";};
	void setAttachment(const char* pcAttachmentId, const char* pcAttachment){};
	const char* getAttachment(const char* pcAttachmentId){return "value";};
	void setEndpointUri(const char* pcEndpointUri)
	{m_pcEndpointUri = strdup(pcEndpointUri);};
	void setSessionId(const char* pcSessionId){};
	const char* getSessionId(){return "some session id";};
	const char* getServiceName();
	AXIS_PROTOCOL_TYPE getProtocol();
	int getSubProtocol();
	AXIS_TRANSPORT_STATUS flushOutput();
	
  /**
    * Set proxy server and port for transport.
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    void setProxy(const char* pcProxyHost, unsigned int uiProxyPort); 

  /**
    * Set transport timeout.
    *
    * @param lSeconds Timeout in seconds
    */
    void setTimeout(const long lSeconds);

/*
    static AXIS_TRANSPORT_STATUS AXISCALL s_Send_bytes(const char* pSendBuffer,
        const void* bufferid, const void* pSStream);
    static AXIS_TRANSPORT_STATUS AXISCALL s_Get_bytes(const char** res, 
        int* retsize, const void* pSStream);
    static void AXISCALL s_SetTransportInformation
        (AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value, 
        const void* pSStream);
    static const char* AXISCALL s_ReceiveTransportInformation
        (AXIS_TRANSPORT_INFORMATION_TYPE type, const void* pSStream);
    static void AXISCALL s_ReleaseReceiveBuffer(const char* buffer, 
        const void* pSStream);
*/
private:
    Transport* m_pHttpTransport;
    Sender* m_pSender;
    Receiver* m_pReceiver;
	int m_iBytesLeft;
	const char* m_pcReceived;
    std::string m_sBytesToSend; 
  /**
    * Proxy server name.
    */
    std::string m_strProxyHost;
  /**
    * Proxy server port.
    */
    unsigned int m_uiProxyPort;
  /**
    * Use Proxy or not?
    */
    bool m_bUseProxy;


};

#endif

    
