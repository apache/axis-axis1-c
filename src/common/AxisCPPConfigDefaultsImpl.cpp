/* -*- C++ -*- */
/*
 *   Copyright 2005 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2005 All Rights Reserved
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
 *   @author John Kelly (john_kelly@uk.ibm.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "AxisCPPConfigDefaultsImpl.hpp"
#include "AxisUtils.h"
#include "AxisConfig.h"
#include "AxisConfigException.h"

#include "AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;
AXIS_CPP_NAMESPACE_START 

AxisCPPConfigDefaultsImpl::AxisCPPConfigDefaultsImpl ()
{
  m_pcClientLog = "";
  m_pcClientWSDDFile = "";
  m_pcXMLParserLibrary = "";
  m_pcHTTPTransportLibrary = "";
  m_pcHTTPChannelLibrary = "";
  m_pcHTTPSSLChannelLibrary = "";
  m_pcNodeName = "";
  m_pcListenPort = "";
  m_pcSecureInfo = "";
  m_pcAxisHome = "";

}

AxisCPPConfigDefaultsImpl::~AxisCPPConfigDefaultsImpl ()
{
}

void AxisCPPConfigDefaultsImpl::apply ()
{
  /* only allow user to apply once befor initialization and NOT AT ALL after */
  if(!g_pConfig)
  {
      char *pszValue=0;
      g_pConfig = new AxisConfig ();
      //todo set each value, if set
      pszValue = getClientLog();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_CLIENTLOGPATH, pszValue);

      pszValue = getClientWSDDFile();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_WSDDFILEPATH, pszValue);

      pszValue = getXMLParserLibrary();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_XMLPARSER, pszValue);

      pszValue = getHTTPTransportLibrary();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_TRANSPORTHTTP, pszValue);

      pszValue = getHTTPChannelLibrary();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_CHANNEL_HTTP, pszValue);

      pszValue = getHTTPSSLChannelLibrary();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_SSLCHANNEL_HTTP, pszValue);

      pszValue = getNodeName();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_NODENAME, pszValue);

      pszValue = getListenPort();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_LISTENPORT, pszValue);

      pszValue = getSecureInfo();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_SECUREINFO, pszValue);

      pszValue = getAxisHome();
      if(pszValue)
          g_pConfig->setValue(0,AXCONF_AXISHOME, pszValue);
  }
  else
  {
      AXISTRACE1 ("configuration defaults aleady set", WARN);
      throw AxisConfigException(CONFIG_DEFAULTS_ALREADY_SET);
  }
}

void AxisCPPConfigDefaultsImpl::setClientLog (char *value)
{
    m_pcClientLog = value;
}
void AxisCPPConfigDefaultsImpl::setClientWSDDFile (char *value)
{
    m_pcClientWSDDFile = value;
}
void AxisCPPConfigDefaultsImpl::setXMLParserLibrary (char *value)
{
    m_pcXMLParserLibrary = value;
}
void AxisCPPConfigDefaultsImpl::setHTTPTransportLibrary (char *value)
{
    m_pcHTTPTransportLibrary = value;
}
void AxisCPPConfigDefaultsImpl::setHTTPChannelLibrary (char *value)
{
    m_pcHTTPChannelLibrary = value;
}
void AxisCPPConfigDefaultsImpl::setHTTPSSLChannelLibrary (char *value)
{
    m_pcHTTPSSLChannelLibrary = value;
}
void AxisCPPConfigDefaultsImpl::setNodeName (char *value)
{
    m_pcNodeName = value;
}
void AxisCPPConfigDefaultsImpl::setListenPort (char *value)
{
    m_pcListenPort = value;
}
void AxisCPPConfigDefaultsImpl::setSecureInfo (char *value)
{
    m_pcSecureInfo = value;
}
void AxisCPPConfigDefaultsImpl::setAxisHome (char *value)
{
    m_pcAxisHome = value;
}


char* AxisCPPConfigDefaultsImpl::getClientLog ()
{
    if (0 == m_pcClientLog.length()) return NULL;
    return (char*)(m_pcClientLog.c_str());
}
char* AxisCPPConfigDefaultsImpl::getClientWSDDFile ()
{
    if (0 == m_pcClientWSDDFile.length()) return NULL;
    return (char*)(m_pcClientWSDDFile.c_str());
}
char* AxisCPPConfigDefaultsImpl::getXMLParserLibrary ()
{
    if (0 == m_pcXMLParserLibrary.length()) return NULL;
    return (char*)(m_pcXMLParserLibrary.c_str());
}
char* AxisCPPConfigDefaultsImpl::getHTTPTransportLibrary ()
{
    if (0 == m_pcHTTPTransportLibrary.length()) return NULL;
    return (char*)(m_pcHTTPTransportLibrary.c_str());
}
char* AxisCPPConfigDefaultsImpl::getHTTPChannelLibrary ()
{
    if (0 == m_pcHTTPChannelLibrary.length()) return NULL;
    return (char*)(m_pcHTTPChannelLibrary.c_str());
}
char* AxisCPPConfigDefaultsImpl::getHTTPSSLChannelLibrary ()
{
    if (0 == m_pcHTTPSSLChannelLibrary.length()) return NULL;
    return (char*)(m_pcHTTPSSLChannelLibrary.c_str());
}
char* AxisCPPConfigDefaultsImpl::getNodeName ()
{
    if (0 == m_pcNodeName.length()) return NULL;
    return (char*)(m_pcNodeName.c_str());
}
char* AxisCPPConfigDefaultsImpl::getListenPort ()
{
    if (0 == m_pcListenPort.length()) return NULL;
    return (char*)(m_pcListenPort.c_str());
}
char* AxisCPPConfigDefaultsImpl::getSecureInfo ()
{
    if (0 == m_pcSecureInfo.length()) return NULL;
    return (char*)(m_pcSecureInfo.c_str());
}
char* AxisCPPConfigDefaultsImpl::getAxisHome ()
{
    if (0 == m_pcAxisHome.length()) return NULL;
    return (char*)(m_pcAxisHome.c_str());
}

/** /todo place some sample code here
*/

AXIS_CPP_NAMESPACE_END
