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

import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;

/**
 * <p>This interface has all the information about the J2EE webservice that is
 * going to be genarated. from this interface onward all the codes are
 * ws4j2ee. If we using any class from the geronimo deployment we should
 * wrap them. This is a Code whith runing once. It is worth keeping the
 * code independent.<p>
 * <p/>
 * <p>This interface and related interfaces has both getter and setter methods
 * but who ever implements this interface might not need the both.
 * e.g. there can be two concreate implementations for this class
 * for the cases
 * <ol>
 * <li>have WSDL</li>
 * <li>do not have WSDL</li>
 * </ol>
 * if some method is not requried please throw java.lang.UnsupportedOperationException</p>
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public interface J2EEWebServiceContext {
	/**
	 * Information about the WSDL file
	 * @return
	 */
    public WSDLContext getWSDLContext();
    public void setWSDLContext(WSDLContext wsdlcontext);

	/**
	 * Information about the webservice.xml file
	 * @return
	 */
    public WSCFContext getWSCFContext();
    public void setWSCFContext(WSCFContext wscfcontext);

	/**
	 * Information about the jaxrpcmapping.xml file  
	 * @return
	 */
    public JaxRpcMapperContext getJAXRPCMappingContext();
    public void setJAXRPCMappingContext(JaxRpcMapperContext context);

	/**
	 * Have the mislaneous infomation about the web service.
	 * @return
	 */
    public MiscInfo getMiscInfo();
    public void setMiscInfo(MiscInfo info);

	/**
	 * validate the context
	 */
    public void validate();
}
