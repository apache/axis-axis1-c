/*
 * XmlSchemaEnumerationFacet.java
 *
 * Created on September 27, 2001, 3:21 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining enumeration facets. Represents the World Wide
 * Web Consortium (W3C) enumeration facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaEnumerationFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaEnumerationFacet */
    public XmlSchemaEnumerationFacet() {
    }

	public XmlSchemaEnumerationFacet( Object value, boolean fixed ) {
		super( value, fixed );
	}
}
