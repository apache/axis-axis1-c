/*
 * XmlSchemaMinInclusive.java
 *
 * Created on September 27, 2001, 3:22 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining minInclusive facets. Represents the World Wide
 * Web Consortium (W3C) minInclusive facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaMinInclusiveFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaMinInclusive */
    public XmlSchemaMinInclusiveFacet() {
    }

	public XmlSchemaMinInclusiveFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
