/*
 * XmlSchemaSequence.java
 *
 * Created on September 27, 2001, 3:37 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Requires the elements in the group to appear in the specified sequence 
 * within the containing element. Represents the World Wide Web Consortium 
 * (W3C) sequence (compositor) element.
 *
 * @author  mukund
 */

public class XmlSchemaSequence extends XmlSchemaGroupBase {

    /** Creates new XmlSchemaSequence */
    public XmlSchemaSequence() {
    }

	/**
	 *  The elements contained within the compositor. 
	 *	Collection of XmlSchemaElement, XmlSchemaGroupRef, 
	 *  XmlSchemaChoice, XmlSchemaSequence, or XmlSchemaAny.
	 */
	public XmlSchemaObjectCollection getItems() {
		return items;
	}	
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		for(int i=0;i<tab;i++)
			xml += "\t";
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";
	
		xml += "<"+prefix+"sequence>\n";
		for(int i=0;i<items.getCount();i++) {
			xml += items.getItem(i).toString(prefix, (tab+1));
		}
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += "</"+prefix+"sequence>\n";
		return xml;
	}
}
