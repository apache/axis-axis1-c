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
 * @author Suasntha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 */

#include "WSDDDocument.h"
#include <iostream>
#include <string>
#include "../common/Debug.h"

WSDDDocument::WSDDDocument()
{
	m_lev0 = WSDD_UNKNOWN;
	m_lev1 = WSDD_UNKNOWN;
	m_lev2 = WSDD_UNKNOWN;
	m_CurTrType = APTHTTP;//default is HTTP
	m_nLibId = 0;
	m_pLibNameIdMap = new map<AxisString, int>;
}

WSDDDocument::~WSDDDocument()
{

}

int WSDDDocument::GetDeployment(const string& sWSDD, WSDDDeployment* pDeployment)
{
	m_pDeployment = pDeployment; //this enables the access to Deployment object while parsing
	if (SUCCESS != ParseDocument(sWSDD)) return FAIL;
	m_pDeployment->SetLibIdMap(m_pLibNameIdMap);
	return SUCCESS;
}

int WSDDDocument::ParseDocument(const string& sWSDD)
{
	DEBUG1("inside ParseDocument\n");
	try
	{
		SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
		parser->setContentHandler(this);
		parser->setErrorHandler(this);     
		DEBUG1("BEFORE parser->parse(sWSDD.c_str());");
		parser->parse(sWSDD.c_str());   
		delete parser;
	}
	catch (...)
	{
		return FAIL;
	}
	return SUCCESS;
}

void  WSDDDocument::endElement (const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname)
{
	if (0 != wcscmp(localname, kw_param)) //just neglect endElement of parameter
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
				if (0 == wcscmp(localname, kw_srv))
				{
					//add service object to Deployment object
					m_pDeployment->AddService(m_pService);
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
			}
		}
		else // inside a requestFlow or responseFlow elements
		{
			if(0 == wcscmp(localname, kw_hdl))
			{
				m_lev2 = WSDD_UNKNOWN;
				//add handler in m_pHandler to the corresponding container.
				switch (m_lev0)
				{
					case WSDD_GLOBCONF:
						{
							m_pDeployment->AddHandler(true,(m_lev1 == WSDD_REQFLOW) , m_pHandler);
							m_pHandler = NULL;
						}
						break;
					case WSDD_TRANSPORT:
						{
							m_pDeployment->AddHandler(false,(m_lev1 == WSDD_REQFLOW) , m_pHandler, m_CurTrType);
							m_pHandler = NULL;
						}
						break;
					case WSDD_SERVICE:
						{
							m_pService->AddHandler((m_lev1 == WSDD_REQFLOW) , m_pHandler);
							m_pHandler = NULL;
						}
						break;
					default: ; //this cannot happen ?? 
				}
			}
			else if(0 == wcscmp(localname, kw_rqf))
			{  
				m_lev1 = WSDD_UNKNOWN;
			}
			else if(0 == wcscmp(localname, kw_rsf))
			{  
				m_lev1 = WSDD_UNKNOWN;
			}						
		}
	}
}

void WSDDDocument::ProcessAttributes(WSDDLevels ElementType, const Attributes &attrs)
{
	for (int i = 0; i < attrs.getLength(); i++) 
	{
		AxisString local = attrs.getLocalName(i);
		AxisString value = attrs.getValue(i);
		switch(ElementType)
		{
		case WSDD_SERVICE: //add this attribute to current service object
			if (local == kw_name)
			{
				m_pService->SetServiceName(value);
			}
			else if (local == kw_prv)
			{
				m_pService->SetProvider(value);
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_HANDLER: //add this attribute to current handler object
			if (local == kw_name)
			{
				//usefull ? ignore for now .. //TODO
			}
			else if (local == kw_type)
			{
				//we get the libname for the hanlder here ???
				m_pHandler->SetLibName(value);
				if (m_pLibNameIdMap->find(value.c_str()) != m_pLibNameIdMap->end()) //libray name already in the map
				{
					m_pHandler->SetLibId((*m_pLibNameIdMap)[value.c_str()]);
				}
				else
				{
					(*m_pLibNameIdMap)[value.c_str()] = ++m_nLibId;
					m_pHandler->SetLibId((*m_pLibNameIdMap)[value.c_str()]);
				}
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_REQFLOW:
		case WSDD_RESFLOW:
			if (local == kw_name)
			{
				//usefull ? ignore for now .. //TODO
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_TRANSPORT:
			if (local == kw_name)
			{
				//get tranport type
				if (value == kw_http)
					m_CurTrType = APTHTTP;
				else if (value == kw_smtp)
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
		}
	}
}

void WSDDDocument::GetParameters(WSDDLevels ElementType, const Attributes &attrs)
{
	AxisString name, value, type;
	bool locked;
	AxisString Localname, Value;
	for (int i = 0; i < attrs.getLength(); i++) 
	{
		Localname = attrs.getLocalName(i);
		Value = attrs.getValue(i);
		if (Localname == kw_name)
		{
			name = Value;
		}
		else if (Localname == kw_value)
		{
			value = Value;
		}
		else if (Localname == kw_type)
		{
			type = Value;
		}
	}
	switch(ElementType)
	{
	case WSDD_GLOBCONF: //parameters just inside globalConfiguration
		//TODO
		break;
	case WSDD_SERVICE:
		if (name == kw_am)
		{
			AddAllowedMethodsToService(value);
		}
		else if(name == kw_cn)
		{
			m_pService->SetLibName(value);
			if (m_pLibNameIdMap->find(value.c_str()) != m_pLibNameIdMap->end()) //libray name already in the map
			{
				m_pService->SetLibId((*m_pLibNameIdMap)[value.c_str()]);
			}
			else
			{
				(*m_pLibNameIdMap)[value.c_str()] = ++m_nLibId;
				m_pService->SetLibId((*m_pLibNameIdMap)[value.c_str()]);
			}
		}
		else if (name == kw_scope)
		{
			m_pService->SetScope(value);
		}
		else if (name == kw_ar)
		{
			AddAllowedRolesToService(value);
		}
		else
		{
			m_pService->AddParameter(name, value);
		}
		break;
	case WSDD_HANDLER:
		if (name == kw_scope)
		{
			m_pHandler->SetScope(value);
		}
		else
		{
			m_pHandler->AddParameter(name, value);
		}
		break;
	}
}

void WSDDDocument::AddAllowedRolesToService(AxisString& value)
{
	int prepos = 0, pos = 0;
	if (value.find('*') == AxisString::npos)
	{
		do 
		{
			pos = value.find(ROLENAME_SEPARATOR, prepos);
//			cout << value.substr(prepos, pos) << endl;
			m_pService->AddAllowedRole(value.substr(prepos, pos));
			prepos = pos + 1;
		} while (AxisString::npos != pos);
	}
}

void WSDDDocument::AddAllowedMethodsToService(AxisString& value)
{
	int prepos = 0, pos = 0;
	if (value.find('*') == AxisString::npos)
	{
		do 
		{
			pos = value.find(METHODNAME_SEPARATOR, prepos);
//			cout << value.substr(prepos, pos) << endl;
			m_pService->AddAllowedMethod(value.substr(prepos, pos));
			prepos = pos + 1;
		} while (AxisString::npos != pos);
	}
}

void WSDDDocument::startElement(const XMLCh *const uri,	const XMLCh *const localname, const XMLCh *const qname,	const Attributes &attrs)
{
	if (m_lev1 == WSDD_UNKNOWN) //not inside a requestFlow or responseFlow elements
	{
		switch(m_lev0)
		{
		case WSDD_UNKNOWN:
			if(0 == wcscmp(localname, kw_depl))
			{  
				m_lev0 = WSDD_DEPLOYMENT;
				//nothing to get
			}
			break;
		case WSDD_DEPLOYMENT:
			if(0 == wcscmp(localname, kw_glconf))
			{  
				m_lev0 = WSDD_GLOBCONF;
				//nothing to get
			}
			else if(0 == wcscmp(localname, kw_srv))
			{  
				m_lev0 = WSDD_SERVICE;
				m_pService = new WSDDService();
				//get service name and proider if any
				ProcessAttributes(WSDD_SERVICE, attrs);
			}
			else if(0 == wcscmp(localname, kw_hdl))
			{  
				m_lev0 = WSDD_HANDLER;
				m_pHandler = new WSDDHandler();
				ProcessAttributes(WSDD_HANDLER, attrs);
				//get handler name and type if any
			}
			else if(0 == wcscmp(localname, kw_tr))
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
			if(0 == wcscmp(localname, kw_param))
			{  
				GetParameters(WSDD_GLOBCONF, attrs);
			}
			else if(0 == wcscmp(localname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(0 == wcscmp(localname, kw_rsf))
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
			if(0 == wcscmp(localname, kw_param))
			{  
				GetParameters(WSDD_SERVICE, attrs);
			}
			else if(0 == wcscmp(localname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(0 == wcscmp(localname, kw_rsf))
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
			if(0 == wcscmp(localname, kw_param))
			{  
				GetParameters(WSDD_HANDLER, attrs);
			}

		break;
		case WSDD_TRANSPORT:
			if(0 == wcscmp(localname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(0 == wcscmp(localname, kw_rsf))
			{  
				m_lev1 = WSDD_RESFLOW;
				ProcessAttributes(WSDD_RESFLOW, attrs);
			}
		break;
		}
	}
	else // inside a requestFlow or responseFlow elements
	{
		if(0 == wcscmp(localname, kw_param))
		{  
			GetParameters(m_lev2, attrs); //must be parameters of a handler or a chain
		}

		else if(0 == wcscmp(localname, kw_hdl))
		{  
			m_lev2 = WSDD_HANDLER;
			m_pHandler = new WSDDHandler();
			ProcessAttributes(WSDD_HANDLER, attrs);
			//get handler name and type if any
		}
		else if(0 == wcscmp(localname, kw_chain))
		{

		}
		else
		{
			//error : unknown element type in wsdd file
		}

	}
}

void WSDDDocument::startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri)
{
//	AxisString sPrifix = prefix;
	AxisString sUri = uri;
	m_NsStack[prefix] = uri; //I think the same prifix cannot repeat ???
}

void WSDDDocument::endPrefixMapping(const XMLCh* const prefix)
{
//	string sPrifix = prefix;
	m_NsStack.erase(prefix); //I think the same prifix cannot repeat ???
}

void  WSDDDocument::characters (const XMLCh *const chars, const unsigned int length)
{
	//cout<<"==="<<XMLString::transcode(chars)<<"==="<<endl;
}