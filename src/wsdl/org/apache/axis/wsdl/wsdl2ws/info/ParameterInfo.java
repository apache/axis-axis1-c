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
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

/**
 * this class represents Parameter(message in the wsdl) 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ParameterInfo {
    protected Type type;
    protected String attribName;
	protected QName elementName;
	private boolean isAnyType = false;
	protected boolean isArray = false;	
	private boolean isAttribute = false;
	
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
	
	public boolean isAttribute(){
		return this.isAttribute;
	}
	
	public void setAttribute(boolean isAttribute)
	{
		this.isAttribute = isAttribute;
	}
	
    public String getParamName() {
		// TODO: design review needed
		// 		- If type and name are equals add "_Ref" ie : ref="..."
		String result;

                if (attribName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1 )
                {
                    attribName =attribName.substring(attribName.lastIndexOf(SymbolTable.ANON_TOKEN)+1,attribName.length());
                }
                // Samisa: This second call to TypeMap.resoleveWSDL2LanguageNameClashes
                // is made to make sure after replacinf ANON_TOKEN it is still not a keyword
                attribName = TypeMap.resolveWSDL2LanguageNameClashes(attribName, WrapperConstants.LANGUAGE_CPP);

		if (isReference())
			result = attribName + "_Ref";
		else
			result = attribName;
		return result;	        
    }

    public String getParamNameAsSOAPElement() {
                String result = attribName;

                if (attribName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1 )
                {
                    result =attribName.substring(attribName.lastIndexOf(SymbolTable.ANON_TOKEN)+1,attribName.length());
                }
                return result;
    }

	/**
	 * @return boolean
	 */
	public boolean isReference() {
		return type != null && attribName.equals(type.getLanguageSpecificName());
	}

    public void setParamName(String paramName) {
        //Samisa: 21/08/2004
        if (paramName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1 )
        {
            paramName = paramName.substring(paramName.lastIndexOf(SymbolTable.ANON_TOKEN)+1,paramName.length());
        }
        paramName = TypeMap.resolveWSDL2LanguageNameClashes(paramName, WrapperConstants.LANGUAGE_CPP);
        //Samisa
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
    //Samisa 21/08/2004
    public String getElementNameAsString() {
        String paramName = elementName.getLocalPart();
        if (paramName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1 )
        {
            paramName = paramName.substring(paramName.lastIndexOf(SymbolTable.ANON_TOKEN)+1,paramName.length());
        }
        paramName = TypeMap.resolveWSDL2LanguageNameClashes(paramName, WrapperConstants.LANGUAGE_CPP);
	return paramName;

    }
    //Samisa

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

	/**
	 * @return
	 */
	public boolean isAnyType() {
		return isAnyType;
	}

	/**
	 * @param b
	 */
	public void setAnyType(boolean b) {
		isAnyType = b;
	}
	
}
