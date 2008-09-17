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

/**
 * This calss represent the Custom Complex type in the service.
 * This Class is the  representation of the WSDL Schema type. The class name is given in the
 * context of the xml QName. It is up to the user to make sense of the QName* 
 * 
 * @author Srianth Perera (hemapani@opensource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.CElementDecl;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.symbolTable.CContainedAttribute;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

public class Type
{
    private QName name;
    /**
     * variable that represents extension base value in case of a complexType 
     * with simpleContent
     */
    private CElementDecl extensionBaseType = null;
    
    /**
     * Indicate whether this is a schema defined simpleType
     */
    private boolean isSimpleType = false;
    
    /**
     * In case this is schema defined simpleType, this is the base type.
     */
    private QName baseType;
    
    /**
      * If the specified node represents a supported JAX-RPC restriction,
      * a Vector is returned which contains the base type and the values.
      * The first element in the vector is the base type (an TypeEntry).
      * Subsequent elements are values(QNames) if any.
      */
    private Vector enumerationdata;
    
    /* This can be null */
    private String languageSpecificName;
    
    /* element names and the type of the elements (QName,ElementInfo)*/
    private Hashtable elements;
    
    /* This vector was added to preserve the order of types parsed from the wsdl. */
    private Vector vElements;

    /* contained attributes. */
    private Vector vAttributes = null;
 
    /* whether the type is Array */
    private boolean isArray;
    
    /* element type */
    private String elementType;
    
    /* is this type going to be thrown as a soap fault? */
    private boolean isFault = false;

    /* Is this type an attachment under the http://xml.apache.org/xml-soap namespace? */
    private boolean isAttachment = false;

    /* Should this type be generated or not - by default, set to true except for anonymous types */
    private boolean externalize = true;

    private boolean   restriction = false;
    private String    restrictionBaseType = null;
    private Vector    restrictionPattern = null;      // future - not currently used 
    private Vector    restrictionEnumeration = null;  // future - not currently used
    
    /* Is anonymous type? qname.localname is checked, and if starts with '>', then true */
    private boolean isAnonymous = false;

    /* This vector was added in order to ensure that when a type is externalized, its 
     * related types (types that are directly or indirectly referenced within this type) 
     * are also externalized. 
     */
    private Vector vRelatedTypes = new Vector();
    
    // is type the output type for unwrapped doc/lit operation?
    private boolean isUnwrappedOutputType = false;
    
    // is type the input type for unwrapped doc/lit operation?
    private boolean isUnwrappedInputType  = false;
    
    // is any type? This is true for xsd:anyType
    private boolean c_isAnyType = false;
    
    // is any element?  This is true for xsd:any.
    private boolean c_isAnyElement = false;


    /**
     * Constructor.
     * This is solely for the creating of types associated with xsd:any elements!
     */
    public Type()
    {
        this(CUtils.xsdAnyElementQName, CUtils.xsdAnyElementQName.getLocalPart());
    }
    
    /**
     * Constructor.
     * 
     * @param name
     * @param languageSpecificName
     */
    public Type(QName name, String languageSpecificName)
    {
        this.languageSpecificName = languageSpecificName;
        this.name = name;
        elements = new Hashtable();
        vElements = new Vector();

        // if the language specific name is not specified try a simple type       
        if (languageSpecificName == null)
            this.languageSpecificName = CUtils.getSimpleType(name);

        //if language specific name still not set, use localPart of QName
        if (this.languageSpecificName == null)
            this.languageSpecificName = this.name.getLocalPart();
        
        // Ensure name is valid and does not clash with language specific constructs
        this.languageSpecificName = CUtils.sanitizeString(this.languageSpecificName);
        
        // Indicate whether type is anonymous. Anonymous type start with '>' and are not
        // externalized by default.
        if (TypeMap.isAnonymousType(this.name))
        {
            isAnonymous = true;
            externalize = false;
        }
        
        // See if this type represents an xsd:any element or an xsd:anyType type.
        c_isAnyType    = CUtils.isAnyType(name);
        c_isAnyElement = CUtils.isAnyElement(name);

        if (name.getNamespaceURI().equals(WrapperConstants.APACHE_XMLSOAP_NAMESPACE) && 
            (name.getLocalPart().equals("DataHandler") ||
             name.getLocalPart().equals("Image") ||
             name.getLocalPart().equals("MimeMultipart") ||
             name.getLocalPart().equals("Source") ||
             name.getLocalPart().equals("octet-stream") ||
             name.getLocalPart().equals("PlainText")) )
        {
             isAttachment = true;
        }
    }

    /**
     * @return QName
     */
    public QName getName()
    {
        return name;
    }

    /**
     * Sets the name.
     * @param name The name to set
     */
    public void setName(QName name)
    {
        this.name = name;
    }

    public Iterator getAttributes()
    {
        if (this.vAttributes != null)
            return this.vAttributes.iterator();
        
        return null;
    }

    public void addAttributes(Vector attrs)
    {
        // Needs to be done this way so we can take care of attributes from extensions
        if (this.vAttributes == null)
            this.vAttributes = attrs;
        else
            this.vAttributes.addAll(attrs);
    }

    public Iterator getElementnames()
    {
        return this.vElements.iterator();
    }

    /**
     */
    public void setTypeNameForElementName(CElementDecl element)
    {
        String attribName = element.getName().getLocalPart();

        if (attribName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1)
        {
            attribName =
                attribName.substring(
                    attribName.lastIndexOf(SymbolTable.ANON_TOKEN) + 1,attribName.length());
        }

        this.elements.put(attribName, element);
        this.vElements.add(attribName);
    }

    public CElementDecl getElementForElementName(String attribName)
    {
        return (CElementDecl) this.elements.get(attribName);
    }

    public String getLanguageSpecificName()
    {
        return languageSpecificName;
    }

    public void setLanguageSpecificName(String languageSpecificName)
    {
        this.languageSpecificName = CUtils.sanitizeString(languageSpecificName);
    }

    /**
     * @return
     */
    public boolean isArray()
    {
        return isArray;
    }

    /**
     * @param b
     */
    public void setArray(boolean b)
    {
        isArray = b;
    }

    /**
      * If the specified node represents a supported JAX-RPC enumeration,
      * a Vector is returned which contains the base type and the enumeration values.
      * The first element in the vector is the base type (an TypeEntry).
      * Subsequent elements are values (Strings).
      * If this is not an enumeration, null is value.
      * @return
      */
    public Vector getEnumerationdata()
    {
        return enumerationdata;
    }

    /**
     * @param vector
     */
    public void setRestrictiondata(Vector vector)
    {
        isSimpleType = true;
        enumerationdata = vector;
    }

    /* (non-Javadoc)
     * @see java.lang.Object#toString()
     */
    public String toString()
    {
        String str = "---------" + this.name + "------------\n";
        str = str + "languageSpecificName = " + languageSpecificName + "\n";
        str = str + "isAnonymous ="           + isAnonymous + "\n";
        str = str + "isSimpleType ="          + isSimpleType + "\n";
        str = str + "externalize ="           + externalize + "\n";
        str = str + "isArray ="               + isArray + "\n";
        str = str + "baseType = "             + baseType + "\n";
        str = str + "restriction = "          + restriction + "\n";
        str = str + "restrictionBaseType ="   + restrictionBaseType + "\n";
         
        if (enumerationdata != null)
        {
            str = str + "enumerationType = " + ((TypeEntry) enumerationdata.get(0)).getQName() + "\n(";
            for (int i = 1; i < enumerationdata.size(); i++)
                str = str + "," + enumerationdata.get(i);
            str = str + ")\n";
        }
        else
        {
            str = str + "Elements[\n";
            Iterator c = elements.values().iterator();
            java.util.Enumeration k = elements.keys(); //.iterator();
            while (c.hasNext())
            {
                str = str + "," + k.toString() + ":" + c.next() + "\n";
            }
            str = str + "]\n";

            str = str + "Attributes[\n";
            c = getAttributes();
            if (c != null)
                while (c.hasNext())
                {
                    CContainedAttribute attr = (CContainedAttribute)c.next();
                    str = str + ",(" + attr.getName() + "," + attr.getTypeEntry() + ")";
                }
            str = str + "]\n";

        }
        str = str + "------------------------------------------------------\n";

        return str;
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

    /**
     * @return QName
     */
    public QName getBaseType()
    {
        return baseType;
    }

    /**
     * Sets the baseType.
     * @param baseType The baseType to set
     */
    public void setBaseType(QName baseType)
    {
        this.baseType = baseType;
    }

    public void setElementType(String type)
    {
        elementType = type;
    }

    public String getElementType()
    {
        return elementType;
    }

    /**
     * @return ElementInfo
     */
    public CElementDecl getExtensionBaseType()
    {
        return extensionBaseType;
    }

    /**
     * Sets the extensionBaseType.
     * @param extensionBaseType The extensionBaseType to set
     */
    public void setExtensionBaseType(CElementDecl extensionBaseType)
    {
        this.extensionBaseType = extensionBaseType;
    }

    public void setAsFault(boolean isFault) 
    {
        this.isFault = isFault;
    }
    
    public boolean isFault() 
    {
        return isFault;
    }

    public boolean isAttachment() 
    {
        return isAttachment;
    }
    
    /**
     * Whether the type represents an anonymous type.
     */
    public boolean isAnonymous()
    {
        return isAnonymous;
    }
    
    /**
     * Whether this type will be generated or not. 
     */
    public boolean isExternalized()
    {
        return externalize; 
    }
    
    /**
     * Indicate whether type should be generated (i.e. externalized).
     */
    public void externalize(boolean flag)
    {           
        externalize = flag;
    }  

    /**
     * Externalize type - changing qname and use localPart of qname as 
     * platform specific language name.
     */
    public void externalize(QName newQName)
    {           
        externalize(true);
        
        setName(newQName);
        setLanguageSpecificName(newQName.getLocalPart());
    }     
    
    /**
     * Return iterator for vector of related non-simple types.
     */
    public Iterator getRelatedTypes()
    {
        return this.vRelatedTypes.iterator();
    }  
    
    /*
     * Add to vector a Type that is related that is non-simple.
     */
    public void addRelatedType(Type type)
    {
        if (type != null && !CUtils.isPrimitiveType(type.getName()))
            this.vRelatedTypes.add(type);
    }    
    // vvv FJP - 17667
    /**
     * @return Returns the restrictionBaseType.
     */
    public String getRestrictionBaseType()
    {
        return restrictionBaseType;
    }
    /**
     * @param restrictionBase The restrictionBase to set.
     */
    public void setRestrictionBaseType(String restrictionBaseType)
    {
        this.restrictionBaseType = restrictionBaseType;
    }
    /**
     * @return Returns the restrictionEnumeration.
     */
    public Vector getRestrictionEnumeration()
    {
        return restrictionEnumeration;
    }
    /**
     * @param restrictionEnumeration The restrictionEnumeration to set.
     */
    public void setRestrictionEnumeration(Vector restrictionEnumeration)
    {
        this.restrictionEnumeration = restrictionEnumeration;
    }
    /**
     * @return Returns the restrictionPattern.
     */
    public Vector getRestrictionPattern()
    {
        return restrictionPattern;
    }
    /**
     * @param restrictionPattern The restrictionPattern to set.
     */
    public void setRestrictionPattern(Vector restrictionPattern)
    {
        this.restrictionPattern = restrictionPattern;
    }
    /**
     * @return Returns the restriction.
     */
    public boolean isRestriction()
    {
        return restriction;
    }
    /**
     * @param restriction The restriction to set.
     */
    public void setRestriction(boolean restriction)
    {
        this.restriction = restriction;
    }
    // ^^^ FJP - 17667


    public void setIsUnwrappedOutputType(boolean b)
    {
        this.isUnwrappedOutputType  = b;  
    }

    public boolean isUnwrappedOutputType()
    {
        return isUnwrappedOutputType;
    }
    
    public void setIsUnwrappedInputType(boolean b)
    {
        this.isUnwrappedInputType    = b;  
    }

    public boolean isUnwrappedInputType()
    {
        return isUnwrappedInputType;
    }

    /**
     * @return the c_isAnyType
     */
    public boolean isAnyType()
    {
        return c_isAnyType;
    }
    
    /**
     * @return the c_isAnyType
     */
    public boolean isAnyElement()
    {
        return c_isAnyElement;
    }
}
