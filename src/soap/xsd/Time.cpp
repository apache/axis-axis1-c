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
    	strftime (serializedValue, 80, "%H:%M:%SZ", value);
     
        IAnySimpleType::serialize(serializedValue);
        delete [] serializedValue;
		return m_Buf;
    }
	
    struct tm* Time::deserializeTime(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
    	struct tm value;
	    struct tm *pTm;
	        	
    	AxisChar *cUtc;
	    AxisChar *cTemp;
	    AxisChar *cTemp2;
	    AxisChar *cTemp3;

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
             * XSD_TIME format is
             * hh:mm:ss.ss...Z OR
             * hh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>
             */
            if (sscanf (valueAsChar, "%d:%d:%d", &value.tm_hour, 
                &value.tm_min, &value.tm_sec) != 3)
            {
            	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
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
                time_t temp = mktime (&value);
                if (temp == -1)
                {
                	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
                }
                pTm = localtime (&temp);
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

                //t = fabs (t - d);
                t = labs (t - d); // Samisa - use correct typed methods - we need long int; not double
                pTm = gmtime (&t);
            }
            /* if the zone is not represented in the date */
            else
            {
                /* else it is assumed that the sent time is localtime */
                // memcpy(&m_TMUTC, &m_TM, sizeof(tm));
                time_t timeInSecs = mktime (&value);
                if (timeInSecs == -1)
                {
                	throw new AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
                }

                pTm = gmtime (&timeInSecs);
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

    WhiteSpace* Time::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }

AXIS_CPP_NAMESPACE_END
