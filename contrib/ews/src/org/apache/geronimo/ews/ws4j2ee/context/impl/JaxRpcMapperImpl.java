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

import java.io.InputStream;
import java.io.Writer;

import javax.wsdl.Operation;
import javax.wsdl.Port;
import javax.xml.namespace.QName;

import org.apache.geronimo.ews.jaxrpcmapping.JaxRpcMapper;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.JavaWsdlMapping;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext;


/**
 * This class wrap the JAXRPCMapper and only expose a interface to
 * the rest of the WS4j2ee.
 * @author hemapani
 */
public class JaxRpcMapperImpl implements JaxRpcMapperContext{
	private JaxRpcMapper jaxrpcmapper;
	
	public JaxRpcMapperImpl(JaxRpcMapper jaxrpcmapper){
		this.jaxrpcmapper = jaxrpcmapper;
	}
    /**
     * @param messageQName
     * @return
     */
    public String getExceptionType(QName messageQName) {
        return jaxrpcmapper.getExceptionType(messageQName);
    }

    /**
     * @param bEntry
     * @param operation
     * @return
     */
    public String getJavaMethodName(BindingEntry bEntry, Operation operation) {
        return jaxrpcmapper.getJavaMethodName(bEntry, operation);
    }

    /**
     * @param bEntry
     * @param operation
     * @param position
     * @return
     */
    public String getJavaMethodParamType(
        BindingEntry bEntry,
        Operation operation,
        int position) {
        return jaxrpcmapper.getJavaMethodParamType(bEntry, operation, position);
    }

    /**
     * @param bEntry
     * @param operation
     * @return
     */
    public String getJavaMethodReturnType(
        BindingEntry bEntry,
        Operation operation) {
        return jaxrpcmapper.getJavaMethodReturnType(bEntry, operation);
    }

    /**
     * @param typeQName
     * @return
     */
    public String getJavaType(QName typeQName) {
        return jaxrpcmapper.getJavaType(typeQName);
    }

    /**
     * @return
     */
    public JavaWsdlMapping getMapping() {
        return jaxrpcmapper.getMapping();
    }

    /**
     * @param port
     * @return
     */
    public String getPortName(Port port) {
        return jaxrpcmapper.getPortName(port);
    }

    /**
     * @param ptEntry
     * @param bEntry
     * @return
     */
    public String getServiceEndpointInterfaceName(
        PortTypeEntry ptEntry,
        BindingEntry bEntry) {
        return jaxrpcmapper.getServiceEndpointInterfaceName(ptEntry, bEntry);
    }

    /**
     * @param entry
     * @return
     */
    public String getServiceInterfaceName(ServiceEntry entry) {
        return jaxrpcmapper.getServiceInterfaceName(entry);
    }

    /**
     * @param path
     */
    public void loadMappingFromDir(String path) {
        jaxrpcmapper.loadMappingFromDir(path);
    }

    /**
     * @param is
     */
    public void loadMappingFromInputStream(InputStream is) {
        jaxrpcmapper.loadMappingFromInputStream(is);
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext#serialize()
     */
    public void serialize(Writer out) {
        throw new UnsupportedOperationException("when the wsdl is avalibe serialization not reqired");
    }

}
