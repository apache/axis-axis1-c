/*
 * XmlSchemaChoice.java
 *
 * Created on September 27, 2001, 3:37 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Allows only one of its children to appear in an instance. Represents 
 * the World Wide Web Consortium (W3C) choice (compositor) element.
 *
 * @author  mukund
 */
public class XmlSchemaChoice extends XmlSchemaGroupBase{

    /** Creates new XmlSchemaChoice */
    public XmlSchemaChoice() {
    }
	
	public XmlSchemaObjectCollection getItems() {
		return this.items;
	}

}
