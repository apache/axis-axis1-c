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
 * @author Lilantha Darshana (lilantha@virtusa.com)
 * @author Damitha Kumarage (damitha@jkcsworld.com, damitha@opensource.lk)
 * @author Susantha Kumara (susantha@opensource.lk, skumara@virtusa.com)
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

#if !defined(_AXIS_HTTPTRANSPORT_HPP)
#define _AXIS_HTTPTRANSPORT_HPP

#include <sstream>
#include <string>
#include <vector>
#include "Transport.hpp"
#include "Channel.hpp"
#ifdef _SSL_ENABLED_
    #include "SecureChannel.hpp"
#endif
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;
#include <axis/AxisTransportException.h>

/*
 * Implements HTTP transport as SOAP-Envelop carrier, for sending/receiving
 * SOAP messages with HTTP 1.1/1.0; This implementation abstract the Transport
 * layer for the SOAP payloads
 *    
 * @brief     The HTTP transport implementation for SOAP 
 *
 */



class HttpTransport  : public Transport
{
public:
    /* HTTP category, Only POST is used currently, MPOST is not supported yet*/
    enum Type{POST, MPOST};

    /* Create HTTP transport with provided URL as remote address, set HTTP 
     * category default to POST 
     */

    /* HttpTransport(Url url) : m_Typ(POST) 
       {m_Url = url; m_IsHttpHeader = 0; m_HttpBindDone = false;} 
     */

    /* Create HTTP transport with provided remote address as URL-string, 
     * set HTTP category default to POST 
     */

    /* HttpTransport(std::string& strUrl) : m_Typ(POST) 
       {m_Url = Url(strUrl); m_IsHttpHeader = 0;m_strUrl = strUrl; 
       m_HttpBindDone = false;}
    */

    ~HttpTransport();

    HttpTransport(std::string& strUrl, int secure);
    
    HttpTransport(Url url, int secure);

    /* Initialize HTTP transport by establishing a channel to the remote end */
    bool  Init();

    /* Finish using this transport and close channel */
    void Fini();

    /* Obtain the status of the HTTP packet validity */
    bool  GetStatus(const std::string& p_HttpPacket);

    /* Set properties of HTTP transport such as additional Header fields like 
     * SOAPAction 
     */
    void  SetProperty(const char* p_Property, const char* p_Value);

    /* Read from a HTTP transport handler and store read payload */
    const Transport& operator >> (const char** pPayload);

    /* Write a given payload by using HTTP transport as carrier */
    const Transport& operator << (const char* p_Payload);
    int getBodyLength();
    void setBodyLength(int bodyLength);
    int getIsHttpHeader();

private:
    /* Build a HTTP packet with a given payload & additional HTTP properties */
    void HTTPBind();

    /* Validate HTTP packets received from the channel. */
    void HTTPValidate(const std::string& p_HttpPacket);

    /* Extract payload from the HTTP packet starting from a given offset */
    void GetPayLoad(const std::string& p_HttpPacket, 
        std::string::size_type& offset);

    /* Report error on read/write */
    void Error(const char * err);

    void ClearAdditionalHeaders();

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


private:

    typedef std::vector< std::pair<std::string, std::string> > Header_t;

    Type m_Typ;                      /* Type of the HTTP; POST or MPOST */

    std::string m_OutHttpHeaders;    /* Holds    outgoing HTTP packet */
    std::istringstream m_InMsg;      /* Holds    incoming HTTP packet */

    std::string m_PayLoad;           /* Holds the payload */
    Header_t    m_AdditionalHeader;
    /* Additional Header fields as name value pairs */
private:
    Channel* m_Channel;
    bool m_HttpBindDone;
    int m_IsHttpHeader;
    std::string m_sHeader;
    int m_intBodyLength;
    bool m_Secure;
  
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
    * Timeout in seconds
    */
    long m_lTimeoutSeconds;

};

#endif

