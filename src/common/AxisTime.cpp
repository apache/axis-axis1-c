/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "SOAP" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 *
 *
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
#include <stdio.h>

#include <axis/common/AxisTime.h>
#include <axis/common/AxisUtils.h>

AxisTime::AxisTime()
{

}

AxisTime::AxisTime(struct tm ntime)
{
    m_TMUTC = ntime;
}

AxisTime::AxisTime(time_t pTime)
{
	tm* pTMUTC = gmtime(&pTime);
	memcpy(&m_TMUTC, pTMUTC, sizeof(tm));
}

AxisTime::~AxisTime()
{

}

void AxisTime::setValue(const AxisChar* strValue)
{
    m_sValue = strValue;
    mkCTime();
}

void AxisTime::setValue(XSDTYPE type,  uParamValue Value)
{
    m_Type = type;
    if(type == XSD_DURATION)
    {
        m_Duration = Value.lDuration;
    }
    else
    {
        m_TM = Value.tValue;
    }
}

void AxisTime::setType(XSDTYPE xsdType)
{
    m_Type = xsdType;
}

AxisString AxisTime::getValue()
{
    return m_sValue;
}

/**
* Serialize the duration in seconds into a xml duration string
* of the format PnYnMnDTnHnMnS
*/
AxisString& AxisTime::serialize(const AxisChar* sName, long long lDuration, XSDTYPE nType)
{
	AxisChar buff[4];
	strXSDDuration = "P";
	int x = 365 * 24 * 3600;
	int intYears = lDuration / x;
    long long tempYears = (long long) intYears * x;
	//sprintf((char*)buff,"%d", intYears);
	AxisSprintf(buff, 4, "%d", intYears);
	strXSDDuration.append(buff);
	strXSDDuration.append("Y");
	lDuration = lDuration - (tempYears);
	x = 30 * 24 * 3600;
	int intMonths = lDuration / x;
	//sprintf((char*)buff,"%d", intMonths);
	AxisSprintf(buff, 4, "%d", intMonths);
	strXSDDuration.append(buff);
	strXSDDuration.append("M");
	lDuration = lDuration - (intMonths * x);
	x = 24 * 3600;
	int intDays = lDuration / x;
	//sprintf((char*)buff,"%d", intDays);
	AxisSprintf(buff, 4, "%d", intDays);
	strXSDDuration.append(buff);
	strXSDDuration.append("DT");
	lDuration = lDuration - (intDays * x);
	x = 3600;
	int intHours = lDuration / x;
	//sprintf((char*)buff,"%d", intHours);
	AxisSprintf(buff, 4, "%d", intHours);
	strXSDDuration.append(buff);
	strXSDDuration.append("H");
	lDuration = lDuration - (intHours * x);
	x = 60;
	int intMins = lDuration / x;
	//sprintf((char*)buff,"%d", intMins);
	AxisSprintf(buff, 4, "%d", intMins);
	strXSDDuration.append(buff);
	strXSDDuration.append("M");
	int intSecs = lDuration - (intMins * x);
	//sprintf((char*)buff,"%d", intSecs);
	AxisSprintf(buff, 4, "%d", intSecs);
	strXSDDuration.append(buff);
	strXSDDuration.append("S");

	return strXSDDuration;
}

/**
* Serialize the c type tm struct into a xml date string.
* The serialized date will represent UTC time
*/
AxisString& AxisTime::serialize(const AxisChar* sName, struct tm tValue, XSDTYPE nType)
{
    /*formats the output date in the format CCYY-MM-DDThh:mm:ssZ*/
    switch(nType)
    {
        case XSD_DATETIME:
            strftime(buf1, 80, "%Y-%m-%dT%H:%M:%SZ", &tValue);
            strXSDDate = buf1;
            //AxisUtils::convert(strXSDDate, buf1);
            break;
        case XSD_DATE:
            strftime(buf1, 80, "%Y-%m-%dZ", &tValue);
            strXSDDate = buf1;
            //AxisUtils::convert(strXSDDate, buf1);
            break;
        case XSD_TIME:
            strftime(buf1, 80, "%H:%M:%SZ", &tValue);
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
void AxisTime::mkCTime()
{
//    AxisChar* endptr;
    unsigned int intPos, intPos1, intPos2, intPos3, intPos4, intPos5, intPos6;
    AxisChar buff[4] = {0};
    time_t now;
    struct tm result1, result2;
	struct tm* pTm;
    time(&now);
	pTm = gmtime(&now);
	memcpy(&result1, pTm, sizeof(tm));
	pTm = localtime(&now);
	memcpy(&result2, pTm, sizeof(tm));
    time_t d = mktime(&result1) - mktime(&result2);

    switch(m_Type)
    {
        case XSD_DURATION:
            /*XSD_DURATION is of the format PnYnMnDTnHnMnS*/
            intPos1 = m_sValue.find_first_of("Y");
            strYears = m_sValue.substr(1,intPos1 - 1);
            m_longYears = (long long) atoi(strYears.c_str());
            //m_intYears = wcstol(strYears.c_str(), &endptr, 10);
            duration.years = m_longYears;
            intPos2 = m_sValue.find_first_of("M");
            strMonths = m_sValue.substr(intPos1 + 1, intPos2 - intPos1 - 1);
            m_intMonths = atoi(strMonths.c_str());
            //m_intMonths = wcstol(strMonths.c_str(), &endptr, 10);
            duration.months = m_intMonths;
            intPos3 = m_sValue.find_first_of("D");
            strDays = m_sValue.substr(intPos2 + 1, intPos3 - intPos2 -1);
            m_intDays = atoi(strDays.c_str());
            //m_intDays = wcstol(strDays.c_str(), &endptr, 10);
            duration.days = m_intDays;
            intPos4 = m_sValue.find_first_of("H");
            strHours = m_sValue.substr(intPos3 + 2, intPos4 - intPos3 -2);
            m_intHours = atoi(strHours.c_str());
            //m_intHours = wcstol(strHours.c_str(), &endptr, 10);
            duration.hours = m_intHours;
            intPos5 = m_sValue.find_first_of("M");
            strMins = m_sValue.substr(intPos4 + 1, intPos5 - intPos4 -1);
            m_intMins = atoi(strMins.c_str());
            //m_intMins = wcstol(strMins.c_str(), &endptr, 10);
            duration.mins = m_intMins;
            intPos6 = m_sValue.find_first_of("S");
            strSecs = m_sValue.substr(intPos5 + 1, intPos6 - intPos5 -1);
            m_intSecs = atoi(strSecs.c_str());
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

            /*dismantle m_sValue to get tm value;
                XSD_DATETIME format is
                CCYY(-)MM(-)DDThh:mm:ss.ss...Z OR
                CCYY(-)MM(-)DDThh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>
            */
            strYears = m_sValue.substr(0,4);
            m_intYears = atoi(strYears.c_str()) - 1900;
            //m_intYears = wcstol(strYears.c_str(), &endptr, 10) - 1900;
            //sprintf((char*)buff,"%d", m_intYears);
            AxisSprintf(buff, 4, "%d", m_intYears);
            strYears = buff;
            intPos = m_sValue.find_first_of("-");
            /* date is of the format CCYY-MM-DD */
            if(intPos != std::string::npos && intPos<=7)
            {
                strMonths = m_sValue.substr(5,2);
                strDays = m_sValue.substr(8,2);
                strHours = m_sValue.substr(11,2);
                strMins = m_sValue.substr(14,2);
                /*Decimal fraction of the second is omitted*/
                strSecs = m_sValue.substr(17,2);
                strZone = m_sValue.substr(19,m_sValue.length()-19);
            }
            /* date is of the format CCYYMMDD */
            else if((intPos == std::string::npos) || (intPos != std::string::npos && intPos > 7))
            {
                strMonths = m_sValue.substr(4,2);
                strMonths = m_sValue.substr(6,2);
                strHours = m_sValue.substr(9,2);
                strMins = m_sValue.substr(12,2);
                /*Decimal fraction of the second is omitted*/
                strSecs = m_sValue.substr(15,2);
                strZone = m_sValue.substr(17,m_sValue.length()-17);
            }

            m_TM.tm_year = atoi(strYears.c_str());
            //m_TM.tm_year = wcstol(strYears.c_str(), &endptr, 10);
            m_TM.tm_mon = atoi(strMonths.c_str());
            //m_TM.tm_mon = wcstol(strMonths.c_str(), &endptr, 10);
            m_TM.tm_mday = atoi(strDays.c_str());
            //m_TM.tm_mday = wcstol(strDays.c_str(), &endptr, 10);
            m_TM.tm_hour = atoi(strHours.c_str());
            //m_TM.tm_hour = wcstol(strHours.c_str(), &endptr, 10);
            m_TM.tm_min = atoi(strMins.c_str());
            //m_TM.tm_min = wcstol(strMins.c_str(), &endptr, 10);
            m_TM.tm_sec = atoi(strSecs.c_str());
            //m_TM.tm_sec = wcstol(strSecs.c_str(), &endptr, 10);

            /*if the timezone is represented adding 'Z' at the end*/
            if(strZone.substr(0,1) == "Z")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }
            /*if the timezone is represented using +/-hh:mm format*/
            else if(strZone.substr(0,1) == "+" ||strZone.substr(0,1) == "-")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
                m_intHours = atoi(strZone.substr(1,2).c_str());
                //m_intHours = wcstol(strZone.substr(1,2).c_str(), &endptr, 10);
                m_intMins = atoi(strZone.substr(3,2).c_str());
                //m_intMins = wcstol(strZone.substr(3,2).c_str(), &endptr, 10);
                m_intSecs = m_intHours * 60 * 60 + m_intMins * 60;
                if(strZone.substr(0,1) == "+")
                {
                    timeInSecs += m_intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));
                }
                else if(strZone.substr(0,1) == "-")
                {

                    timeInSecs -= m_intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));

                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));
                }
            }
            /*if the zone is not represented in the date*/
            else
            {
                /*else it is assumed that the sent time is localtime*/
                time_t timeInSecs = mktime(&m_TM);
				pTm = gmtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }

            break;

        case XSD_DATE:
            /*dismantle m_sValue to get tm value;
                XSD_DATETIME format is
                CCYY(-)MM(-)DDZ OR
                CCYY(-)MM(-)DD+/-<UTC TIME DIFFERENCE>
            */
            strYears = m_sValue.substr(0,4);
            m_intYears = atoi(strYears.c_str()) - 1900;
            //m_intYears = wcstol(strYears.c_str(), &endptr, 10) - 1900;
            //sprintf((char*)buff,"%d", m_intYears);
            AxisSprintf(buff, 4, "%d", m_intYears);
            strYears = buff;
            intPos = m_sValue.find_first_of("-");
            /* date is of the format CCYY-MM-DD */
            if(intPos != std::string::npos && intPos <= 7)
            {
                strMonths = m_sValue.substr(5,2);
                strDays = m_sValue.substr(8,2);
                strZone = m_sValue.substr(10,m_sValue.length() - 10);
            }
            /* date is of the format CCYYMMDD */
            else if((intPos == std::string::npos) || (intPos != std::string::npos && intPos > 7))
            {
                strMonths = m_sValue.substr(4,2);
                strMonths = m_sValue.substr(6,2);
                strZone = m_sValue.substr(8,m_sValue.length() - 8);
            }

            m_TM.tm_year = atoi(strYears.c_str());
            //m_TM.tm_year= wcstol(strYears.c_str(), &endptr, 10);
            m_TM.tm_mon = atoi(strMonths.c_str());
            //m_TM.tm_mon = wcstol(strMonths.c_str(), &endptr, 10);
            m_TM.tm_mday = atoi(strDays.c_str());
            //m_TM.tm_mday = wcstol(strDays.c_str(), &endptr, 10);

            /*if the timezone is represented adding 'Z' at the end*/
            if(strZone.substr(0,1) == "Z")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }
            /*if the timezone is represented using +/-hh:mm format*/
            else if(strZone.substr(0,1) == "+" ||strZone.substr(0,1) == "-")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
                m_intHours = atoi(strZone.substr(1,2).c_str());
                //m_intHours = wcstol(strZone.substr(1,2).c_str(), &endptr, 10);
                m_intMins = atoi(strZone.substr(3,2).c_str());
                //m_intMins = wcstol(strZone.substr(3,2).c_str(), &endptr, 10);
                m_intSecs = m_intHours * 60 * 60 + m_intMins * 60;
                if(strZone.substr(0,1) == "+")
                {
                    timeInSecs += m_intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));
                }
                else if(strZone.substr(0,1) == "-")
                {
                    timeInSecs -= m_intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));
                }
            }
            /*if the zone is not represented in the date*/
            else
            {
                /*else it is assumed that the sent time is localtime*/
                time_t timeInSecs = mktime(&m_TM);
				pTm = gmtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }

            break;

        case XSD_TIME:
            /*dismantle m_sValue to get tm value;
                XSD_TIME format is
                hh:mm:ss.ss...Z OR
                hh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>
            */
            strHours = m_sValue.substr(0,2);
            strMins = m_sValue.substr(3,2);
            /*Decimal fraction of the second is omitted*/
            strSecs = m_sValue.substr(6,2);
            strZone = m_sValue.substr(8,m_sValue.length() - 8);

            m_TM.tm_hour = atoi(strHours.c_str());
            //m_TM.tm_hour = wcstol(strHours.c_str(), &endptr, 10);
            m_TM.tm_min = atoi(strMins.c_str());
            //m_TM.tm_min = wcstol(strMins.c_str(), &endptr, 10);
            m_TM.tm_sec = atoi(strSecs.c_str());
            //m_TM.tm_sec = wcstol(strSecs.c_str(), &endptr, 10);

            /*if the timezone is represented adding 'Z' at the end*/
            if(strZone.substr(0,1) == "Z")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }
            /*if the timezone is represented using +/-hh:mm format*/
            else if(strZone.substr(0,1) == "+" ||strZone.substr(0,1) == "-")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
                m_intHours = atoi(strZone.substr(1,2).c_str());
                //m_intHours = wcstol(strZone.substr(1,2).c_str(), &endptr, 10);
                m_intMins = atoi(strZone.substr(3,2).c_str());
                //m_intMins = wcstol(strZone.substr(3,2).c_str(), &endptr, 10);
                m_intSecs = m_intHours * 60 * 60 + m_intMins * 60;
                if(strZone.substr(0,1) == "+")
                {
                    timeInSecs += m_intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));
                }
                else if(strZone.substr(0,1) == "-")
                {
                    timeInSecs -= m_intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));
                }
            }
            /*if the zone is not represented in the date*/
            else
            {
                /*else it is assumed that the sent time is localtime*/
                time_t timeInSecs = mktime(&m_TM);
				pTm = gmtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }

            break;
        default:;
    }
}


long AxisTime::getDuration()
{
    return m_Duration;
}

struct tm AxisTime::getDateTime()
{
    return m_TMUTC;
}

struct tm AxisTime::getDate()
{
    return m_TMUTC;
}

struct tm AxisTime::getTime()
{
    return m_TMUTC;
}

//following function is written with no consideration of the efficiency.
//should be changed later - Susantha 23-10-2003
struct tm AxisTime::Deserialize(const AxisChar* strValue, XSDTYPE type)
{
	AxisTime at;
	at.setType(type);
	at.setValue(strValue);
	return at.getDateTime();
}

long AxisTime::DeserializeDuration(const AxisChar* strValue, XSDTYPE type)
{
	AxisTime at;
	at.setType(type);
	at.setValue(strValue);
	return at.getDuration();
}

//int main(int)
//{
    //AxisTime* objTime = new AxisTime();
    //===========================
    //objTime->setType(XSD_DATETIME);
    /*GMT in Z format*/
    //objTime->setValue("2003-03-24T21:55:56Z");
    /*GMT in +/- format*/
    //objTime->setValue("2003-03-24T21:55:56+5:30");
    /*no timezone specified. assumed localtime*/
    //objTime->setValue("2003-03-24T21:55:56");
    //struct tm x;
    //x.tm_sec = 20;
    //x.tm_min = 55;
    //x.tm_hour = 21;
    //x.tm_mday = 27;
    //x.tm_mon = 11;
    //x.tm_year = 103;
    //objTime->serialize("", x);
    //objTime->mkCTime();
    //=============================

        //===========================
    //objTime->setType(XSD_TIME);
    /*GMT in Z format*/
    //objTime->setValue("2003-03-24Z");
    /*GMT in +/- format*/
    //objTime->setValue("2003-03-24+5:30");
    /*no timezone specified. assumed localtime*/
    //objTime->setValue("2003-03-24");
    //objTime->mkCTime();
    //=============================

        //===========================
    //objTime->setType(XSD_TIME);
    /*GMT in Z format*/
    //objTime->setValue("21:55:56Z");
    /*GMT in +/- format*/
    //objTime->setValue("T21:55:56+5:30");
    /*no timezone specified. assumed localtime*/
    //objTime->setValue("T21:55:56");
    //objTime->mkCTime();
    //===========================

    //==========================
    //objTime->setType(XSD_DURATION);
    /*Duration in PnYnMnDTnHnMnS format*/
    //objTime->setValue("P100000Y3M21DT11H33M44S");
    //AxisString str = objTime->serialize("", objTime->m_Duration, XSD_DURATION);
    //printf("serialized string is: %s\n", str.c_str());

    //==============================
    //return 0;
//}
