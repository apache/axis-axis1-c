/*
 * XmlSchemaLengthFacet.java
 *
 * Created on September 27, 2001, 3:24 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining length facets. Represents the World Wide Web 
 * Consortium (W3C) length facet.  
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaLengthFacet extends XmlSchemaNumericFacet{

    /** Creates new XmlSchemaLengthFacet */
    public XmlSchemaLengthFacet() {
    }

	public XmlSchemaLengthFacet(Object value, boolean fixed) {
		super( value, fixed );
	}
}
