/*
 * XmlSchemaParticle.java
 *
 * Created on September 27, 2001, 3:35 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Base class for all particle types.
 *
 * @author  mukund
 */

// October 15th - momo - initial implementation

public class XmlSchemaParticle extends XmlSchemaAnnotated {

	long maxOccurs = 1;
	String maxOccursString;
	long minOccurs = 1;
	String minOccursString;
	
    /**
	 * Creates new XmlSchemaParticle 
     * Particle types are usually interchangeable. 
     * A local element declaration or reference to a global element 
     * declaration (element), a compositor ( sequence, choice, or all), 
     * a reference to a named content model group (group), or an element wildcard (any).
     *
	 */
    public XmlSchemaParticle() {
    }

	public void setMaxOccurs(long maxOccurs) {
		this.maxOccurs = maxOccurs;
	}
	
	public long getMaxOccurs() {
		return maxOccurs;
	}
	
	public void setMinOccurs(long minOccurs) {
		this.minOccurs = minOccurs;
	}
	
	public long getMinOccurs() {
		return minOccurs;
	}
}
