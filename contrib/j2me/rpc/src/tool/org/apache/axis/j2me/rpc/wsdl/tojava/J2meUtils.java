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

package org.apache.axis.j2me.rpc.wsdl.tojava;

import java.util.HashMap;

import org.apache.axis.wsdl.symbolTable.Utils;
import org.w3c.dom.Node;

/**
 * This class provides several useful methods for classes 
 * in org.apache.axis.j2me.rpc.wsdl.tojava package
 * 
 * @author Ias (iasandcb@tmax.co.kr)
 * 
 */
public class J2meUtils {
    private static HashMap SIMPLE_TYPES = new HashMap(7);

    static {
        SIMPLE_TYPES.put("int", "INT");
        SIMPLE_TYPES.put("float", "FLOAT");
        SIMPLE_TYPES.put("boolean", "BOOLEAN");
        SIMPLE_TYPES.put("double", "DOUBLE");
        SIMPLE_TYPES.put("byte", "BYTE");
        SIMPLE_TYPES.put("short", "SHORT");
        SIMPLE_TYPES.put("long", "LONG");
        SIMPLE_TYPES.put("java.lang.String", "STRING");
    }

    /**
     * checks out whether a given java type is simple type in J2ME JAX-RPC
     * @param javaType
     * @return a boolean value indicating the result 
     */
    public static boolean isSimpleType(String javaType) {
        String simpleType = (String) SIMPLE_TYPES.get(javaType);
        return simpleType != null;
    }

    /**
     * gets a simple type in J2ME JAX-RPC for a java type
     * @param javaType
     * @return a String value indicating the result 
     */
    public static String getSimpleType(String javaType) {
        String simpleType = (String) SIMPLE_TYPES.get(javaType);
        return simpleType == null ? javaType : simpleType; 
    }

    /**
     * gets minOccurs attribute value of a given node
     * @param node
     * @return a String value indicating the result 
     */
    public static String getMinOccurs(Node node) {
            String minOccurs = Utils.getAttribute(node,
                    "minOccurs");
        return minOccurs == null ? "1" : minOccurs;
    }

    /**
     * gets maxOccurs attribute value of a given node
     * @param node
     * @return a String value indicating the result 
     */
    public static String getMaxOccurs(Node node) {
            String maxOccurs = Utils.getAttribute(node,
                    "maxOccurs");
        return maxOccurs.equals("unbounded") ?
            "javax.microedition.xml.rpc.Element.UNBOUNDED" :
            maxOccurs;
    }
}
