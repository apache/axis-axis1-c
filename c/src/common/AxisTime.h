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
 */
 
#ifndef __AXISTIME_H_INCLUDED_
#define __AXISTIME_H_INCLUDED_

#include <time.h>
#include <string>
#include <axis/common/TypeMapping.h>
#include <axis/common/IParam.h>

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
    @class AxisTime
    @brief time manipulating helper class

    
    @author Damitha Kumarage (damitha@opensource.lk, damitha@jkcsworld.com)    
*/
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
        AxisString& serialize(const AxisChar* sName, struct tm tValue, XSDTYPE nType);
        AxisString& serialize(const AxisChar* sName, long lDuration, XSDTYPE nType);
        long getDuration();
        struct tm getDateTime();
        struct tm getDate();
        struct tm getTime();
        int mkCTime();
		static struct tm Deserialize(const AxisChar* strValue, XSDTYPE type);
		static long DeserializeDuration(const AxisChar* strValue, XSDTYPE type);

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
        time_t m_Duration;
        //string strXSDDuration;
        AxisString strXSDDuration;
        AxisString strXSDDate;
};

#endif
