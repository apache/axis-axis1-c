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
				/*
				 * Needed for self referenced  array.
				* <xsd:complexType name="Type1">
				*	<xsd:sequence>
				*		<xsd:element name="followings" maxOccurs="unbounded" minOccurs="0" type="tns:Type1" />
				*		<xsd:element name="kind" type="xsd:string" />
				*		<xsd:element name="index" type="xsd:int" />
				*	</xsd:sequence>
				*	<xsd:attribute name="att_kind" type="tns:Kind" />
				* </xsd:complexType>
				*/				
				typeName = itr.next().toString();
				if ( ! typeName.equals(type.getName().getLocalPart())) {
					writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
					writer.write("extern void* Axis_Create_"+typeName+"("+typeName+"* pObj, bool bArray, int nSize);\n");
					writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray, int nSize);\n");
					writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray);\n");
					writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");
				} else {
					writer.write("int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
					writer.write("void* Axis_Create_"+typeName+"(void* pObj, bool bArray, int nSize);\n");
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
			System.out.println("possible error class with no attributes....................");
			writer.write("\tpSZ->_functions->Serialize(SZ._object, \">\", 0);\n");
			writer.write("\treturn AXIS_SUCCESS;\n");
			writer.write("}\n\n");				 
			return;
		 }
		String arrayType = null;
		writer.write("\t/* first serialize attributes if any*/\n");
		for(int i = 0; i< attributeParamCount;i++){
			if(attribs[i].isArray() || !(attribs[i].isSimpleType())){
				throw new WrapperFault("Error : an attribute is not basic type");
			}
			else{
				if (attribs[i].isOptional()){
					writer.write("\tif (0 != param->"+attribs[i].getParamName()+")\n");
					writer.write("\tpSZ->_functions->SerializeAsAttribute(pSZ->_object, \""+attribs[i].getParamName()+"\", 0, (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				}
				else{
					writer.write("\tpSZ->_functions->SerializeAsAttribute(pSZ->_object, \""+attribs[i].getParamName()+"\", 0, (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
				}
			}
		}
		writer.write("\tpSZ->_functions->Serialize(pSZ->_object, \">\");\n");
		writer.write("\t/* then serialize elements if any*/\n");
		for(int i = attributeParamCount; i< attribs.length;i++){
			if(attribs[i].isArray()){
				//if Array
				arrayType = attribs[i].getTypeName();
				if (attribs[i].isSimpleType()){
					writer.write("\tpSZ->_functions->SerializeBasicArray(pSZ->_object, (Axis_Array*)(&param->"+attribs[i].getParamName()+"),"+CUtils.getXSDTypeForBasicType(arrayType)+", \""+attribs[i].getElementName().getLocalPart()+"\");\n"); 
				}
				else{
					writer.write("\tpSZ->_functions->SerializeCmplxArray(pSZ->_object, (Axis_Array*)(&param->"+attribs[i].getParamName()+"),\n"); 
					writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n"); 
					writer.write("\t\t\""+attribs[i].getElementName().getLocalPart()+"\", Axis_URI_"+arrayType+");\n");
				}
			}
			else if (attribs[i].isSimpleType()){
				writer.write("\tpSZ->_functions->SerializeAsElement(pSZ->_object, \""+attribs[i].getElementName().getLocalPart()+"\", (void*)&(param->"+attribs[i].getParamName()+"), "+ CUtils.getXSDTypeForBasicType(attribs[i].getTypeName())+");\n");
			}else{
				//if complex type
				writer.write("\tpSZ->_functions->Serialize(pSZ->_object, \"<"+attribs[i].getParamName()+"\");\n");
				writer.write("\tAxis_Serialize_"+attribs[i].getTypeName()+"(param->"+attribs[i].getParamName()+", pSZ->_object, false);\n");
				writer.write("\tpSZ->_functions->Serialize(pSZ->_object, \"</"+attribs[i].getParamName()+">\");\n");
			}			
		}
		writer.write("\treturn AXIS_SUCCESS;\n");
		writer.write("}\n\n");
	
	}
	private void writeDeSerializeGlobalMethod()throws IOException,WrapperFault{	
		writer.write("/**\n");
		writer.write(" * This static method deserialize a "+classname+" type of object\n");
		writer.write(" */\n");
		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer *pDZ)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error calss with no attributes....................");
			 return;
		}
		boolean aretherearrayparams = false;
		for(int i = 0; i< attribs.length;i++){
			if(attribs[i].isArray()){
				aretherearrayparams = true; break;
			}
		}
		if (aretherearrayparams){
			writer.write("\tAxis_Array array;\n");	
		}
		writer.write("\t/* first deserialize attributes if any*/\n");
		for(int i = 0; i< attribs.length;i++){ 
			if (i == attributeParamCount)writer.write("\t/* then deserialize elements if any*/\n");
			if(attribs[i].isArray()){
				//if Array
				String containedType = attribs[i].getTypeName();
				if (attribs[i].isSimpleType()){
					writer.write("\tarray = pDZ->_functions->GetBasicArray(pDZ->_object, "+CUtils.getXSDTypeForBasicType(containedType)+ ", \""+attribs[i].getElementName().getLocalPart()+"\",0);\n");
					writer.write("\tmemcpy(&(param->"+attribs[i].getParamName()+"), &array, sizeof(Axis_Array));\n");
				}
				else{
					writer.write("\tarray = pDZ->_functions->GetCmplxArray(pDZ->_object, (void*)Axis_DeSerialize_"+containedType+ 
						"\n\t\t, (void*)Axis_Create_"+containedType+", (void*)Axis_Delete_"+containedType+
						"\n\t\t, (void*)Axis_GetSize_"+containedType+", \""+attribs[i].getElementName().getLocalPart()+"\", Axis_URI_"+containedType+");\n");
					writer.write("\tmemcpy(&(param->"+attribs[i].getParamName()+"), &array, sizeof(Axis_Array));\n");
				}
			}else if(attribs[i].isSimpleType()){
				//if symple type
				if(attribs[i].isAttribute()){
					if (attribs[i].isOptional()){
						//TODO
					}else{
						writer.write("\tparam->"+attribs[i].getParamName()+" = pDZ->_functions->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), true)+"(pDZ->_object, \""+attribs[i].getParamName()+"\", 0);\n");
					}
				}
				else{
					writer.write("\tparam->"+attribs[i].getParamName()+" = pDZ->_functions->"+CUtils.getParameterGetValueMethodName(attribs[i].getTypeName(), false)+"(pDZ->_object, \""+attribs[i].getElementName().getLocalPart()+"\", 0);\n");
				}
			}else{
				//if complex type
				writer.write("\tparam->"+attribs[i].getParamName()+" = ("+attribs[i].getTypeName()+"*)pDZ->_functions->GetCmplxObject(pDZ->_object, (void*)Axis_DeSerialize_"+attribs[i].getTypeName()+
					"\n\t\t, (void*)Axis_Create_"+attribs[i].getTypeName()+", (void*)Axis_Delete_"+attribs[i].getTypeName()+
					"\n\t\t, \""+attribs[i].getElementName().getLocalPart()+"\", Axis_URI_"+attribs[i].getTypeName()+");\n");
			}		
		}
		writer.write("\treturn pDZ->_functions->GetStatus(pDZ->_object);\n");
		writer.write("}\n");
	}
	
	private void writeCreateGlobalMethod()throws IOException{
		writer.write("void* Axis_Create_"+classname+"(void* pObj, bool bArray, int nSize)\n{\n");
		writer.write("\tif (bArray && (nSize > 0))\n\t{\n");
		writer.write("\t\tif (pObj)\n\t{\n");
		writer.write("\t\t\tpObj = realloc(pObj, sizeof("+classname+")*nSize);\n");
		writer.write("\t\t\tmemset(pObj+sizeof("+classname+")*nSize/2, 0, sizeof("+classname+")*nSize/2);\n");
		writer.write("\t\t}\n\t\telse\n\t\t{\n");
		writer.write("\t\t\tpObj = malloc(sizeof("+classname+")*nSize);\n");
		writer.write("\t\t\tmemset(pObj, 0, sizeof("+classname+")*nSize);\n\t\t}\n");
		writer.write("\t\treturn pObj;\n");
		writer.write("\t}\n\telse\n\t{\n");
		writer.write("\t\tpObj = malloc(sizeof("+classname+"));\n");
		writer.write("\t\tmemset(pObj, 0, sizeof("+classname+"));\n\t}\n");
		writer.write("\treturn pObj;\n}\n");
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
	protected void writeRestrictionCheckerFunction() throws WrapperFault {
		try{
			writer.write("int Check_Restrictions_"+classname+"("+classname+" value)\n");
			writer.write("{\n");
			//TODO write code to check the restrictions
			writer.write("}\n");					
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}	
}
