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

#include "GMonthDay.hpp"

AXIS_CPP_NAMESPACE_START

    GMonthDay::GMonthDay()
    {
    }

    GMonthDay::GMonthDay(const xsd__gMonthDay* value)
    {
        if (value)
        {
            setNil(false);
            serialize(value);
        }
    }

    XSDTYPE GMonthDay::getType()
    {
        return XSD_GMONTHDAY;
    }

    xsd__gMonthDay* GMonthDay::getGMonthDay()
    {
        if(isNil())
        {
            return NULL;
        }
        else
        {
            return deserializeGMonthDay(m_Buf);
        }
    }

    void * GMonthDay::getValue()
    {
        return (void*) getGMonthDay();
    }

    AxisChar* GMonthDay::serialize(const xsd__gMonthDay* value) throw (AxisSoapException)
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
        strftime (valueAsString, 80, "--%m-%d", value);
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
  
    xsd__gMonthDay* GMonthDay::deserializeGMonthDay(const AxisChar* valueAsChar) throw (AxisSoapException)
    {
      struct tm value;
      struct tm *pTm;
        AxisChar *cUtc;
      AxisChar *cTemp;
      AxisChar *cTemp2;

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

        /* dismantle m_sValue to get tm value;
         * XSD_DATETIME format is
         * CCYY(-)MMZ OR
         * CCYY(-)MM+/-<UTC TIME DIFFERENCE>
         */
        if (sscanf (valueAsChar, "--%d-%d", &value.tm_mon, 
            &value.tm_mday) != 2)
        {
         throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
        }

        value.tm_year = 70;
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
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
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
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            
            int hours = 0;
            int mins = 0;   
            if (sscanf (cUtc + 1, "%d:%d", &hours, &mins) != 2)
            {
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
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
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            t = labs (t - d);
            pTm = localtime (&t);
        }
        /*if the zone is not represented in the date */
        else
        {
            /*else it is assumed that the sent time is localtime */
            time_t timeInSecs = mktime (&value);
            if (timeInSecs == -1)
            {
                throw AxisSoapException(CLIENT_SOAP_SOAP_CONTENT_ERROR);
            }
            pTm = localtime (&timeInSecs);
        }

        pTm->tm_year -= 70; // Take off the 70 offset we added initially        

        xsd__gMonthDay * returnValue = new xsd__gMonthDay;
        memcpy (returnValue, pTm, sizeof (tm));
        return returnValue;
 }

    MinInclusive* GMonthDay::getMinInclusive()
    {
        return new MinInclusive();
    }

    MinExclusive* GMonthDay::getMinExclusive()
    {
        return new MinExclusive();
    }

    MaxInclusive* GMonthDay::getMaxInclusive()
    {
        return new MaxInclusive();
    }

    MaxExclusive* GMonthDay::getMaxExclusive()
    {
        return new MaxExclusive();
    }

    WhiteSpace* GMonthDay::getWhiteSpace()
    {
        return new WhiteSpace(COLLAPSE);
    }
    
AXIS_CPP_NAMESPACE_END
