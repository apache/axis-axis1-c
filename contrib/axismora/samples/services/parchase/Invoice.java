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

package services.parchase;

import org.apache.axis.AxisFault;

/* parameter class */
public class Invoice implements org.apache.axismora.encoding.InOutParameter {
    private double prize;
    private java.lang.String itemcode;
    private int amountSent;
    private double totel;
    public Invoice() {
    }
    public Invoice(
        String itemCode,
        int amountSent,
        double pize,
        double totel) {
        this.itemcode = itemCode;
        this.amountSent = amountSent;
        this.prize = pize;
        this.totel = totel;
    }
    public org.apache.axismora.encoding.InParameter desierialize(
        org.apache.axismora.MessageContext msgdata)
        throws AxisFault {
        int count = 4;
        int lock = 0;

        org.apache.axismora.soap.XMLTextData data = msgdata.getTag();
        while (count != 0
            && data.getType() != org.xmlpull.v1.XmlPullParser.END_DOCUMENT) {
            //this is add for security sake
            lock++;
            if (lock == 1000000)
                break;
            if (data.getType() == org.xmlpull.v1.XmlPullParser.START_TAG
                && data.getLocalpart().equals("prize")) {
                count--;
                this.prize =
                    (new org
                        .apache
                        .axismora
                        .wrappers
                        .simpleType
                        .DoubleParam(msgdata))
                        .getParam();
            } else if (
                data.getType() == org.xmlpull.v1.XmlPullParser.START_TAG
                    && data.getLocalpart().equals("itemcode")) {
                count--;
                this.itemcode =
                    (new org
                        .apache
                        .axismora
                        .wrappers
                        .simpleType
                        .StringParam(msgdata))
                        .getParam();
            } else if (
                data.getType() == org.xmlpull.v1.XmlPullParser.START_TAG
                    && data.getLocalpart().equals("amountSent")) {
                count--;
                this.amountSent =
                    (new org
                        .apache
                        .axismora
                        .wrappers
                        .simpleType
                        .IntParam(msgdata))
                        .getParam();
            } else if (
                data.getType() == org.xmlpull.v1.XmlPullParser.START_TAG
                    && data.getLocalpart().equals("totel")) {
                count--;
                this.totel =
                    (new org
                        .apache
                        .axismora
                        .wrappers
                        .simpleType
                        .DoubleParam(msgdata))
                        .getParam();
            }
            data = msgdata.getTag();
        } //end of while
        return this;
    }
    public void serialize(
        org.apache.axis.encoding.SerializationContext context) {
        try {
            javax.xml.namespace.QName qname =
                org
                    .apache
                    .axismora
                    .wsdl2ws
                    .info
                    .TypeMap
                    .getBasicTypeQname4class(
                    this.getClass().getName());
            String m_URI;
            String type_name;
            if (qname == null) {
                m_URI = "urn:Example6";
                type_name = "Broker";
            } else {
                m_URI = qname.getNamespaceURI();
                type_name = qname.getLocalPart();
            }
            //write start tag
            context.writeString(
                "<prf:" + type_name + "  xmlns:prf =\"" + m_URI + "\">");
            //write the parameters
            context.writeString("<prize>");
            context.writeString(String.valueOf(prize));
            context.writeString("</prize>");
            context.writeString("<itemcode>");
            context.writeString(String.valueOf(itemcode));
            context.writeString("</itemcode>");
            context.writeString("<amountSent>");
            context.writeString(String.valueOf(amountSent));
            context.writeString("</amountSent>");
            context.writeString("<totel>");
            context.writeString(String.valueOf(totel));
            context.writeString("</totel>");
            //write the end tag
            context.writeString("</prf:" + type_name + ">");
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }
    /**
     * @return
     */
    public int getAmountSent() {
        return amountSent;
    }

    /**
     * @return
     */
    public java.lang.String getItemcode() {
        return itemcode;
    }

    /**
     * @return
     */
    public double getPrize() {
        return prize;
    }

    /**
     * @return
     */
    public double getTotel() {
        return totel;
    }

    /**
     * @param i
     */
    public void setAmountSent(int i) {
        amountSent = i;
    }

    /**
     * @param string
     */
    public void setItemcode(java.lang.String string) {
        itemcode = string;
    }

    /**
     * @param d
     */
    public void setPrize(double d) {
        prize = d;
    }

    /**
     * @param d
     */
    public void setTotel(double d) {
        totel = d;
    }

}
