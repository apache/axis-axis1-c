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

// AppScopeHandlerPool.cpp: implementation of the AppScopeHandlerPool class.
//
//////////////////////////////////////////////////////////////////////

#include "AppScopeHandlerPool.h"
#include "HandlerLoader.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HandlerLoader* g_pHandlerLoader;

//this class does not do the object level blocking. Instead expects the 
//thread level blocking and waiting by the caller thread.
AppScopeHandlerPool::AppScopeHandlerPool()
{

}

AppScopeHandlerPool::~AppScopeHandlerPool()
{
	for (map<int, list<BasicHandler*> >::iterator it = m_Handlers.begin(); it != m_Handlers.end(); it++)
	{
		for (list<BasicHandler*>::iterator itr = (*it).second.begin(); itr != (*it).second.end(); itr++)
		{
			g_pHandlerLoader->DeleteHandler(*itr, (*it).first);
		}
		(*it).second.clear();
	}
	m_Handlers.clear();
}

//this method does not block the object. Instead expects that the calling thread 
//MUST block itself and wait if the requested handler is not found.
int AppScopeHandlerPool::GetInstance(BasicHandler** pHandler, int nLibId)
{
	lock();
	int Status;
	if (m_Handlers.find(nLibId) != m_Handlers.end()) 
	{
		if (m_Handlers[nLibId].empty()) 
		// this means that the object is being used by some other thread
		// but we cannot create any more objects because this is an application
		// scope object. So just return HANDLER_BEING_USED
		{
			unlock();
			return HANDLER_BEING_USED;
		}
		else
		{
			*pHandler = m_Handlers[nLibId].front();
			m_Handlers[nLibId].pop_front();
			unlock();
			return AXIS_SUCCESS;
		}
	}
	else //not even the handler DLL loaded
	{
		Status = g_pHandlerLoader->CreateHandler(pHandler, nLibId);
		if (AXIS_SUCCESS == Status)
		{
			//this just creates the entry in m_Handlers so that next time we know that the DLL is loaded
			m_Handlers[nLibId].clear();	
		}
		unlock();
		return Status;
	}
}

int AppScopeHandlerPool::PutInstance(BasicHandler* pHandler, int nLibId)
{
	lock();
	m_Handlers[nLibId].push_back(pHandler);
	unlock();
	return AXIS_SUCCESS;
}
