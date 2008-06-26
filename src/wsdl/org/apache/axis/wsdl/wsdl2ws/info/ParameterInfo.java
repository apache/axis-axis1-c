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
 * this class represents Parameter(message in the wsdl) 
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class ParameterInfo
{
    protected Type type;
    protected String attribName = null;
    protected QName elementName = null;
    private String elementNameAsSOAPString = null;
    private String attribNameAsSOAPString = null;
    private String attribNameAsMember = null;
    private String methodName=null;
    private boolean isAnyType = false;
    protected boolean isArray = false;
    private boolean isAttribute = false;
    private boolean isNillable = false;
    private boolean isOptional = false;
    private boolean doGetElementAsCharData=false;

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
        str = str + "isAnyType ="               + isAnyType + "\n";
        str = str + "isArray ="                 + isArray + "\n";
        str = str + "isAttribute ="             + isAttribute + "\n";
        str = str + "isNillable = "             + isNillable + "\n";
        str = str + "isOptional = "             + isOptional + "\n";
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
        
        if (typeMap != null && CUtils.classExists(typeMap, attribNameAsMember))
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
    public boolean isAnyType()
    {
        return isAnyType;
    }

    /**
     * @param b
     */
    public void setAnyType(boolean b)
    {
        isAnyType = b;
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

    public void setMethodName(String methodName)
    {
        this.methodName = methodName;
    }

    public void setGetElementAsCharData(boolean b)
    {
        this.doGetElementAsCharData = true;
        
    }

    public boolean getElementAsCharData()
    {
        return doGetElementAsCharData;
    }
}
