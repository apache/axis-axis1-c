/*
 * XmlSchemaWhiteSpaceFacet.java
 *
 * Created on September 27, 2001, 3:33 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining whiteSpace facets. Represents the World Wide
 * Web Consortium (W3C) whiteSpace facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaWhiteSpaceFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaWhiteSpaceFacet */
    public XmlSchemaWhiteSpaceFacet() {
    }

	public XmlSchemaWhiteSpaceFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
