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

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
import org.apache.axis.wsdl.wsdl2ws.CUtils;

public class WrapWriter extends CPPClassWriter{
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
				writer.write("/*\n");	
				writer.write(" * This is the Service implementation CPP file genarated by theWSDL2Ws.\n");
				writer.write(" * "+classname+".cpp: implemtation for the "+classname+".\n");
				writer.write(" * \n");
				writer.write(" */\n\n");
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
		writer.write("\tpWs = new "+CUtils.getWebServiceNameFromWrapperName(classname)+ "();\n");
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
		writer.write(classname+"::~"+classname+"()\n{\n\tdelete pWs;\n}\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		try{
			writer.write("/*implementation of WrapperClassHandler interface*/\n");
			
			writer.write("void "+classname+"::OnFault(IMessageData *pMsg)\n{\n}\n\n");
			writer.write("int "+classname+"::Init()\n{\n\treturn AXIS_SUCCESS;\n}\n\n");
			writer.write("int "+classname+"::Fini()\n{\n\treturn AXIS_SUCCESS;\n}\n\n");
			writeInvoke();
			writer.write("\n/*Methods corresponding to the web service methods*/\n");
			MethodInfo minfo;
			for (int i = 0; i < methods.size(); i++) {
				 minfo = (MethodInfo)methods.get(i);
				 this.writeMethodInWrapper(minfo);
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
		writer.write("\n/*\n");
		writer.write(" * This method invokes the right service method \n");
		writer.write(" */\n");
		writer.write("int "+classname+"::Invoke(IMessageData *mc)\n{\n");
		//msgdata.setSoapFault(new SOAPFault(new AxisFault()))
		writer.write("\tconst AxisChar *method = mc->GetOperationName();\n");
		//if no methods in the service simply return
		if (methods.size() == 0) {
			writer.write("}\n");
			return;
		}
		MethodInfo minfo = (MethodInfo)methods.get(0);
		//if conditions (if parts)		
		writer.write("\tif (0 == strcmp(method, \""+ minfo.getMethodname() +"\"))\n");
		writer.write("\t\treturn "+minfo.getMethodname()+"(mc);\n");
		//(else if parts)
		if (methods.size() > 1) {
			for (int i = 1; i < methods.size(); i++) {
				minfo = (MethodInfo)methods.get(i);
				writer.write("\telse if (0 == strcmp(method, \""+ minfo.getMethodname() +"\"))\n");
				writer.write("\t\treturn "+minfo.getMethodname()+"(mc);\n");
			}
		}
		//(else part)
		writer.write("\telse return AXIS_FAIL;\n");
		//end of method
		writer.write("}\n\n");
	}

	/**
	 * This method genarate methods that wraps the each method of the service
	 * @param methodName
	 * @param params
	 * @param outparam
	 * @throws IOException
	 */

	public void writeMethodInWrapper(MethodInfo minfo) throws WrapperFault,IOException {
		boolean isAllTreatedAsOutParams = false;
		ParameterInfo returntype = null;
		int noOfOutParams = minfo.getOutputParameterTypes().size();
		if (0==noOfOutParams){
			returntype = null;
		}
		else if (1==noOfOutParams){
			returntype = (ParameterInfo)minfo.getOutputParameterTypes().iterator().next();
		}
		else{
			isAllTreatedAsOutParams = true;
		}
		Collection params = minfo.getInputParameterTypes();
		String methodName = minfo.getMethodname();
		Type retType = null;
		Type type;
		String outparamType = null;
		boolean returntypeissimple = false;
		boolean returntypeisarray = false;
		if (returntype != null){
			retType = wscontext.getTypemap().getType(returntype.getSchemaName());
			if (retType != null){
				outparamType = retType.getLanguageSpecificName();
				returntypeisarray = retType.isArray();
			}
			else{
				outparamType = returntype.getLangName();
			}
			returntypeissimple = CUtils.isSimpleType(outparamType);
		}
		writer.write("\n/*\n");
		writer.write(" * This method wrap the service method \n");
		writer.write(" */\n");
		//method signature
		writer.write("int "+classname+"::" + methodName + "(IMessageData* mc)\n{\n");
		writer.write("\tint nStatus;\n");
		writer.write("\tIWrapperSoapSerializer *pIWSSZ = NULL;\n");
		writer.write("\tmc->GetSoapSerializer(&pIWSSZ);\n");
		writer.write("\tif (!pIWSSZ) return AXIS_FAIL;\n");
		writer.write("\tIWrapperSoapDeSerializer *pIWSDZ = NULL;\n");
		writer.write("\tmc->GetSoapDeSerializer(&pIWSDZ);\n");
		writer.write("\tif (!pIWSDZ) return AXIS_FAIL;\n");
		writer.write("\t/* check whether we have got correct message */\n");
		writer.write("\tif (AXIS_SUCCESS != pIWSDZ->CheckMessageBody(\""+minfo.getMethodname()+"\", \"\")) return AXIS_FAIL;\n");
		writer.write("\tpIWSSZ->CreateSoapMethod(\""+minfo.getMethodname()+"Response\", \"\");\n");
		//create and populate variables for each parameter
		String paraTypeName;
		String parameterName;
		String returnParamName;
		ArrayList paramsB = new ArrayList(params);
		for (int i = 0; i < paramsB.size(); i++) {
			paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
			parameterName = ((ParameterInfo)paramsB.get(i)).getParamName();
			if((CUtils.isSimpleType(((ParameterInfo)paramsB.get(i)).getLangName()))){
				//for simple types	
				writer.write("\t"+paraTypeName+" v"+i+" = pIWSDZ->"+CUtils.getParameterGetValueMethodName(paraTypeName, false)+"(\""+parameterName+"\",0);\n");
			}else if((type = this.wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName())) != null && type.isArray()){
				QName qname = WrapperUtils.getArrayType(type).getName();
				String containedType = null;
				if (CUtils.isSimpleType(qname)){
					containedType = CUtils.getclass4qname(qname);
					writer.write("\t"+paraTypeName+" v"+i+" = ("+CUtils.getBasicArrayNameforType(containedType)+"&)pIWSDZ->GetBasicArray("+CUtils.getXSDTypeForBasicType(containedType)+ ", \""+parameterName+"\",0);\n");
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("\t"+paraTypeName+" v"+i+" = ("+paraTypeName+"&)pIWSDZ->GetCmplxArray((void*)Axis_DeSerialize_"+containedType+ 
						"\n\t\t, (void*)Axis_Create_"+containedType+", (void*)Axis_Delete_"+containedType+
						"\n\t\t, (void*)Axis_GetSize_"+containedType+", \""+parameterName+"\", Axis_URI_"+containedType+");\n");
				}
			}else{
				//for complex types 
				writer.write("\t"+paraTypeName+" *v"+i+" = ("+paraTypeName+"*)pIWSDZ->GetCmplxObject((void*)Axis_DeSerialize_"+paraTypeName+
					"\n\t\t, (void*)Axis_Create_"+paraTypeName+", (void*)Axis_Delete_"+paraTypeName+
					"\n\t\t, \""+parameterName+"\", Axis_URI_"+paraTypeName+");\n");				
			}
		}
		writer.write("\tif (AXIS_SUCCESS != (nStatus = pIWSDZ->GetStatus())) return nStatus;\n");			
		// Multiples parameters so fill the methods prototype
		if ( isAllTreatedAsOutParams ) {
			ArrayList paramsC = (ArrayList)minfo.getOutputParameterTypes();
			for (int i = 0; i < paramsC.size(); i++) {
				type = wscontext.getTypemap().getType(((ParameterInfo)paramsC.get(i)).getSchemaName());
				writer.write("\t"+WrapperUtils.getClassNameFromParamInfoConsideringArrays((ParameterInfo)paramsC.get(i),wscontext)+" out"+i+";\n");
			}
		}
		if(returntype != null){				
			/* Invoke the service when return type not void */
			writer.write("\t"+outparamType+((returntypeisarray || returntypeissimple)?" ":" *")+ "ret = "+"pWs->"+methodName+"(");
			if (0<paramsB.size()){
				for (int i = 0; i <  paramsB.size() - 1; i++) {
					writer.write("v" + i + ",");
				}
				writer.write("v" + ( paramsB.size() - 1));
			}
			writer.write(");\n");
			/* set the result */
			if (returntypeissimple){
				writer.write("\treturn pIWSSZ->AddOutputParam(\""+methodName+"Return\", (void*)&ret, "+CUtils.getXSDTypeForBasicType(outparamType)+");\n");
			}else if(returntypeisarray){
				QName qname = WrapperUtils.getArrayType(retType).getName();
				String containedType = null;
				if (CUtils.isSimpleType(qname)){
					containedType = CUtils.getclass4qname(qname);
					writer.write("\treturn pIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&ret),"+CUtils.getXSDTypeForBasicType(containedType)+", \""+methodName+"Return\");\n");
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("\treturn pIWSSZ->AddOutputCmplxArrayParam((Axis_Array*)(&ret),"+ 
					"(void*) Axis_Serialize_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+methodName+"Return\", 0);\n");
				}
			}
			else{
				//complex type
				writer.write("\treturn pIWSSZ->AddOutputCmplxParam(ret, (void*)Axis_Serialize_"+outparamType+", (void*)Axis_Delete_"+outparamType+", \""+methodName+"Return\", 0);\n");
			}
		}else if (isAllTreatedAsOutParams){
			writer.write("\tpWs->" + methodName + "(");
			if (0<paramsB.size()){
				for (int i = 0; i <  paramsB.size(); i++) {
					writer.write("v" + i + ",");
				}
			}
			ArrayList paramsC = (ArrayList)minfo.getOutputParameterTypes();
			for (int i = 0; i < paramsC.size()-1; i++) {
				writer.write("&out" + i+",");
			}
			writer.write("&out" + (paramsC.size()-1));

			writer.write(");\n");
			paramsC = (ArrayList)minfo.getOutputParameterTypes();
			for (int i = 0; i < paramsC.size(); i++) {
				retType = wscontext.getTypemap().getType(((ParameterInfo)paramsC.get(i)).getSchemaName());
				if (retType != null){
					outparamType = retType.getLanguageSpecificName();
					returntypeisarray = retType.isArray();
				}
				else{
					outparamType = returntype.getLangName();
				}
				returntypeissimple = CUtils.isSimpleType(outparamType);
				returnParamName = ((ParameterInfo)paramsC.get(i)).getParamName();
				if (returntypeissimple){
					writer.write("\tpIWSSZ->AddOutputParam(\""+returnParamName+"\", (void*)&out"+i+", "+CUtils.getXSDTypeForBasicType(outparamType)+");\n");
				}else if(returntypeisarray){
					QName qname = WrapperUtils.getArrayType(retType).getName();
					String containedType = null;
					if (CUtils.isSimpleType(qname)){
						containedType = CUtils.getclass4qname(qname);
						writer.write("\tpIWSSZ->AddOutputBasicArrayParam((Axis_Array*)(&out"+i+"),"+CUtils.getXSDTypeForBasicType(containedType)+", \""+returnParamName+"\");\n");
					}
					else{
						containedType = qname.getLocalPart();
						writer.write("\tpIWSSZ->AddOutputCmplxArrayParam((Axis_Array*)(&out"+i+"),"+ 
						"(void*) Axis_Serialize_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+returnParamName+"\", 0);\n");
					}
				}
				else{
					//complex type
					writer.write("\tpIWSSZ->AddOutputCmplxParam(out"+i+", (void*)Axis_Serialize_"+outparamType+", (void*)Axis_Delete_"+outparamType+", \""+returnParamName+"\", 0);\n");
				}
			}			
			writer.write("\treturn AXIS_SUCCESS;\n");
		}else{//method does not return anything
			/* Invoke the service when return type is void */
	 		writer.write("\tpWs->" + methodName + "(");
			if (0<paramsB.size()){
				for (int i = 0; i <  paramsB.size() - 1; i++) {
					writer.write("v" + i + ",");
				}
				writer.write("v" + ( paramsB.size() - 1));
			}
			writer.write(");\n");
			writer.write("\treturn AXIS_SUCCESS;\n");
		}
		//write end of method
		writer.write("}\n");
	}
	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.CPPClassWriter#writeGlobalCodes()
	 */
	protected void writeGlobalCodes() throws WrapperFault {
		Iterator types = wscontext.getTypemap().getTypes().iterator();
		HashSet typeSet = new HashSet();
		String typeName;
		Type type;
		try {
			while(types.hasNext()){
				type = (Type)types.next();
				if (type.isArray()) continue;
				typeName = type.getLanguageSpecificName();
				if (typeName.startsWith(">")) continue;
				typeSet.add(typeName);
			}
			Iterator itr = typeSet.iterator();
			while(itr.hasNext())
			{
				typeName = itr.next().toString();
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
				writer.write("extern void* Axis_Create_"+typeName+"("+typeName+" *Obj, bool bArray = false, int nSize=0);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer& pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}
}
