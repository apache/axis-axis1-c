/* -*- C++ -*- */

/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */

// HandlerPool.cpp: implementation of the HandlerPool class.
//
//////////////////////////////////////////////////////////////////////

#include "HandlerPool.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "../common/Debug.h"

HandlerPool::HandlerPool()
{
	m_pGReqFChain = NULL;
	m_pGResFChain = NULL;
	m_pServiceReqFChain = NULL;
	m_pServiceResFChain = NULL;	
}

HandlerPool::~HandlerPool()
{
	//unload all the handlers
	LoadedHandler* pLh = NULL;
	for (map<string, LoadedHandler*>::iterator it = m_Handlers.begin();
	it != m_Handlers.end(); it++)
	{
		pLh = (*it).second;
		pLh->m_DL->Finalize();
		delete pLh;
	}
	m_Handlers.clear();

	//delete all handlers and chains etc
	if(m_pGReqFChain) delete m_pGReqFChain;
	if(m_pGResFChain) delete m_pGResFChain;
	if(m_pServiceReqFChain) delete m_pServiceReqFChain;
	if(m_pServiceResFChain) delete m_pServiceResFChain;

	map<AXIS_PROTOCOL_TYPE, HandlerChain*>::iterator it1;
	for (it1 = m_TReqFChains.begin();it1 != m_TReqFChains.end(); it1++)
	{
		delete (*it1).second;
	}
	for (it1 = m_TResFChains.begin();it1 != m_TResFChains.end(); it1++)
	{
		delete (*it1).second;
	}
}

HandlerPool::LoadedHandler::LoadedHandler(string &sFile, int nOptions)
{
	m_DL = new HandlerLoader(sFile, nOptions);
	m_Handler = NULL;
}

HandlerPool::LoadedHandler::~LoadedHandler()
{
	delete m_DL;
}

BasicHandler* HandlerPool::LoadHandler(WSDDHandler *pHandlerInfo)
{
	LoadedHandler* pLh = NULL;
	if (pHandlerInfo) 
	{
    
		pLh = new LoadedHandler(pHandlerInfo->GetLibName(), RTLD_LAZY);

		if (SUCCESS == pLh->m_DL->Initialize())
		{

			BasicHandler* pBh = pLh->m_DL->GetHandler();
      //BasicHandler* pBh = NULL;
			if (pBh) 
			{
				pLh->m_Handler = pBh;
				//Add to m_Handlers - place holder
				m_Handlers[pHandlerInfo->GetLibName()] = pLh;
				return pBh;
			}
			else
			{
				//something wrong
        return NULL;
			}
		}
		else
		{
			//Uninitialize, unload and delete pLh
		}
	}
	return NULL;
}

int HandlerPool::UnLoadHandler(WSDDHandler *pHandlerInfo)
{
	LoadedHandler* pLh = NULL;
	if (m_Handlers.find(pHandlerInfo->GetLibName()) != m_Handlers.end())
	{
		pLh = m_Handlers[pHandlerInfo->GetLibName()];
		pLh->m_DL->Finalize();
		m_Handlers.erase(pHandlerInfo->GetLibName());
		delete pLh;
		return SUCCESS;
	}
	return FAIL;
}

BasicHandler* HandlerPool::GetHandler(WSDDHandler *pHandlerInfo)
{
	if (m_Handlers.find(pHandlerInfo->GetLibName()) != m_Handlers.end())
	{
		return m_Handlers[pHandlerInfo->GetLibName()]->m_Handler;
	}
	return NULL;
}

HandlerChain* HandlerPool::GetGlobalRequestFlowHandlerChain()
{
	return m_pGReqFChain;
}

HandlerChain* HandlerPool::GetGlobalResponseFlowHandlerChain()
{
	return m_pGResFChain;
}

HandlerChain* HandlerPool::GetTransportRequestFlowHandlerChain(AXIS_PROTOCOL_TYPE Protocol)
{
	if (m_TReqFChains.find(Protocol) != m_TReqFChains.end())
		return m_TReqFChains[Protocol];
	return NULL;
}

HandlerChain* HandlerPool::GetTransportResponseFlowHandlerChain(AXIS_PROTOCOL_TYPE Protocol)
{
	if (m_TReqFChains.find(Protocol) != m_TReqFChains.end())
		return m_TResFChains[Protocol];
	return NULL;
}

HandlerChain* HandlerPool::GetServiceRequestFlowHandlerChain()
{
	return m_pServiceReqFChain;
}

HandlerChain* HandlerPool::GetServiceResponseFlowHandlerChain()
{
	return m_pServiceResFChain;
}

int HandlerPool::LoadTransportRequestFlowHandlers(AXIS_PROTOCOL_TYPE Protocol, WSDDHandlerList* pHandlerList)
{
	HandlerChain* pHc = LoadHandlerChain(pHandlerList);
	if (pHc)
	{
		m_TReqFChains[Protocol] = pHc;
		return SUCCESS;
	}
	return FAIL;
}

int HandlerPool::LoadTransportResponseFlowHandlers(AXIS_PROTOCOL_TYPE Protocol, WSDDHandlerList* pHandlerList)
{
	HandlerChain* pHc = LoadHandlerChain(pHandlerList);
	if (pHc)
	{
		m_TResFChains[Protocol] = pHc;
		return SUCCESS;
	}
	return FAIL;
}

int HandlerPool::LoadGlobalResponseFlowHandlers(WSDDHandlerList* pHandlerList)
{
	m_pGResFChain = LoadHandlerChain(pHandlerList);
	return (m_pGResFChain != NULL) ? SUCCESS:FAIL;
}

int HandlerPool::LoadGlobalRequestFlowHandlers(WSDDHandlerList* pHandlerList)
{
	m_pGReqFChain = LoadHandlerChain(pHandlerList);
	return (m_pGReqFChain != NULL) ? SUCCESS:FAIL;
}

int HandlerPool::LoadServiceRequestFlowHandlers(WSDDHandlerList *pHandlerList)
{
	m_pServiceReqFChain = LoadHandlerChain(pHandlerList);
	return (m_pServiceReqFChain != NULL) ? SUCCESS:FAIL;
}

int HandlerPool::LoadServiceResponseFlowHandlers(WSDDHandlerList *pHandlerList)
{
	m_pServiceResFChain = LoadHandlerChain(pHandlerList);
	return (m_pServiceResFChain != NULL) ? SUCCESS:FAIL;
}

void HandlerPool::UnLoadServiceRequestFlowHandlers(WSDDHandlerList *pHandlerList)
{
	UnloadHandlerList(pHandlerList);
	delete m_pServiceReqFChain;
	m_pServiceReqFChain = NULL;
}

void HandlerPool::UnLoadServiceResponseFlowHandlers(WSDDHandlerList *pHandlerList)
{
	UnloadHandlerList(pHandlerList);
	delete m_pServiceResFChain;
	m_pServiceResFChain = NULL;
}

HandlerChain* HandlerPool::LoadHandlerChain(WSDDHandlerList *pHandlerList)
{
	DEBUG1("HandlerPool::LoadHandlerChain");
	int nLoaded = 0;
	HandlerChain* pHc = NULL;
	if (pHandlerList && !pHandlerList->empty())
	{
		pHc = new HandlerChain();
		//BasicHandler* pBh = NULL;;
		Handler* pH = NULL;
		for (WSDDHandlerList::iterator it=pHandlerList->begin(); it != pHandlerList->end(); it++)
		{
			//if ((pBh = LoadHandler(*it)) != NULL)
			DEBUG1("BEFORE BasicHandler *pBh = LoadHandler(*it);");
			BasicHandler *pBh = LoadHandler(*it);
			DEBUG1("AFTER BasicHandler *pBh = LoadHandler(*it);");
			if (pBh)
			{
				DEBUG1("BEFORE pH = dynamic_cast<Handler*>(pBh);");
				if (pBh->GetType() == NORMAL_HANDLER)
					pH = static_cast<Handler*>(pBh);
				else
					pH = NULL;
				DEBUG1("AFTER pH = dynamic_cast<Handler*>(pBh);");
				if (pH)
				{          
					DEBUG1("if (pH)");
					pH->SetOptionList((*it)->GetOptionList());
					nLoaded++;
					pHc->AddHandler(pH);
				}
				else
				{
					return NULL;
				}
			}
		}
		if (0!=nLoaded) 
		{
			return pHc;
		}
		else 
		{
			delete pHc;
			return NULL;
		}
	}
	return NULL;
}

void HandlerPool::UnloadHandlerList(WSDDHandlerList *pHandlerList)
{
	if (pHandlerList && !pHandlerList->empty()) {
		for (WSDDHandlerList::iterator it=pHandlerList->begin();
		it != pHandlerList->end(); it++)
		{
			UnLoadHandler(*it);
		}
	}
}

BasicHandler* HandlerPool::LoadWebService(WSDDService* pService)
{
	return LoadHandler(pService);
}

void HandlerPool::UnloadWebService(WSDDService* pService)
{
	UnLoadHandler(pService);
}
