package org.apache.axismora.wsdl2ws.info;

import javax.xml.namespace.QName;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ElementInfo {
	public static int UNBOUNDED = 999999999; 
	private QName name; 
	private Type type;
	private int maxOccurs = 1;
	private int minOccurs = 1;

	public ElementInfo(QName name,Type type){
		this.name = name;
		this.type = type;
		
		if(this.name == null || this.type == null)
			throw new RuntimeException("name or type of the ElementInfo can not be null ");
	}
	
	/**
	 * @return int
	 */
	public int getMaxOccurs() {
		return maxOccurs;
	}

	/**
	 * @return int
	 */
	public int getMinOccurs() {
		return minOccurs;
	}

	/**
	 * @return QName
	 */
	public QName getName() {
		return name;
	}

	/**
	 * @return QName
	 */
	public Type getType() {
		return type;
	}

	/**
	 * Sets the maxOccurs.
	 * @param maxOccurs The maxOccurs to set
	 */
	public void setMaxOccurs(int maxOccurs) {
		this.maxOccurs = maxOccurs;
	}

	/**
	 * Sets the minOccurs.
	 * @param minOccurs The minOccurs to set
	 */
	public void setMinOccurs(int minOccurs) {
		this.minOccurs = minOccurs;
	}

	/**
	 * Sets the name.
	 * @param name The name to set
	 */
	public void setName(QName name) {
		this.name = name;
	}

	/**
	 * Sets the type.
	 * @param type The type to set
	 */
	public void setType(Type type) {
		this.type = type;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		String str = "("+name+","+type.getName()+"| max = "+maxOccurs+" min ="+minOccurs+"|)\n";
		return str;
	}

}
