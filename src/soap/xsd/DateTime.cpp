#include "DateTime.hpp"

AXIS_CPP_NAMESPACE_START

    DateTime::DateTime():m_DateTime(NULL)
    {
    }

    DateTime::~DateTime()
    {
        if (m_DateTime)
        {
            delete m_DateTime;
            m_DateTime = NULL;
        }
    }

    AxisChar* DateTime::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((struct tm*) value);
    }
	
    void* DateTime::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeDateTime(valueAsChar);
    }
	
    AxisChar* DateTime::serialize(const struct tm* value) throw (AxisSoapException)
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
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
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
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete maxExclusive;
     
    	AxisChar* serializedValue = new AxisChar[80];
    	strftime (serializedValue, 80, "%Y-%m-%dT%H:%M:%SZ", value);
        
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
		return m_Buf;
    }
	
    struct tm* DateTime::deserializeDateTime(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	struct tm value;
    	struct tm* pTm;
	    AxisChar *cUtc;
	    AxisChar *cTemp;
	    AxisChar *cTemp2;
	    AxisChar *cTemp3;

		time_t now;

		time(&now);

	    pTm = gmtime (&now);

	    struct tm result1;
	    memcpy (&result1, pTm, sizeof (tm));
	    pTm = localtime (&now);

   		struct tm result2;
	    memcpy (&result2, pTm, sizeof (tm));

	    time_t d = mktime (&result1) - mktime (&result2);

	    if (d == -1)
	    {
	    	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
	    }
	
        /* dismantle m_sValue to get tm value;
         * XSD_DATETIME format is
         * CCYY(-)MM(-)DDThh:mm:ss.ss...Z OR
         * CCYY(-)MM(-)DDThh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>
         */
        if (sscanf (valueAsChar, "%d-%d-%dT%d:%d:%d", &value.tm_year,
            &value.tm_mon, &value.tm_mday, &value.tm_hour, &value.tm_min, 
			&value.tm_sec) != 6)
		{
	    	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
		}

        value.tm_year -= 1900;
        value.tm_mon--;
        value.tm_isdst = -1;
#if !defined(WIN32) && !defined(AIX) && !defined( __OS400__ ) && !defined(__sun)
        value.tm_zone = NULL;
        value.tm_gmtoff = -1;
#endif
        cTemp2 = const_cast<char*>(strpbrk (valueAsChar, "T"));
        cTemp3 = strrchr (cTemp2, ':');
        cTemp3[0] = '\0';
        unsigned int len = strlen (cTemp2);
        cTemp3[0] = ':';

        /*if the timezone is represented adding 'Z' at the end */
        if ((cTemp = const_cast<char*>(strpbrk (valueAsChar, "Z"))) != NULL)
        {
            time_t temp = mktime (&value);
            if (temp == -1)
            {
		    	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            pTm = localtime (&temp);
        }
        /*if the timezone is represented using +/-hh:mm format */
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
		    	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            
            int hours = 0;
            int minutes = 0;

            if (sscanf (cUtc + 1, "%d:%d", &hours, &minutes) != 2)
            {
		    	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
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
		    	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }

            t = labs (t - d);
            pTm = gmtime (&t);
        }
        /*if the zone is not represented in the date */
        else
        {
            /*else it is assumed that the sent time is localtime */
            time_t timeInSecs = mktime (&value);
            if (timeInSecs == -1)
            {
		    	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            pTm = gmtime (&timeInSecs);
        }
        
        if(m_DateTime)
        {
            delete m_DateTime;
            m_DateTime = NULL;
        }
        m_DateTime = new struct tm;
        memcpy (m_DateTime, pTm, sizeof (tm));
        
        return m_DateTime;
    }

    MinInclusive* DateTime::getMinInclusive()
    {
        return new MinInclusive();
    }

    MinExclusive* DateTime::getMinExclusive()
    {
        return new MinExclusive();
    }

    MaxInclusive* DateTime::getMaxInclusive()
    {
        return new MaxInclusive();
    }

    MaxExclusive* DateTime::getMaxExclusive()
    {
        return new MaxExclusive();
    }

    WhiteSpace* DateTime::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }

AXIS_CPP_NAMESPACE_END
