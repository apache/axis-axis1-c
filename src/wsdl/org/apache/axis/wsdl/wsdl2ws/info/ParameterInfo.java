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

package org.apache.axis.wsdl.wsdl2ws.info;

import javax.xml.namespace.QName;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.wsdl2ws.CUtils;

/**
 * This class stores information about parameters and attributes.
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class ParameterInfo
{
    private Type type;
    private String attribName = null;
    private QName elementName = null;
    private String elementNameAsSOAPString = null;
    private String attribNameAsSOAPString = null;
    private String attribNameAsMember = null;
    private String methodName=null;
    private boolean isAnyElement = false;
    private boolean isArray = false;
    private boolean isAttribute = false;
    private boolean isNillable = false;
    private boolean isOptional = false;
    
    private boolean isSimpleType = true;

    private int maxOccurs = 1;
    private int minOccurs = 1;

    private String typeName;
    
    //this variable states whether the attribute is an xsd:choice
    private boolean isChoiceElement = false;
    
    //this variable states whether the attribute is an xsd:all
    private boolean isAllElement = false;
    
    //This field is set to true if the element is elementFormDefault qualified.
    //This specifies whether the element must be namespace qualified or not in the SOAP message.
    private boolean isNamespaceQualified = false;


    public ParameterInfo()
    {}
    
    public String toString()
    {
        String str ="\n---------BEGIN ParameterInfo------------\n";
        str = str + "type = "                   + type.getName() + "\n";
        str = str + "attribName ="              + attribName + "\n";
        str = str + "attribNameAsMember ="      + attribNameAsMember + "\n";
        str = str + "attribNameAsSOAPString ="  + attribNameAsSOAPString + "\n";
        str = str + "elementName ="             + elementName + "\n";
        str = str + "elementNameAsSOAPString =" + elementNameAsSOAPString + "\n";
        str = str + "isAnyElement ="            + isAnyElement + "\n";
        str = str + "isArray ="                 + isArray + "\n";
        str = str + "isAttribute ="             + isAttribute + "\n";
        str = str + "isNillable = "             + isNillable + "\n";
        str = str + "isOptional = "             + isOptional + "\n";
        
        str = str + "isSimpleType ="          + isSimpleType + "\n";
        str = str + "maxOccurs ="             + maxOccurs + "\n";
        str = str + "minOccurs ="             + minOccurs + "\n";
        str = str + "typeName = "             + typeName + "\n";
        str = str + "choiceElement = "        + isChoiceElement + "\n";
        str = str + "allElement ="            + isAllElement + "\n";
        str = str + "nsQualified ="           + isNamespaceQualified + "\n";
        str = str + "------------END ParameterInfo-------------\n";

        return str;
    }
    
    public boolean isNillable()
    {
        return isNillable;
    }
    
    public void setNillable(boolean nillable)
    {
        isNillable = nillable;
    }
    
    /**
     * @return boolean
     */
    public boolean isArray()
    {
        return isArray;
    }

    /**
     * Sets the isArray.
     * @param isArray The isArray to set
     */
    public void setArray(boolean isArray)
    {
        this.isArray = isArray;
    }

    public boolean isAttribute()
    {
        return this.isAttribute;
    }

    public void setAttribute(boolean isAttribute)
    {
        this.isAttribute = isAttribute;
    }

    public void setParamName(String paramName, TypeMap typeMap)
    {
        // Get the last identifier after anonymous token
        if (paramName.lastIndexOf(SymbolTable.ANON_TOKEN) != -1)
        {
            paramName =
                paramName.substring(paramName.lastIndexOf(SymbolTable.ANON_TOKEN) + 1,
                                    paramName.length());
        }
        
        attribName = paramName;
        attribNameAsSOAPString = paramName;
        
        // Now generate a code-safe representation of the name
        attribNameAsMember = CUtils.sanitizeString(attribName);
        methodName = attribNameAsMember;
        
        if (typeMap != null && typeMap.doesTypeExist(attribNameAsMember))
            attribNameAsMember += "_Ref";
        attribNameAsMember = CUtils.resolveWSDL2LanguageNameClashes(attribNameAsMember);        
    }
    
    public String getParamName()
    {
        return attribName;
    }

    public String getParamNameAsMember()
    {
        return attribNameAsMember;
    }

    public String getParamNameAsSOAPString()
    {
        return attribNameAsSOAPString;
    }

    /**
     * @return boolean
     */
    public boolean isReference()
    {
        return type != null && attribName.equals(type.getLanguageSpecificName());
    }
    
    public Type getType()
    {
        return type;
    }

    public void setType(Type type)
    {
        this.type = type;
    }

    /**
     * @return
     */
    public QName getElementName()
    {
        return elementName;
    }

    public String getElementNameAsSOAPString()
    {
        return elementNameAsSOAPString;
    }

    /**
     * @param name
     */
    public void setElementName(QName name)
    {
        elementName = name;
        if (elementName != null)
        {
            String paramName = elementName.getLocalPart();
            if (paramName.lastIndexOf(SymbolTable.ANON_TOKEN) != -1)
            {
                paramName =
                    paramName.substring(paramName.lastIndexOf(SymbolTable.ANON_TOKEN) + 1,
                                                              paramName.length());
            }
            elementNameAsSOAPString = paramName;            
        }
        else
            elementNameAsSOAPString=null;
    }

    public QName getSchemaName()
    {
        return this.type.getName();
    }

    public String getLangName()
    {
        return this.type.getLanguageSpecificName();
    }

    /**
     * @return
     */
    public boolean isAnyElement()
    {
        return isAnyElement;
    }

    /**
     * @param b
     */
    public void setAnyElement(boolean b)
    {
        isAnyElement = b;
    }

    /**
     * @param b
     */
    public void setOptional(boolean b)
    {
        this.isOptional = b;
        
    }

    public boolean isOptional()
    {
        return isOptional;
    }
    public String getMethodName()
    {
        return methodName;
    }
    
    /**
     * @return String
     */
    public String getTypeName()
    {
        return typeName;
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

    //getter and setter for choiceElement
    public boolean getChoiceElement()
    {
        return this.isChoiceElement;
    }
    
    public void setChoiceElement(boolean newChoiceElement)
    {
        this.isChoiceElement=newChoiceElement;
    }
    
    //getter and setter for allElement
    public boolean getAllElement()
    {
        return this.isAllElement;
    }
    
    public void setAllElement(boolean newAllElement)
    {
        this.isAllElement=newAllElement;
    }
    
    /**
     * Getter and setter for the field nsQualified 
     */
    public boolean getNsQualified()
    {
        return isNamespaceQualified;
    }
    
    public void setNsQualified(boolean nsQual)
    {
        isNamespaceQualified = nsQual;
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
}
