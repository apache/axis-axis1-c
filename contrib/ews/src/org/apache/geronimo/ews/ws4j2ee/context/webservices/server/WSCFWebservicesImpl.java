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
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebservices;
import org.w3c.dom.Element;

import java.util.HashMap;

/**
 * This is the class that will represent the webservices element in the runtime.
 * This is the root element of the webservices.xml file. The parsing of elements will be initiated from here and will be
 * parsed in a depth first manner
 */
public class WSCFWebservicesImpl extends WSCFElement implements WSCFWebservices {

    //TODO figure out how the id should be encapsulated
	
    /**
     * This will refer to the multiple webservice descriptions elements that the
     * webservice element can support
     */
    private HashMap webServiceDescriptions = new HashMap();

    /**
     * Webservice description.
     */
    private String description;

    /**
     * Webservice display name
     */
    private String displayName;

    /**
     * Webservice small Icon.
     */
    private String smallIcon;

    /**
     * Webservice large icon.
     */
    private String largeIcon;

    /**
     * Constructor
     * 
     * @param e Webservices element
     * @throws WSCFException 
     */
    public WSCFWebservicesImpl(Element e) throws WSCFException {
        super(e);
        //extracting the description
        Element element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DESCRIPTION);
        if (null != element) {
            this.description = (element.getChildNodes()).item(0).getNodeValue();
        }
		
        //extraction the dispaly-name
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DISPLAY_NAME);
        if (null != element) {
            this.displayName = element.getChildNodes().item(0).getNodeValue();
        }
		
        //extraction the small icon
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_SMALL_ICON);
        if (null != element) {
            this.smallIcon = element.getChildNodes().item(0).getNodeValue();
        }
				
        //extracting the large icon
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_LARGE_ICON);
        if (null != element) {
            this.largeIcon = element.getChildNodes().item(0).getNodeValue();
        }
        //TODO ********whether this is the most appropreate way to do this
        // getting the webservice description.
        Element[] elements = this.getChildElements(e, WSCFConstants.ELEM_WSCF_WEBSERVICES_DESCRIPTION);
        for (int i = 0; i < elements.length; i++) {
            WSCFWebserviceDescription webservice = new WSCFWebserviceDescriptionImpl(elements[i]);
            this.webServiceDescriptions.put(webservice.getWebserviceDescriptionName(), webservice);
        }

    }

    /**
     * Gets all the webservice descriptions as a array of such elements
     * 
     * @return Webservice description array.
     */
    public WSCFWebserviceDescription[] getWebServiceDescriptions() {
        WSCFWebserviceDescription[] wsdescArray = new WSCFWebserviceDescription[this.webServiceDescriptions.size()];
        this.webServiceDescriptions.values().toArray(wsdescArray);
        return wsdescArray;
    }	


//TODO *throw an exception appropreately if the value is null

    /**
     * Gets the description of the webservices Element
     * 
     * @return The description
     */
    public String getDescription() {
        return description;
    }

    /**
     * Gets the displayname of the webservices element
     * 
     * @return The Display name
     */
    public String getDisplayName() {
        return displayName;
    }

    /**
     * Gets the description of the large icon Element
     * 
     * @return The large icon
     */
    public String getLargeIcon() {
        return largeIcon;
    }

    /**
     * Gets the description of the small icon Element
     * 
     * @return The small icon
     */
    public String getSmallIcon() {
        return smallIcon;
    }

//	/**
//	 * @param description - Description of the webservice
//	 */
//	public void setDescription(String description) {
//		this.description = description;
//	}
//
//	/**
//	 * @param displayName
//	 */
//	public void setDisplayName(String displayName) {
//		this.displayName = displayName;
//	}
//
//	/**
//	 * @param largeIcon
//	 */
//	public void setLargeIcon(String largeIcon) {
//		this.largeIcon = largeIcon;
//	}
//
//	/**
//	 * @param smallIcon
//	 */
//	public void setSmallIcon(String smallIcon) {
//		this.smallIcon = smallIcon;
//	}

}
