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

package org.apache.axis.wsdl.wsdl2ws.c;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class WrapWriter extends CFileWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public WrapWriter(WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()+CUtils.WRAPPER_NAME_APPENDER));
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
				writer.write("//This is the Service implementation CPP file genarated by theWSDL2Ws.\n");
				writer.write("//		"+classname+".cpp: implemtation for the "+classname+".\n");
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
		writer.write(classname+"::~"+classname+"()\n{\n}\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		try{
			writer.write("//implementation of WrapperClassHandler interface\n");
			
			writer.write("void "+classname+"::OnFault(IMessageData *pMsg)\n{\n}\n\n");
			writer.write("int "+classname+"::Init()\n{\n\treturn SUCCESS;\n}\n\n");
			writer.write("int "+classname+"::Fini()\n{\n\treturn SUCCESS;\n}\n\n");
			writeInvoke();
			writeSetSoapMethod();
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
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}
	
	/**
	 * write the invoke method
	 * @throws IOException
	 */
	private void writeInvoke() throws IOException {
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method invokes the right service method \n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		writer.write("int "+classname+"::Invoke(IMessageData *mc)\n{\n");
		//msgdata.setSoapFault(new SOAPFault(new AxisFault()))
		writer.write("\tIWrapperSoapDeSerializer *pIWSDZ = NULL;\n");
		writer.write("\tmc->getSoapDeSerializer(&pIWSDZ);\n");
		writer.write("\tif (!pIWSDZ) return FAIL;\n");
		writer.write("\tconst AxisChar *method = pIWSDZ->GetMethodName();\n");
		//if no methods in the service simply return
		if (methods.size() == 0) {
			writer.write("}\n");
			return;
		}
		MethodInfo minfo = (MethodInfo)methods.get(0);
		//if conditions (if parts)		
		writer.write("\tif (0 == strcmp(method, \""+ minfo.getMethodname() +"\"))\n");
		writer.write("\t\treturn "+minfo.getMethodname()+CUtils.WRAPPER_METHOD_APPENDER+"(mc);\n");
		//(else if parts)
		if (methods.size() > 1) {
			for (int i = 1; i < methods.size(); i++) {
				minfo = (MethodInfo)methods.get(i);
				writer.write("\telse if (0 == strcmp(method, \""+ minfo.getMethodname() +"\"))\n");
				writer.write("\t\treturn "+minfo.getMethodname()+CUtils.WRAPPER_METHOD_APPENDER+"(mc);\n");
			}
		}
		//(else part)
		writer.write("\telse return FAIL;\n");
		//end of method
		writer.write("}\n\n");
	}

	private void writeSetSoapMethod() throws IOException {
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method sets the method element of the Serializer response \n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		writer.write("int "+classname+"::SetResponseMethod(IMessageData* mc, const AxisChar* name)\n{\n");
		writer.write("\tIWrapperSoapSerializer* pIWSSZ = NULL;\n");
		writer.write("\tmc->getSoapSerializer(&pIWSSZ);\n");
		writer.write("\tif (!pIWSSZ) return FAIL;\n");
		writer.write("\tISoapMethod* pMethod = pIWSSZ->createSoapMethod();\n");
		writer.write("\tpMethod->setLocalName(name);\n");
		writer.write("\tpMethod->setPrefix(pIWSSZ->getNewNamespacePrefix());\n");
		writer.write("\tpMethod->setUri(\"http://www.opensource.lk/"+CUtils.getWebServiceNameFromWrapperName(classname)+"\");\n");
		writer.write("\treturn SUCCESS;\n}\n");
	}
	/**
	 * This method genarate methods that wraps the each method of the service
	 * @param methodName
	 * @param params
	 * @param outparam
	 * @throws IOException
	 */

	public void writeMethodInWrapper(String methodName, Collection params, ParameterInfo returntype) throws WrapperFault,IOException {
		String outparam = returntype.getLangName();
		
		boolean isSimpleType = CUtils.isSimpleType(outparam);
		boolean isArray = returntype.getType().isArray();
		Type rettype;
		if ((rettype = this.wscontext.getTypemap().getType(returntype.getSchemaName())) != null ){
			if(isArray = rettype.isArray()){
				outparam = rettype.getTypNameForAttribName("item")+"[]";
			}
		}	
		
		//forward declaration for the C method.
		writer.write("\n//forward declaration for the c method "+methodName+" \n");
		//TODO forward declaration writing logic should be changed when arrays come into picture
		writer.write("extern \"C\" "+outparam+(isSimpleType?" ":" *")+methodName+"(");
		Iterator pms =  params.iterator();
		if(pms.hasNext()){
			String ptype = ((ParameterInfo)pms.next()).getLangName();
			writer.write((CUtils.isSimpleType(ptype)?ptype:ptype+"*"));
			while(pms.hasNext()){
				ptype = ((ParameterInfo)pms.next()).getLangName();
				writer.write(", " +(CUtils.isSimpleType(ptype)?ptype:ptype+"*"));
			}
			writer.write(");\n");
		}
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method wrap the service method \n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		//method signature
		writer.write("int "+classname+"::" + methodName + CUtils.WRAPPER_METHOD_APPENDER + "(IMessageData* mc)\n{\n");
		writer.write("\tIWrapperSoapSerializer *pIWSSZ = NULL;\n");
		writer.write("\tmc->getSoapSerializer(&pIWSSZ);\n");
		writer.write("\tif (!pIWSSZ) return FAIL;\n");
		writer.write("\tIWrapperSoapDeSerializer *pIWSDZ = NULL;\n");
		writer.write("\tmc->getSoapDeSerializer(&pIWSDZ);\n");
		writer.write("\tif (!pIWSDZ) return FAIL;\n");
		writer.write("\tSetResponseMethod(mc, \""+methodName+"Response\");\n");

		//create the param classes for each parameter
		String paraTypeName;
		ArrayList paramsB = new ArrayList(params);
		Iterator p =  params.iterator();
		for (int i = 0; i < paramsB.size(); i++) {
			paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
			Type type;
			writer.write("\tIParam *param"+i+"= pIWSDZ->GetParam();\n");			
			if((CUtils.isSimpleType(((ParameterInfo)paramsB.get(i)).getLangName()))){
				//for simple types	
				if ("char*".equals(paraTypeName)){
					writer.write("\t"+paraTypeName+" v"+i+" = strdup(param->"+CUtils.getParameterGetValueMethodName(paraTypeName)+");\n");
				}
				else {
					writer.write("\t"+paraTypeName+" v"+i+" = param->"+CUtils.getParameterGetValueMethodName(paraTypeName)+";\n");
				}
					 
			}else if((type = this.wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName())) != null 
						&& type.isArray()){
            	//TODO for Array types				
				//String ContentparaTypeName = WrapperUtils.getParameterName4ParamInfo((ParameterInfo)paramsB.get(i),wscontext);
			
			}else{
				//for complex types 
				writer.write("\t"+paraTypeName+" *v"+i+" = new "+paraTypeName+"();\n");
				writer.write("\tparam"+i+"->SetUserType(v"+i+", (AXIS_DESERIALIZE_FUNCT)Axis_DeSerialize_"+paraTypeName+", (AXIS_OBJECT_DELETE_FUNCT)Axis_Delete_"+paraTypeName+");\n");
				writer.write("\tpIWSDZ->Deserialize(param"+i+",0);\n");
			}
		}
			
		if(!(outparam == null ||outparam.equals("void"))){				
			/* Invoke the service when return type not void */
			writer.write("\t"+outparam+(isSimpleType?" ":" *")+ "ret = "+methodName+"(");
			for (int i = 0; i <  paramsB.size() - 1; i++)
					writer.write("v" + i + ",");
			writer.write("v" + ( paramsB.size() - 1));					
			writer.write(");\n");					
			/* set the result */
			if (isSimpleType){
				writer.write("\tIParam *pRetParam = pIWSSZ->AddOutputParam(ret);\n");
			}else if(isArray){
				//TODO array type
			}
			else{
				//complex type
				writer.write("\tIParam *pRetParam = pIWSSZ->AddOutputParam(ret, (void*)Axis_Serialize_"+outparam+", (void*)Axis_Delete_"+outparam+");\n");
			}
			writer.write("\tpRetParam->SetName(\""+methodName+"Return\");\n");
			writer.write("\treturn SUCCESS;\n");
		}else{//method does not return anything
			/* Invoke the service when return type is void */
	 		writer.write("\t" + methodName+"(");
			for (int i = 0; i <  paramsB.size() - 1; i++) {
				writer.write("v" + i + ",");
			}
			writer.write("v" + ( paramsB.size() - 1));
			writer.write(")\n");
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
		try {
			while(types.hasNext()){
				typeName = ((Type)types.next()).getLanguageSpecificName();
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
				writer.write("extern void* Axis_Create_"+typeName+"(bool bArray = false, int nSize=0);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer& pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"("+typeName+"* param);\n\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}
}
