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
		String fileName = targetOutputLocation + "/" + classname + ".c";
		return new File(fileName);
	}

	protected void writeClassComment() throws WrapperFault {
		try{
			writer.write("/*\n");	
			writer.write(" * This is the Wrapper implementation file genarated by WSDL2Ws tool\n");
			writer.write(" *\n");
			writer.write(" */\n\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		try{
			writer.write("/*implementation of BasicHandler interface*/\n");		
			writer.write("void AXISCALL "+classname+"_OnFault(void*p, void *pMsg){\n}\n\n");
			writer.write("int AXISCALL "+classname+"_Init(void*p){\n\treturn AXIS_SUCCESS;\n}\n\n");
			writer.write("int AXISCALL "+classname+"_Fini(void*p){\n\treturn AXIS_SUCCESS;\n}\n\n");
			writer.write("int AXISCALL "+classname+"_GetType(void*p){\n\treturn WEBSERVICE_HANDLER;\n}\n\n");
			writer.write("AXIS_BINDING_STYLE AXISCALL "+classname+"_GetBindingStyle(void*p){\n\treturn DOC_LITERAL;\n}\n\n");
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
			writer.write("#include \""+classname+".h\"\n");
			//As there is no service header file for C the header files for types should be included here itself
			Type atype;
			Iterator types = this.wscontext.getTypemap().getTypes().iterator();
			while(types.hasNext()){
				atype = (Type)types.next();
				if (atype.getLanguageSpecificName().startsWith(">")) continue;
				writer.write("#include \""+atype.getLanguageSpecificName()+".h\"\n");
			}
			writer.write("\n");
		}
		catch(IOException e){
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
		writer.write("int AXISCALL "+classname+"_Invoke(void*p, void *pMsg){\n");
		writer.write("\tIMessageData* mc = (IMessageData*)pMsg;\n");
		writer.write("\tconst AxisChar* method = 0;\n");
		writer.write("\tIWrapperSoapDeSerializer DZ = {0,0};\n");
		writer.write("\tIWrapperSoapSerializer SZ = {0,0};\n");
		writer.write("\tmethod = mc->_functions->GetOperationName(mc->_object);\n");
		writer.write("\tmc->_functions->GetSoapSerializer(mc->_object, &SZ);\n");
		writer.write("\tmc->_functions->GetSoapDeSerializer(mc->_object, &DZ);\n");		
		//if no methods in the service simply return
		if (methods.size() == 0) {
			writer.write("}\n");
			return;
		}
		MethodInfo minfo = (MethodInfo)methods.get(0);
		//if conditions (if parts)		
		writer.write("\tif (0 == strcmp(method, \""+ minfo.getMethodname() +"\"))\n");
		writer.write("\t\treturn "+minfo.getMethodname()+CUtils.WRAPPER_METHOD_APPENDER+"(DZ, SZ);\n");
		//(else if parts)
		if (methods.size() > 1) {
			for (int i = 1; i < methods.size(); i++) {
				minfo = (MethodInfo)methods.get(i);
				writer.write("\telse if (0 == strcmp(method, \""+ minfo.getMethodname() +"\"))\n");
				writer.write("\t\treturn "+minfo.getMethodname()+CUtils.WRAPPER_METHOD_APPENDER+"(DZ, SZ);\n");
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
			//TODO make all outparams when there are more than one return params
			throw new WrapperFault("WSDL2Ws does not still handle more than one return parameters");
		}
		String methodName = minfo.getMethodname();
		Collection params = minfo.getInputParameterTypes();
		Type retType = null;
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
		String paraTypeName;
		ArrayList paramsB = new ArrayList(params);
		Type type;

		writer.write("\n/*forward declaration for the c method "+methodName+" */\n");
		//TODO forward declaration writing logic should be changed when arrays come into picture
		if (returntype == null){
			writer.write("extern void "+methodName+"(");
		}
		else{ 
			writer.write("extern "+outparamType+((returntypeissimple||returntypeisarray)?" ":" *")+methodName+"(");
		}

		for (int i = 0; i < paramsB.size(); i++) {
			if (i>0) writer.write(",");
			paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
			if((CUtils.isSimpleType(paraTypeName))){
				//for simple types	
				writer.write(paraTypeName);
			}else if((type = this.wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName())) != null && type.isArray()){
				writer.write(paraTypeName);
			}else{
				writer.write(paraTypeName+"*");
			}
		}
		writer.write(");\n");
		writer.write("\n/*\n");
		writer.write(" * This method wrap the service method \n");
		writer.write(" */\n");
		//method signature
		writer.write("int "+ methodName + CUtils.WRAPPER_METHOD_APPENDER+ "(IWrapperSoapDeSerializer DZ, IWrapperSoapSerializer SZ)\n{\n");
		writer.write("\tint nStatus;\n");
		boolean aretherearrayparams = false;
		String parameterName;
		String elementName;
		for (int i = 0; i < paramsB.size(); i++) {
			paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
			if((CUtils.isSimpleType(((ParameterInfo)paramsB.get(i)).getLangName()))){
				//for simple types	
				writer.write("\t"+paraTypeName+" v"+i+";\n");
			}else if((type = this.wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName())) != null && type.isArray()){
				//for arrays
				aretherearrayparams = true;
				writer.write("\t"+paraTypeName+" v"+i+";\n"); 
			}else{
				//for complex types
				writer.write("\t"+paraTypeName+" *v"+i+";\n");				
			}
		}
		if(returntype != null){
			writer.write("\t"+outparamType+((returntypeisarray || returntypeissimple)?" ":" *")+ "ret;\n");
		}
		if (aretherearrayparams){
			writer.write("\tAxis_Array array;\n");
		}
		writer.write("\tif (AXIS_SUCCESS != DZ._functions->CheckMessageBody(DZ._object, \""+minfo.getInputMessage().getLocalPart()+"\", \""+minfo.getInputMessage().getNamespaceURI()+"\")) return AXIS_FAIL;\n");
		writer.write("\tpSZ->_functions->CreateSoapMethod(SZ._object, \""+minfo.getOutputMessage().getLocalPart()+"\", \""+minfo.getOutputMessage().getNamespaceURI()+"\");\n");
		//create and populate variables for each parameter
		for (int i = 0; i < paramsB.size(); i++) {
			paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
			parameterName = ((ParameterInfo)paramsB.get(i)).getParamName();
			elementName = ((ParameterInfo)paramsB.get(i)).getElementName().getLocalPart();
			if((CUtils.isSimpleType(((ParameterInfo)paramsB.get(i)).getLangName()))){
				//for simple types	
				writer.write("\tv"+i+" = DZ._functions->"+CUtils.getParameterGetValueMethodName(paraTypeName, false)+"(DZ._object,\""+elementName+"\", 0);\n");
			}else if((type = this.wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName())) != null && type.isArray()){
				QName qname = WrapperUtils.getArrayType(type).getName();
				String containedType = null;
				if (CUtils.isSimpleType(qname)){
					containedType = CUtils.getclass4qname(qname);
					writer.write("\tarray = DZ._functions->GetBasicArray(DZ._object, "+CUtils.getXSDTypeForBasicType(containedType)+"\""+elementName+"\", 0);\n");
					writer.write("\tmemcpy(&v"+i+", &array, sizeof(Axis_Array));\n");
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("\tarray = DZ._functions->GetCmplxArray(DZ._object, (void*)Axis_DeSerialize_"+containedType+ 
						"\n\t\t, (void*)Axis_Create_"+containedType+", (void*)Axis_Delete_"+containedType+
						"\n\t\t, (void*)Axis_GetSize_"+containedType+", \""+elementName+"\", Axis_URI_"+containedType+");\n");
					writer.write("\tmemcpy(&v"+i+", &array, sizeof(Axis_Array));\n");
				}
			}else{
				//for complex types 
				writer.write("\tv"+i+" = ("+paraTypeName+"*)DZ._functions->GetCmplxObject(DZ._object, (void*)Axis_DeSerialize_"+paraTypeName+
					"\n\t\t, (void*)Axis_Create_"+paraTypeName+", (void*)Axis_Delete_"+paraTypeName+
					"\n\t\t,\""+elementName+"\", Axis_URI_"+paraTypeName+");\n");
			}
		}
		writer.write("\tif (AXIS_SUCCESS != (nStatus = DZ._functions->GetStatus(DZ._object))) return nStatus;\n");				
		if(returntype != null){
			String returnParamName = returntype.getElementName().getLocalPart();
			/* Invoke the service when return type not void */
			writer.write("\tret = "+methodName+"(");
			if (0<paramsB.size()){
				for (int i = 0; i <  paramsB.size() - 1; i++) {
					writer.write("v" + i + ",");
				}
				writer.write("v" + ( paramsB.size() - 1));
			}
			writer.write(");\n");
			/* set the result */
			if (returntypeissimple){
				writer.write("\treturn pSZ->_functions->AddOutputParam(SZ._object, \""+returnParamName+"\", (void*)&ret, "+CUtils.getXSDTypeForBasicType(outparamType)+");\n");
			}else if(returntypeisarray){
				QName qname = WrapperUtils.getArrayType(retType).getName();
				String containedType = null;
				if (CUtils.isSimpleType(qname)){
					containedType = CUtils.getclass4qname(qname);
					writer.write("\treturn pSZ->_functions->AddOutputBasicArrayParam(SZ._object, (Axis_Array*)(&ret),"+CUtils.getXSDTypeForBasicType(containedType)+", \""+returnParamName+"\");\n");
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("\treturn pSZ->_functions->AddOutputCmplxArrayParam(SZ._object, (Axis_Array*)(&ret), (void*) Axis_Serialize_"+containedType
					+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+returnParamName+"\", Axis_URI_"+containedType+");\n");
				}
			}
			else{
				//complex type
				writer.write("\treturn pSZ->_functions->AddOutputCmplxParam(SZ._object, ret, (void*)Axis_Serialize_"+outparamType+", (void*)Axis_Delete_"+outparamType+", \""+returnParamName+"\", Axis_URI_"+outparamType+");\n");
			}
		}else{//method does not return anything
			/* Invoke the service when return type is void */
			writer.write("\t" + methodName + "(");
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
				writer.write("extern void* Axis_Create_"+typeName+"("+typeName+" *Obj, bool bArray, int nSize);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray, int nSize);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}
}
