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

package org.apache.geronimo.ews.ws4j2ee.context.wsdl.impl;

import javax.wsdl.Port;

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenerationFault;

/**
 * @author hemapani@opensource.lk
 */
public abstract class AbstractWSDLContext implements WSDLContext{
	private ServiceEntry service;
	private BindingEntry binding;
	private PortTypeEntry portType;
	private Port port;
	
	public BindingEntry gettargetBinding() {
		return binding;
	}

	public PortTypeEntry getTargetPortType() {
		return portType;
	}

	public ServiceEntry gettargetService() {
		return service;
	}

	public void settargetBinding(BindingEntry binding) {
		this.binding = binding;
	}

	public void setTargetPortType(PortTypeEntry port) {
		this.portType = port;
	}

	public void settargetService(ServiceEntry service) {
		this.service = service;
	}
	
	public Port getTargetPort() {
		   return port;
	   }

   public void setTargetPort(Port port) {
	   this.port = port;
   }
    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext#validate()
     */
    public void validate() {
		if (portType == null || binding == null
		 ) {
			throw new UnrecoverableGenerationFault("validation of MiscInfo failed");
		}
    }

}
