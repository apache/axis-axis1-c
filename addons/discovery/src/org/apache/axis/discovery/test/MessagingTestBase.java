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
import org.apache.axis.discovery.core.Const;
import org.apache.axis.discovery.core.DiscoveryMessage;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.DatagramPacket;

/**
 * just a base class
 */
public class MessagingTestBase extends TestCase {

    public MessagingTestBase(String s) {
        super(s);
    }

    /**
     * this is just here as IDEA tries to run all classes that extend TestCase
     * and gets upset when there are no tests in a class.
     */
    public void testNoop() {

    }

    /**
     * create a request
     * @param uri
     * @param scope
     * @return
     */
    protected static DiscoveryMessage createRequest(String uri, String scope) {
        DiscoveryMessage message = new DiscoveryMessage(DiscoveryMessage.MESSAGE_REQUEST);
        message.setUri(uri);
        message.setScope(scope);
        return message;
    }

    /**
     * create a response
     * @param uri
     * @param scope
     * @param url
     * @param description
     * @return
     */
    protected DiscoveryMessage createResponse(String uri,
                                              String scope,
                                              String url,
                                              String description) {
        DiscoveryMessage message = new DiscoveryMessage(DiscoveryMessage.MESSAGE_REQUEST);
        message.setUri(uri);
        message.setScope(scope);
        message.setUrl(url);
        message.setDescription(description);
        return message;
    }

    /**
     * build a datagram from the text
     * @param xml any arbitrary text
     * @return packet for sending/processing
     * @throws IOException
     */
    protected DatagramPacket createDatagramFromText(String xml)
            throws IOException {
        ByteArrayOutputStream byteData = new ByteArrayOutputStream();
        OutputStreamWriter writer;
        writer = new OutputStreamWriter(byteData,
                Const.MESSAGE_CHARSET);
        writer.write(xml);
        writer.flush();
        writer.close();
        byte rawdata[] = byteData.toByteArray();
        DatagramPacket packet = new DatagramPacket(rawdata, byteData.size());
        return packet;
    }
}
