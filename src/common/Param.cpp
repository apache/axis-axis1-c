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
#include "ArrayBean.h"
#include "BasicTypeSerializer.h"
#include <stdlib.h>
#include <stdio.h>
#include "AxisUtils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Param::Param(const Param& param)
{
	m_sName = param.m_sName.c_str();
	m_sValue = param.m_sValue.c_str();
	m_Type = param.m_Type;	
	if (m_Type == USER_TYPE) 
	{
		m_Value.pCplxObj = new ComplexObjectHandler();
		m_Value.pCplxObj->m_TypeName = param.m_Value.pCplxObj->m_TypeName.c_str();
		m_Value.pCplxObj->m_URI = param.m_Value.pCplxObj->m_URI.c_str();
	}
	else if(m_Type == XSD_ARRAY)
	{
		m_Value.pArray = new ArrayBean();
		m_Value.pArray->m_TypeName = param.m_Value.pArray->m_TypeName.c_str();
		m_Value.pArray->m_URI = param.m_Value.pArray->m_URI.c_str();
		m_Value.pArray->m_type = param.m_Value.pArray->m_type;
		m_Value.pArray->m_size = param.m_Value.pArray->m_size;
		m_Value.pArray->m_ItemName = param.m_Value.pArray->m_ItemName.c_str();
		//copy constructor is not intended to use to copy the array in
		//union v
	}
    else if (m_Type == XSD_DURATION || m_Type == XSD_DATETIME)
	{
        m_uAxisTime.setType(m_Type);
	}	
	else 
	{
		m_Value = param.m_Value;
	}
}

Param::Param(const AxisChar* str, XSDTYPE type)
{
	m_sValue = str;
	m_Type = type;
	switch (type)
	{
    case XSD_DURATION: m_sName = "Duration"; break;
    case XSD_DATETIME: m_sName = "DateTime"; break;
    case XSD_TIME: m_sName = "Time"; break;
    case XSD_DATE: m_sName = "Date"; break;
    case XSD_YEARMONTH: m_sName = "YearMonth"; break;
    case XSD_YEAR: m_sName = "Year"; break;
    case XSD_MONTHDAY: m_sName = "MonthDay"; break;
    case XSD_DAY: m_sName = "Day"; break;
    case XSD_MONTH: m_sName = "Month"; break;
    case XSD_ANYURI: m_sName = "AnyURIString"; break;
    case XSD_QNAME: m_sName = "QNameString"; break;
	case XSD_STRING: m_sName = "String"; break;
	case XSD_BASE64BINARY: m_sName = "Base64BinaryString"; break;
	case XSD_HEXBINARY: m_sName = "HexBinaryString"; break;
	}
}

Param::Param(time_t time)
{
    m_uAxisTime = AxisTime(time);
}

Param::Param(struct tm timeStruct)
{
    m_uAxisTime = AxisTime(timeStruct);
}

Param::Param(int nValue)
{
	m_sName = "Int";
	m_Value.nValue = nValue;
	m_Type = XSD_INT;
}

Param::Param(unsigned int unValue)
{
	m_sName = "Unsigned Int";
	m_Value.unValue = unValue;
	m_Type = XSD_UNSIGNEDINT;
}

Param::Param(short sValue)
{
    m_sName = "Short";
	m_Value.sValue = sValue;
	m_Type = XSD_SHORT;	
}

Param::Param(unsigned short usValue)
{
    m_sName = "Unsigned Short";
	m_Value.usValue = usValue;
	m_Type = XSD_UNSIGNEDSHORT;
}

Param::Param(char cValue)
{
    m_sName = "Byte";
	m_Value.cValue = cValue;
	m_Type = XSD_BYTE;
}

Param::Param(unsigned char ucValue)
{
    m_sName = "Unsigned Byte";
	m_Value.ucValue = ucValue;
	m_Type = XSD_UNSIGNEDBYTE;
}

Param::Param(long lValue, XSDTYPE type)
{
    m_Type = type;
	switch (type)
	{
        case XSD_LONG:m_sName = "Long";
        case XSD_INTEGER: m_sName = "Integer";
            m_Value.lValue = lValue;
            break;
	}
}

Param::Param(unsigned long ulValue)
{
	m_sName = "Unsigned Long";
	m_Value.ulValue = ulValue;
	m_Type = XSD_UNSIGNEDLONG;
}

Param::Param(float fValue)
{
	m_sName = "Float";
	m_Value.fValue = fValue;
	m_Type = XSD_FLOAT;
}

Param::Param(double dValue, XSDTYPE type)
{
	m_Type = type;
	switch (type)
	{
        case XSD_DOUBLE: m_sName = "Double";
        case XSD_DECIMAL: m_sName = "Decimal";
            m_Value.dValue = dValue;
            break;
	}
	/*m_sName = "Double";
	m_Value.dValue = dValue;
	m_Type = XSD_DOUBLE;*/

}



Param::~Param()
{
	switch (m_Type){
	case XSD_ARRAY:
		if (m_Value.pArray) delete m_Value.pArray;
		break;
	case USER_TYPE:
		delete m_Value.pCplxObj;
		break;
	default:;
	}
}

const AxisString& Param::GetString()
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

const AxisString& Param::GetAnyURI()
{
	if (m_Type == XSD_ANYURI){}
	else if (m_Type == XSD_UNKNOWN) //see GetInt() to see why we do this
	{
		m_Type = XSD_ANYURI;
	}
	else
	{
		//exception
	}
	return m_sValue;
}

const AxisString& Param::GetQName()
{
	if (m_Type == XSD_QNAME){}
	else if (m_Type == XSD_UNKNOWN) //see GetInt() to see why we do this
	{
		m_Type = XSD_QNAME;
	}
	else
	{
		//exception
	}
	return m_sValue;
}

const AxisString& Param::GetHexString()

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

const AxisString& Param::GetBase64String()
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
		SetValue(m_sValue.c_str());
	}
	else 
	{
		//exception
	}
	return m_Value.nValue;
}

struct tm Param::GetDateTime()
{
	if (m_Type == XSD_DATETIME){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_DATETIME;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_uAxisTime.getDateTime();
}

struct tm Param::GetDate()
{
	if (m_Type == XSD_DATE){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_DATE;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_uAxisTime.getDate();
}

struct tm Param::GetTime()
{
	if (m_Type == XSD_TIME){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_TIME;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_uAxisTime.getTime();
}

long Param::GetDuration()
{
	if (m_Type == XSD_DURATION){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_DATETIME;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_uAxisTime.getDuration();
}

unsigned int Param::GetUnsignedInt()
{
	if (m_Type == XSD_UNSIGNEDINT){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_UNSIGNEDINT;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.unValue;
}

short Param::GetShort()
{
	if (m_Type == XSD_SHORT){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_SHORT;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.sValue;
}

unsigned short Param::GetUnsignedShort()
{
	if (m_Type == XSD_UNSIGNEDSHORT){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_UNSIGNEDSHORT;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.usValue;
}

char Param::GetByte()
{
	if (m_Type == XSD_BYTE){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_BYTE;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.cValue;
}

unsigned char Param::GetUnsignedByte()
{
	if (m_Type == XSD_UNSIGNEDBYTE){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_UNSIGNEDBYTE;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.ucValue;
}

long Param::GetLong()
{
	if (m_Type == XSD_LONG){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_LONG;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.lValue;
}

long Param::GetInteger()
{
	if (m_Type == XSD_INTEGER){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_INTEGER;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.lValue;
}

unsigned long Param::GetUnsignedLong()
{
	if (m_Type == XSD_UNSIGNEDLONG){}
	else if (m_Type == XSD_UNKNOWN)
	{
		//this situation comes when the soap does not contain the type of a parameter
		//but the wrapper class method knows exactly what the type of this parameter is.
		//then the deserializer must have put the value as a string and type as XSD_UNKNOWN.
		//so convert the m_sValue in to an int and change the types etc
		m_Type = XSD_UNSIGNEDLONG;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.ulValue;
}

float Param::GetFloat()
{
	if (m_Type == XSD_FLOAT){}
	else if (m_Type == XSD_UNKNOWN)
	{
		m_Type = XSD_FLOAT;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.fValue;
}

double Param::GetDouble()
{
	if (m_Type == XSD_DOUBLE){}
	else if (m_Type == XSD_UNKNOWN)
	{
		m_Type = XSD_DOUBLE;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.dValue;
}

double Param::GetDecimal()
{
	if (m_Type == XSD_DECIMAL){}
	else if (m_Type == XSD_UNKNOWN)
	{
		m_Type = XSD_DECIMAL;
		SetValue(m_sValue.c_str());
	}
	else
	{
		//exception
	}
	return m_Value.dValue;
}

XSDTYPE Param::GetType() const
{
	return m_Type;
}

int Param::serialize(IWrapperSoapSerializer& pSZ)
{
	AxisString ATprefix;
	switch (m_Type){
	case XSD_INT:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.nValue);
		break; 
    case XSD_UNSIGNEDINT:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.unValue);
		break;           
    case XSD_SHORT:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.sValue);
		break; 
    case XSD_UNSIGNEDSHORT:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.usValue);
		break;         
    case XSD_BYTE:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.cValue);
		break; 
    case XSD_UNSIGNEDBYTE:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.ucValue);
		break;
    case XSD_LONG:
    case XSD_INTEGER:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.lValue);
		break;        
    case XSD_UNSIGNEDLONG:
        pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.ulValue);

		break;
	case XSD_FLOAT:
		pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.fValue);
		break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
		pSZ << m_BTSZ.serialize(m_sName.c_str(), m_Value.dValue);
		break;              
	case XSD_STRING:
		pSZ << m_BTSZ.serialize(m_sName.c_str(), m_sValue.c_str());
		break;
	case XSD_HEXBINARY:
		pSZ << m_BTSZ.serialize(m_sName.c_str(), m_sValue.c_str(), XSD_HEXBINARY);
		break;
	case XSD_BASE64BINARY:
		pSZ << m_BTSZ.serialize(m_sName.c_str(), m_sValue.c_str(), XSD_BASE64BINARY);
		break;
	case XSD_DURATION:
        pSZ << m_uAxisTime.serialize(m_sName, m_Value.lDuration).c_str();
        break;
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
            pSZ << m_uAxisTime.serialize(m_sName, m_Value.tValue).c_str();            
        break;        
	case XSD_ARRAY:
		//pSZ << "<abc:ArrayOfPhoneNumbers xmlns:abc="http://example.org/2001/06/numbers"
		//				xmlns:enc="http://www.w3.org/2001/06/soap-encoding" 
        //              enc:arrayType="abc:phoneNumberType[2]" >";
		if (!m_Value.pArray) return FAIL; //error condition
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
		pSZ << "=\"http://www.w3.org/2001/06/soap-encoding\" ";
		if (m_Value.pArray->m_type == USER_TYPE)
		{
			pSZ << "xmlns:" << ATprefix.c_str() << "=" << m_Value.pArray->m_URI.c_str() << " "; 
		}
		pSZ << "enc:arrayType=";
		if (m_Value.pArray->m_type == USER_TYPE)
		{
			pSZ << ATprefix.c_str() << ":" << m_Value.pArray->m_TypeName.c_str(); 
		}
		else //basic type array
		{
			pSZ << "xsd:";
			pSZ << m_BTSZ.BasicTypeStr(m_Value.pArray->m_type);
		}
		{
			char Buf[10]; //maximum array dimension is 99999999
			for (list<int>::iterator it=m_Value.pArray->m_size.begin(); it!=m_Value.pArray->m_size.end(); it++)
			{
				sprintf(Buf,"[%d]", *it);
				pSZ << Buf;
			}
		}
		pSZ << ">";
		m_Value.pArray->Serialize(pSZ); //Only serializes the inner items
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
		m_Value.pCplxObj->pSZFunct(m_Value.pCplxObj->pObject, pSZ);
		break;
	default:;
	}
	return SUCCESS;
}

////////////////////////////////////////////////////////////////////////
//This method is used by the deserializer to set the value after setting the type.
//Also this method assumes that the type is already set and it is a basic type.
int Param::SetValue(const AxisChar* sValue)
{
	AxisChar* endptr;
	m_sValue = sValue; //Whatever the type we put the string representation of the value
	switch (m_Type)
	{
	case XSD_INT:
        m_Value.nValue = strtol(sValue, &endptr, 10);
		break;
    case XSD_UNSIGNEDINT:
        m_Value.nValue = strtoul(sValue, &endptr, 10);
		break;
    case XSD_SHORT:
        m_Value.sValue = strtol(sValue, &endptr, 10);
		break;
    case XSD_UNSIGNEDSHORT:
        m_Value.usValue = strtoul(sValue, &endptr, 10);
		break;
    case XSD_BYTE:
        m_Value.cValue = strtol(sValue, &endptr, 10);
		break;
    case XSD_UNSIGNEDBYTE:
		m_Value.ucValue = strtoul(sValue, &endptr, 10);
		break;              
    case XSD_LONG:
    case XSD_INTEGER:
        m_Value.lValue = strtol(sValue, &endptr, 10);
		break;                
    case XSD_UNSIGNEDLONG:
		m_Value.ulValue = strtoul(sValue, &endptr, 10);
		break;        
	case XSD_FLOAT:
		m_Value.fValue = strtod(sValue, &endptr);
		break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
		m_Value.dValue = strtod(sValue, &endptr);
		break;        
	case XSD_STRING:
	case XSD_HEXBINARY:
	case XSD_BASE64BINARY:
		m_sValue = sValue;
		break;
    case XSD_DURATION:
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
		m_uAxisTime.setValue(sValue);
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

int Param::SetValue(XSDTYPE nType, uParamValue Value)
{
	m_Type = nType;
	switch (m_Type)
	{
	case XSD_INT:
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
	case XSD_HEXBINARY:
	case XSD_BASE64BINARY:
		m_sValue = Value.pStrValue;
		break;
  case XSD_DURATION:
        m_Value.lDuration = Value.lDuration;
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
        m_Value.tValue = Value.tValue;
        m_uAxisTime.setValue(nType, m_Value);
	//Continue this for all basic types
	case XSD_ARRAY:
		m_Value.pArray = Value.pArray;
		break;
	case USER_TYPE:
		m_Value.pCplxObj = Value.pCplxObj;
		break;
	default:
		return FAIL; //this is an unexpected situation
	}
	return SUCCESS;
}

void Param::setPrefix(const AxisChar* prefix)
{
	m_strPrefix = prefix;
}

void Param::setUri(const AxisChar* uri)
{
	m_strUri = uri;
}

void Param::operator=(const Param &param)
{
	m_sName = param.m_sName;
	m_sValue = param.m_sValue;
	m_Type = param.m_Type;	
	if (m_Type == USER_TYPE) 
	{
		m_Value.pCplxObj = param.m_Value.pCplxObj;
	}
	else if(m_Type == XSD_ARRAY)
	{
		m_Value.pArray = param.m_Value.pArray;
	}	
	else 
	{
		m_Value = param.m_Value;
	}
}

int Param::GetArraySize()
{
	if (m_Type != XSD_ARRAY) return 0;
	return m_Value.pArray->GetArraySize();
}

/*
int Param::SetUserType(IAccessBean* pObject)
{
	if (m_Type != USER_TYPE) return FAIL;
	m_Value.pIBean = pObject;
	return SUCCESS;
}
*/

int Param::SetUserType(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct)
{
	if (m_Type != USER_TYPE) return FAIL;
	m_Value.pCplxObj = new ComplexObjectHandler;
	m_Value.pCplxObj->pObject = pObject;
	m_Value.pCplxObj->pDZFunct = pDZFunct;
	m_Value.pCplxObj->pDelFunct = pDelFunct;
	return SUCCESS;
}

int Param::SetArrayElements(void* pElements)
{
	if (m_Type != XSD_ARRAY) return FAIL;
	if (m_Value.pArray)
	{
		if (m_Value.pArray->m_type != USER_TYPE)
		{
			m_Value.pArray->m_value.sta = pElements;
			return SUCCESS;
		}
		else //unexpected situation
		{
			return FAIL;
		}
	}
	return FAIL;
}

//following function is called to set array of user types.
int Param::SetArrayElements(void* pObject, AXIS_DESERIALIZE_FUNCT pDZFunct, AXIS_OBJECT_DELETE_FUNCT pDelFunct, AXIS_OBJECT_SIZE_FUNCT pSizeFunct)
{
	if (m_Type != XSD_ARRAY) return FAIL;
	if (m_Value.pArray)
	{
		if (m_Value.pArray->m_type == USER_TYPE)
		{
			m_Value.pArray->m_value.cta = new ComplexObjectHandler;
			m_Value.pArray->m_value.cta->pDZFunct = pDZFunct;
			m_Value.pArray->m_value.cta->pDelFunct = pDelFunct;
			m_Value.pArray->m_value.cta->pSizeFunct = pSizeFunct;
			m_Value.pArray->m_value.cta->pObject = pObject;
			return SUCCESS;
		}
		else //unexpected situation
		{
			return FAIL;
		}
	}
	return FAIL;	
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
	if (pObject && pDelFunct) pDelFunct(pObject);
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
