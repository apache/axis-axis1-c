/*
 * XmlSchemaAnnotated.java
 *
 * Created on September 27, 2001, 3:08 AM
 */

package org.apache.axis.xsd.xml.schema;
import org.w3c.dom.Attr;

/**
 * The base class for any element that can contain annotation elements.
 *
 * @author  mukund
 */

// October 15th - momo - initial implementation

public class XmlSchemaAnnotated extends XmlSchemaObject {
	/**
	 * Defines an annotation. 
	 * Creates an annotation element. 
	 * Represents the W3C annotation element.
	 */
	XmlSchemaAnnotation annotation;
	String id;
	
	// Stores qualified attributes that do not belong to the schema target namespace.
	public Attr[] unhandledAttributes;
	
	
    /** Creates new XmlSchemaAnnotated */
    public XmlSchemaAnnotated() {
    }

	public String getId() {
		return id;
	}
	
	public void setId(String id) {
		this.id = id;
	}
	
	public XmlSchemaAnnotation getAnnotation() {
		return annotation;
	}
	
	public void setAnnotation(XmlSchemaAnnotation annotation) {
		this.annotation = annotation;
	}
	
	public Attr[] getUnhandledAttributes() {
		return unhandledAttributes;
	}
	
	public void setUnhandledAttributes(Attr[] unhandledAttributes) {
		this.unhandledAttributes = unhandledAttributes;
	}
	
}

