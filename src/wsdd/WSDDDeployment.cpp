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
 * @author Roshan Weerasuriya (roshan@jkcs.slt.lk, roshan@opensource.lk)
 *
 */

// WSDDDeployment.cpp: implementation of the WSDDDeployment class.
//
//////////////////////////////////////////////////////////////////////

#include "WSDDDeployment.h"
#include "WSDDDocument.h"
#include "../common/GDefine.h"
#include "../common/AxisConfig.h"

extern unsigned char chEBuf[1024];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WSDDDeployment::WSDDDeployment()
{
	m_DeployedServices = NULL;
	m_sAux = "";
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
			delete ((*iter2).second);
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

int WSDDDeployment::LoadWSDD(const AxisChar* sWSDD)
{
	WSDDDocument doc;
	if (SUCCESS != doc.GetDeployment(sWSDD, this))
	{
		return FAIL;
	}
	return SUCCESS;
}

int WSDDDeployment::UpdateWSDD(const AxisChar* sWSDDNew, string sServiceName, string sDllPath, Axis_ArrayTag inAllowedMethodsArray)
{
	printf("entered again to UpdateWSDD \n");
	printf("sServiceName = %s \n", sServiceName.c_str());
	printf("sDllPath = %s \n", sDllPath.c_str());	

	const AxisChar* pAchServiceName;
	const AxisChar* pAchLibName;
	list<AxisString> lstAllowedMethods;

	WSDDServiceMap::iterator itCurrService;

	FILE* file;
	int iStatus = SUCCESS;

	do {
		file = fopen("C:/Axis/conf/server.wsdd", "w");
		if(file) {
			printf("opened the file successfully\n");
		} else {
			printf("FAILED: couldn't open the file successfully\n\n");
			iStatus = FAIL;
			break;
		}

		int iWriteResult = 0;
		
		iWriteResult = fputs("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n", file);
		if (iWriteResult<0) {
			printf("writing to the file is UNSUCCESSFULL\n");
			iStatus = FAIL;
			break;
		} else {
			printf("writing to the file is SUCCESSFULL\n");
		}

		iWriteResult = fputs("<deployment xmlns=\"http://xml.apache.org/axis/wsdd/\" xmlns:java=\"http://xml.apache.org/axis/wsdd/providers/java\">\n", file);
		if (iWriteResult<0) {
			printf("writing to the file is UNSUCCESSFULL\n");
			iStatus = FAIL;
			break;
		} else {
			printf("writing to the file is SUCCESSFULL\n");
		}

		if(m_DeployedServices)
		{
			for(itCurrService=m_DeployedServices->begin()
					;itCurrService!=m_DeployedServices->end();itCurrService++)
			{
				const WSDDService* pWSDDService = (*itCurrService).second;
				AxisChar achTmpChar[1000] = {0};
				pAchServiceName = pWSDDService->GetServiceName();
				pAchLibName = pWSDDService->GetLibName();
				lstAllowedMethods = pWSDDService->getAllowedMethods();				
								
				printf("pAchServiceName = %s\n", pAchServiceName);
				printf("pAchLibName = %s\n", pAchLibName);
				
				strcat(achTmpChar, " <service name=\"");
				strcat(achTmpChar, pAchServiceName);
				strcat(achTmpChar, "\" provider=\"java:RPC\">\n");
				strcat(achTmpChar, "  <parameter name=\"className\" value=\"");
				strcat(achTmpChar, pAchLibName);
				strcat(achTmpChar, "\"/>\n");
				strcat(achTmpChar, "  <parameter name=\"allowedMethods\" value=\"");	
				
				list<AxisString>::iterator iteAllowedMethods = lstAllowedMethods.begin();
				while (iteAllowedMethods != lstAllowedMethods.end()) {	
					
					printf("sAllowedMethod = %s\n", (*iteAllowedMethods).c_str());					
					const AxisChar* tmpChar = (*iteAllowedMethods).c_str();
					strcat(achTmpChar, tmpChar);
					if(iteAllowedMethods != lstAllowedMethods.end()) {
						strcat(achTmpChar, " ");
					}
										
					iteAllowedMethods++;
				}

				strcat(achTmpChar, "\"/>\n </service>\n");

				iWriteResult = fputs(achTmpChar, file);
				if (iWriteResult<0) {
					printf("writing to the file is UNSUCCESSFULL\n");
					iStatus = FAIL;
					break;
				} else {
					printf("writing to the file is SUCCESSFULL\n");
				}				
			}
		}

		/*
		 *New web service details which is to deploy
		 */
		AxisChar achTmpChar[1000] = {0};
		strcat(achTmpChar, " <service name=\"");
		strcat(achTmpChar, sServiceName.c_str());
		strcat(achTmpChar, "\" provider=\"java:RPC\">\n");
		strcat(achTmpChar, "  <parameter name=\"className\" value=\"");
		strcat(achTmpChar, sDllPath.c_str());
		strcat(achTmpChar, "\"/>\n");
		strcat(achTmpChar, "  <parameter name=\"allowedMethods\" value=\"");

		string* sAllowedMethods = (string*)inAllowedMethodsArray.m_Array;
		for (int i=0; i<inAllowedMethodsArray.m_Size; i++ ) {
			printf("Allowed method = %s\n", (sAllowedMethods[i]).c_str());
			strcat(achTmpChar, (sAllowedMethods[i]).c_str());
			if(i != ((inAllowedMethodsArray.m_Size)-1)) {
				strcat(achTmpChar, " ");
			}
		}

		strcat(achTmpChar, "\"/>\n </service>\n");

		iWriteResult = fputs(achTmpChar, file);
		if (iWriteResult<0) {
			printf("writing to the file is UNSUCCESSFULL\n");
			iStatus = FAIL;
			break;
		} else {
			printf("writing to the file is SUCCESSFULL\n");
		}		
		
		/*
		 *--------------------------------------------
		 */

		
		iWriteResult = fputs("</deployment>", file);
		if (iWriteResult<0) {
			printf("writing to the file is UNSUCCESSFULL\n");
			iStatus = FAIL;
			break;
		} else {
			printf("writing to the file is SUCCESSFULL\n");
		}
		
		
	} while (0);

	fclose(file);

	LoadWSDD("C:/Axis/conf/server.wsdd");

	return SUCCESS;
}


const WSDDService* WSDDDeployment::GetService(const AxisChar* sServiceName)
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
	(*m_DeployedServices)[pService->GetServiceName()] = pService;
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