/*
 * XmlSchemaObjectCollection.java
 *
 * Created on September 27, 2001, 2:58 AM
 */

package org.apache.axis.xsd.xml.schema;
import java.util.Vector;
import java.util.Iterator;

/**
 * An object collection class to handle XmlSchemaObjects when collections
 * are returned from method calls.
 *
 * @author  mukund
 */
public class XmlSchemaObjectCollection {

	Vector objects;
	
    /** Creates new XmlSchemaObjectCollection */
    public XmlSchemaObjectCollection() {
		objects = new Vector();
    }
	
	public int getCount() {
		return objects.size();
	}
	
	public XmlSchemaObject getItem(int i) {
		return (XmlSchemaObject)objects.elementAt(i);
	}

	public void setItem(int i, XmlSchemaObject item) {
		objects.insertElementAt(item, i);
	}
	
	public void add(XmlSchemaObject item) {
		objects.addElement(item);
	}
	
	public boolean contains(XmlSchemaObject item) {
		return objects.contains(item);
	}
	
	public int indexOf(XmlSchemaObject item) {
		return objects.indexOf(item);
	}
	
	public void remove(XmlSchemaObject item) {
		objects.remove(item);
	}
	
	public void removeAt(int index) {
		objects.removeElementAt(index);
	}
	
	public Iterator getIterator() {
		return objects.iterator();
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		
		for(int i=0;i<getCount();i++) {
			xml += getItem(i).toString(prefix, tab);
		}

		
		return xml;
			
	}
}
