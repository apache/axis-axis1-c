#include "Duration.hpp"

AXIS_CPP_NAMESPACE_START

    Duration::Duration():m_Duration(NULL)
    {
    }

    AxisChar* Duration::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((long*) value);
    }
	
    void* Duration::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeDuration(valueAsChar);
    }
	
    AxisChar* Duration::serialize(const long* value) throw (AxisSoapException)
    {
     
        MinInclusive* minInclusive = getMinInclusive();
        if (minInclusive->isSet())
        {
            if ( *value < minInclusive->getMinInclusiveAsLONGLONG() )
            {
                AxisString exceptionMessage =
                "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
                AxisChar* length = new AxisChar[25];
                sprintf(length, "%d", minInclusive->getMinInclusiveAsLONGLONG());
                exceptionMessage += length;
                exceptionMessage += ", Value = ";
                sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
                exceptionMessage += length;
                exceptionMessage += ".";
                delete [] length;
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete minInclusive;
     
        MinExclusive* minExclusive = getMinExclusive();
        if (minExclusive->isSet())
        {
            if ( *value < minExclusive->getMinExclusiveAsLONGLONG() )
            {
                AxisString exceptionMessage =
                "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
                AxisChar* length = new AxisChar[25];
                sprintf(length, "%d", minExclusive->getMinExclusiveAsLONGLONG());
                exceptionMessage += length;
                exceptionMessage += ", Value = ";
                sprintf(length, PRINTF_LONGLONG_FORMAT_SPECIFIER, *value);
                exceptionMessage += length;
                exceptionMessage += ".";
                delete [] length;
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete minExclusive;
     
    	long valueToSerialize = *value;
    	AxisChar buff[4];
	    AxisString serializedValue;
    	/*
    	 * Duration takes the form:
    	 * PnYnMnDTnHnMnS
    	 */
	    serializedValue = "P";
	    
	    // Calculate years
	    int x = 365 * 24 * 3600;
	    int intYears = valueToSerialize / x;
	    long tempYears = intYears * x;
	    AxisSprintf (buff, 4, "%d", intYears);
	    serializedValue.append (buff);
	    serializedValue.append ("Y");


		// Calculate Months
	    valueToSerialize = valueToSerialize - (tempYears);
	    x = 30 * 24 * 3600;
	    int intMonths = valueToSerialize / x;
	    AxisSprintf (buff, 4, "%d", intMonths);
	    serializedValue.append (buff);
	    serializedValue.append ("M");

		// Calculate Days
	    valueToSerialize = valueToSerialize - (intMonths * x);
	    x = 24 * 3600;
	    int intDays = valueToSerialize / x;
	    AxisSprintf (buff, 4, "%d", intDays);
	    serializedValue.append (buff);
	    serializedValue.append ("DT");

		// Calculate Hours
	    valueToSerialize = valueToSerialize - (intDays * x);
	    x = 3600;
	    int intHours = valueToSerialize / x;
	    AxisSprintf (buff, 4, "%d", intHours);
	    serializedValue.append (buff);
	    serializedValue.append ("H");

		// Calculate Minutes
	    valueToSerialize = valueToSerialize - (intHours * x);
	    x = 60;
	    int intMins = valueToSerialize / x;
	    AxisSprintf (buff, 4, "%d", intMins);
	    serializedValue.append (buff);
	    serializedValue.append ("M");

		// Calculate Seconds
	    int intSecs = valueToSerialize - (intMins * x);
	    AxisSprintf (buff, 4, "%d", intSecs);
	    serializedValue.append (buff);
	    serializedValue.append ("S");

		// Convert from String to Char[]	
		AxisChar* returnValue = (AxisChar*) serializedValue.c_str ();
       
        IAnySimpleType::serialize(returnValue);
		return m_Buf;
    }
	
    long* Duration::deserializeDuration(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	AxisString valueAsString = valueAsChar;
    	AxisString buff;
	    unsigned int intPos1, intPos2, intPos3, intPos4, intPos5, intPos6;

        if (m_Duration)
        {
            delete m_Duration;
            m_Duration = NULL;
        }
	
	    /*XSD_DURATION is of the format PnYnMnDTnHnMnS */

		// Deserialize Years
		*m_Duration = 0;
	    intPos1 = valueAsString.find_first_of ("Y");
	    buff = valueAsString.substr (1, intPos1 - 1);
	    int years = atoi (buff.c_str ());
	    *m_Duration += years * 365 * 24 * 3600;

		// Deserialize Months
	    intPos2 = valueAsString.find_first_of ("M");
	    buff = valueAsString.substr (intPos1 + 1, intPos2 - intPos1 - 1);
	    int months = atoi (buff.c_str ());
	    *m_Duration = months * 30 * 24 * 3600;

		// Deserialize Days
	    intPos3 = valueAsString.find_first_of ("D");
	    buff = valueAsString.substr (intPos2 + 1, intPos3 - intPos2 - 1);
	    int days = atoi (buff.c_str ());
	    *m_Duration = days * 24 * 3600;

		// Deserialize Hours
	    intPos4 = valueAsString.find_first_of ("H");
	    buff = valueAsString.substr (intPos3 + 2, intPos4 - intPos3 - 2);
	    int hours = atoi (buff.c_str ());
	    *m_Duration = hours * 3600;

		// Deserialize Minutes
	    intPos5 = valueAsString.find_first_of ("M");
	    buff = valueAsString.substr (intPos4 + 1, intPos5 - intPos4 - 1);
	    int mins = atoi (buff.c_str ());
	    *m_Duration += mins * 60;

		// Deserialize Seconds
	    intPos6 = valueAsString.find_first_of ("S");
	    buff = valueAsString.substr (intPos5 + 1, intPos6 - intPos5 - 1);
	    int secs = atoi (buff.c_str ());
	    *m_Duration += secs;
	    
	    return m_Duration;
    }

    WhiteSpace* Duration::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }

    MinInclusive* Duration::getMinInclusive()
    {
        return new MinInclusive();
    }

    MinExclusive* Duration::getMinExclusive()
    {
        return new MinExclusive();
    }
    
AXIS_CPP_NAMESPACE_END
