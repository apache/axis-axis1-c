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
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axis.Constants;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axismora.encoding.Serializable;
import org.apache.axismora.util.UtilityPool;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class SOAPMessageContext {
	private SOAPEnvelope envelope;
	private ArrayList soapHeaders = UtilityPool.getArrayList();
	private ArrayList soapbodyContent = UtilityPool.getArrayList();
	
	public SOAPMessageContext(SOAPEnvelope envelope){
		this.envelope = envelope;
	}
	
	public void addBodyPart(Serializable part){
		this.soapbodyContent.add(part);
	}
	
	public void addHeader(Serializable part){
			this.soapHeaders.add(part);
	}
	
	public void serialize(org.apache.axis.encoding.SerializationContext context)throws IOException{
		String envelopeURI = envelope.getSOAPConstants().getEnvelopeURI();
		
		StringBuffer sbuf =  new StringBuffer();
		sbuf.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		sbuf.append("<env:").append(Constants.ELEM_ENVELOPE).append(" ");
		sbuf.append("xmlns:env = ").append("\"").append(envelopeURI).append("\" ");
		
		Iterator prefixs = envelope.getNamespacePrefixes();
		while(prefixs.hasNext()){
			String prefix = (String)prefixs.next();
			String uri = envelope.getNamespaceURI(prefix);
			if(!envelopeURI.equals(uri))
				sbuf.append(" xmlns:").append(prefix).append(" = ").append("\"").append(uri).append("\" ");
		}
		sbuf.append(">\n");
		context.writeString(sbuf.toString());
		sbuf.delete(0,sbuf.length()-1);
		
		if(soapHeaders != null && soapHeaders.size() > 0){
			sbuf.append("<env:").append(Constants.ELEM_HEADER).append(">\n");
			context.writeString(sbuf.toString());
			sbuf.delete(0,sbuf.length()-1);
			
			int size = soapHeaders.size();
			for(int i = 0;i< size;i++){
				((Serializable)soapHeaders.get(i)).serialize(context);
			}
			
			sbuf.append("</env:").append(Constants.ELEM_HEADER).append(">\n");
		}
		sbuf.append("<env:").append(Constants.ELEM_BODY).append(">\n");
		context.writeString(sbuf.toString());
		sbuf.delete(0,sbuf.length()-1);
		
		int size = soapbodyContent.size();
		for(int i = 0;i< size;i++){
			((Serializable)soapbodyContent.get(i)).serialize(context);
		}
		
		sbuf.append("</env:").append(Constants.ELEM_BODY).append(">\n");
		sbuf.append("</env:").append(Constants.ELEM_ENVELOPE).append(">\n");
		context.writeString(sbuf.toString());
		sbuf.delete(0,sbuf.length()-1);
	} 
	
	public void finish(){
		UtilityPool.returnArrayList(soapbodyContent);
		UtilityPool.returnArrayList(soapHeaders);
	}
}
