/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2004 The Apache Software Foundation.  All rights
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

package org.apache.geronimo.ews.ws4j2ee.toWs.wsdl;

import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.utils.ClassUtils;
import org.apache.axis.wsdl.Java2WSDL;
import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.ContextValidator;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.impl.AxisEmitterBasedJaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.AxisEmitterBasedWSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.impl.AxisEmitterBasedWSDLContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2eeServerCLOptionParser;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

/**
 * <p>This genarated theWrapper WS required in the
 * Axis.</p>
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class WSDLGenerator extends Java2WSDL implements Generator {
	private J2EEWebServiceContext wscontext;
	private Ws4J2eeServerCLOptionParser clparser;
	private Emitter emitter;
	private String wsdlFile;
	private boolean verbose;

	protected static Log log =
			LogFactory.getLog(WSDLGenerator.class.getName());

	public WSDLGenerator(J2EEWebServiceContext wscontext,
			Emitter emitter,
			Ws4J2eeServerCLOptionParser clparser)throws GenerationFault {
		this.wscontext = wscontext;
		this.emitter = emitter;
		this.clparser = clparser;
		this.wsdlFile = wscontext.getMiscInfo().getWsdlFile().fileName();
	}	


	public void generate() throws GenerationFault {
		try {
			if (verbose)
				log.info("calling Java2WSDL to genarated wsdl ...........");
			//generate the wsdl file
			ClassUtils.setDefaultClassLoader(wscontext.getMiscInfo().getClassloader());
			emitter.setLocationUrl("http://127.0.0.1");
			emitter.setServicePortName(
				wscontext.getWSCFContext().getWscfport().getWsdlPort().getLocalpart());
    		
			int mode = Emitter.MODE_ALL;
			mode = clparser.getMode();
			
			// Find the class using the name
			String seiName = wscontext.getMiscInfo().getJaxrpcSEI();
			emitter.setCls(seiName);
			// Generate a full wsdl, or interface & implementation wsdls
			Utils.prepareTheDir(wsdlFile);    
			if (wsdlImplFilename == null) {
				emitter.emit(wsdlFile, mode);
			} else {
				emitter.emit(wsdlFile, wsdlImplFilename);
			}
//			//initiate the wsdlContext
			this.wscontext.setWSDLContext(
				new AxisEmitterBasedWSDLContext(emitter.getWSDL()));
			//parse the ejb-jar.xml here
			ContextValidator validator = new ContextValidator(wscontext);
			//initiate the jaxrpcmapping context 
			this.wscontext.setJAXRPCMappingContext(
				new AxisEmitterBasedJaxRpcMapperContext(emitter, wscontext));
//			//initiate the wscf context 
//			this.wscontext.setWSCFContext( new AxisEmitterBasedWSCFContext(emitter, wscontext));
			//validate the j2ee context
			validator.validateWithOutWSDL(emitter);
		} catch (Exception e) {
			throw GenerationFault.createGenerationFault(e);
		} 

	}
}
