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
 *
 */


#include "HandlerPool.h"
#include "AppScopeHandlerPool.h"
#include "RequestScopeHandlerPool.h"
#include "SessionScopeHandlerPool.h"
#include "../wsdd/WSDDDeployment.h"
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;

extern AppScopeHandlerPool* g_pAppScopeHandlerPool;
extern RequestScopeHandlerPool* g_pRequestScopeHandlerPool;
extern SessionScopeHandlerPool* g_pSessionScopeHandlerPool;
extern WSDDDeployment* g_pWSDDDeployment;

HandlerPool::HandlerPool ()
{
}

HandlerPool::~HandlerPool ()
{
    for (list <HandlerChain*>::iterator it = m_ChainStore.begin ();
        it != m_ChainStore.end (); it++)
    {
        delete (*it);
    }
}

int HandlerPool::getHandler (BasicHandler** ppHandler, string & sSessionId,
    int nScope, int nLibId)
{
    *ppHandler = NULL;
    int Status = AXIS_FAIL;

    switch (nScope)
    {
        case AH_APPLICATION:
            do
            {
                if ((Status =
                    g_pAppScopeHandlerPool->getInstance (ppHandler,
                                                          nLibId)) ==
                    AXIS_SUCCESS)
                {
                    return Status;
                }
                else if (Status == HANDLER_BEING_USED)
                {             //block this thread not this object
                    Ax_Sleep (0);
                }
                else
                {
                    return Status;
                }
            } while (Status == HANDLER_BEING_USED);
            break;
        case AH_SESSION:
            return g_pSessionScopeHandlerPool->getInstance (sSessionId,
                ppHandler, nLibId);
        case AH_REQUEST:
            return g_pRequestScopeHandlerPool->getInstance (ppHandler, nLibId);
    }
    return Status;
}

int HandlerPool::poolHandler (string &sSessionId, BasicHandler* pHandler,
    int nScope, int nLibId)
{
    switch (nScope)
    {
        case AH_APPLICATION:
            g_pAppScopeHandlerPool->putInstance (pHandler, nLibId);
            break;
        case AH_SESSION:
            g_pSessionScopeHandlerPool->putInstance (sSessionId, pHandler,
                nLibId);
            break;
        case AH_REQUEST:
            g_pRequestScopeHandlerPool->putInstance (pHandler, nLibId);
            break;
    }
    return AXIS_SUCCESS;
}

int HandlerPool::getGlobalRequestFlowHandlerChain (HandlerChain** ppChain,
    string & sSessionId)
{
    const WSDDHandlerList* pHandlerList =
        g_pWSDDDeployment->getGlobalRequestFlowHandlers ();
    if (pHandlerList)
    {
        return getHandlerChain (sSessionId, ppChain, pHandlerList);
    }
    else
    {
        *ppChain = NULL;
        return AXIS_SUCCESS;  // NO_HANDLERS_CONFIGURED
    }
}

int HandlerPool::getGlobalResponseFlowHandlerChain (HandlerChain** ppChain,
    string &sSessionId)
{
    const WSDDHandlerList *pHandlerList =
        g_pWSDDDeployment->getGlobalResponseFlowHandlers ();
    if (pHandlerList)
    {
        return getHandlerChain (sSessionId, ppChain, pHandlerList);
    }
    else
    {
        *ppChain = NULL;
        return AXIS_SUCCESS;  // NO_HANDLERS_CONFIGURED
    }
}

int HandlerPool::getTransportRequestFlowHandlerChain (HandlerChain** ppChain,
    string &sSessionId, AXIS_PROTOCOL_TYPE Protocol)
{
    const WSDDHandlerList* pHandlerList =
        g_pWSDDDeployment->getTransportRequestFlowHandlers (Protocol);
    if (pHandlerList)
    {
        return getHandlerChain (sSessionId, ppChain, pHandlerList);
    }
    else
    {
        *ppChain = NULL;
        return AXIS_SUCCESS;  // NO_HANDLERS_CONFIGURED
    }
}

int HandlerPool::getTransportResponseFlowHandlerChain (HandlerChain** ppChain,
    string & sSessionId, AXIS_PROTOCOL_TYPE Protocol)
{
    const WSDDHandlerList* pHandlerList =
        g_pWSDDDeployment->getTransportResponseFlowHandlers (Protocol);
    if (pHandlerList)
    {
        return getHandlerChain (sSessionId, ppChain, pHandlerList);
    }
    else
    {
        *ppChain = NULL;
        return AXIS_SUCCESS;  // NO_HANDLERS_CONFIGURED
    }
}

int HandlerPool::getRequestFlowHandlerChain (HandlerChain** ppChain,
    string &sSessionId, const WSDDService* pService)
{
    const WSDDHandlerList* pHandlerList = pService->getRequestFlowHandlers ();
    if (pHandlerList)
    {
        return getHandlerChain (sSessionId, ppChain, pHandlerList);
    }
    else
    {
        *ppChain = NULL;
        /* AXISTRACE1("No handlers configured", INFO); */
        return AXIS_SUCCESS;  // NO_HANDLERS_CONFIGURED
    }
}

int HandlerPool::getResponseFlowHandlerChain (HandlerChain** ppChain,
    string &sSessionId, const WSDDService* pService)
{
    const WSDDHandlerList* pHandlerList = pService->getResponseFlowHandlers ();
    if (pHandlerList)
    {
        return getHandlerChain (sSessionId, ppChain, pHandlerList);
    }
    else
    {
        *ppChain = NULL;
        return AXIS_SUCCESS;  // NO_HANDLERS_CONFIGURED
    }
}

int HandlerPool::getHandlerChain (string &sSessionId, HandlerChain** ppChain,
    const WSDDHandlerList* pHandlerList)
{
    lock ();
    *ppChain = NULL;
    HandlerChain* pChain;
    // check m_ChainStore to get a HandlerChain
    if (!m_ChainStore.empty ())
    {
        pChain = m_ChainStore.front ();
        m_ChainStore.pop_front ();
        pChain->init ();
    }
    else
    {
        pChain = new HandlerChain ();
    }

    WSDDHandler* pWSDDH;
    BasicHandler* pBH;
    int Status = AXIS_SUCCESS;

    for (WSDDHandlerList::const_iterator it = pHandlerList->begin ();
         it != pHandlerList->end (); it++)
    {
        pWSDDH = (*it);
        if ((Status = getHandler (&pBH, sSessionId, pWSDDH->getScope (),
            pWSDDH->getLibId ())) == AXIS_SUCCESS)
        {
            /*
             * if (NORMAL_HANDLER == pBH->_functions->GetType(pBH->_object))
             * {                
             *     ((Handler*)
	     *     (pBH->_object))->SetOptionList(pWSDDH->GetParameterList());
	     *     pChain->AddHandler(pBH, pWSDDH->GetScope(), pWSDDH->GetLibId());                
             * }
             * else
             * {
             *     Status = WRONG_HANDLER_TYPE;
             *     break;
             * }
             */

            if (0 != pBH->_functions)
            {
                /* C Handler */
            }
            else if (0 != pBH->_object)
            {
                if (NORMAL_HANDLER == ((Handler*) (pBH->_object))->getType ())
                {
                    ((Handler*) (pBH->_object))->
                        setOptionList (pWSDDH->getParameterList ());
                    pChain->addHandler (pBH, pWSDDH->getScope (),
                        pWSDDH->getLibId ());
                }
                else
                {
                    Status = WRONG_HANDLER_TYPE;
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    if (Status != AXIS_SUCCESS) //some failure so undo whatever done here
    {
        AXISTRACE1 ("Handler failure", WARN);
        string nosession = SESSIONLESSHANDLERS;
        for (pChain->m_itCurrHandler = pChain->m_HandlerList.begin ();
             pChain->m_itCurrHandler != pChain->m_HandlerList.end ();
               pChain->m_itCurrHandler++)
        {
            if ((*pChain->m_itCurrHandler).m_pHandler != NULL)
            {
                poolHandler (nosession, (*pChain->m_itCurrHandler).m_pHandler,
                    (*pChain->m_itCurrHandler).m_nScope,
                    (*pChain->m_itCurrHandler).m_nLibId);
            }
        }
        pChain->fini ();
        m_ChainStore.push_back (pChain);
        unlock ();
        return Status;
    }
    else
    {
        *ppChain = pChain;
        unlock ();
        return Status;
    }
}

void HandlerPool::poolHandlerChain (HandlerChain* pChain, string &sSessionId)
{
    for (pChain->m_itCurrHandler = pChain->m_HandlerList.begin ();
        pChain->m_itCurrHandler != pChain->m_HandlerList.end ();
        pChain->m_itCurrHandler++)
    {
        if ((*pChain->m_itCurrHandler).m_pHandler != NULL)
        {
            poolHandler (sSessionId, (*pChain->m_itCurrHandler).m_pHandler,
                (*pChain->m_itCurrHandler).m_nScope, 
                (*pChain->m_itCurrHandler).m_nLibId);
        }
    }
    pChain->fini ();
    lock ();
    m_ChainStore.push_back (pChain);
    unlock ();
}

int HandlerPool::getWebService (BasicHandler** ppHandler, string &sSessionId,
    const WSDDHandler* pService)
{
    int Status;
    if ((Status = getHandler (ppHandler, sSessionId, pService->getScope (),
        pService->getLibId ())) == AXIS_SUCCESS)
    {
        if (0 != (*ppHandler)->_functions)
        /* C web service */
        {
            if (AXIS_SUCCESS !=
                (Status =
                (*ppHandler)->_functions->init ((*ppHandler)->_object)))
            {
                (*ppHandler)->_functions->fini ((*ppHandler)->_object);
                poolHandler (sSessionId, *ppHandler, pService->getScope (),
                    pService->getLibId ());
                *ppHandler = NULL;
            }
        }
        else if (0 == (*ppHandler)->_object)
            return AXIS_FAIL;
        else
        /* C++ web service */
        {
            if (AXIS_SUCCESS !=
                (Status =
                ((HandlerBase *) (*ppHandler)->_object)->init ()))
            {
                ((HandlerBase *) (*ppHandler)->_object)->fini ();
                poolHandler (sSessionId, *ppHandler, pService->getScope (),
                    pService->getLibId ());
                *ppHandler = NULL;
            }
        }
    }
    return Status;
}

void HandlerPool::poolWebService (string &sSessionId, BasicHandler* pHandler,
    const WSDDHandler * pHandlerInfo)
{
    poolHandler (sSessionId, pHandler, pHandlerInfo->getScope (),
        pHandlerInfo->getLibId ());
}
