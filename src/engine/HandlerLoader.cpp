/* -*- C++ -*- */
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
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
#ifdef WIN32
#pragma warning (disable : 4390)        // empty controlled statement found;
#endif

#include "../platforms/PlatformAutoSense.hpp"

#include "HandlerLoader.h"
#include <stdio.h>
#include "../common/AxisUtils.h"
#include "../wsdd/WSDDDeployment.h"
#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX AxisTrace* g_pAT;
extern AXIS_CPP_NAMESPACE_PREFIX WSDDDeployment* g_pWSDDDeployment;

AXIS_CPP_NAMESPACE_START

HandlerLoader::HandlerLoader ()
{
    PLATFORM_LOADLIBINIT();
}

HandlerLoader::~HandlerLoader ()
{
    lock ();
    HandlerInformation* pHandlerInfo = NULL;
    for (map < int, HandlerInformation* >::iterator it =
         m_HandlerInfoList.begin (); it != m_HandlerInfoList.end (); it++)
    {
        pHandlerInfo = (*it).second;
        if (pHandlerInfo->m_nObjCount != 0);  /* It seems that some objects
                                               * created have not been deleted
					                           * - unexpected
					                           */
            unloadLib (pHandlerInfo);
        delete pHandlerInfo;
    }
    unlock ();
    PLATFORM_LOADLIBEXIT()
}

int HandlerLoader::deleteHandler (BasicHandler* pHandler, int nLibId)
{
    lock ();
    if (m_HandlerInfoList.find (nLibId) != m_HandlerInfoList.end ())
    {
        HandlerInformation* pHandlerInfo = m_HandlerInfoList[nLibId];
        pHandlerInfo->m_nObjCount--;
        pHandlerInfo->m_Delete (pHandler);
        if (pHandlerInfo->m_nObjCount == 0);  //time to unload the DLL
            unlock ();
    }
    else
    {
        unlock ();
        throw AxisEngineException(SERVER_ENGINE_HANDLER_NOT_LOADED);
    }
    return AXIS_SUCCESS;
}

int HandlerLoader::loadLib (HandlerInformation* pHandlerInfo)
{
    pHandlerInfo->m_Handler = PLATFORM_LOADLIB(pHandlerInfo->m_sLib.c_str());

    if (!pHandlerInfo->m_Handler)
    {
        AXISTRACE1("SERVER_ENGINE_LIBRARY_LOADING_FAILED", CRITICAL);
        throw AxisEngineException(SERVER_ENGINE_LIBRARY_LOADING_FAILED, PLATFORM_LOADLIB_ERROR);
    }

    return AXIS_SUCCESS;
}

int HandlerLoader::unloadLib (HandlerInformation* pHandlerInfo)
{
    PLATFORM_UNLOADLIB(pHandlerInfo->m_Handler);

    return AXIS_SUCCESS;
}

int HandlerLoader::createHandler (BasicHandler** pHandler, int nLibId)
{
    lock ();
    *pHandler = NULL;
    HandlerInformation* pHandlerInfo = NULL;
    if (m_HandlerInfoList.find (nLibId) == m_HandlerInfoList.end ())
    {
        pHandlerInfo = new HandlerInformation ();
        pHandlerInfo->m_sLib = g_pWSDDDeployment->getLibName (nLibId);
        if (pHandlerInfo->m_sLib.empty ())
        {
            delete pHandlerInfo;
            unlock ();
            AXISTRACE1("SERVER_CONFIG_LIBRARY_PATH_EMPTY", CRITICAL);
            throw AxisConfigException(SERVER_CONFIG_LIBRARY_PATH_EMPTY);
        }

        if (AXIS_SUCCESS == loadLib (pHandlerInfo))
        {
            pHandlerInfo->m_Create =
                (CREATE_OBJECT) PLATFORM_GETPROCADDR(pHandlerInfo->m_Handler,
                CREATE_FUNCTION);
            pHandlerInfo->m_Delete =
                (DELETE_OBJECT) PLATFORM_GETPROCADDR(pHandlerInfo->m_Handler,
                DELETE_FUNCTION);

            if (!pHandlerInfo->m_Create || !pHandlerInfo->m_Delete)
            {
                unloadLib (pHandlerInfo);
                delete pHandlerInfo;
                unlock ();
                AXISTRACE1 ("Library loading failed", CRITICAL);
                throw AxisEngineException(SERVER_ENGINE_LIBRARY_LOADING_FAILED);
            }
            else // success
            {
                m_HandlerInfoList[nLibId] = pHandlerInfo;
            }
        }
        else
        {
            unlock ();
            AXISTRACE1 ("Library loading failed", CRITICAL);
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
                unlock ();
                AXISTRACE1("SERVER_ENGINE_HANDLER_INIT_FAILED", CRITICAL);
                throw AxisEngineException(SERVER_ENGINE_HANDLER_INIT_FAILED);
            }
        }
        else if (0 == pBH->_object)
        {
            AXISTRACE1("SERVER_ENGINE_HANDLER_CREATION_FAILED", CRITICAL);
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
                unlock ();
                AXISTRACE1("SERVER_ENGINE_HANDLER_INIT_FAILED", CRITICAL);
                throw AxisEngineException(SERVER_ENGINE_HANDLER_INIT_FAILED);
            }
        }
    }
    else
    {
        unlock ();
        AXISTRACE1("SERVER_ENGINE_HANDLER_CREATION_FAILED", CRITICAL);
        throw AxisEngineException(SERVER_ENGINE_HANDLER_CREATION_FAILED);
    }

    unlock ();
    return AXIS_SUCCESS;
}

AXIS_CPP_NAMESPACE_END
