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

/**
 * @author Srianth Perera (hemapani@opensource.lk)
 */
public class ByteArrayParam implements InOutParameter {
    public byte[] param;

    public ByteArrayParam() {
    }

    public ByteArrayParam(MessageContext msgdata) throws AxisFault {
        desierialize(msgdata);
    }

    public ByteArrayParam(byte[] param) {
        this.param = param;
    }

    public void serialize(SerializationContext context) {
//        String type_name = org.apache.axis.Constants.XSD_BYTE.getLocalPart();
//        StringBuffer buf = new StringBuffer();
//        buf
//            .append("<byteArray xsi:type=\"ns1:")
//            .append(type_name)
//            .append("\" xmlns:ns1 =\"")
//            .append(Constants.DEFAULT_SIMPLETYPE_ENCODING_URI)
//            .append("\">");
//        buf.append(param);
//        buf.append("</byteArray>\n");
        try {
            context.writeString(new String(param));
        } catch (IOException e) {
            e.printStackTrace(); //ioexception
        }

    }

    /**
     * @return
     */
    public byte[] getParam() {
        return this.param;
    }

    public org.apache.axismora.encoding.InParameter desierialize(MessageContext msgdata)
        throws AxisFault {
        String value = msgdata.nextText();
        this.param = (value != null) ? value.getBytes() : new byte[] {
        };
        return this;
    }
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return new String(param);
	}

}
