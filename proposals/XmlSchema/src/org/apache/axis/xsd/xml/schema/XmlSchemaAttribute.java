/*
 * XmlSchemaAttribute.java
 *
 * Created on September 27, 2001, 3:09 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Class for attribute types. Represents the World Wide Web Consortium
 * (W3C) attribute element.
 *
 * @author  mukund
 */

// October 15th - momo - initial implementation

public class XmlSchemaAttribute extends XmlSchemaAnnotated {

	Object attributeType;
	String defaultValue, fixedValue, name;
	XmlSchemaForm form;
	XmlSchemaSimpleType schemaType;
	QualifiedName schemaTypeName, qualifiedName, refName;
	XmlSchemaUse use;
	
    /** Creates new XmlSchemaAttribute */
	public XmlSchemaAttribute() {
		form = new XmlSchemaForm("None");
		use= new XmlSchemaUse("None");
	}

	public Object getAttributeType() {
		return attributeType;
	}
	
	public String getDefaultValue() {
		return defaultValue;
	}
	
	public void setDefaultValue(String defaultValue) {
		this.defaultValue = defaultValue;
	}
	
	public String getFixedValue() {
		return fixedValue;
	}
	
	public void setFixedValue(String fixedValue) {
		this.fixedValue = fixedValue;
	}
	
	public XmlSchemaForm getForm() {
		return form;
	}
	
	public void setSchemaForm(XmlSchemaForm form) {
		this.form = form;
	}	
	
	public QualifiedName getQualifiedName() {
		return qualifiedName;
	}
	
	public void setQualifiedName(QualifiedName qualifiedName) {
		this.qualifiedName = qualifiedName;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public QualifiedName getRefName() {
		return refName;
	}
	
	public void setRefName(QualifiedName refName) {
		this.refName = refName;
	}
	
	public XmlSchemaSimpleType getSchemaType() {
		return schemaType;
	}
	
	public void setSchemaType(XmlSchemaSimpleType schemaType) {
		this.schemaType = schemaType;
	}
	
	public QualifiedName getSchemaTypeName() {
		return schemaTypeName;
	}
	
	public void setSchemaTypeName(QualifiedName schemaTypeName) {
		this.schemaTypeName = schemaTypeName;
	}
	
	public XmlSchemaUse getUse() {
		return use;
	}
	
	public void setUse(XmlSchemaUse use) {
		this.use = use;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += "<"+prefix+"attribute name=\""+name+"\" type=\""+schemaTypeName+"\"/>\n";
		
		return xml;
	}
}
