/*
 * XmlSchemaObjectTable.java
 *
 * Created on September 27, 2001, 3:41 AM
 */

package org.apache.axis.xsd.xml.schema;

import java.util.Hashtable;
import java.util.Enumeration;
import org.apache.axis.xsd.xml.QualifiedName;

/**
 * A collection class that provides read-only helpers for XmlSchemaObject 
 * objects. This class is used to provide the collections for contained 
 * elements that are within the schema as collections that are accessed 
 * from the XmlSchema class (for example, Attributes, AttributeGroups, 
 * Elements, and so on).
 *
 * @author  mukund
 */

// Vidyanand - 17th Oct - initial implementation

public class XmlSchemaObjectTable {

	Hashtable collection;
    /** Creates new XmlSchemaObjectTable */
    public XmlSchemaObjectTable() {
		this.collection = new Hashtable();;
    }
	
	public int getCount() {
		return this.collection.size();
	}
	
	public XmlSchemaObject getItem( QualifiedName name ) {
		return (XmlSchemaObject) collection.get(name);
	}
	
	public Enumeration getNames(){
		return collection.keys();
	}

	public Enumeration getValues(){
		return collection.elements();
	}
	
	public boolean contains(QualifiedName name) {
		return collection.contains( name );
	}
	
	//TODO: think of smthg better 
	public Object getEnumerator(){
		return null;
	}
	
}
