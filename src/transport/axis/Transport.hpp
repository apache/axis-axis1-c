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
 *
 *
 * @author Lilantha Darshana (lilantha@virtusa.com)
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

#if !defined(_AXIS_TRANSPORT_HPP)
#define _AXIS_TRANSPORT_HPP

#include "Url.hpp"
    
/**
 * 
 *    Implements Transport as SOAP-Envelop carrier, for sending/receiving
 *    SOAP Envelops with any protocol; This implementation abstract the 
 *    Transport layer for the SOAP payloads
 *    
 *    @brief     The Transport interface for SOAP envelop carrier 
 *
 */

class Transport  
{
public:
    Transport();
    virtual ~Transport();

    virtual bool Init() { return false;}      /* Initialize transport channel */
    virtual void Fini(){};
    virtual bool GetStatus(const std::string& payload){return m_bStatus;}
    virtual void SetProperty(const char* p_Property, const char* p_Value)=0;


    virtual const Transport& operator >> (const char** pMsg){*pMsg=NULL;return *this;}
    virtual const Transport& operator << (const char* msg)=0;
    virtual void ClearAdditionalHeaders(){};
    virtual int getBodyLength() = 0;
    virtual void setBodyLength(int bodyLength) = 0;
    virtual int getIsHttpHeader() = 0;
    virtual void setProxy(const char* pcProxyHost, unsigned int uiProxyPort) = 0;
  /**
    * Set transport timeout.
    *
    * @param lSeconds Timeout in seconds
    */
    virtual void setTimeout(const long lSeconds) = 0;

protected:

    Url m_Url;
    std::string m_strUrl;           
    bool m_bStatus;

};

#endif


