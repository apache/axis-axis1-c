/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
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
import java.util.List;
import java.util.Vector;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFConstants;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFHandler;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFInitParam;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFSOAPHeader;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.DescriptionType;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.DisplayNameType;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.IconType;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.PathType;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.PortComponentHandlerType;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.XsdQNameType;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.impl.ParamValueTypeImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.jaxb.impl.StringImpl;
import org.w3c.dom.Element;

/**
 * This encapsulates the layer 3 handler element of the webservices.xml. This
 * is also the concrete implementation of the WSCFHandler.
 *
 */
public class WSCFHandlerImpl extends WSCFElement implements WSCFHandler {

	/**
	 * handler derscription 
	 */
	private String description;
	
	/**
	 * handler display name
	 */
	private String displayName;
	
	/**
	 * handler small icon
	 */
	private String smallIcon;
	
	/**
	 * handler  large icon
	 */
	private String largeIcon;
	
	/**
	 * handler name
	 */
	private String handlerName;
	
	/**
	 * handler class
	 */
	private String handlerClass;
	
	/**
	 * handler init parameters as a collection
	 */
	private HashMap initParam = new HashMap();
	
	/**
	 * handler soap headers as a collection
	 */
	private Vector soapHeader = new Vector();
	
	/**
	 * handler soap roles as a collection
	 */
	private Vector soapRole = new Vector();
	
	////////////////////////////////jaxb interfacing block//////////////////////////////
	
	private PortComponentHandlerType jaxbHandler;
	
	public WSCFHandlerImpl(PortComponentHandlerType jaxbHandler){
		this.jaxbHandler = jaxbHandler;
	
		//////////asigning the values/////////////////
	
		List temp = null;
		
		
		temp = jaxbHandler.getDescription();
		if(0 != temp.size())
			this.description = ((DescriptionType)temp.get(0)).getValue();
			
		temp = jaxbHandler.getDisplayName();
		if(0 != temp.size())
			this.displayName =((DisplayNameType)temp.get(0)).getValue();
			
		temp = jaxbHandler.getIcon();
		if(0 != temp.size()){		
			if(null != (PathType)((IconType)temp.get(0)).getSmallIcon())
				this.smallIcon =((PathType)((IconType)temp.get(0)).getSmallIcon()).getValue();
			
			if(null != (PathType)((IconType)temp.get(0)).getLargeIcon())
				this.largeIcon =((PathType)((IconType)temp.get(0)).getLargeIcon()).getValue();
		}
		
		if(null != jaxbHandler.getHandlerName())
			this.handlerName = jaxbHandler.getHandlerName().getValue();
		
		if(null != jaxbHandler.getHandlerClass())
			this.handlerClass = jaxbHandler.getHandlerClass().getValue();
		
		java.util.List list = jaxbHandler.getInitParam();
		for(int i=0; i < list.size(); i++){			
			WSCFInitParam initParameters = new WSCFInitParamImpl(((ParamValueTypeImpl)list.get(i)));
			this.initParam.put(initParameters.getParamName(), initParameters);
		}
		
		list = jaxbHandler.getSoapHeader();
		for(int i=0; i < list.size(); i++){
			this.soapHeader.add(new WSCFSOAPHeaderImpl((XsdQNameType)list.get(i))); 
		}
		
		list = jaxbHandler.getSoapRole();
		for(int i=0; i < list.size(); i++){
			this.soapRole.add(((StringImpl)list.get(i)).getValue()); 
		}		
	
	}
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////
	
	/**
	 * The constructor. This will parse the chaild elementsin a depth first manner.
	 * @param e handler Element
	 * @throws WSCFException
	 */
	public WSCFHandlerImpl(Element e)throws WSCFException{
		super(e);
		
		//extract description
		Element element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DESCRIPTION);
		if(null != element){this.description = element.getChildNodes().item(0).toString();}
		
		//extracting the display name
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DISPLAY_NAME);
		if(null != element){this.displayName = element.getChildNodes().item(0).toString();}
		
		//extract small icon
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_SMALL_ICON);
		if(null != element){this.smallIcon = element.getChildNodes().item(0).toString();}
		
		//extract handler name
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_HANDLER_NAME);
		if(null != element){this.handlerName = element.getChildNodes().item(0).toString();}
		
		// extract handler class
		element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_HANDLER_CLASS);
		if(null != element){this.handlerClass = element.getChildNodes().item(0).toString();}
		
		//extracting the params
		Element[] elements = this.getChildElements(e, WSCFConstants.ELEM_WSCF_INIT_PARAM);
		for(int i=0; i < elements.length; i++){
			WSCFInitParam initparam = new WSCFInitParamImpl(elements[i]);
			this.initParam.put(initparam.getParamName(), initparam);
		}
		
		//extracting the soap headers
		elements = this.getChildElements(e, WSCFConstants.ELEM_WSCF_SOAP_HEADER);
		for(int i=0; i < elements.length; i++){
			this.soapHeader.add(new WSCFSOAPHeaderImpl(elements[i]));
		}
		
		//extract the SOAP roles
		elements = this.getChildElements(e, WSCFConstants.ELEM_WSCF_SOAP_ROLE);
		for(int i=0; i < elements.length; i++){
			this.soapRole.add(elements[i].getChildNodes().item(0).toString());			
		}
		
	}
		
	

	/**
	 * Gets the description of the handler element
	 * @return description
	 */
	public String getDescription() {
		return description;
	}

	/**
	 * Gets the display name of the handler element
	 * @return display-name
	 */
	public String getDisplayName() {
		return displayName;
	}

	/**
	 * Gets the class of the handler element
	 * @return handler-class
	 */
	public String getHandlerClass() {
		return handlerClass;
	}

	/**
	 * Gets the name of the handler element
	 * @return handler-name
	 */
	public String getHandlerName() {
		return handlerName;
	}

	/**
	 * Gets the init paramaeters of the handler element as a array
	 * @return init-parameters
	 */
	public WSCFInitParam[] getInitParam() {
		WSCFInitParam[] initparam = new WSCFInitParam[this.initParam.size()];
		this.initParam.values().toArray(initparam);
		return initparam;
	}

	/**
	 * Gets the large icon of the handler element
	 * @return large-icon
	 */
	public String getLargeIcon() {
		return largeIcon;
	}

	/**
	 * Gets the small icon of the handler element
	 * @return small-icon
	 */
	public String getSmallIcon() {
		return smallIcon;
	}

	/**
	 * Gets the soap headers of the handler element
	 * @return soap-headers
	 */
	public WSCFSOAPHeader[] getSoapHeader() {
		WSCFSOAPHeader[] soapheader = new WSCFSOAPHeader[this.soapHeader.size()];
		int size = soapHeader.size();
		for(int i = 0;i<size;i++){
			soapheader[i] = ((WSCFSOAPHeader)soapHeader.get(i));
		}
		return soapheader;
	}

	/**
	 * Gets the soap roles of the handler element
	 * @return soap-roles
	 */
	public String[] getSoapRole() {
		String[] soaprole = new String[this.soapRole.size()];
		int size = soapRole.size();
		for(int i = 0;i<size;i++){
			soaprole[i] = (String)soapRole.get(i);
		}
		return soaprole;
	}

	/**
	 * @return
	 */
	public PortComponentHandlerType getJaxbHandler() {
		return jaxbHandler;
	}

}
