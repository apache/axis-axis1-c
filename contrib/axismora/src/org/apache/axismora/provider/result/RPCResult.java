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

package org.apache.axismora.provider.result;

import java.io.IOException;

import javax.xml.namespace.QName;

import org.apache.axismora.encoding.OutParameter;
import org.apache.axismora.encoding.Serializable;
import org.apache.axismora.soap.BasicMessageContext;

import org.apache.axis.encoding.SerializationContext;

/**
 * This calss is used for the represents the RPC style result 
 *  @author Srianth Perera (hemapani@opensource.lk)
 */

public class RPCResult implements Serializable {
    private OutParameter parm;
    private QName method;
    private String xsiString; 

    public RPCResult(OutParameter param, QName method) {
        this.parm = param;
        this.method = method;
		//TODO write the xs String        
    }

    /**
     * this method is called by the SOAPHeaderElement when serializing
     */
    public void serialize(SerializationContext sc) throws IOException {
        StringBuffer buf = new StringBuffer();
        if (parm != null) {
            if (method != null) {
                //write start tag
                String uri = method.getNamespaceURI();
                if (uri != null && !("".equals(uri))) {
                    buf.append("<pre:").append(this.method.getLocalPart());
                    buf.append("Response xmlns:pre=\"").append(uri);
                    buf.append("\" xmlns:soapenc=\"");
                    buf.append(BasicMessageContext.SOAP_CONSTANTS.getEncodingURI());
                    buf.append("\">\n");
                } else {
                    buf.append("<").append(this.method.getLocalPart());
                  
                    buf.append("Response");
					buf.append(" xmlns:soapenc=\"");
					buf.append(BasicMessageContext.SOAP_CONSTANTS.getEncodingURI());
					buf.append("\">\n");
                }
                sc.writeString(buf.toString());
				sc.writeString("<retunValue>\n");
                //write body content
                parm.serialize(sc);
				sc.writeString("</retunValue>\n");
                //write ed tag
                buf = new StringBuffer();
                if (uri != null && !("".equals(uri))) {
                    buf.append("\n</pre:").append(this.method.getLocalPart());
                    buf.append("Response>\n");
                } else {
                    buf.append("\n</").append(this.method.getLocalPart());
                    buf.append("Response>\n");
                }
                sc.writeString(buf.toString());
            } else
                parm.serialize(sc);
        } else
            System.out.println("DEBUG - The param is null");
    }
}
