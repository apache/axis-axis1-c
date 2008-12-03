/* -*- C++ -*- */
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
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <stdio.h>

#include "HandlerLoader.h"
#include "../common/AxisUtils.h"
#include "../wsdd/WSDDDeployment.h"

#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX WSDDDeployment* g_pWSDDDeployment;

AXIS_CPP_NAMESPACE_START

HandlerLoader::
HandlerLoader ()
{
    PLATFORM_LOADLIBINIT();
}

HandlerLoader::
~HandlerLoader ()
{
    logEntryEngine("HandlerLoader::~HandlerLoader")

    //lock ();
    Lock l(this);
    HandlerInformation* pHandlerInfo = NULL;
    for (map < int, HandlerInformation* >::iterator it =
         m_HandlerInfoList.begin (); it != m_HandlerInfoList.end (); it++)
    {
        pHandlerInfo = (*it).second;
        unloadLib (pHandlerInfo);
        delete pHandlerInfo;
    }
    l.unlock ();
    PLATFORM_LOADLIBEXIT()
    
    logExit()
}

int HandlerLoader::
deleteHandler (BasicHandler* pHandler, int nLibId)
{
    logEntryEngine("HandlerLoader::deleteHandler")

    Lock l(this);
    if (m_HandlerInfoList.find (nLibId) != m_HandlerInfoList.end ())
    {
        HandlerInformation* pHandlerInfo = m_HandlerInfoList[nLibId];
        pHandlerInfo->m_nObjCount--;
        pHandlerInfo->m_Delete (pHandler);
    }
    else
    {
        logThrowException("AxisEngineException - SERVER_ENGINE_HANDLER_NOT_LOADED")

        throw AxisEngineException(SERVER_ENGINE_HANDLER_NOT_LOADED);
    }
    
    logExitWithReturnCode(AXIS_SUCCESS)

    return AXIS_SUCCESS;
}

int HandlerLoader::
loadLib (HandlerInformation* pHandlerInfo)
{
    logEntryEngine("HandlerLoader::loadLib")

    logDebugArg1("Loading handler %s", pHandlerInfo->m_sLib.c_str())
    
    pHandlerInfo->m_Handler = PLATFORM_LOADLIB(pHandlerInfo->m_sLib.c_str());

    if (!pHandlerInfo->m_Handler)
    {
        // get load lib error information
        string sFullMessage = "Failed to load handler library " +  
                              pHandlerInfo->m_sLib + ". " + PLATFORM_LOADLIB_ERROR;

        logThrowExceptionWithData("AxisEngineException - SERVER_ENGINE_HANDLER_NOT_LOADED", sFullMessage.c_str())
        
        throw AxisEngineException(SERVER_ENGINE_LIBRARY_LOADING_FAILED, sFullMessage.c_str());
    }

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

int HandlerLoader::
unloadLib (HandlerInformation* pHandlerInfo)
{
    logEntryEngine("HandlerLoader::unloadLib")

    logDebugArg1("Unloading handler %s", pHandlerInfo->m_sLib.c_str())

    PLATFORM_UNLOADLIB(pHandlerInfo->m_Handler);

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

int HandlerLoader::
createHandler (BasicHandler** pHandler, int nLibId)
{
    logEntryEngine("HandlerLoader::createHandler")

    //lock ();
    Lock l(this);
    *pHandler = NULL;
    HandlerInformation* pHandlerInfo = NULL;
    if (m_HandlerInfoList.find (nLibId) == m_HandlerInfoList.end ())
    {
        pHandlerInfo = new HandlerInformation ();
        pHandlerInfo->m_sLib = g_pWSDDDeployment->getLibName (nLibId);
        if (pHandlerInfo->m_sLib.empty ())
        {
            delete pHandlerInfo;
            
            logThrowException("AxisEngineException - SERVER_CONFIG_LIBRARY_PATH_EMPTY")

            throw AxisConfigException(SERVER_CONFIG_LIBRARY_PATH_EMPTY);
        }

        if (AXIS_SUCCESS == loadLib (pHandlerInfo))
        {
            pHandlerInfo->m_Create =
                (CREATE_OBJECT) PLATFORM_GETPROCADDR(pHandlerInfo->m_Handler, CREATE_FUNCTION);
                
            if (pHandlerInfo->m_Create)
                pHandlerInfo->m_Delete =
                    (DELETE_OBJECT) PLATFORM_GETPROCADDR(pHandlerInfo->m_Handler,DELETE_FUNCTION);

            if (!pHandlerInfo->m_Create || !pHandlerInfo->m_Delete)
            {
                // get load lib error information
                string sFullMessage = "Failed to resolve to handler procedures in library " +  
                                      pHandlerInfo->m_sLib + ". " + PLATFORM_LOADLIB_ERROR;
                
                // Unload library - this must be done after obtaining error info above            
                unloadLib (pHandlerInfo);
                delete pHandlerInfo;
                
                logThrowExceptionWithData("AxisEngineException - SERVER_ENGINE_LIBRARY_LOADING_FAILED", sFullMessage.c_str())

                throw AxisEngineException(SERVER_ENGINE_LIBRARY_LOADING_FAILED, sFullMessage.c_str());
            }
            else // success
            {
                m_HandlerInfoList[nLibId] = pHandlerInfo;
            }
        }
        else
        {
            // dead code - will never be reached, need to remove.
            logThrowException("AxisEngineException - SERVER_ENGINE_LIBRARY_LOADING_FAILED")

            throw AxisEngineException(SERVER_ENGINE_LIBRARY_LOADING_FAILED);
        }
    }

    pHandlerInfo = m_HandlerInfoList[nLibId];
    BasicHandler* pBH = NULL;
    pHandlerInfo->m_Create (&pBH);
    if (pBH)
    {
        if (0 != pBH->_functions)
        /* this is a C service or handler */
        {
            if (AXIS_SUCCESS == pBH->_functions->init (pBH->_object))
            {
                pHandlerInfo->m_nObjCount++;
                *pHandler = pBH;
            }
            else
            {
                pBH->_functions->fini (pBH->_object);
                pHandlerInfo->m_Delete (pBH);

                logThrowException("AxisEngineException - SERVER_ENGINE_HANDLER_INIT_FAILED")

                throw AxisEngineException(SERVER_ENGINE_HANDLER_INIT_FAILED);
            }
        }
        else if (0 == pBH->_object)
        {
            logThrowException("AxisEngineException - SERVER_ENGINE_HANDLER_CREATION_FAILED")

            throw AxisEngineException(SERVER_ENGINE_HANDLER_CREATION_FAILED);
        }
        else
        /* C++ service or handler */
        {
            if (AXIS_SUCCESS == ((HandlerBase*) pBH->_object)->init ())
            {
                pHandlerInfo->m_nObjCount++;
                *pHandler = pBH;
            }
            else
            {
                ((HandlerBase*) pBH->_object)->fini ();
                pHandlerInfo->m_Delete (pBH);
                
                logThrowException("AxisEngineException - SERVER_ENGINE_HANDLER_INIT_FAILED")

                throw AxisEngineException(SERVER_ENGINE_HANDLER_INIT_FAILED);
            }
        }
    }
    else
    {
        logThrowException("AxisEngineException - SERVER_ENGINE_HANDLER_CREATION_FAILED")

        throw AxisEngineException(SERVER_ENGINE_HANDLER_CREATION_FAILED);
    }

    logExitWithReturnCode(AXIS_SUCCESS)
    
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
