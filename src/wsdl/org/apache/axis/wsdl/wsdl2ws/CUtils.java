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
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Sanjaya Singharage (sanjayas@opensource.lk, sanjayas@jkcsworld.com)
 */

package org.apache.axis.wsdl.wsdl2ws;

import java.util.Hashtable;
import javax.xml.namespace.QName;
import java.util.Vector;
import org.w3c.dom.Node;
import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.axis.wsdl.toJava.Utils;
import org.apache.axis.Constants;
import org.w3c.dom.NodeList;
import org.apache.axis.wsdl.symbolTable.TypeEntry;
import javax.xml.rpc.holders.BooleanHolder;
import org.apache.axis.wsdl.symbolTable.SchemaUtils;
import org.apache.axis.wsdl.wsdl2ws.info.TypeMap;

public class CUtils {
	public static final String WRAPPER_NAME_APPENDER = "Wrapper";
	public static final String CLASS_LOADER_APPENDER = "Service";
	public static final String WRAPPER_METHOD_APPENDER = "Wrapped";
	public static final QName anyTypeQname = new QName("http://ws.apache.org/axisc/types","AnyType");

	// File suffix for C++ Class files
	public static final String CPP_CLASS_SUFFIX = ".cpp";
	// File suffix for C++ Header files
	public static final String CPP_HEADER_SUFFIX = ".hpp";
	// File suffix for C Source files
	public static final String C_FILE_SUFFIX = ".c";
	// File suffix fr C Header files
	public static final String C_HEADER_SUFFIX = ".h";

	/* This type mapping only maps simple types the mapping for
	   complex types are done with in the type class */
	private static Hashtable class2QNamemapCpp = new Hashtable();
	private static Hashtable class2QNamemapC = new Hashtable();
	private static Hashtable initValuesCpp = new Hashtable();
	private static Hashtable initValuesC = new Hashtable();
	private static Hashtable qname2classmapCpp = new Hashtable();
	private static Hashtable qname2classmapC = new Hashtable();
	private static Hashtable schemaDefinedSimpleTypesMap = new Hashtable();
	private static Hashtable type2getValueMethodNameCpp = new Hashtable();
	private static Hashtable type2getValueMethodNameC = new Hashtable();
	private static Hashtable type2BasicArrayNameCpp = new Hashtable();
	private static Hashtable type2BasicArrayNameC = new Hashtable();
	private static Hashtable basicType2EnumMapCpp = new Hashtable();
	private static Hashtable basicType2EnumMapC = new Hashtable();
	private static boolean cpp = true;
	
	static{	
		class2QNamemapCpp.put("xsd__int",new QName(WrapperConstants.SCHEMA_NAMESPACE,				"int"));
		class2QNamemapCpp.put("xsd__unsignedByte", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"byte"));
		class2QNamemapCpp.put("xsd__float", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"float"));
		class2QNamemapCpp.put("xsd__long", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"long"));
		class2QNamemapCpp.put("xsd__long", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"integer"));
		class2QNamemapCpp.put("xsd__double", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"double"));
		class2QNamemapCpp.put("xsd__char", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"char"));
		class2QNamemapCpp.put("xsd__short", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"short"));
		class2QNamemapCpp.put("xsd__string", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"string"));
		class2QNamemapCpp.put("xsd__dateTime", new QName(WrapperConstants.SCHEMA_NAMESPACE,		"dateTime"));
		class2QNamemapCpp.put("xsd__date", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"date"));
		class2QNamemapCpp.put("xsd__time", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"time"));
		class2QNamemapCpp.put("xsd__base64Binary", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"base64Binary"));
		class2QNamemapCpp.put("xsd__hexBinary", new QName(WrapperConstants.SCHEMA_NAMESPACE,		"hexBinary"));
		class2QNamemapCpp.put("xsd__decimal", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"decimal"));
		class2QNamemapCpp.put("xsd__boolean", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"boolean"));
		class2QNamemapCpp.put("xsd__byte", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"byte"));
		class2QNamemapCpp.put("xsd__anyURI", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"anyURI"));
		class2QNamemapCpp.put("xsd__unsignedByte", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"unsignedByte"));
		class2QNamemapCpp.put("xsd__unsignedInt", new QName(WrapperConstants.SCHEMA_NAMESPACE,		"unsignedInt"));
		class2QNamemapCpp.put("xsd__unsignedLong", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"unsignedLong"));
		class2QNamemapCpp.put("xsd__unsignedShort", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"unsignedShort"));
		class2QNamemapCpp.put("xsd__QName", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"QName"));
		class2QNamemapCpp.put("xsd__NCName", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"NCName"));
		class2QNamemapCpp.put("xsd__NMTOKEN", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"NMTOKEN"));

		class2QNamemapC.put("xsdc__int",new QName(WrapperConstants.SCHEMA_NAMESPACE,				"int"));
		class2QNamemapC.put("xsdc__unsignedByte", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"byte"));
		class2QNamemapC.put("xsdc__float", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"float"));
		class2QNamemapC.put("xsdc__long", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"long"));
		class2QNamemapC.put("xsdc__long", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"integer"));
		class2QNamemapC.put("xsdc__double", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"double"));
		class2QNamemapC.put("xsdc__char", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"char"));
		class2QNamemapC.put("xsdc__short", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"short"));
		class2QNamemapC.put("xsdc__string", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"string"));
		class2QNamemapC.put("xsdc__dateTime", new QName(WrapperConstants.SCHEMA_NAMESPACE,		"dateTime"));
		class2QNamemapC.put("xsdc__date", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"date"));
		class2QNamemapC.put("xsdc__time", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"time"));
		class2QNamemapC.put("xsdc__base64Binary", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"base64Binary"));
		class2QNamemapC.put("xsdc__hexBinary", new QName(WrapperConstants.SCHEMA_NAMESPACE,		"hexBinary"));
		class2QNamemapC.put("xsdc__decimal", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"decimal"));
		class2QNamemapC.put("xsdc__boolean", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"boolean"));
		class2QNamemapC.put("xsdc__byte", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"byte"));
		class2QNamemapC.put("xsdc__anyURI", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"anyURI"));
		class2QNamemapC.put("xsdc__unsignedByte", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"unsignedByte"));
		class2QNamemapC.put("xsdc__unsignedInt", new QName(WrapperConstants.SCHEMA_NAMESPACE,		"unsignedInt"));
		class2QNamemapC.put("xsdc__unsignedLong", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"unsignedLong"));
		class2QNamemapC.put("xsdc__unsignedShort", new QName(WrapperConstants.SCHEMA_NAMESPACE,	"unsignedShort"));
		class2QNamemapC.put("xsdc__QName", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"QName"));
		class2QNamemapC.put("xsdc__NCName", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"NCName"));
		class2QNamemapC.put("xsdc__NMTOKEN", new QName(WrapperConstants.SCHEMA_NAMESPACE,			"NMTOKEN"));

		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"),				"xsd__int");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"),			"xsd__unsignedByte");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"),			"xsd__float");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"),			"xsd__long");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"),			"xsd__long");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"),			"xsd__double");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"),			"xsd__char");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"),			"xsd__short");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"),			"xsd__string");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"),		"xsd__dateTime");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"),			"xsd__date");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"),			"xsd__time");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"),	"xsd__base64Binary");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"),		"xsd__hexBinary");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"),			"xsd__decimal");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"),			"xsd__boolean");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"),			"xsd__anyURI");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"),	"xsd__unsignedByte");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"),		"xsd__unsignedInt");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"),	"xsd__unsignedLong");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"),	"xsd__unsignedShort");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"),			"xsd__QName");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NCName"),			"xsd__NCName");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"),			"xsd__NMTOKEN");
		
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"),				"xsdc__int");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"),			"xsdc__unsignedByte");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"),			"xsdc__float");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"),			"xsdc__long");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"),			"xsdc__long");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"),			"xsdc__double");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"),			"xsdc__char");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"),			"xsdc__short");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"),			"xsdc__string");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"),		"xsdc__dateTime");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"),			"xsdc__date");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"),			"xsdc__time");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"),	"xsdc__base64Binary");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"),		"xsdc__hexBinary");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"),			"xsdc__decimal");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"),			"xsdc__boolean");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"),			"xsdc__anyURI");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"),	"xsdc__unsignedByte");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"),		"xsdc__unsignedInt");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"),	"xsdc__unsignedLong");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"),	"xsdc__unsignedShort");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"),			"xsdc__QName");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NCName"),			"xsdc__NCName");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"),			"xsdc__NMTOKEN");
		
		/* TODO:
		 *   Should be removed when the following issue will be fixed :
		 * 	-> http://marc.theaimsgroup.com/?t=107907748000002&r=1&w=2 
		 */
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"),			"xsd__int");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"),			"xsd__unsignedByte");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"),			"xsd__float");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"),			"xsd__long");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "integer"),		"xsd__long");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"),			"xsd__double");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "char"),			"xsd__char");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"),			"xsd__short");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "string"),			"xsd__string");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "dateTime"),		"xsd__dateTime");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "date"),			"xsd__date");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "time"),			"xsd__time");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64Binary"),	"xsd__base64Binary");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "hexBinary"),		"xsd__hexBinary");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "decimal"),		"xsd__decimal");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "boolean"),		"xsd__boolean");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "anyURI"),			"xsd__anyURI");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedByte"),	"xsd__unsignedByte");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedInt"),	"xsd__unsignedInt");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedLong"),	"xsd__unsignedLong");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedShort"),	"xsd__unsignedShort");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "QName"),			"xsd__QName");		
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "NCName"),			"xsd__NCName");		


		/* TODO:
		 *  Another strange issue from Axis 1.1 runtime when base64binary is in input/output operations.
		 */	
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64"), "xsd__base64Binary");		
		
		/* TODO:
		 *   Should be removed when the following issue will be fixed :
		 * 	-> http://marc.theaimsgroup.com/?t=107907748000002&r=1&w=2 
		 */
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"),			"xsdc__int");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"),			"xsdc__unsignedByte");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"),			"xsdc__float");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"),			"xsdc__long");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "integer"),		"xsdc__long");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"),			"xsdc__double");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "char"),			"xsdc__char");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"),			"xsdc__short");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "string"),			"xsdc__string");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "dateTime"),		"xsdc__dateTime");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "date"),			"xsdc__date");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "time"),			"xsdc__time");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64Binary"),	"xsdc__base64Binary");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "hexBinary"),		"xsdc__hexBinary");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "decimal"),		"xsdc__decimal");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "boolean"),		"xsdc__boolean");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "anyURI"),			"xsdc__anyURI");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedByte"),	"xsdc__unsignedByte");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedInt"),	"xsdc__unsignedInt");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedLong"),	"xsdc__unsignedLong");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedShort"),	"xsdc__unsignedShort");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "QName"),			"xsdc__QName");		
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "NCName"),			"xsdc__NCName");		


		/* TODO:
		 *  Another strange issue from Axis 1.1 runtime when base64binary is in input/output operations.
		 */	
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64"), "xsdc__base64Binary");		
		
		type2getValueMethodNameCpp.put("xsd__int",				"Int");
		type2getValueMethodNameCpp.put("xsd__float",			"Float");
		type2getValueMethodNameCpp.put("xsd__string",			"String");
		type2getValueMethodNameCpp.put("xsd__long",			"Long");
		type2getValueMethodNameCpp.put("xsd__short",			"Short");
		type2getValueMethodNameCpp.put("xsd__char",			"Char");
		type2getValueMethodNameCpp.put("xsd__double",			"Double");
		type2getValueMethodNameCpp.put("xsd__unsignedByte",	"Byte");			
		type2getValueMethodNameCpp.put("xsd__unsignedLong",	"UnsignedLong");
		type2getValueMethodNameCpp.put("xsd__unsignedInt",		"UnsignedInt");
		type2getValueMethodNameCpp.put("xsd__unsignedShort",	"UnsignedShort");
		type2getValueMethodNameCpp.put("xsd__unsignedByte",	"UnsignedByte");
		type2getValueMethodNameCpp.put("xsd__dateTime",		"DateTime");
		type2getValueMethodNameCpp.put("xsd__date",			"Date");
		type2getValueMethodNameCpp.put("xsd__time",			"Time");
		type2getValueMethodNameCpp.put("xsd__base64Binary",	"Base64Binary");
		type2getValueMethodNameCpp.put("xsd__hexBinary",		"HexBinary");
		type2getValueMethodNameCpp.put("xsd__decimal",			"Decimal");
		type2getValueMethodNameCpp.put("xsd__boolean",			"Boolean");
		type2getValueMethodNameCpp.put("xsd__anyURI",			"String");
		type2getValueMethodNameCpp.put("xsd__QName",			"String");
		type2getValueMethodNameCpp.put("xsd__NCName",			"String");
		type2getValueMethodNameCpp.put("xsd__NMTOKEN",			"String");
		
		type2getValueMethodNameC.put("xsdc__int",				"Int");
		type2getValueMethodNameC.put("xsdc__float",			"Float");
		type2getValueMethodNameC.put("xsdc__string",			"String");
		type2getValueMethodNameC.put("xsdc__long",			"Long");
		type2getValueMethodNameC.put("xsdc__short",			"Short");
		type2getValueMethodNameC.put("xsdc__char",			"Char");
		type2getValueMethodNameC.put("xsdc__double",			"Double");
		type2getValueMethodNameC.put("xsdc__unsignedByte",	"Byte");			
		type2getValueMethodNameC.put("xsdc__unsignedLong",	"UnsignedLong");
		type2getValueMethodNameC.put("xsdc__unsignedInt",		"UnsignedInt");
		type2getValueMethodNameC.put("xsdc__unsignedShort",	"UnsignedShort");
		type2getValueMethodNameC.put("xsdc__unsignedByte",	"UnsignedByte");
		type2getValueMethodNameC.put("xsdc__dateTime",		"DateTime");
		type2getValueMethodNameC.put("xsdc__date",			"Date");
		type2getValueMethodNameC.put("xsdc__time",			"Time");
		type2getValueMethodNameC.put("xsdc__base64Binary",	"Base64Binary");
		type2getValueMethodNameC.put("xsdc__hexBinary",		"HexBinary");
		type2getValueMethodNameC.put("xsdc__decimal",			"Decimal");
		type2getValueMethodNameC.put("xsdc__boolean",			"Boolean");
		type2getValueMethodNameC.put("xsdc__anyURI",			"String");
		type2getValueMethodNameC.put("xsdc__QName",			"String");
		type2getValueMethodNameC.put("xsdc__NCName",			"String");
		type2getValueMethodNameC.put("xsdc__NMTOKEN",			"String");
		
		type2BasicArrayNameCpp.put("xsd__int",					"xsd__int_Array");
		type2BasicArrayNameCpp.put("xsd__float",				"xsd__float_Array");
		type2BasicArrayNameCpp.put("xsd__string",				"xsd__string_Array");
		type2BasicArrayNameCpp.put("xsd__long",				"xsd__long_Array");
		type2BasicArrayNameCpp.put("xsd__short",				"xsd__short_Array");
		type2BasicArrayNameCpp.put("xsd__char",				"xsd__byte_Array");
		type2BasicArrayNameCpp.put("xsd__double",				"xsd__double_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedLong",		"xsd__unsignedLong_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedInt",			"xsd__unsignedInt_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedShort",		"xsd__unsignedShort_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedByte",		"xsd__unsignedByte_Array");
		type2BasicArrayNameCpp.put("xsd__dateTime",			"xsd__dateTime_Array");
		type2BasicArrayNameCpp.put("xsd__date",				"xsd__date_Array");
		type2BasicArrayNameCpp.put("xsd__time",				"xsd__time_Array");
		type2BasicArrayNameCpp.put("xsd__base64Binary",		"xsd__base64Binary_Array");
		type2BasicArrayNameCpp.put("xsd__hexBinary",			"xsd__hexBinary_Array");
		type2BasicArrayNameCpp.put("xsd__decimal",				"xsd__decimal_Array");
		type2BasicArrayNameCpp.put("xsd__boolean",				"xsd__boolean_Array");
		type2BasicArrayNameCpp.put("xsd__anyURI",				"xsd__anyURI_Array");
		type2BasicArrayNameCpp.put("xsd__QName",				"xsd__QName_Array");
		type2BasicArrayNameCpp.put("xsd__NCName",				"xsd__NCName_Array");
		type2BasicArrayNameCpp.put("xsd__NMTOKEN",				"xsd__NMTOKEN_Array");
		
		type2BasicArrayNameC.put("xsdc__int",					"xsdc__int_Array");
		type2BasicArrayNameC.put("xsdc__float",				"xsdc__float_Array");
		type2BasicArrayNameC.put("xsdc__string",				"xsdc__string_Array");
		type2BasicArrayNameC.put("xsdc__long",				"xsdc__long_Array");
		type2BasicArrayNameC.put("xsdc__short",				"xsdc__short_Array");
		type2BasicArrayNameC.put("xsdc__char",				"xsdc__byte_Array");
		type2BasicArrayNameC.put("xsdc__double",				"xsdc__double_Array");
		type2BasicArrayNameC.put("xsdc__unsignedLong",		"xsdc__unsignedLong_Array");
		type2BasicArrayNameC.put("xsdc__unsignedInt",			"xsdc__unsignedInt_Array");
		type2BasicArrayNameC.put("xsdc__unsignedShort",		"xsdc__unsignedShort_Array");
		type2BasicArrayNameC.put("xsdc__unsignedByte",		"xsdc__unsignedByte_Array");
		type2BasicArrayNameC.put("xsdc__dateTime",			"xsdc__dateTime_Array");
		type2BasicArrayNameC.put("xsdc__date",				"xsdc__date_Array");
		type2BasicArrayNameC.put("xsdc__time",				"xsdc__time_Array");
		type2BasicArrayNameC.put("xsdc__base64Binary",		"xsdc__base64Binary_Array");
		type2BasicArrayNameC.put("xsdc__hexBinary",			"xsdc__hexBinary_Array");
		type2BasicArrayNameC.put("xsdc__decimal",				"xsdc__decimal_Array");
		type2BasicArrayNameC.put("xsdc__boolean",				"xsdc__boolean_Array");
		type2BasicArrayNameC.put("xsdc__anyURI",				"xsdc__anyURI_Array");
		type2BasicArrayNameC.put("xsdc__QName",				"xsdc__QName_Array");
		type2BasicArrayNameC.put("xsdc__NCName",				"xsdc__NCName_Array");
		type2BasicArrayNameC.put("xsdc__NMTOKEN",				"xsdc__NMTOKEN_Array");
		
		basicType2EnumMapCpp.put("xsd__int",					"XSD_INT");
		basicType2EnumMapCpp.put("xsd__float",					"XSD_FLOAT");
		basicType2EnumMapCpp.put("xsd__string",				"XSD_STRING");
		basicType2EnumMapCpp.put("xsd__long",					"XSD_LONG");
		basicType2EnumMapCpp.put("xsd__short",					"XSD_SHORT");
		basicType2EnumMapCpp.put("xsd__unsignedByte",			"XSD_BYTE");
		basicType2EnumMapCpp.put("xsd__double",				"XSD_DOUBLE");
		basicType2EnumMapCpp.put("xsd__unsignedLong",			"XSD_UNSIGNEDLONG");
		basicType2EnumMapCpp.put("xsd__unsignedInt",			"XSD_UNSIGNEDINT");
		basicType2EnumMapCpp.put("xsd__unsignedShort",			"XSD_UNSIGNEDSHORT");
		basicType2EnumMapCpp.put("xsd__unsignedByte",			"XSD_UNSIGNEDBYTE");
		basicType2EnumMapCpp.put("xsd__dateTime",				"XSD_DATETIME");
		basicType2EnumMapCpp.put("xsd__date",					"XSD_DATE");
		basicType2EnumMapCpp.put("xsd__time",					"XSD_TIME");
		basicType2EnumMapCpp.put("xsd__base64Binary",			"XSD_BASE64BINARY");
		basicType2EnumMapCpp.put("xsd__hexBinary",				"XSD_HEXBINARY");
		basicType2EnumMapCpp.put("xsd__decimal",				"XSD_DECIMAL");
		basicType2EnumMapCpp.put("xsd__boolean",				"XSD_BOOLEAN");
		basicType2EnumMapCpp.put("xsd__anyURI",				"XSD_ANYURI");
		basicType2EnumMapCpp.put("xsd__QName",					"XSD_QNAME");
		basicType2EnumMapCpp.put("xsd__NCName",				"XSD_NCNAME");
		basicType2EnumMapCpp.put("xsd__NMTOKEN",				"XSD_NMTOKEN");

		basicType2EnumMapC.put("xsdc__int",					"XSD_INT");
		basicType2EnumMapC.put("xsdc__float",					"XSD_FLOAT");
		basicType2EnumMapC.put("xsdc__string",				"XSD_STRING");
		basicType2EnumMapC.put("xsdc__long",					"XSD_LONG");
		basicType2EnumMapC.put("xsdc__short",					"XSD_SHORT");
		basicType2EnumMapC.put("xsdc__unsignedByte",			"XSD_BYTE");
		basicType2EnumMapC.put("xsdc__double",				"XSD_DOUBLE");
		basicType2EnumMapC.put("xsdc__unsignedLong",			"XSD_UNSIGNEDLONG");
		basicType2EnumMapC.put("xsdc__unsignedInt",			"XSD_UNSIGNEDINT");
		basicType2EnumMapC.put("xsdc__unsignedShort",			"XSD_UNSIGNEDSHORT");
		basicType2EnumMapC.put("xsdc__unsignedByte",			"XSD_UNSIGNEDBYTE");
		basicType2EnumMapC.put("xsdc__dateTime",				"XSD_DATETIME");
		basicType2EnumMapC.put("xsdc__date",					"XSD_DATE");
		basicType2EnumMapC.put("xsdc__time",					"XSD_TIME");
		basicType2EnumMapC.put("xsdc__base64Binary",			"XSD_BASE64BINARY");
		basicType2EnumMapC.put("xsdc__hexBinary",				"XSD_HEXBINARY");
		basicType2EnumMapC.put("xsdc__decimal",				"XSD_DECIMAL");
		basicType2EnumMapC.put("xsdc__boolean",				"XSD_BOOLEAN");
		basicType2EnumMapC.put("xsdc__anyURI",				"XSD_ANYURI");
		basicType2EnumMapC.put("xsdc__QName",					"XSD_QNAME");
		basicType2EnumMapC.put("xsdc__NCName",				"XSD_NCNAME");
		basicType2EnumMapC.put("xsdc__NMTOKEN",				"XSD_NMTOKEN");


		initValuesCpp.put("xsd__int",				"0"); 
		initValuesCpp.put("xsd__unsignedByte",		"0"); 
		initValuesCpp.put("xsd__float",			"0.0"); 
		initValuesCpp.put("xsd__long",				"0"); 
		initValuesCpp.put("xsd__double",			"0.0"); 
		initValuesCpp.put("xsd__char",				"0"); 
		initValuesCpp.put("xsd__short",			"0"); 
		initValuesCpp.put("xsd__string",			"NULL"); 
		//initValuesCpp.put("xsd__dateTime",		"0"); 
		//initValuesCpp.put("xsd__date",			"0"); 
		//initValuesCpp.put("xsd__time",			"0"); 
		//initValuesCpp.put("xsd__base64Binary",	"0"); 
		//initValuesCpp.put("xsd__hexBinary",		"0"); 
		initValuesCpp.put("xsd__decimal",			"0.0"); 
		initValuesCpp.put("xsd__boolean",			"false_"); 
		initValuesCpp.put("xsd__byte",				"0"); 
		initValuesCpp.put("xsd__anyURI",			"NULL"); 
		initValuesCpp.put("xsd__unsignedByte",		"0"); 
		initValuesCpp.put("xsd__unsignedInt",		"0"); 
		initValuesCpp.put("xsd__unsignedLong",		"0"); 
		initValuesCpp.put("xsd__unsignedShort",	"0"); 
		initValuesCpp.put("xsd__QName",			"NULL"); 
		initValuesCpp.put("xsd__NCName",			"NULL"); 
		initValuesCpp.put("xsd__NMTOKEN",			"NULL"); 
		
		initValuesC.put("xsdc__int",				"0"); 
		initValuesC.put("xsdc__unsignedByte",		"0"); 
		initValuesC.put("xsdc__float",			"0.0"); 
		initValuesC.put("xsdc__long",				"0"); 
		initValuesC.put("xsdc__double",			"0.0"); 
		initValuesC.put("xsdc__char",				"0"); 
		initValuesC.put("xsdc__short",			"0"); 
		initValuesC.put("xsdc__string",			"NULL"); 
		//initValuesC.put("xsdc__dateTime",		"0"); 
		//initValuesC.put("xsdc__date",			"0"); 
		//initValuesC.put("xsdc__time",			"0"); 
		//initValuesC.put("xsdc__base64Binary",	"0"); 
		//initValuesC.put("xsdc__hexBinary",		"0"); 
		initValuesC.put("xsdc__decimal",			"0.0"); 
		initValuesC.put("xsdc__boolean",			"false_"); 
		initValuesC.put("xsdc__byte",				"0"); 
		initValuesC.put("xsdc__anyURI",			"NULL"); 
		initValuesC.put("xsdc__unsignedByte",		"0"); 
		initValuesC.put("xsdc__unsignedInt",		"0"); 
		initValuesC.put("xsdc__unsignedLong",		"0"); 
		initValuesC.put("xsdc__unsignedShort",	"0"); 
		initValuesC.put("xsdc__QName",			"NULL"); 
		initValuesC.put("xsdc__NCName",			"NULL"); 
		initValuesC.put("xsdc__NMTOKEN",			"NULL"); 
	}
	
	public static void setLanguage(String language) {
		// Only C and C++ are supported here.
		if (WrapperConstants.LANGUAGE_C.equalsIgnoreCase(language))
			cpp = false;
		else 
			cpp = true; 
	}
	
	public static void addSchemaDefinedSimpleType(QName qname, String type){
		schemaDefinedSimpleTypesMap.put(qname, type);
	}
	
	public static boolean isBasicType(QName qname){
		if((cpp && qname2classmapCpp.containsKey(qname)) ||
		   (!cpp && qname2classmapC.containsKey(qname))){
			return true;
		}
		return false;
	}
	public static boolean isSimpleType(String name){
		if((cpp && class2QNamemapCpp.containsKey(name)) ||
		   (!cpp && class2QNamemapC.containsKey(name)))
			return true;
		return false;	
	} 
	public static boolean isAnyType(QName name){
			return name.equals(anyTypeQname);
	}
	public static boolean isSimpleType(QName name){
		if((cpp && qname2classmapCpp.containsKey(name)) ||
		   (!cpp && qname2classmapC.containsKey(name))){
			return true;
		}
		else if (schemaDefinedSimpleTypesMap.containsKey(name)){
			return true;
		}
		return false;	
	} 

	public static boolean isDefinedSimpleType(QName name){
		return schemaDefinedSimpleTypesMap.containsKey(name);	
	}
		
	public static String getParameterGetValueMethodName(String typeName, boolean isAttrib){
		String methodname = null;
		if (cpp)
			methodname = (String)type2getValueMethodNameCpp.get(typeName);
		else
			methodname = (String)type2getValueMethodNameC.get(typeName);
		
		if (methodname != null){
			if (cpp)
				methodname = (isAttrib ? "getAttributeAs":"getElementAs") + methodname;
			else
				methodname = "axisc" + (isAttrib ? "GetAttributeAs":"GetElementAs") + methodname + "Call";
			return methodname;
		}
		return null;	
	}
	
	public static QName getQname4class(String classname) {
		Object val = null;
		if (cpp)
			val = class2QNamemapCpp.get(classname);
		else 
			val = class2QNamemapC.get(classname);
		if (val != null)
			return (QName) val;
		else
			return null;
	}

	 public static String getclass4qname(QName qname) {
		Object val = null;
		if (cpp)
			val = qname2classmapCpp.get(qname);
		else
			val = qname2classmapC.get(qname);
		if (val != null)
			return (String) val;
		val = schemaDefinedSimpleTypesMap.get(qname);
		if (val != null)
			return (String) val;
		return null;
	}

	 public static String getInitValue(String typeName) {
		Object val = null;
		if (cpp) 
			val = initValuesCpp.get(typeName);
		else
			val = initValuesC.get(typeName);
		if (val != null)
			return (String) val;
                
		return null;
	}
        
	public static String getWebServiceNameFromWrapperName(String wname){
		return wname.substring(0, wname.length()- CUtils.WRAPPER_NAME_APPENDER.length());
	}
	public static String getXSDTypeForBasicType(String stype){
		String enumName = null;
		if (cpp)
			enumName = (String)basicType2EnumMapCpp.get(stype);
		else
			enumName = (String)basicType2EnumMapC.get(stype);
		if(enumName != null){
			return enumName;
		}
		return null;	
	}
	public static String getCmplxArrayNameforType(QName qname){
		String arrayName = null;
		if((cpp && !qname2classmapCpp.containsKey(qname)) ||
		   (!cpp && !qname2classmapC.containsKey(qname))){
			/* arrayName = qname.getLocalPart()+"_Array";
			* This avoid compilation issue for wsdl SimpleTypeInnerUnboundedInOutput.wsdl
			* See : malling list.
			*/
			arrayName = qname.getLocalPart().replace('>','_')+"_Array";			
		}
		return arrayName;		
	}
	
	public static String getBasicArrayNameforType(String stype){
		if (cpp && type2BasicArrayNameCpp.containsKey(stype))
			return (String)type2BasicArrayNameCpp.get(stype);
		else if (!cpp && type2BasicArrayNameC.containsKey(stype))
			return (String)type2BasicArrayNameC.get(stype);
		else
		 	return "";
	}
	
	/**
	 * If the specified node represents a supported JAX-RPC restriction,
	 * a Vector is returned which contains the base type and the values (enumerations etc).
	 * The first element in the vector is the base type (an TypeEntry).
	 * Subsequent elements are QNames.
	 */
	public static Vector getRestrictionBaseAndValues(Node node, SymbolTable symbolTable) {
		if (node == null) {
			return null;
		}

		// If the node kind is an element, dive into it.
		QName nodeKind = Utils.getNodeQName(node);
		if (nodeKind != null &&
			nodeKind.getLocalPart().equals("element") &&
			Constants.isSchemaXSD(nodeKind.getNamespaceURI())) {
			NodeList children = node.getChildNodes();
			Node simpleNode = null;
			for (int j = 0; j < children.getLength() && simpleNode == null; j++) {
				QName simpleKind = Utils.getNodeQName(children.item(j));
				if (simpleKind != null &&
					simpleKind.getLocalPart().equals("simpleType") &&
					Constants.isSchemaXSD(simpleKind.getNamespaceURI())) {
					simpleNode = children.item(j);
					node = simpleNode;
				}
			}
		}
		// Get the node kind, expecting a schema simpleType
		nodeKind = Utils.getNodeQName(node);
		if (nodeKind != null &&
			nodeKind.getLocalPart().equals("simpleType") &&
			Constants.isSchemaXSD(nodeKind.getNamespaceURI())) {

			// Under the simpleType there should be a restriction.
			// (There may be other #text nodes, which we will ignore).
			NodeList children = node.getChildNodes();
			Node restrictionNode = null;
			for (int j = 0; j < children.getLength() && restrictionNode == null; j++) {
				QName restrictionKind = Utils.getNodeQName(children.item(j));
				if (restrictionKind != null &&
					restrictionKind.getLocalPart().equals("restriction") &&
					Constants.isSchemaXSD(restrictionKind.getNamespaceURI()))
					restrictionNode = children.item(j);
			}

			// The restriction node indicates the type being restricted
			// (the base attribute contains this type).
			// The base type must be a simple type, and not boolean
			TypeEntry baseEType = null;
			if (restrictionNode != null) {
				QName baseType = Utils.getTypeQName(restrictionNode, new BooleanHolder(), false);
				baseEType = symbolTable.getType(baseType);
				if (baseEType != null) {
					String javaName = TypeMap.getBasicTypeClass4qname(baseEType.getQName());
					//String javaName = baseEType.getName();
					if (javaName == null || javaName.equals("boolean") ||
						! SchemaUtils.isSimpleSchemaType(baseEType.getQName())) {
						baseEType = null;
					}
				}
			}

			// Process the enumeration elements underneath the restriction node
			if (baseEType != null && restrictionNode != null) {
				Vector v = new Vector();                
				NodeList enums = restrictionNode.getChildNodes();
				for (int i=0; i < enums.getLength(); i++) {
					QName enumKind = Utils.getNodeQName(enums.item(i));
					if (enumKind != null &&
						/*enumKind.getLocalPart().equals("enumeration") && lets put all not only enumerations */
						Constants.isSchemaXSD(enumKind.getNamespaceURI())) {
							Node enumNode = enums.item(i);
							String value = Utils.getAttribute(enumNode, "value");
							/*if (value != null) {
								v.add(value);
							}*/
							//Samisa 23/08/2004
                                                        // HACK wollsch
                                                        if (value.indexOf(':')>0) {                                                        
                                                                value=value.substring(value.indexOf(':')+1,value.length());
                                                        }
							//Samisa
							v.add(new QName(value, enumKind.getLocalPart()));
					}
				}
                
				// is this really an enumeration?
				/* if(v.isEmpty()) return null; There can be restriction without any child nodes */
				// The first element in the vector is the base type (an TypeEntry).
				v.add(0,baseEType);
				return v;
			}
		}
		return null;
	}	
	
	
}
