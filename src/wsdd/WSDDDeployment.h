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

// WSDDDeployment.h: interface for the WSDDDeployment class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning (disable : 4786)

#if !defined(AFX_WSDDDEPLOYMENT_H__2B3E0205_06F3_47C1_8D9C_479CBFB8ACC2__INCLUDED_)
#define AFX_WSDDDEPLOYMENT_H__2B3E0205_06F3_47C1_8D9C_479CBFB8ACC2__INCLUDED_

#include "WSDDService.h"
#include "WSDDHandler.h"
#include "WSDDTransport.h"

#include <list>

using namespace std;

class WSDDDeployment  
{
	friend class WSDDDocument;
public:
	int LoadWSDD(const AxisChar* sWSDD);
	int UpdateWSDD(const AxisChar* sWSDDNew);
	const AxisChar* GetLibName(int nLibId);
	const WSDDService* GetService(const AxisChar* sServiceName);
	const WSDDHandlerList* GetGlobalRequestFlowHandlers();
	const WSDDHandlerList* GetGlobalResponseFlowHandlers();
	const WSDDHandlerList* GetTransportRequestFlowHandlers(AXIS_PROTOCOL_TYPE protocol);
	const WSDDHandlerList* GetTransportResponseFlowHandlers(AXIS_PROTOCOL_TYPE protocol);
	const WSDDServiceMap* GetWSDDServiceMap() const;
	WSDDDeployment();
	virtual ~WSDDDeployment();
private: //methods that only be used by WSDDDepolyment.
	void SetLibIdMap(map<AxisString, int>* pLibNameIdMap);
	int AddService(WSDDService* pService);
	int AddHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler, AXIS_PROTOCOL_TYPE protocol=APTHTTP);
	int RemoveService(WSDDService* pService);
	int RemoveHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler, AXIS_PROTOCOL_TYPE protocol=APTHTTP);
private:
	WSDDServiceMap* m_DeployedServices;
	WSDDHandlerList* m_GlobalRequestHandlers;
	WSDDHandlerList* m_GlobalResponseHandlers;
	WSDDTransport* m_pTransportHandlers;
	map<AxisString, int>* m_pLibNameIdMap;
	AxisString m_sAux;
};

#endif // !defined(AFX_WSDDDEPLOYMENT_H__2B3E0205_06F3_47C1_8D9C_479CBFB8ACC2__INCLUDED_)
