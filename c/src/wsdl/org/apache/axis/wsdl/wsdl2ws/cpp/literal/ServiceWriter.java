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

package org.apache.axis.wsdl.wsdl2ws.cpp.literal;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;
import org.apache.axis.wsdl.wsdl2ws.info.MethodInfo;
import org.apache.axis.wsdl.wsdl2ws.info.ParameterInfo;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class ServiceWriter extends CPPClassWriter{
	private WebServiceContext wscontext;
	private ArrayList methods;	
	public ServiceWriter(WebServiceContext wscontext)throws WrapperFault{
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
			writer.write(" *This is the Service implementation CPP file genarated by theWSDL2Ws.\n");
			writer.write(" *		"+classname+".cpp: implemtation for the "+classname+".\n");
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
		writer.write("\n"+classname+"::"+classname+"()\n{\n");
		writer.write("}\n");
		}catch(IOException e){
			throw new WrapperFault(e);
		}
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.wsdl.wsdl2ws.cpp.HeaderFileWriter#writeDistructors()
	 */
	protected void writeDistructors() throws WrapperFault {
		try{
		writer.write("\n"+classname+"::~"+classname+"()\n{\n");
		writer.write("}\n");
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
		  	writer.write("\n");	
		  	for(int i = 0; i < methods.size(); i++){
				minfo = (MethodInfo)this.methods.get(i);
				boolean isAllTreatedAsOutParams = false;
				ParameterInfo returntype = null;
				int noOfOutParams = minfo.getOutputParameterTypes().size();
				if (0==noOfOutParams){
					returntype = null;
					writer.write("void ");
				}
				else if (1==noOfOutParams){
					returntype = (ParameterInfo)minfo.getOutputParameterTypes().iterator().next();
					String outparam = returntype.getLangName();
					writer.write(WrapperUtils.getClassNameFromParamInfoConsideringArrays(returntype,wscontext)+" ");
				}
				else{
				  	isAllTreatedAsOutParams = true;
				  	writer.write("void ");
				}
				writer.write(classname+"::"+minfo.getMethodname()+"(");
				//write parameter names 
				Iterator params = minfo.getInputParameterTypes().iterator();
				if(params.hasNext()){
					ParameterInfo fparam = (ParameterInfo)params.next();
					writer.write(WrapperUtils.getClassNameFromParamInfoConsideringArrays(fparam,wscontext)+" Value"+0);
				}
				for(int j =1; params.hasNext();j++){
					ParameterInfo nparam = (ParameterInfo)params.next();
					writer.write(", "+WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext)+" Value"+j);
				}
				if (isAllTreatedAsOutParams){
					params = minfo.getOutputParameterTypes().iterator();
					for(int j =0; params.hasNext();j++){
						ParameterInfo nparam = (ParameterInfo)params.next();
						writer.write(", AXIS_OUT_PARAM "+WrapperUtils.getClassNameFromParamInfoConsideringArrays(nparam,wscontext)+" *OutValue"+j);
					}
				}
				writer.write(")\n{\n}\n");
			}
		}catch (Exception e) {
			e.printStackTrace();
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

}
