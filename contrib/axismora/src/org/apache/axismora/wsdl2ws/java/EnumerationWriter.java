package org.apache.axismora.wsdl2ws.java;

import java.io.IOException;
import java.util.Vector;

import org.apache.axismora.wsdl2ws.WrapperFault;
import org.apache.axismora.wsdl2ws.WrapperUtils;
import org.apache.axismora.wsdl2ws.info.Type;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;

/**
 * @author hemapani
 */
public class EnumerationWriter extends JavaClassWriter{
	private Type type;
	private String basetype;
	private Vector ids; 
	private WebServiceContext wscontext;
	
	public EnumerationWriter(Type type,WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getPackegeName4QualifiedName(type.getLanguageSpecificName()),
		WrapperUtils.getClassNameFromFullyQualifiedName(
			type.getLanguageSpecificName()),wscontext.getWrapInfo().getTargetOutputLocation());
		this.type = type;
		basetype = getBaseTypeInjava();	
		this.wscontext = wscontext;
	}

	protected void writeAttributes() throws WrapperFault {
		try {
			writer.write("    private " + basetype + " _value_;\n");
            
			// The enumeration values are kept in a hashtable
		   // writer.write("    private static java.util.HashMap _table_ = new java.util.HashMap();");
			writer.write("");
            
			ids = getEnumValueIds(type.getEnumerationdata());
			Vector values =  getEnumValues();
			
			for(int i = 0;i<ids.size();i++){
				writer.write("\tpublic static "+basetype+" "+ids.get(i)+" = "+values.get(i)+";\n");
				//writer.write("        _table_.put("+ids.get(i)+",this);");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}

	protected void writeConstructors() throws WrapperFault {
		try {
			writer.write(
					  "\tpublic "
						  + WrapperUtils.getClassNameFromFullyQualifiedName(
							  type.getLanguageSpecificName())
						  + "("+basetype+" value)throws org.apache.axis.AxisFault{\n");
			writer.write("\t\tsetValue(value);\n");			  
			writer.write("\t}\n");
			
			writer.write(
					  "\tpublic "
						  + WrapperUtils.getClassNameFromFullyQualifiedName(
							  type.getLanguageSpecificName())
						  + "(){}\n");
					  
		}catch(IOException e){
			throw new WrapperFault(e);
		}				  
	}

	protected void writeMethods() throws WrapperFault {
		writeDesirializeMethod();
		writeSerializeMethod();
		writeSetValueMethod();
		writegetParamMethod();
	}
    
	public void writeDesirializeMethod() throws WrapperFault {
		try {
			writer.write(
				"\tpublic org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{\n");
			String wrapName = WrapperUtils.getWrapperName4FullyQualifiedName(basetype);
			writer.write("\t\t"+wrapName+" param = new "+wrapName+"();\n");
			writer.write("\t\tsetValue((("+wrapName+")param.desierialize(msgdata)).getParam());\n");
			writer.write("\t\treturn this;\n");
			writer.write("\n\t}\n");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}

	}

	public void writeSerializeMethod() throws WrapperFault {
		try {
			writer.write(
				"\tpublic void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{\n");
			String wrapName = WrapperUtils.getWrapperName4FullyQualifiedName(basetype);
			writer.write("\t\t"+wrapName+" param = new "+wrapName+"(_value_);\n");
			writer.write("\t\tserialize(context);\n");
			writer.write("\t}\n");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}

	public void writeSetValueMethod()throws WrapperFault{
		String equalop = "== value";
		if(!JavaUtils.isJavaSimpleType(basetype))
			equalop = ".equals(value)";
		try {
				writer.write(
			"\tpublic void setValue("+basetype+" value)throws org.apache.axis.AxisFault{\n");
			if(ids.size() == 0)
				return;
				
			writer.write("\t\tif("+ids.get(0)+equalop+"){}\n");		

			for(int i = 1;i<ids.size();i++){
				writer.write("\t\telse if("+ids.get(i)+equalop+"){}\n");
			}
			writer.write("\t\telse\n\t\t\tthrow new org.apache.axis.AxisFault(\"Illegal Enumeration vlue\");\n");
			writer.write("\t\t_value_ = value;\n");
			writer.write("\t}\n");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}
    
	public void writegetParamMethod()throws WrapperFault{
		try {
				writer.write("\tpublic "+basetype+" getParam(){\n");
			writer.write("\t\treturn _value_;\n");
			writer.write("\t}\n");
		} catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}
    

	 /**
	  * Get the enumeration names for the values.
	  * The name is affected by whether all of the values of the enumeration
	  * can be expressed as valid java identifiers.
	  * @param bv Vector base and values vector from getEnumerationBaseAndValues
	  * @return Vector names of enum value identifiers.
	  */
	 public static Vector getEnumValueIds(Vector bv) {
		 // Build the vector of ids
		 Vector ids = new Vector();
		 for (int i=1; i < bv.size(); i++) {
				 ids.add("value" + i);
		 }
		 return ids;
	 }
	 
	 public String getBaseTypeInjava(){
		// The first index is the base type.
		// The base type could be a non-object, if so get the corresponding Class.
		String baseType = ((Type) type.getEnumerationdata().get(0)).getLanguageSpecificName();
		String baseClass = baseType;
//		if (baseType.indexOf("int") == 0) {
//			baseClass = "java.lang.Integer";
//		} else if (baseType.indexOf("char") == 0) {
//			baseClass = "java.lang.Character";
//		} else if (baseType.indexOf("short") == 0) {
//			baseClass = "java.lang.Short";
//		} else if (baseType.indexOf("long") == 0) {
//			baseClass = "java.lang.Long";
//		} else if (baseType.indexOf("double") == 0) {
//			baseClass = "java.lang.Double";
//		} else if (baseType.indexOf("float") == 0) {
//			baseClass = "java.lang.Float";
//		}else if (baseType.indexOf("byte") == 0) {
//			baseClass = "java.lang.Byte";
//		}
		return baseClass;
	 } 
	 
	 private Vector getEnumValues(){
		// Create a list of the literal values.
		Vector values = new Vector();
		Vector elements = type.getEnumerationdata();
		for (int i=1; i < elements.size(); i++) {
			String value = (String) elements.get(i);
			if (basetype.equals("java.lang.String")) {
				value = "\"" + value + "\"";  // Surround literal with double quotes
			} 
			else if (basetype.equals("char")) {
				value = "'" + value + "'";
			}
			else if (basetype.equals("float")) {
				if (!value.endsWith("F") &&   // Indicate float literal so javac
					!value.endsWith("f"))     // doesn't complain about precision.
					value += "F";
			}
			else if (basetype.equals("long")) {
				if (!value.endsWith("L") &&   // Indicate float literal so javac
					!value.endsWith("l"))     // doesn't complain about precision.
					value += "L";
			}else if(basetype.equals("byte")){
				value = "\""+value+"\".getBytes()[0]";
			}else if(basetype.equals("double")||basetype.equals("short")||basetype.equals("int")){
				//value do not change
			}else{
				// Construct baseClass object with literal string
				value = "new "+basetype +"(" + value + ")"; 
			}
			
			values.add(value);
		}
		
		return values;

	 }
	/* (non-Javadoc)
	 * @see org.apache.axismora.wsdl2ws.java.JavaClassWriter#getimplementsPart()
	 */
	protected String getimplementsPart() {
		return " implements org.apache.axismora.encoding.InOutParameter";
	}

}
