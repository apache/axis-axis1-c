/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
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
package org.apache.axis.wsdl;

import java.util.HashMap;

import javax.wsdl.Binding;
import javax.wsdl.Definition;
import javax.wsdl.PortType;
import javax.wsdl.Service;

/**
* Writer and WriterFactory are part of the Writer framework.  Folks who want
* to use the emitter to generate stuff from WSDL should do 3 things:
* 1.  Write implementations of the Writer interface, one each for PortType,
*     Binding, Service, and Type.  These implementations generate the stuff
*     for each of these WSDL types.
* 2.  Write an implementation of the WriterFactory interface that returns
*     instantiations of these Writer implementations as appropriate.
* 3.  Implement a class with a main method (like Wsdl2java) that instantiates
*     an Emitter and passes it the WriterFactory implementation
*/

public interface WriterFactory {
    /**
     * Get a Writer implementation that will generate bindings for the given
     * PortType and HashMap of Parameters keyed off of operations.
     */
    public Writer getWriter(PortType portType, HashMap operationParameters);

    /**
     * Get a Writer implementation that will generate bindings for the given
     * Binding and HashMap of Parameters keyed off of operations.
     */
    public Writer getWriter(Binding binding, HashMap operationParameters);

    /**
     * Get a Writer implementation that will generate bindings for the given
     * Service and HashMap of (HashMap of Parameters keyed off of operations)
     * keyed off of portTypes.
     */
    public Writer getWriter(Service service, HashMap portTypeOperationParameters);

    /**
     * Get a Writer implementation that will generate bindings for the given
     * Type.
     */
    public Writer getWriter(Type type);

    /**
     * Get a Writer implementation that will generate anything that doesn't
     * fit into the scope of any of the other writers.
     */
    public Writer getWriter(Definition definition);

    /**
     * Provide the Emitter to the factory.
     */
    public void setEmitter(Emitter emitter);
}
