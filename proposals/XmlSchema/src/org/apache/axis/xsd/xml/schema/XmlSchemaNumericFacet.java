/*
 * XmlSchemaNumericFacet.java
 *
 * Created on September 27, 2001, 3:23 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Abstract class for defining numeric facets.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public abstract class XmlSchemaNumericFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaNumericFacet */
    protected XmlSchemaNumericFacet() {
    }
	
	protected XmlSchemaNumericFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
	

}
