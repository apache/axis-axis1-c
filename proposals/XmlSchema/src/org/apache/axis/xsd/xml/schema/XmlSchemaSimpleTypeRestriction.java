/*
 * XmlSchemaSimpleTypeRestriction.java
 *
 * Created on September 27, 2001, 3:38 AM
 */

package org.apache.axis.xsd.xml.schema;

import org.apache.axis.xsd.xml.QualifiedName;

/**
 * Class for the restriction of simpleType elements. Represents the World
 * Wide Web Consortium (W3C) restriction element for simple types.
 *
 * @author  mukund
 */

public class XmlSchemaSimpleTypeRestriction extends XmlSchemaSimpleTypeContent{

    /** Creates new XmlSchemaSimpleTypeRestriction */
    public XmlSchemaSimpleTypeRestriction() {
		facets = new XmlSchemaObjectCollection();
    }
	
	XmlSchemaSimpleType baseType;
	
	public	XmlSchemaSimpleType getBaseType() {
		return this.baseType;
	}
	
	public void setBaseType( XmlSchemaSimpleType baseType ) {
		this.baseType = baseType;
	}
	
	QualifiedName baseTypeName;
	
	public QualifiedName getBaseTypeName(){
		return this.baseTypeName;
	}
	
	public void setBaseTypeName( QualifiedName baseTypeName ) {
		this.baseTypeName = baseTypeName;
	}
	
	XmlSchemaObjectCollection facets;// = new XmlSchemaObjectCollection();
	
	public XmlSchemaObjectCollection getFacets() {
		return this.facets;
	}
	
	public String toString(String prefix, int tab) {
		String xml = new String();
		
		if(!prefix.equals("") && prefix.indexOf(":") == -1)
			prefix += ":";
		
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += "<"+prefix + "restriction ";
		
		if(baseTypeName != null) {
			xml += "base =\"" +  baseTypeName + "\">\n";
		} else {
			xml += ">\n";
			// inline def
			xml += baseType.toString(prefix, (tab+1));
		}	
		
		xml += facets.toString(prefix, (tab+1));
		for(int i=0;i<tab;i++)
			xml += "\t";
		xml += "</"+prefix+"restriction>\n";	
	
		
		return xml;
			
	}

}
