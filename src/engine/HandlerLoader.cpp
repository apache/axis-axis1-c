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

#include "HandlerLoader.h"
#include <stdio.h>
#include "../common/AxisUtils.h"
#include "../wsdd/WSDDDeployment.h"
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

extern WSDDDeployment* g_pWSDDDeployment;

HandlerLoader::HandlerLoader ()
{
#if defined(USE_LTDL)
    lt_dlinit ();
#endif
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
#if defined(US_LTDL)
    lt_dlexit ();
#endif
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
        return AXIS_SUCCESS;
    }
    else
    {
        unlock ();
        THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLER_NOT_LOADED);
    }
}

int HandlerLoader::loadLib (HandlerInformation* pHandlerInfo)
{
//#ifdef WIN32
#if defined(USE_LTDL)
    pHandlerInfo->m_Handler = lt_dlopen (pHandlerInfo->m_sLib.c_str ());
    if (!pHandlerInfo->m_Handler)
    {
        AXISTRACE1("SERVER_ENGINE_LIBRARY_LOADING_FAILED", CRITICAL);
        THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_LIBRARY_LOADING_FAILED);
    }
#elif defined(WIN32)
    pHandlerInfo->m_Handler = LoadLibrary (pHandlerInfo->m_sLib.c_str ());
#else //Linux
    pHandlerInfo->m_nLoadOptions = RTLD_LAZY;
    pHandlerInfo->m_Handler =
        dlopen (pHandlerInfo->m_sLib.c_str (), pHandlerInfo->m_nLoadOptions);
    if (!pHandlerInfo->m_Handler)
    {
        AXISTRACE1("DLOPEN FAILED", CRITICAL);
        THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_LIBRARY_LOADING_FAILED);
        //printf ("DLOPEN FAILED: %s\n", dlerror ());
        //exit (1);
    }
#endif
    return (pHandlerInfo->m_Handler != 0) ? AXIS_SUCCESS : AXIS_FAIL;
}

int HandlerLoader::unloadLib (HandlerInformation* pHandlerInfo)
{
//#ifdef WIN32
#if defined(USE_LTDL)
    lt_dlclose (pHandlerInfo->m_Handler);
#elif defined(WIN32)
    FreeLibrary (pHandlerInfo->m_Handler);
#else //Linux
    dlclose (pHandlerInfo->m_Handler);
#endif
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
            THROW_AXIS_CONFIG_EXCEPTION(SERVER_CONFIG_LIBRARY_PATH_EMPTY);
            //return SERVER_CONFIG_LIBRARYPATHEMPTY;
        }
        // pHandlerInfo->m_nLoadOptions = RTLD_LAZY;
        if (AXIS_SUCCESS == loadLib (pHandlerInfo))
        {
            //#ifdef WIN32
#if defined(USE_LTDL)
            pHandlerInfo->m_Create =
                (CREATE_OBJECT) lt_dlsym (pHandlerInfo->m_Handler,
                CREATE_FUNCTION);
            pHandlerInfo->m_Delete =
                (DELETE_OBJECT) lt_dlsym (pHandlerInfo->m_Handler,
                DELETE_FUNCTION);
#elif defined(WIN32)
            pHandlerInfo->m_Create =
                (CREATE_OBJECT) GetProcAddress (pHandlerInfo->m_Handler,
                CREATE_FUNCTION);
            pHandlerInfo->m_Delete =
                (DELETE_OBJECT) GetProcAddress (pHandlerInfo->m_Handler,
                DELETE_FUNCTION);
#else //Linux
            pHandlerInfo->m_Create =
                (CREATE_OBJECT) dlsym (pHandlerInfo->m_Handler,
                CREATE_FUNCTION);
            pHandlerInfo->m_Delete =
                (DELETE_OBJECT) dlsym (pHandlerInfo->m_Handler, 
                DELETE_FUNCTION);
#endif
            if (!pHandlerInfo->m_Create || !pHandlerInfo->m_Delete)
            {
                unloadLib (pHandlerInfo);
                delete pHandlerInfo;
                unlock ();
                AXISTRACE1 ("Library loading failed", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_LIBRARY_LOADING_FAILED);
                //return SERVER_ENGINE_LIBRARYLOADINGFAILED;
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
            THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_LIBRARY_LOADING_FAILED);
            //return SERVER_ENGINE_LIBRARYLOADINGFAILED;
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
                unlock ();
                return AXIS_SUCCESS;
            }
            else
            {
                pBH->_functions->fini (pBH->_object);
                pHandlerInfo->m_Delete (pBH);
                unlock ();
                AXISTRACE1("SERVER_ENGINE_HANDLER_INIT_FAILED", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLER_INIT_FAILED);
                //return SERVER_ENGINE_HANDLERINITFAILED;
            }
        }
        else if (0 == pBH->_object)
        {
            AXISTRACE1("SERVER_ENGINE_HANDLER_CREATION_FAILED", CRITICAL);
            THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLER_CREATION_FAILED);
            //return SERVER_ENGINE_HANDLERCREATIONFAILED;
        }
        else
        /* C++ service or handler */
        {
            if (AXIS_SUCCESS == ((HandlerBase*) pBH->_object)->init ())
            {
                pHandlerInfo->m_nObjCount++;
                *pHandler = pBH;
                unlock ();
                return AXIS_SUCCESS;
            }
            else
            {
                ((HandlerBase*) pBH->_object)->fini ();
                pHandlerInfo->m_Delete (pBH);
                unlock ();
                AXISTRACE1("SERVER_ENGINE_HANDLER_INIT_FAILED", CRITICAL);
                THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLER_INIT_FAILED);
                //return SERVER_ENGINE_HANDLERINITFAILED;
            }
        }
    }
    else
    {
        unlock ();
        AXISTRACE1("SERVER_ENGINE_HANDLER_CREATION_FAILED", CRITICAL);
        THROW_AXIS_ENGINE_EXCEPTION(SERVER_ENGINE_HANDLER_CREATION_FAILED);
        //return SERVER_ENGINE_HANDLERCREATIONFAILED;
    }
}