/*
 * XmlSchemaImport.java
 *
 * Created on September 27, 2001, 3:20 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * The class to import schema components from any schema. 
 * Represents the World Wide Web Consortium (W3C) import element.
 *
 * @author  mukund
 */

public class XmlSchemaImport extends XmlSchemaExternal{

    /** Creates new XmlSchemaImport */
    public XmlSchemaImport() {
		super();
    }

	String namespace;
	
	public String getNamespace(){
		return this.namespace;
	}
	
	public void setNamespace( String namespace){
		this.namespace = namespace;
	}
							  
					 
}
