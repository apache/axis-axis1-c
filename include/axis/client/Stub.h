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
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

/*
 * This is the client Stub base class to be inherited by all stub classes
 * genarated by the tool WSDL2WS
 * Stub.h: interface for the Stubclass.
 *
 */

/*
 * Revision 1.1  2004/05/31 samisa
 * Added setProxy
 */

#if !defined(_STUB_H____OF_AXIS_INCLUDED_)
#define _STUB_H____OF_AXIS_INCLUDED_

#include <axis/client/Call.h>
#include <vector>

class Stub
{
  public:
    Stub (const char *pchEndpointUri);
    virtual ~ Stub ();
    int initilizeCall ();
    void setEndPoint (char *pcEndPoint);
    void setTransportProperty (const char *pcKey, const char *pcValue);
    IHeaderBlock *createHeaderBlock (AxisChar * pachLocalName,
				     AxisChar * pachPrefix,
				     AxisChar * pachUri);
  /**
    * Set proxy server and port for transport.
    *
    * @param pcProxyHost Host name of proxy server
    * @param uiProxyPort Port of proxy server
    */
    void setProxy(const char* pcProxyHost, unsigned int uiProxyPort);

  protected:
    void applyUserPreferences();
    void setTransportProperties();
    void setSOAPHeaders();
    void setProxy();

    Call *m_pCall;
    vector < char *>m_vKeys;
    vector < char *>m_vValues;
    vector < IHeaderBlock * >m_vSOAPHeaderBlocks;

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

#endif /* !defined(_STUB_H____OF_AXIS_INCLUDED_) */
