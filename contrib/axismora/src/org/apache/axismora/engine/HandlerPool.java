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

package org.apache.axismora.engine;

import org.apache.axismora.HandlerChain;
import org.apache.axismora.util.NOTSupportedException;

import org.apache.axis.deployment.wsdd.WSDDService;

/**
 * <code>HandlerPool</code> take care of two types of handles<br>
 * <p><b>service handlers</b> are loaded as the service started and discarded once done. </p>
 * <p><b>static handlers</b> ,globel and transport handlers. They are loaded with the axis engine and will
 * reside in pool. If the call for a handler come when all that type of handlers are in use new handler will created.
 * When the handler is used up it is return to the pool than tye <code>init()</code> is called oupon the handler and
 * used agien.</p>
 * @author Srinath (hemapani@cse.mrt.ac.lk)
 */

public interface HandlerPool {
    public void init();

    /**
     * get request flow handlers assoicated with the protocol
     * @param protocol
     * @return HandlerChin which is not null
     * @throws ClassImplementationNotFoundException
     * @throws NOTSupportedException
     */

    public HandlerChain getTransportRequestFlowHandlers(int protocol)
        throws ClassImplementationNotFoundException, NOTSupportedException;

    /**
     * get request flow handlers assoicated with the protocol 
     * @param protocol
     * @return set of transport handlers from the pool
     */
    public HandlerChain getTransportResponseFlowHandlers(int protocol)
        throws ClassImplementationNotFoundException, NOTSupportedException;

    /**
     * give back the instance to pool so as it can recycle it
     * @param protocol
     * @throws ClassImplementationNotFoundException
     * @throws NOTSupportedException
    
     */
    public void returnTransportRequestFlowHandlers(int protocol, HandlerChain handler);

    /**
     * give back the instance to pool so as it can recycle it
     * @param protocol
     * @throws ClassImplementationNotFoundException
     * @throws NOTSupportedException     
     */
    public void returnTransportResponseFlowHandlers(int protocol, HandlerChain handler);

    /**
     * @return set of transport handlers from the pool
     * @throws ClassImplementationNotFoundException    
     */
    public HandlerChain getGlobelRequestFlowHandlers() 
    	throws ClassImplementationNotFoundException;

    /**
     * @return set of transport handlers from the pool
     * @throws ClassImplementationNotFoundException
     */
    public HandlerChain getGlobelResponseFlowHandlers()
        throws ClassImplementationNotFoundException;

    /**
     * give back the instance to pool so as it can recycle it
     */
    public void returnGlobelRequestFlowHandlers(HandlerChain handler);

    /**
     * give back the instance to pool so as it can recycle it
     */
    public void returnGlobelResponseFlowHandlers(HandlerChain handler);
    /**
     * return set of request flow handlers assoicated with the service
     * @param service
     * @return HandlerChain and it will never null. 
     * @throws ClassImplementationNotFoundException
     */
    public HandlerChain getServiceRequestFlowhandlers(WSDDService service)
        throws ClassImplementationNotFoundException;
    /**
     * return set of response flow handlers assoicated with the service
     * @param service
     * @return HandlerChain and it will never null. 
     * @throws ClassImplementationNotFoundException
     */
    public HandlerChain getServiceResponseFlowhandlers(WSDDService service)
        throws ClassImplementationNotFoundException;
    /**
     * return set of fault flow handlers assoicated with the service
     * @param service
     * @return HandlerChain and it will never null. 
     * @throws ClassImplementationNotFoundException
     */
    public HandlerChain getSeriveFaultFlowHandlers(WSDDService service)
        throws ClassImplementationNotFoundException;
}
