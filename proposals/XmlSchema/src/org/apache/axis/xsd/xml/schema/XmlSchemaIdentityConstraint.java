/*
 * XmlSchemaIdentityConstraint.java
 *
 * Created on September 27, 2001, 3:34 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for the identity constraints: key, keyref, and unique elements.  
 *
 * @author  mukund
 */

// Vidyanand - should this be an abstract class ???

public class XmlSchemaIdentityConstraint extends XmlSchemaAnnotated {

    /** Creates new XmlSchemaIdentityConstraint */
    public XmlSchemaIdentityConstraint() {
		fields = new XmlSchemaObjectCollection();
    }

	XmlSchemaObjectCollection fields;
	
	public XmlSchemaObjectCollection getFields() {
		return fields;
	}
	
	String name;
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	XmlSchemaXPath selector;
	
	public XmlSchemaXPath getSelector() {
		return selector;
	}
	
	public void setSelector(XmlSchemaXPath selector) {
		this.selector = selector;
	}
	
	
	
}
