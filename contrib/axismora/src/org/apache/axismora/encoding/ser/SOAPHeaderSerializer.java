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

package org.apache.axismora.encoding.ser;

import java.io.IOException;
import java.util.Iterator;

import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.message.SOAPHeaderElement;
import org.apache.axismora.encoding.SOAPHeaderElementContent;
import org.apache.axismora.encoding.Serializable;
import org.w3c.dom.Element;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class SOAPHeaderSerializer implements Serializable{
	private SOAPHeaderElement soapHe;
	public SOAPHeaderSerializer(SOAPHeaderElement soapHe){
		this.soapHe = soapHe;
	}
    public void serialize(SerializationContext sc) throws IOException {
		StringBuffer sbuf =  new StringBuffer();
		String localName = soapHe.getName();
		String nsuri = soapHe.getNamespaceURI();
		String prefix = soapHe.getPrefix();
		if(prefix == null || prefix.length()< 1)
			sbuf.append('<').append(localName).append(" ");
		else
			sbuf.append('<').append(prefix).append(":").append(localName).append(" ");
		sbuf.append("xmlns:").append(" = ").append("\"").append(nsuri).append("\" ");
		
		Iterator prefixs = soapHe.getNamespacePrefixes();
		while(prefixs.hasNext()){
			String aPrefix = (String)prefixs.next();
			String uri = soapHe.getNamespaceURI(aPrefix);
			sbuf.append(" xmlns:").append(aPrefix).append(" = ").append("\"").append(uri).append("\" ");
		}
		sbuf.append(">\n");
		sc.writeString(sbuf.toString());
		sbuf.delete(0,sbuf.length()-1);
		
		SOAPHeaderElementContent h = (SOAPHeaderElementContent)soapHe.getObjectValue();
		  for (int i = 0; i < h.size(); i++) {
			  Element e = h.getElement(i);
			  sc.writeDOMElement(e);
		  }
		if(prefix == null || prefix.length()< 1)
			sbuf.append("</").append(localName).append("> ");
		else	
			sbuf.append("</").append(prefix).append(":").append(localName).append("> ");
		sc.writeString(sbuf.toString());
			
    }

}
