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
package javax.xml.rpc.encoding;

import javax.xml.namespace.QName;

/**
 * Class XMLType
 *
 * @version 1.0
 */
public class XMLType {

    /**
     * Constructor XMLType
     */
    public XMLType() {}

    /** Field XSD_STRING           */
    public static final QName XSD_STRING =
        new QName("http://www.w3.org/2001/XMLSchema", "string");

    /** Field XSD_FLOAT           */
    public static final QName XSD_FLOAT =
        new QName("http://www.w3.org/2001/XMLSchema", "float");

    /** Field XSD_BOOLEAN           */
    public static final QName XSD_BOOLEAN =
        new QName("http://www.w3.org/2001/XMLSchema", "boolean");

    /** Field XSD_DOUBLE           */
    public static final QName XSD_DOUBLE =
        new QName("http://www.w3.org/2001/XMLSchema", "double");

    /** Field XSD_INTEGER           */
    public static final QName XSD_INTEGER =
        new QName("http://www.w3.org/2001/XMLSchema", "integer");

    /** Field XSD_INT           */
    public static final QName XSD_INT =
        new QName("http://www.w3.org/2001/XMLSchema", "int");

    /** Field XSD_LONG           */
    public static final QName XSD_LONG =
        new QName("http://www.w3.org/2001/XMLSchema", "long");

    /** Field XSD_SHORT           */
    public static final QName XSD_SHORT =
        new QName("http://www.w3.org/2001/XMLSchema", "short");

    /** Field XSD_DECIMAL           */
    public static final QName XSD_DECIMAL =
        new QName("http://www.w3.org/2001/XMLSchema", "decimal");

    /** Field XSD_BASE64           */
    public static final QName XSD_BASE64 =
        new QName("http://www.w3.org/2001/XMLSchema", "base64Binary");

    /** Field XSD_HEXBINARY           */
    public static final QName XSD_HEXBINARY =
        new QName("http://www.w3.org/2001/XMLSchema", "hexBinary");

    /** Field XSD_BYTE           */
    public static final QName XSD_BYTE =
        new QName("http://www.w3.org/2001/XMLSchema", "byte");

    /** Field XSD_DATETIME           */
    public static final QName XSD_DATETIME =
        new QName("http://www.w3.org/2001/XMLSchema", "dateTime");

    /** Field XSD_QNAME           */
    public static final QName XSD_QNAME =
        new QName("http://www.w3.org/2001/XMLSchema", "QName");

    /** Field SOAP_STRING           */
    public static final QName SOAP_STRING =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "string");

    /** Field SOAP_BOOLEAN           */
    public static final QName SOAP_BOOLEAN =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "boolean");

    /** Field SOAP_DOUBLE           */
    public static final QName SOAP_DOUBLE =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "double");

    /** Field SOAP_BASE64           */
    public static final QName SOAP_BASE64 =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "base64");

    /** Field SOAP_FLOAT           */
    public static final QName SOAP_FLOAT =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "float");

    /** Field SOAP_INT           */
    public static final QName SOAP_INT =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "int");

    /** Field SOAP_LONG           */
    public static final QName SOAP_LONG =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "long");

    /** Field SOAP_SHORT           */
    public static final QName SOAP_SHORT =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "short");

    /** Field SOAP_BYTE           */
    public static final QName SOAP_BYTE =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "byte");

    /** Field SOAP_ARRAY           */
    public static final QName SOAP_ARRAY =
        new QName("http://schemas.xmlsoap.org/soap/encoding/", "Array");
}

