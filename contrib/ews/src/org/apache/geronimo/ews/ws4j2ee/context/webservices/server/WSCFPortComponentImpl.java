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
package org.apache.geronimo.ews.ws4j2ee.context.webservices.server;

import java.util.HashMap;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFConstants;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFServiceImplBean;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWSDLPort;
import org.w3c.dom.Element;

/**
 * This encapsulates the level 2 Elemenr PortComponent which is a child element of the webservice-description element.
 * It is also the concrete implmentation of the WSCFPortComponent. 
 *
 */
public class WSCFPortComponentImpl extends WSCFElement implements WSCFPortComponent {
	
	/**
	 * port-component description 
	 */
	private String description;
	
	/**
	 * port-component display name
	 */
	private String displayName;
	
	/**
	 * port-component small icon
	 */
	private String smallIcon;
	
	/**
	 * port-component large icon
	 */
	private String largeIcon;
	
	/**
	 * port-component name
	 */
	private String portComponentName;
	
	/**
	 * port-component wsdl port
	 */
	private WSCFWSDLPort wsdlPort;
	
	/**
	 * port-component service endpoint interface
	 */
	private String serviceEndpointInterface;
	
	/**
	 * port-component service implementation bean
	 */
	private WSCFServiceImplBean serviceImplBean;
	
	/**
	 * port-component handlers
	 */
	private HashMap handlers = new HashMap();
	
	
	/**
	 * The constructor. This will recursively parse the child elements in depth first manner.
	 * @param e PortComponent Element
	 * @throws WSCFException
	 */
	public WSCFPortComponentImpl(Element e)throws WSCFException{
		super(e);
		
		//extract the description.
		Element element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DESCRIPTION);
		if(null != element){this.description = element.getChildNodes().item(0).toString();}
		
		//extract the display name
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DISPLAY_NAME);
		if(null != element){this.displayName = element.getChildNodes().item(0).toString();}
		
		//extract the small icon
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_SMALL_ICON);
		if(null != element){this.smallIcon = element.getChildNodes().item(0).toString();}
		
		//extract the large icon
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_LARGE_ICON);
		if(null != element){this.largeIcon = element.getChildNodes().item(0).toString();}
		
		//extract the port component name
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_PORT_COMPONENT_NAME);
		if(null != element){this.portComponentName = element.getChildNodes().item(0).toString();}
		
		//extract the  wsdl port
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_WSDL_PORT);
		if(null != element){this.wsdlPort = new WSCFWSDLPortImpl(element);}
		
		//extracting the SEI
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_SERVICE_ENDPOINT_INTERFACE);
		if(null != element){this.serviceEndpointInterface = element.getChildNodes().item(0).toString();}
		
		//extracting the service implementation bean
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_SERVICE_IMPLEMENTATION_BEAN);
		if(null != element){this.serviceImplBean = new WSCFServiceImplBeanImpl(element);}
		
		Element[] elements = this.getChildElements(e, WSCFConstants.ELEM_WSCF_HANDLER);
		for(int i=0; i < elements.length; i++){
			WSCFHandler handler = new WSCFHandlerImpl(elements[i]);
			this.handlers.put(handler.getHandlerName(), handler);					
		}
	
	}	
	
	


	/**
	 * Gets the description of the port component Element
	 * @return description
	 */
	public String getDescription() {
		return description;
	}

	/**
	 * Gets the display name of the port component Element
	 * @return display name
	 */
	public String getDisplayName() {
		return displayName;
	}

	/**
	 * Gets the handlers of the port component Element as an array
	 * @return handlers
	 */
	public WSCFHandler[] getHandlers() {
		WSCFHandler[] handler = new WSCFHandler[this.handlers.size()];
		this.handlers.values().toArray(handler);
		return handler;
	}

	/**
	 * Gets the large icon of the port component Element
	 * @return large icon
	 */
	public String getLargeIcon() {
		return largeIcon;
	}

	/**
	 * Gets the port componenet name of the port component Element
	 * @return name
	 */
	public String getPortComponentName() {
		return portComponentName;
	}

	/**
	 * Gets the SEI of the port component Element
	 * @return SEI
	 */
	public String getServiceEndpointInterface() {
		return serviceEndpointInterface;
	}

	/**
	 * Gets the service implimentation bean of the port component Element
	 * @return service inplinmentation bean
	 */
	public WSCFServiceImplBean getServiceImplBean() {
		return serviceImplBean;
	}

	/**
	 * Gets the small icon of the port component Element
	 * @return small icon
	 */
	public String getSmallIcon() {
		return smallIcon;
	}

	/**
	 * Gets the wsdl port of the port component Element
	 * @return wsd; port
	 */
	public WSCFWSDLPort getWsdlPort() {
		return wsdlPort;
	}

}
