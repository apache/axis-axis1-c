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

// HandlerPool.h: interface for the HandlerPool class.
//
//////////////////////////////////////////////////////////////////////
#ifdef WIN32
#pragma warning (disable : 4503)
#endif

#if !defined(AFX_HANDLERPOOL_H__6C2A4C96_7115_43C6_9EFA_CDAC9247D109__INCLUDED_)
#define AFX_HANDLERPOOL_H__6C2A4C96_7115_43C6_9EFA_CDAC9247D109__INCLUDED_

#include "../wsdd/WSDDHandler.h"
#include "../wsdd/WSDDService.h"
#include "../common/BasicHandler.h"
#include "HandlerLoader.h"
#include "HandlerChain.h"
#include "SharedObject.h"

#include <list>
#include <string>

using namespace std;
/* HandlerPool loads, keeps and destroys all the handlers
 * 
 *
 *
 */
class HandlerPool : protected SharedObject
{
private:
	int GetHandler(BasicHandler** ppHandler, string& sSessionId, int nScope, int nLibId);
	int PoolHandler(string& sSessionId, BasicHandler* pHandler, int nScope, int nLibId);
	int GetHandlerChain(string& sSessionId, HandlerChain** pChain, const WSDDHandlerList* pHandlerList);
public:
	int GetGlobalRequestFlowHandlerChain(HandlerChain** ppChain, string& sSessionId);
	int GetGlobalResponseFlowHandlerChain(HandlerChain** ppChain, string& sSessionId);
	int GetTransportRequestFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, AXIS_PROTOCOL_TYPE Protocol);
	int GetTransportResponseFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, AXIS_PROTOCOL_TYPE Protocol);
	int GetRequestFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, const WSDDService* pService);
	int GetResponseFlowHandlerChain(HandlerChain** ppChain, string& sSessionId, const WSDDService* pService);
	void PoolHandlerChain(HandlerChain* pChain, string& sSessionId);

	int GetWebService(BasicHandler** ppHandler, string& sSessionId, const WSDDHandler* pService);
	void PoolWebService(string& sSessionId, BasicHandler* pHandler, const WSDDHandler* pHandlerInfo);

	HandlerPool();
	virtual ~HandlerPool();
private:
	list<HandlerChain*> m_ChainStore;
};

#endif // !defined(AFX_HANDLERPOOL_H__6C2A4C96_7115_43C6_9EFA_CDAC9247D109__INCLUDED_)
