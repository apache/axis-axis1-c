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

#include "axis/AxisCPPConfigDefaults.hpp"

#include "AxisCPPConfigDefaultsImpl.hpp"
#include "AxisUtils.h"

#include "AxisTrace.h"

AXIS_CPP_NAMESPACE_START 

AxisCPPConfigDefaults::AxisCPPConfigDefaults ()
{
    m_pImpl = new AxisCPPConfigDefaultsImpl(); 
}

AxisCPPConfigDefaults::~AxisCPPConfigDefaults ()
{
    delete m_pImpl;
}

void AxisCPPConfigDefaults::apply ()
{
    m_pImpl->apply();
}
void AxisCPPConfigDefaults::setClientLog (char *value)
{
    m_pImpl->setClientLog(value);
}
void AxisCPPConfigDefaults::setClientWSDDFile (char *value)
{
    m_pImpl->setClientWSDDFile(value);
}
void AxisCPPConfigDefaults::setXMLParserLibrary (char *value)
{
    m_pImpl->setXMLParserLibrary(value);
}
void AxisCPPConfigDefaults::setHTTPTransportLibrary (char *value)
{
    m_pImpl->setHTTPTransportLibrary(value);
}
void AxisCPPConfigDefaults::setHTTPChannelLibrary (char *value)
{
    m_pImpl->setHTTPChannelLibrary(value);
}
void AxisCPPConfigDefaults::setHTTPSSLChannelLibrary (char *value)
{
    m_pImpl->setHTTPSSLChannelLibrary(value);
}
void AxisCPPConfigDefaults::setNodeName (char *value)
{
    m_pImpl->setNodeName(value);
}
void AxisCPPConfigDefaults::setListenPort (char *value)
{
    m_pImpl->setListenPort(value);
}
void AxisCPPConfigDefaults::setSecureInfo (char *value)
{
    m_pImpl->setSecureInfo(value);
}
void AxisCPPConfigDefaults::setAxisHome (char *value)
{
    m_pImpl->setAxisHome(value);
}



char* AxisCPPConfigDefaults::getClientLog ()
{
    return(char*)m_pImpl->getClientLog();
}
char* AxisCPPConfigDefaults::getClientWSDDFile ()
{
    return(char*)m_pImpl->getClientWSDDFile();
}
char* AxisCPPConfigDefaults::getXMLParserLibrary ()
{
    return(char*)m_pImpl->getXMLParserLibrary();
}
char* AxisCPPConfigDefaults::getHTTPTransportLibrary ()
{
    return(char*)m_pImpl->getHTTPTransportLibrary();
}
char* AxisCPPConfigDefaults::getHTTPChannelLibrary ()
{
    return(char*)m_pImpl->getHTTPChannelLibrary();
}
char* AxisCPPConfigDefaults::getHTTPSSLChannelLibrary ()
{
    return(char*)m_pImpl->getHTTPSSLChannelLibrary();
}
char* AxisCPPConfigDefaults::getNodeName ()
{
    return(char*)m_pImpl->getNodeName();
}
char* AxisCPPConfigDefaults::getListenPort ()
{
    return(char*)m_pImpl->getListenPort();
}
char* AxisCPPConfigDefaults::getSecureInfo ()
{
    return(char*)m_pImpl->getSecureInfo();
}
char* AxisCPPConfigDefaults::getAxisHome ()
{
    return(char*)m_pImpl->getAxisHome();
}

/** /todo place some sample code here
*/

AXIS_CPP_NAMESPACE_END
