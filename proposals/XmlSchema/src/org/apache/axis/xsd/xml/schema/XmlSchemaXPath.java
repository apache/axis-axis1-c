/*
 * XmlSchemaXPath.java
 *
 * Created on September 27, 2001, 3:40 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for XML Path Language (XPath) expressions. Represents the
 * World Wide Web Consortium (W3C) selector element. The World Wide 
 * Web Consortium (W3C) field element is a collection of 
 * XmlSchemaXPath classes.
 *
 * @author  mukund
 */

public class XmlSchemaXPath extends XmlSchemaAnnotated {

    /** Creates new XmlSchemaXPath */
    public XmlSchemaXPath() {
    }

	String xpath;
	
	public String getXPath() {
		return xpath;
	}
	
	public void setXPath(String xpath) {
		this.xpath = xpath;
	}
}
