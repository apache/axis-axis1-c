/*
 * XmlSchemaType.java
 *
 * Created on September 27, 2001, 3:39 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;
/**
 * The base class for all simple types and complex types.
 *
 * @author  mukund
 */

// Oct 15th - momo - initial impl

public class XmlSchemaType extends XmlSchemaAnnotated {

	Object baseSchemaType;
	XmlSchemaDatatype dataType;
	XmlSchemaDerivationMethod deriveBy, finalDerivation, finalResolved;
	boolean isMixed;
	
	// name of the type
	String name;
	QualifiedName qualifiedName;
	
	/** Creates new XmlSchemaType */
	public XmlSchemaType() {
		finalDerivation = new XmlSchemaDerivationMethod("None");
	}
	
	public Object getBaseSchemaType() {
		return baseSchemaType;
	}
	
	public XmlSchemaDatatype getDataType() {
		return dataType;
	}
	
	public XmlSchemaDerivationMethod getDeriveBy() {
		return deriveBy;
	}
	
	public XmlSchemaDerivationMethod getFinal() {
		return finalDerivation;
	}
	
	public void setFinal(XmlSchemaDerivationMethod finalDerivation) {
		this.finalDerivation = finalDerivation;
	}
	
	public XmlSchemaDerivationMethod getFinalResolved() {
		return finalResolved;
	}
	
	public boolean isMixed() {
		return isMixed;
	}
	
	public void setMixed(boolean isMixed) {
		this.isMixed = isMixed;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public QualifiedName getQualifiedName() {
		return qualifiedName;
	}
	
	public void setQualifiedName(QualifiedName qName) {
		this.qualifiedName = qName;
	}
}
