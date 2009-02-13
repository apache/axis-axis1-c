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

// !!! This include file must be first thing in file !!!
#include "../../platforms/PlatformAutoSense.hpp"

#include "IAnySimpleType.hpp"

#include "../../platforms/PlatformLanguageUtils.hpp"       

const wchar_t XML_ENTITY_REFERENCE_CHARS_WS[] = L"<>&\"\'";

AXIS_CPP_NAMESPACE_START


IAnySimpleType::
IAnySimpleType():m_Buf(NULL), m_isNil(true)
{
}

IAnySimpleType::
~IAnySimpleType()
{
    delete [] m_Buf;
}

bool IAnySimpleType::
isNil()
{
    return m_isNil;
}

void IAnySimpleType::
setNil(bool nil)
{
    m_isNil = nil;
}

AxisChar* IAnySimpleType::
serialize()
{
    return m_Buf;
}

void IAnySimpleType::
deserialize(const AxisChar* value)
{
    delete [] m_Buf;
    m_Buf = NULL;
 
    if (value)
    {
        setNil(false);        
        m_Buf = new char[strlen (value) + 1];
        strcpy (m_Buf, value);
    }
    else
        setNil(true);
}

AxisChar* IAnySimpleType::
serialize(const AxisChar* value) throw (AxisSoapException)
{
    WhiteSpace* whiteSpace = getWhiteSpace();
    const AxisChar* serializedValue = whiteSpace->processWhiteSpace(value);

    Pattern* pattern = getPattern();
    if(pattern->isSet())
        pattern->validatePattern(serializedValue);
    delete pattern;

    Enumeration* enumeration = getEnumeration();
    if (enumeration->isSet())
        enumeration->validateEnumeration(serializedValue);
    delete enumeration;

    delete [] m_Buf;
    m_Buf = NULL;

    m_Buf = new char[strlen (serializedValue) + 1];
    strcpy (m_Buf, serializedValue);
    delete whiteSpace;
    return m_Buf;
}

const AxisString& IAnySimpleType::
replaceReservedCharacters(AxisString &value)
{
	// If empty string or no entity references just return string.
    if (value.empty ())
        return value;

    unsigned long nPos = value.find_first_of (PLATFORM_XML_ENTITY_REFERENCE_CHARS_S);
    if (AxisString::npos == nPos)
        return value;
	
	replaceReservedCharacters(value, m_strReturnVal);
	return m_strReturnVal;
}


void IAnySimpleType::
replaceReservedCharacters(AxisString &inValue, AxisString &outValue)
{
	outValue = "";
	
	// If empty string or no entity references just return string.
    if (inValue.empty ())
        return;

    // Must do character replacement as wide-character since for locales in which a character
    // represents multiple bytes we might inadverently replace a character that really 
    // is not a reserved character.  This is especially true for EBCDIC-based systems. 
    wchar_t *wcs = PlatformLanguageUtils::toWchar(inValue.c_str(), inValue.length()+1);
    wstring inValueW = wcs;
    delete [] wcs;
    
    unsigned long nPos = inValueW.find_first_of (XML_ENTITY_REFERENCE_CHARS_WS);
    if (wstring::npos == nPos)
    {
    	outValue = inValue;
        return;
    }

    // Loop through character string, replacing any entity characters 
    // TODO - can make more efficient, substr everytime is inefficient. 
    unsigned long nOldIdx = 0;  
    wstring outValueW = L"";
    while (wstring::npos != nPos)
    {
    	wchar_t c = inValueW.at (nPos);
    	
    	if (c == L'<')
    	{
            outValueW.append (inValueW.substr (nOldIdx, nPos - nOldIdx));
            outValueW.append (L"&lt;");
    	}
    	else if (c == L'>')
    	{
            outValueW.append (inValueW.substr (nOldIdx, nPos - nOldIdx));
            outValueW.append (L"&gt;");
    	}
    	else if (c == L'&')
    	{
            outValueW.append (inValueW.substr (nOldIdx, nPos - nOldIdx));
            outValueW.append (L"&amp;");
    	}
    	else if (c == L'"')
    	{
            outValueW.append (inValueW.substr (nOldIdx, nPos - nOldIdx));
            outValueW.append (L"&quot;");
    	}
    	else if (c == L'\'')
    	{
            outValueW.append (inValueW.substr (nOldIdx, nPos - nOldIdx));
            outValueW.append (L"&apos;");
        }
        
        // Get old position
        nOldIdx = ++nPos;
    
        // Find the next entity reference characters from previous found position
        nPos = inValueW.find_first_of (XML_ENTITY_REFERENCE_CHARS_WS, nPos);
    }

    // Append the remaining data  
    unsigned long nDataLen = inValueW.length ();    // Get the length of the field value
    unsigned long nLen = nDataLen - nOldIdx;      // Get remaining number of characters   
    if (nLen > 0)
        outValueW += inValueW.substr (nOldIdx, nLen); 
    
    // Now convert data back to character string and return.
    char *temps = PlatformLanguageUtils::toChar((const wchar_t *)outValueW.c_str(), outValueW.length()+1);
    outValue = temps;
    delete [] temps;
    
    return;
}

WhiteSpace* IAnySimpleType::
getWhiteSpace()
{
    return new WhiteSpace(PRESERVE);
}

Pattern* IAnySimpleType::
getPattern()
{
    return new Pattern();
}

Enumeration* IAnySimpleType::
getEnumeration()
{
    return new Enumeration();
}

AXIS_CPP_NAMESPACE_END
