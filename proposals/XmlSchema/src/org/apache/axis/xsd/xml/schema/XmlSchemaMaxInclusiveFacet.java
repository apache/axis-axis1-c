/*
 * XmlSchemaMaxInclusiveFacet.java
 *
 * Created on September 27, 2001, 3:22 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 *
 * Class for defining maxInclusive facets. Represents the World
 * Wide Web Consortium (W3C) maxInclusive facet.
 * 
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaMaxInclusiveFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaMaxInclusiveFacet */
    public XmlSchemaMaxInclusiveFacet() {
    }

	public XmlSchemaMaxInclusiveFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
