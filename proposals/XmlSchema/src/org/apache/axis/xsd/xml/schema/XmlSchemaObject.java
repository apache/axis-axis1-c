/*
 * XmlSchemaObject.java
 *
 * Created on September 27, 2001, 3:07 AM
 */

package org.apache.axis.xsd.xml.schema;

/**
 *
 * @author  mukund
 */

// October 15th - momo - initial implementation

public abstract class XmlSchemaObject {
	int lineNumber;
	int linePosition;
	String sourceURI;
		
    /** Creates new XmlSchemaObject */
    protected XmlSchemaObject() {
    }
	
	public int getLineNumber() {
		return lineNumber;
	}
	
	public void setLineNumber(int lineNumber) {
		this.lineNumber = lineNumber;
	}
	
	public int getLinePosition() {
		return linePosition;
	}
	
	public void setLinePosition(int linePosition) {
		this.linePosition = linePosition;
	}
	
	public String getSourceURI() {
		return sourceURI;
	}
	
	public void setSourceURI(String sourceURI) {
		this.sourceURI = sourceURI;
	}
	
	public boolean equals(Object what) {
		// toDO : implement this once everything completed
		return true;
	}
	
	public String toString(String prefix, int tab) { 
		String xml = new String();
		for(int i=0;i<tab;i++)
			xml += "\t";
		
		xml += this.getClass().toString() + "\n";
		return xml;
	}
}
