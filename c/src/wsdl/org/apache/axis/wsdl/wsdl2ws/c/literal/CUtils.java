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

package org.apache.axis.wsdl.wsdl2ws.c.literal;

import java.util.Hashtable;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

public class CUtils {
	public static final String WRAPPER_NAME_APPENDER = "Wrapper";
	public static final String CLASS_LODER_APPENDER = "Service";
	public static final String WRAPPER_METHOD_APPENDER = "Wrapped";
	/* This type mapping only maps simple types the mapping for
	   complex types are done with in the type class */
	private static Hashtable class2QNamemap = new Hashtable();
	private static Hashtable qname2classmap = new Hashtable();
	private static Hashtable type2getValueMethodName = new Hashtable();
	private static Hashtable type2BasicArrayName = new Hashtable();
	
	static{	
		class2QNamemap.put("int", new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"));
		class2QNamemap.put("unsigned char", new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"));
		class2QNamemap.put("float", new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"));
		class2QNamemap.put("long", new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"));
		class2QNamemap.put("double", new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"));
		class2QNamemap.put("char", new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"));
		class2QNamemap.put("short", new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"));
		class2QNamemap.put("xsd__string", new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"));
		class2QNamemap.put("xsd__dateTime", new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"));
		class2QNamemap.put("xsd__date", new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"));
		class2QNamemap.put("xsd__time", new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"));
		class2QNamemap.put("xsd__base64Binary", new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"));
		class2QNamemap.put("xsd__hexBinary", new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"));
		class2QNamemap.put("xsd__decimal", new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"));
		class2QNamemap.put("xsd__boolean", new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"));
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"), "int");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"), "unsigned char");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"), "float");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"), "long");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"), "double");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"), "char");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"), "short");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"), "xsd__string");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"), "xsd__dateTime");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"), "xsd__date");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"), "xsd__time");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"), "xsd__base64Binary");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"), "xsd__hexBinary");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"), "xsd__decimal");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"), "xsd__boolean");
		type2getValueMethodName.put("int","Int");
		type2getValueMethodName.put("float","Float");
		type2getValueMethodName.put("xsd__string","String");
		type2getValueMethodName.put("long","Long");
		type2getValueMethodName.put("short","Short");
		type2getValueMethodName.put("char","Char");
		type2getValueMethodName.put("double","Double");
		type2getValueMethodName.put("unsigned long","UnsignedLong");
		type2getValueMethodName.put("unsigned int","UnsignedInt");
		type2getValueMethodName.put("unsigned short","UnsignedShort");
		type2getValueMethodName.put("unsigned char","UnsignedChar");
		type2getValueMethodName.put("xsd__dateTime","DateTime");
		type2getValueMethodName.put("xsd__date","Date");
		type2getValueMethodName.put("xsd__time","Time");
		type2getValueMethodName.put("xsd__base64Binary","Base64Binary");
		type2getValueMethodName.put("xsd__hexBinary","HexBinary");
		type2getValueMethodName.put("xsd__decimal","Decimal");
		type2getValueMethodName.put("xsd__boolean","Boolean");
		type2BasicArrayName.put("int","xsd__int_Array");
		type2BasicArrayName.put("float","xsd__float_Array");
		type2BasicArrayName.put("xsd__string","xsd__string_Array");
		type2BasicArrayName.put("long","xsd__long_Array");
		type2BasicArrayName.put("short","xsd__short_Array");
		type2BasicArrayName.put("char","xsd__byte_Array");
		type2BasicArrayName.put("double","xsd__double_Array");
		type2BasicArrayName.put("unsigned long","xsd__unsignedLong_Array");
		type2BasicArrayName.put("unsigned int","xsd__unsignedInt_Array");
		type2BasicArrayName.put("unsigned short","xsd__unsignedShort_Array");
		type2BasicArrayName.put("unsigned char","xsd__unsignedByte_Array");
		type2BasicArrayName.put("xsd__dateTime","xsd__dateTime_Array");
		type2BasicArrayName.put("xsd__date","xsd__date_Array");
		type2BasicArrayName.put("xsd__time","xsd__time_Array");
		type2BasicArrayName.put("xsd__base64Binary","xsd__base64Binary_Array");
		type2BasicArrayName.put("xsd__hexBinary","xsd__hexBinary_Array");
		type2BasicArrayName.put("xsd__decimal","xsd__decimal_Array");
		type2BasicArrayName.put("xsd__boolean","xsd__boolean_Array");
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

	
	public static String getParameterGetValueMethodName(String typeName, boolean isAttrib){
		String methodname;
		if((methodname = (String)type2getValueMethodName.get(typeName))!= null){
			methodname = (isAttrib ? "GetAttributeAs":"GetElementAs") + methodname;
			return methodname;
		}
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
		return wname.substring(0, wname.length()- CUtils.WRAPPER_NAME_APPENDER.length());
	}
	public static String getXSDTypeForBasicType(String stype){
		if ("int".equals(stype)) return "XSD_INT";
		else if ("xsd__string".equals(stype)) return "XSD_STRING";
		else if ("unsigned int".equals(stype)) return "XSD_UNSIGNEDINT";
		else if ("short".equals(stype)) return "XSD_SHORT";
		else if ("unsigned short".equals(stype)) return "XSD_UNSIGNEDSHORT";
		else if ("long".equals(stype)) return "XSD_LONG";
		else if ("unsigned long".equals(stype)) return "XSD_UNSIGNEDLONG";
		else if ("char".equals(stype)) return "XSD_BYTE";
		else if ("unsigned char".equals(stype)) return "XSD_BYTE";
		else if ("float".equals(stype)) return "XSD_FLOAT";
		else if ("double".equals(stype)) return "XSD_DOUBLE";
		else if ("xsd__dateTime".equals(stype)) return "XSD_DATETIME";
		else if ("xsd__date".equals(stype)) return "XSD_DATE";
		else if ("xsd__time".equals(stype)) return "XSD_TIME";
		else if ("xsd__base64Binary".equals(stype)) return "XSD_BASE64BINARY";
		else if ("xsd__hexBinary".equals(stype)) return "XSD_HEXBINARY";
		else if ("xsd__decimal".equals(stype)) return "XSD_DECIMAL";
		else if ("xsd__boolean".equals(stype)) return "XSD_BOOLEAN";
		else return "unknown type";
	}
	public static String getBasicArrayNameforType(String stype){
		String arrayName;
		if((arrayName = (String)type2BasicArrayName.get(stype))!= null){
			return arrayName;
		}
		return null;		
	}
}
