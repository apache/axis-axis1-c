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

import org.apache.axis.AxisEngine;
import org.apache.axis.ConfigurationException;
import org.apache.axis.description.ServiceDesc;
import org.apache.axis.discovery.core.Const;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import java.util.Iterator;

/**
 *  class to bind against Axis
 *
 */
public class AxisBinder {

    /**
     *  base url of this web service
     */
    private String baseURL;

    /**
     *  the axis engin we are bound to
     */
    private AxisEngine engine;

    /**
     *  the uri store
     */
    private UriStore store;

    /**
     *  when did we last sync up
     */
    private long lastSync = 0;

    /**
     *  sync interval
     */
    private long interval = Const.AXIS_BINDER_RESYNC_INTERVAL;

    /**
     * the log
     */
    private static Log log = LogFactory.getLog(AxisBinder.class);

    /**
     * what is the scope for services unless they (somehow) say otherwise
     */
    private static String defaultScope = "*";

    /**
     *  Constructor for the AxisBinder object
     */
    public AxisBinder() {
    }


    /**
     *  create a binding
     *
     *@param  baseURL
     *@param  engine
     *@param  store
     *@param  interval
     *@return           Description of the Return Value
     */
    public boolean bind(String baseURL, AxisEngine engine, UriStore store, long interval) {
        this.baseURL = baseURL;
        if (!baseURL.endsWith("/")) {
            baseURL += "/";
        }
        this.engine = engine;
        this.store = store;
        this.interval = interval;
        resync();
        return true;
    }


    /**
     *  update the store with the engine settings;
     *
     * @return    true iff a refresh went through
     */
    public synchronized boolean resync() {
        long now = System.currentTimeMillis();
        if (lastSync + interval > now) {
            return false;
        }
        Iterator i = null;
        try {
            i = engine.getConfig().getDeployedServices();
        } catch (ConfigurationException e) {
            log.fatal("getting deployed axis services", e);
            return false;
        }
        store.markAllEntries();
        while (i.hasNext()) {
            ServiceEntry entry = new ServiceEntry();
            ServiceDesc service = (ServiceDesc) i.next();
            String name = service.getName();
            //service.getEndpointURL();

            String uri = service.getDefaultNamespace();
            if (uri == null) {
                uri = "service:" + name;
            }
            entry.setUrl(baseURL + "/services/" + name);
            entry.setUri(uri);
            entry.setMarker(false);
            entry.setStaticEntry(false);
            entry.setDescription("Apache Axis Endpoint");
            entry.setScope(defaultScope);
            store.addServiceEntry(entry);
        }
        store.deleteAllMarkedNonStaticEntries();
        return true;
    }

    /**
     * what is the current scope?
     * @return
     */
    public static String getDefaultScope() {
        return defaultScope;
    }

    /**
     * update the scope of services
     * @param defaultScope new scope
     */
    public static void setDefaultScope(String defaultScope) {
        AxisBinder.defaultScope = defaultScope;
    }
}

