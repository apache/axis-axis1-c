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

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;

import javax.wsdl.Port;
import java.util.ArrayList;

/**
 * <p>This class interface the importent information about the webservice
 * under consideration. E.g. the webservice DD may have one or more
 * WebserviceDescriptions, WSDLportType's WSDLBindings ect. This type of object
 * provide acsess to the instance's under the consideration. It is recomended to
 * acscess these instances over MiscInfo snd It will make sure everybody is
 * acsessing same port type ect.
 * 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public interface MiscInfo {
    public void setOutputPath(String outputpath);

    public String getOutPutPath();

    public ServiceEntry gettargetService();

    public BindingEntry gettargetBinding();

    public PortTypeEntry getTargetPortType();

    public void settargetService(ServiceEntry service);

    public void settargetBinding(BindingEntry binding);

    public void setTargetPortType(PortTypeEntry port);

    public String getEjbsei();

    public void setEjbbean(String string);

    public String getEjbbean();

    public void setEjbsei(String string);

    public String getEjbhome();

    public void setEjbhome(String string);

    public WSCFWebserviceDescription getWscfdWsDesxription();

    public WSCFPortComponent getWscfport();

    public void setWscfdWsDescription(WSCFWebserviceDescription description);

    public void setWscfport(WSCFPortComponent component);

    /**
     * @return ArrayList of SEIOperations
     */
    public ArrayList getSEIOperations();

    public void setSEIOperations(SEIOperation operation);

    public void validate();

    public boolean isVerbose();

    public String getWsConfFileLocation();

    public void setVerbose(boolean b);

    public void setWsConfFileLocation(String string);

    public String getEjbName();

    public void setEjbName(String string);

    public String getJaxrpcfile();

    public String getWsdlFile();

    public void setJaxrpcfile(String string);

    public void setWsdlFile(String string);

    public void setTargetPort(Port port);

    public Port getTargetPort();

    public String getJaxrpcSEI();

    public void setJaxrpcSEI(String string);

    public String getJ2eeContainerDDName();

    public void setJ2eeContainerDDName(String string);
}
