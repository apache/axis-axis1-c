/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
package org.apache.axis.message;

import org.apache.axis.encoding.SerializationContext;
import org.apache.log4j.Category;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.rpc.namespace.QName;
import java.io.IOException;

public class SAXOutputter extends DefaultHandler
{
    static Category category =
            Category.getInstance(SAXOutputter.class.getName());
    
    SerializationContext context;
    
    public SAXOutputter(SerializationContext context)
    {
        this.context = context;
    }
    
    public void startDocument() throws SAXException {
    }
    
    public void endDocument() throws SAXException {
        if (category.isDebugEnabled()) {
            category.debug("SAXOutputter: end document.");
        }
    }
    
    public void startPrefixMapping(String p1, String p2) throws SAXException {
        context.registerPrefixForURI(p1,p2);
    }
    
    public void endPrefixMapping(String p1) throws SAXException {
        // !!!
    }
    
    public void characters(char[] p1, int p2, int p3) throws SAXException {
        if (category.isDebugEnabled()) {
            category.debug("(out) characters ['" +
                               new String(p1, p2, p3) + "']");
        }
        try {
            context.writeChars(p1, p2, p3);
        } catch (IOException e) {
            throw new SAXException(e);
        }
    }
    
    public void ignorableWhitespace(char[] p1, int p2, int p3) 
        throws SAXException
    {
        try {
            context.writeChars(p1, p2, p3);
        } catch (IOException e) {
            throw new SAXException(e);
        }
    }
 
    public void skippedEntity(String p1) throws SAXException {
    }
    
    public void startElement(String namespace, String localName,
                             String qName, Attributes attributes)
        throws SAXException
    {
        if (category.isDebugEnabled()) {
            category.debug("(out) startElement ['" + namespace + "' " +
                           localName + "]");
        }

        try {
            context.startElement(new QName(namespace,localName), attributes);
        } catch (IOException e) {
            throw new SAXException(e);
        }
    }
    
    public void endElement(String namespace, String localName, String qName)
        throws SAXException
    {
        if (category.isDebugEnabled()) {
            category.debug("(out) endElement ['" + namespace + "' " +
                           localName + "]");
        }
        
        try {
            context.endElement();
        } catch (IOException e) {
            throw new SAXException(e);
        }
    }
}
