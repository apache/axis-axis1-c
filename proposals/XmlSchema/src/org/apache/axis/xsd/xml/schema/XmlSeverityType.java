/*
 * XmlSeverityType.java
 *
 * Created on September 27, 2001, 3:06 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.enum.Enum;

/**
 * Represents the severity of the validation event.
 *
 * @author  mukund
 */

public class XmlSeverityType extends Enum	{

	static String[] members = new String[] { "Error", "Warning"};
	
    /** Creates new XmlSeverityType */
    public XmlSeverityType() {
		super();
	}
	
	public XmlSeverityType(String value) {
		super(value);
	}
	
	public String[] getValues() {
		return members;
	}
}
