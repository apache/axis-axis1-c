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
 *    Apache Software Foundation (http://www.apache.org/)."
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

package org.apache.axismora.wsdl2ws;

public interface WrapperConstants {
    public static final String DEFAULT_SIMPLETYPE_PACKAGE =
        "org.apache.axismora.wrappers.simpleType.";
    public static final String SCHEMA_NAMESPACE = "http://www.w3.org/2001/XMLSchema";
    public static final String SOAPENC_NAMESPACE =
        "http://schemas.xmlsoap.org/soap/encoding/";
    //wsdl constants
    public static final String ELEMENT_COMPLEX_TYPE = "ComplexType";
    public static final String ELEMENT_SEQUENCE = "sequence";
    public static final String ELEMENT_ALL = "all";
    public static final String ELEMENT_ELEMENT = "element";

    public static final String ATTRIBUTE_NAME = "name";
    public static final String ATTRIBUTE_TYPE = "type";
    //parameter type
    public static final int INPUT_PARM = 0;
    public static final int RETURN_PARM = 1;
    public static final int COMMAN_PARM = 2;
    //language
    public static final String LANGUAGE_JAVA = "java";
    public static final String LANGUAGE_CPP = "c++";
    public static final String LANGUAGE_C = "c";
    //service style 
    public static final String STYLE_RPC = "rpc";
    public static final String STYLE_DOCUMENT = "document";
    public static final String STYLE_WRAPPED = "wrapped";
    public static final String STYLE_MESSAGE = "message";

    public static final String ENCODING_STYLE_SOAP =
        "http://schemas.xmlsoap.org/soap/encoding/";

    public static final String TRANSPORT_HTTP = "http://schemas.xmlsoap.org/soap/http";

    public static final String DEFAULT_TARGET_ENDPOINT_URI = "http//127.0.0.1/8080";
    //wrapper genarator type
    //java constants
    public static final int GENERATOR_WRAPPER_JAVA = 9;
    public static final int GENERATOR_CLIENT_WRAPPER_JAVA = 10;
    public static final int GENERATOR_PARAM_JAVA = 11;
    public static final int GENERATOR_SERVICE_JAVA = 12;
    public static final int GENERATOR_STUB_LOCATOR_JAVA = 28;
    public static final int GENERATOR_STUB_JAVA = 29;
    public static final int GENERATOR_STUB_SERVICE_INTERFACE_JAVA = 30;

    //cpp constants 
    public static final int GENERATOR_CLASSLOADER_CPP = 13;
    public static final int GENERATOR_WRAPPER_CPP = 14;
    public static final int GENERATOR_CLIENT_WRAPPER_CPP = 15;
    public static final int GENERATOR_SERVICE_CPP = 17;
    public static final int GENERATOR_WRAPPER_HPP = 18;
    public static final int GENERATOR_CLIENT_WRAPPER_HPP = 19;
    public static final int GENERATOR_PARAM_CPP_ALL = 20;
    public static final int GENERATOR_SERVICE_HPP = 21;
    //c constants 
    public static final int GENERATOR_WRAPPER_C = 22;
    public static final int GENERATOR_CLIENT_WRAPPER_C = 23;
    public static final int GENERATOR_SERVICE_C = 24;
    public static final int GENERATOR_WRAPPER_H = 25;
    public static final int GENERATOR_CLIENT_WRAPPER_H = 26;
    public static final int GENERATOR_PARAM_C_ALL = 27;
    public static final int MSG_GENERATOR_WRAPPER = 31;
    public static final int MSG_GENERATOR_SERVICE = 32;

    public static final int GENERATOR_DEPLOYMENT_DISCRIPTOR = 33;
    public static final int GENERATOR_UNDEPLOYMENT_DISCRIPTOR = 34;

    //implementation type
    public static final String IMPL_STYLE_STRUCT = "struct";
    public static final String IMPL_STYLE_VALUEORDER = "order";
    public static final String IMPL_STYLE_SIMPLE = "simple";

    //target engine
    public static final String SERVER = "server";
    public static final String CLIENT = "client";
    public static final String SERVER_CLIENT = "both";

    public static final String SOAPENC_ARRAY = "Array";
}
