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

package org.apache.axismora.handlers;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Vector;

import javax.xml.namespace.QName;

import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
import org.apache.axismora.Handler;
import org.apache.axismora.HandlerChain;
import org.apache.axismora.MessageContext;
/**
 * This Class is the Concerate implementation of the Handler Chain. Invoke 
 * method will call the Handlers in order. In case of Error the Handlers That 
 * are called will be driven backward.   
 * @author Srinath Perera (hemapani@opensource.lk)
 */
public class BasicHandlerChain extends BasicHandler implements HandlerChain {
    private Vector handlers;

    public BasicHandlerChain() {
        this.handlers = new Vector();
    }

    /**
     * add new <code>Handler</code> to the chain
     * @param handler
     */
    public void add(Handler handler) {
        if (handler != null)
            this.handlers.add(handler);
    }

    /**
     * renove <code>Handler</code> to the chain
     * @param handler
     */
    public void remove(Handler handler) {
        if (handler != null)
            this.handlers.remove(handler);
    }

    /**
     *  This method is called by the axis engine when invoking the handler
     *  @param msgdata
     */
    public void invoke(MessageContext msgdata) throws AxisFault {
        boolean hasfault = false;
        AxisFault fault = null;
        int i = 0;
        //invoke the handlers
        try {
            for (i = 0; i < this.handlers.size(); i++) {
                ((Handler) this.handlers.get(i)).invoke(msgdata);
                if (msgdata.hasSoapFault()) {
                    hasfault = true;
                    break;
                }
            }
        } catch (AxisFault e) {
            fault = e;
            msgdata.setSoapFault(new SOAPFault(e));
            hasfault = true;
        }
        //if fault is there all the executed handlers are driven back
        if (hasfault) {
            for (int j = i; j >= 0; j--) {
                ((Handler) this.handlers.get(j)).onFalult(msgdata);
            }
            //after runing the Handlers inside this HandlerChain throw the fault 
            //SOAP the other handers can be driven back
            if (fault != null)
                throw fault;
        }
    }

    /**
     * initalize the HandlerChain using the HashMap of HashMaps(configaration to
     * each handler) passed in as the conf. 
     */
    public void init(HandlerInfo conf) {
		Handler handler;
    	if(conf != null){ 
		    for (int i = 0; i < this.handlers.size(); i++) {
		        handler = ((Handler) this.handlers.get(i));
		        handler.init((HandlerInfo) conf.getConfig().get(handler.getClass().getName()));
		    }
    	}else{
			for (int i = 0; i < this.handlers.size(); i++) {
				handler = ((Handler) this.handlers.get(i));
				handler.init(new HandlerInfo(new Hashtable()));
			}    	
    	}    
    }

    /**
     *  This method is called by axis engine in case of error
     *  @param msgdata
     */
    public void onFalult(MessageContext msgdata) {
        for (int i = this.handlers.size() - 1; i >= 0; i--) {
            ((Handler) this.handlers.get(i)).onFalult(msgdata);
        }
    }

    /**
     * clean up all the handlers 
     */
    public void cleanup() {
        for (int i = 0; i < this.handlers.size(); i++) {
            ((Handler) this.handlers.get(i)).cleanup();
        }
    }

    /**
     * get all the roles that played by the Handlers in this handlerChain 
     */
    public ArrayList getAllRoles() {
        ArrayList roles = new ArrayList();
        String role;
        for (int i = 0; i < this.handlers.size(); i++) {
            role = ((Handler) this.handlers.get(i)).getName();
            if (role != null)
                roles.add(role);
        }
        return roles;
    }

    /**
     * get all the SOAPHeaders this Handler chain can understood  
     */
    public ArrayList getAllUnderStandQNames() {
        ArrayList headersList = new ArrayList();
        QName[] headers;
        for (int i = 0; i < this.handlers.size(); i++) {
            headers = ((Handler) this.handlers.get(i)).getUnderstandHeaders();
            if (headers == null)
                break;
            for (int j = 0; j < headers.length; j++) {
                if (headers[j] != null)
                    headersList.add(headers[j]);
            }
        }
        return headersList;
    }
} //end of class
