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

import java.io.FileReader;
import java.io.InputStream;

import junit.framework.TestCase;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserFactory;

/**
 * This TestCase describes the behaviorsof the XMLPull.
 *  1) The curser moves with next()
 *  2) The getName(),getURI(),getAttributes() ...ect will not change the curser
 *  @author Dimuthu Leelarathne (muthulee@opensource.lk) Srinath Perera (hemapani@opensource.lk)
 */

public class XMLPullTest extends TestCase {
    private XmlPullParserFactory factory;
    private XmlPullParser xpp;
    private int eventType;
    private InputStream in;

    protected void setUp() throws Exception {
        System.out.println("seting up");
        try {
            FileReader in = new FileReader("./samples/web.xml");
            // create the parser
            XmlPullParserFactory factory =
                XmlPullParserFactory.newInstance(
                    System.getProperty(XmlPullParserFactory.PROPERTY_NAME),
                    null);
            factory.setNamespaceAware(true);
            factory.setFeature(XmlPullParser.FEATURE_PROCESS_NAMESPACES, true);
            this.xpp = factory.newPullParser();
            xpp.setInput(in);
            System.out.println("seting up done");
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public void testXMLPull() throws Exception {
        // move form initial position to first TAG
        int eventType = xpp.next();
        boolean isTextAllowed = false;

        while (eventType != XmlPullParser.END_DOCUMENT) {
            if (eventType == XmlPullParser.TEXT) {
                String val = xpp.getText();
                if (isTextAllowed && !("\n".equals(val)))
                    System.out.println("TEXT FOUND" + val);
            } else if (eventType == XmlPullParser.END_TAG) {
                isTextAllowed = false;
                System.out.println("END TAG " + xpp.getName());
            } else if (eventType == XmlPullParser.START_TAG) {
                System.out.println("START TAG " + xpp.getName());
                isTextAllowed = true;
            } else {
                System.out.println("OTHER" + xpp.getText() + eventType);
            }

            eventType = xpp.next();
        }
    }

    /* (non-Javadoc)
     * @see junit.framework.TestCase#tearDown()
     */
    protected void tearDown() throws Exception {

    }

}
