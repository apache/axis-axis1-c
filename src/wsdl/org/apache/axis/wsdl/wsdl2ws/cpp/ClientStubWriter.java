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
 * @author Kanchana Welagedara(kanchana@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
	//import org.apache.axis.wsdl.wsdl2ws.info.WrapperInfo;
	
public class ClientStubWriter extends CPPClassWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public ClientStubWriter(WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()));
		this.wscontext = wscontext;
		this.methods = wscontext.getSerInfo().getMethods();
	}
	protected File getFilePath() throws WrapperFault {
		String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();
		String fileName = targetOutputLocation + "/" + classname + ".cpp";
		return new File(fileName);
	}
	protected void writeClassComment() throws WrapperFault {
			try{
				writer.write("///////////////////////////////////////////////////////////////////////\n");	
				writer.write("// This is the Client Stub implementation file genarated by WSDL2Ws tool.\n");
				writer.write("// "+classname+".cpp: implemtation for the "+classname+".\n");
				writer.write("//\n");
				writer.write("//////////////////////////////////////////////////////////////////////\n\n");
			}catch(IOException e){
				throw new WrapperFault(e);
			}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
		try{
		writer.write(classname+"::"+classname+"()\n{\n");
		writer.write("\tm_pCall = new Call();\n");
		//TODO get TransportURI from WrapInfo and check what the transport is and do the following line accordingly
		writer.write("\tm_pCall->SetProtocol(APTHTTP);\n");
		writer.write("\tm_pCall->SetHeader(\"SOAPAction\", \""+classname+"\");\n");
		writer.write("\tm_pCall->SetEndpointURI(\""+wscontext.getWrapInfo().getTargetEndpointURI()+"\");\n");
		writer.write("}\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write(classname+"::~"+classname+"()\n{\n\tdelete m_pCall;\n}\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		try{
			writer.write("\n//Methods corresponding to the web service methods\n");
			MethodInfo minfo;
			for (int i = 0; i < methods.size(); i++) {
				minfo = (MethodInfo)methods.get(i);
				this.writeMethodInWrapper(minfo.getMethodname(), minfo.getParameterTypes(),minfo.getReturnType());
				writer.write("\n");
			}
     
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
		try{
			writer.write("#include \""+classname+".h\"\n\n");
			writer.write("#include <axis/common/IWrapperSoapDeSerializer.h>\n");
			writer.write("#include <axis/common/IWrapperSoapSerializer.h>\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/**
	 * This method genarate methods that wraps the each method of the service
	 * @param methodName
	 * @param params
	 * @param outparam
	 * @throws IOException
	 */

	public void writeMethodInWrapper(String methodName, Collection params, ParameterInfo returntype) throws WrapperFault,IOException {
		Type retType = null;
		boolean returntypeissimple = false;
		boolean returntypeisarray = false;
		String outparamType = null;
		if (returntype != null)
			retType = wscontext.getTypemap().getType(returntype.getSchemaName());
		if (retType != null){
			outparamType = retType.getLanguageSpecificName();
			returntypeisarray = retType.isArray();
		}
		else if (returntype != null){
			outparamType = returntype.getLangName();
		}
		if (returntype != null)
			returntypeissimple = CPPUtils.isSimpleType(outparamType);
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method wrap the service method"+ methodName +"\n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		//method signature
		String paraTypeName;
		boolean typeisarray = false;
		boolean typeissimple = false;
		Type type;
		if (returntype == null){
			writer.write("void");
		}
		else if (returntypeissimple || returntypeisarray){
			writer.write(outparamType);	
		}else{
			writer.write(outparamType+"*");
		}
		writer.write(" "+classname+"::" + methodName + "(");
		ArrayList paramsB = (ArrayList)params;
		if (0 < paramsB.size()){
			type = wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(0)).getSchemaName());
			if (type != null){
				paraTypeName = type.getLanguageSpecificName();
				typeisarray = type.isArray();
			}
			else {
				paraTypeName = ((ParameterInfo)paramsB.get(0)).getLangName();
				typeisarray = false;
			}
			typeissimple = CPPUtils.isSimpleType(paraTypeName);
			if(typeisarray || typeissimple){
				writer.write(paraTypeName+" Value0");
			}else{
				writer.write(paraTypeName+"* Value0");
			}
			for (int i = 1; i < paramsB.size(); i++) {
				type = wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName());
				if (type != null){
					paraTypeName = type.getLanguageSpecificName();
					typeisarray = type.isArray();
				}
				else {
					paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
					typeisarray = false;
				}
				typeissimple = CPPUtils.isSimpleType(paraTypeName);
				if(typeisarray || typeissimple){
					writer.write(", "+paraTypeName+" Value"+i);
				}else{
					writer.write(", "+paraTypeName+"* Value"+i);
				}
			}
		}
		writer.write(")\n{\n");
		writer.write("\tint nStatus;\n");
		if (returntype != null){
			writer.write("\t");
			if(returntypeisarray){
				//for arrays
				writer.write(outparamType+" RetArray = {NULL, 0};\n");
			}else if(!returntypeissimple){
				writer.write(outparamType+"* pReturn = NULL;\n");
				//for complex types
			}else{
				//for simple types
				writer.write(outparamType+" Ret;\n");
				//TODO initialize return parameter appropriately.
			}
		}
		writer.write("\tif (SUCCESS != m_pCall->Initialize()) return ");
		if (returntype != null){
			writer.write((returntypeisarray?"RetArray":returntypeissimple?"Ret":"pReturn")+";\n\t");
		}
		else{
			writer.write(";\n\t");
		}
		writer.write("m_pCall->SetSOAPVersion(SOAP_VER_1_1);\n"); //TODO check which version is it really.
		writer.write("\tm_pCall->SetOperation(\""+methodName+"\", \""+ wscontext.getWrapInfo().getTargetNameSpaceOfWSDL() +"\");\n");
		for (int i = 0; i < paramsB.size(); i++) {
			type = wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName());
			if (type != null){
				paraTypeName = type.getLanguageSpecificName();
				typeisarray = type.isArray();
			}
			else {
				paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
				typeisarray = false;
			}
			typeissimple = CPPUtils.isSimpleType(paraTypeName);
			writer.write("\tm_pCall->AddParameter(");			
			if(typeisarray){
				//arrays
				QName qname = type.getTypNameForAttribName("item");
				String containedType = null;
				if (CPPUtils.isSimpleType(qname)){
					containedType = CPPUtils.getclass4qname(qname);
					writer.write("(Axis_Array*)(&Value"+i+"), "+CPPUtils.getXSDTypeForBasicType(containedType)+", \""+((ParameterInfo)paramsB.get(i)).getParamName()+"\"");					
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("(Axis_Array*)(&Value"+i+"), (void*)Axis_Serialize_"+containedType+", (void*)Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", Axis_TypeName_"+containedType+", Axis_URI_"+containedType+", \""+((ParameterInfo)paramsB.get(i)).getParamName()+"\"");
				}
			}else if(typeissimple){
				//for simple types	
				writer.write("Value"+i+", \"" + ((ParameterInfo)paramsB.get(i)).getParamName()+"\"");
			}else{
				//for complex types 
				writer.write("Value"+i+", Axis_Serialize_"+paraTypeName+", Axis_Delete_"+paraTypeName+", \"" + ((ParameterInfo)paramsB.get(i)).getParamName()+"\"");
			}
			writer.write(");\n");
		}
		if (returntype == null){
			writer.write("\tnStatus = m_pCall->Invoke();\n");
			writer.write("\tif (SUCCESS != nStatus)\n\t{\n");
			writer.write("\t\t//What to do ? . Throw an exception ??? \n\t}\n");
			writer.write("\tm_pCall->UnInitialize();\n");
		}
		else if (returntypeisarray){
			QName qname = retType.getTypNameForAttribName("item");
			String containedType = null;
			if (CPPUtils.isSimpleType(qname)){
				containedType = CPPUtils.getclass4qname(qname);
				writer.write("\tm_pCall->SetReturnType((Axis_Array*)(&RetArray), "+CPPUtils.getXSDTypeForBasicType(containedType)+");\n");
			}
			else{
				containedType = qname.getLocalPart();
				writer.write("\tm_pCall->SetReturnType((Axis_Array*)(&RetArray), (void*) Axis_DeSerialize_"+containedType);
				writer.write(", (void*) Axis_Create_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", Axis_TypeName_"+containedType+", Axis_URI_"+containedType+");\n");
			}
			writer.write("\tnStatus = m_pCall->Invoke();\n");
			writer.write("\tif (SUCCESS != nStatus)\n\t{\n");
			writer.write("\t\tdelete RetArray.m_Array;\n");
			writer.write("\t\tRetArray.m_Array = NULL;\n");
			writer.write("\t\tRetArray.m_Size = 0;\n\t}\n");
			writer.write("\tm_pCall->UnInitialize();\n");
			writer.write("\treturn RetArray;\n");
		}
		else if(returntypeissimple){
			writer.write("\tm_pCall->SetReturnType("+CPPUtils.getXSDTypeForBasicType(outparamType)+");\n");
			writer.write("\tnStatus = m_pCall->Invoke();\n");
			writer.write("\tif (SUCCESS == nStatus)\n\t{\n");
			writer.write("\t\tRet = m_pCall->GetResult()->"+CPPUtils.getParameterGetValueMethodName(outparamType)+";\n\t}\n");
			writer.write("\tm_pCall->UnInitialize();\n");
			writer.write("\treturn Ret;\n");
		}
		else{
			writer.write("\tm_pCall->SetReturnType((void*) Axis_DeSerialize_"+outparamType+", (void*) Axis_Create_"+outparamType+", (void*) Axis_Delete_"+outparamType+", Axis_TypeName_"+outparamType+", Axis_URI_"+outparamType+");\n");
			writer.write("\tnStatus = m_pCall->Invoke();\n");
			writer.write("\tif (SUCCESS == nStatus)\n\t{\n");
			writer.write("\t\tm_pCall->GetResult((void**)&pReturn);\n\t}\n");
			writer.write("\tm_pCall->UnInitialize();\n");
			writer.write("\treturn pReturn;\n");						
		}
		//write end of method
		writer.write("}\n");
	}
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.CPPClassWriter#writeGlobalCodes()
	 */
	protected void writeGlobalCodes() throws WrapperFault {
		Iterator types = wscontext.getTypemap().getTypes().iterator();
		String typeName;
		Type type;
		try {
			while(types.hasNext()){
				type = (Type)types.next();
				if (type.isArray()) continue;
				typeName = type.getLanguageSpecificName();
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
				writer.write("extern void* Axis_Create_"+typeName+"(bool bArray = false, int nSize=0);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer& pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}	
}





