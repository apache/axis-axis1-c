/*
 * XmlSchemaSimpleTypeList.java
 *
 * Created on September 27, 2001, 3:38 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Class for the list of simpleType elements. Defines a simpleType element
 * as a list of values of a specified data type. Represents the World Wide
 * Web Consortium (W3C) list element.
 *
 * @author  mukund
 */
public class XmlSchemaSimpleTypeList extends XmlSchemaSimpleTypeContent{

    /** Creates new XmlSchemaSimpleTypeList */
    public XmlSchemaSimpleTypeList() {
    }
	
	XmlSchemaSimpleType itemType;
	
	public XmlSchemaSimpleType getItemType() {
		return this.itemType;
	}
	
	public void setItemType( XmlSchemaSimpleType itemType ) {
		this.itemType = itemType;
	}
	
	QualifiedName itemTypeName;
	
	public QualifiedName getItemTypeName() {
		return this.itemTypeName;
	}
	
	public void setItemTypeName( QualifiedName itemTypeName){
		this.itemTypeName = itemTypeName;
	}

}
