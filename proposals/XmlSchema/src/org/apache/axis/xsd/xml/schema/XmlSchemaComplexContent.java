/*
 * XmlSchemaComplexContent.java
 *
 * Created on September 27, 2001, 3:19 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class that represents the complex content model for complex types. 
 * Contains extensions or restrictions on a complex type that has mixed 
 * content or elements only. Represents the World Wide Web Consortium (W3C) 
 * complexContent element.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaComplexContent extends XmlSchemaContentModel {

    /** Creates new XmlSchemaComplexContent */
    public XmlSchemaComplexContent() {
    }
	
	/* One of either the XmlSchemaComplexContentRestriction or 
	 * XmlSchemaComplexContentExtension classes.
	 */
	XmlSchemaContent content;
	
	public XmlSchemaContent getContent() {
		return this.content;
	}

	public void setContent( XmlSchemaContent content) {
		this.content = content;
	}
	
	/* Indicates that this type has a mixed content model. Character data
	 * is allowed to appear between the child elements of the complex type. 
	 */
	public boolean mixed;
	
	public boolean isMixed() {
		return this.mixed;
	}
	
	public void setMixed(boolean mixed) {
		this.mixed = mixed;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";
		
		xml += "<"+prefix+"complexContent>\n";
		
		xml += content.toString(prefix, (tab+1));
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		xml += "<"+prefix+"complexContent>\n";
		return xml;
	}
}
