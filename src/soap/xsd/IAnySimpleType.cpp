#include "IAnySimpleType.hpp"

AXIS_CPP_NAMESPACE_START

IAnySimpleType::IAnySimpleType():m_Buf(NULL)
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
    unsigned int nPos = value.find_first_of (XML_ENTITY_REFERENCE_CHARS);

    /* Check for position validity */
    if (AxisString::npos == nPos)
    {
        return value;
    }

    int nOldIdx = 0;            // Counter value
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

    int nDataLen = value.length ();    // Get the length of the field value
    int nLen = nDataLen - nOldIdx;      // Get remaining number of characters   
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
