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

package org.apache.axis.discovery.test;

import junit.framework.TestCase;
import org.apache.axis.discovery.client.Client;
import org.apache.axis.discovery.core.Const;
import org.apache.axis.discovery.server.DiscoveryServer;

import java.util.List;

/**
 * This is a fun little test case. It sets up a server in one
 * thread then calls it in a client; the client asserts that
 * it gets back at least one response to the request.
 * This test only works if a network is present, because mcast
 * sockets are somehow fussier than normal sockets...you cannot
 * join an mcast group off-line, at least not on WinXP.
 * @author Steve Loughran
 * @created Jul 11, 2002 3:40:51 PM
 */

public class NetworkTest extends TestCase {

    private DiscoveryServer _server;

    public NetworkTest(String s) {
        super(s);
    }


    protected void setUp() throws Exception {
        _server = new DiscoveryServer();
        _server.startInNewThread();

    }

    protected void tearDown() throws Exception {
        _server.stop();
    }

    /**
     * who says you cant do functional tests with junit?
     * @throws Exception
     */
    public void testLoopback() throws Exception {
        String uri = Const.DISCOVERY_SERVICE_URI;
        System.out.println("Searching for [" + uri + "]");
        Client client = new Client();
        List responses = client.findEndpoints(uri,
                1,
                Const.CLIENT_TIMEOUT,
                0);
        String[] endpoints = client.extractEndpointArray(responses);
        int length = endpoints.length;
        assertTrue("No response from server", length > 0);
        String localURL = _server.getTransceiver().getReceiverURL();
        boolean matchFound = false;
        for (int i = 0; i < length; i++) {
            System.out.println(endpoints[i]);
            if (localURL.equals(endpoints[i])) {
                matchFound = true;
            }
        }
        assertTrue("no match for our local server found", matchFound);
    }


}

