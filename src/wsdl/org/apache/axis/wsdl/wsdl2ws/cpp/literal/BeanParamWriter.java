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

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

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
			writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
			writer.write("extern void* Axis_Create_"+typeName+"(void* pObj, bool bArray = false, int nSize=0);\n");
			writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
			writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n");
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
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error class with no attributes....................");
			 return;
		}
		String arrayType;
		writer.write("\t/* first serialize attributes if any*/\n");
		for(int i = 0; i< attributeParamCount;i++){
			if(attribs[i].isArray() || !(attribs[i].isSimpleType())){
				throw new WrapperFault("Error : an attribute is not basic type");
			}
			else{
				if (attribs[i].isOptional()){
					writer.write("\tif (0 != param->"+attribs[i].getParamName()+")\n");
					writer.write("\t\tpSZ->SerializeAsAttribute(\""+attribs[i].getParamName()+"\", (void*)(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				}
				else{
					writer.write("\tpSZ->SerializeAsAttribute(\""+attribs[i].getParamName()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");				
				}
			}
		}
		writer.write("\tpSZ->Serialize(\">\", NULL);\n");
		writer.write("\t/* then serialize elements if any*/\n");
		for(int i = attributeParamCount; i< attribs.length;i++){
			if(attribs[i].isArray()){
				//if Array
				if (attribs[i].isSimpleType()){
					writer.write("\tpSZ->SerializeBasicArray((Axis_Array*)(&param->"+attribs[i].getParamName()+"),"+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+", \""+attribs[i].getParamName()+"\");\n"); 
				}
				else{
					arrayType = attribs[i].getTypeName();
					writer.write("\tpSZ->SerializeCmplxArray((Axis_Array*)(&param->"+attribs[i].getParamName()+"),\n"); 
					writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n"); 
					writer.write("\t\t\""+attribs[i].getParamName()+"\", Axis_URI_"+arrayType+");\n");
				}
			}
			else if (attribs[i].isSimpleType()){
				writer.write("\tpSZ->SerializeAsElement(\""+attribs[i].getParamName()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");				
			}else{
				//if complex type
				writer.write("\tpSZ->Serialize(\"<"+attribs[i].getParamName()+">\", 0);\n");
				writer.write("\tAxis_Serialize_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+", pSZ);\n");
				writer.write("\tpSZ->Serialize(\"<"+attribs[i].getParamName()+">\", 0);\n");
			}
		}
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n\n");
	
	}
	private void writeDeSerializeGlobalMethod()throws IOException,WrapperFault{	
		writer.write("/*\n");
		writer.write(" * This static method deserialize a "+classname+" type of object\n");
		writer.write(" */\n");		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer *pIWSDZ)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error class with no attributes....................");
			 return;
		 }
		String arrayType = null;
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				//if Array
				if (attribs[i].isSimpleType()){
					writer.write("\tparam->"+attribs[i].getParamName()+" = ("+CUtils.getBasicArrayNameforType(attribs[i].getTypeName())+"&)pIWSDZ->GetBasicArray("+CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+ ", \""+attribs[i].getParamName()+"\",0);\n");
				}
				else{
					arrayType = attribs[i].getTypeName();
					writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"_Array&)pIWSDZ->GetCmplxArray((void*)Axis_DeSerialize_"+arrayType+ 
						"\n\t\t, (void*)Axis_Create_"+arrayType+", (void*)Axis_Delete_"+arrayType+
						"\n\t\t, (void*)Axis_GetSize_"+arrayType+", \""+attribs[i].getParamName()+"\", Axis_URI_"+arrayType+");\n");
				}
			}else if(attribs[i].isSimpleType()){
				//TODO handle optional attributes
				writer.write("\tparam->"+attribs[i].getParamName()+" = pIWSDZ->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), attribs[i].isAttribute())+"(\""+attribs[i].getParamName()+"\",0);\n");
			} else{
				//if complex type
				writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_"+attribs[i].getTypeName()+
					"\n\t\t, (void*)Axis_Create_"+attribs[i].getTypeName()+", (void*)Axis_Delete_"+attribs[i].getTypeName()+
					"\n\t\t, \""+attribs[i].getParamName()+"\", Axis_URI_"+attribs[i].getTypeName()+");\n");				
			}		
		}
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n");
	}
	
	private void writeCreateGlobalMethod()throws IOException{
		writer.write("void* Axis_Create_"+classname+"("+classname+"* pObj, bool bArray = false, int nSize=0)\n{\n");
		writer.write("\tif (bArray && (nSize > 0))\n\t{\n\t\tif (pObj)\n\t\t{\n");
		writer.write("\t\t\t"+classname+"* pNew = new "+classname+"[nSize];\n");
		writer.write("\t\t\tmemcpy(pNew, pObj, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\t\tmemset(pObj, 0, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\t\tdelete [] pObj);\n");
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
				writer.write("\t\t"+attribs[i].getParamName()+".m_Array = 0;\n");
				writer.write("\t\t"+attribs[i].getParamName()+".m_Size = 0;\n");
			}
			else if (!attribs[i].isSimpleType()){
				writer.write("\t\t"+attribs[i].getParamName()+"=0;\n");
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
