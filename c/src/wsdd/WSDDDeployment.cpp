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
 * @author Sanjaya Singharage
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */

// WSDDDeployment.cpp: implementation of the WSDDDeployment class.
//
//////////////////////////////////////////////////////////////////////

#include "WSDDDeployment.h"

#ifdef USE_EXPAT_PARSER
#include "WSDDDocumentExpat.h"
#define WSDDDOCUMENTPARSER WSDDDocumentExpat
#elif USE_XERCES_PARSER
#include "WSDDDocumentXerces.h"
#define WSDDDOCUMENTPARSER WSDDDocumentXerces
#else
#include "WSDDDocumentTXPP.h"
#define WSDDDOCUMENTPARSER WSDDDocumentTXPP
#endif

#include <axis/server/GDefine.h>
#include <axis/server/AxisConfig.h>
#include <axis/server/AxisTrace.h>

extern AxisTrace* g_pAT;

WSDDDeployment::WSDDDeployment()
{
	m_DeployedServices = NULL;
	m_sAux = "";
	m_pTransportHandlers = NULL;
	m_GlobalResponseHandlers = NULL;
	m_GlobalRequestHandlers = NULL;
	m_DeplType = DT_DEPLOYMENT;
	m_pLibNameIdMap = new map<AxisString, int>;
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
			delete ((*iter2).second);
		}
	}
}

const WSDDHandlerList* WSDDDeployment::GetGlobalRequestFlowHandlers()
{
	return m_GlobalRequestHandlers;
}

const WSDDHandlerList* WSDDDeployment::GetGlobalResponseFlowHandlers()
{
	return m_GlobalResponseHandlers;
}

int WSDDDeployment::UpdateWSDD(const AxisChar* sWSDD)
{
	WSDDDocument* doc = new WSDDDOCUMENTPARSER(m_pLibNameIdMap);
	if (AXIS_SUCCESS != doc->UpdateDeployment(sWSDD, this))
	{
		delete doc;
		return AXIS_FAIL;
	}
	delete doc;
	SaveWSDD();
	return AXIS_SUCCESS;		
}

int WSDDDeployment::LoadWSDD(const AxisChar* sWSDD)
{
	m_sWSDDPath = string(sWSDD);
	WSDDDocument* doc = new WSDDDOCUMENTPARSER(m_pLibNameIdMap);
	if (AXIS_SUCCESS != doc->GetDeployment(sWSDD, this))
	{
        	printf("wsdd loading failed\n");
		delete doc;
		return AXIS_FAIL;
	}
#ifdef _DEBUG
    printf("wsdd loading successful\n");
#endif
	delete doc;
	return AXIS_SUCCESS;
}

int WSDDDeployment::SaveWSDD()
{
	FILE* file;
	int Status = AXIS_FAIL;
	/* TODO we have to rename the existing server.wsdd to server.wsdd.old
	 * and if anything went wrong we have to rename it back to server.wsdd
	 */
	file = fopen(m_sWSDDPath.c_str(), "w");
	if(!file) return AXIS_FAIL;
	do
	{
		if (fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n", file) < 0) break;
		if (fputs("<deployment xmlns=\"http://xml.apache.org/axis/wsdd/\" xmlns:C=\"http://xml.apache.org/axis/wsdd/providers/C\" xmlns:CPP=\"http://xml.apache.org/axis/wsdd/providers/CPP\">\n", file) < 0) break;
		if (fputs("\t<globalConfiguration>\n", file) < 0) break;
		WSDDHandlerList::iterator iter;
		if(m_GlobalRequestHandlers)
		{
			if (fputs("\t\t<requestFlow>\n", file) < 0) break;
			for(iter=m_GlobalRequestHandlers->begin(); iter!=m_GlobalRequestHandlers->end(); iter++)
			{
				(*iter)->UpdateWSDD(file, 3);
			}
			if (fputs("\t\t</requestFlow>\n", file) < 0) break;
		}

		if(m_GlobalResponseHandlers)
		{
			if (fputs("\t\t<responseFlow>\n", file) < 0) break;
			for(iter=m_GlobalResponseHandlers->begin(); iter!=m_GlobalResponseHandlers->end(); iter++)
			{
				(*iter)->UpdateWSDD(file, 3);
			}
			if (fputs("\t\t</responseFlow>\n", file) < 0) break;
		}

		if (fputs("\t</globalConfiguration>\n", file) < 0) break;

		if(m_pTransportHandlers)
		{
			m_pTransportHandlers->UpdateWSDD(file, 3);
		}

		WSDDServiceMap::iterator iter2;
		if(m_DeployedServices)
		{
			for(iter2=m_DeployedServices->begin(); iter2!=m_DeployedServices->end(); iter2++)
			{
				((*iter2).second)->UpdateWSDD(file, 1);
			}
		}
		
		if (fputs("</deployment>", file) < 0) break;
	} while(0);
	fflush(file);
	fclose(file);
	if (AXIS_SUCCESS != Status)
	{
		/*TODO use the previous server.wsdd file itself. Undo renaming*/
	}
	return AXIS_SUCCESS;
}


const WSDDService* WSDDDeployment::GetService(const AxisChar* sServiceName)
{
	WSDDServiceMap::iterator iter;
	if (!m_DeployedServices) return NULL;
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

const WSDDServiceMap* WSDDDeployment::GetWSDDServiceMap() const
{
	return m_DeployedServices;
}

const AxisChar* WSDDDeployment::GetLibName(int nLibId)
{
	for (map<AxisString, int>::iterator it = m_pLibNameIdMap->begin(); it != m_pLibNameIdMap->end(); it++)
	{
		if ((*it).second == nLibId)
		{
			return (*it).first.c_str();
		}
	}
	return NULL;
}

int WSDDDeployment::AddService(WSDDService* pService)
{
	if (!m_DeployedServices) m_DeployedServices = new WSDDServiceMap;
	if (m_DeployedServices->find(pService->GetServiceName()) != m_DeployedServices->end())
	{
		AXISTRACE1("The service already exists and the attempt to re-deploy is ignored", WARN);
	}
	else
	{
		(*m_DeployedServices)[pService->GetServiceName()] = pService;
	}
	return AXIS_SUCCESS;
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
	return AXIS_SUCCESS;
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
	if (m_DeployedServices && (m_DeployedServices->find(pService->GetServiceName()) != m_DeployedServices->end()))
	{
		WSDDService* pTheService = (*m_DeployedServices)[pService->GetServiceName()];
		m_pLibNameIdMap->erase(pTheService->GetLibName());
		m_DeployedServices->erase(pService->GetServiceName());
		delete pTheService;	
		delete pService;
		return AXIS_SUCCESS;
	}
	return AXIS_NO_SUCH_SERVICE;
}

int WSDDDeployment::RemoveHandler(bool bGlobal, bool bRequestFlow, WSDDHandler* pHandler, AXIS_PROTOCOL_TYPE protocol)
{
	m_pLibNameIdMap->erase(pHandler->GetLibName());
	if (bGlobal)
	{
		WSDDHandlerList* pTempList = bRequestFlow ? m_GlobalRequestHandlers : m_GlobalResponseHandlers;
		if(pTempList)
		{
			for (WSDDHandlerList::iterator itr = pTempList->begin();
				 itr != pTempList->end(); itr++)
			{
				if (strcmp((*itr)->GetLibName(), pHandler->GetLibName()) == 0)
				{
					pTempList->remove(*itr);
					delete (*itr);
					delete pHandler;
					return AXIS_SUCCESS;
				}
			}
		}
	}
	else //transport
	{
		if (!m_pTransportHandlers) return AXIS_NO_SUCH_HANDLER;
		return m_pTransportHandlers->RemoveHandler(bRequestFlow, protocol, pHandler);
	}
	return AXIS_NO_SUCH_HANDLER;	
}

DEPLOYMENTTYPE WSDDDeployment::GetDeploymentType() const
{
	return m_DeplType;
}

void WSDDDeployment::SetDeploymentType(DEPLOYMENTTYPE nType)
{
	m_DeplType = nType;
}


