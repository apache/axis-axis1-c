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
import org.apache.axis.discovery.server.management.ServiceEntryMBean;

import java.io.Serializable;

/**
 *  this is what is put in the UriStore, description and stats for a service
 *  some of the fields here are for the store.
 *  @author steve loughran
 */
public class ServiceEntry
        implements Serializable, ServiceEntryMBean {

    /**
     *  URI of service
     */
    private String uri;
    /**
     *  URL of service
     */
    private String url;
    /**
     *  scope of queries
     */
    private String scope;

    /**
     *  description
     */
    private String description;

    /**
     *  number of times an entry has been hit
     */
    private int hitCount = 0;

    /**
     * is a service static, that is the axis autoregistrar
     * should leave it alone.
     */
    private boolean staticEntry = true;


    /**
     * any extra store/binder data. used as marker when purging the store
     *
     */
    private boolean marker = false;

    /**
     *  an empty entry
     */
    public ServiceEntry() {
    }


    /**
     *  a full entry
     *
     *@param  uri          uri to use as the key
     *@param  url          url to return
     *@param  scope        scope entry
     *@param  description  description
     */
    public ServiceEntry(String uri, String url,
                        String scope, String description) {
        this.setUri(uri);
        this.setUrl(url);
        this.setScope(scope);
        this.setDescription(description);
    }


    /**
     *  Constructor for the ServiceEntry object
     *
     *@param  uri          uri to use as the key
     *@param  url          url to return
     */
    public ServiceEntry(String uri, String url) {
        this.setUri(uri);
        this.setUrl(url);
        setScope(Const.DEFAULT_SCOPE);
        setDescription("");
    }


    /**
     *  hashcode comes from the URL
     *
     *@return
     */
    public int hashCode() {
        return getUrl().hashCode();
    }


    /**
     *  equality is based on URI and url
     *
     *@param  o
     *@return true of URL and URL equality
     */
    public boolean equals(Object o) {
        ServiceEntry that = ((ServiceEntry) o);
        return this.getUri().equals(that.getUri())
                && this.getUrl().equals(that.getUrl());
    }


    /**
     *  test for a complete match across all fields
     *
     *@param  that object to test against
     *@return
     */
    public boolean matches(ServiceEntry that) {
        return this.equals(that)
                && this.getDescription().equals(that.getDescription())
                && this.getScope().equals(that.getScope());
    }


    /**
     *  uri equality
     *
     *@param  uri
     *@return
     */
    public boolean equalsURI(String uri) {
        return this.getUri().equals(uri);
    }


    /**
     *  url equality
     *
     *@param  url
     *@return
     */
    public boolean equalsURL(String url) {
        return this.getUri().equals(url);
    }


    /**
     *  fill in a response with specifics from this entry
     *
     *@param  response
     */
    public void fillIn(DiscoveryMessage response) {
        response.setUrl(getUrl());
        response.setUri(getUri());
        response.setScope(getScope());
        response.setDescription(getDescription());
    }


    /**
     *  Gets the uri attribute of the ServiceEntry object
     *
     *@return    The uri value
     */
    public String getUri() {
        return uri;
    }


    /**
     *  Sets the uri attribute of the ServiceEntry object
     *
     *@param  uri  The new uri value
     */
    public void setUri(String uri) {
        this.uri = uri;
    }


    /**
     *  Gets the url attribute of the ServiceEntry object
     *
     *@return    The url value
     */
    public String getUrl() {
        return url;
    }


    /**
     *  Sets the url attribute of the ServiceEntry object
     *
     *@param  url  The new url value
     */
    public void setUrl(String url) {
        this.url = url;
    }


    /**
     *  Gets the scope attribute of the ServiceEntry object
     *
     *@return    The scope value
     */
    public String getScope() {
        return scope;
    }


    /**
     *  Sets the scope attribute of the ServiceEntry object
     *
     *@param  scope  The new scope value
     */
    public void setScope(String scope) {
        this.scope = scope;
    }


    /**
     *  Gets the description attribute of the ServiceEntry object
     *
     *@return    The description value
     */
    public String getDescription() {
        return description;
    }


    /**
     *  Sets the description attribute of the ServiceEntry object
     *
     *@param  description  The new description value
     */
    public void setDescription(String description) {
        this.description = description;
    }


    /**
     *  Gets the hitCount attribute of the ServiceEntry object
     *
     *@return    The hitCount value
     */
    public Integer getHitCount() {
        return new Integer(hitCount);
    }


    /**
     *  Sets the hitCount attribute of the ServiceEntry object
     *
     *@param  hitCount  The new hitCount value
     */
    public void setHitCount(Integer hitCount) {
        this.setHitCount(hitCount.intValue());
    }


    /**
     *  Gets the hitCountInt attribute of the ServiceEntry object
     *
     *@return    The hitCountInt value
     */
    public int getHitCountInt() {
        return hitCount;
    }


    /**
     *  Sets the hitCount attribute of the ServiceEntry object
     *
     *@param  hitCount  The new hitCount value
     */
    public void setHitCount(int hitCount) {
        this.hitCount = hitCount;
    }


    /**
     *  inc the hit count by one
     */
    public synchronized void hit() {
        setHitCount(hitCount + 1);
    }

    /**
     * is this a static entry
     * @return
     */
    public boolean isStaticEntry() {
        return staticEntry;
    }

    /**
     * set the static entry flag
     * @param staticEntry
     */
    public void setStaticEntry(boolean staticEntry) {
        this.staticEntry = staticEntry;
    }

    /**
     * get the marker status
     * @return
     */
    public boolean getMarker() {
        return marker;
    }

    /**
     * set the marker status
     * @param marker
     */
    public void setMarker(boolean marker) {
        this.marker = marker;
    }
}

