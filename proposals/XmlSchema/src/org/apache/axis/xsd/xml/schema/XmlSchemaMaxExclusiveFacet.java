/*
 * XmlSchemaMaxExclusiveFacet.java
 *
 * Created on September 27, 2001, 3:21 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 *
 * Class for defining maxExclusive facets. Represents the World Wide 
 * Web Consortium (W3C) maxExclusive facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaMaxExclusiveFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaMaxExclusiveFacet */
    public XmlSchemaMaxExclusiveFacet() {
    }
	
	public XmlSchemaMaxExclusiveFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
