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

// HandlerChain.cpp: implementation of the HandlerChain class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/engine/HandlerChain.h>
#include <axis/common/AxisTrace.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HandlerChain::HandlerChain()
{
}

HandlerChain::~HandlerChain()
{
	//nothing to do because the list keeps only pointers to objects that belongs to
	//Handler pool;
}

int HandlerChain::Invoke(IMessageData* pMsg)
{
	AXISTRACE1("HandlerChain::Invoke(IMessageData* pMsg)");
	m_itCurrHandler = m_HandlerList.begin();
	while (m_itCurrHandler != m_HandlerList.end())
	{
        AXISTRACE1("before handler invoke");
		if (AXIS_SUCCESS == (*m_itCurrHandler).m_pHandler->Invoke(pMsg))
		{
            AXISTRACE1("handler invoked");
			m_itCurrHandler++;
		}
		else
		{
            AXISTRACE1("handler invoke not successful");
			OnFault(pMsg);
			return AXIS_FAIL;
		}
	}
	AXISTRACE1("HandlerChain::Invoke end");
	return AXIS_SUCCESS;
}

void HandlerChain::OnFault(IMessageData* pMsg)
{
	while (m_itCurrHandler != m_HandlerList.begin())
	{
		(*m_itCurrHandler).m_pHandler->OnFault(pMsg);
		m_itCurrHandler--;
	}
}

int HandlerChain::AddHandler(Handler* pHandler, int nScope, int nLibId)
{
	ChainItem item;
	item.m_pHandler = pHandler;
	item.m_nScope = nScope;
	item.m_nLibId = nLibId;
	m_HandlerList.push_back(item);
    AXISTRACE1("andlerChain::AddHandler AXIS_SUCCESS");
	return AXIS_SUCCESS;
}

int HandlerChain::Init()
{
	m_HandlerList.clear();
	return AXIS_SUCCESS;
}

int HandlerChain::Fini()
{
	m_HandlerList.clear();
	return AXIS_SUCCESS;	
}
