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
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFInitParam;
import org.w3c.dom.Element;

/**
 * This will encapsulate the init parameter element and the information will be able access
 * using the interface published.
 */
public class WSCFInitParamImpl extends WSCFElement implements WSCFInitParam {

    /**
     * Init parameter name
     */
    private String paramName;

    /**
     * Init parameter value
     */
    private String paramValue;

    /**
     * Init parameter description
     */
    private String description;

    /**
     * The constructor. this willget the child nodes that provide teh sufficient statistics about the init parameters.
     * 
     * @param e init parameter Element
     * @throws WSCFException 
     */
    public WSCFInitParamImpl(Element e) throws WSCFException {
        super(e);
		
        //extract param name
        Element element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_PARAM_NAME);
        if (null != element) {
            this.paramName = element.getChildNodes().item(0).toString();
        }
		
        //extract param value
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_PARAM_VLAUE);
        if (null != element) {
            this.paramValue = element.getChildNodes().item(0).toString();
        }
		
        // extract the description
        element = this.getChildElement(e, WSCFConstants.ELEM_WSCF_DESCRIPTION);
        if (null != element) {
            this.description = element.getChildNodes().item(0).toString();
        }

    }

    /**
     * Gets the description of the init parameter element
     * 
     * @return description
     */
    public String getDescription() {
        return description;
    }

    /**
     * Gets the name of the init parameter element
     * 
     * @return name
     */
    public String getParamName() {
        return paramName;
    }

    /**
     * Gets the value of the init parameter element
     * 
     * @return value
     */
    public String getParamValue() {
        return paramValue;
    }

}
