/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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


package org.apache.axis.discovery.client;

import org.apache.axis.discovery.core.Const;
import org.apache.axis.discovery.core.DiscoveryException;
import org.apache.axis.discovery.core.DiscoveryMessage;
import org.apache.axis.discovery.core.MulticastTransceiver;
import org.apache.axis.discovery.core.Transceiver;
import org.apache.axis.discovery.core.XmlMarshaller;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.IOException;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

/**
 *  implementation of a client to Discovery. Creates a transport,
 *  sends requests out
 *  and handles responses. To get per-message notifications as they come in,
 *  subclass or implement a ResponseReceivedListener and point the Client at it.
 *  @see ResponseReceivedListener
 *
 */
public class Client {

    /**
     *  discovery transceiver for comms
     */
    private Transceiver transceiver;

    /**
     * a single listener for responses; could be expanded to
     * a add/remove listener pattern if someone really wanted.
     */
    private ResponseReceivedListener listener;

    /**
     *  logging
     */
    private static Log log = LogFactory.getLog(Client.class);


    /**
     *  create a client using multicast
     *
     *@throws  IOException when things wont create
     */
    public Client() throws IOException {
        this(new MulticastTransceiver(Const.MBONE_ADDRESS,
                0,
                Const.MBONE_PORT,
                new XmlMarshaller()));
    }

    /**
     * create a client bound to whatever kind of transport is wanted.
     * @param transport
     */
    public Client(Transceiver transport) {
        this.transceiver = transport;
    }

    /**
     *  find all the endpoints in a given ttl area, the timeout is the total
     *  weight time
     *
     *@param  endpointUri what to look for
     *@param  ttl   scope of request
     *@param  timeout time to wait for responses in milliseconds
     *@param  limit max number of responses
     *@return a List of ResolveResponse entries, may be of size 0
     *@exception  IOException  any old trouble
     */
    public List findEndpoints(String endpointUri, int ttl, int timeout, 
                    int limit)
            throws IOException, DiscoveryException {
        DiscoveryMessage request = new DiscoveryMessage(DiscoveryMessage.MESSAGE_REQUEST);
        request.setUri(endpointUri);
        request.setScope("");
        List responses = new LinkedList();
        transceiver.multicastMessage(request, ttl);
        long now = System.currentTimeMillis();
        long end = now + timeout;
        long timeLeft;
        int count = 0;
        while ((timeLeft = end - now) > 0) {
            DiscoveryMessage response = transceiver.receiveMessage(timeLeft);

            if (response != null) {
                responses.add(response);
                log.debug("received " + response);
                count++;
                if (!messageReceived(response)) {
                    break;
                }
                //bail out when done
                if (limit > 0 && count >= limit) {
                    break;
                }
            }
            now = System.currentTimeMillis();
        }
        return responses;
    }

    /**
     * callback method for subclasses to override if they
     * dont want to wait for the timeout or limits to be reached
     * before acting on incoming data, or want a way of breaking early.
     * Default implementation forwards to ant ResponseReceivedListener
     * set previously
     * @param response received message
     * @return true if we are to continue waiting for more responses
     */
    public boolean messageReceived(DiscoveryMessage response) {
        if (listener != null) {
            return listener.messageReceived(response);
        } else {
            return true;
        }
    }

    /**
     *  go from a list of responses to a list of endpoints
     *
     *@param  responses  List of DiscoveryMessage elements
     *@return            array of endpoints
     *@todo              resolve duplicates
     */
    public String[] extractEndpointArray(List responses) {
        String[] endpoints = new String[responses.size()];
        int counter = 0;
        Iterator i = responses.iterator();
        while (i.hasNext()) {
            DiscoveryMessage response = (DiscoveryMessage) i.next();
            endpoints[counter++] = response.getUrl();
        }
        return endpoints;
    }

    /**
     * set a listener to be used for notifications of events
     * @param listener
     */
    public void setListener(ResponseReceivedListener listener) {
        this.listener = listener;
    }

    /**
     *  client entry point
     *
     *@param  args URI
     *@throws  Exception
     */
    public static void main(String args[]) throws Exception {
        String uri = Const.DISCOVERY_SERVICE_URI;
        if (args.length > 0) {
            uri = args[0];
        }
        System.out.println("Searching for [" + uri + "]");
        Client client = new Client();
        List responses = client.findEndpoints(uri,
                1,
                Const.CLIENT_TIMEOUT,
                0);
        String[] endpoints = client.extractEndpointArray(responses);
        System.out.println("Found " + endpoints.length + " endpoint(s)");
        for (int i = 0; i < endpoints.length; i++) {
            System.out.println(endpoints[i]);
        }
    }
}

