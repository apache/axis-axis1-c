/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
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
 *    Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
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
 */

package org.apache.axismora.wrappers.simpleType;

import java.io.IOException;

import org.apache.axis.AxisFault;
import org.apache.axis.encoding.SerializationContext;

import org.apache.axismora.MessageContext;
import org.apache.axismora.encoding.InOutParameter;
import org.apache.axismora.encoding.InParameter;
import org.apache.axis.message.SOAPFault;

/**
 * Created on Sep 18, 2003
 * @author vtpavan(vtpavan@opensource.lk)
 * @see <a href="http://www.w3.org/TR/xmlschema-2/#duration">XML Schema 3.2.6</a>
 */
public class DurationParam implements InOutParameter {
    private boolean isNegative = false;
    private int years;
    private int months;
    private int days;
    private int hours;
    private int minutes;
    private double seconds;
    private String param;

    public DurationParam() {
    }
    public DurationParam(MessageContext msgdata) {
        try {
            this.desierialize(msgdata);
        } catch (AxisFault e) {
            msgdata.setSoapFault(new SOAPFault(e));
        }

    }

    public DurationParam(
        boolean negative,
        int aYears,
        int aMonths,
        int aDays,
        int aHours,
        int aMinutes,
        double aSeconds) {
        isNegative = negative;
        years = aYears;
        months = aMonths;
        days = aDays;
        hours = aHours;
        minutes = aMinutes;
        seconds = aSeconds;
    }
    public DurationParam(String source) {
        this.setSource(source);
    }
    public void setSource(String source) throws IllegalArgumentException {
        int position = 1;
        int timePosition = source.indexOf("T");

        if (source.indexOf("P") == -1)
            throw new IllegalArgumentException("badformat");

        if (source.startsWith("-")) {
            isNegative = true;
            position++;
        }

        if (timePosition != -1)
            parseTime(source.substring(timePosition + 1));
        else
            timePosition = source.length();

        parseDate(source.substring(position, timePosition));
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.encoding.InOutParameter#desierialize(org.apache.axismora.MessageData)
     */
    public InParameter desierialize(MessageContext msgdata) throws AxisFault {
        String value = msgdata.nextText();
        this.setSource(value);
        this.param = this.toString();
        return this;
    }

    /* (non-Javadoc)
     * @see org.apache.axismora.encoding.Parameter#serialize(org.apache.axis.encoding.SerializationContext)
     */
    public void serialize(SerializationContext context) {
        String type_name = "Duration";
        StringBuffer buf = new StringBuffer();
        buf.append("<Duration xsi:type=\"ns1:").append(type_name + "\" xmlns:ns1 =\"");
        buf.append(org.apache.axis.Constants.URI_2001_SCHEMA_XSD + "/#duration\">");
        buf.append(param);
        buf.append("</Duration>\n");
        try {
            context.writeString(buf.toString());
        } catch (IOException e) {
            e.printStackTrace(); //ioexception
        }
    }

    /**
     * This method takes a string that represents an xsd:duration and parses it.
     *
     * @param duration
     * @throws SchemaException if the string doesn't parse correctly.
     */
    public void setDuration(String duration) throws IllegalArgumentException {
        int position = 1;
        int timePosition = duration.indexOf("T");

        if (duration.indexOf("P") == -1)
            throw new IllegalArgumentException("wrong format");

        if (duration.startsWith("-")) {
            isNegative = true;
            position++;
        }

        if (timePosition != -1)
            parseTime(duration.substring(timePosition + 1));
        else
            timePosition = duration.length();

        parseDate(duration.substring(position, timePosition));
    }

    /**
     * This method parses the time portion of a duration.
     *
     * @param time
     */
    public void parseTime(String time) {
        int start = 0;
        int end = time.indexOf("H");

        if (end != -1) {
            hours = Integer.parseInt(time.substring(0, end));
            start = end + 1;
        }

        end = time.indexOf("M");

        if (end != -1) {
            minutes = Integer.parseInt(time.substring(start, end));
            start = end + 1;
        }

        end = time.indexOf("S");

        if (end != -1)
            seconds = Double.parseDouble(time.substring(start, end));
    }

    /**
     * This method parses the date portion of a duration.
     *
     * @param date
     */
    public void parseDate(String date) {
        int start = 0;
        int end = date.indexOf("Y");

        if (end != -1) {
            years = Integer.parseInt(date.substring(0, end));
            start = end + 1;
        }

        end = date.indexOf("M");

        if (end != -1) {
            months = Integer.parseInt(date.substring(start, end));
            start = end + 1;
        }

        end = date.indexOf("D");

        if (end != -1)
            days = Integer.parseInt(date.substring(start, end));
    }

    /**
     * This returns the xml representation of an xsd:duration object.
     */
    public String toString() {
        StringBuffer duration = new StringBuffer();

        duration.append("P");

        if (years != 0)
            duration.append(years + "Y");

        if (months != 0)
            duration.append(months + "M");

        if (days != 0)
            duration.append(days + "D");

        if (hours != 0 || minutes != 0 || seconds != 0.0) {
            duration.append("T");

            if (hours != 0)
                duration.append(hours + "H");

            if (minutes != 0)
                duration.append(minutes + "M");

            if (seconds != 0) {
                if (seconds == (int) seconds)
                    duration.append((int) seconds + "S");
                else
                    duration.append(seconds + "S");
            }
        }

        if (duration.length() == 1)
            duration.append("T0S");

        if (isNegative)
            duration.insert(0, "-");

        return duration.toString();
    }

    public String getParam() {
        return this.param;

    }
}