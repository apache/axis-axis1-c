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

#include "Param.h"
#include "AccessBean.h"
#include "BasicTypeSerializer.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//string Param::m_sSZ = "";
//string ArrayBean::m_sSZ = "";
char Param::m_Buf[64];

Param::Param(Param& param)
{
	m_sName = param.m_sName;
	m_sValue = param.m_sValue;
	m_Type = param.m_Type;	
	if (m_Type == USER_TYPE) 
	{
		m_Value.o = new AccessBean();
		m_Value.o->m_TypeName = param.m_Value.o->m_TypeName;
		m_Value.o->m_URI = param.m_Value.o->m_URI;
	}
	else if(m_Type == XSD_ARRAY)
	{
		m_Value.a = new ArrayBean();
		m_Value.a->m_TypeName = param.m_Value.a->m_TypeName;
		m_Value.a->m_URI = param.m_Value.a->m_URI;
		m_Value.a->m_type = param.m_Value.a->m_type;
		m_Value.a->m_size = param.m_Value.a->m_size;
		m_Value.a->m_ItemName = param.m_Value.a->m_ItemName;
		//copy constructor is not intended to use to copy the array in
		//union v
	}	
	else 
	{
		m_Value = param.m_Value;
	}
}

Param::Param(string &str, XSDTYPE type)
{
	m_sValue = str;
	m_Type = type;
	switch (type)
	{
	case XSD_STRING: m_sName = "String"; break;
	case XSD_BASE64BINARY: m_sName = "Base64BinaryString"; break;
	case XSD_HEXBINARY: m_sName = "HexBinaryString"; break;
	}
}

Param::Param(int nValue)
{
	m_sName = "Int";
	m_Value.n = nValue;
	m_Type = XSD_INT;
}

Param::Param(float fValue)
{
	m_sName = "Float";
	m_Value.f = fValue;
	m_Type = XSD_FLOAT;
}

Param::Param(double dValue)
{
	m_sName = "Double";
	m_Value.d = dValue;
	m_Type = XSD_DOUBLE;
}

Param::~Param()
{
	switch (m_Type){
	case XSD_ARRAY:
		if (m_Value.a) delete m_Value.a;
		break;
	case USER_TYPE:
		if (m_Value.o) delete m_Value.o;
		break;
	default:;
	}
}

const string& Param::GetString()
{
	if (m_Type == XSD_STRING){}
	else if (m_Type == XSD_UNKNOWN) //see GetInt() to see why we do this
	{
		m_Type = XSD_STRING;
	}
	else 
	{
		//exception
	}
	return m_sValue;
}

const string& Param::GetHexString()
{
	if (m_Type == XSD_HEXBINARY){}
	else if (m_Type == XSD_UNKNOWN) //see GetInt() to see why we do this
	{
		m_Type = XSD_HEXBINARY;
	}
	else 
	{
		//exception
	}
	return m_sValue;
}

const string& Param::GetBase64String()
{
	if (m_Type == XSD_BASE64BINARY){}
	else if (m_Type == XSD_UNKNOWN) //see GetInt() to see why we do this
	{
		m_Type = XSD_BASE64BINARY;
	}
	else 
	{
		//exception
	}
	return m_sValue;
}

int Param::GetInt()
{
	if (m_Type == XSD_INT){}
	else if (m_Type == XSD_UNKNOWN) 
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_INT;
		SetValue(m_sValue);
	}
	else 
	{
		//exception
	}
	return m_Value.n;
}

float Param::GetFloat()
{
	if (m_Type == XSD_FLOAT){}
	else if (m_Type == XSD_UNKNOWN)
	{
		m_Type = XSD_FLOAT;
		SetValue(m_sValue);
	}
	else
	{
		//exception
	}
	return m_Value.f;
}

XSDTYPE Param::GetType() const
{
	return m_Type;
}

int Param::serialize(ISoapSerializer& pSZ)
{
	string ATprefix;
	switch (m_Type){
	case XSD_INT:
		pSZ << BasicTypeSerializer::serialize(m_sName, m_Value.n).c_str();
		break;
	case XSD_FLOAT:
		pSZ << BasicTypeSerializer::serialize(m_sName, m_Value.f).c_str();
		break;
	case XSD_STRING:
		pSZ << BasicTypeSerializer::serialize(m_sName, m_sValue).c_str();
		break;
	case XSD_HEXBINARY:
		pSZ << BasicTypeSerializer::serialize(m_sName, m_sValue, XSD_HEXBINARY).c_str();
		break;
	case XSD_BASE64BINARY:
		pSZ << BasicTypeSerializer::serialize(m_sName, m_sValue, XSD_BASE64BINARY).c_str();
		break;
	case XSD_ARRAY:
		//pSZ << "<abc:ArrayOfPhoneNumbers xmlns:abc="http://example.org/2001/06/numbers"
		//				xmlns:enc="http://www.w3.org/2001/06/soap-encoding" 
        //              enc:arrayType="abc:phoneNumberType[2]" >";
		if (!m_Value.a) return FAIL; //error condition
		pSZ << "<";
		if (!m_strPrefix.empty())
		{
			pSZ << m_strPrefix.c_str() << ":" << m_sName.c_str() << " xmlns:" << m_strPrefix.c_str() << "=\"" << m_strUri.c_str() << "\"";
		}
		else
		{
			pSZ << m_sName.c_str();
		}
		//get a prefix from Serializer
		ATprefix = pSZ.getNewNamespacePrefix();

		pSZ << " xmlns:enc"; 
		pSZ << "=\"http://www.w3.org/2001/06/soap-encoding\"";
		if (m_Value.a->m_type == USER_TYPE)
		{
			pSZ << " xmlns:" << ATprefix.c_str() << "=" << m_Value.a->m_URI.c_str(); //this prefix should be dynamically taken from serializer.
		}
		pSZ << "enc:arrayType=";
		if (m_Value.a->m_type == USER_TYPE)
		{
			pSZ << ATprefix.c_str() << ":" << m_Value.a->m_TypeName.c_str(); //this prefix should be dynamically taken from serializer.
		}
		else //basic type array
		{
			pSZ << "xsd:";
			pSZ << BasicTypeSerializer::BasicTypeStr(m_Value.a->m_type);
		}
		{
			for (list<int>::iterator it=m_Value.a->m_size.begin(); it!=m_Value.a->m_size.end(); it++)
			{
				sprintf(m_Buf,"[%d]", *it);
				pSZ << m_Buf;
			}
		}
		pSZ << ">";
		m_Value.a->Serialize(pSZ); //Only serializes the inner items
		pSZ << "</";
		if (!m_strPrefix.empty())
		{
			pSZ << m_strPrefix.c_str() << ":" << m_sName.c_str(); 
		}
		else
		{
			pSZ << m_sName.c_str();
		}
		pSZ << ">";
		break;
	case USER_TYPE:
		m_Value.o->Serialize(pSZ);
		break;
	default:;
	}
	return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//This method is used by the deserializer to set the value after setting the type
//Also this method assumes that the type is already set and it is a basic type
int Param::SetValue(string &sValue)
{
	m_sValue = sValue; //Whatever the type we put the string representation of the value
	switch (m_Type)
	{
	case XSD_INT:
		m_Value.n = atoi(sValue.c_str());
		break;
	case XSD_FLOAT:
		m_Value.f = atof(sValue.c_str());
		break;
	case XSD_STRING:
	case XSD_HEXBINARY:
	case XSD_BASE64BINARY:
		m_sValue = sValue;
		break;
	//Continue this for all basic types
	case XSD_ARRAY:
	case USER_TYPE:
		//this is an error situation - probably something wrong with the soap
		break;
	default:
		return FAIL; //this is an unexpected situation
	}
	return SUCCESS;
}

void Param::setPrefix(const string &prefix)
{
	m_strPrefix = prefix;
}

void Param::setUri(const string &uri)
{
	m_strUri = uri;
}

void Param::operator=(Param &param)
{
	m_sName = param.m_sName;
	m_sValue = param.m_sValue;
	m_Type = param.m_Type;	
	if (m_Type == USER_TYPE) 
	{
		m_Value.o = param.m_Value.o;
	}
	else if(m_Type == XSD_ARRAY)
	{
		m_Value.a = param.m_Value.a;
	}	
	else 
	{
		m_Value = param.m_Value;
	}
}
