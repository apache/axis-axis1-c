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
#include "SecureChannel.h"
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
    void setEndpointUri (const char *) throw (AxisTransportException);
    int openConnection ();
    void closeConnection ();
    AXIS_TRANSPORT_STATUS sendBytes (const char *, const void *);
    
    AXIS_TRANSPORT_STATUS getBytes (char *, int *) throw (AxisException,
							  AxisTransportException);
    void setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE,
			       const char *) throw (AxisTransportException);
    const char *getTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE)
	throw (AxisTransportException);
    void setTransportProperty (const char *,
			       const char *) throw (AxisTransportException);
    const char *getTransportProperty (const char *pcKey)
	throw (AxisTransportException);
    void setAttachment (const char *pcAttachmentId, const char *pcAttachment) {};
    
    const char *getAttachment (const char *pcAttachmentId) {};
    
    void setSessionId (const char *pcSessionId);
    
    const char *getSessionId ();
    
    const char *getServiceName ();
    AXIS_PROTOCOL_TYPE getProtocol ();
    int setProtocol(AXIS_PROTOCOL_TYPE eProtocol);
    int getSubProtocol ();
    AXIS_TRANSPORT_STATUS flushOutput () throw (AxisTransportException);

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
    * @return HTTP Method in use - POST, GET etc.
    */
    const char *getHTTPMethod ();

  /**
    * Set HTTP Method to use
    * @param cpMethod - Possible values POST, GET, etc. 
    *        Only POST is handled correctly at the moment
    */
    void setHTTPMethod (const char *);

    const char *getHTTPHeaders ();

    // This is used by SimpleAxisServer
    void setSocket (unsigned int);
    
    /**
    * Iterator initiatior for trasport property keys
    *
    * This method must be called first to initiate access to the list of 
    * transport property keys.
    *
    * @return First transport property key. If there are no trasport 
    * properties set, returns NULL.
    */
    const char* getFirstTrasportPropertyKey();

  /**
    * Iterator for trasport property keys
    *
    * getFirstTrasportPropertyKey() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method advances the iterator by one position.
    * Repeated calls always retuen the next value.
    *
    * @return Next transport property key. If there are no trasport 
    * properties set or if iterator is at the end of the list, returns NULL.
    */
    const char* getNextTrasportPropertyKey();

  /**
    * Accessor for trasport property keys.
    *
    * This method gives access to the key corresponding to the trasport key
    * currently being pointed by trasport property key iterator.
    *
    * getFirstTrasportPropertyKey() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method does not advance the iterator.
    * Repeated calls always retuen the same key unless 
    * getNextTrasportPropertyKey() is called in between.
    *
    * @return Current transport property key. If there are no trasport 
    * properties set or if iterator is at the end of the list, returns NULL.
    */
    const char* getCurrentTrasportPropertyKey();
    
  /**
    * Accessor for trasport property values.
    *
    * This method gives access to the value corresponding to the trasport key
    * currently being pointed by trasport property key iterator.
    * As keys and values are treated as paires, access to the value field is 
    * based on the access to the key field.
    *
    * getFirstTrasportPropertyKey() method must have been called at least once
    * before this method is called. If not behaviour is undefined.
    *
    * This method does not advance the iterator.
    * Repeated calls always retuen the same value unless 
    * getNextTrasportPropertyKey() is called in between.
    *
    * @return Current transport property value. If there are no trasport 
    * properties set or if iterator is at the end of the list, returns NULL.
    */
    const char* getCurrentTrasportPropertyValue();

  /**
    * Deletes the trasport property key:value pair currently pointed to by 
    * the iterator.
    */
    void deleteCurrentTrasportProperty();

  /**
    * Deletes the given occerance of the trasport property key:value pair
    * corresponding to the given key.
    *
    * This method does not advance the iterator in line with the deletes done.
    * In case you want to access the trasport properties after using this
    * method, it is advisable to reinitialize the iterator using
    * getFirstTrasportPropertyKey();
    * However you can use this method despite where the iterator is 
    * pointing currently.
    *
    * @param pcKey Key of the trasport property key:value pair to be deleted
    *              If the given key is not set currently, nothing will happen.
    * @param uiOccurance Which occerance of the key to be deleted, because 
    *                    there can be multiple values for the same key. 
    *                    Default is to delete the first occurance.
    *                    Count starts from 1.
    */
    void deleteTrasportProperty(char* pcKey, unsigned int uiOccurance = 1);

  /**
    * Set whether to Maitain session with service ot not.
    * @param bSession - true is session should be maintained. False otherwise.
    */
    virtual void setMaintainSession(bool bSession);


  private:
    void processResponseHTTPHeaders ();
    int FindTransportPropertyIndex (std::string);

  /**
    * Keeps track of if we need to reopen connection.
    * Set true by setEndpointUri.
    * Set false when a socket connection is established with the enpoint and 
    * when there is no need renew (that is close and open again) an existing connection.
    */
    bool m_bReopenConnection;

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
    * Trasport header iterator
    */
    vector <std::pair < std::string, std::string > >::iterator m_viCurrentHeader;
    
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
    std::vector < std::pair < std::string,
	std::string > >m_vResponseHTTPHeaders;

  /**
    * Channel used for communication
    */
    Channel *m_pChannel;	
    
    bool m_bChannelSecure;
    
  /**
    * Message header string to be sent.
    */
    std::string m_strHeaderBytesToSend;	
    
  /**
    * Should the Stub maintain session with service?
    */
    bool m_bMaintainSession;

  /**
    * Session key sent by service 
    */
    std::string m_strSessionKey;

    
};

#endif
