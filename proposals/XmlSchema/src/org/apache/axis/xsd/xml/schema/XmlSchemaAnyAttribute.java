/*
 * XmlSchemaAnyAttribute.java
 *
 * Created on September 27, 2001, 3:09 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Enables any attribute from the specified namespace or namespaces 
 * to appear in the containing complexType element. Represents the
 * World Wide Web Consortium (W3C) anyAttribute element.
 *
 * @author  mukund
 */
public class XmlSchemaAnyAttribute extends XmlSchemaAnnotated {

	/** Creates new XmlSchemaAnyAttribute */
	public XmlSchemaAnyAttribute() {
		processContent = new XmlSchemaContentProcessing("None");
	}

	String namespace;
	
	public String getNamespace() {
		return namespace;
	}
	
	public void setNamespace(String namespace) {
		this.namespace = namespace;
	}
	
	XmlSchemaContentProcessing processContent;
	
	public XmlSchemaContentProcessing getProcessContent() {
		return processContent;
	}
	
	public void setProcessContent(XmlSchemaContentProcessing processContent) {
		this.processContent = processContent;
	}
}
