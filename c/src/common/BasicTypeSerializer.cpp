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
#include <axis/server/BasicTypeSerializer.h>
#include "../soap/apr_base64.h"
#include "../soap/HexCoder.h"

BasicTypeSerializer::BasicTypeSerializer()
{
	m_sSZ = "";
	m_AuxStr = "";
}

BasicTypeSerializer::~BasicTypeSerializer()
{

}

const AxisChar* BasicTypeSerializer::SerializeAsElement(const AxisChar* pName, const void* pValue, XSDTYPE type)
{
	const AxisChar* pStr;
	m_sSZ = "<";
	m_sSZ += pName;
	if (RPC_ENCODED == m_nStyle)
	{
		m_sSZ += " xsi:type=\"xsd:";
		m_sSZ += BasicTypeStr(type);
		m_sSZ += "\"";
	}
	m_sSZ += ">";
	switch(type)
	{
	case XSD_INT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%d", *((int*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_BOOLEAN:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%s", (*((int*)(pValue)) == false_)?"false":"true");
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDINT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%u", *((unsigned int*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_SHORT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%d", *((short*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDSHORT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%u", *((unsigned short*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_BYTE:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%c", *((char*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDBYTE:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%c", *((unsigned char*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_LONG:
    case XSD_INTEGER:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%d", *((long*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_DURATION:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%s", m_AxisTime.serialize(pName, *((long*)(pValue)), type).c_str());
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDLONG:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%u", *((unsigned long*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_FLOAT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%f", *((float*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%f", *((double*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_STRING:
	case XSD_ANYURI:
	case XSD_QNAME:
	case XSD_NOTATION:
		pStr = *((char**)(pValue));
	    if (!pStr) {
       /**
       * It is a null value not an empty value.
       */ 
 	 	    m_sSZ = "<";
	  	    m_sSZ +=  pName;
	  	    m_sSZ += " xsi:nil=\"true\"/>";
  	    	return m_sSZ.c_str();
  		}
		m_AuxStr = pStr;
		m_sSZ += GetEntityReferenced(m_AuxStr).c_str();	
		break;
	case XSD_HEXBINARY:
		m_sSZ += EncodeToHexBinary((xsd__hexBinary*)(pValue));
		break;
	case XSD_BASE64BINARY:
		m_sSZ += EncodeToBase64Binary((xsd__base64Binary*)(pValue));
		break;
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%s", m_AxisTime.serialize(pName, *((struct tm*)(pValue)), type).c_str());
		m_sSZ += m_Buf;
		break;
	default:
		return NULL;
	}

	m_sSZ += "</";
	m_sSZ += pName;
	m_sSZ += ">";
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::EncodeToHexBinary(const xsd__hexBinary* pBinary)
{
	char *outstr = (char*) malloc(pBinary->__size*2+1);
	Hex_Encode(outstr, pBinary->__ptr, pBinary->__size);
	outstr[pBinary->__size*2]=0;
	m_AuxStr = outstr;
	free(outstr);
	return m_AuxStr.c_str();
}

const AxisChar* BasicTypeSerializer::EncodeToBase64Binary(const xsd__base64Binary* pBinary)
{
	int len = apr_base64_encode_len(pBinary->__size);
	char *outstr = (char*) malloc(len+1);
	len = apr_base64_encode_binary(outstr, pBinary->__ptr, pBinary->__size);
	outstr[len]=0;
	m_AuxStr = outstr;
	free(outstr);
	return m_AuxStr.c_str();
}

const AxisChar* BasicTypeSerializer::SerializeAsAttribute(const AxisChar* pName, const AxisChar* pPrefix, const void* pValue, XSDTYPE type)
{
	m_sSZ = ' ';
	if (pPrefix) 
	{
		m_sSZ += pPrefix;
		m_sSZ += ':';
	}
	m_sSZ += pName;
	m_sSZ += '=';
	m_sSZ += '"';
	switch(type)
	{
	case XSD_INT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%d", *((int*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_BOOLEAN:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%s", (*((int*)(pValue)) == 0)?"false":"true");
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDINT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%u", *((unsigned int*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_SHORT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%d", *((short*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDSHORT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%u", *((unsigned short*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_BYTE:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%c", *((char*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDBYTE:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%c", *((unsigned char*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_LONG:
    case XSD_INTEGER:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%d", *((long*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_DURATION:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%s", m_AxisTime.serialize(pName, *((long*)(pValue)), type).c_str());
		m_sSZ += m_Buf;
		break;
    case XSD_UNSIGNEDLONG:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%u", *((unsigned long*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_FLOAT:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%f", *((float*)(pValue)));
		m_sSZ += m_Buf;
		break;
    case XSD_DOUBLE:
    case XSD_DECIMAL:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%f", *((double*)(pValue)));
		m_sSZ += m_Buf;
		break;
	case XSD_STRING:
	case XSD_ANYURI:
	case XSD_QNAME:
	case XSD_NOTATION:			
		m_AuxStr = *((char**)(pValue));
		m_sSZ += GetEntityReferenced(m_AuxStr).c_str();	
		break;
	case XSD_HEXBINARY:
		m_sSZ += EncodeToHexBinary((xsd__hexBinary*)(pValue));
		break;
	case XSD_BASE64BINARY:
		m_sSZ += EncodeToBase64Binary((xsd__base64Binary*)(pValue));
		break;
    case XSD_DATETIME:
    case XSD_DATE:
    case XSD_TIME:
		AxisSprintf(m_Buf, BTS_BUFFSIZE, "%s", m_AxisTime.serialize(pName, *((struct tm*)(pValue)), type).c_str());
		m_sSZ += m_Buf;
		break;
	default:
		return NULL;
	}
	m_sSZ += '"';
	return m_sSZ.c_str();
}

const AxisChar* BasicTypeSerializer::BasicTypeStr(XSDTYPE type)
{
	switch (type)
	{
	case XSD_INT: return "int";
	case XSD_BOOLEAN: return "boolean";
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
	m_strReturnVal = "";
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
