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

package org.apache.axismora.services;

import org.apache.axismora.MessageContext;
import org.apache.axismora.deployment.AxisDeployment;
import org.apache.axismora.deployment.wsdd.WSDDDeployment;
import org.apache.axismora.handlers.BasicHandler;
import org.apache.axismora.util.AxisUtils;

import org.apache.axis.AxisFault;
import org.apache.axis.deployment.wsdd.WSDDConstants;
import org.apache.axis.deployment.wsdd.WSDDException;
import org.apache.axis.deployment.wsdd.WSDDService;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

/**
 * This class handles the deployment of web service 
 * as a other web service.     
 * @author Srianth Perera(hemapani@opensource.lk)
 */
public class AdminService extends BasicHandler {
    public void invoke(MessageContext msgContext) throws AxisFault {
        try {
            Element deployment = AxisUtils.make(msgContext.getBodyParser());

            NodeList nl = deployment.getElementsByTagName(
            	WSDDConstants.ELEM_WSDD_SERVICE);

            if (nl.getLength() != 0) {
                WSDDService service = new WSDDService((Element) nl.item(0));
                AxisDeployment adep = msgContext.getDeployment();

                if (WSDDConstants.ELEM_WSDD_DEPLOY.equals(deployment.getLocalName()))
                    adep.deployService(service);
                else if (WSDDConstants.ELEM_WSDD_UNDEPLOY.equals(deployment.getLocalName()))
                    adep.undeployService(service.getQName());
                /* if this is a wsdd deploymnet we will change the configaration file 
                null means that to write to conf file the conf loaded from */
                if (adep instanceof WSDDDeployment)
                     ((WSDDDeployment) adep).writeToContext(null);
                Element e = AxisUtils.getCommonDomDocument().createElement("message");
                e.appendChild(
                    AxisUtils.getCommonDomDocument().createTextNode("configaration processed"));
                msgContext.setSoapBodyContent(new Element[] { e });
            } else
                throw new WSDDException("Cant find data to Deploy the Service");
        } catch (Exception e) {
            if (e instanceof AxisFault)
                throw (AxisFault) e;
            throw AxisUtils.getTheAixsFault(
                org.apache.axis.Constants.FAULT_SOAP12_RECEIVER,
                e.getMessage(),null,this.getName(), e);
        }
    }
}
