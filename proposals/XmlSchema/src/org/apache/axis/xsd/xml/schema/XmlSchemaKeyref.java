/*
 * XmlSchemaKeyref.java
 *
 * Created on September 27, 2001, 3:35 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Identifies a keyref constraint. Represents the World Wide Web 
 * Consortium (W3C) keyref element.
 *
 * @author  mukund
 */

public class XmlSchemaKeyref extends XmlSchemaIdentityConstraint {

    /** Creates new XmlSchemaKeyref */
    public XmlSchemaKeyref() {
    }

	QualifiedName refer;
	
	public QualifiedName getRefer() {
		return refer;
	}
	
	public void setRefer(QualifiedName refer) {
		this.refer = refer;
	}
}
