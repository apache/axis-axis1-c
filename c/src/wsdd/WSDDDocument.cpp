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

#include <axis/wsdd/WSDDDocument.h>
#include <axis/wsdd/WSDDKeywords.h>
#include <string>
#include <axis/common/AxisTrace.h>

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

int WSDDDocument::GetDeployment(const AxisChar* sWSDD, WSDDDeployment* pDeployment)
{
	m_pDeployment = pDeployment; //this enables the access to Deployment object while parsing
	if (SUCCESS != ParseDocument(sWSDD)) return FAIL;
	m_pDeployment->SetLibIdMap(m_pLibNameIdMap);
	return SUCCESS;
}

int WSDDDocument::ParseDocument(const AxisChar* sWSDD)
{
//	AXISTRACE1("inside ParseDocument\n");
	try
	{
		SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
		parser->setContentHandler(this);
		parser->setErrorHandler(this);     
		//AXISTRACE1("BEFORE parser->parse(sWSDD);");
		parser->parse(sWSDD);   
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
	AxisXMLString sLname = __XTRC(localname);
	const AxisXMLCh* lname = sLname.c_str();
	if (!XMLString::equals(lname, kw_param)) //just neglect endElement of parameter
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
				if (XMLString::equals(lname, kw_srv))
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

            default:;
			}
		}
		else // inside a requestFlow or responseFlow elements
		{
			if(XMLString::equals(lname, kw_hdl))
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
			else if(XMLString::equals(lname, kw_rqf))
			{  
				m_lev1 = WSDD_UNKNOWN;
			}
			else if(XMLString::equals(lname, kw_rsf))
			{  
				m_lev1 = WSDD_UNKNOWN;
			}						
		}
	}
}

void WSDDDocument::ProcessAttributes(WSDDLevels ElementType, const Attributes &attrs)
{
	AxisXMLString sLocal;
	AxisXMLString sValue;
	const AxisXMLCh* local;
	const AxisXMLCh* value;
	for (int i = 0; i < attrs.getLength(); i++) 
	{
		sLocal = __XTRC(attrs.getLocalName(i));
		sValue = __XTRC(attrs.getValue(i));
		local = sLocal.c_str();
		value = sValue.c_str();
		switch(ElementType)
		{
		case WSDD_SERVICE: //add this attribute to current service object
			if (XMLString::equals(local, kw_name))
			{
				m_pService->SetServiceName(value);
			}
			else if (XMLString::equals(local, kw_prv))
			{
				m_pService->SetProvider(value);
			}
			else if (XMLString::equals(local, kw_desc))
			{
				m_pService->SetDescription(value);
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_HANDLER: //add this attribute to current handler object
			if (XMLString::equals(local, kw_name))
			{
				//usefull ? ignore for now .. //TODO
			}
			else if (XMLString::equals(local, kw_type))
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
			else if (XMLString::equals(local, kw_desc))
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
			if (XMLString::equals(local, kw_name))
			{
				//usefull ? ignore for now .. //TODO
			}
			else
			{
				//unknown attribute
			}
			break;
		case WSDD_TRANSPORT:
			if (XMLString::equals(local, kw_name))
			{
				//get tranport type
				if (XMLString::equals(value, kw_http))
					m_CurTrType = APTHTTP;
				else if (XMLString::equals(value, kw_smtp))
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
	}
}

void WSDDDocument::GetParameters(WSDDLevels ElementType, const Attributes &attrs)
{
	AxisXMLString sName, sValue, sType;
	const AxisXMLCh *name, *value, *type;
	//bool locked;
	AxisXMLString Localname, Value;
	for (int i = 0; i < attrs.getLength(); i++) 
	{
		Localname = __XTRC(attrs.getLocalName(i));
		Value = __XTRC(attrs.getValue(i));
		if (XMLString::equals(Localname.c_str(), kw_name))
		{
			sName = Value.c_str();
		}
		else if (XMLString::equals(Localname.c_str(), kw_value))
		{
			sValue = Value.c_str();
		}
		else if (XMLString::equals(Localname.c_str(), kw_type))
		{
			sType = Value.c_str();
		}
	}
	
	name = sName.c_str();
	value = sValue.c_str();
	type = sType.c_str();

	switch(ElementType)
	{
	case WSDD_GLOBCONF: //parameters just inside globalConfiguration
		//TODO
		break;
	case WSDD_SERVICE:
		if (XMLString::equals(name, kw_am))
		{
			AddAllowedMethodsToService(value);
		}
		else if(XMLString::equals(name, kw_cn))
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
		else if (XMLString::equals(name, kw_scope))
		{
			m_pService->SetScope(value);
		}
		else if (XMLString::equals(name, kw_ar))
		{
			AddAllowedRolesToService(value);
		}
		else
		{
			m_pService->AddParameter(name, value);
		}
		break;
	case WSDD_HANDLER:
		if (XMLString::equals(name, kw_scope))
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

void WSDDDocument::AddAllowedRolesToService(const AxisXMLCh* value)
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

void WSDDDocument::AddAllowedMethodsToService(const AxisXMLCh* value)
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

void WSDDDocument::startElement(const XMLCh *const uri,	const XMLCh *const localname, const XMLCh *const qname,	const Attributes &attrs)
{
	AxisXMLString sLname = __XTRC(localname);
	const AxisXMLCh* lname = sLname.c_str();

	if (m_lev1 == WSDD_UNKNOWN) //not inside a requestFlow or responseFlow elements
	{
		switch(m_lev0)
		{
		case WSDD_UNKNOWN:
			if((XMLString::equals(lname, kw_depl)) || (XMLString::equals(lname, kw_undepl)))
			{  
				m_lev0 = WSDD_DEPLOYMENT;
				//nothing to get
			}
			break;
		case WSDD_DEPLOYMENT:
			if(XMLString::equals(lname, kw_glconf))
			{  
				m_lev0 = WSDD_GLOBCONF;
				//nothing to get
			}
			else if(XMLString::equals(lname, kw_srv))
			{  
				m_lev0 = WSDD_SERVICE;
				m_pService = new WSDDService();
				//get service name and proider if any
				ProcessAttributes(WSDD_SERVICE, attrs);
			}
			else if(XMLString::equals(lname, kw_hdl))
			{  
				m_lev0 = WSDD_HANDLER;
				m_pHandler = new WSDDHandler();
				ProcessAttributes(WSDD_HANDLER, attrs);
				//get handler name and type if any
			}
			else if(XMLString::equals(lname, kw_tr))
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
			if(XMLString::equals(lname, kw_param))
			{  
				GetParameters(WSDD_GLOBCONF, attrs);
			}
			else if(XMLString::equals(lname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(XMLString::equals(lname, kw_rsf))
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
			if(XMLString::equals(lname, kw_param))
			{  
				GetParameters(WSDD_SERVICE, attrs);
			}
			else if(XMLString::equals(lname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(XMLString::equals(lname, kw_rsf))
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
			if(XMLString::equals(lname, kw_param))
			{  
				GetParameters(WSDD_HANDLER, attrs);
			}

		break;
		case WSDD_TRANSPORT:
			if(XMLString::equals(lname, kw_rqf))
			{  
				m_lev1 = WSDD_REQFLOW;
				ProcessAttributes(WSDD_REQFLOW, attrs);
			}
			else if(XMLString::equals(lname, kw_rsf))
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
		if(XMLString::equals(lname, kw_param))
		{  
			GetParameters(m_lev2, attrs); //must be parameters of a handler or a chain
		}

		else if(XMLString::equals(lname, kw_hdl))
		{  
			m_lev2 = WSDD_HANDLER;
			m_pHandler = new WSDDHandler();
			ProcessAttributes(WSDD_HANDLER, attrs);
			//get handler name and type if any
		}
		else if(XMLString::equals(lname, kw_chain))
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
	m_NsStack[__XTRC(prefix)] = __XTRC(uri); //I think the same prifix cannot repeat ???
}

void WSDDDocument::endPrefixMapping(const XMLCh* const prefix)
{
//	string sPrifix = prefix;
	m_NsStack.erase(__XTRC(prefix)); //I think the same prifix cannot repeat ???
}

void  WSDDDocument::characters (const XMLCh *const chars, const unsigned int length)
{
	//cout<<"==="<<XMLString::transcode(chars)<<"==="<<endl;
}

const AxisChar* WSDDDocument::__XTRC(const XMLCh *pChar)
{
	if (true == (XMLString::transcode(pChar, m_Buffer, TRANSCODE_BUFFER_SIZE-1)))
		return m_Buffer;
	else 
		return ""; 
}
