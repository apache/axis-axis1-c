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

import java.io.InputStream;

import org.apache.axis.wsdl.symbolTable.SymbolTable;
import org.apache.geronimo.ews.jaxrpcmapping.J2eeEmitter;
import org.apache.geronimo.ews.jaxrpcmapping.JaxRpcMapper;
import org.apache.geronimo.ews.ws4j2ee.context.impl.J2EEWebServiceContextImpl;
import org.apache.geronimo.ews.ws4j2ee.context.impl.JaxRpcMapperImpl;
import org.apache.geronimo.ews.ws4j2ee.context.impl.MiscInfoImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.WSCFContextImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.WSCFException;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.impl.AxisWSDLContext;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;
import org.apache.geronimo.ews.ws4j2ee.toWs.UnrecoverableGenerationFault;

/**
 * <p>This class decouple the concreate implementations of the
 * class from the rest of the code</p>
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class ContextFactory {
	private static J2EEWebServiceContext currentContext;
    public static WSDLContext createWSDLContext(Object info) {
        if (info instanceof SymbolTable)
            return new AxisWSDLContext((SymbolTable) info);
        throw new UnrecoverableGenerationFault("unknown context type");
    }

    public static JaxRpcMapperContext createJaxRpcMapperContext(Object[] info) {
        if (info.length == 2 && info[0] instanceof JaxRpcMapper && info[1] instanceof J2eeEmitter)
            return new JaxRpcMapperImpl((JaxRpcMapper) info[0],(J2eeEmitter)info[1]);
        throw new UnrecoverableGenerationFault("unknown mapper type");
    }

    public static WSCFContext createWSCFContext(InputStream in) throws GenerationFault {
        try {
            return new WSCFContextImpl(in);
        } catch (WSCFException e) {
            e.printStackTrace();
            throw new GenerationFault(e.getMessage());
        }
    }

    public static MiscInfo createMiscInfo() {
        return new MiscInfoImpl();
    }
    
    public static J2EEWebServiceContext getCurrentJ2EEWsContext(){
		return currentContext;
    }
	public static J2EEWebServiceContext getJ2EEWsContext(boolean hasWSDL){
		currentContext = new J2EEWebServiceContextImpl(hasWSDL);
		return currentContext;
	} 
 
}
