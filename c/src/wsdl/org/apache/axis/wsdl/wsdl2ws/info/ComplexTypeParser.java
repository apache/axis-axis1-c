/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
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
