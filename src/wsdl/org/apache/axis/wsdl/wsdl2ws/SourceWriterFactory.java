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

package org.apache.axis.wsdl.wsdl2ws;

import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;
/**
 * Genarate a SourceFactory depend on the reqirements. 
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
public class SourceWriterFactory {
	public static SourceWriter createSourceWriter(int genaratorType,WebServiceContext wscontext)throws WrapperFault{
		//write deployment or undeployment wsdd files 
		if (genaratorType == WrapperConstants.GENERATOR_DEPLOYMENT){
			return new DeploymentWriter(wscontext);
		}
		else if (genaratorType == WrapperConstants.GENERATOR_UNDEPLOYMENT){
			return new UndeploymentWriter(wscontext);			
		}
		if("rpc".equals(wscontext.getWrapInfo().getWrapperStyle())){
			//C++
			if(genaratorType == WrapperConstants.GENERATOR_PARAM_CPP_ALL)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.AllParamWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.WrapWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_HPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.WrapHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_SERVICE_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.ServiceWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_SERVICE_HPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.ServiceHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLASSLOADER_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.ClassLoader(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_HPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.ClientStubHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.ClientStubWriter(wscontext);			
			else if(genaratorType == WrapperConstants.GENERATOR_EXCEPTION_ALL) // nithya
						return new org.apache.axis.wsdl.wsdl2ws.cpp.AllExceptionWriter(wscontext);	
			//C
			else if(genaratorType == WrapperConstants.GENERATOR_PARAM_C_ALL)
				return new org.apache.axis.wsdl.wsdl2ws.c.AllParamWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.WrapWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_H)
				return new org.apache.axis.wsdl.wsdl2ws.c.WrapHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_SERVICE_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.ServiceWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLASSLOADER_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.ClassLoader(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_H)
				return new org.apache.axis.wsdl.wsdl2ws.c.ClientStubHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.ClientStubWriter(wscontext);	
			throw new WrapperFault("Source writer type not found");		
		}		
		else if ("document".equals(wscontext.getWrapInfo().getWrapperStyle())){
			if(genaratorType == WrapperConstants.GENERATOR_PARAM_CPP_ALL)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.AllParamWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.WrapWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_HPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.WrapHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_SERVICE_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.ServiceWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_SERVICE_HPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.ServiceHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLASSLOADER_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.ClassLoader(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_HPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.ClientStubHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_CPP)
				return new org.apache.axis.wsdl.wsdl2ws.cpp.literal.ClientStubWriter(wscontext);	
			else if(genaratorType == WrapperConstants.GENERATOR_EXCEPTION_ALL) // nithya
				return new org.apache.axis.wsdl.wsdl2ws.cpp.AllExceptionWriter(wscontext);
			
			//C
			else if(genaratorType == WrapperConstants.GENERATOR_PARAM_C_ALL)
				return new org.apache.axis.wsdl.wsdl2ws.c.literal.AllParamWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.literal.WrapWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_WRAPPER_H)
				return new org.apache.axis.wsdl.wsdl2ws.c.literal.WrapHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_SERVICE_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.literal.ServiceWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLASSLOADER_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.literal.ClassLoader(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_H)
				return new org.apache.axis.wsdl.wsdl2ws.c.literal.ClientStubHeaderWriter(wscontext);
			else if(genaratorType == WrapperConstants.GENERATOR_CLIENT_STUB_C)
				return new org.apache.axis.wsdl.wsdl2ws.c.literal.ClientStubWriter(wscontext);	
			throw new WrapperFault("Source writer type not found");				
		}
		throw new WrapperFault("Source writer type not found");				
	}
}
