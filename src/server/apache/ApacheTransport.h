/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

/*
 * Revision 1.1  2004/06/08 samisa
 * Added setTimeout
 */

#if !defined(AXIS_APACHETRANSPORT_H__OF_AXIS_INCLUDED_)
#define AXIS_APACHETRANSPORT_H__OF_AXIS_INCLUDED_

#include <string>

#ifdef WIN32
#include <apache1_3/httpd.h>
#include <apache1_3/http_config.h>
#include <apache1_3/http_core.h>
#include <apache1_3/http_log.h>
#include <apache1_3/http_protocol.h>
#include <apache1_3/http_main.h>
#else
#include <httpd.h>
#include <http_config.h>
#include <http_core.h>
#include <http_log.h>
#include <http_protocol.h>
#include <http_main.h>
#endif

#include "../../transport/SOAPTransport.h"
//#include <string.h>
#include "AttachmentHelper.h"
#include <axis/ISoapAttachment.hpp>

AXIS_CPP_NAMESPACE_USE

class ApacheTransport : public SOAPTransport  
{
public:
	ApacheTransport(void* pContext);
	virtual ~ApacheTransport();
    int openConnection(){return AXIS_SUCCESS;};
    void closeConnection(bool forceClose=true){};
    AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, const void* pBufferId);
	void registerReleaseBufferCallback(AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pFunct)
	{ m_pReleaseBufferCallback = pFunct; };
    AXIS_TRANSPORT_STATUS getBytes(char* pBuffer, int* piSize);
	void releaseBuffer(const char* pBuffer);
    int setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE type, const char* value);
    const char* getTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType);
    int setTransportProperty(const char* pcKey, const char* pcValue);
    const char* getTransportProperty(const char* pcKey, bool response=true);
    void setAttachment(const char* pcAttachmentid, const char* pcAttachment){};
	
	
	/**
	 * fixing build breaks: Start
	 */
	
	// hawkeye: This should return something ? Asking on mailing list what !
	char* getIncomingSOAPMimeHeaders();
	
	// hawkeyeThis used to return "value" but now fails because of the changed signature
	// What should it be ?
	ISoapAttachment* getAttachment(const char* pcAttachmentid);
    ISoapAttachment** getAllAttachments(int *pAttchArraySize);

	/** 
	 * end of fixing build breaks
	 */
	void setEndpointUri(const char* pcEndpointUri)
	{m_pcEndpointUri = new char[strlen(pcEndpointUri)+1]; strcpy(m_pcEndpointUri,pcEndpointUri);};
	void setSessionId(const char* pcSessionId);
	const char* getSessionId();
	const char* getServiceName();
	AXIS_PROTOCOL_TYPE getProtocol();
    int setProtocol(AXIS_PROTOCOL_TYPE eProtocol);
	int getSubProtocol();
	AXIS_TRANSPORT_STATUS flushOutput();
  /**
    * Set transport timeout.
    * TODO: need to implement
    *
    * @param lSeconds Timeout in seconds
    */
    void setTimeout(long lSeconds) {};

private:
    AttachmentHelper* pAttachmentHelper;
	void* m_pContext;
    bool m_bHeadersSent;
#ifndef CHUNCKED_DATA_SUPPORTED
    BufferInfo* m_pBuffers;
#endif
};

#endif 
