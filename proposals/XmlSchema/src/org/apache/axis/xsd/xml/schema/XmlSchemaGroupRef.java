/*
 * XmlSchemaGroupRef.java
 *
 * Created on September 27, 2001, 3:37 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.apache.axis.xsd.xml.QualifiedName;
/**
 * Class used within complex types that defines the reference to 
 * groups defined at the schema level. Represents the World Wide
 * Web Consortium (W3C) group element with ref attribute.
 *
 * @author  mukund
 */

public class XmlSchemaGroupRef extends XmlSchemaParticle {

    /** Creates new XmlSchemaGroupRef */
    public XmlSchemaGroupRef() {
    }
	
	XmlSchemaGroupBase particle;
	
	public XmlSchemaGroupBase getParticle(){
		return this.particle;
	}
	
	QualifiedName refName;
	
	public QualifiedName getRefName(){
		return this.refName;
	}

	public void setRefName(QualifiedName refName) {
		this.refName = refName;
	}
	

}
