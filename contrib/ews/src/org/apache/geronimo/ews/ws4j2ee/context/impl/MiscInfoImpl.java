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

import java.util.ArrayList;

import javax.wsdl.Port;

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.ws4j2ee.context.MiscInfo;
import org.apache.geronimo.ews.ws4j2ee.context.SEIOperation;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenerationFault;

/**
 * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class MiscInfoImpl implements MiscInfo {
    private WSCFWebserviceDescription wscfdWsDesxription;
    private WSCFPortComponent wscfport;
    private boolean implwithEJB = true;
	/* if Impl is avalible the class need not to be created agaien*/
	private boolean implAvalible = false;
	private String jarFileName;
	
    private String outputPath = ".";

    private ServiceEntry service;
    private BindingEntry binding;
    private PortTypeEntry portType;
    private Port port;

    private String ejbsei = null;
    private String ejbbean = null;
    private String ejbhome = null;
	private String ejblocalsei = null;
	//private String ejblocalbean = null;
	private String ejblocalhome = null;
    private String ejbName = null;
    private String axisSEI;
    private ArrayList operations;
    private boolean verbose = false;
    private String wsConfFileLocation;
    private String wsdlFile;
    private String jaxrpcfile;
    private String wsconffile;
    private String targetJ2EEContainer = GenerationConstants.JBOSS_CONTAINER;
    private String implStyle = GenerationConstants.USE_LOCAL_AND_REMOTE;
    private WSCFHandler[] handlers;
    public MiscInfoImpl() {
        operations = new ArrayList();
        targetJ2EEContainer = GenerationConstants.JBOSS_CONTAINER;
        implStyle = GenerationConstants.USE_REMOTE;
    }

    public String getOutPutPath() {
        return outputPath;
    }

    public void setOutputPath(String string) {
        outputPath = string;
    }

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

    public void validate() {
        if (portType == null || binding == null
                //|| ejbbean == null || ejbsei == null || ejbhome == null
                 ) {
            throw new UnrecoverableGenerationFault("validation of MiscInfo failed");
        }
    }

    /**
     * @return 
     */
    public String getEndpointImplbean() {
        return ejbbean;
    }

    /**
     * @return 
     */
    public String getEjbsei() {
        return ejbsei;
    }

    /**
     * @param string 
     */
    public void setEndpointImplbean(String string) {
        ejbbean = string;
    }

    /**
     * @param string 
     */
    public void setEjbsei(String string) {
        ejbsei = string;
    }

    /**
     * @return 
     */
    public String getEjbhome() {
        return ejbhome;
    }

    /**
     * @param string 
     */
    public void setEjbhome(String string) {
        ejbhome = string;
    }

    /**
     * @return 
     */
    public WSCFWebserviceDescription getWscfdWsDesxription() {
        return wscfdWsDesxription;
    }

    /**
     * @return 
     */
    public WSCFPortComponent getWscfport() {
        return wscfport;
    }

    /**
     * @param description 
     */
    public void setWscfdWsDescription(WSCFWebserviceDescription description) {
        wscfdWsDesxription = description;
    }

    /**
     * @param component 
     */
    public void setWscfport(WSCFPortComponent component) {
        wscfport = component;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#getSEIOperations()
     */
    public ArrayList getSEIOperations() {
        return operations;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#setSEIOperations(java.util.ArrayList)
     */
    public void setSEIOperations(SEIOperation operation) {
        this.operations.add(operation);
    }

    /**
     * @return 
     */
    public boolean isVerbose() {
        return verbose;
    }

    /**
     * @return 
     */
    public String getWsConfFileLocation() {
        return wsConfFileLocation;
    }

    /**
     * @param b 
     */
    public void setVerbose(boolean b) {
        verbose = b;
    }

    /**
     * @param string 
     */
    public void setWsConfFileLocation(String string) {
        wsConfFileLocation = string;
    }

    /**
     * @return 
     */
    public String getEjbName() {
        return ejbName;
    }

    /**
     * @param string 
     */
    public void setEjbName(String string) {
        ejbName = string;
    }

    /**
     * @return 
     */
    public String getJaxrpcfile() {
        return jaxrpcfile;
    }

    /**
     * @return 
     */
    public String getWsdlFile() {
        return wsdlFile;
    }

    /**
     * @param string 
     */
    public void setJaxrpcfile(String string) {
        jaxrpcfile = string;
    }

    /**
     * @param string 
     */
    public void setWsdlFile(String string) {
        wsdlFile = string;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#getTargetPort()
     */
    public Port getTargetPort() {
        return port;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#setTargetPort(javax.wsdl.Port)
     */
    public void setTargetPort(Port port) {
        this.port = port;
    }

    /**
     * @return 
     */
    public String getJaxrpcSEI() {
        return axisSEI;
    }

    /**
     * @param string 
     */
    public void setJaxrpcSEI(String string) {
        axisSEI = string;
    }

    /**
     * @return
     */
    public String getImplStyle() {
        return implStyle;
    }

    /**
     * @return
     */
    public String getTargetJ2EEContainer() {
        return targetJ2EEContainer;
    }

    /**
     * @param string
     */
    public void setImplStyle(String string) {
        implStyle = string;
    }

    /**
     * @param string
     */
    public void setTargetJ2EEContainer(String string) {
        targetJ2EEContainer = string;
    }

    /**
     * @return
     */
    public String getEjblocalhome() {
        return ejblocalhome;
    }

    /**
     * @return
     */
    public String getEjblocalsei() {
        return ejblocalsei;
    }

    /**
     * @param string
     */
    public void setEjblocalhome(String string) {
        ejblocalhome = string;
    }

    /**
     * @param string
     */
    public void setEjblocalsei(String string) {
        ejblocalsei = string;
    }

    /**
     * @return
     */
    public boolean isImplwithEJB() {
        return implwithEJB;
    }

    /**
     * @param b
     */
    public void setImplwithEJB(boolean b) {
        implwithEJB = b;
    }

    /**
     * @return
     */
    public boolean isImplAvalible() {
        return implAvalible;
    }

    /**
     * @param b
     */
    public void setImplAvalible(boolean b) {
        this.implAvalible = b;
    }

	/**
	 * @return
	 */
	public String getWsconffile() {
		return wsconffile;
	}

	/**
	 * @param string
	 */
	public void setWsconffile(String string) {
		wsconffile = string;
	}

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#getHandlers()
     */
    public WSCFHandler[] getHandlers() {
        return handlers;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#setHandlers(org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler[])
     */
    public void setHandlers(WSCFHandler[] handlers) {
		this.handlers = handlers;        
    }

    /**
     * @return
     */
    public String getJarFileName() {
        return jarFileName;
    }

    /**
     * @param string
     */
    public void setJarFileName(String string) {
        jarFileName = string;
    }

}
