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

package org.apache.geronimo.ews.ws4j2ee.toWs.impl;

import javax.xml.namespace.QName;

import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.j2eeDD.EJBContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.Generator;
import org.apache.geronimo.ews.ws4j2ee.toWs.Writer;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2eeDeployContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2eeServerCLOptionParser;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.J2EEContainerSpecificDDGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.JaxrpcMapperGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.dd.WebContainerDDGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.ejb.EJBDDWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.ejb.EJBGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.ejb.EJBHomeWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.ejb.EJBLocalHomeWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.ejb.EJBRemoteWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.ejb.SessionBeanWriter;
import org.apache.geronimo.ews.ws4j2ee.toWs.handlers.HandlerGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.misc.BuildFileGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.wrapperWs.WrapperWsGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.ws.ClientSideWsGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.ws.ServerSideWsGenerator;
import org.apache.geronimo.ews.ws4j2ee.toWs.wsdl.WSDLGenerator;

/**
 * @author hemapani@opensource.lk
 */
public class GenerationFactoryImpl
    implements org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFactory {
    public Writer createEJBWriter(
        J2EEWebServiceContext j2eewscontext,
        EJBContext ejbcontext,
        int writerType)
        throws GenerationFault {
        if (GenerationConstants.EJB_DD_WRITER == writerType)
            return new EJBDDWriter(j2eewscontext, ejbcontext);
        else if (GenerationConstants.EJB_HOME_INTERFACE_WRITER == writerType)
            return new EJBHomeWriter(j2eewscontext, ejbcontext);
        else if (GenerationConstants.EJB_REMOTE_INTERFACE_WRITER == writerType)
            return new EJBRemoteWriter(j2eewscontext, ejbcontext);
        else if (
            GenerationConstants.EJB_LOCAL_HOME_INTERFACE_WRITER == writerType)
            return new EJBLocalHomeWriter(j2eewscontext, ejbcontext);
        else if (GenerationConstants.EJB_LOCAL_INTERFACE_WRITER == writerType)
            return new EJBLocalHomeWriter(j2eewscontext, ejbcontext);
        else if (
            GenerationConstants.EJB_IMPLEMENTATION_BEAN_WRITER == writerType)
            return new SessionBeanWriter(j2eewscontext, ejbcontext);
        else
            throw new GenerationFault("the writer not found");
    }

    public Generator createEJBGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new EJBGenerator(j2eewscontext);
    }
    public Generator createWrapperWsGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new WrapperWsGenerator(j2eewscontext);
    }
    public Generator createClientSideWsGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new ClientSideWsGenerator(j2eewscontext);
    }

    public Generator createWSDLGenerator(J2EEWebServiceContext wscontext,
    	Emitter emitter,
		Ws4J2eeDeployContext clparser)
        throws GenerationFault {
        return new WSDLGenerator(wscontext,emitter,clparser);
    }
    public Generator createServerSideWsGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new ServerSideWsGenerator(j2eewscontext);
    }
    public Generator createHandlerGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new HandlerGenerator(j2eewscontext);
    }
    public Generator createJaxrpcMapperGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new JaxrpcMapperGenerator(j2eewscontext);
    }
    public Generator createContainerSpecificDDGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new J2EEContainerSpecificDDGenerator(j2eewscontext);
    }
    public Generator createBuildFileGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new BuildFileGenerator(j2eewscontext);
    }
    public Generator createWebContainerDDGenerator(J2EEWebServiceContext j2eewscontext)
        throws GenerationFault {
        return new WebContainerDDGenerator(j2eewscontext);
    }

}
