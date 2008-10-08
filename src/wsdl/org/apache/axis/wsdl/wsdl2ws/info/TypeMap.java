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

import java.util.Collection;
import java.util.Hashtable;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.CUtils;

/**
 * Type map has information about all the custom types in the WSDL.
 * The type map registers the types against the XML QName in WSDL. 
 *
 * e.g.  C++  {urn:ns}classname -> ns:classname
 * 
 * @author hemapani 
 * @author nadir amra (amra@us.ibm.com) 
 */
public class TypeMap
{
    public static final String ANON_TOKEN_STRING = ">";
    public static final char   ANON_TOKEN_CHAR   = '>';
    
    // this map stores custom type generated from WSDL
    private Hashtable typeInfo = new Hashtable();
    
    /**
     * Constructor
     */
    public TypeMap()
    {
    }

    /**
     * Returns customer type from map.  Note that primitive basic types
     * are generated on-the-fly.
     * 
     * @param name
     * @return
     */
    public Type getType(QName name)
    {
        if (CUtils.isPrimitiveType(name)) 
            return new Type(name, null);

        return (Type) this.typeInfo.get(name);
    }

    /**
     * Add a type to the map. 
     * 
     * @param qname
     * @param type
     */
    public void addType(QName qname, Type type)
    {
        this.typeInfo.put(qname, type);
    }

    /**
     * Remove type from the map.
     * 
     * @param wsdlname
     */
    public void removeType(QName wsdlname)
    {
        this.typeInfo.remove(wsdlname);
    }

    /**
     * Get all the types in the map.
     * 
     * @return
     */
    public Collection getTypes()
    {
        return this.typeInfo.values();
    }
    
    /**
     * Determines if a type exists in the map.
     * 
     * @param name
     * @return
     */
    public boolean doesTypeExist(String name)
    {   
        Type atype;
        String atypeName;
        Iterator types = getTypes().iterator();
        while (types.hasNext())
        {
            atype = (Type) types.next();
            if (!atype.isExternalized())
                continue;

            atypeName = atype.getLanguageSpecificName();
            if (null != atypeName && atypeName.equals( name ))
                return true;
        }
        
        return false;
    }
    
    /**
     * Checks whether the string represents an anonymous type name.
     * 
     * @param type
     * @return
     */
    public static boolean isAnonymousType(String type)
    {
        if (type != null)
            return type.charAt(0) == ANON_TOKEN_CHAR;

        return false;
    }

    /**
     * Checks to see if the QName represents an anonymous type.
     * 
     * @param type
     * @return
     */
    public static boolean isAnonymousType(QName type)
    {
        if (type != null)
            return isAnonymousType(type.getLocalPart());
        
        return false;
    }    
    
    /**
     * Dump all the types in the collection to stdout.
     */
    public void dump()
    {
        System.out.println( "Dumping typeMap....");
        
        Iterator it = getTypes().iterator();
        while (it.hasNext())
        {
            System.out.println(it.next());
        }   
    }
}
