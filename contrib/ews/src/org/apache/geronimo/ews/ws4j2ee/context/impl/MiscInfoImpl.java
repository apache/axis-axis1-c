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
import java.util.Vector;

import org.apache.geronimo.ews.ws4j2ee.context.InputOutputFile;
import org.apache.geronimo.ews.ws4j2ee.context.MiscInfo;
import org.apache.geronimo.ews.ws4j2ee.context.SEIOperation;
import org
    .apache
    .geronimo
    .ews
    .ws4j2ee
    .context
    .webservices
    .server
    .interfaces
    .WSCFHandler;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationConstants;

/**
 * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class MiscInfoImpl implements MiscInfo {
    private ClassLoader classloader;
    private boolean implwithEJB = true;
    /* if Impl is avalible the class need not to be created agaien*/
    private boolean implAvalible = true;

    private String outputPath = ".";
    private String j2eelink;
    private String seiname;

    private ArrayList operations;
    private boolean verbose = false;
    private String wsConfFileLocation;

    private InputOutputFile wsdlFile;
    private InputOutputFile jaxrpcfile;
    private InputOutputFile wsconffile;

    private String targetJ2EEContainer = GenerationConstants.JBOSS_CONTAINER;
    private String implStyle = GenerationConstants.USE_LOCAL_AND_REMOTE;
    private boolean seiExists = false;
    private Vector classpathelements;

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

    public void validate() {
    }

    /**
     * @return 
     */

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
    public String getJ2eeComponetLink() {
        return j2eelink;
    }

    /**
     * @param string 
     */
    public void setJ2eeComponetLink(String string) {
        j2eelink = string;
    }

    /**
     * @return 
     */
    public InputOutputFile getJaxrpcfile() {
        return jaxrpcfile;
    }

    /**
     * @return 
     */
    public InputOutputFile getWsdlFile() {
        return wsdlFile;
    }

    /**
     * @param string 
     */
    public void setJaxrpcfile(InputOutputFile string) {
        jaxrpcfile = string;
    }

    /**
     * @param string 
     */
    public void setWsdlFile(InputOutputFile string) {
        wsdlFile = string;
    }

    /**
     * @return 
     */
    public String getJaxrpcSEI() {
        return seiname;
    }

    /**
     * @param string 
     */
    public void setJaxrpcSEI(String string) {
        seiname = string;
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
    public InputOutputFile getWsconffile() {
        return wsconffile;
    }

    /**
     * @param string
     */
    public void setWsconffile(InputOutputFile string) {
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

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#isSEIExists()
     */
    public boolean isSEIExists() {
        return seiExists;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#setSEIExists()
     */
    public void setSEIExists(boolean seiExists) {
        this.seiExists = seiExists;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#getClasspathElements()
     */
    public Vector getClasspathElements() {
        return classpathelements;
    }

    /* (non-Javadoc)
     * @see org.apache.geronimo.ews.ws4j2ee.context.MiscInfo#setClassPathElements()
     */
    public void setClassPathElements(Vector classpathelements) {
        this.classpathelements = classpathelements;
    }
    /**
     * @return
     */
    public ClassLoader getClassloader() {
        return classloader;
    }

    /**
     * @param loader
     */
    public void setClassloader(ClassLoader loader) {
        classloader = loader;
    }

}
