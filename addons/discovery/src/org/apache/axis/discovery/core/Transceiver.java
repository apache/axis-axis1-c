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
 * abstract base class for transceivers - classes that send and receive
 * content
 */
public abstract class Transceiver {


    /**
     *  logging entry
     */
    private static Log log = LogFactory.getLog(Transceiver.class);

    /**
     * our marshalling algorithm
     */

    private Marshaller marshaller;

    /**
     * construct a transceiver
     * @param marshaller algorithm to marshall with
     */
    public Transceiver(Marshaller marshaller) {
        this.marshaller = marshaller;
    }

    /**
     * send a packet.
     * @param packet what to send
     * @throws IOException in case of emergency
     */
    public abstract void send(DatagramPacket packet) throws IOException;


    /**
     * send a packet to our configured sender.
     * @param packet what to send
     * @param ttl time to live, which can be ignored
     * @throws IOException in case of emergency
     */
    public abstract void multicast(DatagramPacket packet, int ttl)
            throws IOException;

    /**
     * wait for a packet.
     * @param timeout time to wait in milliseconds; 0 means no wait
     * @return packet received or null for timeout
     * @throws IOException if there was trouble
     */
    public abstract DatagramPacket receive(long timeout) throws IOException;


    /**
     * probe for data being ready.
     * @return true iff data is ready
     */
    public abstract boolean dataReady();

    /**
     * send a message
     * @param message message to send
     * @throws IOException
     */
    public void sendMessage(DiscoveryMessage message)
            throws IOException, DiscoveryException {
        DatagramPacket packet = marshaller.marshall(message);
        message.addressToSender(packet);
        send(packet);
    }

    /**
     * multicast a message
     * @param message message to send
     * @throws IOException
     */
    public void multicastMessage(DiscoveryMessage message, int ttl)
            throws IOException, DiscoveryException {
        DatagramPacket packet = marshaller.marshall(message);
        multicast(packet, ttl);
    }


    /**
     * receive a message
     * @param timeout how long to wait
     * @return null for timeout
     * @throws IOException when there is trouble
     */
    public DiscoveryMessage receiveMessage(long timeout)
            throws IOException, DiscoveryException {
        DatagramPacket packet = receive(timeout);
        if (packet == null) {
            return null;
        } else {
            if (log.isDebugEnabled()) {
                String messageText = Utils.stringFromDatagram(packet, 
                                                Const.MESSAGE_CHARSET);
                log.debug("Received [" + messageText + "]");
            }
            return marshaller.unmarshall(packet);
        }
    }

    /**
     * get a URL for receiving messages
     * @return a url for messages. return something in the uri: schema
     * for no real url.
     */
    public abstract String getReceiverURL();

    /**
     *  set a response packet to the sender info that came in with the request;
     *  the response can then be sent to the sender to arrive at the originating
     *  port
     *
     *@param  request received
     *@param  response response packet to edit
     */
    public void fillResponsePacket(DatagramPacket request,
                                   DatagramPacket response) {
        response.setAddress(request.getAddress());
        response.setPort(request.getPort());
    }

    /**
     * called at destroy time; use for any cleanup
     */
    public void destroy() {
    }

    /**
     * get the name of this transceiver
     * @return a name string
     */
    public abstract String getName();

    /**
     * can this transceiver actually receive data?
     * @return
     */
    public boolean canReceive() {
        return true;
    }

    public Marshaller getMarshaller() {
        return marshaller;
    }

    public void setMarshaller(Marshaller marshaller) {
        this.marshaller = marshaller;
    }
}
