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
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.util.Hashtable;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

public class CPPUtils {
	public static final String WRAPPER_NAME_APPENDER = "Wrapper";
	public static final String CLASS_LODER_APPENDER = "Service";
	/* This type mapping only maps simple types the mapping for
	   complex types are done with in the type class */
	private static Hashtable class2QNamemap = new Hashtable();
	private static Hashtable qname2classmap = new Hashtable();
	private static Hashtable type2getValueMethodName = new Hashtable();
	
	static{
		 /*
		  * This type mapping is not complete. Susantha Ayya Can u please fill it 
		  */		
		 class2QNamemap.put("int", new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"));
		 class2QNamemap.put("unsigned char", new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"));
		 class2QNamemap.put("float", new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"));
		 class2QNamemap.put("long", new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"));
		 class2QNamemap.put("double", new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"));
		 class2QNamemap.put("int", new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"));
		 class2QNamemap.put("char", new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"));
		 class2QNamemap.put("short", new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"));
		 class2QNamemap.put("string", new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"));
		 class2QNamemap.put("string", new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"));

		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"), "int");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"), "unsigned char");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"), "float");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"), "long");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"), "double");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"), "int");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"), "char");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"), "short");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"), "string");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"), "string");
	}
	public static boolean isSimpleType(String name){
		if(class2QNamemap.containsKey(name))
			return true;
		return false;	
	} 

	public static boolean isSimpleType(QName name){
		if(qname2classmap.containsKey(name))
			return true;
		return false;	
	} 

	
	public static String getParameterGetValueMethodName(String typeName){
		type2getValueMethodName.put("int","GetInt");
		type2getValueMethodName.put("float","GetFloat");
		type2getValueMethodName.put("string","GetString");
		type2getValueMethodName.put("long","GetLong");
		type2getValueMethodName.put("short","GetShort");
		type2getValueMethodName.put("char","GetChar");
		type2getValueMethodName.put("double","GetDouble");
		type2getValueMethodName.put("unsigned long","GetUnsignedLong");
		type2getValueMethodName.put("unsigned int","GetUnsignedInt");
		type2getValueMethodName.put("unsigned short","GetUnsignedShort");
		type2getValueMethodName.put("unsigned char","GetUnsignedChar");
		String methodname;
		if((methodname = (String)type2getValueMethodName.get(typeName))!= null)
			return methodname+"()";
		return null;	
	}
	
	public static QName getQname4class(String classname) {
		Object val = class2QNamemap.get(classname);
		if (val != null)
			return (QName) val;
		else
			return null;
	}

	 public static String getclass4qname(QName qname) {
		Object val = qname2classmap.get(qname);
		if (val != null)
			return (String) val;
		else
			return null;
	}
	public static String getWebServiceNameFromWrapperName(String wname){
		return wname.substring(0, wname.length()- CPPUtils.WRAPPER_NAME_APPENDER.length());
	}
	public static String getXSDTypeForBasicType(String stype){
		if ("int".equals(stype)) return "XSD_INT";
		else if ("string".equals(stype)) return "XSD_STRING";
		else if ("unsigned int".equals(stype)) return "XSD_UNSIGNEDINT";
		else if ("short".equals(stype)) return "XSD_SHORT";
		else if ("unsigned short".equals(stype)) return "XSD_UNSIGNEDSHORT";
		else if ("long".equals(stype)) return "XSD_LONG";
		else if ("unsigned long".equals(stype)) return "XSD_UNSIGNEDLONG";
		else if ("char".equals(stype)) return "XSD_BYTE";
		else if ("unsigned char".equals(stype)) return "XSD_BYTE";
		else if ("float".equals(stype)) return "XSD_FLOAT";
		else if ("double".equals(stype)) return "XSD_DOUBLE";
		else if ("struct tm".equals(stype)) return "XSD_DATETIME";
		else return "unknown type";
	}
}
