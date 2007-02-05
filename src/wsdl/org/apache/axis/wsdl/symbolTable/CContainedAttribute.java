/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.axis.wsdl.symbolTable;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.CUtils;

public class CContainedAttribute 
{
    /** Field qname - the qname. Immutable, no setter for  it. */
    protected QName qname;
    
    /** Field name - attibute name used in generated code.  Immutable, no setter for  it. */
    protected String name;
    
    /** Field typeEntry - immutable, no setter for  it. */
    protected TypeEntry typeEntry;       
  
    /** Field type - corresponds to TypeEntry. */
    protected Type type = null; 
    
    /** Field optional - is attribute optional? */
    private boolean optional = false;

    protected CContainedAttribute(TypeEntry typeEntry, QName qname) {
        this.qname     = qname;
        this.typeEntry = typeEntry;
        
        name = qname.getLocalPart();
        if (name.lastIndexOf(SymbolTable.ANON_TOKEN) > 1)
            name = name.substring(name.lastIndexOf(SymbolTable.ANON_TOKEN) + 1, name.length());
    }

    public final QName getQName() {
        return qname;
    }

    public final String getName() {
        return name;
    }      
    
    public final TypeEntry getTypeEntry() {
        return typeEntry;
    }
    
    public Type getType() {
        return type;
    }
    
    public void setType(Type type) {
        this.type = type;
    }
    
    public void setOptional(boolean optional) {
        this.optional = optional;
    }

    public boolean isOptional() {
        return optional;
    }

}
