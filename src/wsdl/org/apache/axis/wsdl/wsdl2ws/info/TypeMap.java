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
 * Type map has information about all the custom types in the webservice and it has the
 * Information about in-built datatypes as well. The Type map class does not know about the
 * namespace(c++) etc information. The typemap registers the types against the
 * xmlqname in WSDL. It is the underline applications responsibility to make sense of the
 * namespaceuri and localname in the qname
 *
 * e.g.  C++  {urn:ns}classname -> ns:classname
 * @author hemapani  
 */

package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.Collection;
import java.util.Hashtable;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

public class TypeMap
{
    public static final String ANON_TOKEN_STRING = ">";
    public static final char   ANON_TOKEN_CHAR   = '>';
    
    /* this map maps QName -> classname */
    private static Hashtable basicTypeQname2classmap = new Hashtable();
    
    /* this map stores Types keyed by the parameter name */
    private Hashtable typeInfo = new Hashtable();;

    static {
        // xml -> c type mapping 
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "duration"),   		"xsd__duration");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"),   		"xsd__dateTime");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"),       		"xsd__time");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"),       		"xsd__date");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYearMonth"),       	"xsd__gYearMonth");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYear"),       		"xsd__gYear");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonthDay"),       	"xsd__gMonthDay");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gDay"),       		"xsd__gDay");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonth"),       		"xsd__gMonth");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"),				"xsd__string");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "normalizedString"),	"xsd__normalizedString");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "token"),				"xsd__token");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "language"),			"xsd__language");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "Name"),				"xsd__Name");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NCName"),				"xsd__NCName");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ID"),					"xsd__ID");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREF"),				"xsd__IDREF");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREFS"),				"xsd__IDREFS");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITY"),				"xsd__ENTITY");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITIES"),			"xsd__ENTITIES");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"),			"xsd__NMTOKEN");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKENS"),			"xsd__NMTOKENS");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"),			"xsd__boolean");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"),		"xsd__base64Binary");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"),			"xsd__hexBinary");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"),				"xsd__float");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"),			"xsd__decimal");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"),			"xsd__integer");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonPositiveInteger"),	"xsd__nonPositiveInteger");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "negativeInteger"),	"xsd__negativeInteger");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"),				"xsd__long");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"),				"xsd__int");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"),				"xsd__short");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"),				"xsd__byte");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonNegativeInteger"),	"xsd__nonNegativeInteger");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"),		"xsd__unsignedLong");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"),		"xsd__unsignedInt");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"),		"xsd__unsignedShort");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"),		"xsd__unsignedByte");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "positiveInteger"),	"xsd__positiveInteger");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"),				"xsd__double");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"),				"xsd__anyURI");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"),				"xsd__QName");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NOTATION"),			"xsd__NOTATION");
        basicTypeQname2classmap.put(new QName(WrapperConstants.APACHE_XMLSOAP_NAMESPACE, "Image"),		"ISoapAttachment");
        basicTypeQname2classmap.put(new QName(WrapperConstants.APACHE_XMLSOAP_NAMESPACE, "PlainText"),	"ISoapAttachment");
        basicTypeQname2classmap.put(new QName(WrapperConstants.APACHE_XMLSOAP_NAMESPACE, "Multipart"),	"ISoapAttachment");
        basicTypeQname2classmap.put(new QName(WrapperConstants.APACHE_XMLSOAP_NAMESPACE, "Source"),		"ISoapAttachment");
        basicTypeQname2classmap.put(new QName(WrapperConstants.APACHE_XMLSOAP_NAMESPACE, "octet-stream"),	"ISoapAttachment");
        basicTypeQname2classmap.put(new QName(WrapperConstants.APACHE_XMLSOAP_NAMESPACE, "DataHandler"),	"ISoapAttachment");

        /* TODO:
         *   Should be removed when the following issue will be fixed :
         * 	-> http://marc.theaimsgroup.com/?t=107907748000002&r=1&w=2 
         */
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "integer"),       "xsd__integer");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "string"),        "xsd__string");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "decimal"),       "xsd__decimal");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "QName"),         "xsd__QName");
/*      basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "NCName"),        "xsd__NCName");  */
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "dateTime"),      "xsd__dateTime");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "date"),          "xsd__date");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "time"),          "xsd__time");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "duration"),      "xsd__duration");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64Binary"),  "xsd__base64Binary");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "hexBinary"),     "xsd__hexBinary");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"),           "xsd__int");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"),          "xsd__byte");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"),         "xsd__float");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"),          "xsd__long");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"),        "xsd__double");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "boolean"),       "xsd__boolean");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"),         "xsd__short");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedByte"),  "xsd__unsignedByte");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedInt"),   "xsd__unsignedInt");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedLong"),  "xsd__unsignedLong");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedShort"), "xsd__unsignedShort");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "anyURI"),        "xsd__anyURI");
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "NMTOKEN"),       "xsd__NMTOKEN");
        /* TODO:
         *  Another strange issue from Axis 1.1 runtime when base64binary is in input/output operations.
         */
        basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64"), "xsd__base64Binary");
    }
    
    public TypeMap()
    {
    }

    public static String getBasicTypeClass4qname(QName qname)
    {
        Object val = basicTypeQname2classmap.get(qname);
        return (String) val;
    }

    public static boolean isSimpleType(QName type)
    {
        return basicTypeQname2classmap.containsKey(type);
    }

    public Type getType(QName name)
    {
        if (isSimpleType(name))
            return new Type(name, null);

        return (Type) this.typeInfo.get(name);
    }

    public void addType(QName wsdlname, Type type)
    {
        this.typeInfo.put(wsdlname, type);
    }

    public void removeType(QName wsdlname)
    {
        this.typeInfo.remove(wsdlname);
    }
    /* get all the custom types in the typeMap */
    public Collection getTypes()
    {
        return this.typeInfo.values();
    }
    
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
    
    public static boolean isAnonymousType(String type)
    {
        if (type != null)
            return type.charAt(0) == ANON_TOKEN_CHAR;

        return false;
    }

    public static boolean isAnonymousType(QName type)
    {
        if (type != null)
            return isAnonymousType(type.getLocalPart());
        
        return false;
    }    
}
