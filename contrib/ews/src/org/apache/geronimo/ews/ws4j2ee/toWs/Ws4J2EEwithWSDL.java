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
import java.io.FileNotFoundException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.ContextValidator;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.MiscInfo;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

/**
 * <p>this class genarate the code when the WSDL presents.</p>
 */
public class Ws4J2EEwithWSDL implements Generator {
    private boolean verbose = false;
    private Ws4J2eeCLOptionParser clparser;
    protected static Log log =
            LogFactory.getLog(Ws4J2EEwithWSDL.class.getName());

    private MiscInfo misc;
	private J2EEWebServiceContext wscontext;

    public Ws4J2EEwithWSDL(String[] args) throws Exception {
        clparser = new Ws4J2eeCLOptionParser(args);
        misc = ContextFactory.createMiscInfo();
    }

    /**
     * genarate. what is genarated is depend on genarators included.
     * 
     * @see org.apache.geronimo.ews.ws4j2ee.toWs.Generator#genarate()
     */
    public void generate() throws GenerationFault {

            try {
                String wscffile = clparser.getWscffile();
                misc.setWsconffile(wscffile);
                misc.setOutputPath(clparser.getOutputDirectory());
                misc.setWsConfFileLocation(Utils.getRootDirOfFile(wscffile));
                wscontext = ContextFactory.getJ2EEWsContext(true);
                wscontext.setMiscInfo(misc);
                //parsing of the webservice.xml happen here 
                WSCFContext wscfcontext = ContextFactory.createWSCFContext(new FileInputStream(wscffile));
                wscontext.setWSCFContext(wscfcontext);
                wscontext.getMiscInfo().setImplStyle(clparser.getImplStyle());
                wscontext.getMiscInfo().setTargetJ2EEContainer(clparser.getContanier());
                
                if (verbose)
                    log.info(wscffile + " parsed ..");
                
                WSCFWebserviceDescription[] wscfwsdiss = wscfcontext.getWebServicesDescription();
                //let us take the first discription
                if (wscfwsdiss == null || wscfwsdiss.length == 0)
                    throw new UnrecoverableGenerationFault("no webservice discription found in the" +
                            "webservice.xml file");
                genarate(wscfwsdiss[0]);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
                throw GenerationFault.createGenerationFault(e);
            }            
        }
		public void genarate(WSCFWebserviceDescription wscfwsdis) throws GenerationFault {            
                        
            wscontext.getMiscInfo().setWscfdWsDescription(wscfwsdis);

            wscontext.getMiscInfo().setJaxrpcfile(Utils.getAbsolutePath(wscfwsdis.getJaxrpcMappingFile(),misc.getWsConfFileLocation()));
            wscontext.getMiscInfo().setWsdlFile(Utils.getAbsolutePath(wscfwsdis.getWsdlFile(), misc.getWsConfFileLocation()));
			wscontext.getMiscInfo().setVerbose(verbose);
			
			
            //JAX-RPC mapper calling       
			Generator jaxrpcmapperGen = GeneratorFactory.createGenerator(wscontext,
                    GenerationConstants.SEI_AND_TYPES_GENERATOR);
			jaxrpcmapperGen.generate();
			ContextValidator cvalidater = new ContextValidator(wscontext);
			cvalidater.validateWithWSDL();
            //get and populate the symbol table 
            
			WSCFPortComponent port = wscontext.getMiscInfo().getWscfport();
			wscontext.getMiscInfo().setHandlers(port.getHandlers());
            String ejbLink = port.getServiceImplBean().getEjblink();
            if(wscontext.getMiscInfo().isImplwithEJB()){
				if (verbose)
					log.info("genarating ejb >>");
				Generator ejbGen =	GeneratorFactory.createGenerator(wscontext,
						GenerationConstants.EJB_GENERATOR);
				ejbGen.generate();
				if (verbose)
					log.info("genarating web service wrapper >>");
				Generator wrapperWsGen = GeneratorFactory.createGenerator(wscontext,
						GenerationConstants.AXIS_WEBSERVICE_WRAPPER_GENERATOR);
				wrapperWsGen.generate();
				if (verbose)
					log.info("genarating j2ee dd >>");
				Generator j2eeContainerDDGen = GeneratorFactory.createGenerator(wscontext, GenerationConstants.J2EE_CONTAINER_DD_GENERATOR);
				j2eeContainerDDGen.generate();
            }else{
            	//in this case user should fill the implementation 
            	//in the *BindingImpl class 
				wscontext.getMiscInfo().setImplwithEJB(false);
				Generator webCointainerDDGen = GeneratorFactory.createGenerator(wscontext, GenerationConstants.WEB_CONTAINER_DD_GENERATOR);
				webCointainerDDGen.generate();
            }
			Generator buildFileGen = GeneratorFactory.createGenerator(wscontext, GenerationConstants.BUILD_FILE_GENERATOR);
			buildFileGen.generate();
			Generator handlerGen = GeneratorFactory.createGenerator(wscontext,
                GenerationConstants.HANDLER_GENERATOR);
			handlerGen.generate();
    }


    public static void main(String[] args) throws Exception {
        Ws4J2EEwithWSDL gen = new Ws4J2EEwithWSDL(args);
        gen.generate();
    }
}
