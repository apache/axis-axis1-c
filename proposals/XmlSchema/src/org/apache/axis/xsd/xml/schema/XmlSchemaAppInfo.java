/*
 * XmlSchemaAppInfo.java
 *
 * Created on September 27, 2001, 3:40 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.w3c.dom.NodeList;

/**
 * Defines application specific information within an annotation. 
 * Represents the World Wide Web Consortium (W3C) appinfo element.
 *
 * @author  mukund
 */

// Jan 24 2002 - Joni - Change the Node into NodeList


public class XmlSchemaAppInfo extends XmlSchemaObject {

	/**
	 * Provides the source of the application information.
	 */
	String source;
	
	/**
	 * Returns an array of XmlNode that represents the document text markup.
	 */
	NodeList markup;
		
    /** 
     * Creates new XmlSchemaAppInfo 
     * The default constructor initializes all fields to their default values.
     * */
    public XmlSchemaAppInfo() {
    }
	
	public String getSource() {
		return source;
	}
	
	public void setSource(String source) {
		this.source = source;
	}
	
	public NodeList getMarkup() {
		return markup;
	}
	
	public void setMarkup(NodeList markup) {
		this.markup = markup;
	}
}
