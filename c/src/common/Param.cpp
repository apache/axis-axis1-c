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
#include "../common/AxisException.h"
#include "BasicTypeSerializer.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
string Param::m_sSZ = "";
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
		m_Value.a->t = param.m_Value.a->t;
		m_Value.a->s = param.m_Value.a->s;
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
		throw new AxisException(SF_PARATYPEMISMATCH); 
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
		throw new AxisException(SF_PARATYPEMISMATCH); 
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
		throw new AxisException(SF_PARATYPEMISMATCH); 
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
    throw new AxisException(SF_PARATYPEMISMATCH); 
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
		throw new AxisException(SF_PARATYPEMISMATCH); 
	}
	return m_Value.f;
}

XSDTYPE Param::GetType() const
{
	return m_Type;
}

int Param::serialize(string& sSerialized, SoapSerializer& pSZ)
{
	return SUCCESS;
}

int Param::serialize(string& sSerialized)
{
	switch (m_Type){
	case XSD_INT:
		m_sSZ = BasicTypeSerializer::serialize(m_sName, m_Value.n);
		break;
	case XSD_FLOAT:
		m_sSZ = BasicTypeSerializer::serialize(m_sName, m_Value.f);
		break;
	case XSD_STRING:
		m_sSZ = BasicTypeSerializer::serialize(m_sName, m_sValue);
		break;
	case XSD_HEXBINARY:
		m_sSZ = BasicTypeSerializer::serialize(m_sName, m_sValue, XSD_HEXBINARY);
		break;
	case XSD_BASE64BINARY:
		m_sSZ = BasicTypeSerializer::serialize(m_sName, m_sValue, XSD_BASE64BINARY);
		break;
	case XSD_ARRAY:
		//m_sSZ = "<abc:ArrayOfPhoneNumbers xmlns:abc="http://example.org/2001/06/numbers"
		//				xmlns:enc="http://www.w3.org/2001/06/soap-encoding" 
        //              enc:arrayType="abc:phoneNumberType[2]" >";
		if (!m_Value.a) return FAIL; //error condition
		m_sSZ = "<";
		if (!m_strPrefix.empty())
		{
			m_sSZ += m_strPrefix + ":" + m_sName + " xmlns:" + m_strPrefix + "=\"" + m_strUri + "\"";
		}
		else
		{
			m_sSZ += m_sName ;
		}

		m_sSZ += " xmlns:enc"; 
		m_sSZ += "=\"http://www.w3.org/2001/06/soap-encoding\"";
		if (m_Value.a->t == USER_TYPE)
		{
			m_sSZ += " xmlns:def=" + m_Value.a->m_URI; //this prefix should be dynamically taken from serializer.
		}
		m_sSZ += "enc:arrayType=";
		if (m_Value.a->t == USER_TYPE)
		{
			m_sSZ += "def:" + m_Value.a->m_TypeName; //this prefix should be dynamically taken from serializer.
		}
		else //basic type array
		{
			m_sSZ += "xsd:";
			m_sSZ += BasicTypeSerializer::BasicTypeStr(m_Value.a->t);
		}

		sprintf(m_Buf,"[%d]", m_Value.a->s);

		m_sSZ += m_Buf;
		m_sSZ += ">";
		m_sSZ += m_Value.a->Serialize(); //Only serializes the inner items
		m_sSZ += "</";
		if (!m_strPrefix.empty())
		{
			m_sSZ += m_strPrefix + ":" + m_sName; 
		}
		else
		{
			m_sSZ += m_sName;
		}
		m_sSZ += ">";
		break;
	case USER_TYPE:
		m_sSZ = m_Value.o->Serialize();
		break;
	default:;
	}
	sSerialized += m_sSZ;
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
    throw new AxisException(SF_PARATYPEMISMATCH);
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
