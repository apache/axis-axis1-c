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

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.IOException;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
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
		writer.write("static const AxisChar* Axis_URI_"+classname+" = \""+type.getName().getNamespaceURI()+"\";\n");
		writer.write("static const AxisChar* Axis_TypeName_"+classname+" = \""+type.getName().getLocalPart()+"\";\n\n");
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
		writer.write("/////////////////////////////////////////////////////////////////////////////\n");
		writer.write("// This static method gives the size of "+classname+" type of object\n");
		writer.write("//////////////////////////////////////////////////////////////////////\n");
		writer.write("int Axis_GetSize_"+classname+"()\n{\n\treturn sizeof("+classname+");\n}\n");
	}
	private void writeSerializeGlobalMethod()throws IOException{
		Type t;
		writer.write("/////////////////////////////////////////////////////////////////////////////\n");
		writer.write("// This static method serialize a "+classname+" type of object\n");
		writer.write("//////////////////////////////////////////////////////////////////////\n");
		
		writer.write("int Axis_Serialize_"+classname+"("+classname+"* param, IWrapperSoapSerializer& pSZ, bool bArray = false)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error calss with no attributes....................");
			 return;
		 }
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		writer.write("\t	pSZ << \"<\" << Axis_TypeName_"+classname+" << \">\";\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t	const AxisChar* sPrefix = pSZ.getNewNamespacePrefix();\n");
		writer.write("\t	pSZ << \"<\" << Axis_TypeName_"+classname+" << \" xsi:type=\\\"\" << sPrefix <<\":\"\n"); 
		writer.write("\t		<< Axis_TypeName_"+classname+" << \"\\\" xmlns:\" << sPrefix << \"=\\\"\"\n"); 
		writer.write("\t		<< Axis_URI_"+classname+" << \"\\\">\";\n");
		writer.write("\t}\n\n");
		for(int i = 0; i< attribs.length;i++){
			if(CPPUtils.isSimpleType(attribs[i][1])){
				//if simple type
				writer.write("\tpSZ << pSZ.SerializeBasicType(\""+attribs[i][0]+"\", param->"+attribs[i][0]+");\n");
			}else if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()){
				//if Array
				String arrayType = t.getTypNameForAttribName("item").getLocalPart();
				writer.write("\tpSZ.SerializeArray((Axis_Array*)(&param->"+attribs[i][0]+"),\n"); 
				writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n"); 
				writer.write("\t\tAxis_TypeName_"+arrayType+", Axis_URI_"+arrayType+", \""+attribs[i][0]+"\");\n");				
			}else{
				//if complex type
				writer.write("\tAxis_Serialize_"+attribs[i][1]+"(param->"+attribs[i][0]+", pSZ);\n");
			}
		}
		writer.write("\n\tpSZ << \"</\" << Axis_TypeName_"+classname+" << \">\";\n");
		writer.write("\treturn SUCCESS;\n");
		writer.write("}\n\n");
	
	}
	private void writeDeSerializeGlobalMethod()throws IOException{	
		Type t;
		writer.write("/////////////////////////////////////////////////////////////////////////////\n");
		writer.write("// This static method deserialize a "+classname+" type of object\n");
		writer.write("//////////////////////////////////////////////////////////////////////\n");
		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer *pDZ)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error calss with no attributes....................");
			 return;
		 }
		writer.write("\tIParam* pParam;\n");		 
		if(CPPUtils.isSimpleType(attribs[0][1])){
			//if symple type
			writer.write("\tparam->"+attribs[0][0]+" = pDZ->GetParam()->"+CPPUtils.getParameterGetValueMethodName(attribs[0][1])+";\n");
		}else if((t = wscontext.getTypemap().getType(new QName(attribs[0][2],attribs[0][3])))!= null && t.isArray()){
			//if Array
		}else{
			//if complex type
			writer.write("\tpParam = pDZ->GetParam(); //get head param and do any validation if necessary.\n");
			writer.write("\tparam->"+attribs[0][0]+" = new "+attribs[0][1]+"();\n");
			writer.write("\tAxis_DeSerialize_"+attribs[0][1]+"(param->"+attribs[0][0]+", pDZ);\n");
		}
		for(int i = 1; i< attribs.length;i++){
			if(CPPUtils.isSimpleType(attribs[i][1])){
				//if symple type
				writer.write("\tparam->"+attribs[i][0]+" = pDZ->GetParam()->"+CPPUtils.getParameterGetValueMethodName(attribs[i][1])+";\n");
			}else if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()){
				//if Array
				String arrayType = t.getTypNameForAttribName("item").getLocalPart();
				writer.write("\tpParam = pIWSDZ->GetParam(); //now we know that this is an array.\n");
				writer.write("\tparam->"+attribs[i][0]+".m_Size = pParam->GetArraySize();\n");
				writer.write("\tif (param->"+attribs[i][0]+".m_Size > 0)\n");
				writer.write("\t\tparam->"+attribs[i][0]+".m_Array = new "+arrayType+"[param->"+attribs[i][0]+".m_Size];\n");
				writer.write("\telse\n\t\treturn FAIL; //CF_ZERO_ARRAY_SIZE_ERROR\n");
				writer.write("\tpParam->SetArrayElements((void*)(param->"+attribs[i][0]+".m_Array), (AXIS_DESERIALIZE_FUNCT)Axis_DeSerialize_"+arrayType+", (AXIS_OBJECT_DELETE_FUNCT)Axis_Delete_"+arrayType+", (AXIS_OBJECT_SIZE_FUNCT)Axis_GetSize_"+arrayType+");\n");
				writer.write("\tpIWSDZ->Deserialize(pParam,0);\n");				
			}else{
				//if complex type
				writer.write("\tpParam = pDZ->GetParam(); //get head param and do any validation if necessary.\n");
				writer.write("\tparam->"+attribs[i][0]+" = new "+attribs[i][1]+"();\n");
				writer.write("\tAxis_DeSerialize_"+attribs[i][1]+"(param->"+attribs[i][0]+ ", pDZ);\n");
			}		
		}
		writer.write("\treturn SUCCESS;\n");
		writer.write("}\n");
	}
	
	private void writeCreateGlobalMethod()throws IOException{
		writer.write("void* Axis_Create_"+classname+"(bool bArray = false, int nSize=0)\n{\n");
		writer.write("\tif (bArray && (nSize > 0))\n\t\treturn new "+classname+"[nSize];\n");
		writer.write("\telse\n\t\treturn new "+classname+";\n}\n\n");	
	}
	
	private void writeDeleteGlobalMethod()throws IOException{
		writer.write("/////////////////////////////////////////////////////////////////////////////\n");
		writer.write("// This static method delete a "+classname+" type of object\n");
		writer.write("//////////////////////////////////////////////////////////////////////\n");
		
		writer.write("void Axis_Delete_"+classname+"("+classname+"* param, bool bArray = false, int nSize=0)\n");
		writer.write("{\n");
		writer.write("\tif (bArray)\n");
		writer.write("\t{\n");
		boolean hasComplexType = false;
		for(int i = 0; i< attribs.length;i++){
			if(!CPPUtils.isSimpleType(attribs[i][1])){
				hasComplexType = true; break;
			}
		}			
		if (hasComplexType){ 
			writer.write("\t\t//delete any pointer members or array members of this struct here\n");
			writer.write("\t\t"+classname+"* pTemp = param;\n");
			writer.write("\t\tfor (int x=0; x<nSize; x++)\n");
			writer.write("\t\t{\n");
			for(int i = 0; i< attribs.length;i++){
				if(!CPPUtils.isSimpleType(attribs[i][1])){ //this can be either an array or complex type
					Type memtype = wscontext.getTypemap().getType(type.getTypNameForAttribName(attribs[i][0]));
					if (memtype.isArray()){
						String containedType = memtype.getTypNameForAttribName("item").getLocalPart();
						writer.write("\t\t\tAxis_Delete_"+containedType+"(pTemp->"+attribs[i][0]+".m_Array, true, pTemp->"+attribs[i][0]+".m_Size);\n");
					}else{
						writer.write("\t\t\tAxis_Delete_"+attribs[i][1]+"(pTemp->"+attribs[i][0]+");\n");
					}
				}
			}			
			writer.write("\t\t\tpTemp++;\n");
			writer.write("\t\t}\n");
		}
		writer.write("\t\tdelete [] param;\n");
		writer.write("\t}\n");
		writer.write("\telse\n");
		writer.write("\t{\n");
		writer.write("\t\t//delete any pointer members or array members of this struct here\n");
		for(int i = 1; i< attribs.length;i++){
			if(!CPPUtils.isSimpleType(attribs[i][1])){
				Type memtype = wscontext.getTypemap().getType(type.getTypNameForAttribName(attribs[i][0]));
				if (memtype.isArray()){
					String containedType = memtype.getTypNameForAttribName("item").getLocalPart();
					writer.write("\t\tAxis_Delete_"+containedType+"(p->"+attribs[i][0]+".m_Array, true, p->"+attribs[i][0]+".m_Size);\n");
				}else{
					writer.write("\t\tAxis_Delete_"+attribs[i][1]+"(p->"+attribs[i][0]+");\n");
				}
			}
		}			
		writer.write("\t\tdelete param;\n");
		writer.write("\t}\n");
		writer.write("}\n");
	}	
}
