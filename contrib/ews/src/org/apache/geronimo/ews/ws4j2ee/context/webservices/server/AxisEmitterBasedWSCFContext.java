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

package org.apache.geronimo.ews.ws4j2ee.context.webservices.server;

import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class AxisEmitterBasedWSCFContext extends AbstractWSCFContext implements WSCFContext {
    private Emitter emitter;
    private J2EEWebServiceContext j2eeweserviceContext;

    public AxisEmitterBasedWSCFContext(Emitter emitter, J2EEWebServiceContext j2eeweserviceContext) {
        this.emitter = emitter;
        this.j2eeweserviceContext = j2eeweserviceContext;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext#getDescription()
     */
    public String getDescription() {
		throw new UnsupportedOperationException();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext#getDisplayName()
     */
    public String getDisplayName() {
		throw new UnsupportedOperationException();
	}

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext#getLargeIcon()
     */
    public String getLargeIcon() {
		throw new UnsupportedOperationException();
	}

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext#getSmallIcon()
     */
    public String getSmallIcon() {
		throw new UnsupportedOperationException();
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext#getWebServicesDescription()
     */
    public WSCFWebserviceDescription[] getWebServicesDescription() {
		throw new UnsupportedOperationException();
    }

    public void serialize(java.io.Writer out) throws GenerationFault {
        try {
            out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            out.write("<webservices xmlns=\"http://java.sun.com/xml/ns/j2ee\"\n"); 
			out.write("xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\n"); 
			out.write("xmlns:ns1=\"http://www.Monson-Haefel.com/jwsbook/BookQuote\n");
			out.write("xsi:schemaLocation=\"http://java.sun.com/xml/ns/j2ee\n");
			out.write("http://www.ibm.com/standards/xml/webservices/j2ee/j2ee_web_services_1_1.xsd\" version=\"1.1\">\n");
            out.write("<webservice-description>\n");
            out.write("<webservice-description-name>" + emitter.getServiceElementName() + "</webservice-description-name>\n");
            out.write("<wsdl-file>" + j2eeweserviceContext.getMiscInfo().getWsdlFile() + "</wsdl-file>\n");
            out.write("<jaxrpc-mapping-file>" + j2eeweserviceContext.getMiscInfo().getJaxrpcfile() + "</jaxrpc-mapping-file>\n");
            out.write("<port-component>\n");
            out.write("<port-component-name>" + emitter.getPortTypeName() + "</port-component-name>\n");
            out.write("<wsdl-port xmlns:ns1=\""+ j2eeweserviceContext.getWSDLContext().getTargetNSURI() + "\">\n");
            out.write("ns1:" + j2eeweserviceContext.getWSDLContext().getTargetPort().getName());
            out.write("</wsdl-port>\n");
            out.write("<service-endpoint-interface>" + emitter.getCls().getName() + "</service-endpoint-interface>\n");
            out.write("<service-impl-bean>\n");
			
            //TODO let usprint the port type name for now here
            //we got to print the ejb name here parsing the ejb-jar.xml
            String ejbName = j2eeweserviceContext.getMiscInfo().getJ2eeComponetLink();
            if (ejbName == null)
                ejbName = emitter.getPortTypeName();
            out.write("<ejb-link >" + ejbName + "</ejb-link>\n");

            out.write("</service-impl-bean>\n");
            out.write("</port-component>\n");
            out.write("</webservice-description>\n");
            out.write("</webservices>\n");
        } catch (Exception e) {
        }
    }

}
