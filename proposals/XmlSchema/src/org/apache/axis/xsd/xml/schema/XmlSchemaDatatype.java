/*
 * XmlSchemaDatatype.java
 *
 * Created on September 27, 2001, 3:07 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.apache.axis.xsd.xml.XmlTokenizedType;

/**
 *
 * @author  mukund
 */

public abstract class XmlSchemaDatatype {

    /** Creates new XmlSchemaDatatype */
    public XmlSchemaDatatype() {
    }
	
	public abstract Object parseValue(Object input);
	public abstract Class valueType();
	public abstract XmlTokenizedType tokenizedType();

}
