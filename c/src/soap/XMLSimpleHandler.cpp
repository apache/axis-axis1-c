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
//#include <stdlib.h>
//#include <axis/soap/XMLStreamHandler.h>
#include <axis/soap/XMLSimpleHandler.h>
#include <axis/common/TypeMapping.h>
#include <axis/soap/URIMapping.h>
#include <axis/soap/Attribute.h>
#include <axis/soap/SoapEnvVersions.h>
#include <axis/soap/CharacterElement.h>
#include <axis/common/AxisUtils.h>

#include <axis/common/AxisTrace.h>


#define __XTRC(x) x

XMLStreamHandler::XMLStreamHandler()
{

    AXISTRACE1("XMLStreamHandler");
	m_pEnv = NULL;
	m_pHead = NULL;
	m_pBody = NULL;
	m_pFault = NULL;
	m_pMethod = NULL;
	m_pHeaderBlock = NULL;
	m_it = NULL;
}

XMLStreamHandler::~XMLStreamHandler()
{
	if (m_pEnv) delete m_pEnv;
	if (m_pHead) delete m_pHead;
	if (m_pBody) delete m_pBody;
	if (m_pFault) delete m_pFault;
	if (m_pMethod) delete m_pMethod;
	if (m_pHeaderBlock) delete m_pHeaderBlock;
	//following is to avoid Param destructor deleting its complex member which object
	//belongs to this class - see //Destructor Notice in this file.
	m_Param.m_Type = XSD_INT;
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

void XMLStreamHandler::startElement(const string& uri,const string& localname,const string& qname,const AttributesT &attrs)
{
    AXISTRACE1("startElement");
	AxisXMLString sLname = __XTRC(localname);
	const AxisXMLCh* lname = sLname.c_str();
	switch (m_PL0)
	{
	case SOAP_UNKNOWN:
	if(0 == strcmp(lname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_ENVELOPE]))
	{
		m_PL0 = SOAP_ENVELOP;
		m_pEnv = new SoapEnvelope();
		//set all attributes of SoapEnvelope
		FillEnvelope(uri,localname,qname,attrs);
	}
	break;
	case SOAP_ENVELOP:
	if(0 == strcmp(lname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_BODY]))
	{
		m_PL0 = SOAP_BODY;
		m_pBody = new SoapBody();
		//set all attributes of SoapBody
		FillBody(uri,localname,qname,attrs);	
	}
	else if (0 == strcmp(lname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_HEADER]))
	{
		m_PL0 = SOAP_HEADER;
		m_pHead = new SoapHeader();
        
		//set all attributes of SoapHeader
		FillHeader(uri,localname,qname,attrs);
	}
	else if (0 == strcmp(lname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_FAULT]))
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
			if (0 == strcmp(lname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_MULTIREF]))
			{
				m_sLastElement = lname;
				SetParamType(attrs); 
				m_PL1 = SOAP_PARAM;
			}
			else //now comes method name in RPC Style
			{
				m_PL1 = SOAP_METHOD;
				m_pMethod = new SoapMethod();
                AXISTRACE2("startElement:localname: ", localname.c_str());
				FillMethod(uri,localname,qname,attrs);
			}
			break;
		case SOAP_METHOD: //now comes parameters
			//Get Param name and type
			//m_Param.m_sName = localname;
			m_sLastElement = lname;
			SetParamType(attrs); 
			m_PL1 = SOAP_PARAM;
			m_nParamNestingLevel++;
			break;
		case SOAP_PARAM: //Custom types
			if (m_sLastElement != lname)
			{
				m_Params.push_back(new Param(m_Param)); //parent param
			}
			//m_Param.m_sName = localname;
			m_sLastElement = lname;
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
}

void XMLStreamHandler::endElement (const string& uri, const string& localname,const string& qname)
{
	AxisXMLString sLname = __XTRC(localname);
	const AxisXMLCh* lname = sLname.c_str();
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
		if (m_sLastElement == lname)
		{
			m_Params.push_back(new Param(m_Param)); //current param
		}
		m_PL1 = SOAP_METHOD; //next parameter can be Nth parameter just within the Method element.
		m_nParamNestingLevel--;
		break;
	case SOAP_HEADER_BLOCK: //enf of a HeaderBlock
		//Add HeaderBlock to Header
		m_pHead->addHeaderBlock(m_pHeaderBlock);

		m_PL1= SOAP_UNKNOWN;
		break;
	default:
		m_Success = FAIL;
	}
}

void  XMLStreamHandler::characters (const string& chars,const unsigned int length)
{
    AXISTRACE1("characters");
	if ((m_PL0 == SOAP_BODY) && (m_PL1 == SOAP_PARAM)) //Make this a switch statement if many cases to be handled
	{
			
		m_Param.SetValue(chars.c_str());
	} 
	else if ((m_PL0 == SOAP_HEADER) && (m_PL1 == SOAP_HEADER_BLOCK)) 
	{
		//Get the value of the header entry
		CharacterElement* pCharacterElement = NULL;
		
		pCharacterElement = new CharacterElement(chars.c_str());
			
		if (pCharacterElement)
			m_pHeaderBlock->addChild(pCharacterElement);
	}
}

void XMLStreamHandler::startPrefixMapping(const std::string& prefix, const std::string& uri)
{
	AxisXMLString sPrefix = __XTRC(prefix); 
	m_NsStack[sPrefix.c_str()] = __XTRC(uri); //I think the same prifix cannot repeat ???
}

void XMLStreamHandler::endPrefixMapping(const std::string& prefix)
{
	m_NsStack.erase(__XTRC(prefix)); //I think the same prifix cannot repeat ???
}

void XMLStreamHandler::warning(const SAX::SAXParseException& exception)
{

}
void XMLStreamHandler::error(const SAX::SAXParseException& exception)
{
//  sprintf((char*)chEBuf, "Error : %s", __TRC(exception.getMessage()));
	m_Success = FAIL;
}
void XMLStreamHandler::fatalError(const SAX::SAXParseException& exception)
{
// sprintf((char*)chEBuf, "Fatal Error : %s", __TRC(exception.getMessage()));
	m_Success = FAIL;
}

int XMLStreamHandler::Success()
{
	return m_Success;
}

void XMLStreamHandler::SetParamType(const AttributesT &attrs)
{
	//in case there are no attributes describing the type the default is set to XSD_UNKNOWN
	m_Param.m_Type = XSD_UNKNOWN;
	AxisXMLString sValue, sPrefix, sType, sDimensions;
	for (int i = 0; i < attrs.getLength(); i++) 
	{
		AxisXMLString sLocal = __XTRC(attrs.getLocalName(i));
		const AxisXMLCh* local = sLocal.c_str();
		sValue = __XTRC(attrs.getValue(i));
		URITYPE urit = URIMapping::Map(__XTRC(attrs.getURI(i).c_str()));
		switch (urit)
		{
		case URI_XSI: //xsi:type="xsd:int"
			if (0 == strcmp(local, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_TYPE]))
			{
				int colonindex = sValue.find(':'); 
				if (colonindex != AxisXMLString::npos) 
				{
					sPrefix = sValue.substr(0, colonindex);
					sType = sValue.substr(colonindex+1,AxisXMLString::npos);
					if (m_NsStack.find(sPrefix) != m_NsStack.end())
					{
						if(URIMapping::Map(m_NsStack[sPrefix].c_str()) == URI_XSD)
						{
							//check for xml data types
							m_Param.m_Type = TypeMapping::Map(sType.c_str());
						}
						else
						{
							//custom data type
							m_Param.m_Type = USER_TYPE;
							m_Param.m_Value.pCplxObj = &m_CplxObj; //Destructor Notice1
							m_Param.m_Value.pCplxObj->m_TypeName = sType.c_str();
							m_Param.m_Value.pCplxObj->m_URI = m_NsStack[sPrefix].c_str();
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
			if (0 == strcmp(local, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_ARRAYTYPE]))
			{
				m_Param.m_Type = XSD_ARRAY;
				m_Param.m_Value.pArray = &m_ArrayBean;

				int colonindex = sValue.find(':'); 
				if (colonindex != AxisXMLString::npos) 
				{
					sPrefix = sValue.substr(0, colonindex);
					int bracketindex = sValue.find('[');
					if (bracketindex == AxisXMLString::npos)
					{
						//no [] - this is an error condition
					}
					sType = sValue.substr(colonindex+1,bracketindex-colonindex-1);
					sDimensions = sValue.substr(bracketindex);

					if (m_NsStack.find(sPrefix) != m_NsStack.end())
					{
						if(URIMapping::Map(m_NsStack[sPrefix].c_str()) == URI_XSD)
						{
							//check for xml data types
							m_Param.m_Value.pArray->m_type = TypeMapping::Map(sType.c_str());
						}
						else
						{
							m_Param.m_Value.pArray->m_TypeName = sType.c_str();
							m_Param.m_Value.pArray->m_URI = m_NsStack[sPrefix].c_str();
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
			if (0 == strcmp(local, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_HREF]))
			{
				m_Param.m_Type = ACCESSOR;
				//m_Param.m_sValue = sValue.substr(sValue.find('#')+1);
			}
			else if (0 == strcmp(local, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_ID]))
			{
				//m_Param.m_sName = sValue;
			}

		default:; // is this an error condition ???
		}	
	}
}	

// Input is a string like "[3]" or "[2,3]" which is the dimension of the array type
// being parsed. 
int XMLStreamHandler::SetArrayDimensions(AxisXMLString &sDimensions)
{
	int si=0;
	int ei=0;
	si = sDimensions.find('[', ei);
	do
	{
		ei = sDimensions.find(',', si+1);
		if (ei == string::npos)
			ei = sDimensions.find(']', si+1);
		m_Param.m_Value.pArray->m_size.push_back(atoi(sDimensions.substr(si+1,(ei-si-1)).c_str()));
		si = ei;
	} while (sDimensions.find(',', si+1) != string::npos);
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
	m_ArrayBean.m_size.clear();
	m_CplxObj.Init();
	m_sLastElement = ' ';
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

void XMLStreamHandler::FillEnvelope(const string& uri, const string& localname, const string& qname, const AttributesT &attrs)
{
	AxisXMLString str;
	const AxisXMLCh* pchURI;
	Attribute* pAttr;
	str = __XTRC(qname);
	pAttr = new Attribute();
	if (str.find(':') != AxisXMLString::npos) 
	{
		str = str.substr(0, str.find(':'));
		m_pEnv->setPrefix(str.c_str());
		pAttr->setPrefix(str.c_str());
	}

	str = __XTRC(uri);
	pchURI = str.c_str();
	
	pAttr->setValue(pchURI);
	m_pEnv->addNamespaceDecl(pAttr);

	if (0 == strcmp(pchURI, SoapKeywordMapping::Map(SOAP_VER_1_1).pchNamespaceUri))
	{
		m_nSoapVersion = SOAP_VER_1_1;
	}
	else if (0 == strcmp(pchURI, SoapKeywordMapping::Map(SOAP_VER_1_2).pchNamespaceUri))
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
		pAttr->setPrefix(__XTRC(attrs.getQName(ix).c_str()));
		pAttr->setValue(__XTRC(attrs.getValue(ix).c_str()));
		pAttr->setLocalName(__XTRC(attrs.getLocalName(ix).c_str()));
		pAttr->setUri(__XTRC(attrs.getURI(ix).c_str()));
		m_pEnv->addAttribute(pAttr);	
	}
}

void XMLStreamHandler::FillBody(const string& uri, const string& localname, const string& qname, const AttributesT &attrs)
{
	//nothing to do
}

void XMLStreamHandler::FillHeader(const string& uri, const string& localname, const string& qname, const AttributesT &attrs)
{
	//nothing to do
}

void XMLStreamHandler::FillFault(const string& uri, const string& localname, const string& qname, const AttributesT &attrs)
{
	//nothing to do
}

void XMLStreamHandler::FillMethod(const string& uri, const string& localname, const string& qname, const AttributesT &attrs)
{
	AxisXMLString str = __XTRC(qname);
	if (str.find(':') != AxisXMLString::npos) 
	{
		str = str.substr(0, str.find(':'));
		m_pMethod->setPrefix(str.c_str());
		str = __XTRC(uri);
		m_pMethod->setUri(str.c_str());
	}
	m_pMethod->setLocalName(__XTRC(localname.c_str()));
}

void XMLStreamHandler::createHeaderBlock(const string& uri, const string& localname, const string& qname, const AttributesT &attrs)
{
	m_pHeaderBlock= new HeaderBlock();
	AxisXMLString str = __XTRC(qname);	
	if (str.find(':') != AxisXMLString::npos) 
	{
		str = str.substr(0, str.find(':'));
		m_pHeaderBlock->setPrefix(str.c_str());		
	}
	m_pHeaderBlock->setLocalName(__XTRC(localname.c_str()));
	m_pHeaderBlock->setUri(__XTRC(uri.c_str()));
}

// EntityResolver
SAX::InputSource XMLStreamHandler::resolveEntity(const std::string& publicId, const std::string& systemId)
{
  return SAX::InputSource();
} // resolveEntity

/*const AxisChar* XMLStreamHandler::__XTRC(const XMLCh *pChar)
{
	if (true == (XMLString::transcode(pChar, m_Buffer, TRANSCODE_BUFFER_SIZE-1)))
		return m_Buffer;
	else 
		return ""; 
}*/
