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


#include <axis/server/TypeMapping.hpp>
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
        m_sTypeMap[__TRC ("int")] = XSD_INT;
        m_sTypeMap[__TRC ("boolean")] = XSD_BOOLEAN;
        m_sTypeMap[__TRC ("unsignedInt")] = XSD_UNSIGNEDINT;
        m_sTypeMap[__TRC ("short")] = XSD_SHORT;
        m_sTypeMap[__TRC ("unsignedShort")] = XSD_UNSIGNEDSHORT;
        m_sTypeMap[__TRC ("byte")] = XSD_BYTE;
        m_sTypeMap[__TRC ("unsignedByte")] = XSD_UNSIGNEDBYTE;
        m_sTypeMap[__TRC ("long")] = XSD_LONG;
        m_sTypeMap[__TRC ("integer")] = XSD_INTEGER;
        m_sTypeMap[__TRC ("unsignedLong")] = XSD_UNSIGNEDLONG;
        m_sTypeMap[__TRC ("float")] = XSD_FLOAT;
        m_sTypeMap[__TRC ("double")] = XSD_DOUBLE;
        m_sTypeMap[__TRC ("decimal")] = XSD_DECIMAL;
        m_sTypeMap[__TRC ("string")] = XSD_STRING;
        m_sTypeMap[__TRC ("base64Binary")] = XSD_BASE64BINARY;
        m_sTypeMap[__TRC ("hexBinary")] = XSD_HEXBINARY;
        m_sTypeMap[__TRC ("anyURI")] = XSD_ANYURI;
        m_sTypeMap[__TRC ("QName")] = XSD_QNAME;
        m_sTypeMap[__TRC ("duration")] = XSD_DURATION;
        m_sTypeMap[__TRC ("dateTime")] = XSD_DATETIME;
        m_sTypeMap[__TRC ("date")] = XSD_DATE;
        m_sTypeMap[__TRC ("time")] = XSD_TIME;
        m_sTypeMap[__TRC ("gYearMonth")] = XSD_YEARMONTH;
        m_sTypeMap[__TRC ("gYear")] = XSD_YEAR;
        m_sTypeMap[__TRC ("gMonthDay")] = XSD_MONTHDAY;
        m_sTypeMap[__TRC ("gDay")] = XSD_DAY;
        m_sTypeMap[__TRC ("gMonth")] = XSD_MONTH;
        m_bInit = true;
    }
}

XSDTYPE TypeMapping::map (const AxisXMLCh* sType)
{
    if (m_sTypeMap.find (sType) != m_sTypeMap.end ())
    {
        return m_sTypeMap[sType];
    }
    return XSD_UNKNOWN;
}

AXIS_CPP_NAMESPACE_END
