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

package org.apache.axis.utils;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Array;
import java.beans.PropertyDescriptor;


/**
 *
 * @author Glen Daniels (gdaniels@apache.org)
 */
public class FieldPropertyDescriptor extends BeanPropertyDescriptor {
    private Field field = null;

    /**
      * Construct a BPD with a field
      * Both must be set
      * @param _name is the name of the property
      * @param _field is the name of the public instance field
      */
     public FieldPropertyDescriptor(String _name,
                                   Field _field) {
         field = _field;
         try {
             myPD = new PropertyDescriptor(_name, null, null);
         } catch (Exception e) {
             // ???
         }
         if (_field == null || _name == null) {
             throw new IllegalArgumentException(
                     Messages.getMessage(_field == null ?
                                          "badField00" : "badProp03"));
         }
     }

    public String getName() {
        return field.getName();
    }

    /**
     * Query if property is readable
     * @return true if readable
     */
    public boolean isReadable() {
        return true;
    }

    /**
     * Query if property is writeable
     * @return true if writeable
     */
    public boolean isWriteable() {
        return true;
    }

    /**
     * Query if property is indexed.
     * Indexed properties require valid setters/getters
     * @return true if indexed methods exist
     */
    public boolean isIndexed() {
        return (field.getType().getComponentType() != null);
    }

    /**
     * Get the property value
     * @param obj is the object
     * @return the entire propery value
     */
    public Object get(Object obj)
            throws InvocationTargetException, IllegalAccessException {
        return field.get(obj);
    }

    /**
     * Set the property value
     * @param obj is the object
     * @param newValue is the new value
     */
    public void set(Object obj, Object newValue)
            throws InvocationTargetException, IllegalAccessException {
        field.set(obj, newValue);
    }

    /**
     * Get an indexed property
     * @param obj is the object
     * @param i the index
     * @return the object at the indicated index
     */
    public Object get(Object obj, int i)
            throws InvocationTargetException, IllegalAccessException {
        if (!isIndexed()) {
            throw new IllegalAccessException("Not an indexed property");
        }

        Object array = field.get(obj);
        return Array.get(array, i);
    }

    /**
     * Set an indexed property value
     * @param obj is the object
     * @param i the index
     * @param newValue is the new value
     */
    public void set(Object obj, int i, Object newValue)
            throws InvocationTargetException, IllegalAccessException {
        if (!isIndexed()) {
            throw new IllegalAccessException("Not an indexed field!");
        }
        Class componentType = field.getType().getComponentType();
        growArrayToSize(obj, componentType, i);
        Array.set(get(obj), i, newValue);
    }

    /**
     * Get the type of a property
     * @return the type of the property
     */
    public Class getType() {
        if (isIndexed()) {
            return field.getType().getComponentType();
        } else {
            return field.getType();
        }
    }
}
