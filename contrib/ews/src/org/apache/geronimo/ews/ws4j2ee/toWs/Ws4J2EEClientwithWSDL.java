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

package org.apache.geronimo.ews.ws4j2ee.toWs;

import java.io.FileInputStream;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.geronimo.ews.ws4j2ee.context.ContextValidator;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.MiscInfo;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferanceContext;
import org.apache.geronimo.ews.ws4j2ee.parsers.ServiceReferanceParser;
import org.apache.geronimo.ews.ws4j2ee.toWs.impl.Ws4J2eeFactoryImpl;
import org.apache.geronimo.ews.ws4j2ee.utils.MiscFactory;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

/**
 * <p>this class genarate the code when the WSDL presents.</p>
 */
public class Ws4J2EEClientwithWSDL implements Generator {
	private String wsConfFileLocation;
    private boolean verbose = false;
    private Ws4J2eeCLOptionParser clparser;
	private Ws4J2eeFactory factory;
    protected static Log log =
            LogFactory.getLog(Ws4J2EEClientwithWSDL.class.getName());
     


    private MiscInfo misc;

    public Ws4J2EEClientwithWSDL(String[] args) throws Exception {
        clparser = new Ws4J2eeCLOptionParser(args);
        
    }

    /**
     * genarate. what is genarated is depend on genarators included.
     * 
     * @see org.apache.geronimo.ews.ws4j2ee.toWs.Generator#genarate()
     */
    public void generate() throws GenerationFault {
        try {
			factory = new Ws4J2eeFactoryImpl(); 
			J2EEWebServiceContext wscontext = factory.getContextFactory().getJ2EEWsContext(true);
			wscontext.setFactory(factory);			
			misc = factory.getContextFactory().createMiscInfo();

			wscontext.setMiscInfo(misc);

            String wscfClientfile = clparser.getWscffile();
			misc.setWsconffile(MiscFactory.getInputFile(wscfClientfile));
            misc.setOutputPath(clparser.getOutputDirectory());
			wsConfFileLocation = Utils.getRootDirOfFile(wscfClientfile);
			wscontext.getMiscInfo().setImplStyle(clparser.getImplStyle());
			wscontext.getMiscInfo().setTargetJ2EEContainer(clparser.getContanier());
            
            
            //parsing of the webservice.xml happen here 
            ServiceReferanceContext serviceContext = 
            	factory.getParserFactory().parseServiceReferance(wscontext,
            		new FileInputStream(wscfClientfile));
            if (verbose){
				log.info(wscfClientfile + " parsed ..");
				log.info(serviceContext.getJaxrpcmappingFile());       
				log.info(serviceContext.getWsdlFile());
           }

            wscontext.getMiscInfo().setJaxrpcfile(
				MiscFactory.getInputFile(
					Utils.getAbsolutePath(serviceContext.getJaxrpcmappingFile(),
					wsConfFileLocation)));
            wscontext.getMiscInfo().setWsdlFile(
				MiscFactory.getInputFile(
            		Utils.getAbsolutePath(serviceContext.getWsdlFile(), 
					wsConfFileLocation)));
			wscontext.getMiscInfo().setVerbose(verbose);
			wscontext.getMiscInfo().setHandlers(serviceContext.getHandlers()); 
			
            //JAX-RPC mapper calling
            if (verbose)
                log.info("starting client side code genaration .. ");
			Generator clientStubGen = factory.getGenerationFactory().createClientSideWsGenerator(wscontext);
			clientStubGen.generate();
			ContextValidator cvalidator = new ContextValidator(wscontext);
			//cvalidator.validateWithWSDL();
			Generator handlerGen = factory.getGenerationFactory().createHandlerGenerator(wscontext);
			handlerGen.generate();
        } catch (Exception e) {
            e.printStackTrace();
            throw GenerationFault.createGenerationFault(e);
        }
    }


    public static void main(String[] args) throws Exception {
        Ws4J2EEClientwithWSDL gen = new Ws4J2EEClientwithWSDL(args);
        gen.generate();
    }
}
