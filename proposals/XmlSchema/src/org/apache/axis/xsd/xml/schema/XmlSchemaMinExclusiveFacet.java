/*
 * XmlSchemaMinExclusive.java
 *
 * Created on September 27, 2001, 3:22 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Class for defining minExclusive facets. Represents the World 
 * Wide Web Consortium (W3C) minExclusive facet.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public class XmlSchemaMinExclusiveFacet extends XmlSchemaFacet {

    /** Creates new XmlSchemaMinExclusive */
    public XmlSchemaMinExclusiveFacet() {
    }
	
	public XmlSchemaMinExclusiveFacet(Object value, boolean fixed) {
		super( value, fixed );
	}

}
