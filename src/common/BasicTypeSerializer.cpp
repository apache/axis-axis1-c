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

#include "BasicTypeSerializer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
char BasicTypeSerializer::m_Buf[64];
XSDTYPE BasicTypeSerializer::m_Type;
string BasicTypeSerializer::m_sSZ = "";
string BasicTypeSerializer::m_AuxStr = "";

BasicTypeSerializer::BasicTypeSerializer()
{

}

BasicTypeSerializer::~BasicTypeSerializer()
{

}

string& BasicTypeSerializer::serialize(const string &sName, int nValue)
{
	m_Type = XSD_INT;
	sprintf(m_Buf, "%d", nValue);
	HelpSerialize(sName, sName);
	return m_sSZ;
}

string& BasicTypeSerializer::serialize(const string &sName, float fValue)
{
	m_Type = XSD_FLOAT;
	sprintf(m_Buf, "%f", fValue);
	HelpSerialize(sName, sName);
	return m_sSZ;
}

string& BasicTypeSerializer::serialize(const string &sName, string &sValue, XSDTYPE type)
{
	m_Type = type;
	HelpSerialize(sName, sValue);
	return m_sSZ;
}

void BasicTypeSerializer::HelpSerialize(const string &sName, const string &sValue)
{
	m_sSZ = "<";
	m_sSZ += sName.c_str();
	m_sSZ +=" xsi:type=\"xsd:";
	m_sSZ += BasicTypeStr(m_Type);
	m_sSZ += "\">";
	switch (m_Type)
	{
	case XSD_STRING:
		m_sSZ += GetEntityReferenced(sValue);	
		break;
	default:
		m_sSZ += m_Buf;
	}
	m_sSZ += "</";
	m_sSZ += sName.c_str();
	m_sSZ +=">";
}

const char* BasicTypeSerializer::BasicTypeStr(XSDTYPE type)
{
	switch (type)
	{
	case XSD_INT: return "int";
	case XSD_FLOAT: return "float";
	case XSD_STRING: return "string";
	case XSD_HEXBINARY: return "hexBinary";
	case XSD_BASE64BINARY: return "base64Binary";
	default: return " ";
	}
}

/// Encode XML entities if any found in user data.
string BasicTypeSerializer::GetEntityReferenced(const string &strVal)
{
	if (strVal.empty())
		return strVal;

	// Find entity reference characters and returns the first any of chars find position
    int nPos = strVal.find_first_of(XML_ENTITY_REFERENCE_CAHRS);	

	// Check for position validity
	if (std::string::npos == nPos)
		return strVal;

	std::string strReturnVal;

	int nOldIdx = 0;	// Counter value
	while(std::string::npos != nPos)
	{	// Get pointered character
		switch(strVal.at(nPos))
		{	
			case LESSER_THAN_CHAR  : // Process < character
				strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				strReturnVal.append(ENCODED_LESSER_STR);
				break;
			case GREATOR_THAN_CHAR  : // Process > character
				strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				strReturnVal.append(ENCODED_GREATOR_STR);
				break;
			case AMPERSAND_CHAR  : // Process & character
				strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				strReturnVal.append(ENCODED_AMPERSAND_STR);
				break;
			case DOUBLE_QUOTE_CHAR : // Process " character
				strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				strReturnVal.append(ENCODED_DBL_QUOTE_STR);
				break;
			case SINGLE_QUOTE_CHAR : // Process ' character
				strReturnVal.append(strVal.substr(nOldIdx, nPos - nOldIdx));
				strReturnVal.append(ENCODED_SGL_QUOTE_STR);
				break;
		}
		nOldIdx = ++nPos; // Get old position
		// Find the next entity reference characters from previous found position,
		nPos = strVal.find_first_of(XML_ENTITY_REFERENCE_CAHRS, nPos);		
	}	

	int nDataLen = strVal.length();		// Get the length of the field value
	int nLen =  nDataLen - nOldIdx;		// Get remaining number of characters	
	if (nLen > 0)
		strReturnVal += strVal.substr(nOldIdx, nLen);// Apend the remaining data		

	return strReturnVal;
}
