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

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.Vector;

import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.utils.ClassUtils;
import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.ContextValidator;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.impl.AxisEmitterBasedJaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.context.impl.J2EEWebServiceContextImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.AxisEmitterBasedWSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.impl.AxisEmitterBasedWSDLContext;
import org.apache.geronimo.ews.ws4j2ee.parsers.EJBDDParser;
import org.apache.geronimo.ews.ws4j2ee.parsers.WebDDParser;
import org.apache.geronimo.ews.ws4j2ee.toWs.wsdl.WSDLGenarator;
import org.apache.geronimo.ews.ws4j2ee.utils.JarFileLoader;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

/**
 * <p>this class genarate the code when the WSDL does not presents.</p>
 */
public class Ws4J2EEwithoutWSDL implements Generator {
    protected static Log log =
            LogFactory.getLog(Ws4J2EEwithWSDL.class.getName());
	private String implbean;
	private String wscffile;
    private Vector genarators;
    private String[] args;
    private J2EEWebServiceContext wscontext;
    private boolean verbose = true;
    private Ws4J2eeWtihoutWSDLCLOptionParser clparser;
	private File jarfile;
    
    private InputStream ejbddin;
    private InputStream webddin;
    private Emitter emitter;
	
	public Ws4J2EEwithoutWSDL(){
		emitter = new Emitter();	
	}


    public Ws4J2EEwithoutWSDL(String[] args, boolean useSEI) throws GenerationFault {
		this();
		try{
			
			this.args = args;
	        genarators = new Vector();
			
			
			//create the context
	        this.wscontext = new J2EEWebServiceContextImpl(false);
	        this.wscontext.setMiscInfo(ContextFactory.createMiscInfo());
			wscontext.getMiscInfo().setVerbose(verbose);
			
			//parse the arguments 
			clparser = new Ws4J2eeWtihoutWSDLCLOptionParser(args,emitter);
			this.wscffile = clparser.getWSCFFileLocation();
			wscontext.getMiscInfo().setWsConfFileLocation(clparser.getOutPutLocation());
			wscontext.getMiscInfo().setOutputPath(clparser.getOutPutLocation());
			
			//create the wscf context
			WSCFContext wscfcontext = ContextFactory.createWSCFContext(new FileInputStream(wscffile));
			wscontext.setWSCFContext(wscfcontext);
			if (verbose)
				log.info(wscffile + " parsed ..");
		}catch(FileNotFoundException e){
			throw new GenerationFault(e);
		}	
    }

	public Ws4J2EEwithoutWSDL(String jarFile,String outputDirOption) throws GenerationFault {
			this();
			jarfile = new File(jarFile);
			genarators = new Vector();
			
			JarFileLoader jarfileLoader = new JarFileLoader(jarFile);
			ejbddin = jarfileLoader.getEjbJarfile();
			webddin = jarfileLoader.getWebddfile();
			
			//create the context
			this.wscontext = new J2EEWebServiceContextImpl(false);
			this.wscontext.setMiscInfo(ContextFactory.createMiscInfo());
			wscontext.getMiscInfo().setVerbose(verbose);
			
			//parse the arguments 
			wscontext.getMiscInfo().setWsConfFileLocation(outputDirOption);
			wscontext.getMiscInfo().setOutputPath(outputDirOption);
			
			//create the wscf context
			WSCFContext wscfcontext = ContextFactory.createWSCFContext(jarfileLoader.getWscfFile());
			wscontext.setWSCFContext(wscfcontext);
	}

    /**
     * genarate. what is genarated is depend on genarators included.
     * 
     * @see org.apache.geronimo.ews.ws4j2ee.toWs.Generator#genarate()
     */
    public void genarate() throws GenerationFault {
		WSCFWebserviceDescription[] wscfwsdiss = wscontext.getWSCFContext().getWebServicesDescription();
		//TODO fix this to handle multiple discriptions let us take the first discription
		if (wscfwsdiss == null || wscfwsdiss.length == 0)
			throw new UnrecoverableGenarationFault("no webservice discription found in the" +
							"webservice.xml file");
		genarate(wscfwsdiss[0]);
    }
    
	public void genarate(WSCFWebserviceDescription wscfwsdis) throws GenerationFault {
		wscontext.getMiscInfo().setWscfdWsDescription(wscfwsdis);
        try {
        	
			WSCFPortComponent[] ports = wscfwsdis.getPortComponent();
			//TODO how to create the correct port type 
			if (ports == null || ports.length == 0)
				throw new UnrecoverableGenarationFault("no port discription found in the" +
						"webservice.xml file");
			WSCFPortComponent port = ports[0];
			
			wscontext.getMiscInfo().setWscfport(port);
			String ejbLink = port.getServiceImplBean().getEjblink();
			String seiName = port.getServiceEndpointInterface();        	
			wscontext.getMiscInfo().setJaxrpcSEI(seiName);
			wscontext.getMiscInfo().setHandlers(port.getHandlers());
			
			
			String wsdlFile = Utils.getAbsolutePath(wscfwsdis.getWsdlFile(),wscontext.getMiscInfo().getWsConfFileLocation());
			wscontext.getMiscInfo().setWsdlFile(wsdlFile);
			wscontext.getMiscInfo().setJaxrpcfile(Utils.getAbsolutePath(wscfwsdis.getJaxrpcMappingFile(),wscontext.getMiscInfo().getOutPutPath()));
			
			File file = new File(wscontext.getMiscInfo().getOutPutPath()+"/META-INF");
			if (!file.exists())
				file.mkdirs();
			
			//generate the wsdl file
			if(jarfile != null){
				ClassUtils.setDefaultClassLoader(ClassUtils.createClassLoader(
						jarfile.getAbsolutePath(),this.getClass().getClassLoader()));
			}

            if (verbose)
                log.info("calling Java2WSDL to genarated wsdl ...........");
            WSDLGenarator wsdlgen = (WSDLGenarator) GeneratorFactory.createGenerator(wscontext, GenerationConstants.WSDL_GENERATOR);

			emitter.setLocationUrl("http://127.0.0.1");
			emitter.setServicePortName(port.getWsdlPort().getLocalpart());
			String wsdlImplFilename = null;
			int mode = Emitter.MODE_ALL;
			if(clparser != null){
				wsdlImplFilename = clparser.getWsdlImplFilename();
				mode = clparser.getMode();
			}

			 // Find the class using the name
			 emitter.setCls(seiName);
			 // Generate a full wsdl, or interface & implementation wsdls
			 if (wsdlImplFilename == null) {
				 emitter.emit(wsdlFile,mode);
			 } else {
				 emitter.emit(wsdlFile, wsdlImplFilename);
			 }
			 
			//initiate the wsdlContext
			this.wscontext.setWSDLContext(new AxisEmitterBasedWSDLContext(emitter.getWSDL()));
			//parse the ejb-jar.xml here
			ContextValidator validator = new ContextValidator(wscontext);
			//initiate the jaxrpcmapping context 
			this.wscontext.setJAXRPCMappingContext(new AxisEmitterBasedJaxRpcMapperContext(emitter, wscontext));
			//initiate the wscf context 
			this.wscontext.setWSCFContext(new AxisEmitterBasedWSCFContext(emitter, wscontext));
			//validate the j2ee context
			validator.validateWithOutWSDL(emitter);

	
				 // everything is good
            if (verbose)
                log.info("genarating jaxrpc-mapper.xml ..............");
			Generator jaxrpcfilegen = GeneratorFactory.createGenerator(wscontext,
                    GenerationConstants.JAXRPCMAPPER_GENERATOR);
			jaxrpcfilegen.genarate();
			
			Generator seiAndTypegen = GeneratorFactory.createGenerator(wscontext,
                    GenerationConstants.SEI_AND_TYPES_GENERATOR);
			seiAndTypegen.genarate();
			
			ContextValidator cvalidater = new ContextValidator(wscontext);
			cvalidater.validateWithWSDL();        

			//remove the repeting SEI. TODO is this required to remove or not                     
			String repeatingSEIName = wscontext.getMiscInfo().getOutPutPath()+"/"+seiName.replace('.','/')+".java"; 
			file = new File(repeatingSEIName);
			if(file.exists()){
				file.delete();
				System.out.println(repeatingSEIName + " deleted..............");
			}

			if(ejbLink != null){
				wscontext.getMiscInfo().setEjbName(ejbLink);
				EJBDDParser ejbDDparser = new EJBDDParser(wscontext);
				 
				if(ejbddin == null){
					file = new File(clparser.getEjbConfFileLocation());
					if(file.exists()){
						ejbddin = new FileInputStream(file);
					}else{
						ejbddin = Ws4J2EEwithoutWSDL.class.getResourceAsStream("META-INF/ejb-jar.xml");
					}
				}

				if (ejbddin != null) {
					ejbDDparser.parse(ejbddin);
					ejbddin.close();
				}else
					throw new GenerationFault("file "+clparser.getWebConfFileLocation()+"does not exsits");
				wscontext.getMiscInfo().setImplAvalible(true);				
				if (verbose)
						log.info("genarating ejb >>");
				GeneratorFactory.createGenerator(wscontext,
					GenerationConstants.EJB_GENERATOR).genarate();
			}else{
				wscontext.getMiscInfo().setImplwithEJB(false);
				//parse the web.xml file and gereratre wrapper
				WebDDParser webddp = new WebDDParser(wscontext);
				file = new File(clparser.getWebConfFileLocation());
				if(webddin == null){				
					if(file.exists()){
							webddin = new FileInputStream(file);
					}else{
						webddin = Ws4J2EEwithoutWSDL.class.getResourceAsStream("META-INF/web.xml");				
					}
				}
				if(webddin != null){
					webddp.parse(webddin);
				}else
					throw new GenerationFault("file "+clparser.getWebConfFileLocation()+"does not exsits");
				
				wscontext.getMiscInfo().setEndpointImplbean(webddp.getServletClass());
			}
			Generator wrapgen = GeneratorFactory.createGenerator(wscontext,
				GenerationConstants.AXIS_WEBSERVICE_WRAPPER_GENERATOR);
			wrapgen.genarate();

        } catch (Exception e) {
        	e.printStackTrace();
            throw GenerationFault.createGenerationFault(e);
        }
    }
	/**
	 * args is String array s.t.
	 * 1)first argument is webservice.xml file 
	 * 2)Other arguments are any option that can given to Java2WSDL
	 * 3)the SEI and the service Implementation bean should be avalible on the class path
	 * 4)the ws4j2ee will search for the web.xml or ejb-jar.xml 
	 * 		a)same directory as the webservice.xml file 
	 * 		b)file should be in the class path s.t META-INF/web.xml or META-INF/ejb-jar.xml
	 * 5)if no file found at the #4 the ws4j2ee continue assuming the Impl bean and the 
	 * DD is not avalible. This is additional to spec.
	 * @param args
	 * @throws Exception
	 */
    public static void main(String[] args) throws Exception {
		Ws4J2EEwithoutWSDL gen = null;
    	if(args.length == 1){
    		 //means a jar file option given 
			 gen = new Ws4J2EEwithoutWSDL(args[0],"-o.");
    	}else if(args.length == 2){
    		//means jar file option and output dir given
			gen = new Ws4J2EEwithoutWSDL(args[0],args[1]);
    	}else{
			gen = new Ws4J2EEwithoutWSDL(args,false);    	
    	}
        gen.genarate();
    }
}