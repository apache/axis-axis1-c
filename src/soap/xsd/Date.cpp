#include "Date.hpp"

AXIS_CPP_NAMESPACE_START

    Date::Date():m_Date(NULL)
    {
    }

    AxisChar* Date::serialize(const void* value) throw (AxisSoapException)
    {
    	return serialize((struct tm*) value);
    }
	
    void* Date::deserialize(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	return (void*) deserializeDate(valueAsChar);
    }
	
    AxisChar* Date::serialize(const struct tm* value) throw (AxisSoapException)
    {
        MinInclusive* minInclusive = getMinInclusive();
        if (minInclusive->isSet())
        {
            if ( 0 > difftime(mktime(&(minInclusive->getMinInclusiveAsStructTM())), mktime(const_cast<struct tm*>(value))) )
            {
                AxisString exceptionMessage =
                "Value to be serialized is less than MinInclusive specified for this type.  MinInclusive = ";
                exceptionMessage += asctime(&(minInclusive->getMinInclusiveAsStructTM()));
                exceptionMessage += ", Value = ";
                exceptionMessage += asctime(value);
                exceptionMessage += ".";
                
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR,
                    const_cast<AxisChar*>(exceptionMessage.c_str()));
            }
        }
        delete minInclusive;
     
    	AxisChar* serializedValue = new AxisChar[80];
    	strftime (serializedValue, 80, "%Y-%m-%dZ", value);
        
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
		return m_Buf;
    }
	
    struct tm* Date::deserializeDate(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	struct tm value;
	    struct tm *pTm;
        AxisChar *cUtc;
	    AxisChar *cTemp;
	    AxisChar *cTemp2;

	    time_t now;
	    time (&now);
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
         * CCYY(-)MM(-)DDZ OR
         * CCYY(-)MM(-)DD+/-<UTC TIME DIFFERENCE>
         */
        if (sscanf (valueAsChar, "%d-%d-%d", &value.tm_year, 
            &value.tm_mon, &value.tm_mday) != 3)
        {
        	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
        }

        value.tm_year -= 1900;
        value.tm_mon--;
        value.tm_hour = 0;
        value.tm_min = 0;
        value.tm_sec = 0;
        value.tm_isdst = -1;
#if !defined(WIN32) && !defined(AIX) && !defined( __OS400__ ) && !defined(__sun)
        value.tm_zone = NULL;
        value.tm_gmtoff = -1;
#endif
        cTemp2 = const_cast<char*>(strpbrk (valueAsChar, ":"));

        /* if the timezone is represented adding 'Z' at the end */
        if ((cTemp = const_cast<char*>(strpbrk (valueAsChar, "Z"))) != NULL)
        {
            time_t timeInSecs = mktime (&value);
            if (timeInSecs == -1)
            {
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            pTm = localtime (&timeInSecs);
        }
        else if (cTemp2 != NULL)
        {
            cUtc = const_cast<char*>(strrchr (valueAsChar, '+'));
            if (cUtc == NULL)
            {
                cUtc = const_cast<char*>(strrchr (valueAsChar, '-'));
            }
            time_t timeInSecs = mktime (&value);
            if (timeInSecs == -1)
            {
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            
            int hours = 0;
            int mins = 0;   
            if (sscanf (cUtc + 1, "%d:%d", &hours, &mins) != 2)
            {
                throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            
            int secs = hours * 60 * 60 + mins * 60;
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
        
        if(m_Date)
        {
            delete m_Date;
            m_Date = NULL;
        }
        m_Date = new struct tm;
        memcpy (m_Date, pTm, sizeof (tm));
        return m_Date;
	}

    MinInclusive* Date::getMinInclusive()
    {
        return new MinInclusive();
    }

    WhiteSpace* Date::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }
	
AXIS_CPP_NAMESPACE_END
