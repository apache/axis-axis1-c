// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "SecureChannel.hpp"

SecureChannel::SecureChannel()
{
    //m_pFactory = new SSLChannelFactory();
    //m_pFactory->initialize();
    //m_pSSLChannel = m_pFactory->getSSLChannelObject(); 
    //m_pSSLChannel->SSLInit();
}

SecureChannel::~SecureChannel()
{
}

bool SecureChannel::open() throw (AxisTransportException&)
{
    //m_pSSLChannel = m_pFactory->getSSLChannelObject(); 
    //m_pSSLChannel->SSLInit();
    //Channel::open();
    //m_pSSLChannel->openSSLConnection(&m_Sock); 
    return true;
}

void SecureChannel::close()
{
}

const Channel & SecureChannel::operator << (const char * msg) throw (AxisTransportException)
{
    //m_pSSLChannel->SSLWrite(msg, &m_Sock);
    return *this;
}

const Channel &SecureChannel::operator >> (std::string & msg) throw (AxisTransportException)
{
    //m_pSSLChannel->SSLRead(msg);
    return *this;
}

void SecureChannel::setSecureProperties( const char * psSSLArgs)
{
	//string * ps = (string *) psSSLArgs;
}

const char * SecureChannel::getSecureProperties()
{
	const char * pSSLProperty = "SecureProperty";

	return pSSLProperty;
}

int SecureChannel::setTransportProperty (AXIS_TRANSPORT_INFORMATION_TYPE type,
    const char* value)
{
    //if(DLL_NAME == type)
    //    m_pFactory->initialize(value);
    //m_pFactory->setTransportProperty(type, value);
    return AXIS_SUCCESS;
}

