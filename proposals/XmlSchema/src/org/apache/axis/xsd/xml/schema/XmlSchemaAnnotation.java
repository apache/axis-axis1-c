/*
 * XmlSchemaAnnotation.java
 *
 * Created on September 27, 2001, 3:40 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

/**
 * Defines an annotation. Represents the World Wide Web Consortium (W3C)
 * annotation element.
 *
 * @author  mukund
 */

// October 15th - momo  - initial implementation
// Feb 15th 2002 - Joni - items initialized when instantiated.

public class XmlSchemaAnnotation extends XmlSchemaObject {
    XmlSchemaObjectCollection items;
	
    /** Creates new XmlSchemaAnnotation */
    public XmlSchemaAnnotation() {
        items = new XmlSchemaObjectCollection();
    }
	
    public XmlSchemaObjectCollection getItems() {
            return items;
    }
}
