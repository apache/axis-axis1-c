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
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.EJBContext;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.WebContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.toWs.impl.Ws4J2eeFactoryImpl;
import org.apache.geronimo.ews.ws4j2ee.utils.MiscFactory;
import org.apache.geronimo.ews.ws4j2ee.utils.packager.load.PackageModule;

/**
 * <p>this class genarate the code when the WSDL does not presents.</p>
 */
public class Ws4J2ee implements Generator {
    protected static Log log =
        LogFactory.getLog(Ws4J2ee.class.getName());
    private J2EEWebServiceContext wscontext;
    private boolean verbose = false;
    private Ws4J2eeDeployContext clparser;
    private WSCFPortComponent port;
    private ClassLoader classloader;
   
    private PackageModule module;
    private String wsdlImplFilename;

    private InputStream wscffile;
    private InputStream ejbddin;
    private InputStream webddin;
	private InputStream wsdlFile;
	private InputStream jaxrpcmappingFile;
	private String ejbLink;
    private Emitter emitter;
	private Ws4J2eeFactory factory;


    public Ws4J2ee(Ws4J2eeDeployContext doployContext,Emitter emitter)
        throws GenerationFault {
        	if(emitter == null){
				this.emitter = new Emitter();        	
        	}else{
				this.emitter = emitter;
        	}
			this.clparser = doployContext;
		    //create the context
			prepareContext();
		    //parse the arguments 
			parseCLargs();
    }
    
	/**
	 * genarate. what is genarated is depend on genarators included.
	 * @see org.apache.geronimo.ews.ws4j2ee.toWs.Generator#genarate()
	 */
	public void generate() throws GenerationFault {
		try{
			//create the wscf context
			WSCFWebserviceDescription wscfwsdis = parseTheWSCF();
			populateWebserviceInfo(wscfwsdis);
			pareseJ2eeModule();
			checkAndGenerateWsdlAndMapping(wscfwsdis);
			Ws4J2eeEmitter ws4j2eeEmitter = new Ws4J2eeEmitter(wscontext);
			ws4j2eeEmitter.emmit();
		}finally{
			cleanup();
		}
       
	}

    private void prepareContext(){
		factory = new Ws4J2eeFactoryImpl();
		this.wscontext = factory.getContextFactory().getJ2EEWsContext(false);
		this.wscontext.setFactory(factory);
		this.wscontext.setMiscInfo(factory.getContextFactory().createMiscInfo());
		wscontext.getMiscInfo().setVerbose(verbose);
    }
    
    private void parseCLargs()throws GenerationFault{
		module = clparser.getModule();
		classloader = module.getClassLoaderWithPackageLoaded();
		wscontext.getMiscInfo().setClassloader(classloader);
		wscontext.getMiscInfo().setOutputPath(clparser.getOutPutLocation());
		wscontext.getMiscInfo().setImplStyle(clparser.getImplStyle());
		wscontext.getMiscInfo().setTargetJ2EEContainer(clparser.getContanier());
        wscontext.getMiscInfo().setCompile(clparser.isCompile());

		wsdlImplFilename = clparser.getWsdlImplFilename();
		this.wscffile = module.getWscfFile();
		ejbddin = module.getEjbJarfile();
		webddin = module.getWebddfile();
		wscontext.getMiscInfo().setWsconffile(MiscFactory.getInputFile(this.wscffile));
		wscontext.getMiscInfo().setClassPathElements(module.getClassPathElements());
    }

	private WSCFWebserviceDescription parseTheWSCF()throws GenerationFault {
		WSCFContext wscfcontext =
			factory.getParserFactory().parseWSCF(wscontext,this.wscffile);
		wscontext.setWSCFContext(wscfcontext);
		if (verbose)
			log.info(wscffile + " parsed ..");
		WSCFWebserviceDescription[] wscfwsdiss =
			wscontext.getWSCFContext().getWebServicesDescription();
		//TODO fix this to handle multiple discriptions let us take the first discription
		if (wscfwsdiss == null || wscfwsdiss.length == 0)
			throw new UnrecoverableGenerationFault(
				"no webservice discription "
					+ "found in the webservice.xml file");
		wscontext.getWSCFContext().setWscfdWsDescription(wscfwsdiss[0]);			
		return wscfwsdiss[0];
	
	}

    
	private void generateTheWSDLfile()throws GenerationFault{
		Generator wsdlgen 
			= factory.getGenerationFactory().createWSDLGenerator(
			wscontext,emitter,clparser);
		wsdlgen.generate();		
	}

	/**
	 * generate the jaxrpcmapping file
	 */
	private void generateTheJaxrpcmappingFile()throws GenerationFault{
		// everything is good
		if (verbose)
			log.info("genarating jaxrpc-mapper.xml ..............");
		Generator jaxrpcfilegen = factory.getGenerationFactory()
			.createJaxrpcMapperGenerator(wscontext);
		jaxrpcfilegen.generate();

	}


	private void parseEJBModule()throws GenerationFault{
        try {
            File file = null;
            if (ejbddin != null) {
            	EJBContext ejbcontext = factory.getParserFactory()
					.parseEJBDDContext(wscontext,ejbddin);
            	wscontext.setEJBDDContext(ejbcontext);
            	ejbddin.close();
				checkForImplBean(ejbcontext.getImplBean());
            } else{
            	throw new GenerationFault(
            		"ejb-jar.xml file file does not exsits");
            }
        } catch (IOException e) {
			throw GenerationFault.createGenerationFault(e);
        }
    }	 

	public void parseWebModule()throws GenerationFault{
		wscontext.getMiscInfo().setImplwithEJB(false);
		if (webddin != null) {
			WebContext webcontext = factory.getParserFactory().parseWebDD(wscontext,webddin);
			wscontext.setWebDDContext(webcontext);
			checkForImplBean(webcontext.getServletClass());
		} else{
			throw new GenerationFault(
				"web.xml file does not exsits");
		}
	}
	
	private void checkForImplBean(String implBean){
		//TODO fix this java.lang.NoClassDefFoundError: javax/ejb/SessionBean
		//from the dependancy class
		if(implBean == null){
			wscontext.getMiscInfo().setImplAvalible(false);
		}else{
			try{
				Class.forName(implBean,true,classloader);
			}catch(ClassNotFoundException e){
				wscontext.getMiscInfo().setImplAvalible(false);
			}catch(java.lang.NoClassDefFoundError e){
				wscontext.getMiscInfo().setImplAvalible(false);
			}			
		}
	}

	private void populateWebserviceInfo(WSCFWebserviceDescription wscfwsdis){
		wscontext.getWSCFContext().setWscfdWsDescription(wscfwsdis);
				wscontext.getMiscInfo().setSEIExists(true);
				WSCFPortComponent[] ports = wscfwsdis.getPortComponent();
				//TODO how to create the correct port type 
				if (ports == null || ports.length == 0)
					throw new UnrecoverableGenerationFault(
						"no port discription"
							+ " found in the webservice.xml file");
				this.port = ports[0];
				wscontext.getWSCFContext().setWscfport(port);
				this.ejbLink = port.getServiceImplBean().getEjblink();
				String seiName = port.getServiceEndpointInterface();
	
				wscontext.getMiscInfo().setJaxrpcSEI(seiName);
				wscontext.getMiscInfo().setHandlers(port.getHandlers());
	}
	
	private void pareseJ2eeModule()throws GenerationFault{
		if (ejbLink != null) {
			wscontext.getMiscInfo().setJ2eeComponetLink(ejbLink);
			wscontext.getMiscInfo().setImplwithEJB(true);
			parseEJBModule();
		}else{
			wscontext.getMiscInfo().setJ2eeComponetLink(port.getServiceImplBean().getServletlink());
			wscontext.getMiscInfo().setImplwithEJB(false);
			parseWebModule();
		}
	}
	
	private void checkAndGenerateWsdlAndMapping(WSCFWebserviceDescription wscfwsdis)
		throws GenerationFault{
		String wsdlFilename = wscfwsdis.getWsdlFile();
		String jaxrpcMappingFileName = wscfwsdis.getJaxrpcMappingFile();
		this.wsdlFile = module.findFileInModule(wsdlFilename);
		if(this.wsdlFile == null){
			String wsdlabsoluteFile = wscontext.getMiscInfo().getOutPutPath()+"/"+wsdlFilename;
			wscontext.getMiscInfo().setWsdlFile(MiscFactory.getInputFile(wsdlabsoluteFile));
			File jaxrpcfile = new File(wscontext.getMiscInfo().getOutPutPath()+"/"+jaxrpcMappingFileName);
			wscontext.getMiscInfo().setJaxrpcfile(MiscFactory.getInputFile(jaxrpcfile.getAbsolutePath()));
			generateTheWSDLfile();
			generateTheJaxrpcmappingFile();
			wscontext.getMiscInfo().setSEIExists(true);
		}else{
			String file = wscontext.getMiscInfo().getOutPutPath()+"/"+wsdlFilename;
			copyTheWSDLFile(file);
			wscontext.getMiscInfo().setWsdlFile(MiscFactory.getInputFile(file));
			jaxrpcmappingFile = module.findFileInModule(jaxrpcMappingFileName);
			if(jaxrpcmappingFile == null){
				throw new GenerationFault("if the wsdlfile avalible the jaxrpcmapping file must be avalible");
			}else{
				wscontext.getMiscInfo().setJaxrpcfile(MiscFactory.getInputFile(jaxrpcmappingFile));			
			}
			wscontext.getMiscInfo().setSEIExists(false);
		}
	
	}


	public void cleanup()throws GenerationFault{
		try{
			wscffile.close();
			if(ejbddin != null){
				ejbddin.close();
			}
			if(webddin != null){
				webddin.close();
			}
			if(jaxrpcmappingFile != null){
				jaxrpcmappingFile.close();
			}
			if(wsdlFile != null){
				wsdlFile.close();
			}			
		}catch(Exception e){
			throw GenerationFault.createGenerationFault(e);
		}
	}
	public void copyTheWSDLFile(String filein) throws GenerationFault{
		try{
			File file = new File(filein);
			OutputStream out = new FileOutputStream(file);
			byte[] buf = new byte[1024];
			int val = this.wsdlFile.read(buf);
			while(val > 0){
				out.write(buf,0,val);
				val = this.wsdlFile.read(buf);
			}
			out.close();
			this.wsdlFile.close();
		}catch(Exception e){
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
        Ws4J2ee gen = null;
        Emitter emitter = new Emitter();
		Ws4J2eeDeployContext deployContext = new Ws4J2eeServerCLOptionParser(args,emitter);
        gen = new Ws4J2ee(deployContext,emitter);
        gen.generate();
    }
}
