/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2003 The Apache Software Foundation.  All rights
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

package org.apache.axis.j2me.xml;

import java.util.Hashtable;

/**
 * This entity resolver is mainly used by NonValidatingParser
 * @author Ias (iasandcb@tmax.co.kr)
 *  
 */
public class EntityResolver {
    /**
	 * The registered entities.
	 */
    private Hashtable entities;

    /**
	 * Initializes the resolver.
	 */
    public EntityResolver() {
        this.entities = new Hashtable();
        this.entities.put("amp", "&#38;");
        this.entities.put("quot", "&#34;");
        this.entities.put("apos", "&#39;");
        this.entities.put("lt", "&#60;");
        this.entities.put("gt", "&#62;");
    }

    /**
	 * Adds an internal entity.
	 * 
	 * @param name - the name of the entity.
	 * @param value - the value of the entity.
	 */
    public void addInternalEntity(String name, String value) {
        if (!this.entities.containsKey(name)) {
            this.entities.put(name, value);
        }
    }

    /**
	 * Adds an external entity.
	 * 
	 * @param name - the name of the entity.
	 * @param publicID - the public ID of the entity, which may be null.
	 * @param systemID - the system ID of the entity.
	 */
    public void addExternalEntity(String name, String publicID, String systemID) {
        if (!this.entities.containsKey(name)) {
            this.entities.put(name, new String[] { publicID, systemID });
        }
    }

    /**
	 * Returns a Java reader containing the value of an entity.
	 * 
	 * @param xmlReader
	 *            the current XML reader
	 * @param name
	 *            the name of the entity.
	 * 
	 * @return the reader, or null if the entity could not be resolved.
	 */
    public Object getEntity(String name) {
        Object obj = this.entities.get(name);

        if (obj == null) {
            return null;
        }
        else if (obj instanceof java.lang.String) {
            return (String) obj;
        }
        else {
            String[] id = (String[]) obj;
            return id;
        }
    }

    /**
	 * Returns true if an entity is external.
	 * 
	 * @param name
	 *            the name of the entity.
	 */
    public boolean isExternalEntity(String name) {
        Object obj = this.entities.get(name);
        return !(obj instanceof java.lang.String);
    }

}
