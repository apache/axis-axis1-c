/*
 * Copyright 2001-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.geronimo.ews.ws4j2ee.toWs;

import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.EJBContext;

/**
 * @author hemapani@opensource.lk
 */
public interface GenerationFactory {
    public Writer createEJBWriter(
        J2EEWebServiceContext j2eewscontext,
        EJBContext ejbcontext,
        int writerType)
        throws GenerationFault;
    public Generator createEJBGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
    public Generator createWrapperWsGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
    public Generator createClientSideWsGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
	public Generator createWSDLGenerator(
		J2EEWebServiceContext wscontext,
		Emitter emitter,
		Ws4J2eeDeployContext clparser)throws GenerationFault;
    public Generator createServerSideWsGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
    public Generator createHandlerGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
    public Generator createJaxrpcMapperGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
    public Generator createContainerSpecificDDGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
    public Generator createBuildFileGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;
    public Generator createWebContainerDDGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault;

}
