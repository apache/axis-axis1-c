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
import java.net.InetAddress;

/**
 * this is a brute force poll-the-subnet discovery algorithm.
 * Bad form as the discovery traffic is huge. So why have it? simple
 * Multicast and Broadcast does not work with WinXP in ad-hoc mode. This
 * transceiver finds services in an ad-hoc space.
 * Do not use this over a big network as people will get upset :)
 */
public class SubnetPollTransceiver extends BroadcastTransceiver {

    private long startAddress;
    private int range;
    private int intervalSize;
    private int intervalPause;
    /**
     *  logging entry
     */
    private static Log log = LogFactory.getLog(SubnetPollTransceiver.class);

    /**
     * create the transceiver with subnet parameters
     * @param marshaller
     * @param portNumber
     * @param startAddress
     * @param range
     * @param intervalSize
     * @param intervalPause
     * @throws IOException
     */
    public SubnetPollTransceiver(Marshaller marshaller, int portNumber,
                                 long startAddress, int range, 
                                 int intervalSize, int intervalPause
                                 ) throws IOException {
        super(portNumber, portNumber, marshaller);
        this.intervalPause = intervalPause;
        this.intervalSize = intervalSize;
        this.range = range;
        this.startAddress = startAddress;
    }

    public void multicast(DatagramPacket packet, int ttl) throws IOException {
        packet.setPort(getSendPortNumber());
        byte[] addr = new byte[4];
        int interval = 0;
        //loop over all the addresses in this address space
        for (long address = startAddress; address < startAddress + range; address++) {
            Utils.makeAddressWord(address, addr);
            InetAddress ipv4Addr = InetAddress.getByAddress(addr);
            packet.setAddress(ipv4Addr);
            if (log.isDebugEnabled()) {
                log.debug("sending to " + ipv4Addr);
            }
            send(packet);
            //check for a timed pause
            if (intervalSize > 0 && ++interval > intervalSize) {
                //reset the counter
                interval = 0;
                //and sleep
                try {
                    Thread.sleep(intervalPause);
                } catch (InterruptedException swallowed) {
                       ;
                }
            }
        }
    }

}
