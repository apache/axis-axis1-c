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

package org.apache.axis.discovery.server;

import org.apache.axis.discovery.core.Const;
import org.apache.axis.discovery.core.DiscoveryMessage;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Properties;


/**
 * Store of uris. May be a map, may be something else
 * to support multiple endpoints implementing the same uri
 * @author steve loughran
 */
public class UriStore {

    /**
     * our list of ServiceEntries
     */
    private LinkedList mappings;

    /**
     * log file
     */
    private static Log log = LogFactory.getLog(UriStore.class);

    /**
     * failure array is cached for performance
     */
    private static final String[] NOMATCH = new String[0];

    /**
     * create a store
     */
    public UriStore() {
        mappings = new LinkedList();
    }

    /**
     * Add a uri,url pair; service is static
     * @param uri
     * @param url
     */
    public void add(String uri, String url) {
        addServiceEntry(new ServiceEntry(uri, url));
    }

    /**
     * find all urls that map to a uri
     * @param uri
     * @return list of zero or more entries.
     */
    public List lookupEntries(String uri) {
        log.debug("looking for " + uri);
        List hits = new LinkedList();
        Iterator entries = mappings.iterator();
        while (entries.hasNext()) {
            ServiceEntry e = (ServiceEntry) entries.next();
            if (e.equalsURI(uri)) {
                hits.add(e);
            }
        }
        return hits;
    }

    /**
     * lookup an entry; match is on uri and url
     * @param entry
     * @return
     */
    public int indexOf(ServiceEntry entry) {
        return mappings.indexOf(entry);
    }

    /**
     * find all urls that map to a uri
     * @param uri
     * @return array of zero or more urls.
     */
    public String[] lookup(String uri) {
        List hits = lookupEntries(uri);
        int l = hits.size();
        log.debug("found " + l + " match(es)");
        if (l == 0) {
            return NOMATCH;
        } else {
            String[] endpoints = new String[l];
            Iterator hitit = hits.iterator();
            int count = 0;
            while (hitit.hasNext()) {
                ServiceEntry entry = (ServiceEntry) hitit.next();
                endpoints[count++] = entry.getUrl();
            }
            return endpoints;
        }
    }

    /**
     * register ourselves from a transport.
     * @param url url to register
     */
    public void registerSelf(String url) {
        add(Const.DISCOVERY_SERVICE_URI, url);
    }

    /**
     * Resolve the request.
     * Do not worry about repeat requests here, or anything
     *
     * @param request
     * @return array of responses
     */
    public DiscoveryMessage[] processRequest(DiscoveryMessage request) {
        List results = lookupEntries(request.getUri());
        DiscoveryMessage[] responses = new DiscoveryMessage[results.size()];
        Iterator resultIterator = results.iterator();
        int index = 0;
        while (resultIterator.hasNext()) {
            ServiceEntry entry = (ServiceEntry) resultIterator.next();
            DiscoveryMessage response = request.createResponse();
            entry.fillIn(response);
            entry.hit();
            responses[index] = response;
        }
        return responses;
    }


    /**
     * add a set of endpoints from a property array
     * @param props
     */
    public void registerProperties(Properties props) {
        Enumeration e = props.keys();
        while (e.hasMoreElements()) {
            String uri = (String) e.nextElement();
            add(uri, props.getProperty(uri));
        }
    }

    /**
     * add an entry to the store
     * @param entry
     */
    public synchronized void addServiceEntry(ServiceEntry entry) {
        int index = indexOf(entry);
        if (index == -1) {
            log.debug("adding "
                    + entry.getUri()
                    + " -> "
                    + entry.getUrl());
            mappings.add(entry);
        } else {
            ServiceEntry oldentry = (ServiceEntry) mappings.get(index);
            if (entry.equals(oldentry)) {
                log.debug("updating "
                        + entry.getUri()
                        + " -> "
                        + entry.getUrl());
                entry.setHitCount(entry.getHitCount().intValue()
                        + oldentry.getHitCount().intValue());
                mappings.set(index, entry);
            }
        }
    }

    /**
     * get an iterator over the entries, all of type ServiceEntry
     * not a clone; not synchronized, use carefully
     * @return iterator of type ServiceEntry
     */
    public Iterator getEntries() {
        return mappings.iterator();
    }

    /**
     * purge all non-static entries from the list that have their
     * marker flag set
     * this is for removing undeployed axis entries
     */
    public synchronized void deleteAllMarkedNonStaticEntries() {
        Iterator entries = mappings.iterator();
        while (entries.hasNext()) {
            ServiceEntry e = (ServiceEntry) entries.next();
            if (!e.isStaticEntry() && e.getMarker()) {
                entries.remove();
            }
        }
    }


    /**
     * purge all non-static entries from the list
     * this is for removing undeployed axis entries
     */
    public synchronized void markAllEntries() {
        Iterator entries = mappings.iterator();
        while (entries.hasNext()) {
            ServiceEntry e = (ServiceEntry) entries.next();
            e.setMarker(true);
        }
    }

    /**
     * get a shallow clone of the mappings
     * @return a clone of the mappings
     */
    public LinkedList cloneMappings() {
        return (LinkedList) mappings.clone();
    }

    /**
     * set the mappings list
     * @param mappings
     */
    public synchronized void setMappings(LinkedList mappings) {
        this.mappings = mappings;
    }

    /**
     * how many entries are in the list
     * @return
     */
    public int size() {
        return mappings.size();
    }

    /**
     * return the sole entry bound to an uri/endpoint pair
     * @param uri   uri of service
     * @param endpoint  endpoint
     * @return entry or null
     */
    public ServiceEntry lookupEntry(String uri, String endpoint) {
        ServiceEntry entry = null;
        List entries = lookupEntries(uri);
        Iterator i = entries.iterator();
        while (i.hasNext()) {
            ServiceEntry serviceEntry = (ServiceEntry) i.next();
            if (endpoint.equals(serviceEntry.getUrl())) {
                entry = serviceEntry;
                break;
            }
        }
        return entry;
    }
}

