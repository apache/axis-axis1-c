/*
 * XmlSchemaContentModel.java
 *
 * Created on September 27, 2001, 3:18 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * An abstract class for the schema content model.
 *
 * @author  mukund
 */

// Vidyanand - 16th Oct - initial implementation

public abstract class XmlSchemaContentModel extends XmlSchemaAnnotated{

    /** Creates new XmlSchemaContentModel */
    protected XmlSchemaContentModel() {
    }

	public abstract void setContent(XmlSchemaContent content);
	
	public abstract XmlSchemaContent getContent();
}
