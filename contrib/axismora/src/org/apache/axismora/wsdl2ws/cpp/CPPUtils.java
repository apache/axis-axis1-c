package org.apache.axismora.wsdl2ws.cpp;

import java.util.Hashtable;

import javax.xml.namespace.QName;

import org.apache.axismora.wsdl2ws.WrapperConstants;

/**
 * 
 * @author hemapani@opensource.lk
 */
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
		 class2QNamemap.put("byte", new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"));
		 class2QNamemap.put("float", new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"));
		 class2QNamemap.put("long", new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"));
		 class2QNamemap.put("double", new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"));
		 class2QNamemap.put("boolean", new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"));
		 class2QNamemap.put("char", new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"));
		 class2QNamemap.put("short", new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"));
		 class2QNamemap.put("string", new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"));

		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "int"), "int");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "byte"), "byte");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "float"), "float");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "long"), "long");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "double"), "double");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "boolean"), "boolean");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "char"), "char");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "short"), "short");
		 qname2classmap.put(new QName(WrapperConstants.SCHEMA_NAMESPACE, "string"), "string");
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
		type2getValueMethodName.put("bool","GetBool");
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
}
