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
package org.apache.geronimo.ews.ws4j2ee.context.webservices.server;

import java.io.FileInputStream;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFDocument;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * This is the concrete implementation of the WSCFContext where the whole context of the
 * webservices.xml file will be published. The appropreate factory class will instanciate the class 
 * and in the factory a inputstream to the webservices.xml will be requires. This is not the 
 * starting point of the element tree, instead this s only giving an inteface
 * to the element tree which is rooted at WSCFDocument.
 *
 */
public class WSCFContextImpl implements WSCFContext {
	
	/**
	 * This reference will be the pointer to the element tree.
	 */
	private WSCFDocument document;
	
	/**
	 * The constructor that will create the element tree starting from the root element as WSCFDocument.
	 * @param document The document object to the webservices.xml
	 * @throws WSCFException 
	 */
	public WSCFContextImpl(FileInputStream in) throws WSCFException{
		this.document = (WSCFDocument) new WSCFDocumentImpl(in);
	}
	
	/**
	 * Interface support method. This will get the description element of the webservices.xml
	 */
	public String getDescription(){
		return this.document.getWebservices().getDescription();
	}
	
	/**
	 * Interface support method. This will get the display name element of the webservices.xml
	 */
	public String getDisplayName(){
		return this.document.getWebservices().getDisplayName();
	}
	
	/**
	 * Interface support method. This will get the small icon element of the webservices.xml
	 */
	public String getSmallIcon(){
		return this.document.getWebservices().getSmallIcon();
	}
	
	/**
	 * Interface support method. This will get the large icon element of the webservices.xml
	 */
	public String getLargeIcon(){
		return this.document.getWebservices().getLargeIcon();
	}
	
	/**
	 * Interface support method. This will get the webservice description elements of the webservices.xml as an array.
	 */
	public WSCFWebserviceDescription[] getWebServicesDescription(){
		return this.document.getWebservices().getWebServiceDescriptions();
	}
	public void serialize(java.io.Writer out) throws GenerationFault {
		  throw new UnsupportedOperationException();
	  }

	
}
