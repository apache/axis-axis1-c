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

package org.apache.axismora.wsdl2ws.info;

import org.apache.axismora.wsdl2ws.WrapperConstants;

/**
 * This Class have the misc infomation about the Wrapper to genatrated
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
public class WrapperInfo {
    //service style
    private String wrapperStyle;
    // programming language
    private String wrapperLanguage;
    //encoding style
    private String encodingStyle;
    // use getvalue or get TAG or SIMPlE
    private String implStyle;
    //serverside or client side
    private String targetEngine;
    //output location
    private String targetOutputLocation;
    //trasport method specified in the binding
    private String trasportUri;
    //target endpoint (the URI the service is deployed in)
    private String targetEndpointURI;
    //private target name space of the wsdl file 
    private String targetNameSpaceOfWSDL;

    public WrapperInfo(
        String wrapperStyle,
        String wrapperLanguage,
        String encodingStyle,
        String targetOutputLocation,
        String implStyle,
        String targetEngine,
        String trasportUri,
        String targetEndpointURI,
        String targetNameSpaceOfWSDL) {
        this.wrapperStyle = wrapperStyle;
        this.wrapperLanguage = wrapperLanguage;
        this.encodingStyle = encodingStyle;
        this.targetOutputLocation = targetOutputLocation;
        this.implStyle = implStyle;

        //validate the data

        //set "" if the value is null
        this.targetNameSpaceOfWSDL =
            (targetNameSpaceOfWSDL == null) ? "" : targetNameSpaceOfWSDL;
        if (this.wrapperLanguage == null
            || this.wrapperLanguage.toLowerCase().equals(WrapperConstants.LANGUAGE_JAVA))
            this.wrapperLanguage = WrapperConstants.LANGUAGE_JAVA;
        else
            this.wrapperLanguage = wrapperLanguage.toLowerCase();
        if (this.wrapperStyle == null
            || this.wrapperStyle.toLowerCase().equals(WrapperConstants.STYLE_RPC))
            this.wrapperStyle = WrapperConstants.STYLE_RPC;
        else
            this.wrapperStyle = this.wrapperStyle.toLowerCase();

        if (encodingStyle == null
            || encodingStyle.equals(WrapperConstants.ENCODING_STYLE_SOAP))
            this.encodingStyle = WrapperConstants.ENCODING_STYLE_SOAP;
        if (targetOutputLocation == null)
            this.targetOutputLocation = ".";

        if (implStyle == null || implStyle.equals(WrapperConstants.IMPL_STYLE_STRUCT))
            this.implStyle = WrapperConstants.IMPL_STYLE_STRUCT;
        else
            this.implStyle = this.implStyle.toLowerCase();

        if (targetEngine == null
            || WrapperConstants.CLIENT.equalsIgnoreCase(targetEngine))
            this.targetEngine = WrapperConstants.CLIENT;
        else if (WrapperConstants.SERVER.equalsIgnoreCase(targetEngine))
            this.targetEngine = WrapperConstants.SERVER;
        else
            this.targetEngine = WrapperConstants.SERVER_CLIENT;

        if (trasportUri == null)
            this.trasportUri = WrapperConstants.TRANSPORT_HTTP;
        else
            this.trasportUri = trasportUri;

        if (targetEndpointURI == null)
            this.targetEndpointURI = WrapperConstants.DEFAULT_TARGET_ENDPOINT_URI;
        else
            this.targetEndpointURI = targetEndpointURI;
    }

    /**
     * @return int
     */
    public String getWrapperLanguage() {
        return wrapperLanguage;
    }

    /**
     * @return int
     */
    public String getWrapperStyle() {
        return wrapperStyle;
    }

    /**
     * Sets the wrapperLanguage.
     * @param wrapperLanguage The wrapperLanguage to set
     */
    public void setWrapperLanguage(String wrapperLanguage) {
        this.wrapperLanguage = wrapperLanguage;
    }

    /**
     * Sets the wrapperStyle.
     * @param wrapperStyle The wrapperStyle to set
     */
    public void setWrapperStyle(String wrapperStyle) {
        this.wrapperStyle = wrapperStyle;
    }

    /**
     * @return int
     */
    public String getEncodingStyle() {
        return encodingStyle;
    }

    /**
     * Sets the encodingStyle.
     * @param encodingStyle The encodingStyle to set
     */
    public void setEncodingStyle(String encodingStyle) {
        this.encodingStyle = encodingStyle;
    }

    /**
     * @return String
     */
    public String getTargetOutputLocation() {
        return targetOutputLocation;
    }

    /**
     * @return String
     */
    public String getImplStyle() {
        return implStyle;
    }

    /**
     * Sets the implStyle.
     * @param implStyle The implStyle to set
     */
    public void setImplStyle(String implStyle) {
        this.implStyle = implStyle;
    }

    public String getTargetEngine() {
        return targetEngine;
    }

    public void setTargetEngine(String targetEngine) {
        this.targetEngine = targetEngine;
    }

    /**
     * @return String
     */
    public String getTargetEndpointURI() {
        return targetEndpointURI;
    }

    /**
     * @return String
     */
    public String getTargetNameSpaceOfWSDL() {
        return targetNameSpaceOfWSDL;
    }

    /**
     * @return String
     */
    public String getTrasportUri() {
        return trasportUri;
    }

}
