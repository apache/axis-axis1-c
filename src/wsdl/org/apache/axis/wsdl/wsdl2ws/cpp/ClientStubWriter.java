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
			writer.write("#include <GDefine.h>\n");
			writer.write("#include <IWrapperSoapDeSerializer.h>\n");
			writer.write("#include <IWrapperSoapSerializer.h>\n");
			writer.write("#include <IParam.h>\n\n");
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
		String outparam = returntype.getLangName();
		writer.write("\n/////////////////////////////////////////////////////////////////\n");
		writer.write("// This method wrap the service method"+ methodName +"\n");
		writer.write("//////////////////////////////////////////////////////////////////\n");
		//method signature
		String paraTypeName;
		Type type;
		ArrayList paramsB = (ArrayList)params;
		writer.write(outparam + " "+classname+"::" + methodName + "(");
		if (0 < paramsB.size()){
			paraTypeName = ((ParameterInfo)paramsB.get(0)).getLangName();
			writer.write(paraTypeName + (CPPUtils.isSimpleType(paraTypeName) ? " Value0":"* pValue0"));
			for (int i = 1; i < paramsB.size(); i++) {
				paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
				writer.write(", "+paraTypeName + (CPPUtils.isSimpleType(paraTypeName) ? " Value":"* pValue")+i);
			}
		}
		writer.write(")\n{\n");
		writer.write("\tint nStatus;\n");
		writer.write("\tif (SUCCESS != m_pCall->Initialize())\n\t");
		writer.write("\treturn "+ (CPPUtils.isSimpleType(outparam)?"0":"NULL") +";\n");
		//TODO handle returning appropriate type in case of string, char* and struct tm.
		writer.write("\tm_pCall->SetOperation(\""+methodName+"\", \""+ wscontext.getWrapInfo().getTargetNameSpaceOfWSDL() +"\");\n");
		for (int i = 0; i < paramsB.size(); i++) {
			paraTypeName = ((ParameterInfo)paramsB.get(i)).getLangName();
			writer.write("\tm_pCall->AddParameter(");			
			if(CPPUtils.isSimpleType(paraTypeName)){
				//for simple types	
				writer.write("Value"+i+", \"" + ((ParameterInfo)paramsB.get(i)).getParamName()+"\"");
			//}else if((type = this.wscontext.getTypemap().getType(((ParameterInfo)paramsB.get(i)).getSchemaName())) != null 
			//			&& type.isArray()){
				//TODO for Array types				
				//String ContentparaTypeName = WrapperUtils.getParameterName4ParamInfo((ParameterInfo)paramsB.get(i),wscontext);
			
			}else{
				//for complex types 
				writer.write("pValue"+i+", Axis_Serialize_"+paraTypeName+", Axis_Delete_"+paraTypeName+", \"" + ((ParameterInfo)paramsB.get(i)).getParamName()+"\"");
			}
			writer.write(");\n");
		}
		if (CPPUtils.isSimpleType(outparam)){
			writer.write("\t"+outparam+" RetValue;\n");
			writer.write("\tm_pCall->SetReturnType(XSD_UNKNOWN);\n");
			writer.write("\tnStatus = m_pCall->Invoke();\n");
			writer.write("\tif (SUCCESS == nStatus)\n\t{\n");
			writer.write("\t\tRetValue = m_pCall->GetResult()."+CPPUtils.getUnionMemberForBasicType(outparam)+";\n\t}\n");
			writer.write("\tm_pCall->UnInitialize();\n");
			writer.write("\treturn RetValue;\n");
		}
		//else if (){
		//TODO handle if return type is array type
		//}
		else{
			writer.write("\t"+outparam+"* pRetValue = new "+outparam+ "();\n");
			writer.write("\tm_pCall->SetReturnType(pRetValue, Axis_DeSerialize_"+outparam+", Axis_Delete_"+outparam+", Axis_TypeName_"+outparam+", Axis_URI_"+outparam+");\n");
			writer.write("\tnStatus = m_pCall->Invoke();\n");
			writer.write("\tif (SUCCESS != nStatus)\n\t{\n");
			writer.write("\t\tdelete pRetValue;\n\t\tpRetValue = NULL;\n\t}\n");
			writer.write("\tm_pCall->UnInitialize();\n");
			writer.write("\treturn pRetValue;\n");			
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
				writer.write("extern void Axis_Delete_"+typeName+"("+typeName+"* param, bool bArray = false, int nSize=0);\n");
				writer.write("extern int Axis_Serialize_"+typeName+"("+typeName+"* param, IWrapperSoapSerializer& pSZ, bool bArray = false);\n");
				writer.write("extern int Axis_GetSize_"+typeName+"("+typeName+"* param);\n\n");
				//Local name and the URI for the type
				writer.write("//Local name and the URI for the type\n");
				writer.write("static const AxisChar* Axis_URI_"+typeName+" = " + "\"http://www.opensource.lk/" + typeName + "\"\n");
				writer.write("static const AxisChar* Axis_TypeName_"+typeName+" = \"" +typeName+"\";\n\n");
			}
		} catch (IOException e) {
			throw new WrapperFault(e);
		}
	}	
}





