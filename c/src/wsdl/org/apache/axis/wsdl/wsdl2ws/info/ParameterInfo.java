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

package org.apache.axis.wsdl.wsdl2ws.info;

import javax.xml.namespace.QName;

/**
 * this class represents Parameter(message in the wsdl) 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ParameterInfo {
    protected Type type;
    protected String attribName;
	protected QName elementName;
	
    public String getParamName() {
		// TODO: design review needed
		// 		- If type and name are equals add "_Ref" ie : ref="..."
		String result;
		if (isReference())
			result = attribName + "_Ref";
		else
			result = attribName;
		return result;	        
    }

	/**
	 * @return boolean
	 */
	public boolean isReference() {
		return type != null && attribName.equals(type.getLanguageSpecificName());
	}

    public void setParamName(String paramName) {
        this.attribName = paramName;
    }

    public ParameterInfo(Type type,String attribName) {
        this.type = type;
        this.attribName = attribName;
    }
    public Type getType() {
        return type;
    }

	/**
	 * 
	 */
	public ParameterInfo() {}

    /**
     * @return
     */
    public QName getElementName() {
        return elementName;
    }

    /**
     * @param name
     */
    public void setElementName(QName name) {
        elementName = name;
    }
    
	public QName getSchemaName(){
		return this.type.getName();
	}
	
	public String getLangName(){
		return this.type.getLanguageSpecificName();
	}

	/**
	 * Sets the type.
	 * @param type The type to set
	 */
	public void setType(Type type) {
		this.type = type;
	}

}
