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
#include "AppScopeHandlerPool.h"
#include "RequestScopeHandlerPool.h"
#include "SessionScopeHandlerPool.h"
#include "../wsdd/WSDDDeployment.h"
#include <axis/server/AxisTrace.h>
extern AxisTrace* g_pAT;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern AppScopeHandlerPool* g_pAppScopeHandlerPool;
extern RequestScopeHandlerPool* g_pRequestScopeHandlerPool;
extern SessionScopeHandlerPool* g_pSessionScopeHandlerPool;
extern WSDDDeployment* g_pWSDDDeployment;

HandlerPool::HandlerPool()
{
}

HandlerPool::~HandlerPool()
{
	for (list<HandlerChain*>::iterator it = m_ChainStore.begin(); it != m_ChainStore.end(); it++)
	{
		delete (*it);
	}
}

int HandlerPool::GetHandler(BasicHandler** ppHandler, string& sSessionId, int nScope, int nLibId)
{
	*ppHandler = NULL;
	int Status = AXIS_FAIL;

	switch (nScope)
	{
	case AH_APPLICATION:
		do {
			if ((Status = g_pAppScopeHandlerPool->GetInstance(ppHandler, nLibId)) == AXIS_SUCCESS)
			{
				return Status;
			}
			else if (Status == HANDLER_BEING_USED)
			{ //block this thread not this object
				Ax_Sleep(0);
			}
			else
			{
				return Status;
			}
		} while (Status == HANDLER_BEING_USED);
		break;
	case AH_SESSION:
		return g_pSessionScopeHandlerPool->GetInstance(sSessionId, ppHandler, nLibId);
	case AH_REQUEST:
		return g_pRequestScopeHandlerPool->GetInstance(ppHandler, nLibId);
	}
	return Status;
}

int HandlerPool::PoolHandler(string& sSessionId, BasicHandler* pHandler, int nScope, int nLibId)
{
	switch (nScope)
	{
	case AH_APPLICATION:
		g_pAppScopeHandlerPool->PutInstance(pHandler, nLibId);
		break;
	case AH_SESSION:
		g_pSessionScopeHandlerPool->PutInstance(sSessionId, pHandler, nLibId);
		break;
	case AH_REQUEST:
		g_pRequestScopeHandlerPool->PutInstance(pHandler, nLibId);
		break;
	}
	return AXIS_SUCCESS;
}

int HandlerPool::GetGlobalRequestFlowHandlerChain(HandlerChain** ppChain, string& sSessionId)
{
	const WSDDHandlerList* pHandlerList = g_pWSDDDeployment->GetGlobalRequestFlowHandlers();
	if (pHandlerList)
	{
		return GetHandlerChain(sSessionId, ppChain, pHandlerList);
	}
	else
	{
		*ppChain = NULL;
		return AXIS_SUCCESS; //NO_HANDLERS_CONFIGURED
	}
}

int HandlerPool::GetGlobalResponseFlowHandlerChain(HandlerChain** ppChain, string& sSessionId)
{
	const WSDDHandlerList* pHandlerList = g_pWSDDDeployment->GetGlobalResponseFlowHandlers();
	if (pHandlerList)
	{
		return GetHandlerChain(sSessionId, ppChain, pHandlerList);
	}
	else
	{
		*ppChain = NULL;
		return AXIS_SUCCESS; //NO_HANDLERS_CONFIGURED
	}
}

int HandlerPool::GetTransportRequestFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, AXIS_PROTOCOL_TYPE Protocol)
{
	const WSDDHandlerList* pHandlerList = g_pWSDDDeployment->GetTransportRequestFlowHandlers(Protocol);
	if (pHandlerList)
	{
		return GetHandlerChain(sSessionId, ppChain, pHandlerList);
	}
	else
	{
		*ppChain = NULL;
		return AXIS_SUCCESS; //NO_HANDLERS_CONFIGURED
	}
}

int HandlerPool::GetTransportResponseFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, AXIS_PROTOCOL_TYPE Protocol)
{
	const WSDDHandlerList* pHandlerList = g_pWSDDDeployment->GetTransportResponseFlowHandlers(Protocol);
	if (pHandlerList)
	{
		return GetHandlerChain(sSessionId, ppChain, pHandlerList);
	}
	else
	{
		*ppChain = NULL;
		return AXIS_SUCCESS; //NO_HANDLERS_CONFIGURED
	}
}

int HandlerPool::GetRequestFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, const WSDDService* pService)
{
	const WSDDHandlerList* pHandlerList = pService->GetRequestFlowHandlers();
	if (pHandlerList)
	{        
		return GetHandlerChain(sSessionId, ppChain, pHandlerList);
	}
	else
	{
		*ppChain = NULL;
        AXISTRACE1("No handlers configured", INFO);        
		return AXIS_SUCCESS; //NO_HANDLERS_CONFIGURED
	}
}

int HandlerPool::GetResponseFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, const WSDDService* pService)
{
	const WSDDHandlerList* pHandlerList = pService->GetResponseFlowHandlers();
	if (pHandlerList)
	{        
		return GetHandlerChain(sSessionId, ppChain, pHandlerList);
	}
	else
	{
		*ppChain = NULL;
		return AXIS_SUCCESS; //NO_HANDLERS_CONFIGURED
	}
}

int HandlerPool::GetHandlerChain(string& sSessionId, HandlerChain** ppChain, const WSDDHandlerList *pHandlerList)
{
	lock();
	*ppChain = NULL;
	HandlerChain* pChain;
	//check m_ChainStore to get a HandlerChain
	if (!m_ChainStore.empty())
	{
		pChain = m_ChainStore.front();
		m_ChainStore.pop_front();
		pChain->Init();
	}
	else
	{
		pChain = new HandlerChain();
	}

	WSDDHandler* pWSDDH;
	BasicHandler* pBH;
	int Status = AXIS_SUCCESS;

	for (WSDDHandlerList::const_iterator it = pHandlerList->begin(); it != pHandlerList->end(); it++)
	{
		pWSDDH = (*it);
		if ((Status = GetHandler(&pBH, sSessionId, pWSDDH->GetScope(),pWSDDH->GetLibId())) == AXIS_SUCCESS)
		{
			/*
			if (NORMAL_HANDLER == pBH->_functions->GetType(pBH->_object))
			{                
				((Handler*)(pBH->_object))->SetOptionList(pWSDDH->GetParameterList());                
				pChain->AddHandler(pBH, pWSDDH->GetScope(), pWSDDH->GetLibId());                
			}
			else
			{
				Status = WRONG_HANDLER_TYPE;
				break;
			}
			*/

			if (0 != pBH->_functions) 
			{
				/* C Handler */
			} 
			else if (0 != pBH->_object) 
			{
				if (NORMAL_HANDLER == ((Handler*)(pBH->_object))->GetType())
				{                
					((Handler*)(pBH->_object))->SetOptionList(pWSDDH->GetParameterList());                
					pChain->AddHandler(pBH, pWSDDH->GetScope(), pWSDDH->GetLibId());                
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
        AXISTRACE1("Handler failure", WARN);        
		string nosession = SESSIONLESSHANDLERS;
		for (pChain->m_itCurrHandler = pChain->m_HandlerList.begin(); pChain->m_itCurrHandler != pChain->m_HandlerList.end(); pChain->m_itCurrHandler++)
		{
			if ((*pChain->m_itCurrHandler).m_pHandler != NULL)
			{
				PoolHandler(nosession, (*pChain->m_itCurrHandler).m_pHandler, (*pChain->m_itCurrHandler).m_nScope, (*pChain->m_itCurrHandler).m_nLibId);
			}
		}
		pChain->Fini();
		m_ChainStore.push_back(pChain);
		unlock();
		return Status;
	}
	else
	{
		*ppChain = pChain;
		unlock();
		return Status;
	}
}

void HandlerPool::PoolHandlerChain(HandlerChain* pChain, string& sSessionId)
{
	for (pChain->m_itCurrHandler = pChain->m_HandlerList.begin(); pChain->m_itCurrHandler != pChain->m_HandlerList.end(); pChain->m_itCurrHandler++)
	{
		if ((*pChain->m_itCurrHandler).m_pHandler != NULL)
		{
			PoolHandler(sSessionId, (*pChain->m_itCurrHandler).m_pHandler, (*pChain->m_itCurrHandler).m_nScope, (*pChain->m_itCurrHandler).m_nLibId);
		}
	}
	pChain->Fini();
	lock();
	m_ChainStore.push_back(pChain);
	unlock();
}

int HandlerPool::GetWebService(BasicHandler** ppHandler, string& sSessionId, const WSDDHandler* pService)
{
	int Status;
	if ((Status = GetHandler(ppHandler, sSessionId, pService->GetScope(), pService->GetLibId())) == AXIS_SUCCESS)
	{
		if (0 != (*ppHandler)->_functions)
		/* C web service */
		{
			if (AXIS_SUCCESS != (Status = (*ppHandler)->_functions->Init((*ppHandler)->_object)))
			{
				(*ppHandler)->_functions->Fini((*ppHandler)->_object);
				PoolHandler(sSessionId, *ppHandler, pService->GetScope(), pService->GetLibId());
				*ppHandler = NULL;
			}
		}
		else if (0 == (*ppHandler)->_object) return AXIS_FAIL;
		else
		/* C++ web service */
		{
			if (AXIS_SUCCESS != (Status = ((HandlerBase*)(*ppHandler)->_object)->Init()))
			{
				((HandlerBase*)(*ppHandler)->_object)->Fini();
				PoolHandler(sSessionId, *ppHandler, pService->GetScope(), pService->GetLibId());
				*ppHandler = NULL;
			}
		}
	}
	return Status;
}

void HandlerPool::PoolWebService(string& sSessionId, BasicHandler* pHandler, const WSDDHandler *pHandlerInfo)
{
	PoolHandler(sSessionId, pHandler, pHandlerInfo->GetScope(), pHandlerInfo->GetLibId());
}
