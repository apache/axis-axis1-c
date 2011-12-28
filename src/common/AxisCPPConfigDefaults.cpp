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
void AxisCPPConfigDefaults::setClientLog (const char *value)
{
    m_pImpl->setClientLog(value);
}
void AxisCPPConfigDefaults::setClientWSDDFile (const char *value)
{
    m_pImpl->setClientWSDDFile(value);
}
void AxisCPPConfigDefaults::setXMLParserLibrary (const char *value)
{
    m_pImpl->setXMLParserLibrary(value);
}
void AxisCPPConfigDefaults::setHTTPTransportLibrary (const char *value)
{
    m_pImpl->setHTTPTransportLibrary(value);
}
void AxisCPPConfigDefaults::setHTTPChannelLibrary (const char *value)
{
    m_pImpl->setHTTPChannelLibrary(value);
}
void AxisCPPConfigDefaults::setHTTPSSLChannelLibrary (const char *value)
{
    m_pImpl->setHTTPSSLChannelLibrary(value);
}
void AxisCPPConfigDefaults::setNodeName (const char *value)
{
    m_pImpl->setNodeName(value);
}
void AxisCPPConfigDefaults::setListenPort (const char *value)
{
    m_pImpl->setListenPort(value);
}
void AxisCPPConfigDefaults::setSecureInfo (const char *value)
{
    m_pImpl->setSecureInfo(value);
}
void AxisCPPConfigDefaults::setAxisHome (const char *value)
{
    m_pImpl->setAxisHome(value);
}



const char* AxisCPPConfigDefaults::getClientLog ()
{
    return m_pImpl->getClientLog();
}
const char* AxisCPPConfigDefaults::getClientWSDDFile ()
{
    return m_pImpl->getClientWSDDFile();
}
const char* AxisCPPConfigDefaults::getXMLParserLibrary ()
{
    return m_pImpl->getXMLParserLibrary();
}
const char* AxisCPPConfigDefaults::getHTTPTransportLibrary ()
{
    return m_pImpl->getHTTPTransportLibrary();
}
const char* AxisCPPConfigDefaults::getHTTPChannelLibrary ()
{
    return m_pImpl->getHTTPChannelLibrary();
}
const char* AxisCPPConfigDefaults::getHTTPSSLChannelLibrary ()
{
    return m_pImpl->getHTTPSSLChannelLibrary();
}
const char* AxisCPPConfigDefaults::getNodeName ()
{
    return m_pImpl->getNodeName();
}
const char* AxisCPPConfigDefaults::getListenPort ()
{
    return m_pImpl->getListenPort();
}
const char* AxisCPPConfigDefaults::getSecureInfo ()
{
    return m_pImpl->getSecureInfo();
}
const char* AxisCPPConfigDefaults::getAxisHome ()
{
    return m_pImpl->getAxisHome();
}


AXIS_CPP_NAMESPACE_END
