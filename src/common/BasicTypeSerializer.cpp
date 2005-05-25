/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 * @author Susantha Kumara (skumara@virtusa.com)
 *
 */


#include <stdio.h>
#include "BasicTypeSerializer.h"
#include "../soap/apr_base64.h"
#include "../soap/HexCoder.h"

AXIS_CPP_NAMESPACE_START

BasicTypeSerializer::BasicTypeSerializer ()
{
    m_sSZ = "";
}

BasicTypeSerializer::~BasicTypeSerializer ()
{

}

const AxisChar* BasicTypeSerializer::serializeAsElement (const AxisChar* pName,
    IAnySimpleType* pSimpleType)
{
	return serializeAsElement(pName, NULL, pSimpleType);
}

const AxisChar* BasicTypeSerializer::serializeAsElement (const AxisChar* pName,
    const AxisChar* pPrefix, IAnySimpleType* pSimpleType)
{
    return serializeAsElement(pName, pPrefix, NULL, pSimpleType);
}

const AxisChar* BasicTypeSerializer::serializeAsElement (const AxisChar* pName,
    const AxisChar* pPrefix, const AxisChar* pNamespace, IAnySimpleType* pSimpleType)
{
    m_sSZ = "<";
	if (NULL != pPrefix) { 
		m_sSZ += pPrefix;
		m_sSZ += ":";
	}
    
    m_sSZ += pName;

    if (NULL != pNamespace)
    {
        m_sSZ += " xmlns:";
        m_sSZ += pPrefix;
        m_sSZ += "=\"";
        m_sSZ += pNamespace;
        m_sSZ += "\"";
    }

    if (RPC_ENCODED == m_nStyle)
    {
        m_sSZ += " xsi:type=\"xsd:";
        m_sSZ += basicTypeStr (pSimpleType->getType());
        m_sSZ += "\"";
    }
    m_sSZ += ">";
    
    if (pSimpleType->isNil())
    {
        /*
         * It is a null value not an empty value.
         */
        m_sSZ = "<";
        if (NULL != pPrefix)
        { 
            m_sSZ += pPrefix;
            m_sSZ += ":";
        }
        m_sSZ += pName;
        
        if (NULL != pNamespace)
        {
            m_sSZ += " xmlns:";
            m_sSZ += pPrefix;
            m_sSZ += "\"";
            m_sSZ += pNamespace;
            m_sSZ += "\"";
        }
        m_sSZ += " xsi:nil=\"true\">";
    }
    else
    {
        m_sSZ += pSimpleType->serialize();
    }
    m_sSZ += "</";
	if (NULL != pPrefix) {
		m_sSZ += pPrefix;
		m_sSZ += ":";
	}
    m_sSZ += pName;
    m_sSZ += ">\n";
    return m_sSZ.c_str ();
}

const AxisChar* BasicTypeSerializer::serializeAsAttribute 
    (const AxisChar* pName, const AxisChar* pPrefix,
    IAnySimpleType* pSimpleType)
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
    
    m_sSZ += pSimpleType->serialize();

    m_sSZ += '"';
    return m_sSZ.c_str ();
}

const AxisChar* BasicTypeSerializer::basicTypeStr (XSDTYPE type)
{
    switch (type)
    {
        case XSD_INT:
            return "int";
        case XSD_BOOLEAN:
            return "boolean";
        case XSD_UNSIGNEDINT:
            return "unsignedInt";
        case XSD_SHORT:
            return "short";
        case XSD_UNSIGNEDSHORT:
            return "unsignedShort";
        case XSD_BYTE:
            return "byte";
        case XSD_UNSIGNEDBYTE:
            return "unsignedByte";
        case XSD_LONG:
            return "long";
        case XSD_INTEGER:
            return "integer";
        case XSD_UNSIGNEDLONG:
            return "unsignedLong";
        case XSD_FLOAT:
            return "float";
        case XSD_DOUBLE:
            return "double";
        case XSD_DECIMAL:
            return "decimal";
        case XSD_STRING:
            return "string";
        case XSD_HEXBINARY:
            return "hexBinary";
        case XSD_BASE64BINARY:
            return "base64Binary";
        case XSD_DURATION:
            return "duration";
        case XSD_DATETIME:
            return "dateTime";
        case XSD_TIME:
            return "time";
        case XSD_DATE:
            return "date";
        case XSD_YEARMONTH:
            return "gYearMonth";
        case XSD_YEAR:
            return "gYear";
        case XSD_MONTHDAY:
            return "gMonthDay";
        case XSD_DAY:
            return "gDay";
        case XSD_MONTH:
            return "gMonth";
        case XSD_ANYURI:
            return "anyURI";
        case XSD_QNAME:
            return "QName";
        default:
            return " ";
    }
}

AXIS_CPP_NAMESPACE_END
