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

#include "SOAPTransportFactory.h"
#include "../transport/SOAPTransport.h"
#include <stdio.h>
#include "../common/AxisConfig.h"
#include "AxisEngineException.h"
#include "../common/AxisTrace.h"
                                                                                                                             
extern AXIS_CPP_NAMESPACE_PREFIX AxisTrace* g_pAT;
extern AXIS_CPP_NAMESPACE_PREFIX AxisConfig* g_pConfig;

AXIS_CPP_NAMESPACE_START

const char* SOAPTransportFactory::m_pcLibraryPath = 0;
DLHandler SOAPTransportFactory::m_LibHandler = 0;
CREATE_OBJECT1 SOAPTransportFactory::m_Create = 0;
DELETE_OBJECT1 SOAPTransportFactory::m_Delete = 0;


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
#if defined(USE_LTDL)
        m_Create = (CREATE_OBJECT1) lt_dlsym(m_LibHandler, CREATE_FUNCTION1);
        m_Delete = (DELETE_OBJECT1) lt_dlsym(m_LibHandler, DELETE_FUNCTION1);
#elif defined(WIN32)
        m_Create = (CREATE_OBJECT1) GetProcAddress(m_LibHandler, CREATE_FUNCTION1);
        m_Delete = (DELETE_OBJECT1) GetProcAddress(m_LibHandler, DELETE_FUNCTION1);
#else
        m_Create = (CREATE_OBJECT1) dlsym(m_LibHandler, CREATE_FUNCTION1);
        m_Delete = (DELETE_OBJECT1) dlsym(m_LibHandler, DELETE_FUNCTION1);
#endif
        if (!m_Create || !m_Delete)
        {
            unloadLib();
                        AXISTRACE1("SERVER_ENGINE_LOADING_TRANSPORT_FAILED", CRITICAL);
                        throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED,  strdup(m_pcLibraryPath));
			//throw AxisEngineException(SERVER_ENGINE_LIBRARY_LOADING_FAILED, strdup(m_pcLibraryPath));
        }
        else
        {
            void (*initializeLibrary) (void);
#if defined(USE_LTDL)
            initializeLibrary = (void (*)(void))lt_dlsym(m_LibHandler, INIT_FUNCTION);
#elif defined(WIN32)
            initializeLibrary = (void (*)(void))GetProcAddress(m_LibHandler, INIT_FUNCTION);
#else
            initializeLibrary = (void (*)(void))dlsym(m_LibHandler, INIT_FUNCTION);
#endif
            if (initializeLibrary)
                 (*initializeLibrary)();
            return AXIS_SUCCESS;
        }		
	}
	else
	{
                AXISTRACE1("SERVER_ENGINE_LOADING_TRANSPORT_FAILED", CRITICAL);
                throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED,  strdup(m_pcLibraryPath));
		//throw AxisEngineException(SERVER_ENGINE_LIBRARY_LOADING_FAILED, strdup(m_pcLibraryPath));
	}
	return AXIS_FAIL;
}

int SOAPTransportFactory::uninitialize()
{
            void (*uninitializeLibrary) (void);
#if defined(USE_LTDL)
            uninitializeLibrary = (void (*)(void))lt_dlsym(m_LibHandler, UNINIT_FUNCTION);
#elif defined(WIN32)
            uninitializeLibrary = (void (*)(void))GetProcAddress(m_LibHandler, UNINIT_FUNCTION);
#else
            uninitializeLibrary = (void (*)(void))dlsym(m_LibHandler, UNINIT_FUNCTION);
#endif
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
	return pTpt;
}

void SOAPTransportFactory::destroyTransportObject(SOAPTransport* pObject)
{
	m_Delete(pObject);
}

int SOAPTransportFactory::loadLib()
{
#if defined(USE_LTDL)
    m_LibHandler = lt_dlopen(m_pcLibraryPath);
    if (!m_LibHandler)
    {
        AXISTRACE1("SERVER_ENGINE_LOADING_TRANSPORT_FAILED", CRITICAL);
        throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED);
        //printf("DLOPEN FAILED in loading transport library: %s\n", lt_dlerror ());
    }
#elif defined(WIN32)
    m_LibHandler = LoadLibrary(m_pcLibraryPath);
#else 
    m_LibHandler = dlopen(m_pcLibraryPath, RTLD_LAZY);
    if (!m_LibHandler)
    {
        AXISTRACE1("SERVER_ENGINE_LOADING_TRANSPORT_FAILED", CRITICAL);
        //printf("DLOPEN FAILED in loading transport library: %s\n", dlerror());
        throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED);
    }
#endif
    return (m_LibHandler != 0) ? AXIS_SUCCESS : AXIS_FAIL;
}

int SOAPTransportFactory::unloadLib()
{
#if defined(USE_LTDL)
    lt_dlclose(m_LibHandler);
#elif defined(WIN32)
    FreeLibrary(m_LibHandler);
#else 
    dlclose(m_LibHandler);
#endif
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
