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
import java.util.HashSet;
import java.util.Iterator;

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
		HashSet typeSet = new HashSet();
		String typeName;
		for(int i = 0; i< attribs.length;i++){
			if(!CPPUtils.isSimpleType(attribs[i][1])){
				Type memtype = wscontext.getTypemap().getType(type.getTypNameForAttribName(attribs[i][0]));
				if (memtype.isArray()){
					QName qname = memtype.getTypNameForAttribName("item");
					if (CPPUtils.isSimpleType(qname)) continue; //no wrapper methods for basic types
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
			writer.write("extern void* Axis_Create_"+typeName+"(bool bArray = false, int nSize=0);\n");
			writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
			writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer& pSZ, bool bArray = false);\n");
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
				writer.write("\tpSZ << pSZ.SerializeBasicType(\""+attribs[i][0]+"\", param->"+attribs[i][0]+", "+ CPPUtils.getXSDTypeForBasicType(attribs[i][1])+");\n");
			}else if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()){
				//if Array
				QName qname = t.getTypNameForAttribName("item");
				String arrayType = null;
				if (CPPUtils.isSimpleType(qname)){
					arrayType = CPPUtils.getclass4qname(qname);
					writer.write("\tpSZ.SerializeArray((Axis_Array*)(&param->"+attribs[i][0]+"),"+CPPUtils.getXSDTypeForBasicType(arrayType)+", \""+attribs[i][0]+"\");\n"); 
				}
				else{
					arrayType = qname.getLocalPart();
					writer.write("\tpSZ.SerializeArray((Axis_Array*)(&param->"+attribs[i][0]+"),\n"); 
					writer.write("\t\t(void*) Axis_Serialize_"+arrayType+", (void*) Axis_Delete_"+arrayType+", (void*) Axis_GetSize_"+arrayType+",\n"); 
					writer.write("\t\tAxis_TypeName_"+arrayType+", Axis_URI_"+arrayType+", \""+attribs[i][0]+"\");\n");
				}
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
		
		writer.write("int Axis_DeSerialize_"+classname+"("+classname+"* param, IWrapperSoapDeSerializer *pIWSDZ)\n{\n");
		if (attribs.length == 0) {
			 //nothing to print if this is simple type we have inbuild types
			 System.out.println("possible error calss with no attributes....................");
			 return;
		 }
		for(int i = 0; i< attribs.length;i++){
			if(CPPUtils.isSimpleType(attribs[i][1])){
				//if symple type
				writer.write("\tparam->"+attribs[i][0]+" = pIWSDZ->"+CPPUtils.getParameterGetValueMethodName(attribs[i][1])+";\n");
			}else if((t = wscontext.getTypemap().getType(new QName(attribs[i][2],attribs[i][3])))!= null && t.isArray()){
				//if Array
				QName qname = t.getTypNameForAttribName("item");
				String arrayType = null;
				if (CPPUtils.isSimpleType(qname)){
					arrayType = CPPUtils.getclass4qname(qname);
					writer.write("\tparam->"+attribs[i][0]+".m_Size = pIWSDZ->GetArraySize();\n");
					writer.write("\tif (param->"+attribs[i][0]+".m_Size < 1) return FAIL;\n");
					writer.write("\tparam->"+attribs[i][0]+".m_Array = new "+arrayType+"[param->"+attribs[i][0]+".m_Size];\n");
					writer.write("\tif (SUCCESS != pIWSDZ->GetArray((Axis_Array*)(&param->"+attribs[i][0]+"), "+CPPUtils.getXSDTypeForBasicType(arrayType)+")) return FAIL;\n");
				}
				else{
					arrayType = qname.getLocalPart();
					writer.write("\tparam->"+attribs[i][0]+" = ("+attribs[i][1]+"&)pIWSDZ->GetArray((AXIS_DESERIALIZE_FUNCT)Axis_DeSerialize_"+arrayType+ 
						"\n\t\t, (AXIS_OBJECT_CREATE_FUNCT)Axis_Create_"+arrayType+", (AXIS_OBJECT_DELETE_FUNCT)Axis_Delete_"+arrayType+
						"\n\t\t, (AXIS_OBJECT_SIZE_FUNCT)Axis_GetSize_"+arrayType+", Axis_TypeName_"+arrayType+", Axis_URI_"+arrayType+");\n");
				}
			}else{
				//if complex type
				writer.write("\tparam->"+attribs[i][0]+" = ("+attribs[i][1]+"*)pIWSDZ->GetObject((AXIS_DESERIALIZE_FUNCT)Axis_DeSerialize_"+attribs[i][1]+
					"\n\t\t, (AXIS_OBJECT_CREATE_FUNCT)Axis_Create_"+attribs[i][1]+", (AXIS_OBJECT_DELETE_FUNCT)Axis_Delete_"+attribs[i][1]+
					"\n\t\t, Axis_TypeName_"+attribs[i][1]+", Axis_URI_"+attribs[i][1]+");\n");				
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
						QName qname = memtype.getTypNameForAttribName("item");
						String containedType = null;
						if (CPPUtils.isSimpleType(qname)){
							containedType = CPPUtils.getclass4qname(qname);
							writer.write("\t\t\tdelete [] (("+containedType+"*)pTemp->"+attribs[i][0]+".m_Array);\n");
						}
						else{
							containedType = qname.getLocalPart();
							writer.write("\t\t\tAxis_Delete_"+containedType+"(pTemp->"+attribs[i][0]+".m_Array, true, pTemp->"+attribs[i][0]+".m_Size);\n");
						}
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
					QName qname = memtype.getTypNameForAttribName("item");
					String containedType = null;
					if (CPPUtils.isSimpleType(qname)){
						containedType = CPPUtils.getclass4qname(qname);
						writer.write("\t\tdelete [] (("+containedType+"*)param->"+attribs[i][0]+".m_Array);\n");
					}
					else{
						containedType = qname.getLocalPart();
						writer.write("\t\tAxis_Delete_"+containedType+"(param->"+attribs[i][0]+".m_Array, true, param->"+attribs[i][0]+".m_Size);\n");
					}
				}else{
					writer.write("\t\tAxis_Delete_"+attribs[i][1]+"(param->"+attribs[i][0]+");\n");
				}
			}
		}			
		writer.write("\t\tdelete param;\n");
		writer.write("\t}\n");
		writer.write("}\n");
	}	
}
