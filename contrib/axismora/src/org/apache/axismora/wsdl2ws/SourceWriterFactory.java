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
 *    Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.axismora.wsdl2ws;

import org.apache.axismora.wsdl2ws.cpp.ClassLoader;
import org.apache.axismora.wsdl2ws.cpp.ServiceHeaderWriter;
import org.apache.axismora.wsdl2ws.cpp.WrapHeaderWriter;
import org.apache.axismora.wsdl2ws.info.WebServiceContext;
import org.apache.axismora.wsdl2ws.java.AllParamWriter;
import org.apache.axismora.wsdl2ws.java.DeploymentWriter;
import org.apache.axismora.wsdl2ws.java.ServiceWriter;
import org.apache.axismora.wsdl2ws.java.UndeployWriter;
import org.apache.axismora.wsdl2ws.java.WrapWriter;
import org.apache.axismora.wsdl2ws.java.client.LocatorWriter;
import org.apache.axismora.wsdl2ws.java.client.ServiceInterfaceWriter;
import org.apache.axismora.wsdl2ws.java.client.StubWriter;
/**
 * Genarate a SourceFactory depend on the reqirements. 
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
public class SourceWriterFactory {
    public static SourceWriter createSourceWriter(
        int genaratorType,
        WebServiceContext wscontext)
        throws WrapperFault {
        //java
        if (genaratorType == WrapperConstants.GENERATOR_PARAM_JAVA) {
            return new AllParamWriter(wscontext);
        } else if (genaratorType == WrapperConstants.GENERATOR_WRAPPER_JAVA)
            return new WrapWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_SERVICE_JAVA)
            return new ServiceWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_STUB_SERVICE_INTERFACE_JAVA)
            return new ServiceInterfaceWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_STUB_LOCATOR_JAVA)
            return new LocatorWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_STUB_JAVA)
            return new StubWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_DEPLOYMENT_DISCRIPTOR)
            return new DeploymentWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_UNDEPLOYMENT_DISCRIPTOR)
            return new UndeployWriter(wscontext);
        //C++	
        else if (genaratorType == WrapperConstants.GENERATOR_PARAM_CPP_ALL)
            return new org.apache.axismora.wsdl2ws.cpp.AllParamWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_WRAPPER_CPP)
            return new org.apache.axismora.wsdl2ws.cpp.WrapWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_WRAPPER_HPP)
            return new WrapHeaderWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_SERVICE_CPP)
            return new org.apache.axismora.wsdl2ws.cpp.ServiceWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_SERVICE_HPP)
            return new ServiceHeaderWriter(wscontext);
        //C
        else if (genaratorType == WrapperConstants.GENERATOR_PARAM_C_ALL)
            return new org.apache.axismora.wsdl2ws.c.AllParamWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_WRAPPER_C)
            return new org.apache.axismora.wsdl2ws.c.WrapWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_WRAPPER_H)
            return new WrapHeaderWriter(wscontext);
        else if (genaratorType == WrapperConstants.GENERATOR_SERVICE_C)
            return new org.apache.axismora.wsdl2ws.c.ServiceWriter(wscontext);
        //Common to C & C++
        else if (genaratorType == WrapperConstants.GENERATOR_CLASSLOADER_CPP)
            return new ClassLoader(wscontext);

        throw new WrapperFault("Source writer type not found");
    }
}
