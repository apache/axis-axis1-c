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

package org.apache.axis.j2me.xml.sax;

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;

import org.xml.sax.Attributes;

/**
 * This is an implementation of org.xml.sax.Attributes
 * @author Ias (iasandcb@tmax.co.kr)
 * 
 */
public class AttributesImpl implements Attributes {

	private Vector keys;
	private Vector values;
	private Vector types;
	private Hashtable namespaces;
	private Hashtable typeDeclarations;

    /**
     * The concrete constructor for Attributes
     * @param namespaces
     * @param defaultValues
     * @param typeDefinitions
     */
	public AttributesImpl(Hashtable namespaces, Hashtable defaultValues, Hashtable typeDefinitions) {
		this.namespaces = namespaces;
		keys = new Vector();
		values = new Vector();
		types = new Vector();
		this.typeDeclarations = typeDefinitions;
		if (defaultValues != null) {
			Enumeration enum = defaultValues.keys();

			while (enum.hasMoreElements()) {
				String key = (String) enum.nextElement();
				add(key, getTypeFromDeclaration(key), (String) defaultValues.get(key));
			}
		}
	}
	
	public String getTypeFromDeclaration(String key) {
		String type = null;
		if (typeDeclarations != null) {
			type = (String) typeDeclarations.get(key);
		}
		if (type == null) {
			type = "CDATA";
		}
		return type;
	}
	
	public void add(String key, String type, String value) {
		keys.addElement(key);
		values.addElement(value);
		types.addElement(type);
	}
	/**
	 * @see org.xml.sax.Attributes#getLength()
	 */
	public int getLength() {
		return keys.size();
	}

	private String getPrefix(String qName) {
		String prefix;
		int colonIndex = qName.indexOf(":");
		if (colonIndex < 0) {
			prefix = "";
		} else {
			prefix = qName.substring(0, colonIndex);
		}
		return prefix;
	}

	private String getLocalName(String qName) {
		String localName;
		int colonIndex = qName.indexOf(":");
		if (colonIndex < 0) {
			localName = qName;
		} else {
			localName = qName.substring(colonIndex + 1);
		}
		return localName;
	}

	/**
	 * @see org.xml.sax.Attributes#getURI(int)
	 */
	public String getURI(int index) {
		if (index >= keys.size()) {
			return null;
		}
		String key = (String) keys.elementAt(index);
		String uri = (String) namespaces.get(getPrefix(key));
		if (uri == null) {
			uri = "";
		}
		return uri;
	}

	/**
	 * @see org.xml.sax.Attributes#getLocalName(int)
	 */
	public String getLocalName(int index) {
		return getLocalName((String) keys.elementAt(index));
	}

	/**
	 * @see org.xml.sax.Attributes#getQName(int)
	 */
	public String getQName(int index) {
		return (String) keys.elementAt(index);
	}

	/**
	 * @see org.xml.sax.Attributes#getType(int)
	 */
	public String getType(int index) {
		return (String) types.elementAt(index);
	}

	/**
	 * @see org.xml.sax.Attributes#getValue(int)
	 */
	public String getValue(int index) {
		return (String) values.elementAt(index);
	}

	/**
	 * @see org.xml.sax.Attributes#getIndex(java.lang.String, java.lang.String)
	 */
	public int getIndex(String uri, String localName) {
		String prefix = null;
		for (Enumeration uris = namespaces.elements(), prefixes = namespaces.keys(); uris.hasMoreElements();) {
			String namespaceUri = (String) uris.nextElement();
			String namespacePrefix = (String) prefixes.nextElement();
			if (namespaceUri.equals(uri)) {
				prefix = namespacePrefix;
				break;
			}
		}
		if (prefix == null) {
			return -1;
		}
		String qName;
		if (prefix.equals("")) {
			qName = localName;
		} else {
			qName = prefix + ":" + localName;
		}
		return getIndex(qName);
	}

	/**
	 * @see org.xml.sax.Attributes#getIndex(java.lang.String)
	 */
	public int getIndex(String qName) {
		return keys.indexOf(qName);
	}

	/**
	 * @see org.xml.sax.Attributes#getType(java.lang.String, java.lang.String)
	 */
	public String getType(String uri, String localName) {
		return (String) types.elementAt(getIndex(uri, localName));
	}

	/**
	 * @see org.xml.sax.Attributes#getType(java.lang.String)
	 */
	public String getType(String qName) {
		return (String) types.elementAt(getIndex(qName));
	}

	/**
	 * @see org.xml.sax.Attributes#getValue(java.lang.String, java.lang.String)
	 */
	public String getValue(String uri, String localName) {
		return (String) values.elementAt(getIndex(uri, localName));
	}

	/**
	 * @see org.xml.sax.Attributes#getValue(java.lang.String)
	 */
	public String getValue(String qName) {
		return (String) values.elementAt(getIndex(qName));
	}

}
