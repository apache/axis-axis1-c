#ifndef __AXISTIME_H_INCLUDED_
#define __AXISTIME_H_INCLUDED_

#include <time.h>
#include <string>
#include "TypeMapping.h"
#include "IParam.h"

using namespace std;

typedef union uDuration
{
    int years;
    int months;
    int days;
    int hours;
    int mins;
    double secs;
} uDuration;

class AxisTime
{
    public:
        AxisTime();
        AxisTime(time_t ptrTime_t);
        AxisTime(struct tm ntime);
        virtual ~AxisTime();
        void setValue(const AxisChar* strValue);
        void setValue(XSDTYPE type, uParamValue Value);
        void setType(XSDTYPE m_Type);
        AxisString getValue();
        AxisString& serialize(const AxisString& sName, struct tm tValue);
        AxisString& serialize(const AxisString& sName, long lDuration);
        long getDuration();
        struct tm getDateTime();
        struct tm getDate();
        struct tm getTime();
        void mkCTime();

    private:
        void processValue();
        AxisString m_sValue;
        XSDTYPE m_Type;
        struct tm m_TM, m_TMUTC, m_TMDuration;
        time_t m_Time;
        char buf1[80];
        AxisString strYears;
        AxisString strMonths;
        AxisString strDays;
        AxisString strHours;
        AxisString strMins;
        AxisString strSecs;
        int intYears;
        int intMonths;
        int intDays;
        int intHours;
        int intMins;
        int intSecs;
        AxisString strZone;
        uDuration duration;
        long m_Duration;
        //string strXSDDuration;
        AxisString strXSDDuration;
        AxisString strXSDDate;
};

#endif