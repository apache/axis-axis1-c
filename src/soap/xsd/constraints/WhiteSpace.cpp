#include "WhiteSpace.hpp"

AXIS_CPP_NAMESPACE_START

    WhiteSpace::WhiteSpace():m_WhiteSpace(PRESERVE), m_Buf(NULL)
    {
        m_isSet = true;
    }

    WhiteSpace::~WhiteSpace()
    {
        delete [] m_Buf;
    }

    WhiteSpace::WhiteSpace(whiteSpaceValue whiteSpace):m_Buf(NULL)
    {
        m_isSet = true;
        m_WhiteSpace = whiteSpace;
    }
    
    const AxisChar* WhiteSpace::processWhiteSpace(const AxisChar* valueToProcess)
    {
        AxisString valueAsString = valueToProcess;
        AxisChar* returnValue = NULL;
     
        switch (m_WhiteSpace)
        {
            case PRESERVE:
                return valueToProcess;
            case REPLACE:
                {
                    returnValue = (AxisChar*) replaceWhiteSpace(valueAsString).c_str();
                }
                break;
            case COLLAPSE:
                {
                    returnValue = (AxisChar*) collapseWhiteSpace(valueAsString).c_str();               
                }
                break;
        }
        
        if (m_Buf)
        {
            delete [] m_Buf;
            m_Buf = NULL;
        }
        m_Buf = new char[strlen (returnValue) + 1];
        strcpy (m_Buf, returnValue);
        return m_Buf;
    }
    
    /**
     * Replaces all occurances of tab, line feed and carriage return with space
     * 
     * @param value The string to have white space characters replaced.
     * @return AxisString The string with all white space characters replaced.
     */
    const AxisString& WhiteSpace::replaceWhiteSpace(AxisString& value)
    {     
        m_strReturnVal = "";

        if (value.empty ())
        {
            return value;
        }

        /* Find white space characters and returns the first any of chars find
         * position
         */ 
        unsigned int nPos = value.find_first_of (WHITE_SPACE_CHARS);
    
        /* Check for position validity */
        if (AxisString::npos == nPos)
        {
            return value;
        }
    
        int nOldIdx = 0;            // Counter value
        while (AxisString::npos != nPos)
        {                         // Get pointered character
            m_strReturnVal.append (value.substr (nOldIdx, nPos - nOldIdx));
            m_strReturnVal.append (" ");

            nOldIdx = ++nPos;     // Get old position

            /* 
             * Find the next white space characters from previous found 
             * position,
             */ 
            nPos = value.find_first_of (WHITE_SPACE_CHARS, nPos);
        }
    
        int nDataLen = value.length ();    // Get the length of the field value
        int nLen = nDataLen - nOldIdx;      // Get remaining number of characters   
        if (nLen > 0)
        {
            /*
             * Append the remaining data
             */
            m_strReturnVal += value.substr (nOldIdx, nLen); 
        }

        return m_strReturnVal;
     
    }


    /**
     * Collapses all white space in a string.
     * All occurances of tab, line feed and carriage return are replaced with
     * space, after which all sequences of spaces are collapsed to a single space.
     * 
     * @param value The string to have all white space collapsed
     * @return AxisString The string with all white space collapsed.
     */
    const AxisString& WhiteSpace::collapseWhiteSpace(AxisString& value)
    {
        m_strReturnVal = "";

        if (value.empty ())
        {
            return value;
        }

        AxisString replacedValue = replaceWhiteSpace(value);

        /*
         * Strip leading and trailing space
         */
        AxisString leadingStripped = stripLeadingWhiteSpace(replacedValue);
        replacedValue = stripTrailingWhiteSpace(leadingStripped);

        /*
         * Find space character and returns the first any of chars find
         * position
         */ 
        unsigned int nPos = replacedValue.find_first_of (' ');
    
        /* Check for position validity */
        if (AxisString::npos == nPos)
        {
            m_strReturnVal.assign (replacedValue);
            return m_strReturnVal;
        }
    
        int nOldIdx = 0;            // Counter value
        while (AxisString::npos != nPos)
        {
            m_strReturnVal.append (replacedValue.substr (nOldIdx, nPos - nOldIdx));

            /**
             * Only copy space character across if it's NOT followed by             
             * another space character
             */
            if ( replacedValue.at(nPos+1) != ' ')
            {
               m_strReturnVal.append (" ");
            }

            nOldIdx = ++nPos;     // Get old position

            /* 
             * Find the next entity reference characters from previous found 
             * position,
             */ 
            nPos = replacedValue.find_first_of (' ', nPos);
        }
    
        int nDataLen = replacedValue.length ();    // Get the length of the field value
        int nLen = nDataLen - nOldIdx;      // Get remaining number of characters   
        if (nLen > 0)
        {
            /*
             * Append the remaining data
             */
            m_strReturnVal += replacedValue.substr (nOldIdx, nLen); 
        }

        return m_strReturnVal;
    }
    
    const AxisString& WhiteSpace::stripLeadingWhiteSpace(AxisString& value)
    {
        while (value.size() > 0)
        {
            if ( isspace (value.at(0)))
            {
                value.erase(0, 1);
            }
            else
            {
                break;
            }
        }

		return value;
    }

	const AxisString& WhiteSpace::stripTrailingWhiteSpace(AxisString& value)
	{
		while (value.size() > 0)
		{
            if ( isspace (value.at( value.size() - 1)))
            {
                value.erase(value.size() - 1, 1);
            }
            else
            {
                break;
            }
		}
        return value;
	}

AXIS_CPP_NAMESPACE_END
