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

// !!! This include file must be first thing in file !!!
#include "../platforms/PlatformAutoSense.hpp"

#include <axis/AxisException.hpp>

#include "HandlerPool.h"
#include "AppScopeHandlerPool.h"
#include "RequestScopeHandlerPool.h"
#include "SessionScopeHandlerPool.h"
#include "../wsdd/WSDDDeployment.h"

#include "../common/AxisTrace.h"

extern AXIS_CPP_NAMESPACE_PREFIX AppScopeHandlerPool* g_pAppScopeHandlerPool;
extern AXIS_CPP_NAMESPACE_PREFIX RequestScopeHandlerPool* g_pRequestScopeHandlerPool;
extern AXIS_CPP_NAMESPACE_PREFIX SessionScopeHandlerPool* g_pSessionScopeHandlerPool;
extern AXIS_CPP_NAMESPACE_PREFIX WSDDDeployment* g_pWSDDDeployment;

AXIS_CPP_NAMESPACE_START

HandlerPool::
HandlerPool ()
{
}

HandlerPool::
~HandlerPool ()
{
	logEntryEngine("HandlerPool::~HandlerPool")

    for (list <HandlerChain*>::iterator it = m_ChainStore.begin (); it != m_ChainStore.end (); it++)
    {
        delete (*it);
    }
	
    logExit()
}

int HandlerPool::
getHandler (BasicHandler** ppHandler, string & sSessionId, int nScope, int nLibId)
{
	logEntryEngine("HandlerPool::getHandler")

    *ppHandler = NULL;
    int Status = AXIS_FAIL;

    switch (nScope)
    {
        case AH_APPLICATION:
            do
            {
            	Status = g_pAppScopeHandlerPool->getInstance (ppHandler, nLibId);
                if (AXIS_SUCCESS == Status)
                	break;
                else if (Status == SERVER_ENGINE_HANDLER_BEING_USED)
                {             
                	//block this thread not this object
                    PLATFORM_SLEEP(0);
                }
                else
                    break;
            }
            while (Status == SERVER_ENGINE_HANDLER_BEING_USED);
            
            break;
            
        case AH_SESSION:
        	Status = g_pSessionScopeHandlerPool->getInstance (sSessionId, ppHandler, nLibId);
        	break;
        	
        case AH_REQUEST:
        	Status = g_pRequestScopeHandlerPool->getInstance (ppHandler, nLibId);
        	break;
    }
    
	logExitWithReturnCode(Status)
	
	return Status; 
}

int HandlerPool::
poolHandler (string &sSessionId, BasicHandler* pHandler, int nScope, int nLibId, bool bWebService)
{
	logEntryEngine("HandlerPool::poolHandler")

    switch (nScope)
    {
        case AH_APPLICATION:
            g_pAppScopeHandlerPool->putInstance (pHandler, nLibId);
            break;
        case AH_SESSION:
            g_pSessionScopeHandlerPool->putInstance (sSessionId, pHandler, nLibId);
            break;
        case AH_REQUEST:
            g_pRequestScopeHandlerPool->putInstance (pHandler, nLibId, bWebService);
            break;
    }
	
	logExitWithReturnCode(AXIS_SUCCESS)
	
    return AXIS_SUCCESS;
}

int HandlerPool::
getGlobalRequestFlowHandlerChain (HandlerChain** ppChain, string & sSessionId)
{
	logEntryEngine("HandlerPool::getGlobalRequestFlowHandlerChain")

    int Status = AXIS_SUCCESS;

    const WSDDHandlerList* pHandlerList = g_pWSDDDeployment->getGlobalRequestFlowHandlers ();
    if (pHandlerList)
    	Status = getHandlerChain (sSessionId, ppChain, pHandlerList);
    else
        *ppChain = NULL;
    
	logExitWithReturnCode(Status)
	
	return Status; 
}

int HandlerPool::
getGlobalResponseFlowHandlerChain (HandlerChain** ppChain, string &sSessionId)
{
	logEntryEngine("HandlerPool::getGlobalResponseFlowHandlerChain")

    int Status = AXIS_SUCCESS;

    const WSDDHandlerList *pHandlerList = g_pWSDDDeployment->getGlobalResponseFlowHandlers ();
    if (pHandlerList)
    	Status = getHandlerChain (sSessionId, ppChain, pHandlerList);
    else
        *ppChain = NULL;
    
	logExitWithReturnCode(Status)
	
	return Status; 
}

int HandlerPool::
getTransportRequestFlowHandlerChain (HandlerChain** ppChain, string &sSessionId, AXIS_PROTOCOL_TYPE Protocol)
{
	logEntryEngine("HandlerPool::getTransportRequestFlowHandlerChain")

    int Status = AXIS_SUCCESS;

    const WSDDHandlerList* pHandlerList = g_pWSDDDeployment->getTransportRequestFlowHandlers (Protocol);
    if (pHandlerList)
        Status = getHandlerChain (sSessionId, ppChain, pHandlerList);
    else
        *ppChain = NULL;
    
	logExitWithReturnCode(Status)
	
	return Status; 
}

int HandlerPool::
getTransportResponseFlowHandlerChain (HandlerChain** ppChain, string & sSessionId, AXIS_PROTOCOL_TYPE Protocol)
{
	logEntryEngine("HandlerPool::getTransportResponseFlowHandlerChain")

    int Status = AXIS_SUCCESS;

    const WSDDHandlerList* pHandlerList = g_pWSDDDeployment->getTransportResponseFlowHandlers (Protocol);
    if (pHandlerList)
        Status = getHandlerChain (sSessionId, ppChain, pHandlerList);
    else
        *ppChain = NULL;
    
	logExitWithReturnCode(Status)
	
	return Status;   
}

int HandlerPool::
getRequestFlowHandlerChain (HandlerChain** ppChain, string &sSessionId, const WSDDService* pService)
{
	logEntryEngine("HandlerPool::getRequestFlowHandlerChain")

    int Status = AXIS_SUCCESS;

    const WSDDHandlerList* pHandlerList = pService->getRequestFlowHandlers ();
    if (pHandlerList)
    	Status = getHandlerChain (sSessionId, ppChain, pHandlerList);
    else
        *ppChain = NULL;
    
	logExitWithReturnCode(Status)
	
	return Status;    
}

int HandlerPool::
getResponseFlowHandlerChain (HandlerChain** ppChain, string &sSessionId, const WSDDService* pService)
{
	logEntryEngine("HandlerPool::getResponseFlowHandlerChain")
	
    int Status = AXIS_SUCCESS;

    const WSDDHandlerList* pHandlerList = pService->getResponseFlowHandlers ();
    if (pHandlerList)
    	Status = getHandlerChain (sSessionId, ppChain, pHandlerList);
    else
        *ppChain = NULL;
    
	logExitWithReturnCode(Status)
	
	return Status;
}

int HandlerPool::
getHandlerChain (string &sSessionId, HandlerChain** ppChain, const WSDDHandlerList* pHandlerList)
{
	logEntryEngine("HandlerPool::getHandlerChain")

	Lock l(this);
    *ppChain = NULL;
    HandlerChain* pChain = NULL;
    
    // check m_ChainStore to get a HandlerChain
    if (!m_ChainStore.empty ())
    {
        pChain = m_ChainStore.front ();
        m_ChainStore.pop_front ();
        pChain->init ();
    }
    else
        pChain = new HandlerChain ();

    WSDDHandler* pWSDDH = NULL;
    BasicHandler* pBH = NULL;
    int Status = AXIS_SUCCESS;

    for (WSDDHandlerList::const_iterator it = pHandlerList->begin (); it != pHandlerList->end (); it++)
    {
        pWSDDH = (*it);
        if ((Status = getHandler (&pBH, sSessionId, pWSDDH->getScope (), pWSDDH->getLibId ())) == AXIS_SUCCESS)
        {
            if (0 != pBH->_functions)
            {
                /* C Handler */
            }
            else if (0 != pBH->_object)
            {
                if (NORMAL_HANDLER == ((Handler*) (pBH->_object))->getType ())
                {
                    ((Handler*) (pBH->_object))-> setOptionList (pWSDDH->getParameterList ());
                    pChain->addHandler (pBH, pWSDDH->getScope (), pWSDDH->getLibId ());
                }
                else
                {
                    Status = SERVER_ENGINE_WRONG_HANDLER_TYPE;
                    break;
                }
            }
        }
        else
            break;
    }
    
    
    if (Status != AXIS_SUCCESS) //some failure so undo whatever done here
    {
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
    }
    else
        *ppChain = pChain;
    
	logExitWithReturnCode(Status)
	
    return Status;
}

void HandlerPool::
poolHandlerChain (HandlerChain* pChain, string &sSessionId)
{
	logEntryEngine("HandlerPool::poolHandlerChain")

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

	Lock l(this);
    m_ChainStore.push_back (pChain);
    
    logExit()
}

int HandlerPool::
getWebService( BasicHandler ** ppHandler, string & sSessionId, const WSDDHandler * pService)
{
	logEntryEngine("HandlerPool::getWebService")

    int Status = getHandler( ppHandler, sSessionId, pService->getScope(), pService->getLibId());

    if( Status == AXIS_SUCCESS)
    {
        if( NULL != (*ppHandler)->_functions)
        // C web service 
        {
            /*if (AXIS_SUCCESS !=
                (Status =
                (*ppHandler)->_functions->init ((*ppHandler)->_object)))
            {
                (*ppHandler)->_functions->fini ((*ppHandler)->_object);
                poolHandler (sSessionId, *ppHandler, pService->getScope (),
                    pService->getLibId ());
                *ppHandler = NULL;
            }*/
        }
        else if( NULL == (*ppHandler)->_object)
		{
            Status = AXIS_FAIL;
		}
        else
        // C++ web service 
        {
            /*if (AXIS_SUCCESS !=
                (Status =
                ((HandlerBase *) (*ppHandler)->_object)->init ()))
            {
                ((HandlerBase *) (*ppHandler)->_object)->fini ();
                poolHandler (sSessionId, *ppHandler, pService->getScope (),
                    pService->getLibId ());
                *ppHandler = NULL;
            }*/
        }
    }
    
	logExitWithReturnCode(Status)

    return Status;
}

void HandlerPool::
poolWebService (string &sSessionId, BasicHandler* pHandler, const WSDDHandler * pHandlerInfo)
{
	logEntryEngine("HandlerPool::poolWebService")

    poolHandler (sSessionId, pHandler, pHandlerInfo->getScope (), pHandlerInfo->getLibId (), true);
	
    logExit()
}

AXIS_CPP_NAMESPACE_END
