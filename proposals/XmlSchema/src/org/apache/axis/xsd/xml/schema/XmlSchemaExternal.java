/*
 * XmlSchemaExternal.java
 *
 * Created on September 27, 2001, 3:19 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * An abstract class. Provides information about the included schema.
 *
 * @author  mukund
 */

public abstract class XmlSchemaExternal extends XmlSchemaAnnotated {

    /** Creates new XmlSchemaExternal */
    protected XmlSchemaExternal() {
    }

	XmlSchema schema;
	
	public XmlSchema getSchema() {
		return schema;
	}
	
	public void setSchema(XmlSchema schema) {
		this.schema = schema;
	}
	
	String schemaLocation;
	
	public String getSchemaLocation() {
		return schemaLocation;
	}
	
	public void setSchemaLocation(String schemaLocation) {
		this.schemaLocation = schemaLocation;
	}
}

