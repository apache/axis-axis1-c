/*
 * XmlSchemaForm.java
 *
 * Created on September 27, 2001, 3:05 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.enum.Enum;

/**
 * Indicates if attributes or elements need to be qualified or left unqualified.  
 *
 * @author  mukund
 */

// October 15th - momo - initial implementation
// Jan 16th - Vidyanand - changed Quailified to qualified and Unqualified to unqualified 
// Feb 12th - Joni change qualified to Qualified  and unqualified to Unqualified 

public class XmlSchemaForm extends Enum {

	static String[] members = new String[] { "None", "Qualified", "Unqualified"};
		
    /** Creates new XmlSchemaForm */
    public XmlSchemaForm() {
		super();
    }
	
	public XmlSchemaForm(String value) {
		super(value);
	}
	
	public String[] getValues() {
		return members;
	}

}
