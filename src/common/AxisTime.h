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
 */

/**
 * @file AxisTime.h
 *
 * @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)
 *
 */
  
#ifndef __AXISTIME_H_OF_AXIS_INCLUDED_
#define __AXISTIME_H_OF_AXIS_INCLUDED_

#include <axis/server/TypeMapping.hpp>
#include <axis/server/IParam.hpp>
#include "Param.h"

using namespace std;

typedef struct
{
    time_t years;
    time_t months;
    time_t days;
    time_t hours;
    time_t mins;
    double secs;
} uDuration;


/**
 *  @class AxisTime
 *  @brief time manipulating helper class
 *
 *   
 *  @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)    
 */

AXIS_CPP_NAMESPACE_START

class AxisTime
{
    public:
        AxisTime();
        AxisTime(time_t ptrTime_t);
        AxisTime(struct tm ntime);
        virtual ~AxisTime();
        void setValue(const AxisChar* strValue);
        void setValue(XSDTYPE type, ParamValue Value);
        void setType(XSDTYPE m_Type);
        AxisString getValue();
        AxisString& serialize(struct tm tValue, 
            XSDTYPE nType);
        AxisString& serialize(long lDuration, XSDTYPE nType);
        double getDuration();
        struct tm getDateTime();
        struct tm getDate();
        struct tm getTime();
        int mkCTime();
        static struct tm deserialize(const AxisChar* strValue, XSDTYPE type);
        static long deserializeDuration(const AxisChar* strValue, 
            XSDTYPE type);

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
        time_t m_intYears;
        time_t m_intMonths;
        time_t m_intDays;
        time_t m_intHours;
        time_t m_intMins;
        time_t m_intSecs;
        AxisString strZone;
        uDuration duration;
        time_t m_longYears;
        double m_Duration;
        /* string strXSDDuration; */
        AxisString strXSDDuration;
        AxisString strXSDDate;
};

AXIS_CPP_NAMESPACE_END

#endif

