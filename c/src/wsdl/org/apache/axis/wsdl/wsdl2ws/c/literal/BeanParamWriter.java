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

import java.io.IOException;
import java.util.HashSet;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
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
				if(!CUtils.isSimpleType(attribs[i][1])){
					//to understand what happens here please refer to where the 
					//attribs[][] is created. (ParamWriter) 		
					if (attribs[i][5] != null){
						QName qname = new QName(attribs[i][4],attribs[i][5]);
						if (CUtils.isSimpleType(qname)) continue; //no wrapper methods for basic types
						typeName = qname.getLocalPart();
					}else{
						typeName = attribs[i][1];
					}	
					typeSet.add(typeName);
				}
			}
		
			Iterator itr = typeSet.iterator();
			while(itr.hasNext())
			{
				typeName = itr.next().toString();
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
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
		Type t;
		writer.write("/**\n");
		writer.write(" * This static method serialize a "+classname+" type of object\n");
		writer.write(" */\n");
		
		writer.write("int Axis_Serialize_"+classname+"("+classname+"* param, IWrapperSoapSerializer* pSZ, bool bArray)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error class with no attributes....................");
			 return;
		 }
		writer.write("\tIWrapperSoapSerializerFunctions* pSZX = pSZ->__vfptr;\n");
		for(int i = 0; i< attribs.length;i++){
			if(CUtils.isSimpleType(attribs[i][1])){
				//if simple type
				//TODO serialize as attribute if this is an attribute
				writer.write("\tpSZX->SerializeAsElement(pSZ, \""+attribs[i][0]+"\", (void*)&(param->"+attribs[i][0]+"), "+ CUtils.getXSDTypeForBasicType(attribs[i][1])+");\n");
			}else if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()){
				//if Array
				QName qname = WrapperUtils.getArrayType(t).getName();
				String arrayType = null;
				if (CUtils.isSimpleType(qname)){
					arrayType = CUtils.getclass4qname(qname);
					writer.write("\tpSZX->SerializeBasicArray(pSZ, (Axis_Array*)(&param->"+attribs[i][0]+"),"+CUtils.getXSDTypeForBasicType(arrayType)+", \""+attribs[i][0]+"\");\n"); 
				}
				else{
					arrayType = qname.getLocalPart();
					writer.write("\tpSZX->SerializeCmplxArray(pSZ, (Axis_Array*)(&param->"+attribs[i][0]+"),\n"); 
					writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n"); 
					writer.write("\t\t\""+attribs[i][0]+"\", Axis_URI_"+arrayType+");\n");
				}
			}else{
				//if complex type
				writer.write("\tAxis_Serialize_"+attribs[i][1]+"(param->"+attribs[i][0]+", pSZ);\n");
			}
		}
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n\n");
	
	}
	private void writeDeSerializeGlobalMethod()throws IOException,WrapperFault{	
		Type t;
		writer.write("/**\n");
		writer.write(" * This static method deserialize a "+classname+" type of object\n");
		writer.write(" */\n");
		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer *pDZ)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error calss with no attributes....................");
			 return;
		}
		writer.write("\tIWrapperSoapDeSerializerFunctions* pDZX = pDZ->__vfptr;\n");
		boolean aretherearrayparams = false;
		for(int i = 0; i< attribs.length;i++){
			if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()){
				aretherearrayparams = true; break;
			}
		}
		if (aretherearrayparams){
			writer.write("\tAxis_Array array;\n");	
		}
		for(int i = 0; i< attribs.length;i++){
			if(CUtils.isSimpleType(attribs[i][1])){
				//if symple type
				writer.write("\tparam->"+attribs[i][0]+" = pDZX->"+CUtils.getParameterGetValueMethodName(attribs[i][1], false)+"(pDZ);\n");
			}else if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()){
				//if Array
				QName qname = WrapperUtils.getArrayType(t).getName(); 
				String containedType = null;
				if (CUtils.isSimpleType(qname)){
					containedType = CUtils.getclass4qname(qname);
					writer.write("\tarray = pDZX->GetBasicArray(pDZ, "+CUtils.getXSDTypeForBasicType(containedType)+ ", \""+attribs[i][0]+"\",0);\n");
					writer.write("\tmemcpy(&(param->"+attribs[i][0]+"), &array, sizeof(Axis_Array));\n");
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("\tarray = pDZX->GetCmplxArray(pDZ, (void*)Axis_DeSerialize_"+containedType+ 
						"\n\t\t, (void*)Axis_Create_"+containedType+", (void*)Axis_Delete_"+containedType+
						"\n\t\t, (void*)Axis_GetSize_"+containedType+", \""+attribs[i][0]+"\", Axis_URI_"+containedType+");\n");
					writer.write("\tmemcpy(&(param->"+attribs[i][0]+"), &array, sizeof(Axis_Array));\n");
				}
			}else{
				//if complex type
				writer.write("\tparam->"+attribs[i][0]+" = ("+attribs[i][1]+"*)pDZX->GetObject(pDZ, (void*)Axis_DeSerialize_"+attribs[i][1]+
					"\n\t\t, (void*)Axis_Create_"+attribs[i][1]+", (void*)Axis_Delete_"+attribs[i][1]+
					"\n\t\t, \""+attribs[i][0]+"\", Axis_URI_"+attribs[i][1]+");\n");				
			}		
		}
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n");
	}
	
	private void writeCreateGlobalMethod()throws IOException{
		writer.write("void* Axis_Create_"+classname+"("+classname+"* pObj, bool bArray, int nSize)\n{\n");
		writer.write("\tif (bArray && (nSize > 0))\n\t{\n");
		writer.write("\t\tpObj = realloc(pObj, sizeof("+classname+")*nSize);\n");
		writer.write("\t\tmemset(pObj+sizeof("+classname+")*nSize/2, 0, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\treturn pObj;\n\t}\n");
		writer.write("\telse\n\t\treturn malloc(sizeof("+classname+"));\n}\n\n");	
	}
	
	private void writeDeleteGlobalMethod()throws IOException{
		writer.write("/**\n");
		writer.write(" * This static method delete a "+classname+" type of object\n");
		writer.write(" */\n");
		
		writer.write("void Axis_Delete_"+classname+"("+classname+"* param, bool bArray, int nSize)\n");
		writer.write("{\n");
		boolean hasComplexTypeOrArray = false;
		for(int i = 0; i< attribs.length;i++){
			if(!CUtils.isSimpleType(attribs[i][1])){
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
				if(!CUtils.isSimpleType(attribs[i][1])){ //this can be either an array or complex type
					//to understand what happens here please refer to where the 
							//attribs[][] is created. (ParamWriter) 		
					if (attribs[i][5] != null){
						QName qname = new QName(attribs[i][4],attribs[i][5]);
						String containedType = null;
						if (CUtils.isSimpleType(qname)){
							containedType = CUtils.getclass4qname(qname);
							writer.write("\t\t\tfree(pTemp->"+attribs[i][0]+".m_Array);\n");
						}
						else{
							containedType = qname.getLocalPart();
							writer.write("\t\t\tAxis_Delete_"+containedType+"(pTemp->"+attribs[i][0]+".m_Array, true, pTemp->"+attribs[i][0]+".m_Size);\n");
						}
					}else{
						writer.write("\t\t\tAxis_Delete_"+attribs[i][1]+"(pTemp->"+attribs[i][0]+", false, 0);\n");
					}
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
		for(int i = 1; i< attribs.length;i++){
			if(!CUtils.isSimpleType(attribs[i][1])){
				//to understand what happens here please refer to where the 
				//attribs[][] is created. (ParamWriter) 		
				if (attribs[i][5] != null){
					QName qname = new QName(attribs[i][4],attribs[i][5]);
					String containedType = null;
					if (CUtils.isSimpleType(qname)){
						containedType = CUtils.getclass4qname(qname);
						writer.write("\t\tfree(param->"+attribs[i][0]+".m_Array);\n");
					}
					else{
						containedType = qname.getLocalPart();
						writer.write("\t\tAxis_Delete_"+containedType+"(param->"+attribs[i][0]+".m_Array, true, param->"+attribs[i][0]+".m_Size);\n");
					}
				}else{
					writer.write("\t\tAxis_Delete_"+attribs[i][1]+"(param->"+attribs[i][0]+", false, 0);\n");
				}
			}
		}			
		writer.write("\t\tfree(param);\n");
		writer.write("\t}\n");
		writer.write("}\n");
	}	
}
