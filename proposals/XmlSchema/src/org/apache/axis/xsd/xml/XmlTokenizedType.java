package org.apache.axis.xsd.xml;

import org.apache.axis.xsd.enum.Enum;
/**
 * @author momo 
 */

// Oct 15th - Momo - Initial Impl

public class XmlTokenizedType extends Enum {

	static String[] members = new String[] { "CDATA", "IDREF", "IDREFS", 
											 "ENTITY", "ENTITIES", "NMTOKEN", 
											 "NMTOKENS", "NOTATION", "ENUMERATION",
											 "QName", "NCName", "None"};
		
    /** Creates new XmlSchemaForm */
	public XmlTokenizedType(String value) {
		super(value);
	}
	
	public String[] getValues() {
		return members;
	}

}
