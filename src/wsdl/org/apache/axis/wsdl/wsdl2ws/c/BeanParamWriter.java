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

package org.apache.axis.wsdl.wsdl2ws.c;

import java.io.File;
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

public class BeanParamWriter extends ParamCFileWriter{
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
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer* pDZ);\n");
				writer.write("extern void* Axis_Create_"+typeName+"("+typeName+"* pObj, bool bArray, int nSize);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray, int nSize);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");			
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
		writer.write("/**\n");
		writer.write(" * This static method gives the size of "+classname+" type of object\n");
		writer.write(" */\n");
		writer.write("int Axis_GetSize_"+classname+"()\n{\n\treturn sizeof("+classname+");\n}\n");
	}
	private void writeSerializeGlobalMethod()throws IOException,WrapperFault{
		writer.write("/**\n");
		writer.write(" * This static method serialize a "+classname+" type of object\n");
		writer.write(" */\n");
		
		writer.write("int Axis_Serialize_"+classname+"("+classname+"* param, IWrapperSoapSerializer* pSZ, bool bArray)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			System.out.println("Possible error in class "  + classname + ": class with no attributes....................");
			 writer.write("\t}\n\n");			 
			 return;
		}
		writer.write("\tconst AxisChar* sPrefix;\n");
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		writer.write("\t\tpSZ->_functions->serializeStartElementOfType(pSZ->_object, Axis_TypeName_"+classname+", 0, 0);\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t\tsPrefix = pSZ->_functions->getNamespacePrefix(pSZ->_object, Axis_URI_"+classname+");\n");
		writer.write("\t\tpSZ->_functions->serializeStartElementOfType(pSZ->_object, Axis_TypeName_"+classname+", Axis_URI_"+classname+", sPrefix);\n");
		writer.write("\t}\n\n");
		String arrayType = null;
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				if(attribs[i].isSimpleType()){
					writer.write("\tpSZ->_functions->serializeBasicArray(pSZ->_object, (Axis_Array*)(&param->"+attribs[i].getParamName()+"),"+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+", \""+attribs[i].getParamName()+"\");\n"); 
				}
				else{
					String elm = attribs[i].getParamName();
					if ( attribs[i].isReference() )
						elm = attribs[i].getTypeName();					
					arrayType = attribs[i].getTypeName();
					writer.write("\tpSZ->_functions->serializeCmplxArray(pSZ->_object, (Axis_Array*)(&param->"+attribs[i].getParamName()+"),\n"); 
					writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n"); 
					writer.write("\t\t\""+elm+"\", Axis_TypeName_"+arrayType+");\n");
				}
			}
			else if(attribs[i].isSimpleType()){
				if(attribs[i].isAttribute()){
					if(attribs[i].isOptional()){
						writer.write("\tif(0 != param->"+attribs[i].getParamName()+")\n");
						writer.write("\t\tpSZ->_functions->serializeAsAttribute(pSZ->_object, \""+attribs[i].getParamName()+"\", 0, (void*)(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
					}else{
						writer.write("\tpSZ->_functions->serializeAsAttribute(pSZ->_object, \""+attribs[i].getParamName()+"\", 0, (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
					}
				}
				else{
					writer.write("\tpSZ->_functions->serializeAsElement(pSZ->_object, \""+attribs[i].getParamName()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				}
			}
			else{
				//if complex type
				writer.write("\tAxis_Serialize_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+", pSZ, false);\n");
			}			
		}
		writer.write("\n\tpSZ->_functions->serializeEndElementOfType(pSZ->_object, Axis_TypeName_"+classname+");\n");
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n\n");
	
	}
	private void writeDeSerializeGlobalMethod()throws IOException,WrapperFault{	
		writer.write("/**\n");
		writer.write(" * This static method deserialize a "+classname+" type of object\n");
		writer.write(" */\n");
		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer* pDZ)\n{\n");
		if (attribs.length == 0) {
			System.out.println("Possible error in class "  + classname + ": class with no attributes....................");
			 writer.write("\t}\n\n");
			 return;
		}
		boolean aretherearrayattribs = false;
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				aretherearrayattribs = true; break;
			}
		}
		if (aretherearrayattribs){
			writer.write("\tAxis_Array array;\n");	
		}
		String containedType = null;
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				containedType = attribs[i].getTypeName();
				if(attribs[i].isSimpleType()){
					writer.write("\tarray = pDZ->_functions->getBasicArray(pDZ->_object, "+CUtils.getXSDTypeForBasicType(containedType)+",0,0);\n");
					writer.write("\tmemcpy(&(param->"+attribs[i].getParamName()+"), &array, sizeof(Axis_Array));\n");
				}
				else{
					writer.write("\tarray = pDZ->_functions->getCmplxArray(pDZ->_object, (void*)Axis_DeSerialize_"+containedType+ 
						"\n\t\t, (void*)Axis_Create_"+containedType+", (void*)Axis_Delete_"+containedType+
						"\n\t\t, (void*)Axis_GetSize_"+containedType+", Axis_TypeName_"+containedType+", Axis_URI_"+containedType+");\n");
					writer.write("\tmemcpy(&(param->"+attribs[i].getParamName()+"), &array, sizeof(Axis_Array));\n");
				}
			}
			else if(attribs[i].isSimpleType()){
				if(attribs[i].isAttribute()){
					if(attribs[i].isOptional()){
						//TODO
					}else{
						writer.write("\tparam->"+attribs[i].getParamName()+" = pDZ->_functions->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(),true)+"(pDZ->_object,0,0);\n");
					}
				}
				else{
					writer.write("\tparam->"+attribs[i].getParamName()+" = pDZ->_functions->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(),false)+"(pDZ->_object,0,0);\n");
				}
			}
			else{
				//if complex type
				writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"*)pDZ->_functions->getCmplxObject(pDZ->_object, (void*)Axis_DeSerialize_"+attribs[i].getTypeName()+
					"\n\t\t, (void*)Axis_Create_"+attribs[i].getTypeName()+", (void*)Axis_Delete_"+attribs[i].getTypeName()+
					"\n\t\t, Axis_TypeName_"+attribs[i].getTypeName()+", Axis_URI_"+attribs[i].getTypeName()+");\n");
			}			
		}
		writer.write("\treturn pDZ->_functions->getStatus(pDZ->_object);\n");
		writer.write("}\n");
	}
	
	private void writeCreateGlobalMethod()throws IOException{
		writer.write("void* Axis_Create_"+classname+"("+classname+"* pObj, bool bArray, int nSize)\n{\n");
		writer.write("\t"+classname+"* pTemp;\n");			
		writer.write("\tif (bArray && (nSize > 0))\n\t{\n");
		writer.write("\t\tpObj = malloc(sizeof("+classname+")*nSize);\n");
		writer.write("\t\t\tpTemp = pObj;\n");		
		writer.write("\t\t\tpTemp += nSize/2;\n");
		writer.write("\t\t\tmemset(pTemp, 0, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t}\n\telse\n\t{\n");
		writer.write("\t\tpObj = malloc(sizeof("+classname+"));\n");
		writer.write("\t\tmemset(pObj, 0, sizeof("+classname+"));\n\n");
		writer.write("\t\tpTemp = pObj;\n");
		for(int i = 0; i< attribs.length;i++){
			if (attribs[i].isArray()){
				writer.write("\t\tpTemp->"+attribs[i].getParamName()+".m_Array = 0;\n");
				writer.write("\t\tpTemp->"+attribs[i].getParamName()+".m_Size = 0;\n");
			}
			else if (!attribs[i].isSimpleType()){
				writer.write("\t\tpTemp->"+attribs[i].getParamName()+"=0;\n");
			}	
		}
		writer.write("\t}\n\treturn pObj;\n}\n");
	}

	private void writeDeleteGlobalMethod()throws IOException{
		writer.write("/**\n");
		writer.write(" * This static method to deallocate a "+classname+" type of object\n");
		writer.write(" */\n");
		
		writer.write("void Axis_Delete_"+classname+"("+classname+"* param, bool bArray, int nSize)\n");
		writer.write("{\n");
		boolean hasComplexTypeOrArray = false;
		for(int i = 0; i< attribs.length;i++){
			if(!attribs[i].isSimpleType()){
				hasComplexTypeOrArray = true; break;
			}
			else if ("xsd__string".equals(attribs[i].getTypeName())){
				hasComplexTypeOrArray = true; break;
			}
			else if ("xsd__base64Binary".equals(attribs[i].getTypeName())){
				hasComplexTypeOrArray = true; break;
			}
			else if ("xsd__hexBinary".equals(attribs[i].getTypeName())){
				hasComplexTypeOrArray = true; break;
			}			
		}
		if (hasComplexTypeOrArray){
			writer.write("\tint x;\n");
			writer.write("\t"+classname+"* pTemp;\n");	
		}			
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		if (hasComplexTypeOrArray){ 
			writer.write("\t\t/*delete any pointer members or array members of this struct here*/\n");
			writer.write("\t\tpTemp = param;\n");
			writer.write("\t\tfor (x=0; x<nSize; x++)\n");
			writer.write("\t\t{\n");
			for(int i = 0; i< attribs.length;i++){
				if(attribs[i].isArray()){
					if(attribs[i].isSimpleType()){
						writer.write("\t\t\tif (pTemp->"+attribs[i].getParamName()+".m_Array) free(pTemp->"+attribs[i].getParamName()+".m_Array);\n");
					}
					else{
						writer.write("\t\t\tif (pTemp->"+attribs[i].getParamName()+".m_Array) Axis_Delete_"+attribs[i].getTypeName()+"(pTemp->"+attribs[i].getParamName()+".m_Array, true, pTemp->"+attribs[i].getParamName()+".m_Size);\n");
					}
				}
				else if(!attribs[i].isSimpleType()){
					writer.write("\t\t\tif (pTemp->"+attribs[i].getParamName()+") Axis_Delete_"+attribs[i].getTypeName()+"(pTemp->"+attribs[i].getParamName()+", false, 0);\n");					
				}
				else if ("xsd__string".equals(attribs[i].getTypeName())){
					writer.write("\t\t\tif(pTemp->"+attribs[i].getParamName()+") free(pTemp->"+attribs[i].getParamName()+");\n");
				}
				else if ("xsd__base64Binary".equals(attribs[i].getTypeName())){
					writer.write("\t\t\tif(pTemp->"+attribs[i].getParamName()+".__ptr) free(pTemp->"+attribs[i].getParamName()+".__ptr);\n");
				}
				else if ("xsd__hexBinary".equals(attribs[i].getTypeName())){
					writer.write("\t\t\tif(pTemp->"+attribs[i].getParamName()+".__ptr) free(pTemp->"+attribs[i].getParamName()+".__ptr);\n");
				}
				else if(attribs[i].isOptional()){
					//TODO
				}
			}			
			writer.write("\t\t\tpTemp++;\n");
			writer.write("\t\t}\n");
		}
		writer.write("\t\tfree(param);\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t\t/*delete any pointer members or array members of this struct here*/\n");
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				if(attribs[i].isSimpleType()){
					writer.write("\t\tif (param->"+attribs[i].getParamName()+".m_Array) free(param->"+attribs[i].getParamName()+".m_Array);\n");
				}
				else{
					writer.write("\t\tif (param->"+attribs[i].getParamName()+".m_Array) Axis_Delete_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+".m_Array, true, param->"+attribs[i].getParamName()+".m_Size);\n");
				}
			}
			else if(!attribs[i].isSimpleType()){
				writer.write("\t\tif (param->"+attribs[i].getParamName()+") Axis_Delete_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+", false, 0);\n");
			}
			else if ("xsd__string".equals(attribs[i].getTypeName())){
				writer.write("\t\tif(param->"+attribs[i].getParamName()+") free(param->"+attribs[i].getParamName()+");\n");
			}
			else if ("xsd__base64Binary".equals(attribs[i].getTypeName())){
				writer.write("\t\tif(param->"+attribs[i].getParamName()+".__ptr) free(param->"+attribs[i].getParamName()+".__ptr);\n");
			}
			else if ("xsd__hexBinary".equals(attribs[i].getTypeName())){
				writer.write("\t\tif(param->"+attribs[i].getParamName()+".__ptr) free(param->"+attribs[i].getParamName()+".__ptr);\n");
			}
			else if(attribs[i].isOptional()){
				//TODO
			}
		}			
		writer.write("\t\tfree(param);\n");
		writer.write("\t}\n");
		writer.write("}\n");
	}	
	protected File getFilePath(boolean useServiceName) throws WrapperFault {
		
		return null;
	}
}
