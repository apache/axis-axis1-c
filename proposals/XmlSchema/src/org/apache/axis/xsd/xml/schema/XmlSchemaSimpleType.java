/*
 * XmlSchemaSimpleType.java
 *
 * Created on September 27, 2001, 3:39 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class defines a simple type that determines the information and
 * constraints for the values of attributes or elements with text-only
 * content. Represents the World Wide Web Consortium (W3C) simpleType element.
 *
 * @author  mukund
 */

// Oct 15th - momo - initial impl

public class XmlSchemaSimpleType extends XmlSchemaType {

	XmlSchemaSimpleTypeContent content;
	
    /** Creates new XmlSchemaSimpleType */
    public XmlSchemaSimpleType() {
    }

	public XmlSchemaSimpleTypeContent getContent() {
		return content;
	}
	
	public void setContent(XmlSchemaSimpleTypeContent content) {
		this.content = content;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";
	
		
		xml += "<" + prefix  + "simpleType>\n";
		
		if(content != null)
			xml += content.toString(prefix, (tab+1));
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += "</" + prefix  + "simpleType>\n";
		return xml;
	}

}

