/*
 * XmlSchemaAttributeGroup.java
 *
 * Created on September 27, 2001, 3:09 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for attribute groups. Groups a set of attribute declarations 
 * so that they can be incorporated as a group into complex type 
 * definitions. Represents the World Wide Web Consortium (W3C) 
 * attributeGroup element.
 *
 * @author  mukund
 */

public class XmlSchemaAttributeGroup extends XmlSchemaAnnotated{

    /** Creates new XmlSchemaAttributeGroup */
    public XmlSchemaAttributeGroup() {
        attributes = new XmlSchemaObjectCollection();
    }

	XmlSchemaAnyAttribute anyAttribute;
	
	public XmlSchemaAnyAttribute getAnyAttribute(){
		return this.anyAttribute;
	}
	
	public void setAnyAttribute(XmlSchemaAnyAttribute anyAttribute){
		this.anyAttribute = anyAttribute;
	}
	
	XmlSchemaObjectCollection attributes;
        
	public XmlSchemaObjectCollection getAttributes(){
		return this.attributes;
	}
	
	public void setAttributes(XmlSchemaObjectCollection attributes){
		this.attributes = attributes;
	}
	
	String name;
	
	public String getName(){
		return this.name;
	}
	
	public void setName( String name) {
		this.name = name;
	}
}
