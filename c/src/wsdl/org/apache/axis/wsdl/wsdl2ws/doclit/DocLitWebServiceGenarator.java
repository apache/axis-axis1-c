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
 * @author Srinath Perera(hemapani
 */

package org.apache.axis.wsdl.wsdl2ws.doclit;

import org.apache.axis.wsdl.wsdl2ws.Genarator;
import org.apache.axis.wsdl.wsdl2ws.WebServiceGenarator;
import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.info.WebServiceContext;

public class DocLitWebServiceGenarator implements WebServiceGenarator{
	private WebServiceContext wscontext;
	public DocLitWebServiceGenarator(WebServiceContext wscontext){						  
		this.wscontext =wscontext;
	}
	/**
	 * Genarate the wrapper genarator, Serivce genatator,Param Genarator and called
	 * Genarate on it. This is the way for the Document literal.   
	 * @see org.apache.axis.wsdl.wsdl2ws.WebServiceGenarator#genarate()
	 */
	public void genarate()throws WrapperFault {
		String language = wscontext.getWrapInfo().getWrapperLanguage();
		if(WrapperConstants.LANGUAGE_JAVA.equalsIgnoreCase(language)){
		//if(WrapperConstants.SERVER.equals(wscontext.getWrapInfo().getTargetEngine()))
			(new Genarator(WrapperConstants.GENERATOR_WRAPPER_JAVA, wscontext)).genarate();
		//else
			//(new Genarator(WrapperConstants.GENERATOR_CLIENT_WRAPPER_JAVA, wscontext)).genarate();
			(new Genarator(WrapperConstants.GENERATOR_SERVICE_JAVA, wscontext)).genarate();
			(new Genarator(WrapperConstants.GENERATOR_PARAM_JAVA, wscontext)).genarate();
		}else if(WrapperConstants.LANGUAGE_CPP.equalsIgnoreCase(language)){
			if(WrapperConstants.SERVER.equals(wscontext.getWrapInfo().getTargetEngine())){
				(new Genarator(WrapperConstants.GENERATOR_WRAPPER_CPP, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_WRAPPER_HPP, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_SERVICE_CPP, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_SERVICE_HPP, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_PARAM_CPP_ALL, wscontext)).genarate();	
				(new Genarator(WrapperConstants.GENERATOR_CLASSLOADER_CPP, wscontext)).genarate();				 				 	
				(new Genarator(WrapperConstants.GENERATOR_DEPLOYMENT, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_UNDEPLOYMENT, wscontext)).genarate();
			}else{
				(new Genarator(WrapperConstants.GENERATOR_CLIENT_STUB_CPP, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_CLIENT_STUB_HPP, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_PARAM_CPP_ALL, wscontext)).genarate();	
			}
		}else if(WrapperConstants.LANGUAGE_C.equalsIgnoreCase(language)){
			if(WrapperConstants.SERVER.equals(wscontext.getWrapInfo().getTargetEngine())){
				(new Genarator(WrapperConstants.GENERATOR_WRAPPER_C, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_WRAPPER_H, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_SERVICE_C, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_PARAM_C_ALL, wscontext)).genarate();	
				(new Genarator(WrapperConstants.GENERATOR_CLASSLOADER_C, wscontext)).genarate();				 				 	
				(new Genarator(WrapperConstants.GENERATOR_DEPLOYMENT, wscontext)).genarate();
				(new Genarator(WrapperConstants.GENERATOR_UNDEPLOYMENT, wscontext)).genarate();
			}else{
				 (new Genarator(WrapperConstants.GENERATOR_CLIENT_STUB_C, wscontext)).genarate();
				 (new Genarator(WrapperConstants.GENERATOR_CLIENT_STUB_H, wscontext)).genarate();
				 (new Genarator(WrapperConstants.GENERATOR_PARAM_C_ALL, wscontext)).genarate();	
			}				 				 	
		}		
		else{
			throw new WrapperFault("Unsupported Language"+language);
		}
	}
}
