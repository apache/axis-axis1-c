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

import java.io.InputStream;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFConstants;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFDocument;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebservices;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.Webservices;

/**
 * This will encapsulate the webservices.xml document and this is the start of the 
 * parsing tree.This will be used to support the the methods of the WSCFContext. The 
 * class tree and the Interface tree will strat from here and there will be sufficient
 * functionality provided by each class to expose the information and to further
 * drill down the element tree. 
 * 
 */
public class WSCFDocumentImpl implements WSCFConstants, WSCFDocument{

	/**
	 * Will keep a reference to the webservices element which is the document element in the webservices.xml
	 * @see org.apache.x.ws4j2ee.context.webservices.interfaces.WSCFWebservices
	 */
	private WSCFWebservices webservices;

/////////////////////////////////The jaxb delegation block////////////////////////////////////////////////

	//This is kept basically to meet the future demands of the serialising.
	private Webservices jaxbWebservices;

	public WSCFDocumentImpl(InputStream in)throws WSCFException{
		try{
			
			JAXBContext jc = JAXBContext.newInstance( "org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb" );
			// create an Unmarshaller
			Unmarshaller unmarshaller = jc.createUnmarshaller();
	
			// unmarshal a FooBar instance document into a tree of Java content
			// objects composed of classes from the example package.
			this.jaxbWebservices = (Webservices)unmarshaller.unmarshal(in);
			this.webservices = new WSCFWebservicesImpl(this.jaxbWebservices);
			
			
	//		  org.apache.x.ws4j2ee.context.webservices.jaxb.impl.DisplayNameTypeImpl dis = (org.apache.x.ws4j2ee.context.webservices.jaxb.impl.DisplayNameTypeImpl)ws.getDisplayName().get(0);
		} catch( JAXBException je ) {
			throw new WSCFException(je);
		} 
		
	}



//////////////////////////////////////////////////////////////////////////////////////////////////////////


//	/**
//	 * The constructor
//	 * @param doc org.w3c.dom.Document object of the webservices.xml
//	 * @throws WSCFException 
//	 */
//	public WSCFDocumentImpl(Document doc) throws WSCFException{
//		Element documentElement = doc.getDocumentElement();		
//		this.webservices = new WSCFWebservicesImpl(documentElement);
//		
//		
//	}
	/**
	 * Getter fo the Webservices element which is the document element of the 
	 * webservices.xml
	 * @return The Webservices object.
	 * @see org.apache.x.ws4j2ee.context.webservices.interfaces.WSCFWebservices
	 */
	public WSCFWebservices getWebservices() {
		return webservices;
	}

/**
 * @return
 */
public Webservices getJaxbWebservices() {
	return jaxbWebservices;
}

}
