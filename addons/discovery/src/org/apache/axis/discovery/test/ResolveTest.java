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
import org.apache.axis.discovery.server.ServiceEntry;
import org.apache.axis.discovery.server.UriStore;

/**
 *  test the uristore
 *
 */
public class ResolveTest extends TestCase {

    /**
     *  uristore used for testing
     */
    private UriStore uristore;

    /**
     *  schema1
     */
    protected static final String SCHEMA = "nap:underworld";

    /**
     *  schema2
     */
    protected static final String SCHEMA2 = "nap:underworld+born+slippy";

    /**
     *  schema3
     */
    protected static final String SCHEMA3 = "http://apache.org/somenamespace";

    /**
     *  endpoint#1
     */
    protected static final String URL = "http://127.0.0.1/endpoint";
    /**
     *  endpoint#2
     */
    protected static final String URL2 = "http://127.0.0.1/endpoint2";

    /**
     *  endpoint#3
     */
    protected static final String URL3 = "http://127.0.0.1/endpoint3";


    /**
     *  Constructor for the ResolveTest object
     *
     *@param  s  Description of the Parameter
     */
    public ResolveTest(String s) {
        super(s);
    }


    /**
     *  The JUnit setup method
     *
     *@exception  Exception  Description of the Exception
     */
    protected void setUp() throws Exception {
        uristore = new UriStore();
        uristore.registerSelf("udp://127.0.0.1:1234");
        uristore.add(SCHEMA, URL);
        uristore.add(SCHEMA2, URL2);
        uristore.add(SCHEMA2, URL3);
        ServiceEntry entry = new ServiceEntry();
        entry.setUrl(URL3);
        entry.setUri(SCHEMA3);
        entry.setMarker(false);
        entry.setStaticEntry(false);
        uristore.addServiceEntry(entry);
    }


    /**
     *  test we are adding our own service
     */
    public void testServiceLookup() {
        assertEquals(1, getEndpointCount(Const.DISCOVERY_SERVICE_URI));
    }


    /**
     *  test lookup of an added entry works
     */
    public void testLookupWorks() {
        String[] endpoints = uristore.lookup(SCHEMA);
        assertEquals(1, endpoints.length);
        assertEquals(URL, endpoints[0]);
    }


    /**
     *  if there is more than one entry, are both found?
     */
    public void testMultipleLookupWorks() {
        String[] endpoints = uristore.lookup(SCHEMA2);
        assertEquals(2, endpoints.length);
        assertTrue(!endpoints[0].equals(endpoints[1]));
    }


    /**
     *  does a message get processed
     */
    public void testProcessing() {
        DiscoveryMessage request = new DiscoveryMessage(DiscoveryMessage.MESSAGE_REQUEST);
        request.setUri(SCHEMA);
        DiscoveryMessage[] responses = uristore.processRequest(request);
        assertEquals(1, responses.length);
        assertEquals(URL, responses[0].getUrl());
        assertEquals(SCHEMA, responses[0].getUri());
        assertEquals(request.getMessageID(), responses[0].getMessageID());
    }

    /**
     * test that we can clean up stuff
     */
    public void testCleanup() {
        assertEquals(1, getEndpointCount(SCHEMA3));
        int size = uristore.size();
        uristore.markAllEntries();
        uristore.deleteAllMarkedNonStaticEntries();
        assertEquals(0, getEndpointCount(SCHEMA3));
        assertEquals(size - 1, uristore.size());

    }

    /**
     * get a count of the # of endpoints implementing a URI
     * @param uri
     * @return count, may be 0
     */
    private int getEndpointCount(String uri) {
        String[] endpoints = uristore.lookup(uri);
        return endpoints.length;
    }

    /**
     * verify that updating an existing endpoint replaces the existing copy
     * but the hit count is the combined value
     */
    public void testUpdatesPreserveHitCount() {
        //first get the existing entry of uri/url value
        ServiceEntry oldEntry = uristore.lookupEntry(SCHEMA2, URL3);
        assertNotNull(oldEntry);
        //set it with a hit count
        oldEntry.setHitCount(50);
        ServiceEntry entry = new ServiceEntry(SCHEMA2, URL3);
        entry.setHitCount(1);
        uristore.addServiceEntry(entry);
        ServiceEntry newEntry = uristore.lookupEntry(SCHEMA2, URL3);
        assertSame(entry, newEntry);
        assertEquals(newEntry.getHitCountInt(), 51);
    }
}

