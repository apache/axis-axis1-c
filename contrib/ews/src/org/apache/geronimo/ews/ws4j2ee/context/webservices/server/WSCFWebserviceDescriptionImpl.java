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

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFConstants;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.w3c.dom.Element;

import java.util.HashMap;

/**
 * This represents a level 1 element in the Element tree :webservice-description. This is the concrete implementation of the
 * WSCFWebServiceDescription interface
 */
public class WSCFWebserviceDescriptionImpl extends WSCFElement implements WSCFWebserviceDescription {

    /**
     * This will refer to the multiple port components that can be there in the webservice-description Element.
     */
    private HashMap portComponent = new HashMap();

    /**
     * Webservice-description - description
     */
    private String description;

    /**
     * Webservice-description - display name
     */
    private String displayName;

    /**
     * Webservice-description - small icon
     */
    private String smallIcon;

    /**
     * Webservice-description - large icon
     */
    private String largeIcon;

    /**
     * Webservice-description - name
     */
    private String webserviceDescriptionName;

    /**
     * Webservice-description - wsdl file
     */
    private String wsdlFile;

    /**
     * Webservice-description - jaxrpc mapping file
     */
    private String jaxrpcMappingFile;

    /**
     * The constructor. Here the child elements will be created recursively in a depth first manner.
     * This is the concrete implementation of the WSCFWebserviceDescrption.
     * 
     * @param e Webservice-description Element
     * @throws WSCFException 
     */
    public WSCFWebserviceDescriptionImpl(Element e) throws WSCFException {
        super(e);
        //extract the description
        Element element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DESCRIPTION);
        if (null != element) {
            this.description = element.getChildNodes().item(0).toString();
        }
		
        //extract the display name
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DISPLAY_NAME);
        if (null != element) {
            this.displayName = element.getChildNodes().item(0).toString();
        }
		
        //extract the small icon.
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_SMALL_ICON);
        if (null != element) {
            this.smallIcon = element.getChildNodes().item(0).toString();
        }
		
        //extract the large icon
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_LARGE_ICON);
        if (null != element) {
            this.largeIcon = element.getChildNodes().item(0).toString();
        }
		
        //extract the webservice description name.
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_WEBSERVICES_DESCRIPTION_NAME);
        if (null != element) {
            this.webserviceDescriptionName = element.getChildNodes().item(0).toString();
        }
		
        //extract the wsdl file
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_WSDLFILE);
        if (null != element) {
            this.wsdlFile = element.getChildNodes().item(0).toString();
        }
		
        //extract the jax rpc mapping file
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_JAXRPC_MAPPING_FILE);
        if (null != element) {
            this.jaxrpcMappingFile = element.getChildNodes().item(0).toString();
        }
		
        //extract the port component
        Element[] elements = this.getChildElements(e, WSCFConstants.ELEM_WSCF_PORT_COMPONENT);
        for (int i = 0; i < elements.length; i++) {
            WSCFPortComponent portComponent = new WSCFPortComponentImpl(elements[i]);
            this.portComponent.put(portComponent.getPortComponentName(), portComponent);
        }

    }

    /**
     * Gets the description of the webservices-description Element
     * 
     * @return description
     */
    public String getDescription() {
        return description;
    }

    /**
     * Gets the display name of the webservices-description Element
     * 
     * @return display-name
     */
    public String getDisplayName() {
        return displayName;
    }

    /**
     * Gets the JAXRPC mapping file of the webservices-description Element
     * 
     * @return JAXRPC-mapping-file
     */
    public String getJaxrpcMappingFile() {
        return jaxrpcMappingFile;
    }

    /**
     * Gets the large icon of the webservices-description Element
     * 
     * @return large-icon
     */
    public String getLargeIcon() {
        return largeIcon;
    }

    /**
     * Gets the port compoments of the webservices-description Element as an array
     * 
     * @return port components
     */
    public WSCFPortComponent[] getPortComponent() {
        WSCFPortComponent[] portComponents = new WSCFPortComponent[this.portComponent.size()];
        this.portComponent.values().toArray(portComponents);
        return portComponents;
    }

    /**
     * Gets the small icon of the webservices-description Element
     * 
     * @return small-icon
     */
    public String getSmallIcon() {
        return smallIcon;
    }

    /**
     * Gets the name of the webservices-description Element
     * 
     * @return webservice-description-name
     */
    public String getWebserviceDescriptionName() {
        return webserviceDescriptionName;
    }

    /**
     * Gets the wsdl file of the webservices-description Element
     * 
     * @return wsdl-file
     */
    public String getWsdlFile() {
        return wsdlFile;
    }

}
