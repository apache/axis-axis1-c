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

package org.apache.axismora.client;

import java.util.ArrayList;

import javax.xml.namespace.QName;

import org.apache.axismora.Constants;
import org.apache.axismora.Handler;
import org.apache.axismora.HandlerChain;
import org.apache.axismora.MessageContext;
import org.apache.axismora.deployment.WebServiceNotFoundException;
import org.apache.axismora.engine.AxisEngine;
import org.apache.axismora.engine.ClassImplementationNotFoundException;
import org.apache.axismora.soap.BasicMessageContext;
import org.apache.axismora.soap.SOAPNodeInfo;

import org.apache.axis.AxisFault;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.apache.axis.message.SOAPFault;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class AxisClient extends AxisEngine {
    public AxisClient() throws Exception {
        super(Constants.CLIENT_CONFIG_FILE);
    }

    /**
     *  The Code does not start a new thread, If used in simple manner the process method will not execute 
     *  In parellel, But the process method is thread safe. To make the code parellel what should be done is 
     *  Called the process() in new thread. That is what done by the TomCat by default.    
     */
    public MessageContext processClient(ClientRequestContext requestContext) throws AxisFault {
        log.info("start processing service " + requestContext.getSoapAction().getLocalPart());
        try {
            MessageContext data = null;

            //create MessageData
            //*** this part should changed acording to actual implementation ****
            // to change here and message data

            WSDDService service;
            try {
                service =
                    deployment.getService(new QName(requestContext.getSoapAction().getLocalPart()));
            } catch (WebServiceNotFoundException e) {
                service = null;
                //client config file may not have entry ...quite ok ....
            }

            //TODO use encoding
            //SOAPAction gives you the name

            this.handlers = new Handler[7];
            /**
             * Load the Handlers to the engine
             */
            //finalize about protocol
            handlers[0] = pool.getTransportRequestFlowHandlers(Constants.HTTP);
            handlers[1] = pool.getGlobelRequestFlowHandlers();
            handlers[2] = pool.getServiceRequestFlowhandlers(service);

            handlers[3] = requestContext.getSender();

            handlers[4] = pool.getServiceResponseFlowhandlers(service);
            handlers[5] = pool.getGlobelResponseFlowHandlers();
            handlers[6] = pool.getTransportResponseFlowHandlers(Constants.HTTP);

            /**
             * get the handler Information and create a SOAPNodeInfo
             */
            SOAPNodeInfo nodeinfo = new SOAPNodeInfo(deployment);
            ArrayList roles = new ArrayList();
            ArrayList headers = new ArrayList();
            for (int i = 0;(i < handlers.length); i++) {
                if (i != 3) {
                    roles.addAll(((HandlerChain) handlers[i]).getAllRoles());
                    headers.addAll(((HandlerChain) handlers[i]).getAllUnderStandQNames());
                }
            }
            for (int i = 0; i < roles.size(); i++) {
                nodeinfo.addRole((String) roles.get(i));
            }
            for (int i = 0; i < headers.size(); i++) {
                nodeinfo.addUnderstandHeader((QName) headers.get(i));
            }
            /**
             * Initalize the MessageData
             */
            data = new BasicMessageContext(nodeinfo, service, servicepool, requestContext);
            data.setAtServerSide(false);
            data.setMethodName(requestContext.getMethodName());
            data.setSoapBodyContent(requestContext.getInparams());

            //set http user detail
            this.invoke(data);
            return data;
        } catch (Exception e) {
            throw AxisFault.makeFault(e);
        }

    } //end of run

    /**
     * Handler execution
     * @see org.apache.axismora.Handler#invoke(org.apache.axismora.MessageContext)
     */
    public void invoke(MessageContext context) throws AxisFault {
        /**
         * Invoke the Handlers
          */
        boolean hasfault = false;
        int i = 0;

        try {
            try {

                for (i = 0; i < handlers.length; i++) {
                    if (i == 3)
                        context.setAtPivot(true);
                    handlers[i].invoke(context);
                    if (i == 3) {
                        context.setAtPivot(false);
                        context.setPassPivot(true);
                    }
                    if (context.hasSoapFault()) {
                        hasfault = true;
                        break;
                    }
                }
            } catch (AxisFault e) {
                context.setSoapFault(new SOAPFault(e));
                hasfault = true;
            }
            //if faults are exits drive back the loop
            if (hasfault) {
                log.error("fault has occured stating driving handlers on onFault() back");
                for (int j = i - 1; j >= 0; j--) {
                    handlers[j].onFalult(context);
                }
                // run the fault flow
                pool.getSeriveFaultFlowHandlers(context.getService()).invoke(context);
            }

            //return the static Handlers
            pool.returnTransportRequestFlowHandlers(Constants.HTTP, (HandlerChain) handlers[0]);
            pool.returnGlobelRequestFlowHandlers((HandlerChain) handlers[1]);

            pool.returnGlobelResponseFlowHandlers((HandlerChain) handlers[5]);
            pool.returnTransportResponseFlowHandlers(Constants.HTTP, (HandlerChain) handlers[6]);
        } catch (ClassImplementationNotFoundException e) {
            e.printStackTrace();
            throw AxisFault.makeFault(e);
        }
    }

}
