/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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

package org.apache.axis.encoding.ser;

import java.beans.IntrospectionException;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import org.apache.axis.InternalException;
import org.apache.axis.message.SOAPHandler;
import org.apache.axis.utils.JavaUtils;

import javax.xml.rpc.namespace.QName;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;

import org.apache.axis.encoding.Serializer;
import org.apache.axis.encoding.SerializerFactory;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.Deserializer;
import org.apache.axis.encoding.DeserializerFactory;
import org.apache.axis.encoding.DeserializationContext;
import org.apache.axis.encoding.DeserializerImpl;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.TimeZone;
/**
 * The DateSerializer deserializes a Date.  Much of the work is done in the 
 * base class.                                               
 *
 * @author Sam Ruby (rubys@us.ibm.com)
 * Modified for JAX-RPC @author Rich Scheuerle (scheu@us.ibm.com)
 */
public class DateDeserializer extends SimpleDeserializer {

    private static SimpleDateFormat zulu = 
        new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS'Z'");
                          //  0123456789 0 123456789

    private static Calendar calendar = new GregorianCalendar();

    static {
        zulu.setTimeZone(TimeZone.getTimeZone("GMT"));
    }

    /**
     * The Deserializer is constructed with the xmlType and 
     * javaType
     */
    public DateDeserializer(Class javaType, QName xmlType) {
        super(javaType, xmlType);
    }

    /**
     * The simple deserializer provides most of the stuff.
     * We just need to override makeValue().
     */
    public Object makeValue(String source) { 
        Date result;
        boolean bc = false;
        
        // validate fixed portion of format
        if ( source != null ) {
            if (source.charAt(0) == '+')
                source = source.substring(1);
            
            if (source.charAt(0) == '-') {
                source = source.substring(1);
                bc = true;
            }
            
            if (source.length() < 19) 
                throw new NumberFormatException(
                           JavaUtils.getMessage("badDateTime00"));
    
            if (source.charAt(4) != '-' || source.charAt(7) != '-' ||
                source.charAt(10) != 'T')
                throw new NumberFormatException(
                                                JavaUtils.getMessage("badDate00"));
            
            if (source.charAt(13) != ':' || source.charAt(16) != ':')
                throw new NumberFormatException(
                                                JavaUtils.getMessage("badTime00"));
        }
        
        // convert what we have validated so far
        try {
            result = zulu.parse(source == null ? null :
                                (source.substring(0,19)+".000Z") );
        } catch (Exception e) {
            throw new NumberFormatException(e.toString());
        }
        
        int pos = 19;
        
        // parse optional milliseconds
        if ( source != null ) {
            if (pos < source.length() && source.charAt(pos)=='.') {
                int milliseconds = 0;
                int start = ++pos;
                while (pos<source.length() && 
                       Character.isDigit(source.charAt(pos)))
                    pos++;
                
                String decimal=source.substring(start,pos);
                if (decimal.length()==3) {
                    milliseconds=Integer.parseInt(decimal);
                } else if (decimal.length() < 3) {
                    milliseconds=Integer.parseInt((decimal+"000")
                                                  .substring(0,3));
                } else {
                    milliseconds=Integer.parseInt(decimal.substring(0,3));
                    if (decimal.charAt(3)>='5') ++milliseconds;
                }
                
                // add milliseconds to the current result
                result.setTime(result.getTime()+milliseconds);
            }
            
            // parse optional timezone
            if (pos+5 < source.length() &&
                (source.charAt(pos)=='+' || (source.charAt(pos)=='-')))
                {
                    if (!Character.isDigit(source.charAt(pos+1)) || 
                        !Character.isDigit(source.charAt(pos+2)) || 
                        source.charAt(pos+3) != ':'              || 
                        !Character.isDigit(source.charAt(pos+4)) || 
                        !Character.isDigit(source.charAt(pos+5)))
                        throw new NumberFormatException(
                                                        JavaUtils.getMessage("badTimezone00"));
                    
                    int hours = (source.charAt(pos+1)-'0')*10
                        +source.charAt(pos+2)-'0';
                    int mins  = (source.charAt(pos+4)-'0')*10
                        +source.charAt(pos+5)-'0';
                    int milliseconds = (hours*60+mins)*60*1000;
                    
                    // subtract milliseconds from current result to obtain GMT
                    if (source.charAt(pos)=='+') milliseconds=-milliseconds;
                    result.setTime(result.getTime()+milliseconds);
                    pos+=6;  
                }
            
            if (pos < source.length() && source.charAt(pos)=='Z') pos++;
            
            if (pos < source.length())
                throw new NumberFormatException(
                                                JavaUtils.getMessage("badChars00"));
        }
        
        // support dates before the Christian era
        if (bc) {
            synchronized (calendar) {
                calendar.setTime(result);
                calendar.set(Calendar.ERA, GregorianCalendar.BC);
                result = calendar.getTime();
            }
        }
        
        return result;
    }
}
