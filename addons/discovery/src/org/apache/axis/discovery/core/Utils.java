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

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 * general utility stuff
 */
public final class Utils {
    private Utils() {
    }

    /**
     *  what this the local address of this system as a dotted string. this may
     *  just be 127.0.0.1 if nothing else
     *
     *@return    host ip addr
     */
    public static String getLocalAddress(DatagramSocket socket) {
        String hostaddr;
        InetAddress address = socket.getLocalAddress();
        hostaddr = address.getHostAddress();

        //looks like the system always thinks we are listening on
        //all ports, even though that is not necessarily true.
        if ("0.0.0.0".equals(hostaddr)) {
            try {
                address = InetAddress.getLocalHost();
                hostaddr = address.getHostAddress();
            } catch (UnknownHostException noIpAddrException) {
                //bail out here
                hostaddr = "127.0.0.1";
            }
        }
        return hostaddr;
    }

    public static long getLocalAddressValue() {
        long addr;
        try {
            InetAddress address = InetAddress.getLocalHost();
            byte[] byteval = address.getAddress();
            addr = (((long) byteval[0]) << 24) | (byteval[1] << 16)
                    | (byteval[2] << 8) | (byteval[3]);
        } catch (UnknownHostException e) {
            addr = (long) 0x7f000001;
        }
        return addr;
    }

    public static String toDotAddressString(long address) {
        byte[] bytes = makeAddressWord(address);
        StringBuffer buffer = new StringBuffer(5 * 3);
        buffer.append(bytes[0]);
        buffer.append('.');
        buffer.append(bytes[1]);
        buffer.append('.');
        buffer.append(bytes[2]);
        buffer.append('.');
        buffer.append(bytes[3]);
        return new String(buffer);
    }

    /**
     * get a string from a datagram
     * @param packet
     * @param charset to use
     * @return datagram string
     * @throws IOException if things go awry
     */
    public static String stringFromDatagram(DatagramPacket packet, String charset)
            throws IOException {
        ByteArrayInputStream bin = new ByteArrayInputStream(packet.getData());
        InputStreamReader reader = null;
        StringBuffer result = new StringBuffer();
        int limit = packet.getLength();
        int count = 0;
        try {

            reader = new InputStreamReader(bin, charset);
            int c;
            //spin till finished, we got a 0 byte (overshoot) or we
            //could not read any more.
            while ((c = reader.read()) != -1 && c != 0 && count < limit) {
                char read = (char) c;
                result.append(read);
                count++;
                //handle UTF8 & UTF16 encoding by skipping more bytes.
                if (c >= 256) {
                    count++;
                }
            }
        } finally {
            try {
                reader.close();
            } catch (IOException swallowed) {
                ;
            }
        }
        return new String(result);
    }

    /**
     * get a word from an address
     * @param address
     * @param addr
     */
    public static void makeAddressWord(long address, byte[] addr) {
        addr[0] = (byte) ((address & 0xff000000) >> 24);
        addr[1] = (byte) ((address & 0x00ff0000) >> 16);
        addr[2] = (byte) ((address & 0x0000ff00) >> 8);
        addr[3] = (byte) (address & 0x000000ff);
    }

    public static byte[] makeAddressWord(long address) {
        byte[] addr = new byte[4];
        makeAddressWord(address, addr);
        return addr;
    }
}
