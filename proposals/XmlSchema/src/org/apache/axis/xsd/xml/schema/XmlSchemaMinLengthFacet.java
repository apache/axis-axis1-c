/*
 * XmlSchemaMinLengthFacet.java
 *
 * Created on September 27, 2001, 3:32 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining minLength facets. Represents the World Wide 
 * Web Consortium (W3C) minLength facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaMinLengthFacet extends XmlSchemaNumericFacet {

    /** Creates new XmlSchemaMinLengthFacet */
    public XmlSchemaMinLengthFacet() {
    }

	public XmlSchemaMinLengthFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
