/*
 * XmlSchemaSimpleTypeUnion.java
 *
 * Created on September 27, 2001, 3:39 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;
/**
 * Class for the union of simpleType elements. Defines a simpleType element
 * as a list of values of a specified data type. Represents the World 
 * Wide Web Consortium (W3C) union element.
 *
 * @author  mukund
 */

public class XmlSchemaSimpleTypeUnion extends XmlSchemaSimpleTypeContent{

	XmlSchemaObjectCollection baseTypes;
	String memberTypesSource;
	QualifiedName[] memberTypesQNames;

	public XmlSchemaSimpleTypeUnion() {
		baseTypes = new XmlSchemaObjectCollection();
	}
	
	public XmlSchemaObjectCollection getBaseTypes() {
		return this.baseTypes;
	}
	
	public void setMemberTypesSource( String memberTypesSources ){
		this.memberTypesSource = memberTypesSources;
	}
	
	public String getMemberTypesSource(){
		return this.memberTypesSource;
	}
        
	public QualifiedName[] getMemberTypesQNames(){
		return this.memberTypesQNames;
	}

}
