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

/**
 * This class 
 *
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 * @author damitha kumarage (damitha@hsenid.lk, damitha@opensource.lk)
 *
 */

#include "../../platforms/PlatformAutoSense.hpp"

#include "SSLChannelFactory.hpp"
#include "../SSLChannel.hpp"
#include <stdio.h>
#include "../../engine/AxisEngineException.h"
//#include "../../common/AxisTrace.h"
                                                                                                                             
//extern AXIS_CPP_NAMESPACE_PREFIX AxisTrace* g_pAT;
//extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

AXIS_CPP_NAMESPACE_START

const char* SSLChannelFactory::m_pcLibraryName = 0;
DLHandler SSLChannelFactory::m_LibHandler = 0;
CREATE_OBJECT3 SSLChannelFactory::m_Create = 0;
DELETE_OBJECT3 SSLChannelFactory::m_Delete = 0;

SSLChannelFactory::SSLChannelFactory()
{
	m_LibHandler = 0;
}

SSLChannelFactory::~SSLChannelFactory()
{

}

int SSLChannelFactory::initialize(const char* pcLibraryName)
{
    //m_pcLibraryName = g_pConfig->getAxisConfProperty(AXCONF_SSLCHANNEL);
      m_pcLibraryName = pcLibraryName;

	if (!loadLib())
	{
        m_Create = (CREATE_OBJECT3) PLATFORM_GETPROCADDR(m_LibHandler, CREATE_FUNCTION3);
        m_Delete = (DELETE_OBJECT3) PLATFORM_GETPROCADDR(m_LibHandler, DELETE_FUNCTION3);
        if (!m_Create || !m_Delete)
        {
            unloadLib();
            char *s = new char[strlen(m_pcLibraryName)+1];
            strcpy(s,m_pcLibraryName);
            throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED, s);
        }
	}
	else
	{
        char *s = new char[strlen(m_pcLibraryName)+1];
        strcpy(s,m_pcLibraryName);
        throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED, s);
	}
   return AXIS_SUCCESS;
}

int SSLChannelFactory::uninitialize()
{
	return unloadLib();
}

/**
 * Should create an instance of transport of type given by eProtocol
 */
SSLChannel* SSLChannelFactory::getSSLChannelObject()
{
	SSLChannel* pTpt = 0;
	if (m_Create) m_Create(&pTpt);
	return pTpt;
}

void SSLChannelFactory::destroySSLChannelObject(SSLChannel* pObject)
{
	m_Delete(pObject);
}

int SSLChannelFactory::loadLib()
{
    m_LibHandler = PLATFORM_LOADLIB(m_pcLibraryName);
    if (!m_LibHandler)
    {
        throw AxisEngineException(SERVER_ENGINE_LOADING_PARSER_FAILED);
    }

    return AXIS_SUCCESS;
}

int SSLChannelFactory::unloadLib()
{
    PLATFORM_UNLOADLIB(m_LibHandler);

    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
