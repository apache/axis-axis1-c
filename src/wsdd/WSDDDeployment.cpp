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

// WSDDDeployment.cpp: implementation of the WSDDDeployment class.
//
//////////////////////////////////////////////////////////////////////

#include "WSDDDeployment.h"
#include "WSDDDocument.h"
#include "../common/GDefine.h"
#include <iostream>

extern unsigned char chEBuf[1024];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WSDDDeployment::WSDDDeployment()
{
	m_DeployedServices = NULL;
	m_sAux = L"";
	m_pTransportHandlers = NULL;

	m_GlobalResponseHandlers = NULL;
	m_GlobalRequestHandlers = NULL;
}

WSDDDeployment::~WSDDDeployment()
{
	WSDDHandlerList::iterator iter;
	if(m_pTransportHandlers)
	{
		delete m_pTransportHandlers;
	}

	if(m_GlobalRequestHandlers)
	{
		for(iter=m_GlobalRequestHandlers->begin();
				iter!=m_GlobalRequestHandlers->end();iter++)
		{
			delete (*iter);
		}
	}

	if(m_GlobalResponseHandlers)
	{
		for(iter=m_GlobalResponseHandlers->begin();
				iter!=m_GlobalResponseHandlers->end();iter++)
		{
			delete (*iter);
		}
	}

	WSDDServiceMap::iterator iter2;
	if(m_DeployedServices)
	{
		for(iter2=m_DeployedServices->begin()
				;iter2!=m_DeployedServices->end();iter2++)
		{
			delete (iter2->second);
		}
	}

}

void WSDDDeployment::SetLibIdMap(map<AxisString, int>* pLibNameIdMap)
{
	m_pLibNameIdMap = pLibNameIdMap;
}


const WSDDHandlerList* WSDDDeployment::GetGlobalRequestFlowHandlers()
{
	return m_GlobalRequestHandlers;
}

const WSDDHandlerList* WSDDDeployment::GetGlobalResponseFlowHandlers()
{
	return m_GlobalResponseHandlers;
}

int WSDDDeployment::LoadWSDD(string &sWSDD)
{
	WSDDDocument doc;
	if (SUCCESS != doc.GetDeployment(sWSDD, this))
	{
		return FAIL;
	}
	return SUCCESS;
}

int WSDDDeployment::UpdateWSDD(string& sWSDDNew)
{
	//TODO
	return SUCCESS;
}


const WSDDService* WSDDDeployment::GetService(const AxisString &sServiceName)
{
	WSDDServiceMap::iterator iter;

	iter = m_DeployedServices->find(sServiceName);
	if (iter != m_DeployedServices->end())
	{
		return (*iter).second;
	}
	else
	{
		return NULL;
	}
}

const WSDDServiceMap* WSDDDeployment::GetWSDDServiceMap()
{
	return m_DeployedServices;
}

const AxisString& WSDDDeployment::GetLibName(int nLibId)
{
	for (map<AxisString, int>::iterator it = m_pLibNameIdMap->begin(); it != m_pLibNameIdMap->end(); it++)
	{
		if ((*it).second == nLibId)
			return (*it).first;
	}
	return m_sAux;
}

int WSDDDeployment::AddService(WSDDService* pService)
{
	if (!m_DeployedServices) m_DeployedServices = new WSDDServiceMap;
	(*m_DeployedServices)[pService->GetServiceName().c_str()] = pService;
	return SUCCESS;
}		

int WSDDDeployment::AddHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler, AXIS_PROTOCOL_TYPE protocol)
{
	if (bGlobal)
	{
		if (bRequestFlow)
		{
			if(!m_GlobalRequestHandlers) m_GlobalRequestHandlers = new WSDDHandlerList;
			m_GlobalRequestHandlers->push_back(pHandler);
		}
		else
		{
			if(!m_GlobalResponseHandlers) m_GlobalResponseHandlers = new WSDDHandlerList;
			m_GlobalResponseHandlers->push_back(pHandler);
		}
	}
	else //transport
	{
		if (!m_pTransportHandlers) m_pTransportHandlers = new WSDDTransport();
		m_pTransportHandlers->AddHandler(bRequestFlow, protocol, pHandler);
	}
	return SUCCESS;
}

const WSDDHandlerList* WSDDDeployment::GetTransportRequestFlowHandlers(AXIS_PROTOCOL_TYPE protocol)
{
	if (!m_pTransportHandlers) return NULL;
	return m_pTransportHandlers->GetRequestFlowHandlers(protocol);
}

const WSDDHandlerList* WSDDDeployment::GetTransportResponseFlowHandlers(AXIS_PROTOCOL_TYPE protocol)
{
	if (!m_pTransportHandlers) return NULL;
	return m_pTransportHandlers->GetResponseFlowHandlers(protocol);
}

int WSDDDeployment::RemoveService(WSDDService* pService)
{
	return SUCCESS;
}

int WSDDDeployment::RemoveHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler, AXIS_PROTOCOL_TYPE protocol)
{
	return SUCCESS;	
}
