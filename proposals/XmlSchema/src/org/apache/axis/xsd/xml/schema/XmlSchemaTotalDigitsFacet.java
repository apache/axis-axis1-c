/*
 * XmlSchemaTotalDigitsFacet.java
 *
 * Created on September 27, 2001, 3:33 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining totalDigits facets. Represents the World Wide
 * Web Consortium (W3C) totalDigits facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaTotalDigitsFacet extends XmlSchemaNumericFacet {

    /** Creates new XmlSchemaTotalDigitsFacet */
    public XmlSchemaTotalDigitsFacet() {
    }

	public XmlSchemaTotalDigitsFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
