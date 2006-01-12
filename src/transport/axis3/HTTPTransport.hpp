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
 */

/*
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 * @author hawkeye (hawkinsj@uk.ibm.com) - improved cookie support
 * 
 * KNOWN LIMITATIONS: 
 * Cookie support: 
 * 1) Cookies are maintained over the life time of a connection only and are not persisted.
 * 2) We ignore expires, path, domain, secure attributes
 * 
 */

#if !defined(_AXIS_AXIS_TRANSPORT_HPP)
#define _AXIS_AXIS_TRANSPORT_HPP

#include "../SOAPTransport.h"
#include "HTTPTransportException.hpp"
#include "IChannel.hpp"
#include "ChannelFactory.hpp"
#include <string>
#include <vector>

AXIS_CPP_NAMESPACE_USE using namespace std;

int axtoi (char *hexStg);

typedef enum
{
	eWaitingForHTTPHeader,
	eSOAPMessageIsChunked,
	eSOAPMessageIsNotChunked
} EGETBYTESSTATE;

class HTTPTransport:public SOAPTransport
{
  public:
    HTTPTransport ();
    virtual ~ HTTPTransport ();

  /**
    * Sets the endpoint URI. 
    * Keeps track of the changes made to the URI. (Because if the URI changes, 
    * we cannot reuse the opned socket)
    * @param pcEndPointURI End point URI of the service to connect to.
    *                       e.g. http://localhost:8080/axis/services/echo
    */
    void					setEndpointUri( const char * pszEndpointURI) throw (HTTPTransportException);
    int						openConnection();
    void					closeConnection();
    AXIS_TRANSPORT_STATUS	sendBytes( const char *, const void *);
    AXIS_TRANSPORT_STATUS	getBytes( char *, int *) throw (AxisException, HTTPTransportException);
    int						setTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE, const char *) throw (HTTPTransportException);
    const char *			getTransportProperty( AXIS_TRANSPORT_INFORMATION_TYPE) throw (HTTPTransportException);
    int						setTransportProperty( const char *, const char *) throw (HTTPTransportException);
    const char *			getTransportProperty( const char * pcKey, bool response=true) throw (HTTPTransportException);
    void					setSessionId( const char * pcSessionId);
    const char *			getSessionId();
    const char *			getServiceName ();
    /* HTTPTransport::getProtocol() Is a public method to return the HTTP protocol
	 * type.
	 *
	 * @return AXIS_PROTOCOL_TYPE Type is an enumerated type for valid HTTP
	 * protocols
	 */
    AXIS_PROTOCOL_TYPE		getProtocol();
    /* HTTPTransport::setProtocol() Is a public method to set the HTTP protocol
	 * type.
	 *
	 * @return AXIS_SUCCESS if the set worked and the protocol is supported AXIS_FAIL otherwise
	 */
    int						setProtocol( AXIS_PROTOCOL_TYPE eProtocol);
    int						getSubProtocol();
    AXIS_TRANSPORT_STATUS	flushOutput() throw (AxisException, HTTPTransportException);
    void					setProxy( const char *pcProxyHost, unsigned int uiProxyPort);
    void					setTimeout( const long lSeconds);
    const char *			getHTTPProtocol();
    const char *			getHTTPMethod();
    void					setHTTPMethod( const char *);
    const char *			getHTTPHeaders();
    void					setSocket( unsigned int);
    const char *			getFirstTransportPropertyKey(bool response);
    const char *			getNextTransportPropertyKey(bool response);
    const char *			getCurrentTransportPropertyKey(bool response);
    const char *			getCurrentTransportPropertyValue(bool response);
    void					deleteCurrentTransportProperty(bool response=true);
    void					deleteTransportProperty( char* pcKey, unsigned int uiOccurance = 1);
    virtual void			setMaintainSession( bool bSession);

    void					setAttachment( const char * pcAttachmentId, const char * pcAttachment) {};
	ISoapAttachment *		getAttachment( const char * pcAttachmentId) { return NULL;};
    ISoapAttachment**       getAllAttachments(int *pAttchArraySize) { return NULL;}; 
    char *					getIncomingSOAPMimeHeaders() {return NULL;}
	const char *			getLastChannelError();

  protected:
    void					processResponseHTTPHeaders() throw (HTTPTransportException);
    void					processRootMimeBody();
    void					processMimeHeader();
    void					processMimeBody();
    void					getAttachment( char* pStrAttachment, int* pIntSize, int intAttachmentId);
    int						FindTransportPropertyIndex( std::string);
	void					readHTTPHeader();
	void					processHTTPHeader();
	void					checkHTTPStatusCode();
	bool					getNextDataPacket( const char * pcszExceptionMessage);
	int						getChunkSize();
	bool					copyDataToParserBuffer( char * pcBuffer, int * piSize, int iBytesToCopy);
	int						peekChunkLength( std::string& strNextChunk);
    /**
     * Adds a cookie to the http header. 
     * 
     * @param name name of the cookie
     * @param value value of the cookie
     * @return AXIS_SUCCESS if the cookie was added succesfully. False otherwise
     */
    int                    addCookie(const string name, const string Value);
    
    /**
     * Adds the name value pair to the cookie list
     * @param nameValuepair in the format name=value
     * @return AXIS_SUCCESS if the cookie was added succesfully false otherwise.
     */
    int addCookie(const string nameValuePair);
    
    /**
     * removes the known cookie
     * @param name - the name of the cookie to be removed
     * @return AXIS_SUCCESS if the cookie and was there and was removed AXIS_FAIL otherwise
     */
     int removeCookie(const string name);
     
     /**
      * If the user passes "Cookie" into deleteTransportProperty() then we remove all cookies
      * This is a convenient internal method to do that.
      * @return AXIS_SUCCESS if all cookies were removed or AXIS_FAIL otherwise
      */
     int removeAllCookies();
     /**
      * Utility function - Removes whitespace from around the given string
      */            
     void trim(string& str);
     
    
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
    * Transport header iterator for the request headers
    */
    vector <std::pair < std::string, std::string > >::iterator m_viCurrentHeader;

  /**
    * Transport header iterator for the reply headers
    */
    vector <std::pair < std::string, std::string > >::iterator m_viCurrentResponseHeader;
    
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
    unsigned int m_iBytesLeft;

  /**
    * Payload length
    */
    unsigned int m_iContentLength;

  /**  
    * String holding what we received over the channel
    */
    std::string m_strReceived;

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
    IChannel *	m_pNormalChannel;
    IChannel *	m_pSecureChannel;
    IChannel *	m_pActiveChannel;
    bool		m_bChannelSecure;

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

  /**
   * Cookies set and to be sent to the server.
   */
  std::vector < std::pair < std::string, std::string > >m_vCookies;
  
  /** 
    * Content-Type holder
    */
    std::string m_strContentType;

  /**
    * Mime Boundary value
    */
    std::string m_strMimeBoundary;

  /**
    * Mime type value
    */
    std::string m_strMimeType;

  /**
    * Mime start value
    */
    std::string m_strMimeStart;

  /**
    * Received payload is a mime struct
    */
    bool m_bMimeTrue;

    bool m_bReadPastRootMimeHeader;
    std::string m_strMimeContentType;
    std::string m_strMimeContentTransferEncoding;
    std::string m_strMimeContentID;
    std::string m_strMimeContentLocation; 
    std::string m_strMimeReceived;
    ChannelFactory* m_pChannelFactory;

	char *	m_pszRxBuffer;

	long	m_lChannelTimeout;

	std::string	m_strBuffered;

  /**
    * New getBytes variables
	*/
	EGETBYTESSTATE	m_GetBytesState;
};

#endif
