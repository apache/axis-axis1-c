/*
 * XmlSchemaAny.java
 *
 * Created on September 27, 2001, 3:36 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Enables any element from the specified namespace or namespaces 
 * to appear in the containing complexType element. Represents the
 * World Wide Web Consortium (W3C) any element.
 *
 * @author  mukund
 */

// Feb 15th 2002 - Joni - Processing content will be initialized with "None"

public class XmlSchemaAny extends XmlSchemaParticle {

	/** Creates new XmlSchemaAny */
	public XmlSchemaAny() {
		processContent = new XmlSchemaContentProcessing("None");
	}
	
	/**
	 * Namespaces containing the elements that can be used.
	 */
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
