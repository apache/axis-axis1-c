/*
 * XmlSchemaGroupBase.java
 *
 * Created on September 27, 2001, 3:36 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * An abstract class for XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence.
 *
 * @author  mukund
 */

public abstract class XmlSchemaGroupBase extends XmlSchemaParticle {
	XmlSchemaObjectCollection items;
	
    /** Creates new XmlSchemaGroupBase */
    public XmlSchemaGroupBase() {
		items = new XmlSchemaObjectCollection();
    }

	public abstract XmlSchemaObjectCollection getItems();
}
