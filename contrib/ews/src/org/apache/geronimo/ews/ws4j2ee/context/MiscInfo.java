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

import java.util.ArrayList;
import java.util.Vector;

import javax.wsdl.Port;

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;

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
	/**
	 * the root diretory for the output  
	 * @param outputpath
	 */
    public void setOutputPath(String outputpath);
    public String getOutPutPath();
    
    /**
     * WSDL artifacts correponds to the current WSCF port.
     * If one element is in the wsdl theu are used. How to select them 
     * if there is more than one is still to do.   
     * @return
     */
    public ServiceEntry gettargetService();
	public void settargetService(ServiceEntry service);

    public BindingEntry gettargetBinding();
	public void settargetBinding(BindingEntry binding);

    public PortTypeEntry getTargetPortType();
	public void setTargetPortType(PortTypeEntry port);

	public void setTargetPort(Port port);
	public Port getTargetPort();
    
	/**
	 * @return ArrayList of SEIOperations
	 */
	public ArrayList getSEIOperations();
	public void setSEIOperations(SEIOperation operation);
	
	public void setSEIExists(boolean seiExists);
	public boolean isSEIExists();

	/**
	 * Names of the classes corresponding to SEI, Implementation bean and the 
	 * web service and the sessionless EJB. 
	 * @return
	 */    
	public String getEjbName();
	public void setEjbName(String string);

	public String getJaxrpcSEI();
	public void setJaxrpcSEI(String string);
    
	public String getEjblocalhome();
	public void setEjblocalhome(String string);

	public String getEjblocalsei();
	public void setEjblocalsei(String string);
	
	public String getEjbsei();
	public void setEjbsei(String string);

	public void setEndpointImplbean(String string);
	public String getEndpointImplbean();

	public String getEjbhome();
	public void setEjbhome(String string);


	/**
	 * WSCF artifacts correponds to the current WSCF file.
	 * If one element is in the wsdl theu are used. How to select them 
	 * if there is more than one is still to do.   
	 * @return
	 */
    public WSCFWebserviceDescription getWscfdWsDesxription();
	public void setWscfdWsDescription(WSCFWebserviceDescription description);

    public WSCFPortComponent getWscfport();
    public void setWscfport(WSCFPortComponent component);

	/**
	 * Validate the Content of the Misc Info
	 */
    public void validate();

    public boolean isVerbose();
	public void setVerbose(boolean b);
	
	/**
	 * the root directory of the webservice.xml file.
	 * @return
	 */
    public String getWsConfFileLocation();
    public void setWsConfFileLocation(String string);
    
	/**
	 * The jaxrpc-file specifies a location of the WSDL description of
	 * a set of Web services. The location is relative to the root of the module
	 * and must be specified by the developer.
	 */
    public InputOutputFile getJaxrpcfile();
	public void setJaxrpcfile(InputOutputFile string);
	/**
	 * The wsdl-file specifies a location of the WSDL description of
	 * a set of Web services. The location is relative to the root of the module
	 * and must be specified by the developer.
	 */
    public InputOutputFile getWsdlFile();
    public void setWsdlFile(InputOutputFile string);

	/**
	 * <p>One of the following values and specify how the ejb based web service 
	 * Obtain the referance to the sessionless web service</p> 
	 * public static final String USE_REMOTE ="use-remote";
	 * public static final String USE_LOCAL =  "use-local";
	 * public static final String USE_INTERNALS = "use-internals";
	 * public static final String USE_LOCAL_AND_REMOTE = "use-local-remote";
	 */
	public String getImplStyle();
	public void setImplStyle(String string);

	/**
	 * <p>One of the following values and specify what is the j2ee container the 
	 * implementation is based on.</p>
	 * public static final String JBOSS_CONTAINER = "jboss";
	 * public static final String JONAS_CONTAINER = "jonas";
	 * public static final String GERONIMO_CONTAINER = "geronimo";
	 */ 
	public String getTargetJ2EEContainer();
	public void setTargetJ2EEContainer(String string);

	/**
	 * Say the implementation of the webservice is based on the sessionless web service 
	 * or a java class. 
	 * @return
	 */
	public boolean isImplwithEJB();
	public void setImplwithEJB(boolean b);

	/**
	 * Say wheather the Implementation bean is avalible when gererating without wsdl.
	 * For other cases it does not make sense.   
	 * @return
	 */
	public boolean isImplAvalible();
	public void setImplAvalible(boolean b);

	/**
	 * The webservice.xml specifies a location of the WSDL description of
	 * a set of Web services. The location is relative to the root of the module
	 * and must be specified by the developer.
	 */
	public InputOutputFile getWsconffile(); 
	public void setWsconffile(InputOutputFile string);

	/**
	 * Handlers. A developer may optionally specify handlers associated with the 
	 * service-ref using the handler element.
	 */
	public WSCFHandler[] getHandlers();
	public void setHandlers(WSCFHandler[] handlers);
	
	/**
	 * Name of the Input jar file
	 */
	public String getJarFileName();
    public void setJarFileName(String string);
    /**
     * the class path elemnts added via jar,war,ear files this is a Vector of
     * java.io.File
     */
    public Vector getClasspathElements();
    public void setClassPathElements(Vector classpathelements);
}
