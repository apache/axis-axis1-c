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
// BasicTypeSerializer.h: interface for the BasicTypeSerializer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASICTYPESERIALIZER_H__7ECDFED3_F3D5_48A1_A7EF_1E30B93BDB2C__INCLUDED_)
#define AFX_BASICTYPESERIALIZER_H__7ECDFED3_F3D5_48A1_A7EF_1E30B93BDB2C__INCLUDED_

#include "TypeMapping.h"

#include <string>
using namespace std;

const AxisChar XML_ENTITY_REFERENCE_CAHRS[]	= "<>&\"\'";// Entity reference characters
const AxisChar ENCODED_LESSER_STR[]			= "&lt;";	// Encoded string for less than character
const AxisChar ENCODED_GREATOR_STR[]		= "&gt;";	// Encoded string for greator than character
const AxisChar ENCODED_AMPERSAND_STR[]		= "&amp;";	// Encoded string for ampersand character
const AxisChar ENCODED_DBL_QUOTE_STR[]		= "&quot;";	// Encoded string for single quote character
const AxisChar ENCODED_SGL_QUOTE_STR[]		= "&apos;";	// Encoded string for double quote character

class BasicTypeSerializer
{
public:
	const AxisString& GetEntityReferenced(const AxisString& str);
	const AxisChar* serialize(const AxisChar* sName, const AxisChar* sValue, XSDTYPE type=XSD_STRING);
	const AxisChar* serialize(const AxisChar* sName, float fValue);
    const AxisChar* serialize(const AxisChar* sName, double dValue, XSDTYPE type=XSD_DOUBLE);    
	const AxisChar* serialize(const AxisChar* sName, int nValue);
    const AxisChar* serialize(const AxisChar* sName, unsigned int unValue);
    const AxisChar* serialize(const AxisChar* sName, short sValue);
    const AxisChar* serialize(const AxisChar* sName, unsigned short usValue);
    const AxisChar* serialize(const AxisChar* sName, char cValue);
    const AxisChar* serialize(const AxisChar* sName, unsigned char ucValue);
    const AxisChar* serialize(const AxisChar* sName, long lValue, XSDTYPE type=XSD_LONG);
    const AxisChar* serialize(const AxisChar* sName, unsigned long ulValue);
	const AxisChar* BasicTypeStr(XSDTYPE type);

	BasicTypeSerializer();
	virtual ~BasicTypeSerializer();

private:
	enum
	{
		GREATOR_THAN_CHAR	=	L'>',	// Greator than character
		LESSER_THAN_CHAR	=	L'<',	// Less than character
		SINGLE_QUOTE_CHAR	=	L'\'',	// Single quotation character
		DOUBLE_QUOTE_CHAR	=	L'\"',	// Double quotation character
		AMPERSAND_CHAR		=	L'&'	// Ampersand character
	};
private:
	void HelpSerialize(const AxisChar* sName, const AxisChar* sValue);
	AxisString m_sSZ;
	AxisString m_AuxStr;
	AxisString m_strReturnVal;
	AxisChar m_Buf[32]; //used for numeric to string conversions with sprintf
	XSDTYPE m_Type; //used to temporarily set the type of item being serialized.
};

#endif // !defined(AFX_BASICTYPESERIALIZER_H__7ECDFED3_F3D5_48A1_A7EF_1E30B93BDB2C__INCLUDED_)
