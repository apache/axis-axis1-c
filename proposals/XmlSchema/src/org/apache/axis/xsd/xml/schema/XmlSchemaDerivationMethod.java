/*
 * XmlSchemaDerivationMethod.java
 *
 * Created on September 27, 2001, 3:04 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.enum.Enum;

/**
 * Provides different methods for preventing derivation.
 *
 * @author  mukund
 */

public class XmlSchemaDerivationMethod extends Enum {
	static String[] members = new String[] { "All", "Empty", "Extension", 
											 "List", "None", "Restriction", 
											 "Substitution", "Union"};
	
    /** Creates new XmlSeverityType */
    public XmlSchemaDerivationMethod() {
		super();
	}
	
	public XmlSchemaDerivationMethod(String value) {
		super(value);
	}
	
	public String[] getValues() {
		return members;
	}


}
