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
import java.util.Iterator;
import java.util.Map;

import javax.wsdl.Operation;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.xml.namespace.QName;

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.jaxrpcmapping.J2eeEmitter;
import org.apache.geronimo.ews.jaxrpcmapping.JaxRpcMapper;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.JavaWsdlMapping;
import org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenerationFault;
import org.apache.geronimo.ews.ws4j2ee.utils.Utils;

/**
 * This class wrap the JAXRPCMapper and only expose a interface to
 * the rest of the WS4j2ee.
 * @see org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class JaxRpcMapperImpl implements JaxRpcMapperContext {
    private JaxRpcMapper jaxrpcmapper;
    private J2eeEmitter j2ee;

    public JaxRpcMapperImpl(JaxRpcMapper jaxrpcmapper,J2eeEmitter j2ee) {
        this.jaxrpcmapper = jaxrpcmapper;
        this.j2ee = j2ee;
    }

    /**
     * @param messageQName 
     * @return 
     */
    public String getExceptionType(QName messageQName) {
        String exceptionName = jaxrpcmapper.getExceptionType(messageQName);
        if(exceptionName == null){
			exceptionName = j2ee.getJavaName(messageQName);
			if(exceptionName == null)
				throw new UnrecoverableGenerationFault("the exception name in a SEI OP can not be null" +
					"possibly be a bug check the WSDL2Java data extraction");
        }	
		return 	exceptionName;
        
    }

    /**
     * @param bEntry    
     * @param operation 
     * @return 
     */
    public String getJavaMethodName(BindingEntry bEntry, Operation operation) {
    	String opName = jaxrpcmapper.getJavaMethodName(bEntry, operation);
    	if(opName == null)
			opName = operation.getName();
		if(opName == null)
			throw new UnrecoverableGenerationFault("the method name in a SEI OP can not be null" +
				"possibly be a bug check the WSDL2Java data extraction");
		
		return 	Utils.firstCharacterToLowerCase(opName);
    }

    /**
     * @param bEntry    
     * @param operation 
     * @param position  
     * @return 
     */
    public String getJavaMethodParamType(BindingEntry bEntry,
                                         Operation operation,
                                         int position,QName parmType) {
        String type = jaxrpcmapper.getJavaMethodParamType(bEntry, operation, position);
        if(type == null){
			type = j2ee.getJavaName(parmType);
			if(type == null)
				throw new UnrecoverableGenerationFault("the parm type name in a SEI OP can not be null" +
					"possibly be a bug check the WSDL2Java data extraction");  
		}
        return type;
    }

    /**
     * @param bEntry    
     * @param operation 
     * @return 
     */
    public String getJavaMethodReturnType(BindingEntry bEntry,
                                          Operation operation) {
        String returnType = jaxrpcmapper.getJavaMethodReturnType(bEntry, operation);
        if(returnType == null){
		  Map parts = operation.getOutput().getMessage().getParts();
		  if (parts != null) {
			  Iterator returnlist = parts.values().iterator();
			  if (returnlist.hasNext()) {
				  Part part = (Part) returnlist.next();
				  returnType = jaxrpcmapper.getJavaType(part.getTypeName());
				  if(returnType == null)
				  	returnType = j2ee.getJavaName(part.getTypeName());
			  }
		  }
        }
        return returnType;
       // fixed inside 
       // return Utils.jni2javaName(returnType);
    }
	
			


    /**
     * @param typeQName 
     * @return 
     */
    public String getJavaType(QName typeQName) {
        String type = jaxrpcmapper.getJavaType(typeQName);
        if(type == null)
        	type = j2ee.getJavaName(typeQName);
        if(type == null)
			throw new UnrecoverableGenerationFault("the type name can" +
				" not be null possibly be a bug check the WSDL2Java data extraction");
		return type;			
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
        String portName = jaxrpcmapper.getPortName(port);
        if(portName == null){
			portName = port.getName();
			if(portName == null)
				throw new UnrecoverableGenerationFault("the portName can" +
				" not be null, possibly be a bug check the WSDL2Java data extraction");
		}
		return portName;
    }

    /**
     * @param ptEntry 
     * @param bEntry  
     * @return 
     */
    public String getServiceEndpointInterfaceName(PortTypeEntry ptEntry,
                                                  BindingEntry bEntry) {
		String seiName = jaxrpcmapper.getServiceEndpointInterfaceName(ptEntry, bEntry);
        if(seiName == null){
			seiName = ptEntry.getName();
			if(seiName == null)
				throw new UnrecoverableGenerationFault("the seiName can" +
				" not be null, possibly be a bug check the WSDL2Java data extraction");
        }
        return seiName;
    }

    /**
     * @param entry 
     * @return 
     */
    public String getServiceInterfaceName(ServiceEntry entry) {
        String serviceInterface = jaxrpcmapper.getServiceInterfaceName(entry);
        if(serviceInterface == null){
			serviceInterface = entry.getName();
			if(serviceInterface == null)
				throw new UnrecoverableGenerationFault("the serviceInterface can" +
				" not be null, possibly be a bug check the WSDL2Java data extraction");
        }
        return serviceInterface;
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
