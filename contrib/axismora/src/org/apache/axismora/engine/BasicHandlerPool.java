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

import java.util.Hashtable;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axismora.Constants;
import org.apache.axismora.Handler;
import org.apache.axismora.HandlerChain;
import org.apache.axismora.deployment.AxisDeployment;
import org.apache.axismora.handlers.BasicHandlerChain;
import org.apache.axismora.handlers.HandlerInfo;
import org.apache.axismora.util.NOTSupportedException;
import org.apache.axismora.util.SingeltonException;

import org.apache.axis.components.logger.LogFactory;
import org.apache.axis.deployment.wsdd.WSDDFaultFlow;
import org.apache.axis.deployment.wsdd.WSDDHandler;
import org.apache.axis.deployment.wsdd.WSDDRequestFlow;
import org.apache.axis.deployment.wsdd.WSDDResponseFlow;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.apache.commons.logging.Log;

/**
 * <code>HandlerPool</code> take care of two types of handles<br>
 * <p><b>service handlers</b> are loaded as the service started and discarded once done. </p>
 * <p><b>static handlers</b> ,globel and transport handlers. They are loaded with the axis engine and will
 * reside in pool. If the call for a handler come when all that type of handlers are in use new handler will created.
 * When the handler is used up it is return to the pool than tye <code>init()</code> is called oupon the handler and
 * used agien.</p> <br>When new handler is requested and it is a static Handler the handler
 * pool will search for the hander inside pool. If unused handlers are avalible it is returned. 
 * otherwise new handler is returned.  
 * <code>HandlerChain</code> is synchornized. 
 *  
 * @author Srinath(hemapani@cse.mrt.ac.lk)
 */
 
public class BasicHandlerPool implements HandlerPool {
    protected static Log log = LogFactory.getLog(BasicHandlerPool.class.getName());
    private Vector transportRequestHandlers;
    private Vector transportResponseHandlers;
    private Vector globelRequestFlowHandlers;
    private Vector globelResponseFlowHandlers;
    private AxisDeployment deployment;
    private Hashtable classname2HandlerInfo;

    private BasicHandlerPool(AxisDeployment deployment) {
        this.transportRequestHandlers = new Vector();
        this.transportResponseHandlers = new Vector();
        this.globelRequestFlowHandlers = new Vector();
        this.globelResponseFlowHandlers = new Vector();
        this.deployment = deployment;
        classname2HandlerInfo = new Hashtable();
        log.info("HandlerPool initialized");
    }

    public static BasicHandlerPool getInstance(AxisDeployment deployment) throws SingeltonException {
        return new BasicHandlerPool(deployment);
    }
	
	//initalize the handler pool
    public void init() {

    }

    /**
     * The code so far suppor HTTP only
     * @param protocol
     * @return set of transport handlers from the pool
     */
    public HandlerChain getTransportRequestFlowHandlers(int protocol) throws ClassImplementationNotFoundException, NOTSupportedException {
        HandlerChain chain;
        if (protocol == Constants.HTTP) {
            if (!this.transportRequestHandlers.isEmpty()) {
                chain = (HandlerChain) this.transportRequestHandlers.remove(0);
            } else {
                chain = this.loadHandlers(this.deployment.getTransportRequestFlowHandlers("http"));
            }
        } else {
            chain = null;
            System.out.println("we support the HTTP only in this version");
        }
        return chain;
    }

    /**
     * code still support HTTP only
     * @param protocol
     * @return set of transport handlers from the pool
     */
    public HandlerChain getTransportResponseFlowHandlers(int protocol) throws ClassImplementationNotFoundException, NOTSupportedException {
        HandlerChain chain;
        if (protocol == Constants.HTTP) {
            //recycle a handler chain
            if (!this.transportResponseHandlers.isEmpty()) {
                chain = (HandlerChain) this.transportResponseHandlers.remove(0);
            } else {
                //create a new handler chain
                chain = this.loadHandlers(this.deployment.getTransportResponseFlowHandlers("http"));
            }
        } else {
            chain = null;
            throw new NOTSupportedException("The implementation support only http");
        }
        return chain;
    }

    /**
     * give back the instance to pool so as it can recycle it
     * @param protocol
     */
    public void returnTransportRequestFlowHandlers(int protocol, HandlerChain handler) {
        handler.cleanup();
        initalizeHadlerChain(handler);
        if (protocol == Constants.HTTP)
            this.transportRequestHandlers.add(handler);
        else
            System.out.println("we support the HTTP only in this version");

    }

    /**
     * give back the instance to pool so as it can recycle it
     * @param protocol
     */
    public void returnTransportResponseFlowHandlers(int protocol, HandlerChain handler) {
        handler.cleanup();
		initalizeHadlerChain(handler);
        if (protocol == Constants.HTTP)
            this.transportResponseHandlers.add(handler);
        else
            System.out.println("we support the HTTP only in this version");
    }

    /**
     * @return set of transport handlers from the pool
     */
    public synchronized HandlerChain getGlobelRequestFlowHandlers() throws ClassImplementationNotFoundException {
        HandlerChain chain;
        if (!this.globelRequestFlowHandlers.isEmpty()) {
            chain = (HandlerChain) this.globelRequestFlowHandlers.remove(0);
        } else {
            chain = this.loadHandlers(this.deployment.getGlobelRequestFlowHandlers());
        }
        return chain;
    }

    /**
     * @return set of transport handlers from the pool
     */
    public synchronized HandlerChain getGlobelResponseFlowHandlers() throws ClassImplementationNotFoundException {
        HandlerChain chain;
        if (!this.globelResponseFlowHandlers.isEmpty()) {
            chain = (HandlerChain) this.globelResponseFlowHandlers.remove(0);
        } else {
            chain = this.loadHandlers(this.deployment.getGlobelResponseFlowHandlers());
        }
        return chain;
    }

    /**
     * give back the instance to pool so as it can recycle it
     */
    public void returnGlobelRequestFlowHandlers(HandlerChain handler) {
        handler.cleanup();
        initalizeHadlerChain(handler);
        this.globelRequestFlowHandlers.add(handler);
    }

    /**
     * give back the instance to pool so as it can recycle it
     */
    public void returnGlobelResponseFlowHandlers(HandlerChain handler) {
        handler.cleanup();
        initalizeHadlerChain(handler);
        this.globelResponseFlowHandlers.add(handler);
    }
 	/**
 	 * code written considering <code>WebService</code> return full qualified class name of handlers
 	 */
    public HandlerChain getServiceRequestFlowhandlers(WSDDService service) throws ClassImplementationNotFoundException {
        if(service == null) return new BasicHandlerChain();
        WSDDRequestFlow requestFlow = service.getRequestFlow();
        Vector reqHandlers;
        if (requestFlow != null)
            reqHandlers = requestFlow.getHandlers();
        else
            reqHandlers = new Vector();
        return this.loadHandlers(reqHandlers);
    }
	/**
	 * code written considering <code>WebService</code> return full qualified class name of handlers
	 */ 
    public HandlerChain getServiceResponseFlowhandlers(WSDDService service) throws ClassImplementationNotFoundException {        
		if(service == null) return new BasicHandlerChain();
        WSDDResponseFlow responseFlow = service.getResponseFlow();
        Vector resHandlers;
        if (responseFlow != null) {
            resHandlers = responseFlow.getHandlers();
        } else
            resHandlers = new Vector();
        return this.loadHandlers(resHandlers);
    }

    /**
     * How can a one service can have more than one FalultFlow ...???
     * I make them into to one chain is that right
     * @param service
     * @return Chain of FaultHandlers
     * @throws ClassImplementationNotFoundException
     */
    //TODO clear the  context of more than one Falut flow in Service
    public HandlerChain getSeriveFaultFlowHandlers(WSDDService service) throws ClassImplementationNotFoundException {
        WSDDFaultFlow[] faults = service.getFaultFlows();
        Vector faultHandlers = new Vector();
        Vector handlers;
        if(faults != null || faults.length != 0){
            for(int i=0;i<faults.length;i++){
                handlers = faults[i].getHandlers();
                if(handlers != null){
                   faultHandlers.addAll(handlers);
                }
            }
        }
        return this.loadHandlers(faultHandlers);
    }
    private synchronized void initalizeHadlerChain(HandlerChain chain){
        if(chain == null) return;
        chain.init(new HandlerInfo(this.classname2HandlerInfo));
    }
    /**
     * given a String Array the method loads classes given by these
     * Strings and return as a Handler Chain. If no handlers the Handler Chains will be
     * empty.
     * @param reqHandlers
     * @return handler Chain
     * @throws ClassImplementationNotFoundException
     */
    private HandlerChain loadHandlers(Vector reqHandlers) throws ClassImplementationNotFoundException {
        try {
            //The Handler must have parameterless contructor
            BasicHandlerChain chain = new BasicHandlerChain();

            if(reqHandlers == null)
                return chain;

            for (int i = 0; i < reqHandlers.size(); i++) {
                WSDDHandler handlerData = ((WSDDHandler) reqHandlers.get(i));
                QName h = handlerData.getType();
				//get handler class name 
                Class handlerType;
                if ("".equals(h.getNamespaceURI()))
                    handlerType = Class.forName(h.getLocalPart());
                else
                    handlerType = Class.forName(h.getNamespaceURI() + "." + h.getLocalPart());
				
				//load the handler ..handler must have a default constructor
                Handler handler = (Handler) handlerType.newInstance();
                //initalize the handler
                HandlerInfo info = new HandlerInfo(handlerData.getParametersTable());
                handler.init(info);
                this.classname2HandlerInfo.put(handlerType.getName(),info);
                
                chain.add(handler);
            }
            return chain;
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            throw new ClassImplementationNotFoundException(e.getMessage());
        } catch (InstantiationException e) {
            e.printStackTrace();
            throw new ClassImplementationNotFoundException(e.getMessage());
        } catch (IllegalAccessException e) {
            e.printStackTrace();
            throw new ClassImplementationNotFoundException(e.getMessage());
        }
    }
}//end of class
