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
import org.apache.axis.discovery.core.XmlMarshaller;

import java.io.IOException;
import java.net.DatagramPacket;

/**
 * test our to-from datagram marshalling
 */
public class MarshallTest extends MessagingTestBase {

    private Marshaller marshaller = new XmlMarshaller();

    public MarshallTest(String s) {
        super(s);
    }

    /**
     * marshall and unmarshall a message
     * @param message
     */
    public void roundTrip(DiscoveryMessage message)
            throws IOException, DiscoveryException {
        DatagramPacket packet = marshaller.marshall(message);
        DiscoveryMessage unmarshalled = marshaller.unmarshall(packet);
        /*
            Writer writer;
            writer = new OutputStreamWriter(System.out);
            unmarshalled.marshall(writer);
            writer.flush();
            System.out.println();
            */
        assertEquals(message, unmarshalled);
    }

    public void testRequest() throws Exception {
        String uri = "http://foo";
        String scope = "test";
        DiscoveryMessage message = createRequest(uri, scope);
        roundTrip(message);
    }

    public void testResponse() throws Exception {
        String uri = "http://foobar";
        String scope = "test";
        String url = "http://localhost";
        DiscoveryMessage message = createResponse(uri, scope, url, null);
        roundTrip(message);
    }

    public void testUnicoding() throws Exception {
        DiscoveryMessage message = createResponse("http://foobar",
                "test",
                "http://localhost",
                "Cost per use is \u20ac30");
        roundTrip(message);
    }


    /**
     * verify that we can handle bad XML
     * @throws Exception
     */
    public void testBadDatagrams() throws Exception {
        expectFailure("");
        expectFailure("<?xml version='1.0'?><discovery/>");
        expectFailure("<?xml version='1.0'?><discovery id='0' type='foobar'><uri>a</uri><scope/></discovery>");
        expectFailure("<?xml version='1.0'?><discovery id='0' type='request'><uri>a</uri><scope/></discovery>");
        expectFailure("<?xml version='1.0'?><discovery id='0' type='request'><uri>a</uri><scope>foo</scope></discovery>");
        expectFailure(new DatagramPacket(new byte[0], 0), "empty buffer");
        expectFailure(new DatagramPacket(new byte[256], 256), "256 buffer");
    }


    /**
     * expect an unmarshall failure on a string or bail
     * @param xml
     * @throws IOException
     */
    public void expectFailure(String xml) throws IOException, DiscoveryException {
        DatagramPacket packet = createDatagramFromText(xml);
        expectFailure(packet, "Expected failure from " + xml);
    }

    /**
     * handle an expected failure of a packet
     * @param packet
     * @param text
     */
    public void expectFailure(DatagramPacket packet, String text) {
        try {
            marshaller.unmarshall(packet);
            fail(text);
        } catch (IOException swallowed) {
            ;
        } catch (DiscoveryException swallowed) {
            ;
        }
    }

}
