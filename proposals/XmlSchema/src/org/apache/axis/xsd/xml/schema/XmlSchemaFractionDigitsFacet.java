/*
 * XmlSchemaFractionDigitsFacet.java
 *
 * Created on September 27, 2001, 3:24 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining fractionDigits facets. Represents the World Wide
 * Web Consortium (W3C) fractionDigits facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaFractionDigitsFacet extends XmlSchemaNumericFacet {

    /** Creates new XmlSchemaFractionDigitsFacet */
    public XmlSchemaFractionDigitsFacet() {
    }
	
	public XmlSchemaFractionDigitsFacet(Object value, boolean fixed) {
		super( value, fixed );
	}

}
