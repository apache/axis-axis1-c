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
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 *
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

/*
 * Revision 1.2  2004/06/08 samisa
 * Added setTimeout
 */

#if !defined(AXIS_SOAPTRANSPORT_H__OF_AXIS_INCLUDED_)
#define AXIS_SOAPTRANSPORT_H__OF_AXIS_INCLUDED_

#include <axis/server/Packet.h>

/**
 * 
 *
 * Each thread should have a different transport object
 */

#ifdef __cplusplus

class AxisIOStream
{
public:
	/**
	 * Used to send buffers to the transport layer. Axis Engine may call this method multiple 
	 * times. Its upto the transport to decide how they are sent (chunked/unchunked etc). This 
	 * method may return 3 status values. Meanings are given below
	 * TRANSPORT_FINISHED - Passed buffer has been sent. So the caller can re-use the buffer
     * TRANSPORT_IN_PROGRESS - Passed buffer is not sent. So the caller cannot re-use the buffer
     * TRANSPORT_FAILED - Transport layer has failed.
	 * In case this function returns TRANSPORT_IN_PROGRESS. The caller should wait till the transport
	 * layer calls the provided callback function with the bufferid to indicate that it can re-use
	 * the buffer.
	 */
    virtual AXIS_TRANSPORT_STATUS sendBytes(const char* pcSendBuffer, const void* pBufferid)=0;
	/**
	 * Used to get part of or all SOAP message. 
	 */
    virtual AXIS_TRANSPORT_STATUS getBytes(char* pcBuffer, int* piRetSize)=0;
};

class SOAPTransport : public AxisIOStream
{
public:
	virtual ~SOAPTransport(){};
    virtual int openConnection()=0;
    virtual void closeConnection()=0;
	/**
	 * Method used to register the callback function which is called by transport layer to inform
	 * Axis Engine that a buffer given to it is sent and it can be re-used by Axis Engine. 
	 * 
	 */
	virtual void registerReleaseBufferCallback(AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pFunct)=0;
    virtual void setTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType, const char* pcValue)=0;
    virtual const char* getTransportProperty(AXIS_TRANSPORT_INFORMATION_TYPE eType)=0;
    virtual void setTransportProperty(const char* pcKey, const char* pcValue)=0;
    virtual const char* getTransportProperty(const char* pcKey)=0;
	virtual void setAttachment(const char* pcAttachmentid, const char* pcAttachment)=0;
	virtual const char* getAttachment(const char* pcAttachmentid)=0;
	virtual void setEndpointUri(const char* pcEndpointUri)=0;
	virtual void setSessionId(const char* pcSessionId)=0;
	virtual const char* getSessionId()=0;
	virtual const char* getServiceName()=0;
	virtual AXIS_PROTOCOL_TYPE getProtocol()=0;
	virtual int getSubProtocol()=0; /* is this appropriate name ? */
	virtual AXIS_TRANSPORT_STATUS flushOutput()=0;
  /**
    * Set proxy server and port for transport.
    *
    * Setting the proxy is useful for users who are behind proxies.
    *
    * For some trasports this method may not make sense. 
    * Hence this method is not pure virtual.
    * Those trasports that implement this interface, that wish to use proxy, must provide an implementation.
    * Also, the hadling of the proxy is the responsibility of the deriving classes
    * 
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    virtual void setProxy(const char* pcProxyHost, unsigned int uiProxyPort) {}

  /**
    * Set transport timeout. 
    *
    * @param lSeconds Timeout in seconds
    */
    virtual void setTimeout(const long lSeconds) = 0; 

protected:
	char* m_pcEndpointUri; /* Outgoing endpoint URI */
	AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER m_pReleaseBufferCallback;

};

#endif

#endif // !defined(AXIS_SOAPTRANSPORT_H__OF_AXIS_INCLUDED_)
