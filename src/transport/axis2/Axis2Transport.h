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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */


#if !defined(_AXIS_AXIS_TRANSPORT_HPP)
#define _AXIS_AXIS_TRANSPORT_HPP

#include "../SOAPTransport.h"
#include "Channel.h"
#include <string>
#include <vector>

AXIS_CPP_NAMESPACE_USE using namespace std;

int axtoi (char *hexStg);

class Axis2Transport:public SOAPTransport
{
  public:
    Axis2Transport ();
    virtual ~ Axis2Transport ();

  /**
    * Sets the endpoint URI. 
    * Keeps track of the changes made to the URI. (Because if the URI changes, 
    * we cannot reuse the opned socket)
    * @param pcEndPointURI End point URI of the service to connect to.
    *                       e.g. http://localhost:8080/axis/services/echo
    */
    void setEndpointUri (const char *pcEndpointUri);
    int openConnection ();
    void closeConnection ();
    AXIS_TRANSPORT_STATUS sendBytes (const char *pcSendBuffer,
				     const void *pBufferId);
    void registerReleaseBufferCallback
	(AXIS_ENGINE_CALLBACK_RELEASE_SEND_BUFFER pFunct)
    {
	m_pReleaseBufferCallback = pFunct;
    };
    AXIS_TRANSPORT_STATUS getBytes (char *pcBuffer, int *piSize);
    void setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType,
			       const char *pcValue);
    const char *getTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE eType);
    void setTransportProperty (const char *pcKey, const char *pcValue);
    const char *getTransportProperty (const char *pcKey)
    {
	return "value";
    };
    void setAttachment (const char *pcAttachmentId, const char *pcAttachment)
    {
    };
    const char *getAttachment (const char *pcAttachmentId)
    {
	return "value";
    };


    void setSessionId (const char *pcSessionId)
    {
    };
    const char *getSessionId ()
    {
	return "some session id";
    };
    const char *getServiceName ();
    AXIS_PROTOCOL_TYPE getProtocol ();
    int getSubProtocol ();
    AXIS_TRANSPORT_STATUS flushOutput ();

  /**
    * Set proxy server and port for transport.
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    void setProxy (const char *pcProxyHost, unsigned int uiProxyPort);

  /**
    * Set transport timeout.
    *
    * @param lSeconds Timeout in seconds
    */
    void setTimeout (const long lSeconds);

  /**
    * @return HTTP protocol in use - HTTP/1.1 or HTTP/1.0
    */
    const char *getHTTPProtocol ();

  /**
    * Sets the HTTP protocol to be 1.1 or 1.0
    * @param iVersion Version to be used 
    *        If 0 HTTP/1.0 would be used, if 1 HTTP/1.1 would be used.
    *        Default is HTTP1.1
    */
    void setHTTPProtocol (int iVersion);

  /**
    * @return HTTP Method in use - POST, GET etc.
    */
    const char *getHTTPMethod ();

  /**
    * Set HTTP Method to use
    * @param cpMethod - Possible values POST, GET, etc. 
    *        Only POST is handled correctly at the moment
    */
    void setHTTPMethod (const char *cpMethod);

    const char *getHTTPHeaders ();

    // This is used by SimpleAxisServer
    void setSocket(unsigned int uiNewSocket);

  private:
   
    void processResponseHTTPHeaders();

  /**
    * Keeps track of URI changes.
    * Set true by setEndpointUri.
    * Set false when a socket connection is established with the enpoint.
    */
    bool m_bURIChanged;

  /**
    * Channel used for comminication
    */
    Channel m_Channel;

  /**
    * Message string to be sent.
    */
    std::string m_strBytesToSend;

  /**
    * Message header to be sent.
    */
    std::string m_strHeaderToSend;

  /**
    * Vector to hold HTTP header key/value pairs
    */
    std::vector < std::pair < std::string, std::string > >m_vHTTPHeaders;
  /**
    * HTTP protocol (1.1 or 1.0). Default is HTTP/1.1
    */
    std::string m_strHTTPProtocol;
  /**
    * HTTP method (POST, GET etc.)  - Only support POST at the moment
    */
    std::string m_strHTTPMethod;

  /**
    * Bytes left in the payload buffer to be read
    */
    int m_iBytesLeft;

  /**
    * Payload lenght
    */
    unsigned int m_iContentLength;

  /**
    * Is the message chunked
    */
    int m_bChunked;

  /**  
    * String holding what we received over the channel
    */
    std::string m_strReceived;

  /**
    * Have we read past HTTP headers?
    */
    bool m_bReadPastHTTPHeaders;

  /**
    * Payload buffer
    */
    const char *m_pcReceived;

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
  /**
    * HTTP headers in response 
    */
    std::string m_strResponseHTTPHeaders;
  /**
    * HTTP protocol (1.1 or 1.0). Default is HTTP/1.1
    */
    std::string m_strResponseHTTPProtocol;
  /**
    * HTTP status code 
    */
    int m_iResponseHTTPStatusCode;
  /**
    * HTTP status code 
    */
    std::string m_strResponseHTTPStatusMessage;
  /**
    * Vector to hold response HTTP header key/value pairs
    */
    std::vector < std::pair < std::string, std::string > >m_vResponseHTTPHeaders;
};

#endif
