/* -*- C++ -*- */
/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */

#include <stdio.h>
#include <axis/server/AxisTime.h>
#include "AxisUtils.h"

#define TIMEBUFFSIZE 80

AxisTime::AxisTime ()
{

}

AxisTime::AxisTime (struct tm ntime)
{
    m_TMUTC = ntime;
}

AxisTime::AxisTime (time_t pTime)
{
    tm* pTMUTC = gmtime (&pTime);
    memcpy (&m_TMUTC, pTMUTC, sizeof (tm));
}

AxisTime::~AxisTime ()
{

}

void AxisTime::setValue (const AxisChar* strValue)
{
    m_sValue = strValue;
    mkCTime ();
}

void AxisTime::setValue (XSDTYPE type, uParamValue Value)
{
    m_Type = type;
    if (type == XSD_DURATION)
    {
        m_Duration = Value.lDuration;
    }
    else
    {
        m_TM = Value.tValue;
    }
}

void AxisTime::setType (XSDTYPE xsdType)
{
    m_Type = xsdType;
}

AxisString AxisTime::getValue ()
{
    return m_sValue;
}

/**
* Serialize the duration in seconds into a xml duration string
* of the format PnYnMnDTnHnMnS
*/

AxisString & AxisTime::serialize (const AxisChar* sName, long lDuration,
    XSDTYPE nType)
{
    AxisChar buff[4];
    strXSDDuration = "P";
    int x = 365 * 24 * 3600;
    int intYears = lDuration / x;
    long tempYears = intYears * x;
    //sprintf((char*)buff,"%d", intYears);
    AxisSprintf (buff, 4, "%d", intYears);
    strXSDDuration.append (buff);
    strXSDDuration.append ("Y");
    lDuration = lDuration - (tempYears);
    x = 30 * 24 * 3600;
    int intMonths = lDuration / x;
    //sprintf((char*)buff,"%d", intMonths);
    AxisSprintf (buff, 4, "%d", intMonths);
    strXSDDuration.append (buff);
    strXSDDuration.append ("M");
    lDuration = lDuration - (intMonths * x);
    x = 24 * 3600;
    int intDays = lDuration / x;
    //sprintf((char*)buff,"%d", intDays);
    AxisSprintf (buff, 4, "%d", intDays);
    strXSDDuration.append (buff);
    strXSDDuration.append ("DT");
    lDuration = lDuration - (intDays * x);
    x = 3600;
    int intHours = lDuration / x;
    //sprintf((char*)buff,"%d", intHours);
    AxisSprintf (buff, 4, "%d", intHours);
    strXSDDuration.append (buff);
    strXSDDuration.append ("H");
    lDuration = lDuration - (intHours * x);
    x = 60;
    int intMins = lDuration / x;
    //sprintf((char*)buff,"%d", intMins);
    AxisSprintf (buff, 4, "%d", intMins);
    strXSDDuration.append (buff);
    strXSDDuration.append ("M");
    int intSecs = lDuration - (intMins * x);
    //sprintf((char*)buff,"%d", intSecs);
    AxisSprintf (buff, 4, "%d", intSecs);
    strXSDDuration.append (buff);
    strXSDDuration.append ("S");

    return strXSDDuration;
}

/**
* Serialize the c type tm struct into a xml date string.
* The serialized date will represent UTC time
*/
AxisString & AxisTime::serialize (const AxisChar* sName, struct tm tValue,
                                  XSDTYPE nType)
{
    /*formats the output date in the format CCYY-MM-DDThh:mm:ssZ */
    switch (nType)
    {
        case XSD_DATETIME:
            strftime (buf1, TIMEBUFFSIZE, "%Y-%m-%dT%H:%M:%SZ", &tValue);
            strXSDDate = buf1;
            //AxisUtils::convert(strXSDDate, buf1);
            break;
        case XSD_DATE:
            strftime (buf1, TIMEBUFFSIZE, "%Y-%m-%dZ", &tValue);
            strXSDDate = buf1;
            //AxisUtils::convert(strXSDDate, buf1);
            break;
        case XSD_TIME:
            strftime (buf1, TIMEBUFFSIZE, "%H:%M:%SZ", &tValue);
            strXSDDate = buf1;
            //AxisUtils::convert(strXSDDate, buf1);
            break;
        default:;
    }
    return strXSDDate;
}

/**
* This function deserialize the xml datetime type into a c type
* tm struct. The struct tm created will contain the UTC time
*/

int AxisTime::mkCTime ()
{
//    AxisChar* endptr;
    AxisChar *cUtc;
    AxisChar *cTemp;
    AxisChar *cTemp2;
    AxisChar *cTemp3;
    int intLen = 0;
    int intHours = 0;
    int intMins = 0;
    int intSecs = 0;
    unsigned int intPos, intPos1, intPos2, intPos3, intPos4, intPos5, intPos6;
    time_t now;
    struct tm result1, result2;
    struct tm *pTm;
    time (&now);
    pTm = gmtime (&now);
    memcpy (&result1, pTm, sizeof (tm));
    pTm = localtime (&now);
    memcpy (&result2, pTm, sizeof (tm));
    time_t d = mktime (&result1) - mktime (&result2);
    if (d == -1)
        return AXIS_FAIL;

    switch (m_Type)
    {
        case XSD_DURATION:
            /*XSD_DURATION is of the format PnYnMnDTnHnMnS */
            intPos1 = m_sValue.find_first_of ("Y");
            strYears = m_sValue.substr (1, intPos1 - 1);
            m_longYears = atoi (strYears.c_str ());
            //m_intYears = wcstol(strYears.c_str(), &endptr, 10);
            duration.years = m_longYears;
            intPos2 = m_sValue.find_first_of ("M");
            strMonths = m_sValue.substr (intPos1 + 1, intPos2 - intPos1 - 1);
            m_intMonths = atoi (strMonths.c_str ());
            //m_intMonths = wcstol(strMonths.c_str(), &endptr, 10);
            duration.months = m_intMonths;
            intPos3 = m_sValue.find_first_of ("D");
            strDays = m_sValue.substr (intPos2 + 1, intPos3 - intPos2 - 1);
            m_intDays = atoi (strDays.c_str ());
            //m_intDays = wcstol(strDays.c_str(), &endptr, 10);
            duration.days = m_intDays;
            intPos4 = m_sValue.find_first_of ("H");
            strHours = m_sValue.substr (intPos3 + 2, intPos4 - intPos3 - 2);
            m_intHours = atoi (strHours.c_str ());
            //m_intHours = wcstol(strHours.c_str(), &endptr, 10);
            duration.hours = m_intHours;
            intPos5 = m_sValue.find_first_of ("M");
            strMins = m_sValue.substr (intPos4 + 1, intPos5 - intPos4 - 1);
            m_intMins = atoi (strMins.c_str ());
            //m_intMins = wcstol(strMins.c_str(), &endptr, 10);
            duration.mins = m_intMins;
            intPos6 = m_sValue.find_first_of ("S");
            strSecs = m_sValue.substr (intPos5 + 1, intPos6 - intPos5 - 1);
            m_intSecs = atoi (strSecs.c_str ());
            //m_intSecs = wcstol(strSecs.c_str(), &endptr, 10);
            duration.secs = m_intSecs;

            m_Duration = 0;
            m_Duration += duration.years * 365 * 24 * 3600;
            m_Duration += duration.months * 30 * 24 * 3600;
            m_Duration += duration.days * 24 * 3600;
            m_Duration += duration.hours * 3600;
            m_Duration += duration.mins * 60;
            m_Duration += duration.secs;

            break;

        case XSD_DATETIME:

            /* dismantle m_sValue to get tm value;
             * XSD_DATETIME format is
             * CCYY(-)MM(-)DDThh:mm:ss.ss...Z OR
             * CCYY(-)MM(-)DDThh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>
             */
            if (sscanf (m_sValue.c_str (), "%d-%d-%dT%d:%d:%d", &m_TM.tm_year,
                &m_TM.tm_mon, &m_TM.tm_mday, &m_TM.tm_hour, &m_TM.tm_min, 
		&m_TM.tm_sec) != 6)
                return AXIS_FAIL; /*invalid data format */



            m_TM.tm_year -= 1900;
            m_TM.tm_mon--;
            m_TM.tm_isdst = -1;
#if !defined(WIN32) && !defined(AIX)
            m_TM.tm_zone = NULL;
            m_TM.tm_gmtoff = -1;
#endif
            cTemp2 = strpbrk (m_sValue.c_str (), "T");
            cTemp3 = strrchr (cTemp2, ':');
            cTemp3[0] = '\0';
            intLen = strlen (cTemp2);
            cTemp3[0] = ':';

            /*if the timezone is represented adding 'Z' at the end */
            if ((cTemp = strpbrk (m_sValue.c_str (), "Z")) != NULL)
            {
                time_t temp = mktime (&m_TM);
                if (temp == -1)
                    return AXIS_FAIL;
                pTm = localtime (&temp);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }
            /*if the timezone is represented using +/-hh:mm format */

            else if (intLen > (sizeof (char) * 6))
            {
                cUtc = strpbrk (cTemp2, "+");
                if (cUtc == NULL)
                    cUtc = strpbrk (cTemp2, "-");
                time_t timeInSecs = mktime (&m_TM);
                if (timeInSecs == -1)
                    return AXIS_FAIL;
                //pTm = localtime(&timeInSecs);
                if (sscanf (cUtc + 1, "%d:%d", &intHours, &intMins) != 2)
                    return AXIS_FAIL;
                intSecs = intHours * 60 * 60 + intMins * 60;
                if ((cTemp = strpbrk ((cUtc), "+")) != NULL)
                {
                    timeInSecs += intSecs;
                }
                else
                {
                    timeInSecs -= intSecs;
                }
                pTm = localtime (&timeInSecs);
                memcpy (&m_TM, pTm, sizeof (tm));
                time_t t = mktime (&m_TM);
                if (t == -1)
                    return AXIS_FAIL;
                t = abs (t - d);
                pTm = gmtime (&t);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }
            /*if the zone is not represented in the date */
            else
            {
                /*else it is assumed that the sent time is localtime */
                time_t timeInSecs = mktime (&m_TM);
                if (timeInSecs == -1)
                    return AXIS_FAIL;
                pTm = gmtime (&timeInSecs);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }

            break;

        case XSD_DATE:
            /* dismantle m_sValue to get tm value;
             * XSD_DATETIME format is
             * CCYY(-)MM(-)DDZ OR
             * CCYY(-)MM(-)DD+/-<UTC TIME DIFFERENCE>
             */
            if (sscanf (m_sValue.c_str (), "%d-%d-%d", &m_TM.tm_year, 
                &m_TM.tm_mon, &m_TM.tm_mday) != 3)
                return AXIS_FAIL; /*invalid data format */

            m_TM.tm_year -= 1900;
            m_TM.tm_mon--;
            m_TM.tm_hour = 0;
            m_TM.tm_min = 0;
            m_TM.tm_sec = 0;
            m_TM.tm_isdst = -1;
#if !defined(WIN32) && !defined(AIX)
            m_TM.tm_zone = NULL;
            m_TM.tm_gmtoff = -1;
#endif
            cTemp3 = strpbrk (m_sValue.c_str (), ":");

            /* if the timezone is represented adding 'Z' at the end */
            if ((cTemp = strpbrk (m_sValue.c_str (), "Z")) != NULL)
            {
                time_t timeInSecs = mktime (&m_TM);
                if (timeInSecs == -1)
                    return AXIS_FAIL;
                pTm = localtime (&timeInSecs);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }
            else if (cTemp3 != NULL)
            {
                cUtc = strrchr (m_sValue.c_str (), '+');
                if (cUtc == NULL)
                    cUtc = strrchr (m_sValue.c_str (), '-');
                time_t timeInSecs = mktime (&m_TM);
                if (timeInSecs == -1)
                    return AXIS_FAIL;
                if (sscanf (cUtc + 1, "%d:%d", &intHours, &intMins) != 2)
                    return AXIS_FAIL;
                intSecs = intHours * 60 * 60 + intMins * 60;
                if ((cTemp = strpbrk ((cUtc), "+")) != NULL)
                {
                    timeInSecs += intSecs;
                }
                else
                {
                    timeInSecs -= intSecs;
                }
                pTm = localtime (&timeInSecs);
                memcpy (&m_TM, pTm, sizeof (tm));
                time_t t = mktime (&m_TM);
                if (t == -1)
                    return AXIS_FAIL;
                t = abs (t - d);
                pTm = gmtime (&t);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }
            /*if the zone is not represented in the date */
            else
            {
                /*else it is assumed that the sent time is localtime */
                time_t timeInSecs = mktime (&m_TM);
                if (timeInSecs == -1)
                    return AXIS_FAIL;
                pTm = gmtime (&timeInSecs);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }

            break;

        case XSD_TIME:
            /* dismantle m_sValue to get tm value;
             * XSD_TIME format is
             * hh:mm:ss.ss...Z OR
             * hh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>
             */
            if (sscanf (m_sValue.c_str (), "%d:%d:%d", &m_TM.tm_hour, 
                &m_TM.tm_min, &m_TM.tm_sec) != 3)
                return AXIS_FAIL; /* invalid data format */

            m_TM.tm_year = 70;
            m_TM.tm_mon = 0;
            m_TM.tm_mday = 1;     /* Day of month (1 - 31) */
            m_TM.tm_isdst = -1;
#if !defined(WIN32) && !defined(AIX)
            m_TM.tm_zone = NULL;
            m_TM.tm_gmtoff = -1;
#endif
            // printf("m_sValue:%s\n", m_sValue.c_str());

            // cTemp2 = strpbrk(m_sValue.c_str(), "T");
            // strcpy ( cTemp2,m_sValue.c_str());
            cTemp2 = (char*) m_sValue.c_str ();
            // printf("cTemp2:%s\n", cTemp2);

            cTemp3 = strrchr (cTemp2, ':');
            // printf("cTemp3:%s\n", cTemp3);
            cTemp3[0] = '\0';
            intLen = strlen (cTemp2);
            cTemp3[0] = ':';

            /* if the timezone is represented adding 'Z' at the end */
            if ((cTemp = strpbrk (m_sValue.c_str (), "Z")) != NULL)
            {
                time_t temp = mktime (&m_TM);
                if (temp == -1)
                    return AXIS_FAIL;
                pTm = localtime (&temp);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }
            /* if the timezone is represented using +/-hh:mm format */

            else if (intLen > (sizeof (char) * 6))
            {
                cUtc = strpbrk (cTemp2, "+");
                if (cUtc == NULL)
                    cUtc = strpbrk (cTemp2, "-");
                time_t timeInSecs = mktime (&m_TM);
                if (timeInSecs == -1)
                    return AXIS_FAIL;
                // pTm = localtime(&timeInSecs);
                if (sscanf (cUtc + 1, "%d:%d", &intHours, &intMins) != 2)
                    return AXIS_FAIL;
                intSecs = intHours * 60 * 60 + intMins * 60;
                if ((cTemp = strpbrk ((cUtc), "+")) != NULL)
                {
                    timeInSecs += intSecs;
                }
                else
                {
                    timeInSecs -= intSecs;
                }
                pTm = localtime (&timeInSecs);
                memcpy (&m_TM, pTm, sizeof (tm));
                time_t t = mktime (&m_TM);
                if (t == -1)
                    return AXIS_FAIL;
                t = abs (t - d);
                pTm = gmtime (&t);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }
            /* if the zone is not represented in the date */
            else
            {
                /* else it is assumed that the sent time is localtime */
                // memcpy(&m_TMUTC, &m_TM, sizeof(tm));
                time_t timeInSecs = mktime (&m_TM);
                if (timeInSecs == -1)
                    return AXIS_FAIL;
                pTm = gmtime (&timeInSecs);
                memcpy (&m_TMUTC, pTm, sizeof (tm));
            }

            break;

        default:;
    }
}

long AxisTime::getDuration ()
{
    return m_Duration;
}

struct tm AxisTime::getDateTime ()
{
    return m_TMUTC;
}

struct tm AxisTime::getDate ()
{
    return m_TMUTC;
}

struct tm AxisTime::getTime ()
{
    return m_TMUTC;
}

// following function is written with no consideration of the efficiency.
// should be changed later - Susantha 23-10-2003

struct tm AxisTime::Deserialize (const AxisChar* strValue, XSDTYPE type)
{
    AxisTime at;
    at.setType (type);
    at.setValue (strValue);
    return at.getDateTime ();
}

long AxisTime::DeserializeDuration (const AxisChar* strValue, XSDTYPE type)
{
    AxisTime at;
    at.setType (type);
    at.setValue (strValue);
    return at.getDuration ();
}


/*int main2(int)
{
    AxisTime* objTime = new AxisTime();
*/
/*    //===========================
    objTime->setType(XSD_DATETIME);
    //GMT in Z format
    //objTime->setValue("2003-03-24T21:55:56Z");
    //GMT in +/- format
    objTime->setValue("2003-03-24T21:55:56-5:30");
    //no timezone specified. assumed localtime
    //objTime->setValue("2003-03-24T21:55:56");


    struct tm tmObj = objTime->getDateTime();
    AxisString str = objTime->serialize("", tmObj, XSD_DATETIME);
    printf("sent datetime:%s\n", "2003-03-24T21:55:56-5:30");
    printf("got  datetime:%s\n", str.c_str());
    
*/
    //=============================
        //===========================
/*  objTime->setType(XSD_DATE);
    //GMT in Z format
    //objTime->setValue("2003-03-24Z");
    //GMT in +/- format
    objTime->setValue("2003-03-24+5:30");
    //no timezone specified. assumed localtime
    //objTime->setValue("2003-03-24");


    struct tm tmObj = objTime->getDate();
    AxisString str = objTime->serialize("", tmObj, XSD_DATE);
    printf("sent date:%s\n", "2003-03-24+5:30");
    printf("got  date:%s\n", str.c_str());
*/
    //=============================
        //===========================
/*    objTime->setType(XSD_TIME);
    //GMT in Z format
    //objTime->setValue("T1:3:3");
    //GMT in +/- format
    objTime->setValue("T21:55:56+5:30");
    //no timezone specified. assumed localtime
    //objTime->setValue("T21:55:56");

    struct tm tmObj = objTime->getTime();
    AxisString str = objTime->serialize("", tmObj, XSD_TIME);
    //printf("sent time:%s\n", "T1:1:1");
    printf("got  time:%s\n", str.c_str());
*/
    //===========================
    //==========================*/
/*    objTime->setType(XSD_DURATION);
    //Duration in PnYnMnDTnHnMnS format
    objTime->setValue("P59Y5M1DT11H26M29S");
    printf("m_Duration:%d\n", objTime->m_Duration);
    AxisString str = objTime->serialize("", objTime->m_Duration, XSD_DURATION);
    printf("sent string:%s\n", "P59Y5M1DT11H26M29S");
    printf("got  string:%s\n", str.c_str());
*/
    //==============================
/*
    return 0;

}
*/
