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

package org.apache.axis.encoding;

import org.apache.axis.Constants;

import javax.xml.rpc.namespace.QName;
import javax.xml.rpc.JAXRPCException;

import java.util.ArrayList;
import java.util.HashMap;

/**
 * @author Rich Scheuerle (scheu@us.ibm.com)
 * 
 * This is the implementation of the axis TypeMapping interface (which extends
 * the JAX-RPC TypeMapping interface).
 * 
 * A TypeMapping is obtained from the singleton TypeMappingRegistry using
 * the namespace of the webservice.  The TypeMapping contains the tuples
 * {Java type, SerializerFactory, DeserializerFactory, Type QName)
 *
 * So if you have a Web Service with the namespace "XYZ", you call 
 * the TypeMappingRegistry.getTypeMapping("XYZ").
 *
 * The wsdl in your web service will use a number of types.  The tuple
 * information for each of these will be accessed via the TypeMapping.
 *
 * Because every web service uses the soap, schema, wsdl primitives, we could 
 * pre-populate the TypeMapping with these standard tuples.  Instead, if requested
 * namespace/class matches is not found in the TypeMapping but matches one these
 * known primitives, the request is delegated to the Default TypeMapping.
 * 
 */
public class TypeMappingImpl implements TypeMapping { 

    public class Pair {
        public Class javaType;
        public QName xmlType;
        public Pair(Class javaType, QName xmlType) {
            this.javaType = javaType;
            this.xmlType = xmlType;
        }
        public boolean equals(Object o) {
            Pair p = (Pair) o;
            return (p.xmlType.equals(this.xmlType) && p.javaType.equals(this.javaType));
        }
        public int hashCode() {
            return javaType.hashCode();
        }
    }

    private HashMap qName2Pair;     // QName to Pair Mapping                              
    private HashMap class2Pair;     // Class Name to Pair Mapping                           
    private HashMap pair2SF;        // Pair to Serialization Factory
    private HashMap pair2DF;        // Pair to Deserialization Factory
    private TypeMappingRegistry tmr;  // Back pointer to owning TMR
    protected boolean delegateIfNotFound; // Indicates to delegate to Default if not found
    private ArrayList namespaces;   // Supported namespaces

    /**
     * Construct TypeMapping
     */
    public TypeMappingImpl(TypeMappingRegistry tmr) {
        this.tmr = tmr;
        qName2Pair  = new HashMap();
        class2Pair  = new HashMap();
        pair2SF     = new HashMap();
        pair2DF     = new HashMap();
        delegateIfNotFound = true;
        namespaces  = new ArrayList();
    }
    
    /********* JAX-RPC Compliant Method Definitions *****************/
    
    /**
     * Gets the list of encoding styles supported by this TypeMapping object.
     *
     * @return  String[] of namespace URIs for the supported encoding 
     * styles and XML schema namespaces.
     */
    public String[] getSupportedEncodings() {
        return (String[]) namespaces.toArray();
    }

    /**
     * Sets the list of encoding styles supported by this TypeMapping object.
     * (Not sure why this is useful...this information is automatically updated
     * during registration.
     *
     * @param namespaceURIs String[] of namespace URI's                
     */
    public void setSupportedEncodings(String[] namespaceURIs) {
        namespaces.clear();
        for (int i =0; i< namespaceURIs.length; i++) {
            if (!namespaces.contains(namespaceURIs[i])) {
                namespaces.add(namespaceURIs[i]);
            }
        }
    }
    
    /**
     * Registers SerializerFactory and DeserializerFactory for a 
     * specific type mapping between an XML type and Java type.
     *
     * @param javaType - Class of the Java type
     * @param xmlType - Qualified name of the XML data type
     * @param sf - SerializerFactory
     * @param dsf - DeserializerFactory
     *
     * @throws JAXRPCException - If any error during the registration
     */
    public void register(Class javaType, QName xmlType, 
                         javax.xml.rpc.encoding.SerializerFactory sf,
                         javax.xml.rpc.encoding.DeserializerFactory dsf) throws JAXRPCException {        
        if (xmlType.getNamespaceURI() == null ||
            xmlType.getNamespaceURI().equals("") ||
            javaType == null ||
            xmlType == null) {
            throw new JAXRPCException();
        }
        // Make sure the factories conform to the Axis interfaces
        if (sf != null &&
            !(sf instanceof SerializerFactory)) {
            throw new JAXRPCException();
        }
        if (dsf != null &&
            !(dsf instanceof DeserializerFactory)) {
            throw new JAXRPCException();
        }
        Pair pair = new Pair(javaType, xmlType);

        qName2Pair.put(xmlType, pair);
        class2Pair.put(javaType, pair);   
        pair2SF.put(pair, sf);
        pair2DF.put(pair, dsf);
    }
    
    /**
     * Gets the SerializerFactory registered for the specified pair
     * of Java type and XML data type.
     *
     * @param javaType - Class of the Java type
     * @param xmlType - Qualified name of the XML data type
     *
     * @return Registered SerializerFactory
     *
     * @throws JAXRPCException - If there is no registered SerializerFactory 
     * for this pair of Java type and XML data type 
     * java.lang.IllegalArgumentException - If invalid or unsupported XML/Java type is specified
     */
    public javax.xml.rpc.encoding.SerializerFactory getSerializer(Class javaType, QName xmlType)
        throws JAXRPCException
    {
        SerializerFactory sf = null;
        // Try to get the serializer associated with this pair
        Pair pair = new Pair(javaType, xmlType);

        // If the xmlType was not provided, get one
        if (xmlType == null) {
            pair.xmlType = getTypeQName(javaType);
        }
        // Now get the serializer with the pair
        if (pair.xmlType != null) {
            sf = (SerializerFactory) pair2SF.get(pair);
            // If not successful, use the xmlType to get
            // another pair.  For some xmlTypes (like SOAP_ARRAY)
            // all of the possible javaTypes are not registered.
            if (sf == null) {
                pair = (Pair) qName2Pair.get(pair.xmlType);
                if (pair != null) {
                    sf = (SerializerFactory) pair2SF.get(pair);
                }
            }
        }
        if (sf == null && delegateIfNotFound) {
            TypeMapping defaultTM = (TypeMapping) tmr.getDefaultTypeMapping();
            if (defaultTM != null) {
                sf = (SerializerFactory) defaultTM.getSerializer(javaType, xmlType);
            }
        }
        return sf;
    }
    public javax.xml.rpc.encoding.SerializerFactory getSerializer(Class javaType) 
        throws JAXRPCException 
    {
        return getSerializer(javaType, null);
    }

    /**
     * Gets the DeserializerFactory registered for the specified pair 
     * of Java type and XML data type.
     *
     * @param javaType - Class of the Java type
     * @param xmlType - Qualified name of the XML data type
     *
     * @return Registered DeserializerFactory
     *
     * @throws JAXRPCException - If there is no registered DeserializerFactory
     * for this pair of Java type and  XML data type 
     * java.lang.IllegalArgumentException - If invalid or unsupported XML/Java type is specified
     */
    public javax.xml.rpc.encoding.DeserializerFactory getDeserializer(Class javaType, QName xmlType)
        throws JAXRPCException {
        DeserializerFactory df = null;
        Pair pair = new Pair(javaType, xmlType);
        if (javaType == null) {
            pair.javaType = getClassForQName(xmlType);
        }
        if (pair.javaType != null) {
            df = (DeserializerFactory) pair2DF.get(pair);
        } 
        if (df == null && delegateIfNotFound) {
            TypeMapping defaultTM = (TypeMapping) tmr.getDefaultTypeMapping();
            if (defaultTM != null) {
                df = (DeserializerFactory) defaultTM.getDeserializer(javaType, xmlType);
            }
        }
        return df;
    }
    public javax.xml.rpc.encoding.DeserializerFactory getDeserializer(QName xmlType)
        throws JAXRPCException {
        return getDeserializer(null, xmlType);
    }

    /**
     * Removes the SerializerFactory registered for the specified 
     * pair of Java type and XML data type.
     *
     * @param javaType - Class of the Java type
     * @param xmlType - Qualified name of the XML data type
     *
     * @throws JAXRPCException - If there is error in removing the registered SerializerFactory 
     * java.lang.IllegalArgumentException - If invalid or unsupported XML/Java type is specified
     */
    public void removeSerializer(Class javaType, QName xmlType)
        throws JAXRPCException {
        Pair pair = new Pair(javaType, xmlType);
        pair2SF.remove(pair);
    }

    /**
     * Removes the DeserializerFactory registered for the specified 
     * pair of Java type and XML data type.
     *
     * @param javaType - Class of the Java type
     * @param xmlType - Qualified name of the XML data type
     *
     * @throws JAXRPCException - If there is error in removing the registered DeserializerFactory
     * java.lang.IllegalArgumentException - If invalid or unsupported XML/Java type is specified
     */
    public void removeDeserializer(Class javaType, QName xmlType)
        throws JAXRPCException {
        Pair pair = new Pair(javaType, xmlType);
        pair2DF.remove(pair);
    }


     /********* End JAX-RPC Compliant Method Definitions *****************/
     
    /**
     * Gets the QName for the type mapped to Class.
     * @param javaType class or type
     * @return xmlType qname or null
     */
    public QName getTypeQName(Class javaType) {
        //System.out.println("getTypeQName javaType =" + javaType);
        QName xmlType = null;
        Pair pair = (Pair) class2Pair.get(javaType);
        if (pair == null && delegateIfNotFound) {
            TypeMapping defaultTM = (TypeMapping) tmr.getDefaultTypeMapping();
            if (defaultTM != null) {
                xmlType = defaultTM.getTypeQName(javaType);
            }
        } else if (pair != null) {
            xmlType = pair.xmlType;
        }
        
        //System.out.println("getTypeQName xmlType =" + xmlType);
        return xmlType;
    }
    
    /**
     * Gets the Class mapped to QName.
     * @param xmlType qname or null
     * @return javaType class or type
     */
    public Class getClassForQName(QName xmlType) {
        //System.out.println("getClassForQName xmlType =" + xmlType);
        Class javaType = null;
        Pair pair = (Pair) qName2Pair.get(xmlType);
        if (pair == null && delegateIfNotFound) {
            TypeMapping defaultTM = (TypeMapping) tmr.getDefaultTypeMapping();
            if (defaultTM != null) {
                javaType = defaultTM.getClassForQName(xmlType);
            }
        } else if (pair != null) {
            javaType = pair.javaType;
        }

        //System.out.println("getClassForQName javaType =" + javaType);
        return javaType;
    }
}
