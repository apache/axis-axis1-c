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
// SessionScopeHandlerPool.cpp: implementation of the SessionScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4503)

#include "SessionScopeHandlerPool.h"
#include "HandlerLoader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HandlerLoader* g_pHandlerLoader;

SessionScopeHandlerPool::SessionScopeHandlerPool()
{

}

SessionScopeHandlerPool::~SessionScopeHandlerPool()
{
	for (map<int, SessionHandlers*>::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++)
	{
		SessionHandlers* pSH = (*it).second;
		for (SessionHandlers::iterator itr = pSH->begin(); itr != pSH->end(); itr++)
		{
			for (list<BasicHandler*>::iterator ite = (*itr).second.begin(); ite != (*itr).second.end(); ite++)
			{
				g_pHandlerLoader->DeleteHandler(*ite, (*it).first);
			}
			(*itr).second.clear();
		}
		delete pSH;
	}
	m_Handlers.clear();
}

int SessionScopeHandlerPool::GetInstance(string& sSessionId, BasicHandler** pHandler, int nLibId)
{
	lock();
	int Status;
	if (m_Handlers.find(nLibId) != m_Handlers.end()) 
	{
		SessionHandlers* pSesHandlers = m_Handlers[nLibId];
		if (pSesHandlers->find(sSessionId) != pSesHandlers->end())
		{
			list<BasicHandler*> &HandlerList = ((*pSesHandlers)[sSessionId]);
			if (HandlerList.empty())
			{
				//check in the store for reuse
				if ((*pSesHandlers)[SESSIONLESSHANDLERS].empty())
				{
					unlock();
					return g_pHandlerLoader->CreateHandler(pHandler, nLibId);
				}
				else
				{
					*pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front();
					(*pSesHandlers)[SESSIONLESSHANDLERS].pop_front();
					unlock();
					return SUCCESS;
				}
			}
			else
			{
				*pHandler = HandlerList.front();
				HandlerList.pop_front();
				unlock();
				return SUCCESS;
			}
			unlock();
			return g_pHandlerLoader->CreateHandler(pHandler, nLibId);
		}
		else //no handler list for this session id
		{
			//check in the store for reuse
			if ((*pSesHandlers)[SESSIONLESSHANDLERS].empty())
			{
				unlock();
				return g_pHandlerLoader->CreateHandler(pHandler, nLibId);
			}
			else
			{
				*pHandler = (*pSesHandlers)[SESSIONLESSHANDLERS].front();
				(*pSesHandlers)[SESSIONLESSHANDLERS].pop_front();
				unlock();
				return SUCCESS;
			}
		}
	}
	else //not even the handler DLL loaded
	{
		Status = g_pHandlerLoader->CreateHandler(pHandler, nLibId);
		if (SUCCESS == Status)
		{
			//this just creates the entry in m_Handlers so that next time we know that the DLL is loaded
			SessionHandlers* pNewSH = new SessionHandlers;
			pNewSH->clear();
			m_Handlers[nLibId] = pNewSH;	
		}
		unlock();
		return Status;
	}
}

int SessionScopeHandlerPool::PutInstance(string& sSessionId, BasicHandler* pHandler, int nLibId)
{
	lock();
	SessionHandlers* pSesHandlers;
	if (m_Handlers.find(nLibId) != m_Handlers.end())
	{
		pSesHandlers = m_Handlers[nLibId];
	}
	else // this is unexpected situation. anyway do it
	{
		pSesHandlers = new SessionHandlers;
		pSesHandlers->clear();
		m_Handlers[nLibId] = pSesHandlers;	
	}
	list<BasicHandler*> &HandlerList = ((*pSesHandlers)[sSessionId]);
	HandlerList.push_back(pHandler);
	unlock();
	return SUCCESS;
}

void SessionScopeHandlerPool::EndSession(string& sSessionId)
{
	//traverse all the lists and remove corresponding handlers if any and put to SESSIONLESSHANDLERS	
}
