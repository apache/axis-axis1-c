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
import java.io.IOException;

import javax.xml.namespace.QName;

import org.apache.axismora.soap.XMLTextData;
import org.apache.axismora.util.Parser2Element;

import org.apache.axis.AxisFault;
import org.apache.axis.soap.SOAPConstants;
import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

/**
 * @author Dimuthu Leelarathne(muthulee@opensource.lk)
 */

public class DeserializationMethods {

    private static int blindLevel;
    private int state = 0;
    private XmlPullParserFactory factory;
    private XmlPullParser xpp;

    public DeserializationMethods(String file)
        throws XmlPullParserException, IOException {
        this.factory = XmlPullParserFactory.newInstance();
        this.factory.setNamespaceAware(true);
        xpp = factory.newPullParser();
        xpp.setInput(new FileReader(file));
        this.state = xpp.next();
        System.out.println("" + xpp.getText());
    }

    public void resetBlindLevel() {
        blindLevel = 0;
    }

    //	   for dynamic structrues one after another
    //	   cannot support for dynamic structures withing dynamicstructures
    public String getValueOREnd() throws Exception {

        String value = null;

        while (this.state != XmlPullParser.END_DOCUMENT) {
            if (this.state == XmlPullParser.TEXT && xpp.isWhitespace() == false) {
                value = xpp.getText();
                if (value != null) {
                    this.state = xpp.next();
                    return value;
                }
            } else if (this.state == XmlPullParser.END_TAG) {
                if (blindLevel > 1) {
                    blindLevel--;
                } else if (blindLevel == 1) {
                    blindLevel--;
                    this.state = xpp.next();
                    return null;
                } else {
                    throw (new Exception("Cannot find a start of element"));
                }
            } else if (this.state == XmlPullParser.START_TAG) {
                blindLevel++;
            } else { // other stuff
                // do nothing
            }
            this.state = xpp.next();
        } //end of while
        throw (new XmlPullParserException("OOps !! End of the document"));
    }

    //	   convieniece method
    private void moveCursorToSameLevelOrStart(int level)
        throws XmlPullParserException, IOException {
        System.out.println("Vadagath !!");
        while (this.state != XmlPullParser.END_DOCUMENT) {
            if (this.state == XmlPullParser.START_TAG || level == 0) {
                this.state = xpp.next();
                return;
            }
            if (this.state == XmlPullParser.END_TAG)
                level--;
            this.state = xpp.next();
        } // end of while
        throw (new XmlPullParserException("Oops !! 123end of the document"));
    }

    public AxisFault parseFault() throws AxisFault {
        AxisFault af = new AxisFault();
        SOAPConstants soapConstants = SOAPConstants.SOAP11_CONSTANTS;

        try {
            while (this.state != XmlPullParser.END_DOCUMENT) {
                if (this.state == XmlPullParser.START_TAG) {
                    if ((xpp.getName().equals("Fault"))
                        && soapConstants.getEnvelopeURI().equals(xpp.getNamespace()))
                        this.state = xpp.next();
                    break;
                }
                this.state = xpp.next();
            }

            while (this.state != XmlPullParser.END_DOCUMENT) {
                if (this.state == XmlPullParser.START_TAG) {
                    if (xpp.getName().equals("faultcode")) {
                        String nspace = xpp.getNamespace();
                        String code = getValue();
                        af.setFaultCode(new QName(nspace, code));
                    } else if (xpp.getName().equals("faultstring")) {
                        af.setFaultString(getValue());
                    } else if (xpp.getName().equals("faultactor")) {
                        af.setFaultActor(getValue());
                    } else if (xpp.getName().equals("detail")) {
                        af.setFaultDetail(
                            Parser2Element.RootElement2ChildElements(
                                null,
                                "detail",
                                xpp));
                    } else {
                        this.state = xpp.next();
                        throw (
                            new AxisFault("Unexpected child element encountered in SoapFault"));
                    }

                } else if (this.state == XmlPullParser.END_TAG) {
                    if ((xpp.getName() == "Fault")
                        && soapConstants.getEnvelopeURI().equals(xpp.getNamespace())) {
                        this.state = xpp.next();
                        return af;
                    }
                } else {

                }
                this.state = xpp.next();
            } //while

        } catch (AxisFault e) {
            e.printStackTrace();
            throw e;
        } catch (IOException e) {
            e.printStackTrace();
            throw new AxisFault("Encountered error while deserializing SOAPFault", e);
        } catch (XmlPullParserException e) {
            e.printStackTrace();
            throw new AxisFault("Encountered error while deserializing SOAPFault", e);
        }
        throw new AxisFault("Oops!!! End of Document");
    } // parsefault

    public XMLTextData getTag() throws Exception {
        String value = null;
        String uri = null;
        String localName = null;
        String attrType = null;
        XMLTextData tag = null;
        while (this.state != XmlPullParser.END_DOCUMENT) {
            if (this.state == XmlPullParser.TEXT) {
                if (xpp.isWhitespace() == true) {
                    this.state = xpp.next();
                    continue;
                }
                value = xpp.getText();
                if (value != null) {
                    this.state = xpp.next();
                    continue;
                }
            } else if (this.state == XmlPullParser.START_TAG) {
                attrType =
                    xpp.getAttributeValue(
                        "http://www.w3.org/2001/XMLSchema-instance",
                        "type");
            } else {
                // do nothing
            }
            // bellow things should be done for all tags
            uri = xpp.getNamespace();
            localName = xpp.getName();
            tag = new XMLTextData(this.state, value, uri, localName, attrType);
            this.state = xpp.next();
            return tag;
        } //end of while
        throw (new XmlPullParserException("OOps !! End of the document"));
    }

    public String getValue(String uri, String localPart) throws Exception {
        String value = null;
        while (xpp.getEventType() != XmlPullParser.END_DOCUMENT) {
            if (xpp.getEventType() == XmlPullParser.TEXT
                && xpp.isWhitespace() == false) {
                value = xpp.getText();
                if (value != null) {
                    this.state = xpp.next();
                    return value;
                }
            } else if (xpp.getEventType() == XmlPullParser.END_TAG) {
                if (xpp.getNamespace() == uri && xpp.getName() == localPart) {
                    this.state = xpp.next();
                    return null;
                }
            } else {
            }
            this.state = xpp.next();
        } // end of while
        throw new XmlPullParserException("Opps !!!! End of the document");
    }

    public String getValue() throws IOException, XmlPullParserException {
        String value = null;

        while (this.state != XmlPullParser.END_DOCUMENT) {
            if (this.state == XmlPullParser.TEXT) {
                if (xpp.isWhitespace() == false) {
                    value = xpp.getText();
                    if (value != null) {
                        this.state = xpp.next();
                        return value;
                    } // null if		 
                } // white space
            } //text
            this.state = xpp.next();
        } //while			
        throw new XmlPullParserException("Oops get Value!!! End of Document");
    }

    public void mmmNext() throws Exception {
        this.state = xpp.next();
    }
}
