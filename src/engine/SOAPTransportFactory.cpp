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
#include <axis/SOAPTransport.h>
#include <stdio.h>

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
#ifdef WIN32
#ifdef _DEBUG
	m_pcLibraryPath = "AxisTransport_D.dll"; //this will be taken from configuration file
#else
	m_pcLibraryPath = "AxisTransport.dll"; //this will be taken from configuration file
#endif
#else
	m_pcLibraryPath = "libAxisTransport.so"; //this will be taken from configuration file
#endif
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
            printf("Transport library loading failed");
        }
        else
        {
            return AXIS_SUCCESS;
        }		
	}
	return AXIS_FAIL;
}

int SOAPTransportFactory::uninitialize()
{
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
        printf("DLOPEN FAILED in loading transport library: %s\n", lt_dlerror ());
    }
#elif defined(WIN32)
    m_LibHandler = LoadLibrary(m_pcLibraryPath);
#else 
    m_LibHandler = dlopen(m_pcLibraryPath, RTLD_LAZY);
    if (!m_LibHandler)
    {
        printf("DLOPEN FAILED in loading transport library: %s\n", dlerror());
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

