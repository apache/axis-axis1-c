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
 * @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */

#include "WSDDDocumentExpat.h"
#include "WSDDKeywords.h"
#include <axis/server/AxisTrace.h>

#define NAMESPACESEPARATOR 0x03 /*Heart*/
#define FILEBUFFSIZE 1024

extern AxisTrace* g_pAT;

WSDDDocumentExpat::WSDDDocumentExpat(map<AxisString, int>* pLibNameIdMap)
{
	m_lev0 = WSDD_UNKNOWN;
	m_lev1 = WSDD_UNKNOWN;
	m_lev2 = WSDD_UNKNOWN;
	m_CurTrType = APTHTTP;//default is HTTP
	m_nLibId = 0;
	m_pLibNameIdMap = pLibNameIdMap;
	/* Get the maximum Lib Id from the entries in the map if available */
	for (map<AxisString, int>::iterator itr = m_pLibNameIdMap->begin(); 
		 itr != m_pLibNameIdMap->end(); itr++)
	{
		if (m_nLibId < (*itr).second) m_nLibId = (*itr).second;
	}
	m_bFatalError = false;
	m_bError = false;
}

WSDDDocumentExpat::~WSDDDocumentExpat()
{

}

int WSDDDocumentExpat::GetDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment)
{
	m_pDeployment = pDeployment; //this enables the access to Deployment object while parsing
	if (AXIS_SUCCESS != ParseDocument(sWSDD))
	{
		AXISTRACE1("Deployment descripter loading failed", CRITICAL);
		return AXIS_FAIL;
	}
	return AXIS_SUCCESS;
}

int WSDDDocumentExpat::ParseDocument(const AxisChar* sWSDD)
{
	XML_Ch Buff[FILEBUFFSIZE];
	XML_Parser Parser = XML_ParserCreateNS(NULL, NAMESPACESEPARATOR);
	XML_SetUserData(Parser, this);
	XML_SetNamespaceDeclHandler(Parser, s_startPrefixMapping, s_endPrefixMapping);
	XML_SetElementHandler(Parser, s_startElement, s_endElement);
	XML_SetCharacterDataHandler(Parser, s_characters);
	FILE *file = fopen(sWSDD, "r");
	if (NULL == file) 
	{ 
		XML_ParserFree(Parser); 
		return AXIS_FAIL;
	}
	while (true) 
	{
		int done;
		int len;
		len = fread(Buff, 1, FILEBUFFSIZE, file);
		if (ferror(file)) 
		{
			fclose(file);
			XML_ParserFree(Parser); 
			return AXIS_FAIL;
		}
		done = feof(file);
		if (XML_Parse(Parser, Buff, len, done) == XML_STATUS_ERROR) 
		{
			fclose(file);
			XML_ParserFree(Parser); 
			return AXIS_FAIL;
		}

		if (done)
			break;
	}
	fclose(file);
	XML_ParserFree(Parser); 
	return AXIS_SUCCESS;
}

int WSDDDocumentExpat::UpdateDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment)
{
	m_pDeployment = pDeployment; //this enables the access to Deployment object while parsing
	XML_Parser Parser = XML_ParserCreateNS(NULL, NAMESPACESEPARATOR);
	XML_SetUserData(Parser, this);
	XML_SetNamespaceDeclHandler(Parser, s_startPrefixMapping, s_endPrefixMapping);
	XML_SetElementHandler(Parser, s_startElement, s_endElement);
	XML_SetCharacterDataHandler(Parser, s_characters);
	if (XML_Parse(Parser, sWSDD, strlen(sWSDD), true) == XML_STATUS_ERROR) 
	{
		XML_ParserFree(Parser); 
		AXISTRACE1("Update of wsdd failed", CRITICAL);
		return AXIS_FAIL;
	}
	XML_ParserFree(Parser);
	return AXIS_SUCCESS;
}

void  WSDDDocumentExpat::endElement (const XML_Ch *qname)
{
	QName qn;
	qn.SplitQNameString(qname,NAMESPACESEPARATOR);
	if (0 != strcmp(qn.localname, kw_param)) //just neglect endElement of parameter
	{
		if (m_lev1 == WSDD_UNKNOWN) //not inside a requestFlow or responseFlow elements
		{
			switch(m_lev0)
			{
			case WSDD_DEPLOYMENT:
				m_lev0 = WSDD_UNKNOWN;
				break;
			case WSDD_GLOBCONF:
				m_lev0 = WSDD_DEPLOYMENT;
				break;
			case WSDD_SERVICE:
				if (0 == strcmp(qn.localname, kw_srv))
				{
					//add service object to Deployment object
					if (DT_DEPLOYMENT == m_pDeployment->GetDeploymentType()) /* deployment */
					{
						m_pDeployment->AddService(m_pService);
					}
					else
					{
						m_pDeployment->RemoveService(m_pService);
					}
					m_pService = NULL;
					m_lev0 = WSDD_DEPLOYMENT;
				}
				else
				{

				}
				break;
			case WSDD_HANDLER:
				//just ignore the handlers defined outside ??? //TODO
				delete m_pHandler;
				m_pHandler = NULL;
				m_lev0 = WSDD_DEPLOYMENT;
				break;
			case WSDD_TRANSPORT:
				m_CurTrType = APTHTTP;//default is HTTP
				m_lev0 = WSDD_DEPLOYMENT;
				break;
			break;

            default:;
			}
		}
		else // inside a requestFlow or responseFlow elements
		{
			if(0 == strcmp(qn.localname, kw_hdl))
			{
				m_lev2 = WSDD_UNKNOWN;
				//add handler in m_pHandler to the corresponding container.
				switch (m_lev0)
				{
					case WSDD_GLOBCONF:
						{
							if (DT_DEPLOYMENT == m_pDeployment->GetDeploymentType()) /* deployment */
							{
								m_pDeployment->AddHandler(true,(m_lev1 == WSDD_REQFLOW) , m_pHandler);
							}
							else
							{
								m_pDeployment->RemoveHandler(true,(m_lev1 == WSDD_REQFLOW) , m_pHandler);
							}
							m_pHandler = NULL;
						}
						break;
					case WSDD_TRANSPORT:
						{
							if (DT_DEPLOYMENT == m_pDeployment->GetDeploymentType()) /* deployment */
							{
								m_pDeployment->AddHandler(false,(m_lev1 == WSDD_REQFLOW) , m_pHandler, m_CurTrType);
							}
							else
							{
								m_pDeployment->RemoveHandler(false,(m_lev1 == WSDD_REQFLOW) , m_pHandler, m_CurTrType);
							}
							m_pHandler = NULL;
						}
						break;
					case WSDD_SERVICE:
						{
							if (DT_DEPLOYMENT == m_pDeployment->GetDeploymentType()) /* deployment */
							{
								m_pService->AddHandler((m_lev1 == WSDD_REQFLOW) , m_pHandler);
							}
							else
							{
								m_pService->RemoveHandler((m_lev1 == WSDD_REQFLOW) , m_pHandler);
							}
							m_pHandler = NULL;
						}
						break;
					default: ; //this cannot happen ?? 
				}
			}
			else if(0 == strcmp(qn.localname, kw_rqf))
			{  
				m_lev1 = WSDD_UNKNOWN;
			}
			else if(0 == strcmp(qn.localname, kw_rsf))
			{  
				m_lev1 = WSDD_UNKNOWN;
			}						
		}
	}
	qn.MergeQNameString(NAMESPACESEPARATOR);
}

void WSDDDocumentExpat::ProcessAttributes(WSDDLevels ElementType, const XML_Ch **attrs)
{
	QName qn;
	const XML_Ch* value;
	for (int i = 0; attrs[i]; i += 2) 
	{
		qn.SplitQNameString(attrs[i],NAMESPACESEPARATOR);
		value = attrs[i+1];
		switch(ElementType)
		{
		case WSDD_SERVICE: //add this attribute to current service object
			if (0 == strcmp(qn.localname, kw_name))
			{
				m_pService->SetName(value);
			}
			else if (0 == strcmp(qn.localname, kw_prv))
			{
				m_pService->SetProvider(value);
			}
			else if (0 == strcmp(qn.localname, kw_desc))
			{
				m_pService->SetDescription(value);
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_HANDLER: //add this attribute to current handler object
			if (0 == strcmp(qn.localname, kw_name))
			{
				m_pHandler->SetName(value);
			}
			else if (0 == strcmp(qn.localname, kw_type))
			{
				//we get the libname for the hanlder here ???
				m_pHandler->SetLibName(value);
				if (m_pLibNameIdMap->find(value) != m_pLibNameIdMap->end()) //libray name already in the map
				{
					m_pHandler->SetLibId((*m_pLibNameIdMap)[value]);
				}
				else
				{
					(*m_pLibNameIdMap)[value] = ++m_nLibId;
					m_pHandler->SetLibId((*m_pLibNameIdMap)[value]);
				}
			}
			else if (0 == strcmp(qn.localname, kw_desc))
			{
				m_pHandler->SetDescription(value);
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_REQFLOW:
		case WSDD_RESFLOW:
			if (0 == strcmp(qn.localname, kw_name))
			{
				//usefull ? ignore for now .. //TODO
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_TRANSPORT:
			if (0 == strcmp(qn.localname, kw_name))
			{
				//get tranport type
				if (0 == strcmp(value, kw_http))
					m_CurTrType = APTHTTP;
				else if (0 == strcmp(value, kw_smtp))
					m_CurTrType = APTSMTP;
				else
				{
					//unhandled transport type
				}
			}
			else
			{
				//unknown attribute
			}
			break;
        default:;
		}
		qn.MergeQNameString(NAMESPACESEPARATOR);
	}
}

void WSDDDocumentExpat::GetParameters(WSDDLevels ElementType, const XML_Ch **attrs)
{
	QName qn;
	const XML_Ch* value;
	const XML_Ch* type;
	const XML_Ch* name;
	for (int i = 0; attrs[i]; i += 2) 
	{
		qn.SplitQNameString(attrs[i],NAMESPACESEPARATOR);
		value = attrs[i+1];
		if (0 == strcmp(qn.localname, kw_name))
		{
			name = value;
		}
		else if (0 == strcmp(qn.localname, kw_value))
		{
			value = value;
		}
		else if (0 == strcmp(qn.localname, kw_type))
		{
			type = value;
		}
		qn.MergeQNameString(NAMESPACESEPARATOR);
	}

	switch(ElementType)
	{
	case WSDD_GLOBCONF: //parameters just inside globalConfiguration
		//TODO
		break;
	case WSDD_SERVICE:
		if (0 == strcmp(name, kw_am))
		{
			AddAllowedMethodsToService(value);
		}
		else if(0 == strcmp(name, kw_cn))
		{
			m_pService->SetLibName(value);
			if (m_pLibNameIdMap->find(value) != m_pLibNameIdMap->end()) //libray name already in the map
			{
				m_pService->SetLibId((*m_pLibNameIdMap)[value]);
			}
			else
			{
				(*m_pLibNameIdMap)[value] = ++m_nLibId;
				m_pService->SetLibId((*m_pLibNameIdMap)[value]);
			}
		}
		else if (0 == strcmp(name, kw_scope))
		{
			m_pService->SetScope(value);
		}
		else if (0 == strcmp(name, kw_ar))
		{
			AddAllowedRolesToService(value);
		}
		else
		{
			m_pService->AddParameter(name, value);
		}
		break;
	case WSDD_HANDLER:
		if (0 == strcmp(name, kw_scope))
		{
			m_pHandler->SetScope(value);
		}
		else
		{
			m_pHandler->AddParameter(name, value);
		}
		break;

     default:;
	}
}

void WSDDDocumentExpat::AddAllowedRolesToService(const AxisXMLCh* value)
{
	AxisString sValue = value;
	int prepos = 0, pos = 0;
	if (sValue.find('*') == AxisString::npos)
	{
		do 
		{
			pos = sValue.find(ROLENAME_SEPARATOR, prepos);
			if (AxisString::npos == pos) break;
			m_pService->AddAllowedRole(sValue.substr(prepos, pos-prepos).c_str());
			prepos = pos + 1;
		} while (true);
	}
}

void WSDDDocumentExpat::AddAllowedMethodsToService(const AxisXMLCh* value)
{
	AxisString sValue = value;
	int prepos = 0, pos = 0;
	if (sValue.find('*') == AxisString::npos)
	{
		do 
		{
			pos = sValue.find(METHODNAME_SEPARATOR, prepos);
			if (AxisString::npos == pos) break;
			m_pService->AddAllowedMethod(sValue.substr(prepos, pos-prepos).c_str());
			prepos = pos + 1;
		} while (true);
	}
}


void WSDDDocumentExpat::startElement(const XML_Ch *qname,const XML_Ch **attrs)
{
	QName qn;
	qn.SplitQNameString(qname,NAMESPACESEPARATOR);
	if (m_lev1 == WSDD_UNKNOWN) //not inside a requestFlow or responseFlow elements
	{
		switch(m_lev0)
		{
		case WSDD_UNKNOWN:
			if(0 == strcmp(qn.localname, kw_depl))
			{  
				m_lev0 = WSDD_DEPLOYMENT;
				m_pDeployment->SetDeploymentType(DT_DEPLOYMENT);
			}
			else if(0 == strcmp(qn.localname, kw_undepl))
			{  
				m_lev0 = WSDD_DEPLOYMENT;
				m_pDeployment->SetDeploymentType(DT_UNDEPLOYMENT);
			}
			break;
		case WSDD_DEPLOYMENT:
			if(0 == strcmp(qn.localname, kw_glconf))
			{  
				m_lev0 = WSDD_GLOBCONF;
				//nothing to get
			}
			else if(0 == strcmp(qn.localname, kw_srv))
			{  
				m_lev0 = WSDD_SERVICE;
				m_pService = new WSDDService();
				//get service name and proider if any
				ProcessAttributes(WSDD_SERVICE, attrs);
			}
			else if(0 == strcmp(qn.localname, kw_hdl))
			{  
				m_lev0 = WSDD_HANDLER;
				m_pHandler = new WSDDHandler();
				ProcessAttributes(WSDD_HANDLER, attrs);
				//get handler name and type if any
			}
			else if(0 == strcmp(qn.localname, kw_tr))
			{  
				m_lev0 = WSDD_TRANSPORT;
				ProcessAttributes(WSDD_TRANSPORT, attrs);
			}
			else
			{
				//error : unknown element type in wsdd file
			}
			break;
		case WSDD_GLOBCONF:
			if(0 == strcmp(qn.localname, kw_param))
			{  
				GetParameters(WSDD_GLOBCONF, attrs);
			}
			else if(0 == strcmp(qn.localname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(0 == strcmp(qn.localname, kw_rsf))
			{  
				m_lev1 = WSDD_RESFLOW;
				ProcessAttributes(WSDD_RESFLOW, attrs);
			}
			else
			{
				//yet unhandled element type
			}
		break; 
		case WSDD_SERVICE:
			if(0 == strcmp(qn.localname, kw_param))
			{  
				GetParameters(WSDD_SERVICE, attrs);
			}
			else if(0 == strcmp(qn.localname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(0 == strcmp(qn.localname, kw_rsf))
			{  
				m_lev1 = WSDD_RESFLOW;
				ProcessAttributes(WSDD_RESFLOW, attrs);
			}
			else
			{
				//yet unhandled element type like namespace
			}
		break;
		case WSDD_HANDLER:
			if(0 == strcmp(qn.localname, kw_param))
			{  
				GetParameters(WSDD_HANDLER, attrs);
			}

		break;
		case WSDD_TRANSPORT:
			if(0 == strcmp(qn.localname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(0 == strcmp(qn.localname, kw_rsf))
			{  
				m_lev1 = WSDD_RESFLOW;
				ProcessAttributes(WSDD_RESFLOW, attrs);
			}
		break;
        default:;
		}
	}
	else // inside a requestFlow or responseFlow elements
	{
		if(0 == strcmp(qn.localname, kw_param))
		{  
			GetParameters(m_lev2, attrs); //must be parameters of a handler or a chain
		}

		else if(0 == strcmp(qn.localname, kw_hdl))
		{  
			m_lev2 = WSDD_HANDLER;
			m_pHandler = new WSDDHandler();
			ProcessAttributes(WSDD_HANDLER, attrs);
			//get handler name and type if any
		}
		else if(0 == strcmp(qn.localname, kw_chain))
		{

		}
		else
		{
			//error : unknown element type in wsdd file
		}
	}
	qn.MergeQNameString(NAMESPACESEPARATOR);
}

void WSDDDocumentExpat::startPrefixMapping(const XML_Ch *prefix, const XML_Ch *uri)
{
	if (prefix) m_NsStack[prefix] = uri; //I think the same prifix cannot repeat ???
}

void WSDDDocumentExpat::endPrefixMapping(const XML_Ch *prefix)
{
	if (prefix) m_NsStack.erase(prefix); //I think the same prifix cannot repeat ???
}

void  WSDDDocumentExpat::characters (const XML_Ch* chars,int length)
{
	//cout<<"==="<<XMLString::transcode(chars)<<"==="<<endl;
}


