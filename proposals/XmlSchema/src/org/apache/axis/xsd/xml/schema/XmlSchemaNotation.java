/*
 * XmlSchemaNotation.java
 *
 * Created on September 27, 2001, 3:35 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class represents a notation. An XML Schema definition language (XSD)
 * notation declaration is a reconstruction of XML 1.0 NOTATION 
 * declarations. The purpose of notations is to describe the format of
 * non-XML data within an XML document. Represents the World Wide Web Consortium 
 * (W3C) notation element.
 *
 * @author  mukund
 */

public class XmlSchemaNotation extends XmlSchemaAnnotated  {

	String name, system, publicNotation;
	
    /** Creates new XmlSchemaNotation */
    public XmlSchemaNotation() {
    }

	public String getName() {
		return name;
	}
	
	public void setString(String name) {
		this.name = name;
	}
	
	public String getPublic() {
		return publicNotation;
	}
	
	public void setPublic(String publicNotation) {
		this.publicNotation = publicNotation;
	}
	
	public String getSystem() {
		return system;
	}
	
	public void setSystem(String system) {
		this.system = system;
	}
	
	
	
}
