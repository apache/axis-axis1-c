/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Axis" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/**
 * Type map has information about all the custom types in the webservice and it has the
 * Information about inbuild datatypes as well. The Type map class does not know about the
 * packages(java)and namespace(c++) ect information. The typemap registered the types agien the
 * xmlqname in WSDL. It is the underline applications responsibility to make sense of the
 * namespaceuri and localname in the qname
 *
 * e.g. java {urn:ns}classname -> ns.classname
 *      C++  {urn:ns}classname -> ns:classname
 * @author hemapani  
 */

package org.apache.axismora.wsdl2ws.info;

import java.util.Collection;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axismora.wrappers.simpleType.HexBinaryParam;
import org.apache.axismora.wsdl2ws.WrapperConstants;
import org.apache.axismora.wsdl2ws.WrapperFault;



public class TypeMap {
    public static final int SIMPLE_PARAM_GEN = 0;
    public static final int BEAN_PARAM_GEN = 1;
    private static String language = WrapperConstants.LANGUAGE_JAVA; 

    /* this map maps the classname -> QName */
    private static Hashtable basicTypeClass2QNamemap = new Hashtable();
    /* this map maps QName -> classname */
    private static Hashtable basicTypeQname2classmap = new Hashtable();
    
    private static Hashtable basicTypeClassName2WrapperClassmap = new Hashtable();
    /* this map stores Types keyed by the parameter name */
    private Hashtable typeInfo;
	/* 
	 * There are two QNames associated with a type in wsdl. the QName given with the
	 * element tag and the QName given with the complex type. (I am not very
	 * Confident about the diiferance between two). So I Use the QName at complex type
	 * I use this map to locate it when the element QName is given. 
	 */
    private static HashMap elementQName2ComplexTypeQName = new HashMap();
	private static Hashtable javakeywords = new Hashtable();
	private static Hashtable cppkeywords = new Hashtable();

	static {
		// java -> xml type mapping
		
		basicTypeClass2QNamemap.put("int", new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"));
		basicTypeClass2QNamemap.put("byte", new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"));
		basicTypeClass2QNamemap.put("float", new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"));
		basicTypeClass2QNamemap.put("long", new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"));
		basicTypeClass2QNamemap.put("double", new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"));
		basicTypeClass2QNamemap.put("boolean", new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"));
		basicTypeClass2QNamemap.put("char", new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"));
		basicTypeClass2QNamemap.put("short", new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"));
		basicTypeClass2QNamemap.put("byte[]", new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"));
		
		basicTypeClass2QNamemap.put("java.lang.String", new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"));
		basicTypeClass2QNamemap.put("java.math.BigDecimal", new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"));
		basicTypeClass2QNamemap.put("java.math.BigInteger", new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"));
		basicTypeClass2QNamemap.put("org.apache.axismora.wrappers.simpleType.DayParam", new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"));
		basicTypeClass2QNamemap.put("org.apache.axismora.wrappers.simpleType.DateParam", new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"));
		basicTypeClass2QNamemap.put("java.lang.Integer",new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"));
		basicTypeClass2QNamemap.put("java.lang.Double",new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"));
		basicTypeClass2QNamemap.put("java.lang.Long",new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"));
		basicTypeClass2QNamemap.put("java.lang.Byte",new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"));
		basicTypeClass2QNamemap.put("java.lang.Character",new QName(WrapperConstants.SOAPENC_NAMESPACE, "char"));
		basicTypeClass2QNamemap.put("java.lang.Short",new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"));
		basicTypeClass2QNamemap.put("java.lang.Boolean",new QName(WrapperConstants.SOAPENC_NAMESPACE, "boolean"));
		basicTypeClass2QNamemap.put("java.lang.Float",new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"));
		
		
		// xml -> java type mapping 
	
		basicTypeQname2classmap.put("int", "int");
		basicTypeQname2classmap.put("integer", "int");
		basicTypeQname2classmap.put("byte", "byte");
		basicTypeQname2classmap.put("float", "float");
		basicTypeQname2classmap.put("long", "long");
		basicTypeQname2classmap.put("double", "double");
		basicTypeQname2classmap.put("boolean", "boolean");
		basicTypeQname2classmap.put("char", "char");
		basicTypeQname2classmap.put("short", "short");
		basicTypeQname2classmap.put("string", "java.lang.String");
		basicTypeQname2classmap.put("decimal", "java.math.BigDecimal");
		
		basicTypeQname2classmap.put("Qname", "javax.xml.namespace.QName");
		basicTypeQname2classmap.put("dateTime", "org.apache.axismora.wrappers.simpleType.DayParam");
		basicTypeQname2classmap.put("base64Binary", "org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam");
		basicTypeQname2classmap.put("base64", "org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam");
		basicTypeQname2classmap.put("hexBinary", "org.apache.axismora.wrappers.simpleType.HexBinaryParam");
		basicTypeQname2classmap.put("gMonth", "org.apache.axismora.wrappers.simpleType.MonthParam");
		basicTypeQname2classmap.put("gMonthDay", "org.apache.axismora.wrappers.simpleType.MonthDayParam");
		basicTypeQname2classmap.put("gDay", "org.apache.axismora.wrappers.simpleType.DayParam");
		basicTypeQname2classmap.put("gYear", "org.apache.axismora.wrappers.simpleType.YearParam");
		basicTypeQname2classmap.put("gYearMonth", "org.apache.axismora.wrappers.simpleType.YearMonthParam");
		basicTypeQname2classmap.put("unsignedByte", "byte");
		basicTypeQname2classmap.put("negativeInteger", "int");
		basicTypeQname2classmap.put("nonNegativeInteger", "int");
		basicTypeQname2classmap.put("positiveInteger", "int");
		basicTypeQname2classmap.put("nonPositiveInteger", "int");
		basicTypeQname2classmap.put("time", "org.apache.axismora.wrappers.simpleType.TimeParam");
		basicTypeQname2classmap.put("unsignedLong", "org.apache.axismora.wrappers.simpleType.TimeParam");
		basicTypeQname2classmap.put("unsignedShort", "short");
		basicTypeQname2classmap.put("unsignedInt", "int");
		basicTypeQname2classmap.put("any", "org.apache.axismora.wrappers.simpleType.AnyParam");
		basicTypeQname2classmap.put("anyType", "org.apache.axismora.wrappers.simpleType.AnyParam");
		basicTypeQname2classmap.put("NMTOKEN", "java.lang.String");
		
		
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"), "java.lang.Integer");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"), "java.lang.Byte");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"), "java.lang.Float");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"), "java.lang.Long");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"), "java.lang.Double");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "boolean"), "java.lang.Boolean");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "char"), "java.lang.Charcter");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"), "java.lang.Short");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "string"), "java.lang.String");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "decimal"), "java.math.BigDecimal");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64"), "org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam");
		
		
		
		basicTypeClassName2WrapperClassmap.put("int", "org.apache.axismora.wrappers.simpleType.IntParam");
		basicTypeClassName2WrapperClassmap.put("byte", "org.apache.axismora.wrappers.simpleType.ByteParam");
		basicTypeClassName2WrapperClassmap.put("float", "org.apache.axismora.wrappers.simpleType.FloatParam");
		basicTypeClassName2WrapperClassmap.put("long", "org.apache.axismora.wrappers.simpleType.LongParam");
		basicTypeClassName2WrapperClassmap.put("double", "org.apache.axismora.wrappers.simpleType.DoubleParam");
		basicTypeClassName2WrapperClassmap.put("boolean", "org.apache.axismora.wrappers.simpleType.BooleanParam");
		basicTypeClassName2WrapperClassmap.put("char", "org.apache.axismora.wrappers.simpleType.CharParam");
		basicTypeClassName2WrapperClassmap.put("short", "org.apache.axismora.wrappers.simpleType.ShortParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.String","org.apache.axismora.wrappers.simpleType.StringParam");
		basicTypeClassName2WrapperClassmap.put("javax.xml.namespace.QName","org.apache.axismora.wrappers.simpleType.QNameParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.DayParam","org.apache.axismora.wrappers.simpleType.DayParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.MonthParam","org.apache.axismora.wrappers.simpleType.MonthParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.MonthDayParam", "org.apache.axismora.wrappers.simpleType.MonthDayParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.DayParam", "org.apache.axismora.wrappers.simpleType.DayParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.YearParam", "org.apache.axismora.wrappers.simpleType.YearParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.YearMonthParam", "org.apache.axismora.wrappers.simpleType.YearMonthParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.TimeParam", "org.apache.axismora.wrappers.simpleType.TimeParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.TimeParam", "org.apache.axismora.wrappers.simpleType.TimeParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.AnyParam", "org.apache.axismora.wrappers.simpleType.AnyParam");
		
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam", "org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam");
		basicTypeClassName2WrapperClassmap.put("org.apache.axismora.wrappers.simpleType.HexBinaryParam", "org.apache.axismora.wrappers.simpleType.HexBinaryParam");
		
		basicTypeClassName2WrapperClassmap.put("java.lang.Integer","org.apache.axismora.wrappers.simpleType.WrapIntParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.Byte","org.apache.axismora.wrappers.simpleType.WrapByteParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.Float","org.apache.axismora.wrappers.simpleType.WrapFloatParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.Long","org.apache.axismora.wrappers.simpleType.WrapLongParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.Double","org.apache.axismora.wrappers.simpleType.WrapDoubleParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.Boolean","org.apache.axismora.wrappers.simpleType.WrapBooleanParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.Charcter","org.apache.axismora.wrappers.simpleType.WrapCharParam");
		basicTypeClassName2WrapperClassmap.put("java.lang.Short","org.apache.axismora.wrappers.simpleType.WrapShortParam");
		basicTypeClassName2WrapperClassmap.put("java.math.BigDecimal","org.apache.axismora.wrappers.simpleType.BigDecimalParam");
		basicTypeClassName2WrapperClassmap.put("byte[]","org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam");

		
		String[] words1 ={"abstract","default","if","private","this","boolean","do","implements",
			"protected","throw","break","double","import","public","throws","byte","else","instanceof",
			"return","transient","case","extends","int","short","try","catch","final","interface",
			"static","void","char","finally","long","strictfp","volatile","class","float","native",
			"super","while","const","for","new","switch","continue","goto","package","synchronized",
			"return","false","null"};
		for(int i = 0;i<words1.length;i++){
				javakeywords.put(words1[i],words1[i]);
		}
		String[] words2 ={"and","and_eq","asm","auto","bitand","bitor","bool","break"
			,"case","catch","char","class","compl","const","const_cast","continue","default"
			,"delete","do","double","dynamic_cast","else","enum","explicit","export"
			,"extern","false","float","for","friend","goto","if","inline","int","long","mutable","namespace","new","not"
			,"not_eq","operator","or","or_eq","private","protected","public","register"
			,"reinterpret_cast","return","short","signed","sizeof","static","static_cast"
			,"struct","switch","template","this","throw","true","try","typedef","typeid"
			,"typename","union","unsigned","using","virtual","void","volatile"
			,"wchar_t","while","xor","xor_eq","string"};
		for(int i = 0;i<words2.length;i++){
			cppkeywords.put(words2[i],words2[i]);
		}

	
	}
    public TypeMap(String language) {
		TypeMap.language = language;
        this.typeInfo = new Hashtable();
    }

    public static QName getBasicTypeQname4class(String classname) {
    	Object val = basicTypeClass2QNamemap.get(classname); 	
       	return val!=null?(QName)val:null;
    }
	
    public static String getBasicTypeClass4qname(QName qname) {
        Object val = null;
        if (org.apache.axis.Constants.URI_1999_SCHEMA_XSD.equals(qname.getNamespaceURI())
            || org.apache.axis.Constants.URI_2000_SCHEMA_XSD.equals(qname.getNamespaceURI())
            || org.apache.axis.Constants.URI_2001_SCHEMA_XSD.equals(
                qname.getNamespaceURI()))
            val = basicTypeQname2classmap.get(qname.getLocalPart());
        else if (WrapperConstants.SOAPENC_NAMESPACE.equals(qname.getNamespaceURI()))
            val = basicTypeQname2classmap.get(qname);
		return val!=null?(String)val:null;
	}//
	
    public static boolean isSimpleType(String type) {
        return (
            //type.startsWith("org.apache.axismora.wrappers.simpleType")
              //  || 
              basicTypeClassName2WrapperClassmap.containsKey(type));
    }

     public static boolean isSimpleType(QName type) {
        if (org.apache.axis.Constants.URI_1999_SCHEMA_XSD.equals(type.getNamespaceURI())
            || org.apache.axis.Constants.URI_2000_SCHEMA_XSD.equals(type.getNamespaceURI())
            || org.apache.axis.Constants.URI_2001_SCHEMA_XSD.equals(type.getNamespaceURI()))
            return basicTypeQname2classmap.containsKey(type.getLocalPart());
        else if (WrapperConstants.SOAPENC_NAMESPACE.equals(type.getNamespaceURI()))
			return basicTypeQname2classmap.containsKey(type);    
        return false;
    }

    public Type getType(QName name) {
    	if(isSimpleType(name))
    		return new Type(name,null,false,TypeMap.language);
        return (Type) this.typeInfo.get(name);
    }


    public void addType(QName wsdlname, Type type) {
        this.typeInfo.put(wsdlname, type);
    }

    /* get all the custom types in the typeMap */
    public Collection getTypes() {
        return this.typeInfo.values();
    } 
	
   /**
     * The wsdl support the attributes names that are not allowed by the program langage.
     * e.g. use keyword 
     * This method resolved those clashes by adding "_" to the front. This is a 
     * JAX_RPC recomendation of the situation.  
     * @param name
     * @param language
     * @return
     */
    public static String resoleveWSDL2LanguageNameClashes(String name,String language){
		Hashtable keywords;
	  	if(WrapperConstants.LANGUAGE_JAVA.equalsIgnoreCase(language)){
			keywords = javakeywords;
	  	}else{
			keywords = cppkeywords;
	  	}	
    	
    	if(keywords.containsKey(name))
    		return "_"+name;
    	
    	return name;
    }
    
    //private static Hashtable unregisterdArrayTypes = new Hashtable();
    
	private static Vector unregisterdArrayTypes = new Vector();
    
    public static String regestorArrayTypeToCreate(Type type)throws WrapperFault{
//    	QName arrayType = WrapperUtils.getArrayType(type).getName();
//		Object obj = unregisterdArrayTypes.get(arrayType);
//		if(obj != null)
//			return ((Type)obj).getLanguageSpecificName();
//		else{
//			unregisterdArrayTypes.put(arrayType,type);
//			return type.getLanguageSpecificName();
//		}	
		unregisterdArrayTypes.add(type);
		return type.getLanguageSpecificName();
    }
    
    public static Iterator getUnregisterdArrayTypes(){
		return unregisterdArrayTypes.iterator();
    }
    
    public static String getWrapperCalssNameForJavaClass(String javaclass){
    	String wrapperClass = (String)basicTypeClassName2WrapperClassmap.get(javaclass);
    	return (wrapperClass!=null)?wrapperClass:javaclass;
    }
}
