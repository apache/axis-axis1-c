/*
 * XmlSchemaComplexType.java
 *
 * Created on September 27, 2001, 3:40 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for complex types. Defines a complex type that determines the
 * set of attributes and content of an element. Represents the World Wide 
 * Web Consortium (W3C) complexType element.
 *
 * @author  mukund
 */

public class XmlSchemaComplexType extends XmlSchemaType {
	XmlSchemaAnyAttribute anyAttribute, attributeWildcard;
	XmlSchemaObjectCollection attributes;
	XmlSchemaObjectTable attributeUses;
	XmlSchemaDerivationMethod block, blockResolved;
	XmlSchemaContentModel contentModel;
	XmlSchemaContentType contentType;
	XmlSchemaParticle particleType, particle;
	boolean isAbstract, isMixed;
	
    /** Creates new XmlSchemaComplexType */
	public XmlSchemaComplexType() {
		attributes = new XmlSchemaObjectCollection();
		block=new XmlSchemaDerivationMethod("None");
		isAbstract=false;
		isMixed=false;
	}

	public XmlSchemaAnyAttribute getAnyAttribute() {
		return anyAttribute;
	}
	
	public void setAnyAttribute(XmlSchemaAnyAttribute anyAttribute) {
		this.anyAttribute = anyAttribute;
	}
	
	public  XmlSchemaObjectCollection getAttributes() {
		return attributes;
	}
	
	public XmlSchemaObjectTable getAttributeUses() {
		return attributeUses;
	}
	
	public XmlSchemaAnyAttribute getAttributeWildcard() {
		return attributeWildcard;
	}
	
	public XmlSchemaDerivationMethod getBlock() {
		return block;
	}
	
	public void setBlock(XmlSchemaDerivationMethod block) {
		this.block = block;
	}
	
	public XmlSchemaDerivationMethod getBlockResolved() {
		return blockResolved;
	}
	
	public XmlSchemaContentModel getContentModel() {
		return contentModel;
	}
	
	public void setContentModel(XmlSchemaContentModel contentModel) {
		this.contentModel = contentModel;
	}
	
	public XmlSchemaContentType  getContentType() {
		return contentType;
	}
	
	public void setContentType(XmlSchemaContentType contentType) {
		this.contentType = contentType;
	}
	
	public XmlSchemaParticle getContentTypeParticle() {
		return particleType;
	}
	
	public boolean isAbstract() {
		return isAbstract;
	}
	
	public void setAbstract(boolean b) {
		isAbstract = b;
	}
	
	public boolean isMixed() {
		return isMixed;
	}
	
	public void setMixed(boolean b) {
		isMixed = b;
	}
	
	public XmlSchemaParticle getParticle() {
		return particle;
	}
	
	public void setParticle(XmlSchemaParticle particle) {
		this.particle = particle;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";

		String typeName = name != null ? name : "";
		
		xml += "<"+prefix+"complexType name=\""+typeName+"\">\n";
		
		if(particle != null) 
			xml += particle.toString(prefix, (tab+1));
		
		if(contentModel != null) 
			xml += contentModel.toString(prefix, (tab+1));
		
		for(int i=0;i<attributes.getCount();i++) {
			xml += attributes.getItem(i).toString(prefix, (tab+1));
		}
		
		for(int i=0;i<tab;i++)
			xml += "\t";
				
		xml += "</"+prefix+"complexType>\n";
		return xml;
	}
}
