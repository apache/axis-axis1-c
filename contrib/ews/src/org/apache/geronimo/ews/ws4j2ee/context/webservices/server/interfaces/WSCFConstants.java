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
package org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces;

/**
 * @author Chathura Herath
 *
 */
public interface WSCFConstants {


	public static final String URI_WSCF = "http://xml.apache.org/x/wscf/";
    

	public static final String ELEM_WSCF_WEBSERVICES = "webservices";
	public static final String ELEM_WSCF_DESCRIPTION = "description";
	public static final String ELEM_WSCF_DISPLAY_NAME = "display-name";
	public static final String ELEM_WSCF_SMALL_ICON = "small-icon";
	public static final String ELEM_WSCF_LARGE_ICON = "large-icon";
	public static final String ELEM_WSCF_WEBSERVICES_DESCRIPTION = "webservice-description";
	public static final String ELEM_WSCF_WEBSERVICES_DESCRIPTION_NAME = "webservice-description-name";
	public static final String ELEM_WSCF_WSDLFILE = "wsdl-file";
	public static final String ELEM_WSCF_JAXRPC_MAPPING_FILE = "jaxrpc-mapping-file";
	public static final String ELEM_WSCF_PORT_COMPONENT = "port-component";
	public static final String ELEM_WSCF_PORT_COMPONENT_NAME = "port-component-name";
	public static final String ELEM_WSCF_WSDL_PORT = "wsdl-port";
	public static final String ELEM_WSCF_NAMESPACE_URI = "namespaceURI";
	public static final String ELEM_WSCF_LOCALPART = "localpart";
	public static final String ELEM_WSCF_SERVICE_ENDPOINT_INTERFACE = "service-endpoint-interface";
	public static final String ELEM_WSCF_SERVICE_IMPLEMENTATION_BEAN = "service-impl-bean";
	public static final String ELEM_WSCF_EJB_LINK = "ejb-link";
	public static final String ELEM_WSCF_HANDLER = "handler";
	public static final String ELEM_WSCF_HANDLER_NAME = "handler-name";
	public static final String ELEM_WSCF_HANDLER_CLASS = "handler-class";
	public static final String ELEM_WSCF_INIT_PARAM = "init-param";
	public static final String ELEM_WSCF_PARAM_NAME = "param-name";
	public static final String ELEM_WSCF_PARAM_VLAUE = "param-value";
	public static final String ELEM_WSCF_SOAP_HEADER = "soap-header";
	public static final String ELEM_WSCF_SOAP_ROLE = "soap-role";
	
	
}
