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
 *
 */

#include "../platforms/PlatformAutoSense.hpp"

#include "SOAPTransportFactory.h"
#include "../transport/SOAPTransport.h"
#include <stdio.h>
#include "../common/AxisConfig.h"
#include "AxisEngineException.h"
#include "../common/AxisTrace.h"
                                                                                                                             
extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

AXIS_CPP_NAMESPACE_START

const char* SOAPTransportFactory::m_pcLibraryPath = 0;
DLHandler SOAPTransportFactory::m_LibHandler = 0;
CREATE_OBJECT1 SOAPTransportFactory::m_Create = 0;
DELETE_OBJECT1 SOAPTransportFactory::m_Delete = 0;
//void(*SOAPTransportFactory::m_startEventLoop)(void) = NULL;
//void(*SOAPTransportFactory::m_stopEventLoop)(void) = NULL;

SOAPTransportFactory::SOAPTransportFactory()
{
	m_LibHandler = 0;
}

SOAPTransportFactory::~SOAPTransportFactory()
{

}

int SOAPTransportFactory::initialize()
{
	m_pcLibraryPath = g_pConfig->getAxisConfProperty(AXCONF_TRANSPORTHTTP);

	if (!loadLib())
	{
        m_Create = (CREATE_OBJECT1) PLATFORM_GETPROCADDR(m_LibHandler, CREATE_FUNCTION1);
        m_Delete = (DELETE_OBJECT1) PLATFORM_GETPROCADDR(m_LibHandler, DELETE_FUNCTION1);

        if (!m_Create || !m_Delete)
        {
            unloadLib();
            AXISTRACE1("SERVER_ENGINE_LOADING_TRANSPORT_FAILED", CRITICAL);
            char *s = new char[strlen(m_pcLibraryPath)+1];
            strcpy(s,m_pcLibraryPath);
            throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED,  s);
        }
        else
        {
            // Load function to do lib level inits
            void (*initializeLibrary) (AxisTraceEntrypoints&);
            initializeLibrary = (void (*)(AxisTraceEntrypoints&))PLATFORM_GETPROCADDR(m_LibHandler, INIT_FUNCTION);

            AxisTraceEntrypoints ep;
            AxisTrace::getTraceEntrypoints(ep);
            if (initializeLibrary)
                 (*initializeLibrary)(ep);

/*
            // Load functions that does start and stop of event loop
            m_startEventLoop = (void (*)(void))PLATFORM_GETPROCADDR(m_LibHandler, START_EVENT_LOOP_FUNCTION);
            m_stopEventLoop = (void (*)(void))PLATFORM_GETPROCADDR(m_LibHandler, STOP_EVENT_LOOP_FUNCTION);
*/
        }		
	}
	else
	{
        AXISTRACE1("SERVER_ENGINE_LOADING_TRANSPORT_FAILED", CRITICAL);
        char *s = new char[strlen(m_pcLibraryPath)+1];
        strcpy(s,m_pcLibraryPath);
        throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED,  s);
	}
	return AXIS_SUCCESS;
}

int SOAPTransportFactory::uninitialize()
{
   void (*uninitializeLibrary) (void);
   uninitializeLibrary = (void (*)(void))PLATFORM_GETPROCADDR(m_LibHandler, UNINIT_FUNCTION);
   if (uninitializeLibrary)
        (*uninitializeLibrary)();
	return unloadLib();
}

/**
 * Should create an instance of transport of type given by eProtocol
 */
SOAPTransport* SOAPTransportFactory::getTransportObject(AXIS_PROTOCOL_TYPE eProtocol)
{
	SOAPTransport* pTpt;
	m_Create(&pTpt);
        pTpt->setProtocol(eProtocol);
	return pTpt;
}

void SOAPTransportFactory::destroyTransportObject(SOAPTransport* pObject)
{
	m_Delete(pObject);
}

int SOAPTransportFactory::loadLib()
{
    m_LibHandler = PLATFORM_LOADLIB(m_pcLibraryPath);

    if (!m_LibHandler)
    {
        AXISTRACE1("SERVER_ENGINE_LOADING_TRANSPORT_FAILED", CRITICAL);
        throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED, PLATFORM_LOADLIB_ERROR);
    }
    return AXIS_SUCCESS;
}

int SOAPTransportFactory::unloadLib()
{
    PLATFORM_UNLOADLIB(m_LibHandler);

    return AXIS_SUCCESS;
}

/*
void SOAPTransportFactory::startEventLoop()
{
    if (m_startEventLoop)
        (*m_startEventLoop)();
}

void SOAPTransportFactory::stopEventLoop()
{
    if (m_stopEventLoop)
        (*m_stopEventLoop)();
}
*/

AXIS_CPP_NAMESPACE_END

