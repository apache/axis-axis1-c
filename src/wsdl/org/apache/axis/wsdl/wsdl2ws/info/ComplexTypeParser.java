/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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
 
/**
 * @author Srinath Perera(hemapani@openource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws.info;

/**
 * This class genarate a Type from the dom node given.
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ComplexTypeParser {
/**
 * According to the XML Schema Part 1: Structures W3C Recommendation 2 May 2001
 * <complexType 
 * 	abstract = boolean : false
 * 	block = (#all | List of (extension | restriction)) 
 * 	final = (#all | List of (extension | restriction)) 
 * 	id = ID 
 * 	mixed = boolean : false
 * 	name = NCName 
 * 	{any attributes with non-schema namespace . . .}>
 * 	Content: (annotation?, (simpleContent | complexContent | ((group | all | choice | sequence)?, ((attribute | attributeGroup)*, anyAttribute?))))
 * </complexType>
 * but the ws-i Basic Profile Version 1.0a Final Specification Date: 2003/08/08 17:00:01
 * impose following rules
 * 
 * WSDL 1.1 is unclear as to which schema target namespaces are suitable for QName references from a
 * WSDL element. The Profile allows QName references from WSDL elements both to the target namespace 
 * defined by the xsd:schema element, and to imported namespaces. Similar to XML Schema, namespaces not
 * referenced directly within the WSDL file (through the targetNamespace attribute on xsd:schema, or 
 * through the namespace attribute on xsd:import) are available for use in QName reference. 
 * QName references to namespaces that are only defined through a nested import are not allowed.
 *
 * R2101 A DESCRIPTION MUST NOT use QName references to elements in namespaces that have been neither 
 * imported, nor defined in the referring WSDL document.
 * R2102 A QName reference to a Schema component in a DESCRIPTION MUST use the namespace defined in the
 * targetNamespace attribute on the xsd:schema element, or to a namespace defined in the namespace attribute
 * on an xsd:import element within the xsd:schema element.
 * 


5.2.2 Schema targetNamespace Syntax


Requiring a targetNamespace on all xsd:schema elements that are children of wsdl:types is a good practice, places a minimal burden on authors of WSDL documents, and avoids the cases that are not as clearly defined as they might be. 


R2105 All xsd:schema elements contained in a wsdl:types element of a DESCRIPTION MUST have a targetNamespace attribute with a valid and non-null value, UNLESS the xsd:schema element has xsd:import and/or xsd:annotation as its only child element(s). 


5.2.3 soapenc:Array


The recommendations in WSDL 1.1 Section 2.2 for declaration of array types have been interpreted in various ways, leading to interoperability problems. Further, there are other clearer ways to declare arrays. 


R2110 In a DESCRIPTION, array declarations MUST NOT extend or restrict the soapenc:Array type. 


R2111 In a DESCRIPTION, array declarations MUST NOT use wsdl:arrayType attribute in the type declaration. 


R2112 In a DESCRIPTION, array declaration wrapper elements SHOULD NOT be named using the convention ArrayOfXXX. 


R2113 A MESSAGE containing serialized arrays MUST NOT include the soapenc:arrayType attribute.    
 * 
 * The code currently supports only few options that can 
 * be occured in the complextype.
 */	

}
