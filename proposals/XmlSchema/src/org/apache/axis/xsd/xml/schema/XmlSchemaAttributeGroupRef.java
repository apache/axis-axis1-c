/*
 * XmlSchemaAttributeGroupRef.java
 *
 * Created on September 27, 2001, 3:10 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.apache.axis.xsd.xml.QualifiedName;
/**
 *
 * Class for the attribute group reference. Represents the World Wide
 * Web Consortium (W3C) attributeGroup element with the ref attribute.
 * 
 * @author  mukund
 * 
 */
public class XmlSchemaAttributeGroupRef extends XmlSchemaAnnotated {

    /** Creates new XmlSchemaAttributeGroupRef */
    public XmlSchemaAttributeGroupRef() {
    }
	
	QualifiedName refName;
	
	public QualifiedName getRefName(){
		return this.refName;
	}

	public void setRefName(QualifiedName refName) {
		this.refName = refName;
	}
		
}
