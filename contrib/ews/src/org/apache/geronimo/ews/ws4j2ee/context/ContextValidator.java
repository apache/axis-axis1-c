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

package org.apache.geronimo.ews.ws4j2ee.context;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.wsdl.Fault;
import javax.wsdl.Operation;
import javax.wsdl.Port;
import javax.wsdl.Service;
import javax.xml.namespace.QName;

import org.apache.axis.wsdl.fromJava.Emitter;
import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.Parameter;
import org.apache.axis.wsdl.symbolTable.Parameters;
import org.apache.axis.wsdl.symbolTable.PortEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.ws4j2ee.context.impl.SEIOperationImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenerationFault;

/**
 * <p>Before the code genaration this class is used to analyis the parse inforemation
 * and make sure that the data populated in the different *Context* are
 * consistent. This class will populate the most of the infomation in the
 * MiscInfo.</p>
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ContextValidator {
    private J2EEWebServiceContext context;

    public ContextValidator(J2EEWebServiceContext context) throws GenerationFault {
        try {
            this.context = context;
        } catch (Exception e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }

    /**
     * <p>Just as in the server side this code find the WSDL Service and WSDLport and
     * populate them in the MiscInfo</p>
     * 
     * @param emitter 
     * @throws GenerationFault 
     */
    public void validateWithOutWSDL(Emitter emitter) throws GenerationFault {
        try {
            Collection servicesCollection = context.getWSDLContext().getServices();
            if (servicesCollection.size() > 1)
                throw new UnrecoverableGenerationFault("we are supporting one service yet");
            Iterator services = servicesCollection.iterator();
            Service service = null;
            if (services.hasNext()) {
                service = ((Service) services.next());
                context.getMiscInfo().settargetService(new ServiceEntry(service));
            }
            
			//get the service ports 
            Collection portCollecton = service.getPorts().values();
			//just as before if there are more than one servie just let
			//it failed
            if (servicesCollection.size() > 1)
                throw new UnrecoverableGenerationFault("we are supporting one port yet");
            Iterator portList = portCollecton.iterator();
            Port wsdlport = null;
            while (portList.hasNext()) {
				wsdlport = (Port) portList.next();
                context.getMiscInfo().setTargetPort(wsdlport);
            }

		  if (wsdlport == null)
			  throw new UnrecoverableGenerationFault("no port discription not match with the wsdl file");
		  QName bindingName = wsdlport.getBinding().getQName();
		  BindingEntry wsdlbinding = context.getWSDLContext().getBinding(bindingName);
		  context.getMiscInfo().settargetBinding(wsdlbinding);
		  QName portTypename = wsdlbinding.getBinding().getPortType().getQName();
		  PortTypeEntry port = context.getWSDLContext().getPortType(portTypename);
		  if(port == null)
		  		throw new UnrecoverableGenerationFault("port type must exits");
		  context.getMiscInfo().setTargetPortType(port);
        } catch (Exception e) {
            throw GenerationFault.createGenerationFault(e);
        }
    }

    public void validateWithWSDL() {
        WSCFWebserviceDescription wscfwsdis = context.getMiscInfo().getWscfdWsDesxription();
        WSCFPortComponent[] ports = wscfwsdis.getPortComponent();
        if (ports == null || ports.length == 0)
            throw new UnrecoverableGenerationFault("no port discription found in the" +
                    "webservice.xml file");
        WSCFPortComponent port = ports[0];
        context.getMiscInfo().setWscfport(port);
		String ejbLink = port.getServiceImplBean().getEjblink();
        // context.getMiscInfo().setJaxrpcSEI(port.getServiceEndpointInterface());
        if(ejbLink != null){
	        context.getMiscInfo().setEndpointImplbean(port.getServiceEndpointInterface() + "Bean");
	        context.getMiscInfo().setEjbhome(port.getServiceEndpointInterface() + "Home");
	        context.getMiscInfo().setEjbsei(port.getServiceEndpointInterface() + "EJB");
			context.getMiscInfo().setEjblocalhome(port.getServiceEndpointInterface() + "LocalHome");
			context.getMiscInfo().setEjblocalsei(port.getServiceEndpointInterface() + "LocalEJB");
	        context.getMiscInfo().setEjbName(port.getServiceImplBean().getEjblink());
	    }else{
			context.getMiscInfo().setImplwithEJB(false);
	    }
        QName portName = new QName(port.getWsdlPort().getNamespaceURI(), port.getWsdlPort().getLocalpart());

        PortEntry wsdlport = context.getWSDLContext().getPort(portName);

		if (wsdlport == null)
			throw new UnrecoverableGenerationFault("wsdl port can not be null, you may have the " +
				"wsdlport define wrongly on the webservice.xml");
        Iterator services = context.getWSDLContext().getServices().iterator();
        while (services.hasNext()) {
            ServiceEntry service = (ServiceEntry) services.next();
            Iterator portList = service.getService().getPorts().values().iterator();
            while (portList.hasNext()) {
                if (((Port) portList.next()) == wsdlport.getPort()) {
                    context.getMiscInfo().settargetService(service);
                    break;
                }
            }

        }

        if (wsdlport == null)
            throw new UnrecoverableGenerationFault("no port discription not match with the wsdl file");
        QName bindingName = wsdlport.getPort().getBinding().getQName();

        BindingEntry wsdlbinding = context.getWSDLContext().getBinding(bindingName);
        context.getMiscInfo().settargetBinding(wsdlbinding);

        QName portTypename = wsdlbinding.getBinding().getPortType().getQName();
        context.getMiscInfo().setTargetPortType(context.getWSDLContext().getPortType(portTypename));

        context.validate();
			
            //find and populate the information about the SEI in the 
            //MiscInfo
		String seiName = context.getJAXRPCMappingContext()
			.getServiceEndpointInterfaceName(context.getMiscInfo().getTargetPortType(),context.getMiscInfo().gettargetBinding());
		context.getMiscInfo().setJaxrpcSEI(seiName);	    
			
        List operations = context.getMiscInfo().getTargetPortType().getPortType().getOperations();
        for (int i = 0; i < operations.size(); i++) {
            SEIOperation seiOp = new SEIOperationImpl();

            Operation op = (Operation) operations.get(i);
            BindingEntry binding = context.getMiscInfo().gettargetBinding();
            
			//got to get the same parameter order as the JAXRPC mapper does
			//So I am using the same methods. Can somebody find something better?? 
			Parameters parms = binding.getParameters(op);
			//set return type	
			 String returnType = context.getJAXRPCMappingContext().getJavaMethodReturnType(binding, op);
			 seiOp.setReturnType(returnType);


			 //set method name 
			 String methodName = context.getJAXRPCMappingContext().getJavaMethodName(binding, op);
			 seiOp.setMethodName(methodName);

			//Iterator paramlist = parms.list.iterator();
			 String parameterName = null;
			 String parameterType = null;	  
			
			 //find the parameters and add each parameter to parameter list 
			 for (int paramCount = 0;paramCount < parms.list.size();paramCount++) {
				 Parameter p = (Parameter) parms.list.get(paramCount);
				 parameterName = p.getName();
				 parameterType = context.getJAXRPCMappingContext().getJavaMethodParamType(binding, op, paramCount,p.getType().getQName());
				 seiOp.addParameter(parameterType, parameterName);
			 }
			 //let us find the faults
			 Map faults = parms.faults;
			 if (faults != null) {
				 Iterator it = faults.values().iterator();
				 while (it.hasNext()) {
					 Fault fault = (Fault) it.next();
					 String faulltName = context.getJAXRPCMappingContext()
							 .getExceptionType(fault.getMessage().getQName());
					 seiOp.addFault(faulltName);
				 }
			 }
            context.getMiscInfo().setSEIOperations(seiOp);
        }
//        
//        String serviceName = context.getJAXRPCMappingContext()
//                .getServiceInterfaceName(context.getMiscInfo().gettargetService());
    }
}
