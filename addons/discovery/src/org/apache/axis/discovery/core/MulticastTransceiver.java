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
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;

/**
 * This class uses multicasting to send and receive requests
 */
public class MulticastTransceiver extends BroadcastTransceiver {

    /**
     *  logging entry
     */
    private static Log log = LogFactory.getLog(MulticastTransceiver.class);

    /**
     * get access to the multicast socket
     * @return
     */
    public MulticastSocket getMulticastSocket() {
        return (MulticastSocket) getSocket();
    }

    /**
     * create a new multicast transceiver.
     * @param address       multicast address
     * @param receivePortNumber receive port, or 0 for dont bind
     * @param sendPortNumber    send port
     * @throws IOException if anything went wrong, including missing lan
     */
    public MulticastTransceiver(String address,
                                int receivePortNumber,
                                int sendPortNumber,
                                Marshaller marshaller)
            throws IOException {
        super(marshaller);
        InetAddress multicastAddress = InetAddress.getByName(address);
        bind(receivePortNumber,
                sendPortNumber,
                multicastAddress.getByName("255.255.255.255"));

        try {
            getMulticastSocket().joinGroup(multicastAddress);
        } catch (IOException e) {
            //log with a hint then rethrow
            log.error("Unable to join group " + address
                    + "; this may mean the network is absent", e);
            throw e;
        }

        log.info("joined mcast " + address + ":" + sendPortNumber
                + "; listening on " + receivePortNumber);
    }

    /**
     * get the name of this transceiver
     * @return a name string
     */
    public String getName() {
        return "Multicast";
    }


    /**
     * send a packet to our configured sender.
     * @param packet what to send
     * @param ttl time to live, which can be ignored
     * @throws IOException in case of emergency
     */
    public void multicast(DatagramPacket packet, int ttl) throws IOException {
        getMulticastSocket().setTimeToLive(ttl);
        super.multicast(packet, ttl);
    }

    /**
     * create a new multicast socket.
     * @param receivePortNumber
     * @return
     * @throws IOException
     */
    protected DatagramSocket createSocket(int receivePortNumber)
            throws IOException {
        if (receivePortNumber != 0) {
            return new MulticastSocket(receivePortNumber);
        } else {
            return new MulticastSocket();
        }
    }

}
