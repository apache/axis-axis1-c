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
