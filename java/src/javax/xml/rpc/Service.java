/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
package javax.xml.rpc;



import javax.xml.rpc.encoding.TypeMappingRegistry;
import javax.xml.rpc.namespace.QName;


/**
 * A service class acts as a factory of the following objects:
 * <UL>
 * <LI>Dynamic proxy for a service port.
 * <LI>Instance of the type javax.xml.rpc.Call for the dynamic
 *    invocation of a remote operation on a service port. 
 * <LI>Instance of a generated static stub class
 * </UL>
 * 
 * <p>The Service implementation class is required to implement 
 * java.io.Serializable and javax.naming.Referenceable 
 * interfaces to support registration in the JNDI namespace.
 *
 * @author
 * @version 0.1
 */
public interface Service
    extends java.io.Serializable, javax.naming.Referenceable {

    /**
     * The getPort method returns a dynamic proxy for the specified service port. A service client uses this dynamic 
     * proxy to invoke operations on the target service port. The proxyInterface specifies the service definition 
     * interface that is supported by the created dynamic proxy.
     *
     * @param portName - Qualified name of the service port in the WSDL based service description
     * @param proxyInterface - Service definition interface supported by the dynamic proxy
     *
     * @return Dynamic proxy object that supports the service definition interface that extends the java.rmi.Remote
     *
     * @throws JAXRPCException - If the service class fails to create a dynamic proxy
     */
    public java.rmi.Remote getPort(QName portName, Class proxyInterface)
        throws JAXRPCException;

    /**
     * Creates a Call instance.
     *
     * @param - The qualified name for the target service port
     *
     * @return Call object
     *
     * @throws JAXRPCException - If the Service class fails to create a Call object
     */
    public Call createCall(QName portName) throws JAXRPCException;

    /**
     * Creates a Call instance.
     *
     * @param portName - The qualified name for the target service port
     * @param operationName - Name of the operation for which this Call object is created.
     *
     * @return Call object
     *
     * @throws JAXRPCException - If the Service class fails to create a Call object
     */
    public Call createCall(QName portName, String operationName)
        throws JAXRPCException;

    /**
     * Creates an empty Call object that needs to be configured using the setter methods on the Call interface.
     *
     * @return  Call object
     *
     * @throws JAXRPCException
     */
    public Call createCall() throws JAXRPCException;

    /**
     * Gets location of the WSDL document for this Service.
     *
     * @return Location of the WSDL document for this service
     */
    public java.net.URL getWSDLDocumentLocation();

    /**
     * Gets the name of this Service.
     *
     * @return Qualified name of this service
     */
    public QName getServiceName();

    /**
     * Gets the list of qualified names of the ports grouped by this service
     *
     * @return iterator containing list of qualified names of the ports  
     */
    public java.util.Iterator getPorts();

    /**
     * Registers a type mapping registry with this Service object.
     *
     * @param registry - TypeMappingRegistry object
     *
     * @throws JAXRPCException - if there is an error in the configuration of the TypeMappingRegistry
     */
    public void setTypeMappingRegistry(TypeMappingRegistry registry)
        throws JAXRPCException;

    /**
     * Gets the TypeMappingRegistry registered with this Service object
     *
     * @return  The configured TypeMappingRegistry or null if no TypeMappingRegistry has been set on the Service object
     */
    public TypeMappingRegistry getTypeMappingRegistry();
}


