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

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ElementInfo
{
    public static int UNBOUNDED = 999999999;
    private QName name;
    private Type type;
    private int maxOccurs = 1;
    private int minOccurs = 1;
    private boolean nillable = false;

    public ElementInfo(QName name, Type type)
    {
        this.name = name;
        this.type = type;

        if (this.name == null || this.type == null)
        {
            throw new RuntimeException("name or type of the ElementInfo can not be null ");
        }
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
     * @return QName
     */
    public QName getName()
    {
        return this.name;
    }

    /**
     * @return QName
     */
    public Type getType()
    {
        return this.type;
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

    /**
     * Sets the name.
     * @param name The name to set
     */
    public void setName(QName name)
    {
        this.name = name;
    }

    /**
     * Sets the type.
     * @param type The type to set
     */
    public void setType(Type type)
    {
        this.type = type;
    }

	/**
	 * @return boolean
	 */
	public boolean getNillable()
	{
		return this.nillable;
	}

	/**
	 * @param boolean
	 */
	public void setNillable( boolean newNillable)
	{
		this.nillable = newNillable;
	}

    /* (non-Javadoc)
     * @see java.lang.Object#toString()
     */
    public String toString()
    {
        String str =
            "("
                + name
                + ","
                + type.getName()
                + "| max = "
                + maxOccurs
                + " min ="
                + minOccurs
                + "|)\n";
        return str;
    }

}
