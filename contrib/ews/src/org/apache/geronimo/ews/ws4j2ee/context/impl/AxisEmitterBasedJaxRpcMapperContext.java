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
import java.lang.reflect.Method;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import javax.wsdl.Binding;
import javax.wsdl.Operation;
import javax.wsdl.Part;
import javax.wsdl.Port;
import javax.wsdl.Service;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.namespace.QName;

import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.FullyQualifiedClassType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.JavaTypeType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.JavaWsdlMapping;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.MethodParamPartsMappingType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.ObjectFactory;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.PackageMappingType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.ParameterModeType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.PortMappingType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.ServiceEndpointMethodMappingType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.WsdlMessageMappingType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.WsdlMessagePartNameType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.WsdlMessageType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.WsdlReturnValueMappingType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.XsdAnyURIType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.XsdNonNegativeIntegerType;
import org.apache.geronimo.ews.jaxrpcmapping.descriptor.XsdQNameType;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenarationFault;

/**
 * This class wrap the JAXRPCMapper and only expose a interface to
 * the rest of the WS4j2ee.
 * 
 * @author hemapani
 */
public class AxisEmitterBasedJaxRpcMapperContext implements JaxRpcMapperContext {
    private Emitter emitter;
    private J2EEWebServiceContext j2eewscontext;
    private HashMap methods = new HashMap();

    public AxisEmitterBasedJaxRpcMapperContext(Emitter emitter, J2EEWebServiceContext j2eewscontext) {
        this.emitter = emitter;
        this.j2eewscontext = j2eewscontext;
        Method[] methods = emitter.getCls().getMethods();
        for (int i = 0; i < methods.length; i++) {
            this.methods.put(methods[0].getName(), methods[0]);
        }

    }

    /**
     * @param messageQName 
     * @return 
     */
    public String getExceptionType(QName messageQName) {
        throw new UnsupportedOperationException();
        //return jaxrpcmapper.getExceptionType(messageQName);
    }

    /**
     * @param bEntry    
     * @param operation 
     * @return 
     */
    public String getJavaMethodName(BindingEntry bEntry, Operation operation) {
        return operation.getName();
    }

    /**
     * @param bEntry    
     * @param operation 
     * @param position  
     * @return 
     */
    public String getJavaMethodParamType(BindingEntry bEntry,
                                         Operation operation,
                                         int position,QName type) {
        Method m = (Method) this.methods.get(operation.getName());
        //axis do not map the method names or types
        //so this should do 
        if (m == null)
            throw new UnrecoverableGenarationFault("logic expected is differnet .. worng" +
                    "design decision");
        return m.getParameterTypes()[position].getName();
    }

    /**
     * @param bEntry    
     * @param operation 
     * @return 
     */
    public String getJavaMethodReturnType(BindingEntry bEntry,
                                          Operation operation) {
        Method m = (Method) this.methods.get(operation.getName());
        //axis do not map the method names or types
        //so this should do 
        if (m == null)
            throw new UnrecoverableGenarationFault("logic expected is differnet .. worng" +
                    "design decision");
        return m.getReturnType().getName();
    }

    /**
     * @param typeQName 
     * @return 
     */
    public String getJavaType(QName typeQName) {
        throw new UnsupportedOperationException();
        // return jaxrpcmapper.getJavaType(typeQName);
    }

    /**
     * @return 
     */
    public JavaWsdlMapping getMapping() {
        throw new UnsupportedOperationException();
    }

    /**
     * @param port 
     * @return 
     */
    public String getPortName(Port port) {
        return emitter.getServicePortName();
    }

    /**
     * @param ptEntry 
     * @param bEntry  
     * @return 
     */
    public String getServiceEndpointInterfaceName(PortTypeEntry ptEntry,
                                                  BindingEntry bEntry) {
        return emitter.getPortTypeName();
    }

    /**
     * @param entry 
     * @return 
     */
    public String getServiceInterfaceName(ServiceEntry entry) {
        return emitter.getServiceElementName();
    }

    /**
     * @param path 
     */
    public void loadMappingFromDir(String path) {
        throw new UnsupportedOperationException();
    }

    /**
     * @param is 
     */
    public void loadMappingFromInputStream(InputStream is) {
        throw new UnsupportedOperationException();
    }

    public void serialize(Writer out) throws GenerationFault {

        try {
            JAXBContext jc = JAXBContext.newInstance("org.apache.geronimo.ews.jaxrpcmapping.descriptor");
            ObjectFactory objFactory = new ObjectFactory();

            JavaWsdlMapping jaxrpcmap = objFactory.createJavaWsdlMapping();
            jaxrpcmap.setVersion(new BigDecimal("1.0"));
            
//adding pckage mappings
            Map map = emitter.getNamespaceMap();
            if (map != null) {
                Iterator packages = map.keySet().iterator();
                while (packages.hasNext()) {
                    PackageMappingType pkgmap = objFactory.createPackageMappingType();
                    //set the package name
                    FullyQualifiedClassType packagename = objFactory.createFullyQualifiedClassType();
                    String pkg = (String) packages.next();
                    
                    if(pkg.equals(j2eewscontext.getMiscInfo().getJaxrpcSEI())){
                   		break;
                    }
                    packagename.setValue(pkg);
                    pkgmap.setPackageType(packagename);
                    //set the namespace URI
                    XsdAnyURIType nsuri = objFactory.createXsdAnyURIType();
                    nsuri.setValue((String) map.get(pkg));
                    pkgmap.setNamespaceURI(nsuri);
                    //done :) add the package type
                    jaxrpcmap.getPackageMapping().add(pkgmap);
                }
            }
            
//adding Service mappings
///////////////////////////
            Service service = j2eewscontext.getMiscInfo().gettargetService().getService();
            org.apache.geronimo.ews.jaxrpcmapping.descriptor.JavaWsdlMappingType.ServiceInterfaceMapping servciemaping = objFactory.createJavaWsdlMappingTypeServiceInterfaceMapping();
			
            	
            //get the sevice QName	
            XsdQNameType serviceName = objFactory.createXsdQNameType();
            serviceName.setValue(service.getQName());
            servciemaping.setWsdlServiceName(serviceName);
        	
            //set the service java Name 
            FullyQualifiedClassType serviceJavaName = objFactory.createFullyQualifiedClassType();

            String name = emitter.getCls().getName();
            int index = name.lastIndexOf('.');
            String packageName = "";
            if (index > 0)
                packageName = name.substring(0, index + 1);

            serviceJavaName.setValue(packageName + emitter.getServiceElementName());

            servciemaping.setServiceInterface(serviceJavaName);
            jaxrpcmap.getServiceInterfaceMappingAndServiceEndpointInterfaceMapping().add(servciemaping);

            Port wsdlport = j2eewscontext.getMiscInfo().getTargetPort();
            Binding binding = wsdlport.getBinding();
         	
            //create a portmap
            PortMappingType portmap = objFactory.createPortMappingType();
            //java port name 
            org.apache.geronimo.ews.jaxrpcmapping.descriptor.String javaportname = objFactory.createString();
            javaportname.setValue(emitter.getServicePortName());
            portmap.setJavaPortName(javaportname);
            //wsdl port name 
            org.apache.geronimo.ews.jaxrpcmapping.descriptor.String wsdlportname = objFactory.createString();
            wsdlportname.setValue(wsdlport.getName());
            portmap.setPortName(wsdlportname);

            servciemaping.getPortMapping().add(portmap);

            if (binding == null)
                throw new UnrecoverableGenarationFault("no port discription not match with the wsdl file");

            org.apache.geronimo.ews.jaxrpcmapping.descriptor.JavaWsdlMappingType.ServiceEndpointInterfaceMapping seimapping = objFactory.createJavaWsdlMappingTypeServiceEndpointInterfaceMapping();
            
//set java SEI name
            FullyQualifiedClassType seijavaName = objFactory.createFullyQualifiedClassType();
            seijavaName.setValue(emitter.getCls().getName());
            seimapping.setServiceEndpointInterface(seijavaName);
//set the wsdl finding name
            XsdQNameType bindingQName = objFactory.createXsdQNameType();
            bindingQName.setValue(binding.getQName());
            seimapping.setWsdlBinding(bindingQName);
//set the wsdl port type
            XsdQNameType portTypeQName = objFactory.createXsdQNameType();
            portTypeQName.setValue(binding.getPortType().getQName());
            seimapping.setWsdlPortType(portTypeQName);
            
//add the operation mappings
            Iterator ops = binding.getPortType().getOperations().iterator();

            while (ops.hasNext()) {
                ServiceEndpointMethodMappingType seimethodmapping = objFactory.createServiceEndpointMethodMappingType();
                Operation op = (Operation) ops.next();
            	
                //set the java method name
                org.apache.geronimo.ews.jaxrpcmapping.descriptor.String javamethodname = objFactory.createString();
                javamethodname.setValue(op.getName());
                seimethodmapping.setJavaMethodName(javamethodname);
            
                //TODO not sure what this WrappedElement do. FIXIT
                //seimethodmapping.setWrappedElement();
            	
                //set wsdl method name 
                org.apache.geronimo.ews.jaxrpcmapping.descriptor.String wsdlmethodname = objFactory.createString();
                wsdlmethodname.setValue(op.getName());
                seimethodmapping.setWsdlOperation(wsdlmethodname);
            
                //this work only when the method names are same
                //im printing it so that it is easier for user to change 
                //it am sure that no body will writing nor webservice.xml 
                //or jaxrpcmapping.xml files if there is a short cut.
				
                //create return type  Map
                WsdlReturnValueMappingType retvalmap = objFactory.createWsdlReturnValueMappingType();
            	
                //set return type
                FullyQualifiedClassType retValjavaName = objFactory.createFullyQualifiedClassType();
                retValjavaName.setValue(((Method) methods.get(op.getName())).getReturnType().getName());
                retvalmap.setMethodReturnValue(retValjavaName);
            
                //set return type info
                Map parts = op.getOutput().getMessage().getParts();
                if (parts != null) {
                    Iterator partIt = parts.values().iterator();
                    if (partIt.hasNext()) {
                        //set wsdl message type
                        WsdlMessageType messageType = objFactory.createWsdlMessageType();
                        messageType.setValue(op.getOutput().getMessage().getQName());
                        retvalmap.setWsdlMessage(messageType);
            			
                        //set wsdl message part type
                        WsdlMessagePartNameType messagePartName = objFactory.createWsdlMessagePartNameType();
                        messagePartName.setValue(((Part) partIt.next()).getName());
                        retvalmap.setWsdlMessagePartName(messagePartName);
                    }

                }

                seimethodmapping.setWsdlReturnValueMapping(retvalmap);
            
            	
                //create method param parts mappings	
                int position = 0;
                Class[] params = ((Method) methods.get(op.getName())).getParameterTypes();

                Iterator parmIt = null;
                Map parameters = op.getInput().getMessage().getParts();
                if (parameters != null) {
                    parmIt = parameters.values().iterator();
                }

                while (parmIt != null && parmIt.hasNext()) {
                    Part part = (Part) parmIt.next();
                    //create parts mapping
                    MethodParamPartsMappingType partsMapping = objFactory.createMethodParamPartsMappingType();
                    //set parameter position
                    XsdNonNegativeIntegerType pos = objFactory.createXsdNonNegativeIntegerType();
                    pos.setValue(new BigInteger(Integer.toString(position)));
                    partsMapping.setParamPosition(pos);
            		
                    //set parameter java typr
                    JavaTypeType javaType = objFactory.createJavaTypeType();
                    javaType.setValue(params[position].getName());
                    partsMapping.setParamType(javaType);
            		
                    //set message mapping
                    WsdlMessageMappingType msgmappingType = objFactory.createWsdlMessageMappingType();
                    //set mode
                    ParameterModeType mode = objFactory.createParameterModeType();
                    mode.setValue("IN");
                    msgmappingType.setParameterMode(mode);
                    //TODO Im a not sure what to do with the header 
                    //msgmappingType.setSoapHeader();
                    //set wsdl message type
                    WsdlMessageType messageType = objFactory.createWsdlMessageType();
                    messageType.setValue(op.getInput().getMessage().getQName());
                    msgmappingType.setWsdlMessage(messageType);
                    //set wsdl message part type
                    WsdlMessagePartNameType messagePartName = objFactory.createWsdlMessagePartNameType();
                    messagePartName.setValue(part.getName());
                    msgmappingType.setWsdlMessagePartName(messagePartName);

                    partsMapping.setWsdlMessageMapping(msgmappingType);
                    seimethodmapping.getMethodParamPartsMapping().add(partsMapping);
                }

                seimapping.getServiceEndpointMethodMapping().add(seimethodmapping);

            }
            jaxrpcmap.getServiceInterfaceMappingAndServiceEndpointInterfaceMapping().add(seimapping);
                  
//axis do not support XML type mapping or Exception
//maping to be specifed so I do not brother tp print them out. 
//jaxrpcmap.getExceptionMapping();
//jaxrpcmap.getJavaXmlTypeMapping();
            
            Marshaller m = jc.createMarshaller();
            m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, Boolean.TRUE);
            m.marshal(jaxrpcmap, out);

            Unmarshaller u = jc.createUnmarshaller();
        } catch (Exception e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }
}
