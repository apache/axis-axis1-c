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

package org.apache.axis.j2me.xml;

import java.util.Hashtable;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.SAXException;
import org.xml.sax.SAXNotRecognizedException;
import org.xml.sax.SAXNotSupportedException;

/**
 * This is an implementation of javax.xml.parsers.SAXParserFactory
 * @author Ias (iasandcb@tmax.co.kr)
 * 
 */
public class SAXParserFactoryImpl extends SAXParserFactory {

	/** SAX feature prefix ("http://xml.org/sax/features/"). */
	public static final String SAX_FEATURE_PREFIX = "http://xml.org/sax/features/";

	/** Namespaces feature ("namespaces"). */
	public static final String NAMESPACES_FEATURE = "namespaces";

	/** Namespace prefixes feature ("namespace-prefixes"). */
	public static final String NAMESPACE_PREFIXES_FEATURE = "namespace-prefixes";


	private Hashtable features;

    /**
     * a default constructor
     */
	public SAXParserFactoryImpl() {
		features = new Hashtable();
		features.put(SAX_FEATURE_PREFIX + NAMESPACES_FEATURE, new Boolean(true));
		features.put(SAX_FEATURE_PREFIX + NAMESPACE_PREFIXES_FEATURE, new Boolean(false));
	}
	/**
	 * @see javax.xml.parsers.SAXParserFactory#setFeature(java.lang.String, boolean)
	 */
	public void setFeature(String name, boolean value)
		throws ParserConfigurationException, SAXNotRecognizedException, SAXNotSupportedException {
		features.put(name, value ? new Boolean(true) : new Boolean(false));
	}

	/**
	 * @see javax.xml.parsers.SAXParserFactory#getFeature(java.lang.String)
	 */
	public boolean getFeature(String name)
		throws ParserConfigurationException, SAXNotRecognizedException, SAXNotSupportedException {
		Boolean value = (Boolean) features.get(name);
		return value.booleanValue();
	}

	/**
	 * @see javax.xml.parsers.SAXParserFactory#newSAXParser()
	 */
	public SAXParser newSAXParser() throws ParserConfigurationException, SAXException {
		return new SAXParserImpl(this);
	}
}
