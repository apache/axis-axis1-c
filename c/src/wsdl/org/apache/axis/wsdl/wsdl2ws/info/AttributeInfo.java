/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/*
 * Created on Jan 12, 2004
 *
 */
 
package org.apache.axis.wsdl.wsdl2ws.info;

/**
 * @author Susantha Kumara (skumara@virtusa.com, susantha@opensource.lk)
 *
 *  
 * 
 */
public class AttributeInfo extends ParameterInfo {
	private boolean isSimpleType = true;
	private boolean isAttribute = false;
	private boolean isOptional = false;
	private boolean isArray = false;
	private String typeName;
	private String typeNamespace;
	
	/**
	 * @param type
	 * @param attribName
	 */
	public AttributeInfo() {
		// TODO Auto-generated constructor stub
	}
	
	/**
	 * @return boolean
	 */
	public boolean isAttribute() {
		return isAttribute;
	}

	/**
	 * @return boolean
	 */
	public boolean isOptional() {
		return isOptional;
	}
	/**
	 * Sets the isAttribute.
	 * @param isAttribute The isAttribute to set
	 */
	public void setAttribute(boolean isAttribute) {
		this.isAttribute = isAttribute;
	}

	/**
	 * Sets the isOptional.
	 * @param isOptional The isOptional to set
	 */
	public void setOptional(boolean isOptional) {
		this.isOptional = isOptional;
	}
	/**
	 * @return String
	 */
	public String getTypeName() {
		return typeName;
	}

	/**
	 * @return String
	 */
	public String getTypeNamespace() {
		return typeNamespace;
	}

	/**
	 * Sets the typeName.
	 * @param typeName The typeName to set
	 */
	public void setTypeName(String typeName) {
		this.typeName = typeName;
	}

	/**
	 * Sets the typeNamespace.
	 * @param typeNamespace The typeNamespace to set
	 */
	public void setTypeNamespace(String typeNamespace) {
		this.typeNamespace = typeNamespace;
	}

	/**
	 * @return boolean
	 */
	public boolean isArray() {
		return isArray;
	}

	/**
	 * Sets the isArray.
	 * @param isArray The isArray to set
	 */
	public void setArray(boolean isArray) {
		this.isArray = isArray;
	}

	/**
	 * @return boolean
	 */
	public boolean isSimpleType() {
		return isSimpleType;
	}

	/**
	 * Sets the isSimpleType.
	 * @param isSimpleType The isSimpleType to set
	 */
	public void setSimpleType(boolean isSimpleType) {
		this.isSimpleType = isSimpleType;
	}

}
