/*
 * XmlSchemaComplexContentExtension.java
 *
 * Created on September 27, 2001, 3:11 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Class for complex types with a complex content model derived by extension. 
 * Extends the complex type by adding attributes or elements. Represents the 
 * World Wide Web Consortium (W3C) extension element for complex content.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaComplexContentExtension extends XmlSchemaContent {

    /** Creates new XmlSchemaComplexContentExtension */
    public XmlSchemaComplexContentExtension() {
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
	
	/*One of the XmlSchemaGroupRef, XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.*/
	XmlSchemaParticle particle;
	
	public XmlSchemaParticle getParticle() {
		return this.particle;
	}
	
	public void setParticle( XmlSchemaParticle particle ) {
		this.particle = particle;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		for(int i=0;i<tab;i++)
			xml += "\t";
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";
	
		xml += "<"+prefix+"extension>\n";
		
		if(particle != null)
			xml += particle.toString(prefix, (tab+1));
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += "</"+prefix+"extension>\n";
		return xml;
	}
}
