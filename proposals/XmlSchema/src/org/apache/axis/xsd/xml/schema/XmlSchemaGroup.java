/*
 * XmlSchemaGroup.java
 *
 * Created on September 27, 2001, 3:34 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class that defines groups at the schema level that are referenced 
 * from the complex types. Groups a set of element declarations so that
 * they can be incorporated as a group into complex type definitions. 
 * Represents the World Wide Web Consortium (W3C) group element.
 *
 * @author  mukund
 */

public class XmlSchemaGroup extends XmlSchemaAnnotated {

    /** Creates new XmlSchemaGroup */
    public XmlSchemaGroup() {
    }
	
	String name;
	XmlSchemaGroupBase particle;
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public XmlSchemaGroupBase getParticle() {
		return particle;
	}
	
	public void setParticle(XmlSchemaGroupBase particle) {
		this.particle = particle;
	}
	
}
