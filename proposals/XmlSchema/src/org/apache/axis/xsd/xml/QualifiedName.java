package org.apache.axis.xsd.xml;


/**
 * @author momo
 */

// Oct 15th - Momo - Initial Impl

public class QualifiedName {

	String name, namespace;
	
    public QualifiedName() {
    }
	
	public QualifiedName(String name) {
		this.name = name;
	}
	
	public QualifiedName(String name, String namespace) {
		this.name = name;
		this.namespace = namespace;
	}
	
	
	public boolean isEmpty() {
		return (name == null);
	}
	
	public String getName() {
            if (name.indexOf(":")<0)
		return name;
            else
                return (name.substring(name.indexOf(":")+1));
	}

	public String getNameSpace() {
		return namespace;
	}
	
	public String toString() {
		return name;
	}
}
