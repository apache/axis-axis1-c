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

package org.apache.axismora.util;

import java.io.IOException;
import java.util.Vector;

import org.apache.axis.AxisFault;
import org.w3c.dom.Element;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

/**
 * @author Dimuthu Leelarathne. (muthulee@opensource.lk)
 *
 */
public class Parser2Element {

    /**
     * Cursor must be positioned at the start tag of the desired root element.
     * Otherwise this utility method would not work properly.
     * 
     * @param eleNameSpace
     * @param eleName
     * @param xpp
     * @return
     */
    public static Element[] RootElement2ChildElements(
        String eleNameSpace,
        String eleName,
        XmlPullParser xpp)
        throws AxisFault {

        if (eleNameSpace == null) {
            eleNameSpace = ""; // because pull parser returns a ""
        }

        Vector elements = new Vector();
        try {
            int state = xpp.getEventType();

            if (state == XmlPullParser.START_TAG) {
                if (xpp.getName() == eleName) {
                    state = xpp.next();
                } else {
                    throw new AxisFault("Cursor is not positioned! Element name and the xpp pull parser's local name do not match !! ");
                }

            } else {
                throw new AxisFault("Cursor is not positioned on a start tag!!! You must put the cursor on the the start tag of the Root element. ");
            }

            int i = 0;
            while (state != XmlPullParser.END_DOCUMENT) {
                if (state == XmlPullParser.END_TAG) {
                    if (xpp.getNamespace() == eleNameSpace && xpp.getName() == eleName) {
                        Element[] eleArry = new Element[i];
                        for (int j = 0; j < i; j++) {
                            eleArry[j] = (Element) elements.get(j);
                        }
                        return eleArry;
                    }
                } else if (state == XmlPullParser.START_TAG) {
                    elements.add((Object) AxisUtils.make(xpp));
                    i++;
                    state = xpp.getEventType();
                    continue;
                } else {
                }
                state = xpp.next();
            } // end of while
            throw new AxisFault("End of the document is reached while trying to Serialize into a Element[] at util.Parser2Element");
        } catch (IOException e1) {
            e1.printStackTrace();
            throw new AxisFault("Error at util.Parser2Element", e1);
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw new AxisFault("Error at util.Parser2Element", e);
        }

    } //RootElement2ChildElement

}
