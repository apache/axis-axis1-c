/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2001-2004 The Apache Software Foundation.  All rights
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

package org.apache.geronimo.ews.ws4j2ee.toWs;

/**
 * <p>This interface has constants that are specific to the generators.</p>
 */
public interface GenerationConstants {
    //generators
    public static final int EJB_GENERATOR = 0;
    public static final int AXIS_WEBSERVICE_WRAPPER_GENERATOR = 1;
    public static final int WSDL_GENERATOR = 2;
    public static final int CLIENT_STUB_GENERATOR = 3;
    public static final int SEI_AND_TYPES_GENERATOR = 4;
    public static final int HANDLER_GENERATOR = 13;
    public static final int JAXRPCMAPPER_GENERATOR = 14;
    public static final int WEBSERVICEDD_GENERATOR = 15;
    public static final int J2EE_CONTAINER_DD_GENERATOR = 16;
    public static final int BUILD_FILE_GENERATOR = 17;

    //writers
    public static final int EJB_REMOTE_INTERFACE_WRITER = 5;
    public static final int EJB_HOME_INTERFACE_WRITER = 6;
    public static final int EJB_IMPLEMENTATION_BEAN_WRITER = 7;
    public static final int EJB_DD_WRITER = 8;
    public static final int AXIS_WEBSERVICE_WRAPPER_WRITER = 9;
    public static final int AXIS_WEBSERVICE_WRAPPER_DEPLOYMENT_FILE_WRITER = 10;
    public static final int WSDL_FILE_WRITER = 11;
    public static final int SEI_FILE_WRITER = 12;

    public static final String OPTION_WS4J2EE_PROPERTY_FILE = "ws4j2ee.ConfigFile";

    //more to come
    public static final String J2EE_CONTAINER_DD = "j2ee-container-dd";
    public static final String WS4J2EE_PROPERTY_FILE = "ws4j2ee.properties";

    public static final String JBOSS_DD = "jboss.xml";
    public static final String JONAS_DD = "jonas-ejb-jar.xml";
    public static final String GERONIMO_DD = "geronimo.xml";
}
