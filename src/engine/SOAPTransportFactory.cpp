/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <stdio.h>

#include "SOAPTransportFactory.h"
#include "../transport/SOAPTransport.h"
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

SOAPTransportFactory::
SOAPTransportFactory()
{
    m_LibHandler = 0;
}

SOAPTransportFactory::
~SOAPTransportFactory()
{
    logEntryEngine("SOAPTransportFactory::~SOAPTransportFactory")

    logExit()
}

int SOAPTransportFactory::
initialize()
{
    logEntryEngine("SOAPTransportFactory::initialize")

    m_pcLibraryPath = g_pConfig->getAxisConfProperty(AXCONF_TRANSPORTHTTP);

    if (!loadLib())
    {
        m_Create = (CREATE_OBJECT1) PLATFORM_GETPROCADDR(m_LibHandler, CREATE_FUNCTION1);
        if (m_Create)
            m_Delete = (DELETE_OBJECT1) PLATFORM_GETPROCADDR(m_LibHandler, DELETE_FUNCTION1);

        if (!m_Create || !m_Delete)
        {
            // get load lib error information
            string sFullMessage = "Failed to resolve to SOAP transport procedures in library " +
                                  string(m_pcLibraryPath) + ". " +  PLATFORM_LOADLIB_ERROR;
            
            logThrowExceptionWithData("AxisEngineException - SERVER_ENGINE_LOADING_TRANSPORT_FAILED", sFullMessage.c_str())

            // Unload library - this must be done after obtaining error info above
            unloadLib();
            
            throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED,  sFullMessage.c_str());
        }

        void (*preloadChannels) (char*, char*);
        preloadChannels = (void (*)(char*, char*))PLATFORM_GETPROCADDR(m_LibHandler, "preloadChannels");
        if (preloadChannels)
            (*preloadChannels)(g_pConfig->getAxisConfProperty( AXCONF_CHANNEL_HTTP), 
                g_pConfig->getAxisConfProperty( AXCONF_SSLCHANNEL_HTTP));
    }
    else
    {
        // dead code - will never be reached, need to remove.
        logThrowException("AxisEngineException - SERVER_ENGINE_LOADING_TRANSPORT_FAILED")

        throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED);
    }
    
    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

int SOAPTransportFactory::
uninitialize()
{
   logEntryEngine("SOAPTransportFactory::uninitialize")

   void (*uninitializeLibrary) (void);
   uninitializeLibrary = (void (*)(void))PLATFORM_GETPROCADDR(m_LibHandler, UNINIT_FUNCTION);
   if (uninitializeLibrary)
        (*uninitializeLibrary)();
   
   int Status = unloadLib();
   
   logExitWithReturnCode(Status)
   
   return Status;
}

/**
 * Should create an instance of transport of type given by eProtocol
 */
SOAPTransport* SOAPTransportFactory::
getTransportObject(AXIS_PROTOCOL_TYPE eProtocol)
{
    logEntryEngine("SOAPTransportFactory::getTransportObject")

    SOAPTransport* pTpt = NULL;
    m_Create(&pTpt);
    
    if (pTpt)
    {
        pTpt->setProtocol(eProtocol);
        if (AxisTrace::isLoggingEnabled() && AxisTrace::isTransportLoggingEnabled())
            pTpt->enableTrace(AxisTrace::getLogFilePath().c_str(), AxisTrace::getLogFilter().c_str());
    }
    
    logExitWithPointer(pTpt)
    
    return pTpt;
}

void SOAPTransportFactory::
destroyTransportObject(SOAPTransport* pObject)
{
    logEntryEngine("SOAPTransportFactory::destroyTransportObject")

    m_Delete(pObject);
    
    logExit()
}

int SOAPTransportFactory::
loadLib()
{
    logEntryEngine("SOAPTransportFactory::loadLib")

    logDebugArg1("Loading transport %s", m_pcLibraryPath)

    m_LibHandler = PLATFORM_LOADLIB(m_pcLibraryPath);

    if (!m_LibHandler)
    {
        // get load lib error information
        string sFullMessage = "Failed to load transport library " +  
                              string(m_pcLibraryPath) + ". " + PLATFORM_LOADLIB_ERROR;

        logThrowExceptionWithData("AxisEngineException - SERVER_ENGINE_LOADING_TRANSPORT_FAILED", sFullMessage.c_str())

        throw AxisEngineException(SERVER_ENGINE_LOADING_TRANSPORT_FAILED, sFullMessage.c_str());
    }
    
    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

int SOAPTransportFactory::
unloadLib()
{
    logEntryEngine("SOAPTransportFactory::unloadLib")

    logDebugArg1("Unloading transport %s", m_pcLibraryPath)

    PLATFORM_UNLOADLIB(m_LibHandler);

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END

