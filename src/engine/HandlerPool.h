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

#if !defined(AFX_HANDLERPOOL_H__6C2A4C96_7115_43C6_9EFA_CDAC9247D109__INCLUDED_)
#define AFX_HANDLERPOOL_H__6C2A4C96_7115_43C6_9EFA_CDAC9247D109__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../wsdd/WSDDHandler.h"
#include "../wsdd/WSDDService.h"
#include "../common/BasicHandler.h"
#include "HandlerLoader.h"
#include "HandlerChain.h"

#include <map>
#include <string>

using namespace std;
/* HandlerPool loads, keeps and destroys all the handlers
 * 
 *
 *
 */
class HandlerPool  
{
private:
	class LoadedHandler {
	public:
		HandlerLoader* m_DL;
		BasicHandler* m_Handler;
		LoadedHandler(string &sFile, int nOptions=0);
		~LoadedHandler();
	};
public:
	void UnloadWebService(WSDDService* pService);
	BasicHandler* LoadWebService(WSDDService* pService);
	void UnLoadServiceRequestFlowHandlers(WSDDHandlerList *pHandlerList);
	void UnLoadServiceResponseFlowHandlers(WSDDHandlerList *pHandlerList);
	int LoadServiceResponseFlowHandlers(WSDDHandlerList* pHandlerList);
	int LoadServiceRequestFlowHandlers(WSDDHandlerList* pHandlerList);
	HandlerChain* GetTransportRequestFlowHandlerChain(AXIS_PROTOCOL_TYPE Protocol);
	HandlerChain* GetTransportResponseFlowHandlerChain(AXIS_PROTOCOL_TYPE Protocol);
	HandlerChain* GetGlobalResponseFlowHandlerChain();
	HandlerChain* GetGlobalRequestFlowHandlerChain();
	HandlerChain* GetServiceRequestFlowHandlerChain();
	HandlerChain* GetServiceResponseFlowHandlerChain();
	//Following will load handlers and keep them in private members.
	int LoadTransportRequestFlowHandlers(AXIS_PROTOCOL_TYPE Protocol, WSDDHandlerList* pHandlerList);
	int LoadTransportResponseFlowHandlers(AXIS_PROTOCOL_TYPE Protocol, WSDDHandlerList* pHandlerList);
	int LoadGlobalResponseFlowHandlers(WSDDHandlerList* pHandlerList);
	int LoadGlobalRequestFlowHandlers(WSDDHandlerList* pHandlerList);

	HandlerPool();
	virtual ~HandlerPool();
private:
	BasicHandler* GetHandler(WSDDHandler* pHandlerInfo);
	int UnLoadHandler(WSDDHandler* pHandlerInfo);
	BasicHandler* LoadHandler(WSDDHandler* pHandlerInfo);

private:
	void UnloadHandlerList(WSDDHandlerList *pHandlerList);
	HandlerChain* LoadHandlerChain(WSDDHandlerList* pHandlerList);
	map<string, LoadedHandler*> m_Handlers; //all handlers will be retained here
	HandlerChain* m_pGReqFChain; //Global Handler chain(Request)
	HandlerChain* m_pGResFChain; //Global Handler chain(Response)
	HandlerChain* m_pServiceReqFChain; //Service specific Handler chain(Request)
	HandlerChain* m_pServiceResFChain; //Service specific Handler chain(Response)
	map<AXIS_PROTOCOL_TYPE, HandlerChain*> m_TReqFChains; //Transport Handler chains (Request)
	map<AXIS_PROTOCOL_TYPE, HandlerChain*> m_TResFChains; //Transport Handler chains (Response)
};

#endif // !defined(AFX_HANDLERPOOL_H__6C2A4C96_7115_43C6_9EFA_CDAC9247D109__INCLUDED_)
