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

import org.apache.axis.wsdl.symbolTable.BaseType;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;

public class Type
{
    private QName name;
    /**
     * variable that represents extension base value in case of a complexType 
     * with simpleContent
     */
    private ElementInfo extensionBaseType = null;
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
    /* This vector was added to preserve the order of types parsed from the wsdl. 
     * This may be a hack. Should be improved if necessary
     */
    private Vector vElements;
    /* attribute names and the type of the attributes (QName,QName)*/
    private Hashtable attributes;
    /* This vector was added to preserve the order of types parsed from the wsdl. 
     * This may be a hack. Should be improved if necessary
     */
    private Vector vAttributes;
    /* has the attributes are specified with order <sequence> in the schema */
    private boolean hasOrder;
    /*if order presents the order is set in the vector */
    private Vector attribOrder;
    /* weather the type is Array */
    private boolean isArray;

    private boolean isreferenced = false;

    private String language;
    //Samisa: element type
    private String elementType;

    public Type(
        QName name,
        String languageSpecificName,
        boolean hasOrder,
        String language)
    {
        this.languageSpecificName = languageSpecificName;
        this.hasOrder = hasOrder;
        this.name = name;
        elements = new Hashtable();
        attributes = new Hashtable();
        vElements = new Vector();
        vAttributes = new Vector();
        if (language == null)
        {
            this.language = WrapperConstants.LANGUAGE_JAVA;
        }
        else
        {
            this.language = language;
        }

        // if the language specific name does not specified try weather is it a simple type  	 
        if (languageSpecificName == null)
        {
            if (WrapperConstants.LANGUAGE_CPP.equalsIgnoreCase(this.language))
            {
                this.languageSpecificName = CUtils.getclass4qname(name);
            }
            else
            {
                if (WrapperConstants
                    .LANGUAGE_C
                    .equalsIgnoreCase(this.language))
                {
                    this.languageSpecificName = CUtils.getclass4qname(name);
                }
                else
                {
                    this.languageSpecificName =
                        TypeMap.getBasicTypeClass4qname(name);
                }
            }

        }

        //if it is not a simple type genarate the name using usual QName -> language specific name mapping
        if (this.languageSpecificName == null)
        {
            this.languageSpecificName = qname2LSN();
        }
        else
        {
            //remove any funny Charactors
            this.languageSpecificName =
                this.languageSpecificName.replaceAll("/", "_");

            this.languageSpecificName =
                this.languageSpecificName.replaceAll(":", "_");
            // JBY : add this one more clean?
            // This arrived in case of inner type declaration. And for compilation
            // we replace all '>' by '_' (not the first one). Quick and durty fix.
            if (this.languageSpecificName.length() > 1)
            {
                if (this.languageSpecificName.charAt(0) == '>')
                {
                    this.languageSpecificName =
                        ">"
                            + this.languageSpecificName.substring(1).replaceAll(
                                ">",
                                "_");
                }
                else
                {
                    this.languageSpecificName =
                        this.languageSpecificName.replaceAll(">", "_");
                }
            }
        }
        this.attribOrder = new Vector();
    }

    /**
     * @return QName
     */
    public QName getName()
    {
        return name;
    }

    /**
     * @return String 
     */
    public String getLocalPartOfName()
    {
        String attribName = name.getLocalPart();
        if (attribName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1)
        {
            attribName =
                attribName.substring(
                    attribName.lastIndexOf(SymbolTable.ANON_TOKEN) + 1,
                    attribName.length());
        }
        attribName =
            TypeMap.resolveWSDL2LanguageNameClashes(attribName, this.language);

        return attribName;
    }

    /**
     * Sets the name.
     * @param name The name to set
     */
    public void setName(QName name)
    {
        this.name = name;
    }

    public Iterator getAttributeNames()
    {
        return this.vAttributes.iterator();
    }

    /**
     * The Type take the attributes name to lowercase when add, If there is two names like "Name" and "name"
     * they will convert to "name"  Is that acceptable ....  
     */
    public void setTypeForAttributeName(String attribName, Type type)
    {
        //Samisa:	
        // Check to see if this is an anonymous type,
        // if it is, replace Axis' ANON_TOKEN with
        // an underscore to make sure we don't run
        // into name collisions with similarly named
        // non-anonymous types
        // StringBuffer sb = new StringBuffer(attribName);
        // int aidx = -1;

        // while ((aidx = sb.toString().indexOf(SymbolTable.ANON_TOKEN)) > -1) {
        // sb.replace(aidx, aidx + SymbolTable.ANON_TOKEN.length(), "_");
        // }

        // attribName = sb.toString();
        // Nithya:
        // To resolve fault soap message issue

        if (attribName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1)
        {
            attribName =
                attribName.substring(
                    attribName.lastIndexOf(SymbolTable.ANON_TOKEN) + 1,
                    attribName.length());
        }
        attribName =
            TypeMap.resolveWSDL2LanguageNameClashes(attribName, this.language);

        if (hasOrder)
        {
            this.attribOrder.add(attribName);
        }
        this.attributes.put(attribName, type);
        this.vAttributes.add(attribName);
    }

    public Type getTypForAttribName(String attribName)
    {
        return (Type) this.attributes.get(attribName);
    }

    public Iterator getElementnames()
    {
        return this.vElements.iterator();
    }

    /**
     * The Type take the attributes name to lowercase when add, If there is two names like "Name" and "name"
     * they will convert to "name"  Is that acceptable ....  
     */
    public void setTypeNameForElementName(ElementInfo element)
    {
        String attribName =
            TypeMap.resolveWSDL2LanguageNameClashes(
                element.getName().getLocalPart(),
                this.language);

        //Samisa:	
        // Check to see if this is an anonymous type,
        // if it is, replace Axis' ANON_TOKEN with
        // an underscore to make sure we don't run
        // into name collisions with similarly named
        // non-anonymous types
        //StringBuffer sb = new StringBuffer(attribName);
        //int aidx = -1;

        //while ((aidx = sb.toString().indexOf(SymbolTable.ANON_TOKEN)) > -1) {
        //    sb.replace(aidx, aidx + SymbolTable.ANON_TOKEN.length(), "_");
        // }

        //attribName = sb.toString();
        //Nithya:
        //to resolve fault soap message

        if (attribName.lastIndexOf(SymbolTable.ANON_TOKEN) > 1)
        {
            attribName =
                attribName.substring(
                    attribName.lastIndexOf(SymbolTable.ANON_TOKEN) + 1,
                    attribName.length());
        }
        // Samisa: This second call to TypeMap.resoleveWSDL2LanguageNameClashes
        // is made to make sure after replacinf ANON_TOKEN it is still not a keyword
        attribName =
            TypeMap.resolveWSDL2LanguageNameClashes(attribName, this.language);

        if (hasOrder)
        {
            this.attribOrder.add(attribName);
        }
        this.elements.put(attribName, element);
        this.vElements.add(attribName);
    }

    public ElementInfo getElementForElementName(String attribName)
    {
        return (ElementInfo) this.elements.get(attribName);
    }

    public void setAttribOrder(Vector order)
    {
        this.attribOrder = order;
    }

    public boolean hasOrder()
    {
        return this.hasOrder;
    }

    public String getLanguageSpecificName()
    {
        return languageSpecificName;
    }

    public void setLanguageSpecificName(String languageSpecificName)
    {
        this.languageSpecificName = languageSpecificName;
    }
    /**
     *  This mrthod define the standread conversion from qname to language spesific name
     *  @return language specific name 
     */
    protected String qname2LSN()
    {
        String nsuri = this.name.getNamespaceURI();
        if (nsuri == null)
        {
            return this.name.getLocalPart();
        }

        if (language.equalsIgnoreCase(WrapperConstants.LANGUAGE_CPP))
        {
            /* if it is CPP the namespace is neglected fr time been */
            return this.name.getLocalPart();
        }
        else
            if (language.equalsIgnoreCase(WrapperConstants.LANGUAGE_C))
            {
                return this.name.getLocalPart();
            }
            else
            {
                return WrapperUtils.firstCharacterToLowercase(
                    WrapperUtils.nsURI2packageName(nsuri))
                    + "."
                    + WrapperUtils.capitalizeFirstCaractor(
                        this.name.getLocalPart());
            }
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

    public boolean isContainedType(Type containedType)
    {
        Iterator ntype = this.attributes.values().iterator();
        QName typeName;
        while (ntype.hasNext())
        {
            typeName = ((Type) ntype.next()).getName();
            if (typeName.equals(containedType.name))
            {
                return true;
            }
        }
        Iterator nelements = this.elements.values().iterator();
        while (nelements.hasNext())
        {
            typeName = ((ElementInfo) nelements.next()).getType().getName();
            if (typeName.equals(containedType.name))
            {
                return true;
            }
        }
        return false;
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
        if (vector != null)
        {
            isSimpleType = true;
            BaseType basetype = (BaseType) vector.firstElement();
            if (basetype != null)
            {
                setBaseType(basetype.getQName());
                CUtils.addSchemaDefinedSimpleType(
                    name,
                    CUtils.getclass4qname(baseType));
            }
            enumerationdata = vector;
        }
    }

    /* (non-Javadoc)
     * @see java.lang.Object#toString()
     */
    public String toString()
    {
        String str =
            "---------"
                + this.name
                + "------------\n"
                + "languageSpecificName = "
                + this.languageSpecificName
                + "\n";
        if (enumerationdata != null)
        {
            str =
                str
                    + "enumerationType = "
                    + ((TypeEntry) enumerationdata.get(0)).getQName()
                    + "\n(";
            for (int i = 1; i < enumerationdata.size(); i++)
            {
                str = str + "," + enumerationdata.get(i);
            }
            str = str + ")\n";
        }
        else
        {
            str = str + "isArray =" + isArray + "\n";
            str = str + "Elements[\n";
            Iterator c = elements.values().iterator();
            java.util.Enumeration k = elements.keys(); //.iterator();
            while (c.hasNext())
            {
                str = str + "," + k.toString() + ":" + c.next() + "\n";
            }
            str = str + "]\n";

            c = attributes.keySet().iterator();
            str = str + "Attributes[\n";

            while (c.hasNext())
            {
                String name = (String) c.next();
                str = str + ",(" + name + "," + attributes.get(name) + ")";
            }
            str = str + "]\n";

        }
        str = str + "------------------------------------------------------\n";

        return str;
    }

    /**
     * @return boolean
     */
    public boolean isIsreferenced()
    {
        return isreferenced;
    }

    /**
     * Sets the isreferenced.
     * @param isreferenced The isreferenced to set
     */
    public void setIsreferenced(boolean isreferenced)
    {
        this.isreferenced = isreferenced;
        /* TODO also make the inner type of this be referenced*/

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
    public ElementInfo getExtensionBaseType()
    {
        return extensionBaseType;
    }

    /**
     * Sets the extensionBaseType.
     * @param extensionBaseType The extensionBaseType to set
     */
    public void setExtensionBaseType(ElementInfo extensionBaseType)
    {
        this.extensionBaseType = extensionBaseType;
    }

}
