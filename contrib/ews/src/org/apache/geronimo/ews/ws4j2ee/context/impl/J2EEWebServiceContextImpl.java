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

package org.apache.geronimo.ews.ws4j2ee.context.impl;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.context.MiscInfo;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenarationFault;

/**
 * <p>Code should use parsers and create runtime representation
 * of the information taken fom the WSDL and configaration files.</p>
 * <p/>
 * <p>depend on hasWSDL or the not the implementation should
 * <ol>
 * <li>parse the WSDL and populate informatio in <code>WSDLContext</code></li>
 * <li>parse the SEI or EJB and populate the information in <code>WSDLContext</code>
 * with the help of the jaxrpc mapping file information.
 * </li>
 * </ol>
 * </p>
 */
public class J2EEWebServiceContextImpl implements J2EEWebServiceContext {
    private boolean hasWSDL = true;
    private WSCFContext wscfcontext;
    private WSDLContext wsdlcontext;
    private JaxRpcMapperContext jaxrpcmappingcontext;
    private MiscInfo miscInfo;

    public J2EEWebServiceContextImpl(boolean hasWSDL) {
        this.hasWSDL = hasWSDL;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext#getWSDLContext()
     */
    public WSDLContext getWSDLContext() {
        return wsdlcontext;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext#setWSDLContext(org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext)
     */
    public void setWSDLContext(WSDLContext wsdlcontext) {
        this.wsdlcontext = wsdlcontext;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext#getJAXRPCMappingContext()
     */
    public JaxRpcMapperContext getJAXRPCMappingContext() {
        return jaxrpcmappingcontext;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext#setJAXRPCMappingContext(org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext)
     */
    public void setJAXRPCMappingContext(JaxRpcMapperContext context) {
        this.jaxrpcmappingcontext = context;

    }

    public WSCFContext getWSCFContext() {
        return wscfcontext;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext#setWSCFContext(org.apache.geronimo.ews.ws4j2ee.context.webservices.interfaces.WSCFContext)
     */
    public void setWSCFContext(WSCFContext wscfcontext) {
        this.wscfcontext = wscfcontext;

    }

    public MiscInfo getMiscInfo() {
        return miscInfo;
    }

    /**
     * @param info 
     */
    public void setMiscInfo(MiscInfo info) {
        this.miscInfo = info;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext#validate()
     */
    public void validate() {
        if (wscfcontext == null || miscInfo == null ||
                (hasWSDL && wsdlcontext == null) || jaxrpcmappingcontext == null)
            throw new UnrecoverableGenarationFault("valdation of the j2ee context failed");
        miscInfo.validate();
    }

}
