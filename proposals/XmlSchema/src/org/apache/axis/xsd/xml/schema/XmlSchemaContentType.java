/*
 * XmlSchemaContentType.java
 *
 * Created on September 27, 2001, 3:04 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.enum.Enum;

/**
 * Enumerations for the content model of the complex type. This 
 * represents the content in the post-schema-validation infoset.
 *
 * @author  mukund
 */

public class XmlSchemaContentType extends Enum {

	static String[] members = new String[] { "ElementOnly", "Empty", 
											 "Mixed", "TextOnly"};
		
    /** Creates new XmlSchemaContentType */
    public XmlSchemaContentType() {
		super();
    }

	public XmlSchemaContentType(String value) {
		super(value); 
	}
	
	public String[] getValues() {
		return members;
	}
}
