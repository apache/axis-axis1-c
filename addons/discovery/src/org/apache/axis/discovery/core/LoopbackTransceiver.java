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

package org.apache.axis.discovery.core;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.io.IOException;
import java.net.DatagramPacket;

/**
 * loopback for testing and the like
 */
public class LoopbackTransceiver extends Transceiver {

    public LoopbackTransceiver(Marshaller marshaller) {
        super(marshaller);
    }

    private MessageQueue queue = new MessageQueue();

    /**
     *  logging entry
     */
    private static Log log = LogFactory.getLog(LoopbackTransceiver.class);

    /**
     * wait for a packet.
     * @param timeout time to wait in milliseconds; 0 means no wait
     * @return packet received or null for timeout
     * @throws IOException if there was trouble
     */
    public DatagramPacket receive(long timeout) throws IOException {
        return queue.getNextPacketBlocking(timeout);
    }

    /**
     * send a packet.
     * @param packet what to send
     * @throws IOException in case of emergency
     */
    public void send(DatagramPacket packet) throws IOException {
        queue.add(packet);
    }

    /**
     * send a packet to our configured sender.
     * @param packet what to send
     * @param ttl time to live, which can be ignored
     * @throws IOException in case of emergency
     */
    public void multicast(DatagramPacket packet, int ttl) throws IOException {
        send(packet);
    }

    /**
     * probe for data being ready. optional implementation
     * @return true iff data is ready
     */
    public boolean dataReady() {
        return !queue.isEmpty();
    }

    /**
     * get a URL for receiving messages
     * @return a url for messages. return something in the uri: schema
     * for no real url.
     */
    public String getReceiverURL() {
        return "uri:loopback";
    }

    /**
     * get the name of this transceiver
     * @return a name string
     */
    public String getName() {
        return "Loopback";
    }
}
