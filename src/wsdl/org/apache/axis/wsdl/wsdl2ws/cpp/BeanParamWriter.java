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
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

/**
 * Genarate a webservice for the complex types likes structs.
 * @author hemapani
 */

public class BeanParamWriter extends ParamCPPFileWriter{
	public BeanParamWriter(WebServiceContext wscontext,Type type)throws WrapperFault{
		super(wscontext,type);
	}
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.ParamCPPFileWriter#writeGlobalCodes()
	 */
	protected void writeGlobalCodes()throws WrapperFault{
		try{
		HashSet typeSet = new HashSet();
		String typeName;
		for(int i = 0; i< attribs.length;i++){
			if(!attribs[i].isSimpleType()){
				typeSet.add(attribs[i].getTypeName());
			}
		}
		Iterator itr = typeSet.iterator();
		while(itr.hasNext())
		{
			typeName = itr.next().toString();
			if ( ! typeName.equals(type.getName().getLocalPart())) {
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer* pDZ);\n");
				writer.write("extern void* Axis_Create_"+typeName+"("+typeName+"* pObj, bool bArray = false, int nSize=0);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");
			} else {
				writer.write("int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer* pDZ);\n");
				writer.write("void* Axis_Create_"+typeName+"("+typeName+"* pObj, bool bArray, int nSize);\n");
				writer.write("void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray, int nSize);\n");
				writer.write("int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray);\n");
				writer.write("int Axis_GetSize_"+typeName+"();\n\n");
			}		
		}
		writeSerializeGlobalMethod();
		writeDeSerializeGlobalMethod();
		writeCreateGlobalMethod();
		writeDeleteGlobalMethod();
		writeGetSizeGlobalMethod();
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
	private void writeGetSizeGlobalMethod() throws IOException{
		writer.write("/*\n");
		writer.write(" * This static method gives the size of "+classname+" type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_GetSize_"+classname+"()\n{\n\treturn sizeof("+classname+");\n}\n");
	}
	private void writeSerializeGlobalMethod()throws IOException,WrapperFault{
		writer.write("/*\n");
		writer.write(" * This static method serialize a "+classname+" type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_Serialize_"+classname+"("+classname+"* param, IWrapperSoapSerializer* pSZ, bool bArray = false)\n{\n");
		if (attribs.length == 0) {
			System.out.println("Possible error in class "  + classname + ": class with no attributes....................");
			writer.write("\t}\n\n");
			return;
		}
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		writer.write("\t\tpSZ->serialize(\"<\", Axis_TypeName_"+classname+", \">\", NULL);\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t\tconst AxisChar* sPrefix = pSZ->getNamespacePrefix(Axis_URI_"+classname+");\n");
		writer.write("\t\tpSZ->serialize(\"<\", Axis_TypeName_"+classname+", \" xsi:type=\\\"\", sPrefix, \":\",\n"); 
		writer.write("\t\t\tAxis_TypeName_"+classname+", \"\\\" xmlns:\", sPrefix, \"=\\\"\",\n"); 
		writer.write("\t\t\tAxis_URI_"+classname+", \"\\\">\", NULL);\n");
		writer.write("\t}\n\n");

		String arrayType;
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				//if Array
				if (attribs[i].isSimpleType()){
					writer.write("\tpSZ->serializeBasicArray((Axis_Array*)(&param->"+attribs[i].getParamName()+"),"+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+", \""+attribs[i].getParamName()+"\");\n"); 
				}
				else{
					String elm = attribs[i].getParamName();
					if ( attribs[i].isReference() )
						elm = attribs[i].getTypeName();
					arrayType =  attribs[i].getTypeName();
					writer.write("\tpSZ->serializeCmplxArray((Axis_Array*)(&param->"+attribs[i].getParamName()+"),\n"); 
					writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n"); 
					writer.write("\t\t\""+elm+"\", Axis_URI_"+arrayType+");\n");
				}
			}
			else if (attribs[i].isSimpleType()){
				if (attribs[i].isAttribute()){
					if (attribs[i].isOptional()){
						writer.write("\tif (0 != param->"+attribs[i].getParamName()+")\n");
						writer.write("\t\tpSZ->serializeAsAttribute(\""+attribs[i].getParamName()+"\", 0, (void*)(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
					}
					else{
						writer.write("\tpSZ->serializeAsAttribute(\""+attribs[i].getParamName()+"\", 0, (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");				
					}
				}
				else
					writer.write("\tpSZ->serializeAsElement(\""+attribs[i].getParamName()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");				
			}else{
				//if complex type
				writer.write("\tAxis_Serialize_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+", pSZ);\n");
			}
		}
		writer.write("\n\tpSZ->serialize(\"</\", Axis_TypeName_"+classname+", \">\", NULL);\n");
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n\n");
	
	}
	private void writeDeSerializeGlobalMethod()throws IOException,WrapperFault{	
		writer.write("/*\n");
		writer.write(" * This static method deserialize a "+classname+" type of object\n");
		writer.write(" */\n");		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer* pIWSDZ)\n{\n");
		if (attribs.length == 0) {
			System.out.println("Possible error in class "  + classname + ": class with no attributes....................");
			writer.write("\t}\n\n");
			return;
		 }
		String arrayType = null;
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				//if Array
				if (attribs[i].isSimpleType()){
					writer.write("\tparam->"+attribs[i].getParamName()+" = ("+CUtils.getBasicArrayNameforType(attribs[i].getTypeName())+"&)pIWSDZ->getBasicArray("+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+ ", \""+attribs[i].getParamName()+"\",0);\n");
				}
				else{
					String elm = attribs[i].getParamName();
					if ( attribs[i].isReference() )
						elm = attribs[i].getTypeName();					
					arrayType = attribs[i].getTypeName();
					writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"_Array&)pIWSDZ->getCmplxArray((void*)Axis_DeSerialize_"+arrayType+ 
						"\n\t\t, (void*)Axis_Create_"+arrayType+", (void*)Axis_Delete_"+arrayType+
						"\n\t\t, (void*)Axis_GetSize_"+arrayType+", \""+elm+"\", Axis_URI_"+arrayType+");\n");
				}
			}else if(attribs[i].isSimpleType()){
				//TODO handle optional attributes
				writer.write("\tparam->"+attribs[i].getParamName()+" = pIWSDZ->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute())+"(\""+attribs[i].getParamName()+"\",0);\n");
			} else{
				//if complex type
				String elm = attribs[i].getParamName();
				if ( attribs[i].isReference() )
					elm = attribs[i].getTypeName();					
				writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"*)pIWSDZ->getCmplxObject((void*)Axis_DeSerialize_"+attribs[i].getTypeName()+
					"\n\t\t, (void*)Axis_Create_"+attribs[i].getTypeName()+", (void*)Axis_Delete_"+attribs[i].getTypeName()+
					"\n\t\t, \""+attribs[i].getTypeName()+"\", Axis_URI_"+attribs[i].getTypeName()+");\n");				
			}		
		}
		writer.write("\treturn pIWSDZ->getStatus();\n");
		writer.write("}\n");
	}
	
	private void writeCreateGlobalMethod()throws IOException{
		writer.write("void* Axis_Create_"+classname+"("+classname+"* pObj, bool bArray = false, int nSize=0)\n{\n");
		writer.write("\tif (bArray && (nSize > 0))\n\t{\n\t\tif (pObj)\n\t\t{\n");
		writer.write("\t\t\t"+classname+"* pNew = new "+classname+"[nSize];\n");
		writer.write("\t\t\tmemcpy(pNew, pObj, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\t\tmemset(pObj, 0, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\t\tdelete [] pObj;\n");
		writer.write("\t\t\treturn pNew;\n\t\t}\n\t\telse\n\t\t{\n");
		writer.write("\t\t\treturn new "+classname+"[nSize];\n\t\t}\n\t}\n");
		writer.write("\telse\n\t\treturn new "+classname+";\n}\n\n");
	}
	private void writeDeleteGlobalMethod()throws IOException{
		writer.write("/*\n");
		writer.write(" * This static method delete a "+classname+" type of object\n");
		writer.write(" */\n");		
		writer.write("void Axis_Delete_"+classname+"("+classname+"* param, bool bArray = false, int nSize=0)\n");
		writer.write("{\n");
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		writer.write("\t\tdelete [] param;\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t\tdelete param;\n");
		writer.write("\t}\n");
		writer.write("}\n");
	}
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
		try{
		writer.write("\n"+classname+"::"+classname+"()\n{\n");
		writer.write("\t/*do not allocate memory to any pointer members here\n\t because deserializer will allocate memory anyway. */\n");
		for(int i = 0; i< attribs.length;i++){
			if (attribs[i].isArray()){
				writer.write("\t"+attribs[i].getParamName()+".m_Array = 0;\n");
				writer.write("\t"+attribs[i].getParamName()+".m_Size = 0;\n");
			}
			else if (!attribs[i].isSimpleType()){
				writer.write("\t"+attribs[i].getParamName()+"=0;\n");
			}
		}			
		writer.write("}\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write("\n"+classname+"::~"+classname+"()\n{\n");
		writer.write("\t/*delete any pointer and array members here*/\n");
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				writer.write("\tdelete [] (("+attribs[i].getTypeName()+"*)"+attribs[i].getParamName()+".m_Array);\n");
			}
			else if (!attribs[i].isSimpleType()){
				writer.write("\tdelete "+attribs[i].getParamName()+";\n");				
			}
		}			
		writer.write("}\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}		
}
