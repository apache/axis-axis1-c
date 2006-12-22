/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
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
 */
public class AttributeInfo extends ParameterInfo
{
    private boolean isSimpleType = true;
    private boolean isAttribute = false;
    private boolean isOptional = false;

    private int maxOccurs = 1;
    private int minOccurs = 1;

    private String typeName;
    private String typeNamespace;
    private String className;
    private String attribNameAsMember;
    private String methodName;
    
    //this variable states whether the attribute is an xsd:choice
    private boolean choiceElement = false;
    
    //this variable states whether the attribute is an xsd:all
    private boolean allElement = false;
    
    //This field is set to true if the element is elementFormDefault qualified.
    //This specifies whether the element must be namespace qualified or not in the SOAP message.
    private boolean nsQualified = false;
    
    public String toString()
    {
        String str = "\n---------BEGIN AttributeInfo------------\n";
        str = str + super.toString();
        str = str + "isOptional = "           + isOptional + "\n";
        str = str + "isAttribute ="           + isAttribute + "\n";
        str = str + "isSimpleType ="          + isSimpleType + "\n";
        str = str + "maxOccurs ="             + maxOccurs + "\n";
        str = str + "minOccurs ="             + minOccurs + "\n";
        str = str + "typeName = "             + typeName + "\n";
        str = str + "typeNamespace = "        + typeNamespace + "\n";
        str = str + "className ="             + className + "\n";
        str = str + "attribNameAsMember ="    + attribNameAsMember + "\n";
        str = str + "choiceElement = "        + choiceElement + "\n";
        str = str + "allElement ="            + allElement + "\n";
        str = str + "nsQualified ="           + nsQualified + "\n";

        str = str + "-----------END AttributeInfo---------------\n";

        return str;
    }
    
    
    /**
     */
    public AttributeInfo(String className)
    {
        this.className = className;
    }

    /**
     * @return boolean
     */
    public boolean isAttribute()
    {
        return isAttribute;
    }

    /**
     * @return boolean
     */
    public boolean isOptional()
    {
        return isOptional;
    }
    /**
     * Sets the isAttribute.
     * @param isAttribute The isAttribute to set
     */
    public void setAttribute(boolean isAttribute)
    {
        this.isAttribute = isAttribute;
    }

    /**
     * Sets the isOptional.
     * @param isOptional The isOptional to set
     */
    public void setOptional(boolean isOptional)
    {
        this.isOptional = isOptional;
    }
    /**
     * @return String
     */
    public String getTypeName()
    {
        return typeName;
    }

    /**
     * @return String
     */
    public String getTypeNamespace()
    {
        return typeNamespace;
    }

    /**
     * Sets the typeName.
     * @param typeName The typeName to set
     */
    public void setTypeName(String typeName)
    {
        this.typeName = typeName;
    }

    /**
     * Sets the typeNamespace.
     * @param typeNamespace The typeNamespace to set
     */
    public void setTypeNamespace(String typeNamespace)
    {
        this.typeNamespace = typeNamespace;
    }

    /**
     * @return boolean
     */
    public boolean isSimpleType()
    {
        return isSimpleType;
    }

    /**
     * Sets the isSimpleType.
     * @param isSimpleType The isSimpleType to set
     */
    public void setSimpleType(boolean isSimpleType)
    {
        this.isSimpleType = isSimpleType;
    }

    // TODO - probably can remove since we sanitize attribute name.
    public String getParamNameAsMember()
    {
        this.attribNameAsMember = super.getParamNameWithoutSymbols();
        
        // need to deal with _Ref stuff :(
        if (this.className != null && this.className.equals(attribNameAsMember))
            this.attribNameAsMember = "m_" + this.attribNameAsMember;

        return this.attribNameAsMember;
    }

    public void setParamName(String paramName)
    {
        super.setParamName(paramName);
        
        // TODO - probably can remove since we sanitize attribute name.
        // make sure attributes does not have the same name as class name
        if (this.className != null && this.className.equals(attribName))
            this.attribNameAsMember = "m_" + attribName;
        else
            this.attribNameAsMember = attribName;
    }
    
    //getter and setter for choiceElement
    public boolean getChoiceElement()
    {
        return this.choiceElement;
    }
    
    public void setChoiceElement(boolean newChoiceElement)
    {
        this.choiceElement=newChoiceElement;
    }
    
    //getter and setter for allElement
    public boolean getAllElement()
    {
        return this.allElement;
    }
    
    public void setAllElement(boolean newAllElement)
    {
        this.allElement=newAllElement;
    }
    
    /**
     * Getter and setter for the field nsQualified 
     */
    public boolean getNsQualified()
    {
        return nsQualified;
    }
    
    public void setNsQualified(boolean nsQual)
    {
        nsQualified = nsQual;
    }

    /**
     * @return int
     */
    public int getMaxOccurs()
    {
        return this.maxOccurs;
    }

    /**
     * @return int
     */
    public int getMinOccurs()
    {
        return this.minOccurs;
    }
    /**
     * Sets the maxOccurs.
     * @param maxOccurs The maxOccurs to set
     */
    public void setMaxOccurs(int maxOccurs)
    {
        this.maxOccurs = maxOccurs;
    }

    /**
     * Sets the minOccurs.
     * @param minOccurs The minOccurs to set
     */
    public void setMinOccurs(int minOccurs)
    {
        this.minOccurs = minOccurs;
    }
    
    public String getMethodName()
    {
        return methodName;
    }

    public void setMethodName(String methodName)
    {
        this.methodName = methodName;
    }
}
