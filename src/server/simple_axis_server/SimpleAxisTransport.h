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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

#if !defined(SIMPLE_AXIS_TRANSPORT_H__OF_AXIS_INCLUDED_)
#define SIMPLE_AXIS_TRANSPORT_H__OF_AXIS_INCLUDED_

#ifdef WIN32
#include <winsock2.h>
#else
#include    <sys/socket.h>
#include    <sys/types.h>
#endif
#include    <string.h>
#include "../../transport/SOAPTransport.h"
#include    <string>

AXIS_CPP_NAMESPACE_USE class SimpleAxisTransport:public SOAPTransport
{
  public:
    SimpleAxisTransport (int iSocket);
    virtual ~ SimpleAxisTransport ();
    int openConnection ()
    {
	return AXIS_SUCCESS;
    };
    void closeConnection ()
    {
    };
    AXIS_TRANSPORT_STATUS sendBytes (const char *pcSendBuffer,
				     const void *pBufferId);
    void registerReleaseBufferCallback
	(AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pFunct)
    {
	m_pReleaseBufferCallback = pFunct;
    };
    AXIS_TRANSPORT_STATUS getBytes (char *pBuffer, int *piSize);
    void releaseBuffer (const char *pBuffer);
    void setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE type,
			       const char *value);
    const char *getTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType);
    void setTransportProperty (const char *pcKey, const char *pcValue);
    const char *getTransportProperty (const char *pcKey);
    void setAttachment (const char *pcAttachmentid, const char *pcAttachment)
    {
    };
    const char *getAttachment (const char *pcAttachmentid)
    {
	return "value";
    };
    void setEndpointUri (const char *pcEndpointUri)
    {
      m_pcEndpointUri = new char[strlen(pcEndpointUri)+1]; 
      strcpy(m_pcEndpointUri,pcEndpointUri);
    };
    void setSessionId (const char *pcSessionId);
    const char *getSessionId ();
    const char *getServiceName ();
    AXIS_PROTOCOL_TYPE getProtocol ();
    int setProtocol(AXIS_PROTOCOL_TYPE eProtocol);
    int getSubProtocol ();
    AXIS_TRANSPORT_STATUS flushOutput ();
  /**
    * Set transport timeout.
    * TODO: need to implement
    *
    * @param lSeconds Timeout in seconds
    */
    void setTimeout (const long lSeconds)
    {
    };

  private:
    int m_iSocket;
    BufferInfo *m_pBuffers;
    std::string m_strHTTPHeaders;
    bool m_bReadPastHeaders;
    std::string m_strPayloadToSend;
    std::string m_strServiceURI;
    std::string m_strReceived;
    std::string m_strSOAPAction;
    std::string m_strTransportPropertyURI;
    std::string m_strTransportPropertyOperation;
    void readFromClient ();

};

#endif //SIMPLE_AXIS_TRANSPORT_H__OF_AXIS_INCLUDED_

