/*
 * XmlSchemaRedefine.java
 *
 * Created on September 27, 2001, 3:20 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 * Allows simple and complex types, groups, and attribute groups from 
 * external schema files to be redefined in the current schema. This 
 * class provides versioning for the schema elements. Represents the
 * World Wide Web Consortium (W3C) redefine element.
 *
 * @author  mukund
 */

public class XmlSchemaRedefine  extends XmlSchemaExternal {

    /** Creates new XmlSchemaRedefine */
    public XmlSchemaRedefine() {
        items = new XmlSchemaObjectCollection();
    }

	XmlSchemaObjectTable attributeGroups, groups, schemaTypes;
	
	public XmlSchemaObjectTable getAttributeGroup() {
		return attributeGroups;
	}
	
	public XmlSchemaObjectTable getGroup() {
		return groups;
	}
	
	XmlSchemaObjectCollection items;
	
	public XmlSchemaObjectCollection getItems() {
		return items;
	}
	
	public XmlSchemaObjectTable getSchemaTypes() {
		return schemaTypes;
	}
	
}
