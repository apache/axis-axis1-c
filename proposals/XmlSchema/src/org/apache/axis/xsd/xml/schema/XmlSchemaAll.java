/*
 * XmlSchemaAll.java
 *
 * Created on September 27, 2001, 3:37 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Permits the elements in the group to appear (or not appear) 
 * in any order in the containing element. Represents the World
 * Wide Web Consortium (W3C) all element (compositor).
 *
 * @author  mukund
 */
public class XmlSchemaAll extends XmlSchemaGroupBase {

    /** Creates new XmlSchemaAll */
    public XmlSchemaAll() {
    }
	
	public XmlSchemaObjectCollection getItems() {
		return this.items;
	}

}
