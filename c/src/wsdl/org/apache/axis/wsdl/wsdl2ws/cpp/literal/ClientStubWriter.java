/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

 
/**
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 * @author Samisa Abeysinghe (sabeysinghe@virtusa.com)
 */

/*
 * Revision 1.1  2004/05/26 samisa
 * Added Stub base class into code generation
 */

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

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
			writer.write(classname+"::"+classname+"(const char* pcEndpointUri):Stub(pcEndpointUri)\n{\n");
		//writer.write(classname+"::"+classname+"()\n{\n");
		/*		
		writer.write("\tm_pCall = new Call();\n");
		//TODO get TransportURI from WrapInfo and check what the transport is and do the following line accordingly
		writer.write("\tm_pCall->setProtocol(APTHTTP);\n");
		writer.write("\tm_pCall->setEndpointURI(\""+wscontext.getWrapInfo().getTargetEndpointURI()+"\");\n");
		*/
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
		writer.write(classname+"::~"+classname+"()\n{\n}\n\n");//\tdelete m_pCall;\n}\n\n");
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
			writer.write("\tint "+classname+"::getStatus(){if ( m_pCall==NULL ) return AXIS_SUCCESS; else return m_pCall->getStatus();}\n");     
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
			if (retType.isSimpleType()){
				outparamType = CUtils.getclass4qname(retType.getBaseType());	
			}
			else{
				outparamType = retType.getLanguageSpecificName();
			}
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
				if (type.isSimpleType()){ //schema defined simpleType
					paraTypeName = 	CUtils.getclass4qname(type.getBaseType());
				}
				else{
					paraTypeName = type.getLanguageSpecificName();
				}
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
					if (type.isSimpleType()){ //schema defined simpleType
						paraTypeName = 	CUtils.getclass4qname(type.getBaseType());
					}
					else{
						paraTypeName = type.getLanguageSpecificName();
					}
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
		writer.write("\tif (AXIS_SUCCESS != m_pCall->initialize(CPP_DOC_PROVIDER, "+channelSecurityType+")) return ");
		if (returntype != null){
			writer.write((returntypeisarray?"RetArray":returntypeissimple?"Ret":"pReturn")+";\n\t");
		}
		else{
			writer.write(";\n");
		}
		writer.write("\tm_pCall->setTransportProperty(SOAPACTION_HEADER , \""+minfo.getSoapAction()+"\");\n");
		writer.write("\tm_pCall->setSOAPVersion(SOAP_VER_1_1);\n"); //TODO check which version is it really.
		writer.write("\tm_pCall->setOperation(\""+minfo.getInputMessage().getLocalPart()+"\", \""+ minfo.getInputMessage().getNamespaceURI()+"\");\n");
		//new calls from stub base
		writer.write("\tsetTransportProperties();\n");
		writer.write("\tsetSOAPHeaders();\n");
		for (int i = 0; i < paramsB.size(); i++) {
			type = wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName());
			if (type != null){
				if (type.isSimpleType()){//schema defined simpleType possibly with restrictions
					paraTypeName = CUtils.getclass4qname(type.getBaseType());
				}
				else{
					paraTypeName = type.getLanguageSpecificName();
				}
				typeisarray = type.isArray();
			}
			else {
				paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
				typeisarray = false;
			}
			typeissimple = CUtils.isSimpleType(paraTypeName);
			if(typeisarray){
				//arrays
				Type arrayType = WrapperUtils.getArrayType(type);
				QName qname = arrayType.getName();
				String containedType = null;
				if (CUtils.isSimpleType(qname)){
					containedType = CUtils.getclass4qname(qname);
					writer.write("\tm_pCall->addBasicArrayParameter(");			
					writer.write("(Axis_Array*)(&Value"+i+"), "+CUtils.getXSDTypeForBasicType(containedType)+", \""+((ParameterInfo)paramsB.get(i)).getElementName().getLocalPart()+"\"");					
				}
				else if (arrayType.isSimpleType()){//SimpleType in the schema 
					containedType = CUtils.getclass4qname(arrayType.getBaseType());
					writer.write("\tm_pCall->addBasicArrayParameter(");			
					writer.write("(Axis_Array*)(&Value"+i+"), "+CUtils.getXSDTypeForBasicType(containedType)+", \""+((ParameterInfo)paramsB.get(i)).getElementName().getLocalPart()+"\"");					
				}
				else{
					containedType = qname.getLocalPart();
					writer.write("\tm_pCall->addCmplxArrayParameter(");			
					writer.write("(Axis_Array*)(&Value"+i+"), (void*)Axis_Serialize_"+containedType+", (void*)Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+((ParameterInfo)paramsB.get(i)).getElementName().getLocalPart()+"\", Axis_URI_"+containedType);
				}
			}else if(typeissimple){
				//for simple types	
				writer.write("\tm_pCall->addParameter(");			
				writer.write("(void*)&Value"+i+", \"" + ((ParameterInfo)paramsB.get(i)).getElementName().getLocalPart()+"\", "+CUtils.getXSDTypeForBasicType(paraTypeName));
			}else{
				//for complex types 
				writer.write("\tm_pCall->addCmplxParameter(");			
				writer.write("Value"+i+", (void*)Axis_Serialize_"+paraTypeName+", (void*)Axis_Delete_"+paraTypeName+", \"" + ((ParameterInfo)paramsB.get(i)).getElementName().getLocalPart()+"\", Axis_URI_"+paraTypeName);
			}
			writer.write(");\n");
		}
		writer.write("\tif (AXIS_SUCCESS == m_pCall->invoke())\n\t{\n");
		if(minfo.getOutputMessage()!=null)
			writer.write("\t\tif(AXIS_SUCCESS == m_pCall->checkMessage(\""+minfo.getOutputMessage().getLocalPart()+"\", \""+minfo.getOutputMessage().getNamespaceURI()+"\"))\n\t\t{\n");
		if ( isAllTreatedAsOutParams) {
			String currentParamName;
			String currentParaType;
			for (int i = 0; i < paramsC.size(); i++) {
				ParameterInfo currentType = (ParameterInfo)paramsC.get(i);
				type = wscontext.getTypemap().getType(currentType.getSchemaName());
				if (type != null){
					if (type.isSimpleType()){
						currentParaType = CUtils.getclass4qname(type.getBaseType());
					}
					else{
						currentParaType = type.getLanguageSpecificName();
					}
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
					Type arrayType = WrapperUtils.getArrayType(type);
					QName qname = arrayType.getName();
					String containedType = null;
					if (CUtils.isSimpleType(qname)){
						containedType = CUtils.getclass4qname(qname);
						writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"&)m_pCall->getBasicArray("+CUtils.getXSDTypeForBasicType(containedType)+", \""+currentType.getElementName().getLocalPart()+"\", 0);\n");
					}
					else if (arrayType.isSimpleType()){//SimpleType in the schema 
						containedType = CUtils.getclass4qname(arrayType.getBaseType());
						writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"&)m_pCall->getBasicArray("+CUtils.getXSDTypeForBasicType(containedType)+", \""+currentType.getElementName().getLocalPart()+"\", 0);\n");
					}
					else{
						containedType = qname.getLocalPart();
						writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_"+containedType);
						writer.write(", (void*) Axis_Create_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+currentType.getElementName().getLocalPart()+"\", Axis_URI_"+containedType+");\n");
					}
				}
				else if(typeissimple){
				   writer.write("\t\t\t" + currentParamName + " = m_pCall->"+ CUtils.getParameterGetValueMethodName(currentParaType, false)+"(\""+currentType.getElementName().getLocalPart()+"\", 0);\n");
				}
				else{
				   writer.write("\t\t\t" + currentParamName + " = ("+currentParaType+"*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"+currentParaType+", (void*) Axis_Create_"+currentParaType+", (void*) Axis_Delete_"+currentParaType+",\""+currentType.getElementName().getLocalPart()+"\", 0);\n"); 
				}				
			}	
			writer.write("\t\t}\n");
			writer.write("\t}\n\tm_pCall->unInitialize();\n");	
		}
		else if (returntype == null){
			if(minfo.getOutputMessage()!=null)
				writer.write("\t\t\t/*not successful*/\n\t\t}\n");
			writer.write("\t}\n\tm_pCall->unInitialize();\n");
		}
		else if (returntypeisarray){
			QName qname = WrapperUtils.getArrayType(retType).getName();
			String containedType = null;
			if (CUtils.isSimpleType(qname)){
				containedType = CUtils.getclass4qname(qname);
				writer.write("\tRetArray = ("+outparamType+"&)m_pCall->getBasicArray("+CUtils.getXSDTypeForBasicType(containedType)+", \""+returntype.getElementName().getLocalPart()+"\", 0);\n\t\t}\n");
			}
			else{
				containedType = qname.getLocalPart();
				writer.write("\tRetArray = ("+outparamType+"&)m_pCall->getCmplxArray((void*) Axis_DeSerialize_"+containedType);
				writer.write(", (void*) Axis_Create_"+containedType+", (void*) Axis_Delete_"+containedType+", (void*) Axis_GetSize_"+containedType+", \""+returntype.getElementName().getLocalPart()+"\", Axis_URI_"+containedType+");\n\t\t}\n");
			}
			writer.write("\t}\n\tm_pCall->unInitialize();\n");
			writer.write("\treturn RetArray;\n");
		}
		else if(returntypeissimple){
			writer.write("\t\t\tRet = m_pCall->"+ CUtils.getParameterGetValueMethodName(outparamType, false)+"(\""+returntype.getElementName().getLocalPart()+"\", 0);\n\t\t}\n");
			writer.write("\t}\n\tm_pCall->unInitialize();\n");
			writer.write("\treturn Ret;\n");
		}
		else{
			writer.write("\t\t\tpReturn = ("+outparamType+"*)m_pCall->getCmplxObject((void*) Axis_DeSerialize_"+outparamType+", (void*) Axis_Create_"+outparamType+", (void*) Axis_Delete_"+outparamType+",\""+returntype.getElementName().getLocalPart()+"\", 0);\n\t\t}\n"); 
			writer.write("\t}\n\tm_pCall->unInitialize();\n");
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
				if (type.isSimpleType()) continue;
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





