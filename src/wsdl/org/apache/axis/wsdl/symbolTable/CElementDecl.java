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

package org.apache.axis.wsdl.symbolTable;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.info.Type;

/**
 * Simple utility struct for holding element declarations.
 * 
 * This simply correlates a QName to a TypeEntry.
 * 
 * @author Glen Daniels (gdaniels@apache.org)
 * @author Tom Jordahl (tomj@apache.org)
 */
public class CElementDecl //extends ElementDecl
{
    public static int UNBOUNDED = 999999999;
    
    private QName name;
    private TypeEntry typeEntry = null;
    private Type type = null;

    // An item that is not set and has minOccurs=0 should not be passed over the wire.  This
    // is slightly different than nillable=true which causes nil=true to be passed over the wire.
    private int minOccurs = 1;
    private int maxOccurs = 1;
    private boolean nillable = false;
    private boolean optional = false;

    // Indicate if the CElementDecl represents an xsd:any element
    private boolean anyElement = false;
    
    // indicate if the CElementDecl represents an xsd:choice element 
    private boolean choiceElement = false;
    
    // indicate if the CElementDecl represents an xsd:all element 
    private boolean allElement = false;
    
    //This field is set to true if the element is elementFormDefault qualified.
    //This specifies whether the element must be namespace qualified or not in the SOAP message.
    private boolean nsQualified = false;
    
    /** Field documentation */
    private String documentation;

    public CElementDecl(TypeEntry type, QName name)
    {
        this.typeEntry = type;
        this.name = name;
    }

    public CElementDecl(Type type, QName name)
    {
        this.type = type;
        this.name = name;
    }    
    
    public TypeEntry getTypeEntry()
    {
        return this.typeEntry;
    }

    public void setTypeEntry(TypeEntry type)
    {
        this.typeEntry = type;
    }
    
    public Type getType()
    {
        return this.type;
    }

    public void setType(Type type)
    {
        this.type = type;
    }
    
    public QName getName()
    {
        return this.name;
    }

    public void setName(QName name)
    {
        this.name = name;
    }

    public boolean isMinOccurs0()
    {
        return minOccurs == 0;
    }

    public boolean isMaxOccursUnbounded() 
    {
        return maxOccurs == UNBOUNDED;
    }
    
    public boolean isMaxOccursExactlyOne() 
    {
        return maxOccurs == 1;
    }
    
    public boolean getAnyElement()
    {
        return this.anyElement;
    }

    public void setAnyElement(boolean anyElement)
    {
        this.anyElement = anyElement;
    }
    
    public boolean getChoiceElement()
    {
        return this.choiceElement;
    }

    public void setChoiceElement(boolean choiceElement)
    {
        this.choiceElement = choiceElement;
    }
    
    public boolean getAllElement()
    {
        return this.allElement;
    }

    public void setAllElement(boolean allElement)
    {
        this.allElement = allElement;
    }

    public boolean getNsQualified()
    {
        return nsQualified;
    }

    public void setNsQualified(boolean nsQual)
    {
        nsQualified = nsQual;
    }

    public int getMaxOccurs()
    {
        return this.maxOccurs;
    }

    public int getMinOccurs()
    {
        return this.minOccurs;
    }

    public boolean isNillable()
    {
        return this.nillable;
    }

    public void setMaxOccurs(int i)
    {
        maxOccurs = i;
    }

    public void setMinOccurs(int i)
    {
        minOccurs = i;
    }

    public void setNillable(boolean b)
    {
        this.nillable = b;
    }

    public void setOptional(boolean optional)
    {
        this.optional = optional;
    }

    public boolean getOptional()
    {
        return optional;
    }

    public String getDocumentation()
    {
        return this.documentation;
    }

    public void setDocumentation(String documentation)
    {
        this.documentation = documentation;
    }
}