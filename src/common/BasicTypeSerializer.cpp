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

// BasicTypeSerializer.cpp: implementation of the BasicTypeSerializer class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "BasicTypeSerializer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BasicTypeSerializer::BasicTypeSerializer()
{
	m_sSZ = "";
	m_AuxStr = "";
}

BasicTypeSerializer::~BasicTypeSerializer()
{

}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, int nValue)
{
	m_Type = XSD_INT;
	AxisSprintf(m_Buf, 32, "%d", nValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, unsigned int unValue)
{
	m_Type = XSD_UNSIGNEDINT;
	AxisSprintf(m_Buf, 32, "%d", unValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, char cValue)
{
	m_Type = XSD_BYTE;
	AxisSprintf(m_Buf, 32, "%c", cValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, unsigned char ucValue)
{
	m_Type = XSD_UNSIGNEDBYTE;
	AxisSprintf(m_Buf, 32, "%c", ucValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, short sValue)
{
	m_Type = XSD_SHORT;
	AxisSprintf(m_Buf, 32, "%d", sValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, unsigned short usValue)
{
	m_Type = XSD_UNSIGNEDSHORT;
	AxisSprintf(m_Buf, 32, "%d", usValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, long lValue, XSDTYPE type)
{
	m_Type = type;
	AxisSprintf(m_Buf, 32, "%d", lValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, unsigned long ulValue)
{
	m_Type = XSD_UNSIGNEDLONG;
	AxisSprintf(m_Buf, 32, "%d", ulValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, float fValue)
{
	m_Type = XSD_FLOAT;
	AxisSprintf(m_Buf, 32, "%f", fValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, double dValue, XSDTYPE type)
{
	m_Type = type;
	AxisSprintf(m_Buf, 32, "%f", dValue);
	HelpSerialize(sName, sName);
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::serialize(const AxisChar* sName, const AxisChar* sValue, XSDTYPE type)

{
	m_Type = type;
	HelpSerialize(sName, sValue);
	return m_sSZ.c_str();
}

void BasicTypeSerializer::HelpSerialize(const AxisChar* sName, const AxisChar* sValue)
{
	m_sSZ = "<";
	m_sSZ += sName;
	m_sSZ += " xsi:type=\"xsd:";
	m_sSZ += BasicTypeStr(m_Type);
	m_sSZ += "\">";
	switch (m_Type)
	{
	case XSD_STRING:
		m_AuxStr = sValue;
		m_sSZ += GetEntityReferenced(m_AuxStr).c_str();	
		break;
          
	default:
		m_sSZ += m_Buf;
	}
	m_sSZ += "</";
	m_sSZ += sName;
	m_sSZ += ">";
}

const AxisChar* BasicTypeSerializer::BasicTypeStr(XSDTYPE type)
{
	switch (type)
	{
	case XSD_INT: return "int";
    case XSD_UNSIGNEDINT: return "unsignedInt";
    case XSD_SHORT: return "short";
    case XSD_UNSIGNEDSHORT: return "unsignedShort";
    case XSD_BYTE: return "byte";
    case XSD_UNSIGNEDBYTE: return "unsignedByte";
    case XSD_LONG: return "long";
    case XSD_INTEGER: return "integer";
    case XSD_UNSIGNEDLONG: return "unsignedLong";
	case XSD_FLOAT: return "float";
    case XSD_DOUBLE: return "double";
    case XSD_DECIMAL: return "decimal";  
	case XSD_STRING: return "string";
	case XSD_HEXBINARY: return "hexBinary";
	case XSD_BASE64BINARY: return "base64Binary";
    case XSD_DURATION: return "duration";
    case XSD_DATETIME: return "dateTime";
    case XSD_TIME: return "time";
    case XSD_DATE: return "date";
    case XSD_YEARMONTH: return "gYearMonth";
    case XSD_YEAR: return "gYear";
    case XSD_MONTHDAY: return "gMonthDay";
    case XSD_DAY: return "gDay";
    case XSD_MONTH: return "gMonth";
    case XSD_ANYURI: return "anyURI";
    case XSD_QNAME: return "QName";
	default: return " ";
	}
}

/// Encode XML entities if any found in user data.
const AxisString& BasicTypeSerializer::GetEntityReferenced(const AxisString& strVal)
{
	if (strVal.empty())
		return strVal;

	// Find entity reference characters and returns the first any of chars find position
    int nPos = strVal.find_first_of(XML_ENTITY_REFERENCE_CAHRS);	

	// Check for position validity
	if (std::AxisString::npos == nPos)
		return strVal;

	int nOldIdx = 0;	// Counter value
	while(std::AxisString::npos != nPos)
	{	// Get pointered character
		switch(strVal.at(nPos))
		{	
			case LESSER_THAN_CHAR  : // Process < character
				m_strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				m_strReturnVal.append(ENCODED_LESSER_STR);
				break;
			case GREATOR_THAN_CHAR  : // Process > character
				m_strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				m_strReturnVal.append(ENCODED_GREATOR_STR);
				break;
			case AMPERSAND_CHAR  : // Process & character
				m_strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				m_strReturnVal.append(ENCODED_AMPERSAND_STR);
				break;
			case DOUBLE_QUOTE_CHAR : // Process " character
				m_strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				m_strReturnVal.append(ENCODED_DBL_QUOTE_STR);
				break;
			case SINGLE_QUOTE_CHAR : // Process ' character
				m_strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				m_strReturnVal.append(ENCODED_SGL_QUOTE_STR);
				break;
		}
		nOldIdx = ++nPos; // Get old position
		// Find the next entity reference characters from previous found position,
		nPos = strVal.find_first_of(XML_ENTITY_REFERENCE_CAHRS, nPos);		
	}	

	int nDataLen = strVal.length();		// Get the length of the field value
	int nLen =  nDataLen - nOldIdx;		// Get remaining number of characters	
	if (nLen > 0)
		m_strReturnVal += strVal.substr(nOldIdx, nLen);// Apend the remaining data		

	return m_strReturnVal;
}
