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

import javax.xml.namespace.QName;

import org.apache.axis.AxisFault;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.message.SOAPFault;

import org.apache.axismora.MessageContext;
import org.apache.axismora.encoding.InOutParameter;
import org.apache.axismora.encoding.InParameter;

/**
 * Created on Sep 29, 2003
 * @author vtpavan(vtpavan@opensource.lk)
 */
public class QNameParam implements InOutParameter {

    private QName param;

    /**
     * Constructor for the QName.
     *
     * @param localPart Local part of the QName
     */
    public QNameParam() {
    }
    public QNameParam(MessageContext msgcontext) {
        try {
            desierialize(msgcontext);
        } catch (AxisFault e) {
            msgcontext.setSoapFault(new SOAPFault(e));
        }
    }
    public QNameParam(String localPart) {
        param = new QName(localPart);
    }
    /**
     * Constructor for the QName.
     *
     * @param namespaceURI Namespace URI for the QName
     * @param localPart Local part of the QName.
     */
    public QNameParam(String namespaceURI, String localPart) {
        param = new QName(namespaceURI, localPart);

    }

    /* (non-Javadoc)
     * @see org.apache.axismora.encoding.OutParameter#serialize(org.apache.axis.encoding.SerializationContext)
     */
    public void serialize(SerializationContext context) throws IOException {
        String type_name = "QName";
        StringBuffer buf = new StringBuffer();
        buf.append("<QName xsi:type=\"ns1:").append(type_name + "\" xmlns:ns1 =\"");
        buf.append(org.apache.axis.Constants.URI_DEFAULT_SCHEMA_XSD + "/#QName\">");
        buf.append(this.toString());
        buf.append("</QName>");
        try {
            context.writeString(buf.toString());
        } catch (IOException e) {
            e.printStackTrace(); //ioexception
        }

    }

    /* (non-Javadoc)
     * @see org.apache.axismora.encoding.InParameter#desierialize(org.apache.axismora.MessageContext)
     */
    public InParameter desierialize(MessageContext msgcontext) throws AxisFault {
        String value = msgcontext.nextText();
        this.param = setSource(value);
        return this;
    }

    /**
     * Returns a string representation of this QName
     *
     * @return  a string representation of the QName
     */
    public String toString() {
        return param.toString();

    }

    public QName setSource(String s) {
        if ((s == null) || s.equals("")) {
            throw new IllegalArgumentException("invalid QName literal");
        }

        if (s.charAt(0) == '{') {
            int i = s.indexOf('}');

            if (i == -1) {
                throw new IllegalArgumentException("invalid QName literal");
            }

            if (i == s.length() - 1) {
                throw new IllegalArgumentException("invalid QName literal");
            } else {
                return new QName(s.substring(1, i), s.substring(i + 1));
            }
        } else {
            return new QName(s);
        }
    }

    public QName getParam() {
        return param;
    }

}
