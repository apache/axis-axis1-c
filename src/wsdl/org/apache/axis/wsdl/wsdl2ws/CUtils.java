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

	/* This type mapping only maps simple types the mapping for
	   complex types are done with in the type class */
	private static Hashtable class2QNamemap = new Hashtable();
	private static Hashtable qname2classmap = new Hashtable();
	private static Hashtable schemaDefinedSimpleTypesMap = new Hashtable();
	private static Hashtable type2getValueMethodName = new Hashtable();
	private static Hashtable type2BasicArrayName = new Hashtable();
	private static Hashtable basicType2EnumMap = new Hashtable();
	
	static{	
		class2QNamemap.put("int", new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"));
		class2QNamemap.put("unsigned char", new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"));
		class2QNamemap.put("float", new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"));
		class2QNamemap.put("long", new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"));
		class2QNamemap.put("long", new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"));
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
		class2QNamemap.put("xsd__anyURI", new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"));
		class2QNamemap.put("xsd__unsignedByte", new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"));
		class2QNamemap.put("xsd__unsignedInt", new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"));
		class2QNamemap.put("xsd__unsignedLong", new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"));
		class2QNamemap.put("xsd__unsignedShort", new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"));
		class2QNamemap.put("xsd__QName", new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"));
		class2QNamemap.put("xsd__NMTOKEN", new QName(WrapperConstants.SCHEMA_NAMESPACE,"NMTOKEN"));
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"), "int");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"), "unsigned char");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"), "float");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"), "long");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "integer"), "long");
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
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "anyURI"), "xsd__anyURI");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedByte"), "xsd__unsignedByte");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedInt"), "xsd__unsignedInt");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedLong"), "xsd__unsignedLong");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "unsignedShort"), "xsd__unsignedShort");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "QName"), "xsd__QName");
		qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "NMTOKEN"), "xsd__NMTOKEN");
		
		/* TODO:
		 *   Should be removed when the following issue will be fixed :
		 * 	-> http://marc.theaimsgroup.com/?t=107907748000002&r=1&w=2 
		 */
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "int"), "int");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "byte"), "unsigned char");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "float"), "float");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "long"), "long");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "integer"), "long");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "double"), "double");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "char"), "char");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "short"), "short");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "string"), "xsd__string");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "dateTime"), "xsd__dateTime");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "date"), "xsd__date");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "time"), "xsd__time");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64Binary"), "xsd__base64Binary");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "hexBinary"), "xsd__hexBinary");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "decimal"), "xsd__decimal");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "boolean"), "xsd__boolean");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "anyURI"), "xsd__anyURI");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedByte"), "xsd__unsignedByte");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedInt"), "xsd__unsignedInt");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedLong"), "xsd__unsignedLong");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "unsignedShort"), "xsd__unsignedShort");
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "QName"), "xsd__QName");		


		/* TODO:
		 *  Another strange issue from Axis 1.1 runtime when base64binary is in input/output operations.
		 */	
		qname2classmap.put(new QName(WrapperConstants.SOAPENC_NAMESPACE, "base64"), "xsd__base64Binary");		
		
		type2getValueMethodName.put("int","Int");
		type2getValueMethodName.put("float","Float");
		type2getValueMethodName.put("xsd__string","String");
		type2getValueMethodName.put("long","Long");
		type2getValueMethodName.put("short","Short");
		type2getValueMethodName.put("char","Char");
		type2getValueMethodName.put("double","Double");
		type2getValueMethodName.put("unsigned char","Byte");			
		type2getValueMethodName.put("xsd__unsignedLong","UnsignedLong");
		type2getValueMethodName.put("xsd__unsignedInt","UnsignedInt");
		type2getValueMethodName.put("xsd__unsignedShort","UnsignedShort");
		type2getValueMethodName.put("xsd__unsignedByte","UnsignedChar");
		type2getValueMethodName.put("xsd__dateTime","DateTime");
		type2getValueMethodName.put("xsd__date","Date");
		type2getValueMethodName.put("xsd__time","Time");
		type2getValueMethodName.put("xsd__base64Binary","Base64Binary");
		type2getValueMethodName.put("xsd__hexBinary","HexBinary");
		type2getValueMethodName.put("xsd__decimal","Decimal");
		type2getValueMethodName.put("xsd__boolean","Boolean");
		type2getValueMethodName.put("xsd__anyURI","String");
		type2getValueMethodName.put("xsd__QName","String");
		type2getValueMethodName.put("xsd__NMTOKEN","String");
		type2BasicArrayName.put("int","xsd__int_Array");
		type2BasicArrayName.put("float","xsd__float_Array");
		type2BasicArrayName.put("xsd__string","xsd__string_Array");
		type2BasicArrayName.put("long","xsd__long_Array");
		type2BasicArrayName.put("short","xsd__short_Array");
		type2BasicArrayName.put("char","xsd__byte_Array");
		type2BasicArrayName.put("double","xsd__double_Array");
		type2BasicArrayName.put("xsd__unsignedLong","xsd__unsignedLong_Array");
		type2BasicArrayName.put("xsd__unsignedInt","xsd__unsignedInt_Array");
		type2BasicArrayName.put("xsd__unsignedShort","xsd__unsignedShort_Array");
		type2BasicArrayName.put("xsd__unsignedByte","xsd__unsignedByte_Array");
		type2BasicArrayName.put("xsd__dateTime","xsd__dateTime_Array");
		type2BasicArrayName.put("xsd__date","xsd__date_Array");
		type2BasicArrayName.put("xsd__time","xsd__time_Array");
		type2BasicArrayName.put("xsd__base64Binary","xsd__base64Binary_Array");
		type2BasicArrayName.put("xsd__hexBinary","xsd__hexBinary_Array");
		type2BasicArrayName.put("xsd__decimal","xsd__decimal_Array");
		type2BasicArrayName.put("xsd__boolean","xsd__boolean_Array");
		type2BasicArrayName.put("xsd__anyURI","xsd__anyURI_Array");
		type2BasicArrayName.put("xsd__QName","xsd__QName_Array");
		type2BasicArrayName.put("xsd__NMTOKEN","xsd__NMTOKEN_Array");
		basicType2EnumMap.put("int","XSD_INT");
		basicType2EnumMap.put("float","XSD_FLOAT");
		basicType2EnumMap.put("xsd__string","XSD_STRING");
		basicType2EnumMap.put("long","XSD_LONG");
		basicType2EnumMap.put("short","XSD_SHORT");
		basicType2EnumMap.put("unsigned char","XSD_BYTE");
		basicType2EnumMap.put("double","XSD_DOUBLE");
		basicType2EnumMap.put("xsd__unsignedLong","XSD_UNSIGNEDLONG");
		basicType2EnumMap.put("xsd__unsignedInt","XSD_UNSIGNEDINT");
		basicType2EnumMap.put("xsd__unsignedShort","XSD_UNSIGNEDSHORT");
		basicType2EnumMap.put("xsd__unsignedByte","XSD_UNSIGNEDBYTE");
		basicType2EnumMap.put("xsd__dateTime","XSD_DATETIME");
		basicType2EnumMap.put("xsd__date","XSD_DATE");
		basicType2EnumMap.put("xsd__time","XSD_TIME");
		basicType2EnumMap.put("xsd__base64Binary","XSD_BASE64BINARY");
		basicType2EnumMap.put("xsd__hexBinary","XSD_HEXBINARY");
		basicType2EnumMap.put("xsd__decimal","XSD_DECIMAL");
		basicType2EnumMap.put("xsd__boolean","XSD_BOOLEAN");
		basicType2EnumMap.put("xsd__anyURI","XSD_ANYURI");
		basicType2EnumMap.put("xsd__QName","XSD_QNAME");
		basicType2EnumMap.put("xsd__NMTOKEN","XSD_NMTOKEN");
	}
	
	public static void addSchemaDefinedSimpleType(QName qname, String type){
		schemaDefinedSimpleTypesMap.put(qname, type);
	}
	
	public static boolean isBasicType(QName qname){
		if(qname2classmap.containsKey(qname)){
			return true;
		}
		return false;
	}
	public static boolean isSimpleType(String name){
		if(class2QNamemap.containsKey(name))
			return true;
		return false;	
	} 
	public static boolean isAnyType(QName name){
			return name.equals(anyTypeQname);
	}
	public static boolean isSimpleType(QName name){
		if(qname2classmap.containsKey(name)){
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
		String methodname;
		if((methodname = (String)type2getValueMethodName.get(typeName))!= null){
			methodname = (isAttrib ? "getAttributeAs":"getElementAs") + methodname;
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
		val = schemaDefinedSimpleTypesMap.get(qname);
		if (val != null)
			return (String) val;
		return null;
	}
	public static String getWebServiceNameFromWrapperName(String wname){
		return wname.substring(0, wname.length()- CUtils.WRAPPER_NAME_APPENDER.length());
	}
	public static String getXSDTypeForBasicType(String stype){
		String enumName;
		//Samisa 23/08/2004
		System.out.println( "Could not find the type " + stype );
		//Samisa
		if((enumName = (String)basicType2EnumMap.get(stype))!= null){
			return enumName;
		}
		//Samisa 23/08/2004
		System.out.println( "Could not find the type " + stype );
		//Samisa
		return null;	
	}
	public static String getCmplxArrayNameforType(QName qname){
		String arrayName = null;
		if(!qname2classmap.containsKey(qname)){
			/* arrayName = qname.getLocalPart()+"_Array";
			* This avoid compilation issue for wsdl SimpleTypeInnerUnboundedInOutput.wsdl
			* See : malling list.
			*/
			arrayName = qname.getLocalPart().replace('>','_')+"_Array";			
		}
		return arrayName;		
	}
	
	public static String getBasicArrayNameforType(String stype){
		if (type2BasicArrayName.containsKey(stype))
			return (String)type2BasicArrayName.get(stype);
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
					if (javaName.equals("boolean") ||
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
