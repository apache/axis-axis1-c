/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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


#include <axis/TypeMapping.hpp>
#include "AxisUtils.h"
#define __TRC(X) AxisUtils::Convert(X)

AXIS_CPP_NAMESPACE_START
using namespace std;

#if (defined(AIX) || defined( __OS400__ ) || (defined(_MSC_VER) && _MSC_VER >= 1300) || defined(__sun))
    std::map < AxisXMLString, XSDTYPE > 
    AXIS_CPP_NAMESPACE_PREFIX TypeMapping::m_sTypeMap;
#else
    std::map < const AxisXMLString, XSDTYPE > 
    AXIS_CPP_NAMESPACE_PREFIX TypeMapping::m_sTypeMap;
#endif
volatile bool TypeMapping::m_bInit = false;

TypeMapping::TypeMapping ()
{

}

TypeMapping::~TypeMapping ()
{

}

void TypeMapping::initialize ()
{
    if (!m_bInit)
    {
        m_sTypeMap[std::string ("int")] = XSD_INT;
        m_sTypeMap[std::string ("boolean")] = XSD_BOOLEAN;
        m_sTypeMap[std::string ("unsignedInt")] = XSD_UNSIGNEDINT;
        m_sTypeMap[std::string ("short")] = XSD_SHORT;
        m_sTypeMap[std::string ("unsignedShort")] = XSD_UNSIGNEDSHORT;
        m_sTypeMap[std::string ("byte")] = XSD_BYTE;
        m_sTypeMap[std::string ("unsignedByte")] = XSD_UNSIGNEDBYTE;
        m_sTypeMap[std::string ("long")] = XSD_LONG;
        m_sTypeMap[std::string ("integer")] = XSD_INTEGER;
        m_sTypeMap[std::string ("unsignedLong")] = XSD_UNSIGNEDLONG;
        m_sTypeMap[std::string ("float")] = XSD_FLOAT;
        m_sTypeMap[std::string ("double")] = XSD_DOUBLE;
        m_sTypeMap[std::string ("decimal")] = XSD_DECIMAL;
        m_sTypeMap[std::string ("std::string")] = XSD_STRING;
        m_sTypeMap[std::string ("base64Binary")] = XSD_BASE64BINARY;
        m_sTypeMap[std::string ("hexBinary")] = XSD_HEXBINARY;
        m_sTypeMap[std::string ("anyURI")] = XSD_ANYURI;
        m_sTypeMap[std::string ("QName")] = XSD_QNAME;
        m_sTypeMap[std::string ("duration")] = XSD_DURATION;
        m_sTypeMap[std::string ("dateTime")] = XSD_DATETIME;
        m_sTypeMap[std::string ("date")] = XSD_DATE;
        m_sTypeMap[std::string ("time")] = XSD_TIME;
        m_sTypeMap[std::string ("gYearMonth")] = XSD_YEARMONTH;
        m_sTypeMap[std::string ("gYear")] = XSD_YEAR;
        m_sTypeMap[std::string ("gMonthDay")] = XSD_MONTHDAY;
        m_sTypeMap[std::string ("gDay")] = XSD_DAY;
        m_sTypeMap[std::string ("gMonth")] = XSD_MONTH;
        m_bInit = true;
    }
}

void TypeMapping::uninitialize()
{
    if (m_bInit)
	{
        m_sTypeMap.clear();
		m_bInit = false;
	}
}


XSDTYPE TypeMapping::map (const AxisXMLCh* sType)
{
    if (m_sTypeMap.find (std::string(sType)) != m_sTypeMap.end ())
    {
        return m_sTypeMap[std::string(sType)];
    }
    return XSD_UNKNOWN;
}

AXIS_CPP_NAMESPACE_END
