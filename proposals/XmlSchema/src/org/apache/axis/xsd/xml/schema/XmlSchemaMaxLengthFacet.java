/*
 * XmlSchemaMaxLengthFacet.java
 *
 * Created on September 27, 2001, 3:32 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining maxLength facets. Represents the World Wide 
 * Web Consortium (W3C) maxLength facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaMaxLengthFacet extends XmlSchemaNumericFacet {

    /** Creates new XmlSchemaMaxLengthFacet */
    public XmlSchemaMaxLengthFacet() {
    }

	public XmlSchemaMaxLengthFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
