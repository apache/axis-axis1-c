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
 *
 *
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
 *
 */

#if !defined(AXIS_APACHETRANSPORT_H__OF_AXIS_INCLUDED_)
#define AXIS_APACHETRANSPORT_H__OF_AXIS_INCLUDED_

#define SIZEOFTRANSPORTBUFFER 256

#include <apache1_3/httpd.h>
#include <apache1_3/http_config.h>
#include <apache1_3/http_core.h>
#include <apache1_3/http_log.h>
#include <apache1_3/http_protocol.h>
#include <apache1_3/http_main.h>
#include <axis/SOAPTransport.h>
#include <string.h>

class ApacheTransport : public SOAPTransport  
{
public:
	ApacheTransport(void* pContext);
	virtual ~ApacheTransport();
    int openConnection(){return AXIS_SUCCESS;};
    void closeConnection(){};
    AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, const void* pBufferId);
	void registerReleaseBufferCallback(AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pFunct)
	{ m_pReleaseBufferCallback = pFunct; };
    AXIS_TRANSPORT_STATUS getBytes(char* pBuffer, int* piSize);
	void releaseBuffer(const char* pBuffer);
    void setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value);
    const char* getTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType);
    void setTransportProperty(const char* pcKey, const char* pcValue);
    const char* getTransportProperty(const char* pcKey);
	void setAttachment(const char* pcAttachmentid, const char* pcAttachment){};
	const char* getAttachment(const char* pcAttachmentid){return "value";};
	void setEndpointUri(const char* pcEndpointUri)
	{m_pcEndpointUri = strdup(pcEndpointUri);};
	void setSessionId(const char* pcSessionId);
	const char* getSessionId();
	const char* getServiceName();
	AXIS_PROTOCOL_TYPE getProtocol();
	int getSubProtocol();
	AXIS_TRANSPORT_STATUS flushOutput();
private:
	void* m_pContext;
	char m_Buffer[SIZEOFTRANSPORTBUFFER];
#ifndef CHUNCKED_DATA_SUPPORTED
    BufferInfo* m_pBuffers;
#endif
};

#endif 
