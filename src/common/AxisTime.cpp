#include "AxisTime.h"
#include "AxisUtils.h"

AxisTime::AxisTime()
{
    
}

AxisTime::AxisTime(struct tm ntime)
{
    m_TMUTC = ntime;
}

AxisTime::AxisTime(time_t m_Time)
{
    if(m_Time != NULL)
    {
		tm* pTMUTC = gmtime(&m_Time);
		memcpy(&m_TMUTC, pTMUTC, sizeof(tm));
    }
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
    if(type = XSD_DURATION)
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
AxisString& AxisTime::serialize(const AxisString& sName, long lDuration)
{
        AxisChar buff[4];
        strXSDDuration = L"P";
        int x = 365 * 24 * 3600;
        int intYears = lDuration / x;
        //sprintf((char*)buff,"%d", intYears);
        AxisSprintf(buff, 4, L"%d", intYears);
        strXSDDuration.append(buff);
        lDuration = lDuration - (lDuration / x * x);
        x = 30 * 24 * 3600;
        int intMonths = lDuration / x;
        //sprintf((char*)buff,"%d", intMonths);
        AxisSprintf(buff, 4, L"%d", intMonths);
        strXSDDuration.append(buff);
        lDuration = lDuration - (lDuration / x * x);
        x = 24 * 3600;
        int intDays = lDuration / x;
        //sprintf((char*)buff,"%d", intDays);
        AxisSprintf(buff, 4, L"%d", intDays);
        strXSDDuration.append(buff);
        lDuration = lDuration - (lDuration / x * x);
        x = 3600;
        int intHours = lDuration / x;
        //sprintf((char*)buff,"%d", intHours);
        AxisSprintf(buff, 4, L"%d", intHours);
        strXSDDuration.append(buff);
        lDuration = lDuration - (lDuration / x * x);
        x = 60;
        int intMins = lDuration / x;
        //sprintf((char*)buff,"%d", intMins);
        AxisSprintf(buff, 4, L"%d", intMins);
        strXSDDuration.append(buff);
        int intSecs = lDuration - (lDuration / x * x);
        //sprintf((char*)buff,"%d", intSecs);
        AxisSprintf(buff, 4, L"%d", intSecs);
        strXSDDuration.append(buff);
        
        return strXSDDuration;
}

/**
* Serialize the c type tm struct into a xml date string.
* The serialized date will represent UTC time
*/
AxisString& AxisTime::serialize(const AxisString& sName, struct tm tValue)
{
        /*formats the output date in the format CCYY-MM-DDThh:mm:ssZ*/
        switch(m_Type)
        {
            case XSD_DATETIME:
                strftime(buf1, 80, "%Y-%m-%dT%H:%M:%SZ", &tValue);
                //strXSDDate = buf1;
                AxisUtils::convert(strXSDDate, buf1);
            case XSD_DATE:
                strftime(buf1, 80, "%Y-%m-%dZ", &tValue);
                //strXSDDate = buf1;
                AxisUtils::convert(strXSDDate, buf1);
            case XSD_TIME:
                strftime(buf1, 80, "%H:%M:%SZ", &tValue);
                //strXSDDate = buf1;
                AxisUtils::convert(strXSDDate, buf1);
            
        }
        
        return strXSDDate;
}

/**
* This function deserialize the xml datetime type into a c type
* tm struct. The struct tm created will contain the UTC time
*/
void AxisTime::mkCTime()
{
    AxisChar* endptr;
    int intPos, intPos1, intPos2, intPos3, intPos4, intPos5, intPos6;
    AxisChar buff[4];
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
            intPos1 = m_sValue.find_first_of(L"Y");
            strYears = m_sValue.substr(1,intPos1 - 1);
            //intYears = atoi(strYears.c_str());
            intYears = wcstol(strYears.c_str(), &endptr, 10);
            duration.years = intYears;
            intPos2 = m_sValue.find_first_of(L"M");
            strMonths = m_sValue.substr(intPos1 + 1, intPos2 - intPos1 - 1);
            //intMonths = atoi(strMonths.c_str());
            intMonths = wcstol(strMonths.c_str(), &endptr, 10);
            duration.months = intMonths;
            intPos3 = m_sValue.find_first_of(L"D");
            strDays = m_sValue.substr(intPos2 + 1, intPos3 - intPos2 -1);
            //intDays = atoi(strDays.c_str());
            intDays = wcstol(strDays.c_str(), &endptr, 10);
            duration.days = intDays;
            intPos4 = m_sValue.find_first_of(L"H");
            strHours = m_sValue.substr(intPos3 + 1, intPos4 - intPos3 -1);
            //intHours = atoi(strHours.c_str());
            intHours = wcstol(strHours.c_str(), &endptr, 10);
            duration.hours = intHours;
            intPos5 = m_sValue.find_first_of(L"M");
            strMins = m_sValue.substr(intPos4 + 1, intPos5 - intPos4 -1);
            //intMins = atoi(strMins.c_str());
            intMins = wcstol(strMins.c_str(), &endptr, 10);
            duration.mins = intMins;
            intPos6 = m_sValue.find_first_of(L"S");
            strSecs = m_sValue.substr(intPos5 + 1, intPos6 - intPos5 -1);
            //intSecs = atoi(strSecs.c_str());
            intSecs = wcstol(strSecs.c_str(), &endptr, 10);
            duration.secs = intSecs;

            break;
    
        case XSD_DATETIME:
    
            /*dismantle m_sValue to get tm value;
                XSD_DATETIME format is
                CCYY(-)MM(-)DDThh:mm:ss.ss...Z OR
                CCYY(-)MM(-)DDThh:mm:ss.ss...+/-<UTC TIME DIFFERENCE>            
            */        
            strYears = m_sValue.substr(0,2);
            //intYears = atoi(strYears.c_str()) - 1900;
            intYears = wcstol(strYears.c_str(), &endptr, 10) - 1900;
            //sprintf((char*)buff,"%d", intYears);
            AxisSprintf(buff, 4, L"%d", intYears);
            strYears = buff;
            intPos = m_sValue.find_first_of(L"-");
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

            //m_TM.tm_year = atoi(strYears.c_str());
            m_TM.tm_year = wcstol(strYears.c_str(), &endptr, 10);
            //m_TM.tm_mon = atoi(strMonths.c_str());
            m_TM.tm_mon = wcstol(strMonths.c_str(), &endptr, 10);
            //m_TM.tm_mday = atoi(strDays.c_str());
            m_TM.tm_mday = wcstol(strDays.c_str(), &endptr, 10);
            //m_TM.tm_hour = atoi(strHours.c_str());
            m_TM.tm_hour = wcstol(strHours.c_str(), &endptr, 10);
            //m_TM.tm_min = atoi(strMins.c_str());
            m_TM.tm_min = wcstol(strMins.c_str(), &endptr, 10);
            //m_TM.tm_sec = atoi(strSecs.c_str());
            m_TM.tm_sec = wcstol(strSecs.c_str(), &endptr, 10);

            /*if the timezone is represented adding 'Z' at the end*/
            if(strZone.substr(0,1) == L"Z")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }
            /*if the timezone is represented using +/-hh:mm format*/
            else if(strZone.substr(0,1) == L"+" ||strZone.substr(0,1) == L"-")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
                //intHours = atoi(strZone.substr(1,2).c_str());
                intHours = wcstol(strZone.substr(1,2).c_str(), &endptr, 10);
                //intMins = atoi(strZone.substr(3,2).c_str());
                intMins = wcstol(strZone.substr(3,2).c_str(), &endptr, 10);
                intSecs = intHours * 60 * 60 + intMins * 60;
                if(strZone.substr(0,1) == L"+")
                {
                    timeInSecs += intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));                
                }
                else if(strZone.substr(0,1) == L"-")
                {
                    timeInSecs -= intSecs;
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
            strYears = m_sValue.substr(0,2);
            //intYears = atoi(strYears.c_str()) - 1900;
            intYears = wcstol(strYears.c_str(), &endptr, 10) - 1900;
            //sprintf((char*)buff,"%d", intYears);
            AxisSprintf(buff, 4, L"%d", intYears);
            strYears = buff;
            intPos = m_sValue.find_first_of(L"-");
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

            //m_TM.tm_year = atoi(strYears.c_str());
            m_TM.tm_year= wcstol(strYears.c_str(), &endptr, 10);
            //m_TM.tm_mon = atoi(strMonths.c_str());
            m_TM.tm_mon = wcstol(strMonths.c_str(), &endptr, 10);
            //m_TM.tm_mday = atoi(strDays.c_str());
            m_TM.tm_mday = wcstol(strDays.c_str(), &endptr, 10);

            /*if the timezone is represented adding 'Z' at the end*/
            if(strZone.substr(0,1) == L"Z")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }
            /*if the timezone is represented using +/-hh:mm format*/
            else if(strZone.substr(0,1) == L"+" ||strZone.substr(0,1) == L"-")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
                //intHours = atoi(strZone.substr(1,2).c_str());
                intHours = wcstol(strZone.substr(1,2).c_str(), &endptr, 10);
                //intMins = atoi(strZone.substr(3,2).c_str());
                intMins = wcstol(strZone.substr(3,2).c_str(), &endptr, 10);
                intSecs = intHours * 60 * 60 + intMins * 60;
                if(strZone.substr(0,1) == L"+")
                {
                    timeInSecs += intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));                
                }
                else if(strZone.substr(0,1) == L"-")
                {
                    timeInSecs -= intSecs;
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

            //m_TM.tm_hour = atoi(strHours.c_str());
            m_TM.tm_hour = wcstol(strHours.c_str(), &endptr, 10);
            //m_TM.tm_min = atoi(strMins.c_str());
            m_TM.tm_min = wcstol(strMins.c_str(), &endptr, 10);
            //m_TM.tm_sec = atoi(strSecs.c_str());
            m_TM.tm_sec = wcstol(strSecs.c_str(), &endptr, 10);

            /*if the timezone is represented adding 'Z' at the end*/
            if(strZone.substr(0,1) == L"Z")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
            }
            /*if the timezone is represented using +/-hh:mm format*/
            else if(strZone.substr(0,1) == L"+" ||strZone.substr(0,1) == L"-")
            {
                time_t timeInSecs = mktime(&m_TM);
				pTm = localtime(&timeInSecs);
				memcpy(&m_TMUTC, pTm, sizeof(tm));
                //intHours = atoi(strZone.substr(1,2).c_str());
                intHours = wcstol(strZone.substr(1,2).c_str(), &endptr, 10);
                //intMins = atoi(strZone.substr(3,2).c_str());
                intMins = wcstol(strZone.substr(3,2).c_str(), &endptr, 10);
                intSecs = intHours * 60 * 60 + intMins * 60;
                if(strZone.substr(0,1) == L"+")
                {
                    timeInSecs += intSecs;
					pTm = localtime(&timeInSecs);
					memcpy(&m_TM, pTm, sizeof(tm));
                    time_t t = mktime(&m_TM);
                    t = abs(t - d);
					pTm = gmtime(&t);
					memcpy(&m_TMUTC, pTm, sizeof(tm));                
                }
                else if(strZone.substr(0,1) == L"-")
                {
                    timeInSecs -= intSecs;
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