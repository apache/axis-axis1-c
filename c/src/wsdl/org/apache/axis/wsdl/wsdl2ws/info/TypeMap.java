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

package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.Collection;
import java.util.HashMap;
import java.util.Hashtable;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

public class TypeMap {
    public static final int SIMPLE_PARAM_GEN = 0;
    public static final int BEAN_PARAM_GEN = 1;

    /* this map maps the classname -> QName */
    private static Hashtable basicTypeClass2QNamemap = new Hashtable();
    /* this map maps QName -> classname */
    private static Hashtable basicTypeQname2classmap = new Hashtable();
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
		basicTypeClass2QNamemap.put("java.lang.String", new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"));
		basicTypeClass2QNamemap.put("java.math.BigDecimal", new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"));
		basicTypeClass2QNamemap.put("java.math.BigInteger", new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"));
		basicTypeClass2QNamemap.put("java.utils.Calendar", new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"));
		basicTypeClass2QNamemap.put("java.utils.Date", new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"));
		
		// xml -> java type mapping 
	
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"), "int");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"), "byte");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"), "float");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"), "long");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"), "double");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"), "boolean");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"), "char");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"), "short");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"), "java.lang.String");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"), "java.math.BigDecimal");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "Qname"), "javax.xml.namespace.QName");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"), "java.utils.Date");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"), "byte[]");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"), "byte[]");
		
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"), "java.lang.Integer");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"), "java.lang.Byte");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"), "java.lang.Float");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"), "java.lang.Long");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"), "java.lang.Double");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "boolean"), "java.lang.Boolean");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "char"), "java.lang.Charcter");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"), "java.lang.Short");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "string"), "java.lang.String");
		basicTypeQname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"), "java.math.BigDecimal");

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
    public TypeMap() {
        this.typeInfo = new Hashtable();
    }

    public static QName getBasicTypeQname4class(String classname) {
    	Object val = basicTypeClass2QNamemap.get(classname); 	
       	return val!=null?(QName)val:null;
    }
	
    public static String getBasicTypeClass4qname(QName qname) {
        Object val = basicTypeQname2classmap.get(qname);
		return val!=null?(String)val:null;
	}//
	
    public static boolean isSimpleType(String type) {
  		return basicTypeClass2QNamemap.containsKey(type);
    }

     public static boolean isSimpleType(QName type) {
		return basicTypeQname2classmap.containsKey(type);    
    }

    public Type getType(QName name) {
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
}
