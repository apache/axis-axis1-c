/*
 * XmlSchemaUse.java
 *
 * Created on September 27, 2001, 3:05 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.enum.Enum;

/**
 * Indicator of how the attribute is used.  
 *
 * @author  mukund
 */
public class XmlSchemaUse extends Enum {

	static String[] members = new String[] { "None", "Optional", 
											 "Prohibited", "Required"};
	
    /** Creates new XmlSchemaUse */
    public XmlSchemaUse() {
		super();
    }
	
	public XmlSchemaUse(String value) {
		super(value);
	}
	
	public String[] getValues() {
		return members;
	}

}
