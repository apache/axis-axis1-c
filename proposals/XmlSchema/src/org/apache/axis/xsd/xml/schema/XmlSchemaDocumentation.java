/*
 * XmlSchemaDocumentation.java
 *
 * Created on September 27, 2001, 3:41 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.w3c.dom.NodeList;

/**
 * Class that specifies information to be read or used by humans
 * within an annotation. Represents the World Wide Web Consortium 
 * (W3C) documentation element.
 *
 * @author  mukund
 */

public class XmlSchemaDocumentation extends XmlSchemaObject {

    /** Creates new XmlSchemaDocumentation */
    public XmlSchemaDocumentation() {
    }
	
	/**
	 * Provides the source of the application information.
	 */
	String source;
	String language;
	
	/**
	 * Returns an array of XmlNode that represents the document text markup.
	 */
	NodeList markup;
	
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
	
	public String getLanguage() {
		return language;
	}
	
	public void setLanguage(String language) {
		this.language = language;
	}

}
