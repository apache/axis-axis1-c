/*
 * XmlSchemaSimpleContent.java
 *
 * Created on September 27, 2001, 3:19 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for simple types and complex types with a simple content model. 
 * Represents the World Wide Web Consortium (W3C) simpleContent element.  
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaSimpleContent extends XmlSchemaContentModel{

    /** Creates new XmlSchemaSimpleContent */
    public XmlSchemaSimpleContent() {
    }

	/*  One of XmlSchemaSimpleContentRestriction or XmlSchemaSimpleContentExtension. */
	XmlSchemaContent content;
	
	public XmlSchemaContent getContent() {
		return this.content;
	}
	
	public void setContent( XmlSchemaContent content ) {
		this.content = content;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		
		if(!prefix.equals("") && prefix.indexOf(":") == -1) {
			prefix += ":";	
		}
		return xml;
	}
}
