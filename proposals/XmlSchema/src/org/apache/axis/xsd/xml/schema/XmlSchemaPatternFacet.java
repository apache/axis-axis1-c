/*
 * XmlSchemaPatternFacet.java
 *
 * Created on September 27, 2001, 3:33 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining pattern facets. Represents the World Wide 
 * Web Consortium (W3C) pattern facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaPatternFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaPatternFacet */
    public XmlSchemaPatternFacet() {
    }

	public XmlSchemaPatternFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
