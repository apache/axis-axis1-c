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

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.ContextValidator;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.MiscInfo;
import org.apache.geronimo.ews.ws4j2ee.context.impl.J2EEWebServiceContextImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;
import org.w3c.dom.Document;

import javax.xml.parsers.DocumentBuilderFactory;

/**
 * <p>this class genarate the code when the WSDL presents.</p>
 */
public class Ws4J2EEwithWSDL implements Generator {
    private boolean verbose = true;
    private Ws4J2eeCLOptionParser clparser;
    protected static Log log =
            LogFactory.getLog(Ws4J2EEwithWSDL.class.getName());

    /* indicate code to genarate is server side or the client side*/
    private boolean isSeverSideCodeGenaration = true;

    private MiscInfo misc;

    public Ws4J2EEwithWSDL(String[] args) throws Exception {
        clparser = new Ws4J2eeCLOptionParser(args);
        misc = ContextFactory.createMiscInfo();
    }

    /**
     * genarate. what is genarated is depend on genarators included.
     * 
     * @see org.apache.geronimo.ews.ws4j2ee.toWs.Generator#genarate()
     */
    public void genarate() throws GenerationFault {
        try {
            String wscffile = clparser.getWscffile();
            misc.setOutputPath(clparser.getOutputDirectory());
            misc.setWsConfFileLocation(wscffile.substring(0, wscffile.lastIndexOf('/')));
            isSeverSideCodeGenaration = clparser.isServerSide();
    
            //we may need to pass few parameters to the J2EEWebServiceContextImpl they are TODO
            J2EEWebServiceContext wscontext = new J2EEWebServiceContextImpl(true);
            wscontext.setMiscInfo(misc);
            //parsing of the webservice.xml happen here 
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            dbf.setNamespaceAware(true);
            Document wscfdoc = dbf.newDocumentBuilder().parse(wscffile);
            WSCFContext wscfcontext = ContextFactory.createWSCFContext(wscfdoc);
            wscontext.setWSCFContext(wscfcontext);
            if (verbose)
                log.info(wscffile + " parsed ..");

            WSCFWebserviceDescription[] wscfwsdiss = wscfcontext.getWebServicesDescription();
            //let us take the first discription
            if (wscfwsdiss == null || wscfwsdiss.length == 0)
                throw new UnrecoverableGenarationFault("no webservice discription found in the" +
                        "webservice.xml file");
            wscontext.getMiscInfo().setWscfdWsDescription(wscfwsdiss[0]);

            wscontext.getMiscInfo().setJaxrpcfile(Utils.getAbsolutePath(wscfwsdiss[0].getJaxrpcMappingFile(), wscffile.substring(0, wscffile.lastIndexOf('/'))));
            wscontext.getMiscInfo().setWsdlFile(Utils.getAbsolutePath(wscfwsdiss[0].getWsdlFile(), wscffile.substring(0, wscffile.lastIndexOf('/'))));
            if (isSeverSideCodeGenaration) {
                //JAX-RPC mapper calling       
                GeneratorFactory.createGenerator(wscontext,
                        GenerationConstants.SEI_AND_TYPES_GENERATOR).genarate();
                (new ContextValidator(wscontext)).validateWithWSDL();
                //get and populate the symbol table 
                if (verbose)
                    log.info("genarating ejb >>");
                GeneratorFactory.createGenerator(wscontext,
                        GenerationConstants.EJB_GENERATOR).genarate();
                if (verbose)
                    log.info("genarating web service wrapper >>");

                GeneratorFactory.createGenerator(wscontext,
                        GenerationConstants.AXIS_WEBSERVICE_WRAPPER_GENERATOR).genarate();
                if (verbose)
                    log.info("genarating j2ee dd >>");
                GeneratorFactory.createGenerator(wscontext, GenerationConstants.J2EE_CONTAINER_DD_GENERATOR).genarate();
                GeneratorFactory.createGenerator(wscontext, GenerationConstants.BUILD_FILE_GENERATOR).genarate();

            } else {
                //JAX-RPC mapper calling
                if (verbose)
                    log.info("starting client side code genaration .. ");

                GeneratorFactory.createGenerator(wscontext,
                        GenerationConstants.CLIENT_STUB_GENERATOR).genarate();
                (new ContextValidator(wscontext)).validateWithWSDL();

            }

            GeneratorFactory.createGenerator(wscontext,
                    GenerationConstants.HANDLER_GENERATOR).genarate();

        } catch (Exception e) {
            e.printStackTrace();
            throw new GenerationFault(e);
        }
    }

    private String getAbsolutePath(String path, String confFileLocation) {
        if (path.indexOf(":/") > -1 || path.indexOf(":\\") > -1)
            return path;
        return confFileLocation + "/" + path;

    }

    public static void main(String[] args) throws Exception {
        //String wscffile  = "./samples/book/webservice.xml";
        Ws4J2EEwithWSDL gen = new Ws4J2EEwithWSDL(args);
        gen.genarate();

    }
}
