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
            UnloadLib (pHandlerInfo);
        delete pHandlerInfo;
    }
    unlock ();
#if defined(US_LTDL)
    lt_dlexit ();
#endif
}

int HandlerLoader::DeleteHandler (BasicHandler* pHandler, int nLibId)
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
        return HANDLER_NOT_LOADED;
    }
}

int HandlerLoader::LoadLib (HandlerInformation* pHandlerInfo)
{
//#ifdef WIN32
#if defined(USE_LTDL)
    pHandlerInfo->m_Handler = lt_dlopen (pHandlerInfo->m_sLib.c_str ());
    if (!pHandlerInfo->m_Handler)
    {
        printf ("DLOPEN FAILED: %s\n", lt_dlerror ());
    }
#elif defined(WIN32)
    pHandlerInfo->m_Handler = LoadLibrary (pHandlerInfo->m_sLib.c_str ());
#else //Linux
    pHandlerInfo->m_nLoadOptions = RTLD_LAZY;
    pHandlerInfo->m_Handler =
        dlopen (pHandlerInfo->m_sLib.c_str (), pHandlerInfo->m_nLoadOptions);
    if (!pHandlerInfo->m_Handler)
    {
        printf ("DLOPEN FAILED: %s\n", dlerror ());
        exit (1);
    }
#endif
    return (pHandlerInfo->m_Handler != 0) ? AXIS_SUCCESS : AXIS_FAIL;
}

int HandlerLoader::UnloadLib (HandlerInformation* pHandlerInfo)
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

int HandlerLoader::CreateHandler (BasicHandler** pHandler, int nLibId)
{
    lock ();
    *pHandler = NULL;
    HandlerInformation* pHandlerInfo = NULL;
    if (m_HandlerInfoList.find (nLibId) == m_HandlerInfoList.end ())
    {
        pHandlerInfo = new HandlerInformation ();
        pHandlerInfo->m_sLib = g_pWSDDDeployment->GetLibName (nLibId);
        if (pHandlerInfo->m_sLib.empty ())
        {
            delete pHandlerInfo;
            unlock ();
            return LIBRARY_PATH_EMPTY;
        }
        // pHandlerInfo->m_nLoadOptions = RTLD_LAZY;
        if (AXIS_SUCCESS == LoadLib (pHandlerInfo))
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
                UnloadLib (pHandlerInfo);
                delete pHandlerInfo;
                unlock ();
                AXISTRACE1 ("Library loading failed", CRITICAL);
                return LOADLIBRARY_FAILED;
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
            return LOADLIBRARY_FAILED;
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
            if (AXIS_SUCCESS == pBH->_functions->Init (pBH->_object))
            {
                pHandlerInfo->m_nObjCount++;
                *pHandler = pBH;
                unlock ();
                return AXIS_SUCCESS;
            }
            else
            {
                pBH->_functions->Fini (pBH->_object);
                pHandlerInfo->m_Delete (pBH);
                unlock ();
                return HANDLER_INIT_FAIL;
            }
        }
        else if (0 == pBH->_object)
        {
            return CREATION_FAILED;
        }
        else
        /* C++ service or handler */
        {
            if (AXIS_SUCCESS == ((HandlerBase*) pBH->_object)->Init ())
            {
                pHandlerInfo->m_nObjCount++;
                *pHandler = pBH;
                unlock ();
                return AXIS_SUCCESS;
            }
            else
            {
                ((HandlerBase*) pBH->_object)->Fini ();
                pHandlerInfo->m_Delete (pBH);
                unlock ();
                return HANDLER_INIT_FAIL;
            }
        }
    }
    else
    {
        unlock ();
        return CREATION_FAILED;
    }
}
