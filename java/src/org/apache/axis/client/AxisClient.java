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

package org.apache.axis.client ;

import org.apache.axis.AxisEngine;
import org.apache.axis.AxisFault;
import org.apache.axis.ConfigurationProvider;
import org.apache.axis.Constants;
import org.apache.axis.Handler;
import org.apache.axis.MessageContext;
import org.apache.axis.SimpleTargetedChain;
import org.apache.axis.configuration.FileProvider;
import org.apache.axis.utils.JavaUtils;
import org.apache.log4j.Category;

/**
 * Provides the equivalent of an "Axis engine" on the client side.
 * Subclasses hardcode initialization & setup logic for particular
 * client-side transports.
 *
 * @author Rob Jellinghaus (robj@unrealities.com)
 * @author Doug Davis (dug@us.ibm.com)
 * @author Glen Daniels (gdaniels@allaire.com)
 */
public class AxisClient extends AxisEngine
{
    static Category category =
            Category.getInstance(AxisClient.class.getName());

    public AxisClient(ConfigurationProvider provider)
    {
        super(provider);
    }
    
    public AxisClient()
    {
        this(new FileProvider(Constants.CLIENT_CONFIG_FILE));
    }

    /**
     * this *is* the client engine!
     */
    public AxisEngine getClientEngine () {
        return this;
    }

    /**
     * Main routine of the AXIS engine.  In short we locate the appropriate
     * handler for the desired service and invoke() it.
     */
    public void invoke(MessageContext msgContext) throws AxisFault {
        if (category.isDebugEnabled()) {
            category.debug(JavaUtils.getMessage("enter00", 
                "AxisClient::invoke") );
        }

        String  hName = null ;
        Handler h     = null ;

        // save previous context
        MessageContext previousContext = getCurrentMessageContext();

        try {
            // set active context
            setCurrentMessageContext(msgContext);

            hName = msgContext.getStrProp( MessageContext.ENGINE_HANDLER );
            if (category.isDebugEnabled()) {
                category.debug( "EngineHandler: " + hName );
            }

            if ( hName != null ) {
                h = getHandler( hName );
                if ( h != null )
                    h.invoke(msgContext);
                else
                    throw new AxisFault( "Client.error",
                                        JavaUtils.getMessage("noHandler00", hName),
                                        null, null );
            }
            else {
                // This really should be in a handler - but we need to discuss it
                // first - to make sure that's what we want.

                /* Now we do the 'real' work.  The flow is basically:         */
                /*                                                            */
                /*   Service Specific Request Chain                           */
                /*   Global Request Chain                                     */
                /*   Transport Request Chain - must have a send at the end    */
                /*   Transport Response Chain                                 */
                /*   Global Response Chain                                    */
                /*   Service Specific Response Chain                          */
                /*   Protocol Specific-Handler/Checker                        */
                /**************************************************************/

                // When do we call init/cleanup??

                SimpleTargetedChain service = null ;
                msgContext.setPastPivot(false);

                /* Process the Service Specific Request Chain */
                /**********************************************/
                hName =  msgContext.getTargetService();
                if ( hName != null && (h = getService( hName )) != null ) {
                    if ( h instanceof SimpleTargetedChain ) {
                        service = (SimpleTargetedChain) h ;
                        h = service.getRequestHandler();
                    }
                    if ( h != null ) h.invoke( msgContext );
                }

                /* Process the Global Request Chain */
                /**********************************/
                if ((h = getGlobalRequest()) != null )
                    h.invoke(msgContext);

                /** Process the Transport Specific stuff
                 *
                 * NOTE: Somewhere in here there is a handler which actually
                 * sends the message and receives a response.  Generally
                 * this is the pivot point in the Transport chain.
                 */
                hName = msgContext.getTransportName();
                if ( hName != null && (h = getTransport( hName )) != null )
                    h.invoke(msgContext);
                else
                    throw new AxisFault(JavaUtils.getMessage("noTransport00", hName));

                /* Process the Global Response Chain */
                /***********************************/
                if ((h = getGlobalResponse()) != null)
                    h.invoke(msgContext);

                if ( service != null ) {
                    h = service.getResponseHandler();
                    if ( h != null )
                        h.invoke(msgContext);
                }

                // Do SOAP Semantics checks here - this needs to be a call to
                // a pluggable object/handler/something
            }

        } catch( Exception e ) {
            // Should we even bother catching it ?
            category.error( e );
            throw AxisFault.makeFault(e);

        } finally {
            // restore previous state
            setCurrentMessageContext(previousContext);
        }

        if (category.isDebugEnabled()) {
            category.debug(JavaUtils.getMessage("exit00", 
                "AxisClient::invoke") );
        }
    };

    public void undo(MessageContext msgContext) {
        if (category.isDebugEnabled()) {
            category.debug(JavaUtils.getMessage("enter00", "AxisClient::undo"));
            category.debug(JavaUtils.getMessage("exit00", "AxisClient::undo") );
        }
    }
}

