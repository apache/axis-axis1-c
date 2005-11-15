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
	// Valid XML but invalid or reserved C/C++ characters 
	public static final String VALID_XML_INVALID_C = "//!\"#$%&'()*+,-./:;<=>?@\\^`{|}~[]\u00A3";

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
	private static Hashtable isPointerBasedType = new Hashtable();
	private static boolean cpp = true;
	
	static{	
		class2QNamemapCpp.put("xsd__duration",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "duration"));
		class2QNamemapCpp.put("xsd__dateTime",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"));
		class2QNamemapCpp.put("xsd__time",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"));
		class2QNamemapCpp.put("xsd__date",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"));
		class2QNamemapCpp.put("xsd__gYearMonth",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYearMonth"));
		class2QNamemapCpp.put("xsd__gYear",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYear"));
		class2QNamemapCpp.put("xsd__gMonthDay",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonthDay"));
		class2QNamemapCpp.put("xsd__gDay",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "gDay"));
		class2QNamemapCpp.put("xsd__gMonth",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonth"));
		class2QNamemapCpp.put("xsd__string",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"));
		class2QNamemapCpp.put("xsd__normalizedString", 		new QName(WrapperConstants.SCHEMA_NAMESPACE, "normalizedString"));
		class2QNamemapCpp.put("xsd__token",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "token"));
		class2QNamemapCpp.put("xsd__language",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "language"));
		class2QNamemapCpp.put("xsd__Name",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "Name"));
		class2QNamemapCpp.put("xsd__NCName",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "NCName"));
		class2QNamemapCpp.put("xsd__ID",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "ID"));
		class2QNamemapCpp.put("xsd__IDREF",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREF"));
		class2QNamemapCpp.put("xsd__IDREFS",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREFS"));
		class2QNamemapCpp.put("xsd__ENTITY",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITY"));
		class2QNamemapCpp.put("xsd__ENTITIES",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITIES"));
		class2QNamemapCpp.put("xsd__NMTOKEN",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"));
		class2QNamemapCpp.put("xsd__NMTOKENS",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKENS"));
		class2QNamemapCpp.put("xsd__boolean",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"));
		class2QNamemapCpp.put("xsd__base64Binary",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"));
		class2QNamemapCpp.put("xsd__hexBinary",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"));
		class2QNamemapCpp.put("xsd__float",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"));
		class2QNamemapCpp.put("xsd__decimal",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"));
		class2QNamemapCpp.put("xsd__integer",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"));
		class2QNamemapCpp.put("xsd__nonPositiveInteger",	new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonPositiveInteger"));
		class2QNamemapCpp.put("xsd__negativeInteger",		new QName(WrapperConstants.SCHEMA_NAMESPACE, "negativeInteger"));
		class2QNamemapCpp.put("xsd__long",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"));
		class2QNamemapCpp.put("xsd__int",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"));
		class2QNamemapCpp.put("xsd__short",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"));
		class2QNamemapCpp.put("xsd__byte",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"));
		class2QNamemapCpp.put("xsd__nonNegativeInteger",	new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonNegativeInteger"));
		class2QNamemapCpp.put("xsd__unsignedLong",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"));
		class2QNamemapCpp.put("xsd__unsignedInt",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"));
		class2QNamemapCpp.put("xsd__unsignedShort",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"));
		class2QNamemapCpp.put("xsd__unsignedByte",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"));
		class2QNamemapCpp.put("xsd__positiveInteger",		new QName(WrapperConstants.SCHEMA_NAMESPACE, "positiveInteger"));
		class2QNamemapCpp.put("xsd__double",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"));
		class2QNamemapCpp.put("xsd__anyURI",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"));
		class2QNamemapCpp.put("xsd__QName",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"));
		class2QNamemapCpp.put("xsd__NOTATION",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "NOTATION"));

		class2QNamemapC.put("xsdc__duration",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "duration"));
		class2QNamemapC.put("xsdc__dateTime",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"));
		class2QNamemapC.put("xsdc__time",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"));
		class2QNamemapC.put("xsdc__date",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"));
		class2QNamemapC.put("xsdc__gYearMonth",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYearMonth"));
		class2QNamemapC.put("xsdc__gYear",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYear"));
		class2QNamemapC.put("xsdc__gMonthDay",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonthDay"));
		class2QNamemapC.put("xsdc__gDay",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "gDay"));
		class2QNamemapC.put("xsdc__gMonth",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonth"));
		class2QNamemapC.put("xsdc__string",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"));
		class2QNamemapC.put("xsdc__normalizedString", 		new QName(WrapperConstants.SCHEMA_NAMESPACE, "normalizedString"));
		class2QNamemapC.put("xsdc__token",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "token"));
		class2QNamemapC.put("xsdc__language",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "language"));
		class2QNamemapC.put("xsdc__Name",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "Name"));
		class2QNamemapC.put("xsdc__NCName",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "NCName"));
		class2QNamemapC.put("xsdc__ID",						new QName(WrapperConstants.SCHEMA_NAMESPACE, "ID"));
		class2QNamemapC.put("xsdc__IDREF",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREF"));
		class2QNamemapC.put("xsdc__IDREFS",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREFS"));
		class2QNamemapC.put("xsdc__ENTITY",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITY"));
		class2QNamemapC.put("xsdc__ENTITIES",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITIES"));
		class2QNamemapC.put("xsdc__NMTOKEN",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"));
		class2QNamemapC.put("xsdc__NMTOKENS",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKENS"));
		class2QNamemapC.put("xsdc__boolean",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"));
		class2QNamemapC.put("xsdc__base64Binary",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"));
		class2QNamemapC.put("xsdc__hexBinary",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"));
		class2QNamemapC.put("xsdc__float",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"));
		class2QNamemapC.put("xsdc__decimal",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"));
		class2QNamemapC.put("xsdc__integer",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"));
		class2QNamemapC.put("xsdc__nonPositiveInteger",	new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonPositiveInteger"));
		class2QNamemapC.put("xsdc__negativeInteger",		new QName(WrapperConstants.SCHEMA_NAMESPACE, "negativeInteger"));
		class2QNamemapC.put("xsdc__long",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"));
		class2QNamemapC.put("xsdc__int",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"));
		class2QNamemapC.put("xsdc__short",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"));
		class2QNamemapC.put("xsdc__byte",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"));
		class2QNamemapC.put("xsdc__nonNegativeInteger",		new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonNegativeInteger"));
		class2QNamemapC.put("xsdc__unsignedLong",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"));
		class2QNamemapC.put("xsdc__unsignedInt",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"));
		class2QNamemapC.put("xsdc__unsignedShort",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"));
		class2QNamemapC.put("xsdc__unsignedByte",			new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"));
		class2QNamemapC.put("xsdc__positiveInteger",		new QName(WrapperConstants.SCHEMA_NAMESPACE, "positiveInteger"));
		class2QNamemapC.put("xsdc__double",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"));
		class2QNamemapC.put("xsdc__anyURI",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"));
		class2QNamemapC.put("xsdc__QName",					new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"));
		class2QNamemapC.put("xsdc__NOTATION",				new QName(WrapperConstants.SCHEMA_NAMESPACE, "NOTATION"));
		
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "duration"),				"xsd__duration");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"),				"xsd__dateTime");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"),					"xsd__time");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"),					"xsd__date");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYearMonth"),			"xsd__gYearMonth");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYear"),				"xsd__gYear");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonthDay"),			"xsd__gMonthDay");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gDay"),					"xsd__gDay");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonth"),				"xsd__gMonth");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"),				"xsd__string");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "normalizedString"),		"xsd__normalizedString");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "token"),				"xsd__token");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "language"),				"xsd__language");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "Name"),					"xsd__Name");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NCName"),				"xsd__NCName");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ID"),					"xsd__ID");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREF"),				"xsd__IDREF");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREFS"),				"xsd__IDREFS");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITY"),				"xsd__ENTITY");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITIES"),				"xsd__ENTITIES");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"),				"xsd__NMTOKEN");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKENS"),				"xsd__NMTOKENS");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"),				"xsd__boolean");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"),			"xsd__base64Binary");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"),			"xsd__hexBinary");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"),				"xsd__float");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"),				"xsd__decimal");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"),				"xsd__integer");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonPositiveInteger"),	"xsd__nonPositiveInteger");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "negativeInteger"),		"xsd__negativeInteger");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"),					"xsd__long");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"),					"xsd__int");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"),				"xsd__short");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"),					"xsd__byte");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonNegativeInteger"),	"xsd__nonNegativeInteger");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"),			"xsd__unsignedLong");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"),			"xsd__unsignedInt");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"),		"xsd__unsignedShort");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"),			"xsd__unsignedByte");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "positiveInteger"),		"xsd__positiveInteger");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"),				"xsd__double");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"),				"xsd__QName");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"),				"xsd__anyURI");
		qname2classmapCpp.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NOTATION"),				"xsd__NOTATION");
		
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "duration"),			"xsdc__duration");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "dateTime"),			"xsdc__dateTime");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "time"),				"xsdc__time");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "date"),				"xsdc__date");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYearMonth"),			"xsdc__gYearMonth");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gYear"),				"xsdc__gYear");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonthDay"),			"xsdc__gMonthDay");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gDay"),				"xsdc__gDay");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "gMonth"),				"xsdc__gMonth");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"),				"xsdc__string");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "normalizedString"),	"xsdc__normalizedString");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "token"),				"xsdc__token");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "language"),			"xsdc__language");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "Name"),				"xsdc__Name");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NCName"),				"xsdc__NCName");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ID"),					"xsdc__ID");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREF"),				"xsdc__IDREF");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "IDREFS"),				"xsdc__IDREFS");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITY"),				"xsdc__ENTITY");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "ENTITIES"),			"xsdc__ENTITIES");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"),			"xsdc__NMTOKEN");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKENS"),			"xsdc__NMTOKENS");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"),			"xsdc__boolean");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "base64Binary"),		"xsdc__base64Binary");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "hexBinary"),			"xsdc__hexBinary");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"),				"xsdc__float");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "decimal"),			"xsdc__decimal");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"),			"xsdc__integer");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonPositiveInteger"),	"xsdc__nonPositiveInteger");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "negativeInteger"),	"xsdc__negativeInteger");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"),				"xsdc__long");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"),				"xsdc__int");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"),				"xsdc__short");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"),				"xsdc__byte");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "nonNegativeInteger"),	"xsdc__nonNegativeInteger");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"),		"xsdc__unsignedLong");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"),		"xsdc__unsignedInt");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"),		"xsdc__unsignedShort");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"),		"xsdc__unsignedByte");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "positiveInteger"),	"xsdc__positiveInteger");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"),				"xsdc__double");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"),				"xsdc__QName");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"),				"xsdc__anyURI");
		qname2classmapC.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NOTATION"),			"xsdc__NOTATION");
		
		/* TODO:
		 *   Should be removed when the following issue will be fixed :
		 * 	-> http://marc.theaimsgroup.com/?t=107907748000002&r=1&w=2 
		 */
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"),			"xsd__int");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"),			"xsd__byte");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"),			"xsd__float");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"),			"xsd__long");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "integer"),		"xsd__integer");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"),			"xsd__double");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "char"),			"xsd__char");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"),			"xsd__short");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "string"),			"xsd__string");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "dateTime"),		"xsd__dateTime");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "date"),			"xsd__date");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "time"),			"xsd__time");
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "duration"),		"xsd__duration");
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
//		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "NCName"),			"xsd__NCName");		


		/* TODO:
		 *  Another strange issue from Axis 1.1 runtime when base64binary is in input/output operations.
		 */	
		qname2classmapCpp.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64"), "xsd__base64Binary");		
		
		/* TODO:
		 *   Should be removed when the following issue will be fixed :
		 * 	-> http://marc.theaimsgroup.com/?t=107907748000002&r=1&w=2 
		 */
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"),			"xsdc__int");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"),			"xsdc__byte");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"),			"xsdc__float");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"),			"xsdc__long");
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "integer"),		"xsdc__integer");
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
//		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "NCName"),			"xsdc__NCName");		


		/* TODO:
		 *  Another strange issue from Axis 1.1 runtime when base64binary is in input/output operations.
		 */	
		qname2classmapC.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64"), "xsdc__base64Binary");		
		
		type2getValueMethodNameCpp.put("xsd__duration",				"Duration");
		type2getValueMethodNameCpp.put("xsd__dateTime",				"DateTime");
		type2getValueMethodNameCpp.put("xsd__time",					"Time");
		type2getValueMethodNameCpp.put("xsd__date",					"Date");
		type2getValueMethodNameCpp.put("xsd__gYearMonth",			"GYearMonth");
		type2getValueMethodNameCpp.put("xsd__gYear",				"GYear");
		type2getValueMethodNameCpp.put("xsd__gMonthDay",			"GMonthDay");
		type2getValueMethodNameCpp.put("xsd__gDay",					"GDay");
		type2getValueMethodNameCpp.put("xsd__gMonth",				"GMonth");
		type2getValueMethodNameCpp.put("xsd__string",				"String");
		type2getValueMethodNameCpp.put("xsd__normalizedString",		"NormalizedString");
		type2getValueMethodNameCpp.put("xsd__token",				"Token");
		type2getValueMethodNameCpp.put("xsd__language",				"Language");
		type2getValueMethodNameCpp.put("xsd__Name",					"Name");
		type2getValueMethodNameCpp.put("xsd__NCName",				"NCName");
		type2getValueMethodNameCpp.put("xsd__ID",					"ID");
		type2getValueMethodNameCpp.put("xsd__IDREF",				"IDREF");
		type2getValueMethodNameCpp.put("xsd__IDREFS",				"IDREFS");
		type2getValueMethodNameCpp.put("xsd__ENTITY",				"ENTITY");
		type2getValueMethodNameCpp.put("xsd__ENTITIES",				"ENTITIES");
		type2getValueMethodNameCpp.put("xsd__NMTOKEN",				"NMTOKEN");
		type2getValueMethodNameCpp.put("xsd__NMTOKENS",				"NMTOKENS");
		type2getValueMethodNameCpp.put("xsd__boolean",				"Boolean");
		type2getValueMethodNameCpp.put("xsd__base64Binary",			"Base64Binary");
		type2getValueMethodNameCpp.put("xsd__hexBinary",			"HexBinary");
		type2getValueMethodNameCpp.put("xsd__float",				"Float");
		type2getValueMethodNameCpp.put("xsd__decimal",				"Decimal");
		type2getValueMethodNameCpp.put("xsd__integer",				"Integer");
		type2getValueMethodNameCpp.put("xsd__nonPositiveInteger", 	"NonPositiveInteger");
		type2getValueMethodNameCpp.put("xsd__negativeInteger",		"NegativeInteger");
		type2getValueMethodNameCpp.put("xsd__long",					"Long");
		type2getValueMethodNameCpp.put("xsd__int",					"Int");
		type2getValueMethodNameCpp.put("xsd__short",				"Short");
		type2getValueMethodNameCpp.put("xsd__byte",					"Byte");
		type2getValueMethodNameCpp.put("xsd__nonNegativeInteger",	"NonNegativeInteger");
		type2getValueMethodNameCpp.put("xsd__unsignedLong",			"UnsignedLong");
		type2getValueMethodNameCpp.put("xsd__unsignedInt",			"UnsignedInt");
		type2getValueMethodNameCpp.put("xsd__unsignedShort",		"UnsignedShort");
		type2getValueMethodNameCpp.put("xsd__unsignedByte",			"UnsignedByte");
		type2getValueMethodNameCpp.put("xsd__positiveInteger",		"PositiveInteger");
		type2getValueMethodNameCpp.put("xsd__double",				"Double");
		type2getValueMethodNameCpp.put("xsd__anyURI",				"AnyURI");
		type2getValueMethodNameCpp.put("xsd__QName",				"QName");
		type2getValueMethodNameCpp.put("xsd__NOTATION",				"NOTATION");
		
		type2getValueMethodNameC.put("xsdc__duration",				"Duration");
		type2getValueMethodNameC.put("xsdc__dateTime",				"DateTime");
		type2getValueMethodNameC.put("xsdc__time",					"Time");
		type2getValueMethodNameC.put("xsdc__date",					"Date");
		type2getValueMethodNameC.put("xsdc__gYearMonth",			"GYearMonth");
		type2getValueMethodNameC.put("xsdc__gYear",					"GYear");
		type2getValueMethodNameC.put("xsdc__gMonthDay",				"GMonthDay");
		type2getValueMethodNameC.put("xsdc__gDay",					"GDay");
		type2getValueMethodNameC.put("xsdc__gMonth",				"GMonth");
		type2getValueMethodNameC.put("xsdc__string",				"String");
		type2getValueMethodNameC.put("xsdc__normalizedString",		"NormalizedString");
		type2getValueMethodNameC.put("xsdc__token",					"Token");
		type2getValueMethodNameC.put("xsdc__language",				"Language");
		type2getValueMethodNameC.put("xsdc__Name",					"Name");
		type2getValueMethodNameC.put("xsdc__NCName",				"NCName");
		type2getValueMethodNameC.put("xsdc__ID",					"ID");
		type2getValueMethodNameC.put("xsdc__IDREF",					"IDREF");
		type2getValueMethodNameC.put("xsdc__IDREFS",				"IDREFS");
		type2getValueMethodNameC.put("xsdc__ENTITY",				"ENTITY");
		type2getValueMethodNameC.put("xsdc__ENTITIES",				"ENTITIES");
		type2getValueMethodNameC.put("xsdc__NMTOKEN",				"NMTOKEN");
		type2getValueMethodNameC.put("xsdc__NMTOKENS",				"NMTOKENS");
		type2getValueMethodNameC.put("xsdc__boolean",				"Boolean");
		type2getValueMethodNameC.put("xsdc__base64Binary",			"Base64Binary");
		type2getValueMethodNameC.put("xsdc__hexBinary",				"HexBinary");
		type2getValueMethodNameC.put("xsdc__float",					"Float");
		type2getValueMethodNameC.put("xsdc__decimal",				"Decimal");
		type2getValueMethodNameC.put("xsdc__integer",				"Integer");
		type2getValueMethodNameC.put("xsdc__nonPositiveInteger", 	"NonPositiveInteger");
		type2getValueMethodNameC.put("xsdc__negativeInteger",		"NegativeInteger");
		type2getValueMethodNameC.put("xsdc__long",					"Long");
		type2getValueMethodNameC.put("xsdc__int",					"Int");
		type2getValueMethodNameC.put("xsdc__short",					"Short");
		type2getValueMethodNameC.put("xsdc__byte",					"Byte");
		type2getValueMethodNameC.put("xsdc__nonNegativeInteger",	"NonNegativeInteger");
		type2getValueMethodNameC.put("xsdc__unsignedLong",			"UnsignedLong");
		type2getValueMethodNameC.put("xsdc__unsignedInt",			"UnsignedInt");
		type2getValueMethodNameC.put("xsdc__unsignedShort",			"UnsignedShort");
		type2getValueMethodNameC.put("xsdc__unsignedByte",			"UnsignedByte");
		type2getValueMethodNameC.put("xsdc__positiveInteger",		"PositiveInteger");
		type2getValueMethodNameC.put("xsdc__double",				"Double");
		type2getValueMethodNameC.put("xsdc__anyURI",				"AnyURI");
		type2getValueMethodNameC.put("xsdc__QName",					"QName");
		type2getValueMethodNameC.put("xsdc__NOTATION",				"NOTATION");
		
		
		type2BasicArrayNameCpp.put("xsd__duration",				"xsd__duration_Array");
		type2BasicArrayNameCpp.put("xsd__dateTime",				"xsd__dateTime_Array");
		type2BasicArrayNameCpp.put("xsd__time",					"xsd__time_Array");
		type2BasicArrayNameCpp.put("xsd__date",					"xsd__date_Array");
		type2BasicArrayNameCpp.put("xsd__gYearMonth",			"xsd__gYearMonth_Array");
		type2BasicArrayNameCpp.put("xsd__gYear",				"xsd__gYear_Array");
		type2BasicArrayNameCpp.put("xsd__gMonthDay",			"xsd__gMonthDay_Array");
		type2BasicArrayNameCpp.put("xsd__gDay",					"xsd__gDay_Array");
		type2BasicArrayNameCpp.put("xsd__gMonth",				"xsd__gMonth_Array");
		type2BasicArrayNameCpp.put("xsd__string",				"xsd__string_Array");
		type2BasicArrayNameCpp.put("xsd__normalizedString",		"xsd__normalizedString_Array");
		type2BasicArrayNameCpp.put("xsd__token",				"xsd__token_Array");
		type2BasicArrayNameCpp.put("xsd__language",				"xsd__language_Array");
		type2BasicArrayNameCpp.put("xsd__Name",					"xsd__Name_Array");
		type2BasicArrayNameCpp.put("xsd__NCName",				"xsd__NCName_Array");
		type2BasicArrayNameCpp.put("xsd__ID",					"xsd__ID_Array");
		type2BasicArrayNameCpp.put("xsd__IDREF",				"xsd__IDREF_Array");
		type2BasicArrayNameCpp.put("xsd__IDREFS",				"xsd__IDREFS_Array");
		type2BasicArrayNameCpp.put("xsd__ENTITY",				"xsd__ENTITY_Array");
		type2BasicArrayNameCpp.put("xsd__ENTITIES",				"xsd__ENTITIES_Array");
		type2BasicArrayNameCpp.put("xsd__NMTOKEN",				"xsd__NMTOKEN_Array");
		type2BasicArrayNameCpp.put("xsd__NMTOKENS",				"xsd__NMTOKENS_Array");
		type2BasicArrayNameCpp.put("xsd__boolean",				"xsd__boolean_Array");
		type2BasicArrayNameCpp.put("xsd__base64Binary",			"xsd__base64Binary_Array");
		type2BasicArrayNameCpp.put("xsd__hexBinary",			"xsd__hexBinary_Array");
		type2BasicArrayNameCpp.put("xsd__float",				"xsd__float_Array");
		type2BasicArrayNameCpp.put("xsd__decimal",				"xsd__decimal_Array");
		type2BasicArrayNameCpp.put("xsd__integer",				"xsd__integer_Array");
		type2BasicArrayNameCpp.put("xsd__nonPositiveInteger",	"xsd__nonPositiveInteger_Array");
		type2BasicArrayNameCpp.put("xsd__negativeInteger",		"xsd__negativeInteger_Array");
		type2BasicArrayNameCpp.put("xsd__long",					"xsd__long_Array");
		type2BasicArrayNameCpp.put("xsd__int",					"xsd__int_Array");
		type2BasicArrayNameCpp.put("xsd__short",				"xsd__short_Array");
		type2BasicArrayNameCpp.put("xsd__byte",					"xsd__byte_Array");
		type2BasicArrayNameCpp.put("xsd__nonNegativeInteger",	"xsd__nonNegativeInteger_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedLong",			"xsd__unsignedLong_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedInt",			"xsd__unsignedInt_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedShort",		"xsd__unsignedShort_Array");
		type2BasicArrayNameCpp.put("xsd__unsignedByte",			"xsd__unsignedByte_Array");
		type2BasicArrayNameCpp.put("xsd__positiveInteger",		"xsd__positiveInteger_Array");
		type2BasicArrayNameCpp.put("xsd__double",				"xsd__double_Array");
		type2BasicArrayNameCpp.put("xsd__anyURI",				"xsd__anyURI_Array");
		type2BasicArrayNameCpp.put("xsd__QName",				"xsd__QName_Array");
		type2BasicArrayNameCpp.put("xsd__NOTATION",				"xsd__NOTATION_Array");
		
		type2BasicArrayNameC.put("xsdc__duration",				"xsdc__duration_Array");
		type2BasicArrayNameC.put("xsdc__dateTime",				"xsdc__dateTime_Array");
		type2BasicArrayNameC.put("xsdc__time",					"xsdc__time_Array");
		type2BasicArrayNameC.put("xsdc__date",					"xsdc__date_Array");
		type2BasicArrayNameC.put("xsdc__gYearMonth",			"xsdc__gYearMonth_Array");
		type2BasicArrayNameC.put("xsdc__gYear",					"xsdc__gYear_Array");
		type2BasicArrayNameC.put("xsdc__gMonthDay",				"xsdc__gMonthDay_Array");
		type2BasicArrayNameC.put("xsdc__gDay",					"xsdc__gDay_Array");
		type2BasicArrayNameC.put("xsdc__gMonth",				"xsdc__gMonth_Array");
		type2BasicArrayNameC.put("xsdc__string",				"xsdc__string_Array");
		type2BasicArrayNameC.put("xsdc__normalizedString",		"xsdc__normalizedString_Array");
		type2BasicArrayNameC.put("xsdc__token",					"xsdc__token_Array");
		type2BasicArrayNameC.put("xsdc__language",				"xsdc__language_Array");
		type2BasicArrayNameC.put("xsdc__Name",					"xsdc__Name_Array");
		type2BasicArrayNameC.put("xsdc__NCName",				"xsdc__NCName_Array");
		type2BasicArrayNameC.put("xsdc__ID",					"xsdc__ID_Array");
		type2BasicArrayNameC.put("xsdc__IDREF",					"xsdc__IDREF_Array");
		type2BasicArrayNameC.put("xsdc__IDREFS",				"xsdc__IDREFS_Array");
		type2BasicArrayNameC.put("xsdc__ENTITY",				"xsdc__ENTITY_Array");
		type2BasicArrayNameC.put("xsdc__ENTITIES",				"xsdc__ENTITIES_Array");
		type2BasicArrayNameC.put("xsdc__NMTOKEN",				"xsdc__NMTOKEN_Array");
		type2BasicArrayNameC.put("xsdc__NMTOKENS",				"xsdc__NMTOKENS_Array");
		type2BasicArrayNameC.put("xsdc__boolean",				"xsdc__boolean_Array");
		type2BasicArrayNameC.put("xsdc__base64Binary",			"xsdc__base64Binary_Array");
		type2BasicArrayNameC.put("xsdc__hexBinary",				"xsdc__hexBinary_Array");
		type2BasicArrayNameC.put("xsdc__float",					"xsdc__float_Array");
		type2BasicArrayNameC.put("xsdc__decimal",				"xsdc__decimal_Array");
		type2BasicArrayNameC.put("xsdc__integer",				"xsdc__integer_Array");
		type2BasicArrayNameC.put("xsdc__nonPositiveInteger",	"xsdc__nonPositiveInteger_Array");
		type2BasicArrayNameC.put("xsdc__negativeInteger",		"xsdc__negativeInteger_Array");
		type2BasicArrayNameC.put("xsdc__long",					"xsdc__long_Array");
		type2BasicArrayNameC.put("xsdc__int",					"xsdc__int_Array");
		type2BasicArrayNameC.put("xsdc__short",					"xsdc__short_Array");
		type2BasicArrayNameC.put("xsdc__byte",					"xsdc__byte_Array");
		type2BasicArrayNameC.put("xsdc__nonNegativeInteger",	"xsdc__nonNegativeInteger_Array");
		type2BasicArrayNameC.put("xsdc__unsignedLong",			"xsdc__unsignedLong_Array");
		type2BasicArrayNameC.put("xsdc__unsignedInt",			"xsdc__unsignedInt_Array");
		type2BasicArrayNameC.put("xsdc__unsignedShort",			"xsdc__unsignedShort_Array");
		type2BasicArrayNameC.put("xsdc__unsignedByte",			"xsdc__unsignedByte_Array");
		type2BasicArrayNameC.put("xsdc__positiveInteger",		"xsdc__positiveInteger_Array");
		type2BasicArrayNameC.put("xsdc__double",				"xsdc__double_Array");
		type2BasicArrayNameC.put("xsdc__anyURI",				"xsdc__anyURI_Array");
		type2BasicArrayNameC.put("xsdc__QName",					"xsdc__QName_Array");
		type2BasicArrayNameC.put("xsdc__NOTATION",				"xsdc__NOTATION_Array");
		
		basicType2EnumMapCpp.put("xsd__duration",			"XSD_DURATION");
		basicType2EnumMapCpp.put("xsd__dateTime",			"XSD_DATETIME");
		basicType2EnumMapCpp.put("xsd__time",				"XSD_TIME");
		basicType2EnumMapCpp.put("xsd__date",				"XSD_DATE");
		basicType2EnumMapCpp.put("xsd__gYearMonth",			"XSD_GYEARMONTH");
		basicType2EnumMapCpp.put("xsd__gYear",				"XSD_GYEAR");
		basicType2EnumMapCpp.put("xsd__gMonthDay",			"XSD_GMONTHDAY");
		basicType2EnumMapCpp.put("xsd__gDay",				"XSD_GDAY");
		basicType2EnumMapCpp.put("xsd__gMonth",				"XSD_GMONTH");
		basicType2EnumMapCpp.put("xsd__string",				"XSD_STRING");
		basicType2EnumMapCpp.put("xsd__normalizedString",	"XSD_NORMALIZEDSTRING");
		basicType2EnumMapCpp.put("xsd__token",				"XSD_TOKEN");
		basicType2EnumMapCpp.put("xsd__language",			"XSD_LANGUAGE");
		basicType2EnumMapCpp.put("xsd__Name",				"XSD_NAME");
		basicType2EnumMapCpp.put("xsd__NCName",				"XSD_NCNAME");
		basicType2EnumMapCpp.put("xsd__ID",					"XSD_ID");
		basicType2EnumMapCpp.put("xsd__IDREF",				"XSD_IDREF");
		basicType2EnumMapCpp.put("xsd__IDREFS",				"XSD_IDREFS");
		basicType2EnumMapCpp.put("xsd__ENTITY",				"XSD_ENTITY");
		basicType2EnumMapCpp.put("xsd__ENTITIES",			"XSD_ENTITIES");
		basicType2EnumMapCpp.put("xsd__NMTOKEN",			"XSD_NMTOKEN");
		basicType2EnumMapCpp.put("xsd__NMTOKENS",			"XSD_NMTOKENS");
		basicType2EnumMapCpp.put("xsd__boolean",			"XSD_BOOLEAN");
		basicType2EnumMapCpp.put("xsd__base64Binary",		"XSD_BASE64BINARY");
		basicType2EnumMapCpp.put("xsd__hexBinary",			"XSD_HEXBINARY");
		basicType2EnumMapCpp.put("xsd__float",				"XSD_FLOAT");
		basicType2EnumMapCpp.put("xsd__decimal",			"XSD_DECIMAL");
		basicType2EnumMapCpp.put("xsd__integer",			"XSD_INTEGER");
		basicType2EnumMapCpp.put("xsd__nonPositiveInteger",	"XSD_NONPOSITIVEINTEGER");
		basicType2EnumMapCpp.put("xsd__negativeInteger",	"XSD_NEGATIVEINTEGER");
		basicType2EnumMapCpp.put("xsd__long",				"XSD_LONG");
		basicType2EnumMapCpp.put("xsd__int",				"XSD_INT");
		basicType2EnumMapCpp.put("xsd__short",				"XSD_SHORT");
		basicType2EnumMapCpp.put("xsd__byte",				"XSD_BYTE");
		basicType2EnumMapCpp.put("xsd__nonNegativeInteger",	"XSD_NONNEGATIVEINTEGER");
		basicType2EnumMapCpp.put("xsd__unsignedLong",		"XSD_UNSIGNEDLONG");
		basicType2EnumMapCpp.put("xsd__unsignedInt",		"XSD_UNSIGNEDINT");
		basicType2EnumMapCpp.put("xsd__unsignedShort",		"XSD_UNSIGNEDSHORT");
		basicType2EnumMapCpp.put("xsd__unsignedByte",		"XSD_UNSIGNEDBYTE");
		basicType2EnumMapCpp.put("xsd__positiveInteger",		"XSD_POSITIVEINTEGER");
		basicType2EnumMapCpp.put("xsd__double",				"XSD_DOUBLE");
		basicType2EnumMapCpp.put("xsd__anyURI",				"XSD_ANYURI");
		basicType2EnumMapCpp.put("xsd__QName",				"XSD_QNAME");
		basicType2EnumMapCpp.put("xsd__NOTATION",			"XSD_NOTATION");

		basicType2EnumMapC.put("xsdc__duration",			"XSD_DURATION");
		basicType2EnumMapC.put("xsdc__dateTime",			"XSD_DATETIME");
		basicType2EnumMapC.put("xsdc__time",				"XSD_TIME");
		basicType2EnumMapC.put("xsdc__date",				"XSD_DATE");
		basicType2EnumMapC.put("xsdc__gYearMonth",			"XSD_GYEARMONTH");
		basicType2EnumMapC.put("xsdc__gYear",				"XSD_GYEAR");
		basicType2EnumMapC.put("xsdc__gMonthDay",			"XSD_GMONTHDAY");
		basicType2EnumMapC.put("xsdc__gDay",				"XSD_GDAY");
		basicType2EnumMapC.put("xsdc__gMonth",				"XSD_GMONTH");
		basicType2EnumMapC.put("xsdc__string",				"XSD_STRING");
		basicType2EnumMapC.put("xsdc__normalizedString",	"XSD_NORMALIZEDSTRING");
		basicType2EnumMapC.put("xsdc__token",				"XSD_TOKEN");
		basicType2EnumMapC.put("xsdc__language",			"XSD_LANGUAGE");
		basicType2EnumMapC.put("xsdc__Name",				"XSD_NAME");
		basicType2EnumMapC.put("xsdc__NCName",				"XSD_NCNAME");
		basicType2EnumMapC.put("xsdc__ID",					"XSD_ID");
		basicType2EnumMapC.put("xsdc__IDREF",				"XSD_IDREF");
		basicType2EnumMapC.put("xsdc__IDREFS",				"XSD_IDREFS");
		basicType2EnumMapC.put("xsdc__ENTITY",				"XSD_ENTITY");
		basicType2EnumMapC.put("xsdc__ENTITIES",			"XSD_ENTITIES");
		basicType2EnumMapC.put("xsdc__NMTOKEN",				"XSD_NMTOKEN");
		basicType2EnumMapC.put("xsdc__NMTOKENS",			"XSD_NMTOKENS");
		basicType2EnumMapC.put("xsdc__boolean",				"XSD_BOOLEAN");
		basicType2EnumMapC.put("xsdc__base64Binary",		"XSD_BASE64BINARY");
		basicType2EnumMapC.put("xsdc__hexBinary",			"XSD_HEXBINARY");
		basicType2EnumMapC.put("xsdc__float",				"XSD_FLOAT");
		basicType2EnumMapC.put("xsdc__decimal",				"XSD_DECIMAL");
		basicType2EnumMapC.put("xsdc__integer",				"XSD_INTEGER");
		basicType2EnumMapC.put("xsdc__nonPositiveInteger",	"XSD_NONPOSITIVEINTEGER");
		basicType2EnumMapC.put("xsdc__negativeInteger",		"XSD_NEGATIVEINTEGER");
		basicType2EnumMapC.put("xsdc__long",				"XSD_LONG");
		basicType2EnumMapC.put("xsdc__int",					"XSD_INT");
		basicType2EnumMapC.put("xsdc__short",				"XSD_SHORT");
		basicType2EnumMapC.put("xsdc__byte",				"XSD_BYTE");
		basicType2EnumMapC.put("xsdc__nonNegativeInteger",	"XSD_NONNEGATIVEINTEGER");
		basicType2EnumMapC.put("xsdc__unsignedLong",		"XSD_UNSIGNEDLONG");
		basicType2EnumMapC.put("xsdc__unsignedInt",			"XSD_UNSIGNEDINT");
		basicType2EnumMapC.put("xsdc__unsignedShort",		"XSD_UNSIGNEDSHORT");
		basicType2EnumMapC.put("xsdc__unsignedByte",		"XSD_UNSIGNEDBYTE");
		basicType2EnumMapC.put("xsdc__positiveInteger",		"XSD_POSITIVEINTEGER");
		basicType2EnumMapC.put("xsdc__double",				"XSD_DOUBLE");
		basicType2EnumMapC.put("xsdc__anyURI",				"XSD_ANYURI");
		basicType2EnumMapC.put("xsdc__QName",				"XSD_QNAME");
		basicType2EnumMapC.put("xsdc__NOTATION",			"XSD_NOTATION");


		initValuesCpp.put("xsd__duration",				"0");
		initValuesCpp.put("xsd__dateTime",				"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__time",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__date",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__gYearMonth",			"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__gYear",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__gMonthDay",				"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__gDay",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__gMonth",				"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesCpp.put("xsd__string",				"NULL");
		initValuesCpp.put("xsd__normalizedString",		"NULL");
		initValuesCpp.put("xsd__token",					"NULL");
		initValuesCpp.put("xsd__language",				"NULL");
		initValuesCpp.put("xsd__Name",					"NULL");
		initValuesCpp.put("xsd__NCName",				"NULL");
		initValuesCpp.put("xsd__ID",					"NULL");
		initValuesCpp.put("xsd__IDREF",					"NULL");
		initValuesCpp.put("xsd__IDREFS",				"NULL");
		initValuesCpp.put("xsd__ENTITY",				"NULL");
		initValuesCpp.put("xsd__ENTITIES",				"NULL");
		initValuesCpp.put("xsd__NMTOKEN",				"NULL");
		initValuesCpp.put("xsd__NMTOKENS",				"NULL");
		initValuesCpp.put("xsd__boolean",				"false_");
//		initValuesCpp.put("xsd__base64Binary",			""); // This is a class, so doesn't need to be initialized.
//		initValuesCpp.put("xsd__hexBinary",				""); // This is a class, so doesn't need to be initialized.
		initValuesCpp.put("xsd__float",					"0.0");
		initValuesCpp.put("xsd__decimal",				"0.0");
		initValuesCpp.put("xsd__integer",				"0");
		initValuesCpp.put("xsd__nonPositiveInteger",	"0");
		initValuesCpp.put("xsd__negativeInteger",		"0");
		initValuesCpp.put("xsd__long",					"0");
		initValuesCpp.put("xsd__int",					"0");
		initValuesCpp.put("xsd__short",					"0");
		initValuesCpp.put("xsd__byte",					"0");
		initValuesCpp.put("xsd__nonNegativeInteger",	"0");
		initValuesCpp.put("xsd__unsignedByte",			"0");
		initValuesCpp.put("xsd__unsignedInt",			"0");
		initValuesCpp.put("xsd__unsignedLong",			"0");
		initValuesCpp.put("xsd__unsignedShort",			"0");
		initValuesCpp.put("xsd__positiveInteger",		"0");
		initValuesCpp.put("xsd__double",				"0.0");
		initValuesCpp.put("xsd__anyURI",				"NULL");
		initValuesCpp.put("xsd__QName",					"NULL");
		initValuesCpp.put("xsd__NOTATION",				"NULL");
 
		
		initValuesC.put("xsdc__duration",				"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__dateTime",				"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__time",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__date",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__gYearMonth",				"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__gYear",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__gMonthDay",				"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__gDay",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__gMonth",					"{0, 0, 0, 0, 0, 0, 0, 0, 0}");
		initValuesC.put("xsdc__string",					"NULL");
		initValuesC.put("xsdc__normalizedString",		"NULL");
		initValuesC.put("xsdc__token",					"NULL");
		initValuesC.put("xsdc__language",				"NULL");
		initValuesC.put("xsdc__Name",					"NULL");
		initValuesC.put("xsdc__NCName",					"NULL");
		initValuesC.put("xsdc__ID",						"NULL");
		initValuesC.put("xsdc__IDREF",					"NULL");
		initValuesC.put("xsdc__IDREFS",					"NULL");
		initValuesC.put("xsdc__ENTITY",					"NULL");
		initValuesC.put("xsdc__ENTITIES",				"NULL");
		initValuesC.put("xsdc__NMTOKEN",				"NULL");
		initValuesC.put("xsdc__NMTOKENS",				"NULL");
		initValuesC.put("xsdc__boolean",				"false_");
		initValuesC.put("xsdc__base64Binary",			"{NULL, 0}");
		initValuesC.put("xsdc__hexBinary",				"{NULL, 0}");
		initValuesC.put("xsdc__float",					"0.0");
		initValuesC.put("xsdc__decimal",				"0.0");
		initValuesC.put("xsdc__integer",				"0");
		initValuesC.put("xsdc__nonPositiveInteger",		"0");
		initValuesC.put("xsdc__negativeInteger",		"0");
		initValuesC.put("xsdc__long",					"0");
		initValuesC.put("xsdc__int",					"0");
		initValuesC.put("xsdc__short",					"0");
		initValuesC.put("xsdc__byte",					"0");
		initValuesC.put("xsdc__nonNegativeInteger",		"0");
		initValuesC.put("xsdc__unsignedByte",			"0");
		initValuesC.put("xsdc__unsignedInt",			"0");
		initValuesC.put("xsdc__unsignedLong",			"0");
		initValuesC.put("xsdc__unsignedShort",			"0");
		initValuesC.put("xsdc__positiveInteger",		"0");
		initValuesC.put("xsdc__double",					"0.0");
		initValuesC.put("xsdc__anyURI",					"NULL");
		initValuesC.put("xsdc__QName",					"NULL");
		initValuesC.put("xsdc__NOTATION",				"NULL");
		
		isPointerBasedType.put("xsd__duration", new Boolean(false));
		isPointerBasedType.put("xsd__dateTime", new Boolean(false));
		isPointerBasedType.put("xsd__time", new Boolean(false));
		isPointerBasedType.put("xsd__date", new Boolean(false));
		isPointerBasedType.put("xsd__gYearMonth", new Boolean(false));
		isPointerBasedType.put("xsd__gYear", new Boolean(false));
		isPointerBasedType.put("xsd__gMonthDay", new Boolean(false));
		isPointerBasedType.put("xsd__gDay", new Boolean(false));
		isPointerBasedType.put("xsd__gMonth", new Boolean(false));
		isPointerBasedType.put("xsd__string", new Boolean(true));
		isPointerBasedType.put("xsd__normalizedString", new Boolean(true));
		isPointerBasedType.put("xsd__token", new Boolean(true));
		isPointerBasedType.put("xsd__language", new Boolean(true));
		isPointerBasedType.put("xsd__Name", new Boolean(true));
		isPointerBasedType.put("xsd__NCName", new Boolean(true));
		isPointerBasedType.put("xsd__ID", new Boolean(true));
		isPointerBasedType.put("xsd__IDREF", new Boolean(true));
		isPointerBasedType.put("xsd__IDREFS", new Boolean(true));
		isPointerBasedType.put("xsd__ENTITY", new Boolean(true));
		isPointerBasedType.put("xsd__ENTITIES", new Boolean(true));
		isPointerBasedType.put("xsd__NMTOKEN", new Boolean(true));
		isPointerBasedType.put("xsd__NMTOKENS", new Boolean(true));
		isPointerBasedType.put("xsd__boolean", new Boolean(false));
		isPointerBasedType.put("xsd__base64Binary", new Boolean(false));
		isPointerBasedType.put("xsd__hexBinary", new Boolean(false));
		isPointerBasedType.put("xsd__float", new Boolean(false));
		isPointerBasedType.put("xsd__decimal", new Boolean(false));
		isPointerBasedType.put("xsd__integer", new Boolean(false));
		isPointerBasedType.put("xsd__nonPositiveInteger", new Boolean(false));
		isPointerBasedType.put("xsd__negativeInteger", new Boolean(false));
		isPointerBasedType.put("xsd__long", new Boolean(false));
		isPointerBasedType.put("xsd__int", new Boolean(false));
		isPointerBasedType.put("xsd__short", new Boolean(false));
		isPointerBasedType.put("xsd__byte", new Boolean(false));
		isPointerBasedType.put("xsd__nonNegativeInteger", new Boolean(false));
		isPointerBasedType.put("xsd__unsignedLong", new Boolean(false));
		isPointerBasedType.put("xsd__unsignedInt", new Boolean(false));
		isPointerBasedType.put("xsd__unsignedShort", new Boolean(false));
		isPointerBasedType.put("xsd__unsignedByte", new Boolean(false));
		isPointerBasedType.put("xsd__positiveInteger", new Boolean(false));
		isPointerBasedType.put("xsd__double", new Boolean(false));
		isPointerBasedType.put("xsd__anyURI", new Boolean(true));
		isPointerBasedType.put("xsd__QName", new Boolean(true));
		isPointerBasedType.put("xsd__NOTATION", new Boolean(true));

		isPointerBasedType.put("xsdc__duration", new Boolean(false));
		isPointerBasedType.put("xsdc__dateTime", new Boolean(false));
		isPointerBasedType.put("xsdc__time", new Boolean(false));
		isPointerBasedType.put("xsdc__date", new Boolean(false));
		isPointerBasedType.put("xsdc__gYearMonth", new Boolean(false));
		isPointerBasedType.put("xsdc__gYear", new Boolean(false));
		isPointerBasedType.put("xsdc__gMonthDay", new Boolean(false));
		isPointerBasedType.put("xsdc__gDay", new Boolean(false));
		isPointerBasedType.put("xsdc__gMonth", new Boolean(false));
		isPointerBasedType.put("xsdc__string", new Boolean(true));
		isPointerBasedType.put("xsdc__normalizedString", new Boolean(true));
		isPointerBasedType.put("xsdc__token", new Boolean(true));
		isPointerBasedType.put("xsdc__language", new Boolean(true));
		isPointerBasedType.put("xsdc__Name", new Boolean(true));
		isPointerBasedType.put("xsdc__NCName", new Boolean(true));
		isPointerBasedType.put("xsdc__ID", new Boolean(true));
		isPointerBasedType.put("xsdc__IDREF", new Boolean(true));
		isPointerBasedType.put("xsdc__IDREF", new Boolean(true));
		isPointerBasedType.put("xsdc__IDREFS", new Boolean(true));
		isPointerBasedType.put("xsdc__ENTITY", new Boolean(true));
		isPointerBasedType.put("xsdc__ENTITIES", new Boolean(true));
		isPointerBasedType.put("xsdc__NMTOKEN", new Boolean(true));
		isPointerBasedType.put("xsdc__NMTOKENS", new Boolean(true));
		isPointerBasedType.put("xsdc__boolean", new Boolean(false));
		isPointerBasedType.put("xsdc__base64Binary", new Boolean(false));
		isPointerBasedType.put("xsdc__hexBinary", new Boolean(false));
		isPointerBasedType.put("xsdc__float", new Boolean(false));
		isPointerBasedType.put("xsdc__decimal", new Boolean(false));
		isPointerBasedType.put("xsdc__integer", new Boolean(false));
		isPointerBasedType.put("xsdc__nonPositiveInteger", new Boolean(false));
		isPointerBasedType.put("xsdc__negativeInteger", new Boolean(false));
		isPointerBasedType.put("xsdc__long", new Boolean(false));
		isPointerBasedType.put("xsdc__int", new Boolean(false));
		isPointerBasedType.put("xsdc__short", new Boolean(false));
		isPointerBasedType.put("xsdc__byte", new Boolean(false));
		isPointerBasedType.put("xsdc__nonNegativeInteger", new Boolean(false));
		isPointerBasedType.put("xsdc__unsignedLong", new Boolean(false));
		isPointerBasedType.put("xsdc__unsignedInt", new Boolean(false));
		isPointerBasedType.put("xsdc__unsignedShort", new Boolean(false));
		isPointerBasedType.put("xsdc__unsignedByte", new Boolean(false));
		isPointerBasedType.put("xsdc__positiveInteger", new Boolean(false));
		isPointerBasedType.put("xsdc__double", new Boolean(false));
		isPointerBasedType.put("xsdc__anyURI", new Boolean(true));
		isPointerBasedType.put("xsdc__QName", new Boolean(true));
		isPointerBasedType.put("xsdc__NOTATION", new Boolean(true));
	
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
	public static boolean isPointerType(String name)
	{
		return ((Boolean) isPointerBasedType.get(name)).booleanValue();
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
	
    public static String sanitiseClassName( String name)
    {
        String sanitisedName = name;

        for( int iRSLCount = 0; iRSLCount < VALID_XML_INVALID_C.length(); iRSLCount++)
        {
            int		iOffset;
            String	sChar = VALID_XML_INVALID_C.substring( iRSLCount, iRSLCount + 1);
            
            while( (iOffset = sanitisedName.indexOf( sChar)) != -1)
            {
                String	sBefore = sanitisedName.substring( 0, iOffset);
                String	sAfter = sanitisedName.substring( iOffset + 1);
                sanitisedName = sBefore + "_" + sAfter; 
            }
        }
        
        //System.out.println("name=" + name + " sanitisedName=" + sanitisedName);
        
        return sanitisedName;
    }

    public static String sanitiseAttributeName( String classname, String name)
    {
        String sanitisedName = sanitiseClassName( name);

        if( classname.equals( sanitisedName))
        {
            sanitisedName += "_";
        }
        
        return sanitisedName;
    }
}
