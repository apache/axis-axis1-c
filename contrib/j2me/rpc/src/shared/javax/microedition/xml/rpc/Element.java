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

package javax.microedition.xml.rpc;

import javax.xml.namespace.QName;

/**
 * The class Element is a special Object used to represent an xsd:element defined in a Web Service's WSDL definition. An element can have the additional properties of being an array, being nillable, and has minOccurs and maxOccurs values. 
 * @author Ias (iasandcb@tmax.co.kr)
 * 
 */
public class Element extends Type {

    /** The Type of this Element's content. */
	public final Type contentType;
    /** True if this element is an array */
    public final boolean isArray;
    /** True if this element is nillable */
    public final boolean isNillable;
    /** True if this element is optional, that is, its minOccurs is defined as being 0. */
    public final boolean isOptional;
    /** The 'minOccurs' attribute of this element. Default value of 1, if this element has no 'minOccurs' attribute. */
	public final int minOccurs;
    /** The 'maxOccurs' attribute of this element. Default value of 1, if this element has no 'maxOccurs' attribute. */
	public final int maxOccurs;
    /** The QName of this element */
	public final QName name;
    /** Constant used to indicate that maxOccurs is unbounded. */
	public static final int UNBOUNDED = -1;
	
    /**
     * Construct an Element with the given properties. The defaults for the unspecified properties are:
     * minOccurs = 1
     * maxOccurs = 1
     * isOptional = false
     * isArray = false
     * isNillable = false
     * This Type subclass will have a value of 9.  
     * @param name - the QName of this element
     * @param type - the Type of this element's content 
     */
	public Element(QName name, Type type) {
		this(name, type, 1, 1, false);
	}

    /**
     * Construct an Element with the given properties. This Type subclass will have a value of 9. 
     * @param name - the QName of this element
     * @param type - the Type of this element's content 
     * @param minOccurs - indicates the minimum number of times this element can occur. A value of '0' indicates this element is optional.
     * @param maxOccurs - indicates the maximum number of times this element can occur. A value > 1 or equal to UNBOUNDED indicates this element is an array.
     * @param nillable - indicates if this element may have the xsd:nil attribute equal true. 
     */
	public Element(QName name, Type type, int minOccurs, int maxOccurs, boolean nillable) {
		super(9);
		if (name == null) {
			throw new IllegalArgumentException("invalid name");
		} else {
			this.name = name;
		}
		
		if ((type == null) || (type instanceof Element)) {
			throw new IllegalArgumentException("invalid type");
		} else {
			this.contentType = type;
		}
		
		if ((minOccurs < 0) || ((minOccurs > maxOccurs) && (maxOccurs != UNBOUNDED))) {
			throw new IllegalArgumentException("invalid minOccurs");
		} else {
			this.minOccurs = minOccurs;
		}

        if (minOccurs == 0) {
            isOptional = true;
        } else {
            isOptional = false;
        }

        if (maxOccurs == 0) {
			throw new IllegalArgumentException("invalid maxOccurs");
		} else {
			this.maxOccurs = maxOccurs;
		}
		
		if (maxOccurs > 1 || maxOccurs == UNBOUNDED) {
			isArray = true;
		} else {
			isArray = false;
		}

		this.isNillable = nillable;		
		
	}
}
