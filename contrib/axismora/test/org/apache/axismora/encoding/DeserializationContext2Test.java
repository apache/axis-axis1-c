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
 
package org.apache.axismora.encoding;

import java.io.IOException;
import java.util.Vector;

import javax.xml.namespace.QName;

import junit.framework.TestCase;

import org.apache.axis.AxisFault;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

/**
 * @author Dimuthu Leelarathne.(muthulee@yahoo.com)
 */

public class DeserializationContext2Test extends TestCase {

    DesirializationContext ds = null;
    AxisPullParser parser = null;

    public DeserializationContext2Test() {
        try {
            ds =
                new DesirializationContext("test\\testData\\DeserializationAxisPull.txt");

        } catch (XmlPullParserException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void testAll() {
        try {

            super.assertEquals("Dimuthu", ds.nextText());

            super.assertEquals("2", ds.nextText());
            // checks for this null and "" business of namespace

            //get simpleValue called for a null
            super.assertEquals("", ds.getSimpleValue(new QName("", "op2")));

            // checks whether for a null between a start tag and end tag i.e.<something / >"" is returned.
            System.out.println(
                "Emty namespace and geting whitespace working with getSimpleValue");

            // simpleValue-next()-nextText()
            parser = ds.getAxisPullParser();
            super.assertEquals(XmlPullParser.START_TAG, parser.next());
            ds.setParser(parser.getParser());
            super.assertEquals("", ds.nextText().trim());

            //checks whether for a "" between a start tag and end tag "" is returned.

            // here we are at for windows <xsd:simpleType name="simpleDate"></xsd:simpleType>
            super.assertEquals("", ds.nextText().trim());

            // getSimpleValue test
            //nextText()-next()-SimpleValue()
            parser = ds.getAxisPullParser();
            super.assertEquals(XmlPullParser.START_TAG, parser.next());
            ds.setParser(parser.getParser());
            super.assertEquals(
                "3",
                ds.getSimpleValue(new QName("http://www.w3.org/2001/XMLSchema", "op3")));

            //getSimpleValue with null Namesapce.
            //getSimpleValue() , nextText();
            super.assertEquals("4", ds.getSimpleValue(new QName("", "op4")));
            super.assertEquals("", ds.nextText().trim()); // at op20

            parser = ds.getAxisPullParser();

            //op5 start tag to be read  
            super.assertEquals(parser.next(), XmlPullParser.START_TAG);

            //op5 endtag to be read
            super.assertEquals(parser.next(), XmlPullParser.END_TAG);

            //op6 start tag to be read
            super.assertEquals(parser.next(), XmlPullParser.START_TAG);
            // op6 end tag to be read
            super.assertEquals(parser.next(), XmlPullParser.END_TAG);
            // x start tag
            super.assertEquals(parser.next(), XmlPullParser.START_TAG);
            //y start tag
            super.assertEquals(parser.next(), XmlPullParser.START_TAG);
            // y end tag
            super.assertEquals(parser.next(), XmlPullParser.END_TAG);
            // x end tag 

            ds.setParser(parser.getParser());
            //check null behavior in getSimplevalue
            super.assertEquals(
                "",
                ds.getSimpleValue(
                    new QName("http://www.w3.org/2001/XMLSchema", "enumeration"))
                    .trim());

            super.assertEquals("", ds.getSimpleValue(new QName("", "op7")).trim());
            super.assertEquals("8", ds.nextText());

            Vector vec =
                ds.getValuesUntil(new QName("http://www.w3.org/2001/XMLSchema", "all"));
            System.out.println("vector size is ::" + vec.size());
            //super.assertEquals(vec.size(),9);

            for (int i = 0; i < vec.size(); i++) {
                System.out.print(
                    ""
                        + i
                        + "th Value in the vector is :: "
                        + (String) vec.get(i)
                        + "\n");
            }

            System.out.println("Nulls should be printed for last two values... ");
            parser = ds.getAxisPullParser();
            super.assertEquals("all", parser.getName());
            super.assertEquals(XmlPullParser.END_TAG, parser.next());
            ds.setParser(parser.getParser());

        } catch (AxisFault e) {
            e.printStackTrace();
        }
    }
}
