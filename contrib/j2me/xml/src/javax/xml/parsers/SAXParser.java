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

package javax.xml.parsers;

import java.io.IOException;
import java.io.InputStream;

import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

/**
 * Defines the API that wraps an {@link org.xml.sax.XMLReader}
 * implementation class. In JAXP 1.0, this class wrapped the
 * {@link org.xml.sax.Parser} interface, however this interface was
 * replaced by the {@link org.xml.sax.XMLReader}. For ease
 * of transition, this class continues to support the same name
 * and interface as well as supporting new methods.
 *
 * An instance of this class can be obtained from the
 * {@link javax.xml.parsers.SAXParserFactory#newSAXParser()} method.
 * Once an instance of this class is obtained, XML can be parsed from
 * a variety of input sources. These input sources are InputStreams,
 * Files, URLs, and SAX InputSources.<p>
 *
 *
 * As the content is parsed by the underlying parser, methods of the
 * given {@link org.xml.sax.HandlerBase} or the
 * {@link org.xml.sax.helpers.DefaultHandler} are called.<p>
 *
 * Implementors of this class which wrap an underlying implementation
 * can consider using the {@link org.xml.sax.helpers.ParserAdapter}
 * class to initially adapt their SAX1 impelemntation to work under
 * this revised class.<p>
 *
 * An implementation of <code>SAXParser</code> is <em>NOT</em> 
 * guaranteed to behave as per the specification if it is used concurrently by 
 * two or more threads. It is recommended to have one instance of the
 * <code>SAXParser</code> per thread or it is upto the application to 
 * make sure about the use of <code>SAXParser</code> from more than one
 * thread.
 *
 * @author Ias (iasandcb@tmax.co.kr)
 */

public abstract class SAXParser {

	protected SAXParser() {

	}

	/**
	 * Parse the content of the given {@link java.io.InputStream}
	 * instance as XML using the specified
	 * {@link org.xml.sax.helpers.DefaultHandler}.
	 *
	 * @param is InputStream containing the content to be parsed.
	 * @param dh The SAX DefaultHandler to use.
	 * @exception IOException If any IO errors occur.
	 * @exception IllegalArgumentException If the given InputStream is null.
	 * @exception SAXException If the underlying parser throws a
	 * SAXException while parsing.
	 * @see org.xml.sax.DocumentHandler
	 */

	public abstract void parse(InputStream is, DefaultHandler dh) throws SAXException, IOException;

	/**
	 * Parse the content given {@link org.xml.sax.InputSource}
	 * as XML using the specified
	 * {@link org.xml.sax.helpers.DefaultHandler}.
	 *
	 * @param is The InputSource containing the content to be parsed.
	 * @param dh The SAX DefaultHandler to use.
	 * @exception IOException If any IO errors occur.
	 * @exception IllegalArgumentException If the InputSource is null.
	 * @exception SAXException If the underlying parser throws a
	 * SAXException while parsing.
	 * @see org.xml.sax.DocumentHandler
	 */

	public abstract void parse(InputSource is, DefaultHandler dh) throws SAXException, IOException;

	/**
	 * Indicates whether or not this parser is configured to
	 * understand namespaces.
	 *
	 * @return true if this parser is configured to
	 *         understand namespaces; false otherwise.
	 */

	public abstract boolean isNamespaceAware();

	/**
	 * Indicates whether or not this parser is configured to
	 * validate XML documents.
	 *
	 * @return true if this parser is configured to
	 *         validate XML documents; false otherwise.
	 */

	public abstract boolean isValidating();

}
