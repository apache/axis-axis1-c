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
#include <axis/soap/SoapParser.h>
#include <axis/common/TypeMapping.h>
#include <axis/soap/URIMapping.h>
#include <axis/soap/Attribute.h>
#include <axis/soap/SoapEnvVersions.h>
#include <axis/soap/CharacterElement.h>
#include <axis/common/AxisUtils.h>

SoapParser::SoapParser()
{
	m_pEnv = NULL;
	m_pHead = NULL;
	m_pBody = NULL;
	m_pFault = NULL;
	m_pMethod = NULL;
	m_pHeaderBlock = NULL;
	m_it = NULL;
	m_Parser = XML_ParserCreateNS(NULL, NAMESPACESEPARATOR);
	m_CharData = "";
}

SoapParser::~SoapParser()
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

void SoapParser::startElement(const XMLCh *qname,const XMLCh **attrs)
{
	QName qn;
	qn.SplitQNameString(qname);
	switch (m_PL0)
	{
	case SOAP_UNKNOWN:
	if(0 == strcmp(qn.localname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_ENVELOPE]))
	{
		m_PL0 = SOAP_ENVELOP;
		m_pEnv = new SoapEnvelope();
		//set all attributes of SoapEnvelope
		FillEnvelope(qn.uri,qn.localname,attrs);
	}
	break;
	case SOAP_ENVELOP:
	if(0 == strcmp(qn.localname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_BODY]))
	{
		m_PL0 = SOAP_BODY;
		m_pBody = new SoapBody();
		//set all attributes of SoapBody
		FillBody(qn.uri,qn.localname,attrs);	
	}
	else if (0 == strcmp(qn.localname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_HEADER]))
	{
		m_PL0 = SOAP_HEADER;
		m_pHead = new SoapHeader();
		//set all attributes of SoapHeader
		FillHeader(qn.uri,qn.localname,attrs);
	}
	else if (0 == strcmp(qn.localname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_FAULT]))
	{
		//m_PL0 = SOAP_FAULT;
		//m_pFault = SoapFault::getSoapFault(1);
		//set all attributes of SoapFault
		//FillFault(qn.uri,qn.localname,qname,attrs);
	}
	else { //Soap error
		m_Success = AXIS_FAIL;
	}
	break;
	case SOAP_HEADER:
		//Soap header entry
		createHeaderBlock(qn.uri, qn.localname, attrs);
		m_PL1= SOAP_HEADER_BLOCK;
		break;
	case SOAP_FAULT:
		//Soap fault sub element
		break;
	case SOAP_BODY:
		switch (m_PL1)
		{
		case SOAP_UNKNOWN:
			if (0 == strcmp(qn.localname,SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_MULTIREF]))
			{
				m_sLastElement = qn.localname;
				SetParamType(attrs); 
				m_PL1 = SOAP_PARAM;
			}
			else //now comes method name in RPC Style
			{
				m_PL1 = SOAP_METHOD;
				m_pMethod = new SoapMethod();
				FillMethod(qn.uri,qn.localname,attrs);
			}
			break;
		case SOAP_METHOD: //now comes parameters
			//Get Param name and type
			//m_Param.m_sName = qn.localname;
			m_sLastElement = qn.localname;
			SetParamType(attrs); 
			m_PL1 = SOAP_PARAM;
			m_nParamNestingLevel++;
			break;
		case SOAP_PARAM: //Custom types
			if (m_sLastElement != qn.localname)
			{
				m_Param.SetValue(m_CharData.c_str());
				m_Params.push_back(new Param(m_Param)); //parent param
				m_CharData = "";
			}
			//m_Param.m_sName = qn.localname;
			m_sLastElement = qn.localname;
			SetParamType(attrs); 
			m_nParamNestingLevel++;
			break;
		default:
			m_Success = AXIS_FAIL;
		}
	break;
	default:
		m_Success = AXIS_FAIL;
	}
	qn.MergeQNameString();
}

void SoapParser::endElement (const XMLCh *qname)
{
	QName qn;
	qn.SplitQNameString(qname);
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
		if (m_sLastElement == qn.localname)
		{
				m_Param.SetValue(m_CharData.c_str());
				m_Params.push_back(new Param(m_Param)); //parent param
				m_CharData = "";
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
		m_Success = AXIS_FAIL;
	}
	qn.MergeQNameString();
}

void  SoapParser::characters(const XMLCh *chars, int length)
{
	XMLCh* pTemp = const_cast<XMLCh*>(chars);
	XMLCh replacedchar = pTemp[length]; //copy and keep existing char at length position
	pTemp[length] = '\0'; //putting nul charactor so that chars can be used safely

	if ((m_PL0 == SOAP_BODY) && (m_PL1 == SOAP_PARAM)) //Make this a switch statement if many cases to be handled
	{
		m_CharData += chars; 
	} 
	else if ((m_PL0 == SOAP_HEADER) && (m_PL1 == SOAP_HEADER_BLOCK)) 
	{
		//Get the value of the header entry
		CharacterElement* pCharacterElement = new CharacterElement(chars);		
		if (pCharacterElement)
			m_pHeaderBlock->addChild(pCharacterElement);
	}
	pTemp[length] = replacedchar; //put back the charactor that was there before putting nul charactor
}

void SoapParser::startPrefixMapping(const XMLCh *prefix, const XMLCh *uri)
{
	if (prefix) m_NsStack[prefix] = uri; //I think the same prifix cannot repeat ???
}

void SoapParser::endPrefixMapping(const XMLCh *prefix)
{
	if (prefix) m_NsStack.erase(prefix); //I think the same prifix cannot repeat ???
}

/*
void SoapParser::warning(const SAXParseException& exception)
{

}
void SoapParser::error(const SAXParseException& exception)
{
//  sprintf((char*)chEBuf, "Error : %s", __TRC(exception.getMessage()));
	m_Success = AXIS_FAIL;
}
void SoapParser::fatalError(const SAXParseException& exception)
{
// sprintf((char*)chEBuf, "Fatal Error : %s", __TRC(exception.getMessage()));
	m_Success = AXIS_FAIL;
}
*/

int SoapParser::Success()
{
	return m_Success;
}

void SoapParser::SetParamType(const XMLCh **attrs)
{
	QName qn;
	//in case there are no attributes describing the type the default is set to XSD_UNKNOWN
	m_Param.m_Type = XSD_UNKNOWN;
	AxisXMLString sValue, sPrefix, sType, sDimensions;
	for (int i = 0; attrs[i]; i += 2) 
	{
		qn.SplitQNameString(attrs[i]);
		sValue = attrs[i+1];
		URITYPE urit = URIMapping::Map(qn.uri);
		switch (urit)
		{
		case URI_XSI: //xsi:type="xsd:int"
			if (0 == strcmp(qn.localname, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_TYPE]))
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
			if (0 == strcmp(qn.localname, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_ARRAYTYPE]))
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
						if(AXIS_SUCCESS != SetArrayDimensions(sDimensions))
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
			if (0 == strcmp(qn.localname, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_HREF]))
			{
				m_Param.m_Type = ACCESSOR;
				//m_Param.m_sValue = sValue.substr(sValue.find('#')+1);
			}
			else if (0 == strcmp(qn.localname, SoapKeywordMapping::Map(m_nSoapVersion).pchWords[SKW_ID]))
			{
				//m_Param.m_sName = sValue;
			}

		default:; // is this an error condition ???
		}
		qn.MergeQNameString();
	}
}	

// Input is a string like "[3]" or "[2,3]" which is the dimension of the array type
// being parsed. 
int SoapParser::SetArrayDimensions(AxisXMLString &sDimensions)
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
	return AXIS_SUCCESS;
}

Param* SoapParser::GetParam()
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

//resets SoapParser object
void SoapParser::Init()
{
	XML_ParserReset(m_Parser, NULL);
	XML_SetUserData(m_Parser, this);
	XML_SetNamespaceDeclHandler(m_Parser, s_startPrefixMapping, s_endPrefixMapping);
	XML_SetElementHandler(m_Parser, s_startElement, s_endElement);
	XML_SetCharacterDataHandler(m_Parser, s_characters);

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
	m_Success = AXIS_SUCCESS;
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

void SoapParser::FillEnvelope(const XMLCh* uri,const XMLCh* localname,const XMLCh **attrs)
{
	AxisXMLString str;
	Attribute* pAttr;
	pAttr = new Attribute();

	pAttr->setValue(uri);
	m_pEnv->addNamespaceDecl(pAttr);

	if (0 == strcmp(uri, SoapKeywordMapping::Map(SOAP_VER_1_1).pchNamespaceUri))
	{
		m_nSoapVersion = SOAP_VER_1_1;
	}
	else if (0 == strcmp(uri, SoapKeywordMapping::Map(SOAP_VER_1_2).pchNamespaceUri))
	{
		m_nSoapVersion = SOAP_VER_1_2;
	}
	else
	{
		//error condition
	}

	QName qn;
	//Set Attributes
	for (int i = 0; attrs[i]; i += 2) 
	{
		qn.SplitQNameString(attrs[i]);
		pAttr = new Attribute();
		pAttr->setValue(attrs[i+1]);
		pAttr->setLocalName(qn.localname);
		pAttr->setUri(qn.uri);
		m_pEnv->addAttribute(pAttr);
		qn.MergeQNameString();
	}
}

void SoapParser::FillBody(const XMLCh* uri,const XMLCh* localname,const XMLCh **attrs)
{
	//nothing to do
}

void SoapParser::FillHeader(const XMLCh* uri,const XMLCh* localname,const XMLCh **attrs)
{
	//nothing to do
}

void SoapParser::FillFault(const XMLCh* uri,const XMLCh* localname,const XMLCh **attrs)
{
	//nothing to do
}

void SoapParser::FillMethod(const XMLCh* uri,const XMLCh* localname,const XMLCh **attrs)
{
	m_pMethod->setUri(uri);
	m_pMethod->setLocalName(localname);
}

void SoapParser::createHeaderBlock(const XMLCh* uri,const XMLCh* localname,const XMLCh **attrs)
{
	m_pHeaderBlock= new HeaderBlock();
	m_pHeaderBlock->setLocalName(localname);
	m_pHeaderBlock->setUri(uri);
}

