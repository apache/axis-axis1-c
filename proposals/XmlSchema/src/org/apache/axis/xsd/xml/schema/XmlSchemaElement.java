/*
 * XmlSchemaElement.java
 *
 * Created on September 27, 2001, 3:36 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Class for elements. Represents the World Wide Web Consortium (W3C) element element.  
 *
 * @author  mukund
 */

// October 15th - momo - initial implementation
public class XmlSchemaElement extends XmlSchemaParticle  {

	/**
	 * Attribute used to block a type derivation.
	 */
	XmlSchemaDerivationMethod block;
	
	/**
	 * The value after an element has been compiled to post-schema infoset. 
	 * This value is either from the type itself or, if not defined on the type, taken from the schema element.
	 */
	XmlSchemaDerivationMethod blockResolved;
	XmlSchemaObjectCollection constraints;
	
	/**
	 * Provides the default value of the element if its content 
	 * is a simple type or the element's content is textOnly.
	 */
	String defaultValue;
	String fixedValue;
	
	/**
	 * Returns the correct common runtime library 
	 * object based upon the SchemaType for the element.
	 */
	Object elementType;

	XmlSchemaDerivationMethod finalDerivation;
	XmlSchemaDerivationMethod finalDerivationResolved;
	
	/**
	 * The default value is the value of the elementFormDefault attribute for the schema element containing the attribute. 
	 * The default is Unqualified.
	 */
	XmlSchemaForm form; 
	boolean isAbstract;
	boolean isNillable;
	String name;
	QualifiedName qualifiedName;
	QualifiedName refName;
	
	/**
	 * Returns the type of the element. 
	 * This can either be a complex type or a simple type.
	 */
	XmlSchemaType schemaType;
	
	/**
	 * QualifiedName of a built-in data type defined in this schema or another 
	 * schema indicated by the specified namespace.
	 */
	QualifiedName schemaTypeName;
	
	/**
	 * QualifiedName of an element that can be a substitute for this element.
	 */
	QualifiedName substitutionGroup;
	
	/** Creates new XmlSchemaElement */
        public XmlSchemaElement() {
               constraints = new XmlSchemaObjectCollection();
               isAbstract = false;
               isNillable = false;
               form = new XmlSchemaForm("None");
               finalDerivation = new XmlSchemaDerivationMethod("None");
               block = new XmlSchemaDerivationMethod("None");
        }
	
	/**
	 * Returns a collection of constraints on the element.
	 */
	public XmlSchemaObjectCollection getConstraints() {
		return constraints;
	}
	
	public String getDefaultValue() {
		return defaultValue;
	}
	
	public void setDefaultValue(String defaultValue) {
		this.defaultValue = defaultValue;
	}
	
	public XmlSchemaDerivationMethod getBlock() {
		return block;
	}
	
	public void setBlock(XmlSchemaDerivationMethod block) {
		this.block = block;
	}
	
	public XmlSchemaDerivationMethod getFinal() {
		return finalDerivation;
	}
	
	public void setFinal(XmlSchemaDerivationMethod finalDerivation) {
		this.finalDerivation = finalDerivation;
	}
	
	public XmlSchemaDerivationMethod getBlockResolved() {
		return blockResolved;
	}
	
	public String getFixedValue() {
		return fixedValue;
	}
	
	public void setFixedValue(String fixedValue) {
		this.fixedValue = fixedValue;
	}
	
	public Object getElementType() {
		return elementType;
	}
	
	public XmlSchemaForm getForm() {
		return form;
	}
	
	public void setForm(XmlSchemaForm form) {
		this.form = form;
	}
	
	public boolean isAbstract() {
		return isAbstract;
	}
	
	public void setAbstract(boolean isAbstract) {
		this.isAbstract = isAbstract;
	}
	
	public boolean isNillable() {
		return isNillable;
	}
	
	public void setNillable(boolean isNillable) {
		this.isNillable = isNillable;
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
	
	public QualifiedName getQualifiedName() {
		return qualifiedName;
	}
	
	public void setQualifiedName(QualifiedName qualifiedName) {
		this.qualifiedName = qualifiedName;
	}
	
	public XmlSchemaType getSchemaType() {
		return schemaType;
	}
	
	public void setSchemaType(XmlSchemaType schemaType) {
		this.schemaType = schemaType;
	}
	
	public QualifiedName getSchemaTypeName() {
		return schemaTypeName;
	}
	
	public void setSchemaTypeName(QualifiedName schemaTypeName) {
		this.schemaTypeName = schemaTypeName;
	}
	
	public QualifiedName getSubstitutionGroup() {
		return substitutionGroup;
	}
	
	public void setSubstitutionGroup(QualifiedName substitutionGroup) {
		this.substitutionGroup = substitutionGroup;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += "<"+prefix+"element ";
		
		if(!name.equals("")) 
			xml += "name=\""+name+"\" ";
		
		if(schemaTypeName != null) 
			xml +="type=\""+schemaTypeName+"\"";
		
		if(refName != null)
			xml += "ref=\"" + refName + "\" ";
		
		if(minOccurs != 1)
			xml +=  "minOccurs=\""+minOccurs+"\" "; 
		
		if(maxOccurs != 1)
			xml += "maxOccurs=\""+maxOccurs+"\" ";
			   
		xml += ">\n";
		
		if(constraints != null)
			xml += constraints.toString(prefix, (tab+1));
	
		if(schemaType != null) {
			xml += schemaType.toString(prefix, (tab + 1));
		} 
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += "</"+prefix+"element>\n";
		
		return xml;
	}
}
