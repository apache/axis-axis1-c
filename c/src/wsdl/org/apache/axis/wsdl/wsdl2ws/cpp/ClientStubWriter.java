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

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.CUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
	
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
				writer.write("/*\n");	
				writer.write(" * This is the Client Stub implementation file genarated by WSDL2Ws tool.\n");
				writer.write(" * "+classname+".cpp: implemtation for the "+classname+".\n");
				writer.write(" *\n");
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
		writer.write("\tm_pCall = new Call();\n");
		//TODO get TransportURI from WrapInfo and check what the transport is and do the following line accordingly
		writer.write("\tm_pCall->SetProtocol(APTHTTP);\n");
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
			writer.write("#include <axis/server/AxisWrapperAPI.h>\n\n");
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
			returntypeissimple = CUtils.isSimpleType(outparamType);
		writer.write("\n/*\n");
		writer.write(" * This method wrap the service method"+ methodName +"\n");
		writer.write(" */\n");
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
			typeissimple = CUtils.isSimpleType(paraTypeName);
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
				typeissimple = CUtils.isSimpleType(paraTypeName);
				if(typeisarray || typeissimple){
					writer.write(", "+paraTypeName+" Value"+i);
				}else{
					writer.write(", "+paraTypeName+"* Value"+i);
				}
			}
		}
		// Multiples parameters so fill the methods prototype
		ArrayList paramsC = (ArrayList)minfo.getOutputParameterTypes();
		if ( isAllTreatedAsOutParams ) {
			String currentParaTypeName;
			for (int i = 0; i < paramsC.size(); i++) {
				type = wscontext.getTypemap().getType(((ParameterInfo)paramsC.get(i)).getSchemaName());
				writer.write(", AXIS_OUT_PARAM  "+WrapperUtils.getClassNameFromParamInfoConsideringArrays((ParameterInfo)paramsC.get(i),wscontext)+" *OutValue"+i);
			}
		}

		writer.write(")\n{\n");
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
		String channelSecurityType = (WrapperConstants.CHANNEL_SECURITY_SSL.equals(wscontext.getWrapInfo().getChannelSecurity()))?
										"SSL_CHANNEL" : "NORMAL_CHANNEL";
		writer.write("\tif (AXIS_SUCCESS != m_pCall->Initialize(CPP_RPC_PROVIDER, "+channelSecurityType +")) return ");
		if (returntype != null){
			writer.write((returntypeisarray?"RetArray":returntypeissimple?"Ret":"pReturn")+";\n");
		}
		else{
			writer.write(";\n");
		}
		writer.write("\tm_pCall->SetTransportProperty(SOAPACTION_HEADER , \""+minfo.getSoapAction()+"\");\n");
		writer.write("\tm_pCall->SetSOAPVersion(SOAP_VER_1_1);\n"); //TODO check which version is it really.
		writer.write("\tm_pCall->SetOperation(\""+minfo.getMethodname()+"\", \"\");\n");
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
			typeissimple = CUtils.isSimpleType(paraTypeName);
			if(typeisarray){
				//arrays
				QName qname = WrapperUtils.getArrayType(type).getName();
				String containedType = null;
				if (CUtils.isSimpleType(qname)){
					containedType = CUtils.getclass4qname(qname);
					writer.write("\tm_pCall->AddBasicArrayParameter(");			
					writer.write("(Axis_Array*)(&Value"+i+"), "+CUtils.getXSDTypeForBasicType(containedType)+", \""+((ParameterInfo)paramsB.get(i)).getParamName()+"\"");					
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("\tm_pCall->AddCmplxArrayParameter(");			
					writer.write("(Axis_Array*)(&Value"+i+"), (void*)Axis_Serialize_"+containedType+", (void*)Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+((ParameterInfo)paramsB.get(i)).getParamName()+"\", Axis_URI_"+containedType);
				}
			}else if(typeissimple){
				//for simple types	
				writer.write("\tm_pCall->AddParameter(");			
				writer.write("(void*)&Value"+i+", \"" + ((ParameterInfo)paramsB.get(i)).getParamName()+"\", "+CUtils.getXSDTypeForBasicType(paraTypeName));
			}else{
				//for complex types 
				writer.write("\tm_pCall->AddCmplxParameter(");			
				writer.write("Value"+i+", (void*)Axis_Serialize_"+paraTypeName+", (void*)Axis_Delete_"+paraTypeName+", \"" + ((ParameterInfo)paramsB.get(i)).getParamName()+"\", Axis_URI_"+paraTypeName);
			}
			writer.write(");\n");
		}
		writer.write("\tif (AXIS_SUCCESS == m_pCall->Invoke())\n\t{\n");
		writer.write("\t\tif(AXIS_SUCCESS == m_pCall->CheckMessage(\""+minfo.getMethodname()+"Response\", \"\"))\n\t\t{\n");
		if ( isAllTreatedAsOutParams) {
			String currentParamName;
			String currentParaType;
			for (int i = 0; i < paramsC.size(); i++) {
				ParameterInfo currentType = (ParameterInfo)paramsC.get(i);
				type = wscontext.getTypemap().getType(currentType.getSchemaName());
				if (type != null){
					currentParaType = type.getLanguageSpecificName();
					typeisarray = type.isArray();
				}
				else {
					currentParaType = ((ParameterInfo)paramsC.get(i)).getLangName();
					typeisarray = false;
				}
				typeissimple = CUtils.isSimpleType(currentParaType);
								
				currentParamName = "*OutValue"+i;
				// Some code need to be merged as we have some duplicated in coding here.
				if (typeisarray){
					QName qname = WrapperUtils.getArrayType(type).getName();
					String containedType = null;
					if (CUtils.isSimpleType(qname)){
						containedType = CUtils.getclass4qname(qname);
						writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"&)m_pCall->GetBasicArray("+CUtils.getXSDTypeForBasicType(containedType)+", \""+currentType.getParamName()+"\", 0);\n");
					}
					else{
						containedType = qname.getLocalPart();
						writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"&)m_pCall->GetCmplxArray((void*) Axis_DeSerialize_"+containedType);
						writer.write(", (void*) Axis_Create_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+currentType.getParamName()+"\", Axis_URI_"+containedType+");\n");
					}
				}
				else if(typeissimple){
				   writer.write("\t\t\t" + currentParamName + " = m_pCall->"+ CUtils.getParameterGetValueMethodName(currentParaType, false)+"(\""+currentType.getParamName()+"\", 0);\n");
				}
				else{
				   writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_"+currentParaType+", (void*) Axis_Create_"+currentParaType+", (void*) Axis_Delete_"+currentParaType+",\""+currentType.getParamName()+"\", 0);\n"); 
				}				
			}	
			writer.write("\t\t}\n");
			writer.write("\t}\n\tm_pCall->UnInitialize();\n");	
		}
		else if (returntype == null){
			writer.write("\t\t\t/*not successful*/\n\t\t}\n");
			writer.write("\t}\n\tm_pCall->UnInitialize();\n");
		}
		else if (returntypeisarray){
			QName qname = WrapperUtils.getArrayType(retType).getName();
			String containedType = null;
			if (CUtils.isSimpleType(qname)){
				containedType = CUtils.getclass4qname(qname);
				writer.write("\tRetArray = ("+outparamType+"&)m_pCall->GetBasicArray("+CUtils.getXSDTypeForBasicType(containedType)+", \""+returntype.getParamName()+"\", 0);\n\t\t}\n");
			}
			else{
				containedType = qname.getLocalPart();
				writer.write("\tRetArray = ("+outparamType+"&)m_pCall->GetCmplxArray((void*) Axis_DeSerialize_"+containedType);
				writer.write(", (void*) Axis_Create_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+returntype.getParamName()+"\", Axis_URI_"+containedType+");\n\t\t}\n");
			}
			writer.write("\t}\n\tm_pCall->UnInitialize();\n");
			writer.write("\treturn RetArray;\n");
		}
		else if(returntypeissimple){
			writer.write("\t\t\tRet = m_pCall->"+ CUtils.getParameterGetValueMethodName(outparamType, false)+"(\""+returntype.getParamName()+"\", 0);\n\t\t}\n");
			writer.write("\t}\n\tm_pCall->UnInitialize();\n");
			writer.write("\treturn Ret;\n");
		}
		else{
			writer.write("\t\t\tpReturn = ("+outparamType+"*)m_pCall->GetCmplxObject((void*) Axis_DeSerialize_"+outparamType+", (void*) Axis_Create_"+outparamType+", (void*) Axis_Delete_"+outparamType+",\""+returntype.getParamName()+"\", 0);\n\t\t}\n"); 
			writer.write("\t}\n\tm_pCall->UnInitialize();\n");
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
			writer.write("bool CallBase::bInitialized;\n" +
				"CallFunctions CallBase::ms_VFtable;\n");
			Iterator itr = typeSet.iterator();
			while(itr.hasNext())
			{
				typeName = itr.next().toString();
				writer.write("extern int Axis_DeSerialize_"+typeName+"("+typeName+"* param, IWrapperSoapDeSerializer *pDZ);\n");
				writer.write("extern void* Axis_Create_"+typeName+"("+typeName+" *Obj, bool bArray = false, int nSize=0);\n");
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer* pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"();\n\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}	
}





