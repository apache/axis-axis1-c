/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights 
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

package org.apache.axis.utils.cache;

import java.lang.reflect.Method;
import java.util.Hashtable;

/**
 * A simple cache of previously loaded classes, and their methods.
 *
 * @author Sam Ruby <rubys@us.ibm.com>
 */
public class JavaClass {

    private static Hashtable classes = new Hashtable();
    private Hashtable methods = new Hashtable();

    private Class jc;

    /**
     * Find (or create if necessary) a JavaClass associated with a given
     * class
     */
    public static synchronized JavaClass find(Class jc) {
        JavaClass result = (JavaClass) classes.get(jc);

        if (result == null) {
            result = new JavaClass(jc);
            classes.put(jc, result);
        }

        return result;
    }

    /**
     * Create a cache entry for this java.lang.Class
     */
    public JavaClass(Class jc) {
        this.jc = jc;
        classes.put(jc, this);
    }
    
    /**
     * Return the java.lang.Class associated with this entry
     */
    public Class getJavaClass() {
        return jc;
    }

    /**
     * Lookup a method based on name.  This method returns an array just in
     * case there is more than one.
     * @param name name of method
     */
    public Method[] getMethod(String name) {
        JavaMethod jm = (JavaMethod) methods.get(name);

        if (jm == null) {
            methods.put(name, jm=new JavaMethod(jc, name));
        }

        return jm.getMethod();
    }
};
