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

package org.apache.axismora.provider;

import javax.xml.namespace.QName;

import org.apache.axismora.Constants;
import org.apache.axismora.Handler;
import org.apache.axismora.MessageContext;
import org.apache.axismora.handlers.BasicHandler;
import org.apache.axismora.util.AxisUtils;

import org.apache.axis.AxisFault;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.apache.axis.message.SOAPFault;
import org.apache.axis.session.Session;
/**
 * This is the provider ... the actual implementation depends on the 
 * Concreate class. (the defferance of the style(RPC|MSG...) depends on the wrapper.)
 * @author hemapani
 */
public class BasicProvider extends BasicHandler implements Provider {
    protected Handler wrapper;
    protected WSDDService service;

    public BasicProvider(WSDDService service) {
        this.service = service;
    }

    public void invoke(MessageContext msgdata) throws AxisFault {
        try {
            // read  and validate body element and read the method name if it is RPC style.
            msgdata.startParseSOAPBody();

            String scope = service.getParameter(Constants.PARAMETER_SCOPE);

            //load according to the scope
            if (Constants.SCOPE_REQUEST.equals(scope)) {
                this.wrapper =
                    (Handler) msgdata.getServicePool().getService(
                        service.getServiceDesc().getName());
                if (this.wrapper == null) {
                    this.wrapper = this.loadNewWrapper();
                    msgdata.getServicePool().putService(
                        this.wrapper,
                        service.getServiceDesc().getName());
                    /* This is reqiured or else it is mark as avalible on the Service pool */
                    this.wrapper =
                        (Handler) msgdata.getServicePool().getService(
                            service.getServiceDesc().getName());
                }

            } else if (Constants.SCOPE_SESSION.equals(scope)) {
                //TODO still the session is based on the user and will not time out ???? 
                Session session = msgdata.getSession();
                if (session == null)
                    throw AxisUtils.getTheAixsFault(
                        org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                        "Session does not exists",
                        null,
                        this.getName(),
                        null);

                this.wrapper =
                    (Handler) msgdata.getServicePool().getService(
                        service.getServiceDesc().getName(),
                        String.valueOf(session.hashCode()));
                if (this.wrapper == null) {
                    this.wrapper = this.loadNewWrapper();
                    msgdata.getServicePool().putService(
                        this.wrapper,
                        service.getServiceDesc().getName(),
                        String.valueOf(session.hashCode()));
                    /* This is reqiured or else it is mark as avalible on the Service pool */
                    this.wrapper =
                        (Handler) msgdata.getServicePool().getService(
                            service.getServiceDesc().getName(),
                            String.valueOf(session.hashCode()));
                }

            }

            //if not one of above that means we should load new wrapper
            if (this.wrapper == null)
                this.wrapper = this.loadNewWrapper();
            this.wrapper.invoke(msgdata);

            //k ... we are done now return the service object
            if (!Constants.SCOPE_APPLICATION.equals(scope))
                msgdata.getServicePool().returnService(this.wrapper);
        } catch (Exception e) {
            e.printStackTrace();
            msgdata.setSoapFault(
                new SOAPFault(
                    AxisUtils.getTheAixsFault(
                        org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                        "Genaeral Exception at wrapper ",
                        null,
                        this.getName(),
                        e)));
        }
    }

    /**
     * This class load the Wrapper class for a given service dinamically 
     * @return Wrapper instance as a Handler 
     * @throws AxisFault
     */
    protected Handler loadNewWrapper() throws AxisFault {
        try {
            Class type = null;
            String wrapper = service.getParameter("className");
            if (wrapper == null || wrapper == "") {
                //if the parameter is not given check the default location
                QName qn = service.getQName();
                type =
                    Class.forName(
                        Constants.PATH_TO_WRAPPERS
                            + qn.getLocalPart()
                            + Constants.WRAPPER_NAME_APPENDER);
            } else {
                type = Class.forName(wrapper);
            }
            return (Handler) type.newInstance();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                "class not found",
                null,
                this.getName(),
                e);
        } catch (InstantiationException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                "instantiation error",
                null,
                this.getName(),
                e);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),
                null,
                this.getName(),
                e);
        }
    }
    /** 
     * This method give the role played by this handler
     * @see lk.opensource.service.Handler#getName()
     */
    public String getName() {
        return Constants.PROVIDER_ROLE;
    }

}
