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

// Param.cpp: implementation of the Param class.
//
//////////////////////////////////////////////////////////////////////

#include <axis/engine/AxisEngine.h>
#include <axis/common/Param.h>
#include <axis/common/ArrayBean.h>
#include <axis/common/BasicTypeSerializer.h>
#include <stdlib.h>
#include <stdio.h>
#include <axis/common/AxisUtils.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int AxisEngine::m_bServer;

Param::~Param()
{
	switch (m_Type){
	case XSD_ARRAY:
		if (m_Value.pArray) delete m_Value.pArray;
		break;
	case USER_TYPE:
		delete m_Value.pCplxObj;
		break;
	case XSD_STRING:
	case XSD_ANYURI:
	case XSD_QNAME:
	case XSD_NOTATION:
		if (AxisEngine::m_bServer) 
		{
			free((void*)m_Value.pStrValue);
		}
		break;
	case XSD_BASE64BINARY:
	case XSD_HEXBINARY:
		if (AxisEngine::m_bServer) 
		{
			free((void*)(m_Value.hbValue.__ptr));
		}
		break;
	default:;
	}
}

int Param::serialize(SoapSerializer& pSZ)
{
	AxisString ATprefix;
	switch (m_Type){
	case XSD_ARRAY:
		//pSZ.Serialize("<abc:ArrayOfPhoneNumbers xmlns:abc="http://example.org/2001/06/numbers"
		//				xmlns:enc="http://www.w3.org/2001/06/soap-encoding" 
        //              enc:arrayType="abc:phoneNumberType[2]" >";
		if (!m_Value.pArray) return AXIS_FAIL; //error condition
		if (RPC_ENCODED == pSZ.GetStyle())
		{
			pSZ.Serialize("<", NULL);
			if (!m_strPrefix.empty())
			{
				pSZ.Serialize(m_strPrefix.c_str(), ":",  m_sName.c_str(), "Array", " xmlns:", m_strPrefix.c_str(), "=\"", m_strUri.c_str(), "\"", NULL);
			}
			else
			{
				pSZ.Serialize(m_sName.c_str(), "Array", NULL);
			}
			//get a prefix from Serializer
			ATprefix = pSZ.GetNamespacePrefix(m_Value.pArray->m_URI.c_str());

			pSZ.Serialize(" xmlns:enc", NULL); 
			pSZ.Serialize("=\"http://www.w3.org/2001/06/soap-encoding\" ", NULL);
			if (m_Value.pArray->m_type == USER_TYPE)
			{
				pSZ.Serialize("xmlns:", ATprefix.c_str(), "=\"", m_Value.pArray->m_URI.c_str(), "\" ", NULL); 
			}
			pSZ.Serialize("enc:arrayType=\"", NULL);
			if (m_Value.pArray->m_type == USER_TYPE)
			{
				pSZ.Serialize(ATprefix.c_str(), ":", m_Value.pArray->m_TypeName.c_str(), NULL);
			}
			else //basic type array
			{
				pSZ.Serialize("xsd:", BasicTypeSerializer::BasicTypeStr(m_Value.pArray->m_type), NULL);
			}
			{
				char Buf[10]; //maximum array dimension is 99999999
				sprintf(Buf,"[%d]", m_Value.pArray->m_nSize);
				pSZ.Serialize(Buf, NULL);
			}

			pSZ.Serialize("\">", NULL);
			m_Value.pArray->Serialize(pSZ); //Only serializes the inner items
			pSZ.Serialize("</", NULL);
			if (!m_strPrefix.empty())
			{
				pSZ.Serialize(m_strPrefix.c_str(), ":", m_sName.c_str(), "Array", NULL); 
			}
			else
			{
				pSZ.Serialize(m_sName.c_str(), "Array", NULL);
			}
			pSZ.RemoveNamespacePrefix(m_Value.pArray->m_URI.c_str());
			pSZ.Serialize(">", NULL);
		}
		else /* no wrapper element in doc/lit style. So directly call Array Serializer */
		{
			m_Value.pArray->Serialize(pSZ); //Only serializes the inner items
		}
		break;
	case USER_TYPE:
		if (RPC_ENCODED == pSZ.GetStyle())
		{
			m_Value.pCplxObj->pSZFunct(m_Value.pCplxObj->pObject, &pSZ, false);
		}
		else
		{
			pSZ.Serialize("<", m_sName.c_str(), ">", NULL);
			m_Value.pCplxObj->pSZFunct(m_Value.pCplxObj->pObject, &pSZ, false);			
			pSZ.Serialize("</", m_sName.c_str(), ">", NULL);
		}
		break;
	default: 
		/* all basic types */
		pSZ.SerializeAsElement(m_sName.c_str(), &(m_Value.nValue), m_Type);
	}
	return AXIS_SUCCESS;
}

int Param::SetValue(XSDTYPE nType, uParamValue Value)
{
	m_Type = nType;
	switch (m_Type)
	{
	case XSD_INT:
	case XSD_BOOLEAN:
        m_Value.nValue = Value.nValue;
		break;
	case XSD_UNSIGNEDINT:
        m_Value.unValue = Value.unValue;
		break;
    case XSD_SHORT:
        m_Value.sValue = Value.sValue;
		break;
	case XSD_UNSIGNEDSHORT:
        m_Value.usValue = Value.usValue;
		break;
    case XSD_BYTE:
        m_Value.cValue = Value.cValue;
		break;
	case XSD_UNSIGNEDBYTE:
        m_Value.ucValue = Value.ucValue;
		break;
    case XSD_LONG:
    case XSD_INTEGER:
        m_Value.lValue = Value.lValue;
		break;
	case XSD_UNSIGNEDLONG:
        m_Value.ulValue = Value.ulValue;
		break;
	case XSD_FLOAT:
        m_Value.fValue = Value.fValue;
		break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
		m_Value.dValue = Value.dValue;
		break;        
	case XSD_STRING:
	case XSD_ANYURI:
	case XSD_QNAME:
	case XSD_NOTATION:
		m_Value.pStrValue = Value.pStrValue;
		break;
	case XSD_HEXBINARY:
		m_Value.hbValue = Value.hbValue;
		break;
	case XSD_BASE64BINARY:
		m_Value.b64bValue = Value.b64bValue;
		break;
  case XSD_DURATION:
        m_Value.lDuration = Value.lDuration;
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
        m_Value.tValue = Value.tValue;
    //    m_uAxisTime.setValue(nType, m_Value);
	//Continue this for all basic types
	case XSD_ARRAY:
		m_Value.pArray = Value.pArray;
		break;
	case USER_TYPE:
		m_Value.pCplxObj = Value.pCplxObj;
		break;
	default:
		return AXIS_FAIL; //this is an unexpected situation
	}
	return AXIS_SUCCESS;
}

void Param::setPrefix(const AxisChar* prefix)
{
	m_strPrefix = prefix;
}

void Param::setUri(const AxisChar* uri)
{
	m_strUri = uri;
}

int Param::SetUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct)
{
	if (m_Type != USER_TYPE) return AXIS_FAIL;
	m_Value.pCplxObj = new ComplexObjectHandler;
	m_Value.pCplxObj->pObject = pObject;
	m_Value.pCplxObj->pDZFunct = pDZFunct;
	m_Value.pCplxObj->pDelFunct = pDelFunct;
	return AXIS_SUCCESS;
}

int Param::SetArrayElements(void* pElements)
{
	if (m_Type != XSD_ARRAY) return AXIS_FAIL;
	if (m_Value.pArray)
	{
		if (m_Value.pArray->m_type != USER_TYPE)
		{
			m_Value.pArray->m_value.sta = pElements;
			return AXIS_SUCCESS;
		}
		else //unexpected situation
		{
			return AXIS_FAIL;
		}
	}
	return AXIS_FAIL;
}

//following function is called to set array of user types.
int Param::SetArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct)
{
	if (m_Type != XSD_ARRAY) return AXIS_FAIL;
	if (m_Value.pArray)
	{
		if (m_Value.pArray->m_type == USER_TYPE)
		{
			m_Value.pArray->m_value.cta = new ComplexObjectHandler;
			m_Value.pArray->m_value.cta->pDZFunct = pDZFunct;
			m_Value.pArray->m_value.cta->pDelFunct = pDelFunct;
			m_Value.pArray->m_value.cta->pSizeFunct = pSizeFunct;
			m_Value.pArray->m_value.cta->pObject = pObject;
			return AXIS_SUCCESS;
		}
		else //unexpected situation
		{
			return AXIS_FAIL;
		}
	}
	return AXIS_FAIL;	
}

void Param::SetName(const AxisChar* sName)
{
	m_sName = sName;
}

// ComplexObjectHandler functions
ComplexObjectHandler::ComplexObjectHandler()
{
	Init();
}

ComplexObjectHandler::~ComplexObjectHandler()
{
	/* At client side we do not delete either output or return objects */
	if (AxisEngine::m_bServer) 
	{
		if (pObject && pDelFunct) pDelFunct(pObject, false, 0);
	}
}

void ComplexObjectHandler::Init()
{
	pObject = NULL;
	pSZFunct = NULL;
	pDelFunct = NULL; 
	pDZFunct = NULL;
	pSizeFunct = NULL;
	m_TypeName = "";
	m_URI = "";	
}
