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
#include <stdlib.h>
#include "XMLStreamHandler.h"
#include <string.h>
#include "../common/TypeMapping.h"
#include "URIMapping.h"
#include "Attribute.h"
#include "SoapEnvVersions.h"
#include "CharacterElement.h"

#define __TRC(X) XMLString::transcode(X)
#define __REL(X) XMLString::release(X)

XMLStreamHandler::XMLStreamHandler()
{
	m_pEnv = NULL;
	m_pHead = NULL;
	m_pBody = NULL;
	m_pFault = NULL;
	m_pMethod = NULL;
	m_it = NULL;
}

XMLStreamHandler::~XMLStreamHandler()
{
	if (m_pEnv) delete m_pEnv;
	if (m_pHead) delete m_pHead;
	if (m_pBody) delete m_pBody;
	if (m_pFault) delete m_pFault;
	if (m_pMethod) delete m_pMethod;
}
/*
 * Please do a bench test with following parameter inside soap method
 * to understand the algorithm

<e:Book xmlns:e="http://example.org/2001/06/books" >
   <title>My Life and Work</title>
   <author>
       <name>Henry Ford</name>
       <address>
          <email>mailto:henryford@hotmail.com</email>
          <web>http://www.henryford.com</web>
       </address>
   </author>
</e:Book>

*/

void XMLStreamHandler::startElement(const XMLCh *const uri,const XMLCh *const localname,const XMLCh *const qname,const Attributes &attrs)
{
	char *pcLocalName = __TRC(localname);
	if (pcLocalName)
	{
		switch (m_PL0)
		{
		case SOAP_UNKNOWN:
		if(0 == strcmp(pcLocalName,g_sObjSoapEnvVersionsStruct[m_nSoapVersion].pcharWords[SKW_ENVELOPE]))
		{
			m_PL0 = SOAP_ENVELOP;
			m_pEnv = new SoapEnvelope();
			//set all attributes of SoapEnvelope
			FillEnvelope(uri,localname,qname,attrs);
		}
		break;
		case SOAP_ENVELOP:
		if(0 == strcmp(pcLocalName,g_sObjSoapEnvVersionsStruct[m_nSoapVersion].pcharWords[SKW_BODY]))
		{
			m_PL0 = SOAP_BODY;
			m_pBody = new SoapBody();
			//set all attributes of SoapBody
			FillBody(uri,localname,qname,attrs);	
		}
		else if (0 == strcmp(pcLocalName,g_sObjSoapEnvVersionsStruct[m_nSoapVersion].pcharWords[SKW_HEADER]))
		{
			m_PL0 = SOAP_HEADER;
			m_pHead = new SoapHeader();
			//set all attributes of SoapHeader
			FillHeader(uri,localname,qname,attrs);
		}
		else if (0 == strcmp(pcLocalName,g_sObjSoapEnvVersionsStruct[m_nSoapVersion].pcharWords[SKW_FAULT]))
		{
			//m_PL0 = SOAP_FAULT;
			//m_pFault = SoapFault::getSoapFault(1);
			//set all attributes of SoapFault
			//FillFault(uri,localname,qname,attrs);
		}
		else { //Soap error
			m_Success = FAIL;
		}
		break;
		case SOAP_HEADER:
			//Soap header entry
			createHeaderBlock(uri, localname, qname, attrs);
			m_PL1= SOAP_HEADER_BLOCK;
			break;
		case SOAP_FAULT:
			//Soap fault sub element
			break;
		case SOAP_BODY:
			switch (m_PL1)
			{
			case SOAP_UNKNOWN:
				if (0 == strcmp(pcLocalName,g_sObjSoapEnvVersionsStruct[m_nSoapVersion].pcharWords[SKW_MULTIREF]))
				{
					m_sLastElement = pcLocalName;
					SetParamType(attrs); 
					m_PL1 = SOAP_PARAM;
				}
				else //now comes method name in RPC Style
				{
					m_PL1 = SOAP_METHOD;
					m_pMethod = new SoapMethod();
					FillMethod(uri,localname,qname,attrs);
				}
				break;
			case SOAP_METHOD: //now comes parameters
				//Get Param name and type
				m_Param.m_sName = pcLocalName;
				m_sLastElement = pcLocalName;
				SetParamType(attrs); 
				m_PL1 = SOAP_PARAM;
				m_nParamNestingLevel++;
				break;
			case SOAP_PARAM: //Custom types
				if (m_sLastElement != pcLocalName)
				{
					m_Params.push_back(new Param(m_Param)); //parent param
				}
				m_Param.m_sName = pcLocalName;
				m_sLastElement = pcLocalName;
				SetParamType(attrs); 
				m_nParamNestingLevel++;
				break;
			default:
				m_Success = FAIL;
			}
		break;
		default:
			m_Success = FAIL;
		}
		__REL(&pcLocalName);
	}
}

void XMLStreamHandler::endElement (const XMLCh *const uri,const XMLCh *const localname,const XMLCh *const qname)
{
	char *pcLocalName = __TRC(localname);
	if (pcLocalName) {
		switch (m_PL1)
		{
		case SOAP_UNKNOWN: 
			if(m_PL0==SOAP_HEADER) {
				m_PL0= SOAP_ENVELOP;
			}
			break;
		case SOAP_METHOD: //end of method element
			if (m_nParamNestingLevel == 0)
				m_PL1 = SOAP_UNKNOWN;
			m_nParamNestingLevel--;
			break;
		case SOAP_PARAM: //end of a parameter
			//Add parameter to list
			if (m_sLastElement == pcLocalName)
			{
				m_Params.push_back(new Param(m_Param)); //current param
			}
			m_PL1 = SOAP_METHOD; //next parameter can be Nth parameter just within the Method element.
			m_nParamNestingLevel--;
			break;
		case SOAP_HEADER_BLOCK: //enf of a HeaderBlock
			//Add HeaderBlock to Header
			m_pHead->addHeaderBlock(pHeaderBlock);

			m_PL1= SOAP_UNKNOWN;
			break;
		default:
			m_Success = FAIL;
		}
		__REL(&pcLocalName);
	}
}

void  XMLStreamHandler::characters (const XMLCh *const chars,const unsigned int length)
{
	if ((m_PL0 == SOAP_BODY) && (m_PL1 == SOAP_PARAM)) //Make this a switch statement if many cases to be handled
	{
		//Get value of the parameter
		char *value = __TRC(chars);
		if (value)
		{
			string str = value;
			m_Param.SetValue(str);
			__REL(&value);
		}
	} else if ((m_PL0 == SOAP_HEADER) && (m_PL1 == SOAP_HEADER_BLOCK)) {
		//Get the value of the header entry
		char *value = __TRC(chars);
		if(value) {
			string str= value;
			CharacterElement* pCharacterElement= new CharacterElement(str);
			pHeaderBlock->addChild(pCharacterElement);
		}
	}
}

void XMLStreamHandler::startPrefixMapping(const XMLCh* const prefix, const XMLCh* const uri)
{
	char* pc; 
	pc = __TRC(prefix);
	string sPrifix = pc;
	__REL(&pc);
	pc = __TRC(uri);
	string sUri = pc;
	__REL(&pc);
	m_NsStack[sPrifix] = sUri; //I think the same prifix cannot repeat ???
}

void XMLStreamHandler::endPrefixMapping(const XMLCh* const prefix)
{
	char* pc; 
	pc = __TRC(prefix);
	string sPrifix = pc;
	__REL(&pc);
	m_NsStack.erase(sPrifix); //I think the same prifix cannot repeat ???
}

void XMLStreamHandler::warning(const SAXParseException& exception)
{

}
void XMLStreamHandler::error(const SAXParseException& exception)
{
//  sprintf((char*)chEBuf, "Error : %s", __TRC(exception.getMessage()));
	m_Success = FAIL;
}
void XMLStreamHandler::fatalError(const SAXParseException& exception)
{
// sprintf((char*)chEBuf, "Fatal Error : %s", __TRC(exception.getMessage()));
	m_Success = FAIL;
}

int XMLStreamHandler::Success()
{
	return m_Success;
}

void XMLStreamHandler::SetParamType(const Attributes &attrs)
{
	char* pc; 
	//in case there are no attributes describing the type the default is set to XSD_UNKNOWN
	m_Param.m_Type = XSD_UNKNOWN; 
	for (int i = 0; i < attrs.getLength(); i++) 
	{
		pc = __TRC(attrs.getURI(i));
		string URI = pc;
		__REL(&pc);
		pc = __TRC(attrs.getLocalName(i));
		string local = pc;
		__REL(&pc);
		pc = __TRC(attrs.getValue(i));
		string value = pc;
		__REL(&pc);
		URITYPE urit = URIMapping::Map(URI);
		switch (urit)
		{
		case URI_XSI: //xsi:type="xsd:int"
			if (local == "type")
			{
				int colonindex = value.find(':'); 
				if (colonindex != string::npos) 
				{
					string sPrefix = value.substr(0, colonindex);
					string sType = value.substr(colonindex+1,string::npos);
					if (m_NsStack.find(sPrefix) != m_NsStack.end())
					{
						if(URIMapping::Map(m_NsStack[sPrefix]) == URI_XSD)
						{
							//check for xml data types
							m_Param.m_Type = TypeMapping::Map(sType);
						}
						else
						{
							//custom data type
							m_Param.m_Type = USER_TYPE;
							m_Param.m_Value.pBean = &m_AccessBean; //ArrayBean can be used as an AccessBean;
							m_Param.m_Value.pBean->m_TypeName = sType;
							m_Param.m_Value.pBean->m_URI = m_NsStack[sPrefix];
						}
					}
					else
					{
						//unknown prefix - something wrong with the soap
					}
				}
				else 
				{
					//unqualified type - an error in soap ????
				}
			}
			else  
			{

			}
			break;
		case URI_ENC: //enc:arrayType="xs:string[6]"
			if (local == "arrayType")
			{
				m_Param.m_Type = XSD_ARRAY;
				m_Param.m_Value.pArray = &m_ArrayBean;

				int colonindex = value.find(':'); 
				if (colonindex != string::npos) 
				{
					string sPrefix = value.substr(0, colonindex);
					int bracketindex = value.find('[');
					if (bracketindex == string::npos)
					{
						//no [] - this is an error condition
					}
					string sType = value.substr(colonindex+1,bracketindex-colonindex-1);
					string sDimensions = value.substr(bracketindex);

					if (m_NsStack.find(sPrefix) != m_NsStack.end())
					{
						if(URIMapping::Map(m_NsStack[sPrefix]) == URI_XSD)
						{
							//check for xml data types
							m_Param.m_Value.pArray->m_type = TypeMapping::Map(sType);
						}
						else
						{
							m_Param.m_Value.pArray->m_TypeName = sType;
							m_Param.m_Value.pArray->m_URI = m_NsStack[sPrefix];
							m_Param.m_Value.pArray->m_type = USER_TYPE;
							//array of custom data types
						}
						if(SUCCESS != SetArrayDimensions(sDimensions))
						{
							//couldnt get dimension of the array - error condition
						}
					}
					else
					{
						//unknown prefix - something wrong with the soap
					}
				}
				else 
				{
					//unqualified type - an error in soap ????
				}
			}
			else
			{

			}
			break;
		case URI_UNKNOWN:
			//check for accessors for multiref values
			if (local == "href")
			{
				m_Param.m_Type = ACCESSOR;
				m_Param.m_sValue = value.substr(value.find('#')+1);
			}
			else if (local == "id")
			{
				m_Param.m_sName = value;
			}

		default:; // is this an error condition ???
		}	
	}
}	

// Input is a string like "[3]" or "[2,3]" which is the dimension of the array type
// being parsed. 
int XMLStreamHandler::SetArrayDimensions(string &sDimensions)
{
	int si=0;
	int ei=0;
	do
	{
		si = sDimensions.find('[',ei);
		ei = sDimensions.find(']',si);
		m_Param.m_Value.pArray->m_size.push_back(atoi((sDimensions.substr(si+1,ei)).c_str()));
	} while (sDimensions.find('[',ei) != string::npos);
	return SUCCESS;
}

Param* XMLStreamHandler::GetParam()
{
	if (m_it == NULL)
	{
		m_it = m_Params.begin();
	}
	else 
	{
		m_it++;
	}
	if (m_it != m_Params.end())
	{
		return *m_it;
	}
	return NULL;
}

//resets XMLStreamHandler object
void XMLStreamHandler::Init()
{
	if (m_pEnv) delete m_pEnv;
	if (m_pHead) delete m_pHead;
	if (m_pBody) delete m_pBody;
	if (m_pFault) delete m_pFault;
	if (m_pMethod) delete m_pMethod;
	m_pEnv = NULL;
	m_pHead = NULL;
	m_pBody = NULL;
	m_pFault = NULL;
	m_pMethod = NULL;
	m_PL0 = SOAP_UNKNOWN;
	m_PL1 = SOAP_UNKNOWN;
	m_PL2 = SOAP_UNKNOWN;
	m_Success = SUCCESS;
	m_nSoapVersion = SOAP_VER_1_1;
	for (m_it = m_Params.begin(); m_it != m_Params.end(); m_it++)
	{
		delete (*m_it);
	}
	m_Params.clear();
	m_NsStack.clear(); //this will also delete any strings there
	m_it = NULL;
	m_nParamNestingLevel = 0;
}

void XMLStreamHandler::FillEnvelope(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs)
{
	char* pc; 
	string str;
	Attribute* pAttr;
	pc = __TRC(qname);
	str = pc;
	__REL(&pc);
	pAttr = new Attribute();
	if (str.find(':') != string::npos) 
	{
		str = str.substr(0, str.find(':'));
		m_pEnv->setPrefix(str);
		pAttr->setPrefix(str);
	}
	pc =__TRC(uri);
	str = pc;
	__REL(&pc);
	pAttr->setValue(str);
	m_pEnv->addNamespaceDecl(pAttr);

	if (str == g_sObjSoapEnvVersionsStruct[SOAP_VER_1_1].pchEnvelopeNamespaceUri)
	{
		m_nSoapVersion = SOAP_VER_1_1;
	}
	else if (str == g_sObjSoapEnvVersionsStruct[SOAP_VER_1_2].pchEnvelopeNamespaceUri)
	{
		m_nSoapVersion = SOAP_VER_1_2;
	}
	else
	{
		//error condition
	}

	//Set Attributes
	unsigned int nAttrs = attrs.getLength();
	for (unsigned int ix=0;ix<nAttrs;ix++)
	{
		pAttr = new Attribute();
		
		pc = __TRC(attrs.getQName(ix));
		str = pc;
		__REL(&pc);
		pAttr->setPrefix(str);

		pc = __TRC(attrs.getValue(ix));
		str = pc;
		__REL(&pc);
		pAttr->setValue(str);

		pc = __TRC(attrs.getLocalName(ix));
		str = pc;
		__REL(&pc);
		pAttr->setLocalName(str);

		pc = __TRC(attrs.getURI(ix));
		str = pc;
		__REL(&pc);
		pAttr->setUri(str);

		m_pEnv->addAttribute(pAttr);	
	}
}

void XMLStreamHandler::FillBody(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs)
{
	//nothing to do
}

void XMLStreamHandler::FillHeader(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs)
{
	//nothing to do
}

void XMLStreamHandler::FillFault(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs)
{
	//nothing to do
}

void XMLStreamHandler::FillMethod(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs)
{
	char* pc; 
	string str;
	pc = __TRC(qname);
	str = pc;
	__REL(&pc);
	if (str.find(':') != string::npos) 
	{
		str = str.substr(0, str.find(':'));
		m_pMethod->setPrefix(str);
		pc = __TRC(uri);
		str = pc;
		__REL(&pc);
		m_pMethod->setUri(str);
	}
	pc = __TRC(localname);
	str = pc;
	__REL(&pc);
	m_pMethod->setLocalName(str);
/*
	//Set Attributes
	unsigned int nAttrs = attrs.getLength();
	for (unsigned int ix=0;ix<nAttrs;ix++)
	{
		pAttr = new Attribute();
		
		pc = __TRC(attrs.getQName(ix));
		str = pc;
		__REL(&pc);
		pAttr->setPrefix(str);

		pc = __TRC(attrs.getValue(ix));
		str = pc;
		__REL(&pc);
		pAttr->setValue(str);

		pc = __TRC(attrs.getLocalName(ix));
		str = pc;
		__REL(&pc);
		pAttr->setLocalName(str);

		pc = __TRC(attrs.getURI(ix));
		str = pc;
		__REL(&pc);
		pAttr->setUri(str);

		m_pMethod->addAttribute(pAttr);	
	}
*/
}

void XMLStreamHandler::createHeaderBlock(const XMLCh *const uri, const XMLCh *const localname, const XMLCh *const qname, const Attributes &attrs)
{
	pHeaderBlock= new HeaderBlock();
	//pHeaderBlock->setPrefix("A");
	//pHeaderBlock->setLocalName("A");
	pHeaderBlock->setUri("A");


	char* pc; 
	string str;	
	pc = __TRC(qname);
	str = pc;
	__REL(&pc);
	
	if (str.find(':') != string::npos) 
	{
		str = str.substr(0, str.find(':'));
		pHeaderBlock->setPrefix(str);		
	}

	pc = __TRC(localname);
	str = pc;
	__REL(&pc);
	pHeaderBlock->setLocalName(str);

	pc = __TRC(uri);
	str = pc;
	__REL(&pc);
	pHeaderBlock->setUri(str);

}
