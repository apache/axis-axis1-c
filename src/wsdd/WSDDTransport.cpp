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
 * @author Sanjaya Singharage
 *
 */

// WSDDTransport.cpp: implementation of the WSDDTransport class.
//
//////////////////////////////////////////////////////////////////////

#include "WSDDTransport.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WSDDTransport::WSDDTransport()
{
	m_RequestHandlers = NULL;
	m_ResponseHandlers = NULL;
}

WSDDTransport::~WSDDTransport()
{
	map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>::iterator iter;
	WSDDHandlerList * hl = NULL;
	WSDDHandlerList::iterator iter2;
	if(m_RequestHandlers)
	{
		for(iter = m_RequestHandlers->begin(); iter != m_RequestHandlers->end(); iter++)
		{
			for(iter2 = (*iter).second.begin(); iter2 != (*iter).second.end(); iter2++)
			{
				delete (*iter2);
			}
		}
	}

	if(m_ResponseHandlers)
	{
		for(iter = m_ResponseHandlers->begin(); iter != m_ResponseHandlers->end(); iter++)
		{
			for(iter2 = (*iter).second.begin(); iter2 != (*iter).second.end();iter2++)
			{
				delete (*iter2);
			}
		}
	}

}

const WSDDHandlerList* WSDDTransport::GetRequestFlowHandlers(AXIS_PROTOCOL_TYPE Protocol)
{
	if (m_RequestHandlers && m_RequestHandlers->find(Protocol) != m_RequestHandlers->end())
		return &(*m_RequestHandlers)[Protocol];
	return NULL;
}


const WSDDHandlerList* WSDDTransport::GetResponseFlowHandlers(AXIS_PROTOCOL_TYPE Protocol)
{
	if (m_ResponseHandlers && m_ResponseHandlers->find(Protocol) != m_ResponseHandlers->end())
		return &(*m_ResponseHandlers)[Protocol];
	return NULL;
}

void WSDDTransport::AddHandler(bool bRequestFlow, AXIS_PROTOCOL_TYPE protocol, WSDDHandler* pHandler)
{
	if (bRequestFlow)
	{
		if (!m_RequestHandlers) m_RequestHandlers = new map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>;
		(*m_RequestHandlers)[protocol].push_back(pHandler);
	}
	else
	{
		if (!m_ResponseHandlers) m_ResponseHandlers = new map<AXIS_PROTOCOL_TYPE, WSDDHandlerList>;
		(*m_ResponseHandlers)[protocol].push_back(pHandler);
	}
}
