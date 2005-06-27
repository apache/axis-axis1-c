// Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "IAnySimpleType.hpp"

AXIS_CPP_NAMESPACE_START

IAnySimpleType::IAnySimpleType():m_Buf(NULL), m_isNil(true)
{
}

IAnySimpleType::~IAnySimpleType()
{
    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }
}

bool IAnySimpleType::isNil()
{
    return m_isNil;
}

void IAnySimpleType::setNil(bool nil)
{
    m_isNil = nil;
}

AxisChar* IAnySimpleType::serialize()
{
    return m_Buf;
}

void IAnySimpleType::deserialize(const AxisChar* value)
{
    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    }
 
    if (value)
    {
        setNil(false);        
        m_Buf = new char[strlen (value) + 1];
        strcpy (m_Buf, value);
    }
    else
    {
        setNil(true);
    }
}

AxisChar* IAnySimpleType::serialize(const AxisChar* value) throw (AxisSoapException)
{
    WhiteSpace* whiteSpace = getWhiteSpace();
    const AxisChar* serializedValue = whiteSpace->processWhiteSpace(value);

    Pattern* pattern = getPattern();
    if(pattern->isSet())
    {
        pattern->validatePattern(serializedValue);
    }
    delete pattern;

    Enumeration* enumeration = getEnumeration();
    if (enumeration->isSet())
    {
        enumeration->validateEnumeration(serializedValue);
    }
    delete enumeration;

    if (m_Buf)
    {
        delete [] m_Buf;
        m_Buf = NULL;
    } 
    m_Buf = new char[strlen (serializedValue) + 1];
    strcpy (m_Buf, serializedValue);
    delete whiteSpace;
    return m_Buf;
}

const AxisString& IAnySimpleType::replaceReservedCharacters(AxisString &value)
{
    m_strReturnVal = "";
    if (value.empty ())
    {
        return value;
    }

    /* Find entity reference characters and returns the first any of chars find
     * position
     */ 
    unsigned long nPos = value.find_first_of (XML_ENTITY_REFERENCE_CHARS);

    /* Check for position validity */
    if (AxisString::npos == nPos)
    {
        return value;
    }

    unsigned long nOldIdx = 0;            // Counter value
    while (AxisString::npos != nPos)
    {                         // Get pointered character
        switch (value.at (nPos))
        {
            case LESSER_THAN_CHAR:     // Process < character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_LESSER_STR);
                break;
            case GREATER_THAN_CHAR:    // Process > character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_GREATER_STR);
                break;
            case AMPERSAND_CHAR:       // Process & character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_AMPERSAND_STR);
                break;
            case DOUBLE_QUOTE_CHAR:    // Process " character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_DBL_QUOTE_STR);
                break;
            case SINGLE_QUOTE_CHAR:    // Process ' character
                m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
                m_strReturnVal.append (ENCODED_SGL_QUOTE_STR);
                break;
        }
        nOldIdx = ++nPos;     // Get old position
    /* Find the next entity reference characters from previous found 
	 * position,
	 */ 
        nPos = value.find_first_of (XML_ENTITY_REFERENCE_CHARS, nPos);
    }

    unsigned long nDataLen = value.length ();    // Get the length of the field value
    unsigned long nLen = nDataLen - nOldIdx;      // Get remaining number of characters   
    if (nLen > 0)
    {
        m_strReturnVal += value.substr (nOldIdx, nLen); /* Apend the remaining
							  * data
							  */ 
    }
    return m_strReturnVal;
}

WhiteSpace* IAnySimpleType::getWhiteSpace()
{
    return new WhiteSpace(PRESERVE);
}

Pattern* IAnySimpleType::getPattern()
{
    return new Pattern();
}

Enumeration* IAnySimpleType::getEnumeration()
{
    return new Enumeration();
}

AXIS_CPP_NAMESPACE_END
