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

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.J2EEContainerSpecificDDGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.JaxrpcMapperGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.WebContainerDDGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.WebServiceDDGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.ejb.EJBGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.handlers.HandlerGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.misc.BuildFileGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.wrapperWs.WrapperWsGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.ws.ClientSideWsGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.ws.ServerSideWsGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.wsdl.WSDLGenerator;

/**
 * <p>This class is for keep the interface and the concreate implementation of the
 * <code>Generator</code> separate. It is go without saying that the only place where
 * the concrete implementation of the Generator class can refernce is this class.</p>
 */
public class GeneratorFactory {
    public static Generator createGenerator(J2EEWebServiceContext j2eewscontext,
                                            int genaratorType) throws GenerationFault {
        if (genaratorType == GenerationConstants.EJB_GENERATOR) {
            return new EJBGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.AXIS_WEBSERVICE_WRAPPER_GENERATOR) {
            return new WrapperWsGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.CLIENT_STUB_GENERATOR) {
            return new ClientSideWsGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.WSDL_GENERATOR) {
            return new WSDLGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.SEI_AND_TYPES_GENERATOR) {
            return new ServerSideWsGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.HANDLER_GENERATOR) {
            return new HandlerGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.JAXRPCMAPPER_GENERATOR) {
            return new JaxrpcMapperGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.WEBSERVICEDD_GENERATOR) {
            return new WebServiceDDGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.J2EE_CONTAINER_DD_GENERATOR) {
            return new J2EEContainerSpecificDDGenerator(j2eewscontext);
        } else if (genaratorType == GenerationConstants.BUILD_FILE_GENERATOR) {
            return new BuildFileGenerator(j2eewscontext);
        }else if(genaratorType == GenerationConstants.WEB_CONTAINER_DD_GENERATOR){ 
        	return new WebContainerDDGenerator(j2eewscontext);
        } else
            throw new IllegalArgumentException("No genarator exists for the genarator type given");
    }
}
