/*
 * XmlSchemaContentProcessing.java
 *
 * Created on September 27, 2001, 3:04 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.enum.Enum;

/**
 * Provides information about the validation mode of any 
 * and anyAttribute element replacements.
 *
 * @author  mukund
 */

public class XmlSchemaContentProcessing extends Enum {

	static String[] members = new String[] { "Lax", "None",
											 "Skip", "Strict"};
	
    /** Creates new XmlSeverityType */
    public XmlSchemaContentProcessing() {
		super();
	}
	
	public XmlSchemaContentProcessing(String value) {
		super(value);
	}
	
	public String[] getValues() {
		return members;
	}

}
