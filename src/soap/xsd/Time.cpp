#include "Time.hpp"

AXIS_CPP_NAMESPACE_START

    Time::Time():m_Time(NULL)
    {
    }

    AxisChar* Time::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((struct tm*) value);
    }
	
    void* Time::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeTime(valueAsChar);
    }
	
    AxisChar* Time::serialize(const struct tm* value) throw (AxisSoapException)
    {
        MinInclusive* minInclusive = getMinInclusive();
        if (minInclusive->isSet())
        {
            struct tm minInclusiveAsStructTM = minInclusive->getMinInclusiveAsStructTM();
            if ( 0 > difftime(mktime(&minInclusiveAsStructTM), mktime(const_cast<struct tm*>(value))) )
            {
                AxisString exceptionMessage =
                "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
                exceptionMessage += asctime(&minInclusiveAsStructTM);
                exceptionMessage += ", Value = ";
                exceptionMessage += asctime(value);
                exceptionMessage += ".";
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete minInclusive;

        MinExclusive* minExclusive = getMinExclusive();
        if (minExclusive->isSet())
        {
            struct tm minExclusiveAsStructTM = minExclusive->getMinExclusiveAsStructTM();
            if ( 0 >= difftime(mktime(&minExclusiveAsStructTM), mktime(const_cast<struct tm*>(value))) )
            {
                AxisString exceptionMessage =
                "Value to be serialized is less than or equal to MinExclusive specified for this type.  MinExclusive = ";
                exceptionMessage += asctime(&minExclusiveAsStructTM);
                exceptionMessage += ", Value = ";
                exceptionMessage += asctime(value);
                exceptionMessage += ".";
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete minExclusive;

        MaxInclusive* maxInclusive = getMaxInclusive();
        if (maxInclusive->isSet())
        {
            struct tm maxInclusiveAsStructTM = maxInclusive->getMaxInclusiveAsStructTM();
            if ( 0 < difftime(mktime(&maxInclusiveAsStructTM), mktime(const_cast<struct tm*>(value))) )
            {
                AxisString exceptionMessage =
                "Value to be serialized is greater than MaxInclusive specified for this type.  MaxInclusive = ";
                exceptionMessage += asctime(&maxInclusiveAsStructTM);
                exceptionMessage += ", Value = ";
                exceptionMessage += asctime(value);
                exceptionMessage += ".";
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete maxInclusive;

        MaxExclusive* maxExclusive = getMaxExclusive();
        if (maxExclusive->isSet())
        {
            struct tm maxExclusiveAsStructTM = maxExclusive->getMaxExclusiveAsStructTM();
            if ( 0 <= difftime(mktime(&maxExclusiveAsStructTM), mktime(const_cast<struct tm*>(value))) )
            {
                AxisString exceptionMessage =
                "Value to be serialized is greater than or equal to MaxExclusive specified for this type.  MaxExclusive = ";
                exceptionMessage += asctime(&maxExclusiveAsStructTM);
                exceptionMessage += ", Value = ";
                exceptionMessage += asctime(value);
                exceptionMessage += ".";
                
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete maxExclusive;
     
        AxisString serializedValue = "";
        AxisChar* valueAsString = new AxisChar[80];
        strftime (valueAsString, 80, "%H:%M:%S", value);
        serializedValue += valueAsString;
        delete [] valueAsString;

        // Calculate local timezone offset
        time_t now = 0;
        struct tm *temp = gmtime(&now);
        struct tm utcTime;
        memcpy(&utcTime, temp, sizeof(struct tm));
        temp = localtime(&now);
        struct tm localTime;
        memcpy(&localTime, temp, sizeof(struct tm));

        long utcTimeInMinutes = (utcTime.tm_year * 60 * 24 * 365)
            + (utcTime.tm_yday * 60 * 24)
            + (utcTime.tm_hour * 60)
            + utcTime.tm_min;

        long localTimeInMinutes = (localTime.tm_year * 60 * 24 * 365)
            + (localTime.tm_yday * 60 * 24)
            + (localTime.tm_hour * 60)
            + localTime.tm_min;

        int timeOffsetInMinutes = localTimeInMinutes - utcTimeInMinutes;

        if (timeOffsetInMinutes == 0)
        {
            serializedValue += "Z";
        }
        else
        {
            struct tm timeOffset;
            timeOffset.tm_year = 0;
            timeOffset.tm_yday = 0;
            timeOffset.tm_sec = 0;
            timeOffset.tm_min = timeOffsetInMinutes % 60;
            timeOffsetInMinutes -= timeOffset.tm_min;
            timeOffset.tm_hour = (timeOffsetInMinutes % (60 * 24)) / 60;
            
            if ( (timeOffset.tm_hour < 0) || (timeOffset.tm_min < 0) )
            {
                serializedValue += "-";
                timeOffset.tm_hour *= -1;
                timeOffset.tm_min *= -1;
            }
            else
            {
                serializedValue += "+";
            }
            
            AxisChar * offSetString = new AxisChar[6];
            sprintf(offSetString, "%02i:%02i", timeOffset.tm_hour, timeOffset.tm_min);
            serializedValue += offSetString;
            delete [] offSetString;
        }

        
        IAnySimpleType::serialize(serializedValue.c_str());
        return m_Buf;
    }
	
    struct tm* Time::deserializeTime(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	struct tm value;
    	struct tm* pTm;
    	AxisChar *cUtc;
	    AxisChar *cTemp;
	    AxisChar *cTemp2;
	    AxisChar *cTemp3;

        // Calculate local timezone offset
        time_t now = 0;
        struct tm *temp = gmtime(&now);
        struct tm utcTime;
        memcpy(&utcTime, temp, sizeof(struct tm));
        temp = localtime(&now);
        struct tm localTime;
        memcpy(&localTime, temp, sizeof(struct tm));

        long utcTimeInSeconds = (utcTime.tm_year * 60 * 60 * 24 * 365)
            + (utcTime.tm_yday * 60 * 60 * 24)
            + (utcTime.tm_hour * 60 * 60)
            + (utcTime.tm_min * 60);

        long localTimeInSeconds = (localTime.tm_year * 60 * 60 * 24 * 365)
            + (localTime.tm_yday * 60 * 60 * 24)
            + (localTime.tm_hour * 60 * 60)
            + (localTime.tm_min * 60);

        time_t d = utcTimeInSeconds - localTimeInSeconds;
    	
        /* dismantle valueAsChar to get tm value;
         * XSD_TIME format is
         * hh:mm:ss.ss...Z OR
         * hh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>
         */
        if (sscanf (valueAsChar, "%d:%d:%d", &value.tm_hour, 
            &value.tm_min, &value.tm_sec) != 3)
        {
        AxisString exceptionMessage =
        "Unable to decompose from string form of DateTime value.  Value =";
        exceptionMessage += valueAsChar;
        exceptionMessage += ".";
        
        throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
            const_cast<AxisChar*>(exceptionMessage.c_str()));
        }

        value.tm_year = 70;
        value.tm_mon = 0;
        value.tm_mday = 1;     /* Day of month (1 - 31) */
        value.tm_isdst = -1;
#if !defined(WIN32) && !defined(AIX) && !defined( __OS400__ ) && !defined(__sun)
        value.tm_zone = NULL;
        value.tm_gmtoff = -1;
#endif
        cTemp2 = (char*) valueAsChar;
        cTemp3 = strrchr (cTemp2, ':');
        cTemp3[0] = '\0';
        unsigned int len = strlen (cTemp2);
        cTemp3[0] = ':';

        /* if the timezone is represented adding 'Z' at the end */
        if ((cTemp = const_cast<char*>(strpbrk (valueAsChar, "Z"))) != NULL)
        {
            time_t temp = mktime (&value); // convert tm object to seconds
            if (temp == -1)
            {
            	throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            pTm = localtime (&temp); // construct tm object from seconds
            memcpy (&value, pTm, sizeof (tm));
            time_t t = mktime (&value);
            if (t == -1)
            {
              throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            t = labs (t - d);
            pTm = localtime (&t);
        }
        /* if the timezone is represented using +/-hh:mm format */
        else if (len > (sizeof (char) * 6))
        {
            cUtc = strpbrk (cTemp2, "+");
            if (cUtc == NULL)
            {
                cUtc = strpbrk (cTemp2, "-");
            }
            time_t timeInSecs = mktime (&value);
            if (timeInSecs == -1)
            {
            	throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            
            int hours = 0;
            int minutes = 0;
            if (sscanf (cUtc + 1, "%d:%d", &hours, &minutes) != 2)
            {
            	throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }

            int secs = hours * 60 * 60 + minutes * 60;
            if ((cTemp = strpbrk ((cUtc), "+")) != NULL)
            {
                timeInSecs += secs;
            }
            else
            {
                timeInSecs -= secs;
            }
            pTm = localtime (&timeInSecs);
            memcpy (&value, pTm, sizeof (tm));
            time_t t = mktime (&value);
            if (t == -1)
            {
            	throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            t = labs (t - d);
            pTm = localtime (&t);
        }
        /* if the zone is not represented in the date */
        else
        {
            /* else it is assumed that the sent time is localtime */
            time_t timeInSecs = mktime (&value);
            if (timeInSecs == -1)
            {
            	throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            pTm = localtime (&timeInSecs);
        }

        if(m_Time)
        {
            delete m_Time;
            m_Time = NULL;
        }
    	
    	m_Time = new struct tm;
		memcpy (m_Time, pTm, sizeof (tm));
    	return m_Time;
    }

    MinInclusive* Time::getMinInclusive()
    {
        return new MinInclusive();
    }

    MinExclusive* Time::getMinExclusive()
    {
        return new MinExclusive();
    }

    MaxInclusive* Time::getMaxInclusive()
    {
        return new MaxInclusive();
    }

    MaxExclusive* Time::getMaxExclusive()
    {
        return new MaxExclusive();
    }

    WhiteSpace* Time::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }

AXIS_CPP_NAMESPACE_END
