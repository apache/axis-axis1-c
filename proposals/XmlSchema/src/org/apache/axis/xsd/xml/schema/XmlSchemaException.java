/*
 * XmlSchemaException.java
 *
 * Created on September 27, 2001, 3:00 AM
 */

package org.apache.axis.xsd.xml.schema;


/**
 * Returns detailed information about the schema exception.
 *
 * @author  mukund
 */

public class XmlSchemaException extends RuntimeException {

    /** Creates new XmlSchemaException */
    public XmlSchemaException() {
    }
    
	public XmlSchemaException(String message) {
		super(message);
	}
	// TODO :implement
    public int getLineNumer() {
		return 1;
    }
    
    public int getLinePosition() {
		return 1;
    }
    
    public XmlSchemaObject getSourceSchemaObject() {
		return null;
    }
    
    public String getSourceUri() {
		return null;
    }
}
