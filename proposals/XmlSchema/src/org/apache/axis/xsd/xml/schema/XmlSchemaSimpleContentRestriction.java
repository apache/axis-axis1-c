/*
 * XmlSchemaSimpleContentRestriction.java
 *
 * Created on September 27, 2001, 3:18 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Class for simple types that are derived by restriction. Restricts the
 * range of values for the element to a subset of the inherited simple types. 
 * Represents the World Wide Web Consortium (W3C) restriction element for simple content.  
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaSimpleContentRestriction extends XmlSchemaContent{

    /** Creates new XmlSchemaSimpleContentRestriction */
    public XmlSchemaSimpleContentRestriction() {
		facets = new XmlSchemaObjectCollection();
		attributes = new XmlSchemaObjectCollection();
    }
	
	/* Allows an XmlSchemaAnyAttribute to be used for the attribute value.*/
	XmlSchemaAnyAttribute anyAttribute;
	
	public void setAnyAttribute( XmlSchemaAnyAttribute anyAttribute ) {
		this.anyAttribute = anyAttribute;
	}
	
	public XmlSchemaAnyAttribute getAnyAttribute() {
		return this.anyAttribute;
	}
	/* Contains XmlSchemaAttribute and XmlSchemaAttributeGroupRef. Collection of attributes for the simple type.*/
	XmlSchemaObjectCollection  attributes;
	
	public XmlSchemaObjectCollection getAttributes() {
		return this.attributes;
	}

	/*Derived from the type specified by the base value.*/
	XmlSchemaSimpleType baseType;
	
	public void setBaseType( XmlSchemaSimpleType  baseType) {
		this.baseType = baseType;
	}
	
	public XmlSchemaSimpleType getBaseType() {
		return this.baseType;
	}
	
	/* Name of the built-in data type, simple type, or complex type.*/
	QualifiedName baseTypeName;
	
	public void setBaseTypeName( QualifiedName  baseTypeName) {
		this.baseTypeName = baseTypeName;
	}
	
	public QualifiedName getBaseTypeName() {
		return this.baseTypeName;
	}
	
	/* One or more of the facet classes: */
	XmlSchemaObjectCollection facets;
	
	public XmlSchemaObjectCollection getFacets() {
		return this.facets;
	}
	
}
			
