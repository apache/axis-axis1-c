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
import java.text.NumberFormat;

import org.apache.axismora.MessageContext;
import org.apache.axismora.encoding.InOutParameter;
import org.apache.axismora.encoding.InParameter;

import org.apache.axis.AxisFault;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.message.SOAPFault;

/**
 * @author vtpavan(vtpavan@opensource.lk)
 * @see <a href="http://www.w3.org/TR/xmlschema-2/#gDay">XML Schema 3.2.13</a>
 */

public class DayParam implements InOutParameter {
    //private static XMLTextData tag;
    private int day;
    private String timezone = null;
    private String param;

    public DayParam() {
    }
    public DayParam(MessageContext msgcontext) throws AxisFault {
        try {
            desierialize(msgcontext);
        } catch (AxisFault e) {
            msgcontext.setSoapFault(new SOAPFault(e));
        }
    }
    public DayParam(String source) {
        this.setSource(source);
    }
    public DayParam(int day, String timeZone) {
        this.setDay(day);
        this.setTimezone(timeZone);
    }
    public void setSource(String source) throws NumberFormatException {
        if (source.length() < 5) {
            throw new NumberFormatException("wrong format");
        }

        if (source.charAt(0) != '-'
            || source.charAt(1) != '-'
            || source.charAt(2) != '-') {
            throw new NumberFormatException("wrong format");
        }

        setValue(Integer.parseInt(source.substring(3, 5)), source.substring(5));
    }
    public InParameter desierialize(MessageContext msgcontext) throws AxisFault {
        String value = msgcontext.nextText();
        this.setSource(value);
        this.param = this.toString();
        return this;

    }

    /* (non-Javadoc)
     * @see org.apache.axismora.encoding.Parameter#serialize(org.apache.axis.encoding.SerializationContext)
     *@see <a href="http://www.w3.org/TR/xmlschema-2/#gDay">XML Schema 3.2.13</a>
     */
    public void serialize(SerializationContext context) {
        String type_name = "Day";
        StringBuffer buf = new StringBuffer();
        buf.append("<Day xsi:type=\"ns1:").append(type_name + "\" xmlns:ns1 =\"");
        buf.append(org.apache.axis.Constants.URI_2001_SCHEMA_XSD + "/#gDay\">");
        buf.append(param);
        buf.append("</Day>\n");
        try {
            context.writeString(buf.toString());
        } catch (IOException e) {
            e.printStackTrace(); //ioexception
        }

    }

    public void setDay(int day) {
        // validate day
        if (day < 1 || day > 31) {
            throw new NumberFormatException("wrong format");
        }
        this.day = day;
    }

    public void setTimezone(String timezone) {
        // validate timezone
        if (timezone != null && timezone.length() > 0) {
            // Format [+/-]HH:MM
            if (timezone.charAt(0) == '+' || (timezone.charAt(0) == '-')) {
                if (timezone.length() != 6
                    || !Character.isDigit(timezone.charAt(1))
                    || !Character.isDigit(timezone.charAt(2))
                    || timezone.charAt(3) != ':'
                    || !Character.isDigit(timezone.charAt(4))
                    || !Character.isDigit(timezone.charAt(5)))
                    throw new NumberFormatException("badformat");

            } else if (!timezone.equals("Z")) {
                throw new NumberFormatException("wrong format");
            }
            // if we got this far, its good
            this.timezone = timezone;
        }
    }

    public void setValue(int day, String timezone) throws NumberFormatException {
        setDay(day);
        setTimezone(timezone);
    }
    public String toString() {
        // use NumberFormat to ensure leading zeros
        NumberFormat nf = NumberFormat.getInstance();
        nf.setGroupingUsed(false);

        // Day
        nf.setMinimumIntegerDigits(2);
        String s = "---" + nf.format(day);

        // timezone
        if (timezone != null) {
            s = s + timezone;
        }
        return s;
    }

    public String getParam() {
        return this.param;

    }
}