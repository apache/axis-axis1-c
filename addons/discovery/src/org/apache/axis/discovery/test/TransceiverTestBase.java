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

import org.apache.axis.discovery.core.DiscoveryException;
import org.apache.axis.discovery.core.DiscoveryMessage;
import org.apache.axis.discovery.core.Marshaller;
import org.apache.axis.discovery.core.Transceiver;
import org.apache.axis.discovery.core.XmlMarshaller;

import java.io.IOException;

/**
 * This is just the base class for transceiver tests
 */
public abstract class TransceiverTestBase extends MessagingTestBase {

    protected Transceiver transceiver;

    public TransceiverTestBase(String s) {
        super(s);
    }

    /**
     * create a subclass of transceiver
     * @return a new txr instance
     */
    protected abstract Transceiver createTransceiver()
            throws IOException, DiscoveryException;

    /**
     * create the transceiver from the subclass
     * @throws Exception
     */
    protected void setUp() throws Exception {
        transceiver = createTransceiver();
    }

    /**
     * destroy the transceiver
     * @throws Exception
     */
    protected void tearDown() throws Exception {
        transceiver.destroy();
    }


    public void testMulticastPush() throws Exception {
        DiscoveryMessage message = createRequest("uri:foo", "debug");
        transceiver.multicastMessage(message, 0);
        DiscoveryMessage message2;
        message2 = transceiver.receiveMessage(0);
        assertNotNull(message2);
    }

    public void testMulticastRoundTrip() throws Exception {
        DiscoveryMessage message = createRequest("uri:foo", "debug");
        transceiver.multicastMessage(message, 0);
        DiscoveryMessage message2;
        message2 = transceiver.receiveMessage(0);
        assertEquals(message, message2);
    }

    public void testUnicodeRoundTrip() throws Exception {
        DiscoveryMessage message = createRequest("uri:\u05d00", "\u0416");
        transceiver.multicastMessage(message, 0);
        DiscoveryMessage message2;
        message2 = transceiver.receiveMessage(0);
        assertEquals(message, message2);
    }

    public void testBlockingWorks() throws Exception {
        DiscoveryMessage message;
        message = transceiver.receiveMessage(100);
        assertNull(message);
    }

    public void testGetURL() {
        String url = transceiver.getReceiverURL();
        assertNotNull(url);
    }

    public Marshaller createMarshaller() {
        return new XmlMarshaller();
    }


}
