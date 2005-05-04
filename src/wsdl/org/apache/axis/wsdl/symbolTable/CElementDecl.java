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
    private QName name;
    private TypeEntry type;

    private int minOccurs = 1;
    private int maxOccurs = 1;
    private boolean nillable = false;

    // The following property is set if minOccurs=0.
    // An item that is not set and has minOccurs=0 
    // should not be passed over the wire.  This
    // is slightly different than nillable=true which
    // causes nil=true to be passed over the wire.
    private boolean minOccursIs0 = false;

    // Indicate if the CElementDecl represents
    // an xsd:any element
    private boolean anyElement = false;
    
    // Dushshantha:
    // indicate if the CElementDecl represents 
    // an xsd:choice element 
    private boolean choiceElement = false;

    /** Field documentation */
    private String documentation;

    public CElementDecl()
    {}

    public CElementDecl(TypeEntry type, QName name)
    {
        this.type = type;
        this.name = name;
    }

    public TypeEntry getType()
    {
        return this.type;
    }

    public void setType(TypeEntry type)
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

    public boolean getMinOccursIs0()
    {
        return this.minOccursIs0;
    }

    public void setMinOccursIs0(boolean minOccursIs0)
    {
        this.minOccursIs0 = minOccursIs0;
    }

    public boolean getAnyElement()
    {
        return this.anyElement;
    }

    public void setAnyElement(boolean anyElement)
    {
        this.anyElement = anyElement;
    }
    
    // Dushshantha:
    //setters and getters for choiceElement
    
    public boolean getChoiceElement()
    {
        return this.choiceElement;
    }

    public void setChoiceElement(boolean choiceElement)
    {
        this.choiceElement = choiceElement;
    }
    
    /**
     * @return
     */
    public int getMaxOccurs()
    {
        return this.maxOccurs;
    }

    /**
     * @return
     */
    public int getMinOccurs()
    {
        return this.minOccurs;
    }

    /**
     * @return
     */
    public boolean isNillable()
    {
        return this.nillable;
    }

    /**
     * @param i
     */
    public void setMaxOccurs(int i)
    {
        maxOccurs = i;
    }

    /**
     * @param i
     */
    public void setMinOccurs(int i)
    {
        minOccurs = i;
    }

    /**
     * @param b
     */
    public void setNillable(boolean b)
    {
		this.nillable = b;
    }

    /**
     *       Method getDocumentation
     *       @return string       
     */

    public String getDocumentation()
    {
        return this.documentation;
    }

    /**
     *       Method setDocumentation
     *       @param documentation
     */

    public void setDocumentation(String documentation)
    {
        this.documentation = documentation;
    }

}
