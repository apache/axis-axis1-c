/*
 * XmlSchemaSimpleContentExtension.java
 *
 * Created on September 27, 2001, 3:18 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;
/**
 * Class for simple types that are derived by extension. Extends the simple
 * type content of the element by adding attributes. Represents the World Wide
 * Web Consortium (W3C) extension element for simple content.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaSimpleContentExtension extends XmlSchemaContent {

    /** Creates new XmlSchemaSimpleContentExtension */
    public XmlSchemaSimpleContentExtension() {
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

	/* Name of the built-in data type, simple type, or complex type.*/
	QualifiedName baseTypeName;
	
	public void setBaseTypeName( QualifiedName  baseTypeName) {
		this.baseTypeName = baseTypeName;
	}
	
	public QualifiedName getBaseTypeName() {
		return this.baseTypeName;
	}
	
}

