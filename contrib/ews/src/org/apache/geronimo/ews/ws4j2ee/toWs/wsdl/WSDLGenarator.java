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

import java.util.List;

import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.encoding.TypeMapping;
import org.apache.axis.encoding.TypeMappingImpl;
import org.apache.axis.utils.CLArgsParser;
import org.apache.axis.utils.CLOption;
import org.apache.axis.utils.Messages;
import org.apache.axis.wsdl.Java2WSDL;
import org.apache.commons.logging.Log;
import org.apache.geronimo.ews.ws4j2ee.context.ContextValidator;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.impl.AxisEmitterBasedJaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.AxisEmitterBasedWSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.impl.AxisEmitterBasedWSDLContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;

/**
 * <p>This genarated theWrapper WS required in the
 * Axis.</p>
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class WSDLGenarator extends Java2WSDL implements Generator {
    private J2EEWebServiceContext j2eewscontext;
    private String[] args;

    protected static Log log =
            LogFactory.getLog(WSDLGenarator.class.getName());

    public WSDLGenarator(J2EEWebServiceContext j2eewscontext) {
        this.j2eewscontext = j2eewscontext;
    }

    public void setArgs(String[] args) {
        this.args = args;
    }

    /**
     * run
     * checks the command-line arguments and runs the tool.
     * 
     * @param args String[] command-line arguments.
     */
    protected int run(String[] args) {
        // Parse the arguments
        CLArgsParser argsParser = new CLArgsParser(args, options);

        // Print parser errors, if any
        if (null != argsParser.getErrorString()) {
            System.err.println(Messages.getMessage("j2werror00", argsParser.getErrorString()));
            printUsage();
            return (1);
        }

        // Get a list of parsed options
        List clOptions = argsParser.getArguments();
        int size = clOptions.size();

        try {
            // Parse the options and configure the emitter as appropriate.
            for (int i = 0; i < size; i++) {
                if (parseOption((CLOption) clOptions.get(i)) == false) {
                    return (1);
                }
            }

            // validate argument combinations
            if (validateOptions() == false)
                return (1);

            // Set the namespace map
            if (!namespaceMap.isEmpty()) {
                emitter.setNamespaceMap(namespaceMap);
            }
            
			TypeMapping tm = new TypeMappingImpl(emitter.getDefaultTypeMapping());
			emitter.setTypeMapping(tm);
            
            // Find the class using the name
            emitter.setCls(className);
            // Generate a full wsdl, or interface & implementation wsdls
            if (wsdlImplFilename == null) {
                emitter.emit(wsdlFilename, mode);
            } else {
                emitter.emit(wsdlFilename, wsdlImplFilename);
            }

            // everything is good
            return (0);
        } catch (Throwable t) {
            t.printStackTrace();
            return (1);
        }
    } // run

    public void genarate() throws GenerationFault {
        try {
            //write the WSDLFile
            this.run(args);
            //initiate the wsdlContext
            this.j2eewscontext.setWSDLContext(new AxisEmitterBasedWSDLContext(emitter.getWSDL()));
            //parse the ejb-jar.xml here
            ContextValidator validator = new ContextValidator(j2eewscontext);
            //initiate the jaxrpcmapping context 
            this.j2eewscontext.setJAXRPCMappingContext(new AxisEmitterBasedJaxRpcMapperContext(emitter, j2eewscontext));
            //initiate the wscf context 
            this.j2eewscontext.setWSCFContext(new AxisEmitterBasedWSCFContext(emitter, j2eewscontext));

            //validate the j2ee context
            validator.validateWithOutWSDL(emitter);
        } catch (Exception e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }
}
