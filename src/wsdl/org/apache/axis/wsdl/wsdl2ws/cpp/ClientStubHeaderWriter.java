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
 * @author Srinath Perera(hemapani@openource.lk)
 * @author Susantha Kumara(susantha@opensource.lk, skumara@virtusa.com)
 */

package org.apache.axis.wsdl.wsdl2ws.cpp;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.Type;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ClientStubHeaderWriter extends HeaderFileWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public ClientStubHeaderWriter(WebServiceContext wscontext)throws WrapperFault{
		super(WrapperUtils.getClassNameFromFullyQualifiedName(wscontext.getSerInfo().getQualifiedServiceName()));
		this.wscontext = wscontext;
		this.methods = wscontext.getSerInfo().getMethods();
	}

	protected File getFilePath() throws WrapperFault {
		String targetOutputLocation = this.wscontext.getWrapInfo().getTargetOutputLocation();
		if(targetOutputLocation.endsWith("/"))
			targetOutputLocation = targetOutputLocation.substring(0, targetOutputLocation.length() - 1);
		new File(targetOutputLocation).mkdirs();
		String fileName = targetOutputLocation + "/" + classname + ".h";
		return new File(fileName);
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeAttributes()
	 */
	protected void writeAttributes() throws WrapperFault {
		try {
			writer.write("private:\n\tCall* m_pCall;\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeClassComment()
	 */
	protected void writeClassComment() throws WrapperFault {
		try{
			writer.write("/*\n");
			writer.write(" * This is the Client Stub Class genarated by the tool WSDL2Ws\n");
			writer.write(" * "+classname+".h: interface for the "+classname+"class.\n");
			writer.write(" *\n");
			writer.write(" */\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeConstructors()
	 */
	protected void writeConstructors() throws WrapperFault {
		try{
		writer.write("public:\n\t"+classname+"();\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write("public:\n\tvirtual ~"+classname+"();\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeMethods()
	 */
	protected void writeMethods() throws WrapperFault {
		MethodInfo minfo;
		boolean isSimpleType;
		try{
		  	writer.write("public: \n");	
		  	for(int i = 0; i < methods.size(); i++){
				minfo = (MethodInfo)this.methods.get(i);
				boolean isAllTreatedAsOutParams = false;
				int noOfOutParams = minfo.getOutputParameterTypes().size();
				//write return type
				if(0==noOfOutParams)
					writer.write("\tvoid ");
				else if(1==noOfOutParams){
					ParameterInfo returnParam = (ParameterInfo)minfo.getOutputParameterTypes().iterator().next();
					String outparam = returnParam.getLangName();
					writer.write("\t"+WrapperUtils.getClassNameFromParamInfoConsideringArrays(returnParam,wscontext)+" ");
				}
				else{
					isAllTreatedAsOutParams = true;
					writer.write("\tvoid ");
				}
			  //write return type
			  writer.write(minfo.getMethodname()+"(");
            
			  //write parameter names 
			  Iterator params = minfo.getInputParameterTypes().iterator();
			  if(params.hasNext()){
			  	  ParameterInfo fparam = (ParameterInfo)params.next();
				  writer.write(WrapperUtils.getClassNameFromParamInfoConsideringArrays(fparam,wscontext)+" Value"+0);
			  }
			  for(int j =1; params.hasNext();j++){
				  ParameterInfo nparam = (ParameterInfo)params.next();
				  writer.write(","+WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext)+" Value"+j);
			  }
			  if (isAllTreatedAsOutParams){
				  params = minfo.getOutputParameterTypes().iterator();
				  for(int j =0; params.hasNext();j++){
					  ParameterInfo nparam = (ParameterInfo)params.next();
					  writer.write(", AXIS_OUT_PARAM "+WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext)+" *OutValue"+j);
				  }
			  }			  
			  writer.write(");\n");
		  }
		  writer.write("\tint getStatus();\n");		  
		}catch (Exception e) {
			  e.printStackTrace();
			  throw new WrapperFault(e);
		}	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writePreprocssorStatements()
	 */
	protected void writePreprocssorStatements() throws WrapperFault {
		try{
			writer.write("#include <axis/client/Call.h>\n");
			Type atype;
			Iterator types = this.wscontext.getTypemap().getTypes().iterator();
			HashSet typeSet = new HashSet();
			String typeName = null;
			while(types.hasNext()){
				atype = (Type)types.next();
				if (atype.getLanguageSpecificName().startsWith(">")) continue;
				typeName = WrapperUtils.getLanguageTypeName4Type(atype);
				if (null != typeName) typeSet.add(typeName);
			}
			Iterator itr = typeSet.iterator();
			while(itr.hasNext())
			{
				writer.write("#include \""+itr.next().toString()+".h\"\n");
			}			
			writer.write("\n");
		}catch (IOException e) {
			e.printStackTrace();
			throw new WrapperFault(e);
		}
	}
	protected String getFileType()
	{
		return "ClientStub";	
	}
}
