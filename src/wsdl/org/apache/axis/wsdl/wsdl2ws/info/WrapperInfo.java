/*
 *   Copyright 2003-2004 The Apache Software Foundation.
// (c) Copyright IBM Corp. 2004, 2005 All Rights Reserved
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * This Class have the misc infomation about the Wrapper to genatrated
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */

package org.apache.axis.wsdl.wsdl2ws.info;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

public class WrapperInfo
{
    //service style
    private String wrapperStyle;
    
    // programming language
    private String wrapperLanguage;

    //server side or client side
    private String targetEngine;
    
    //output location
    private String targetOutputLocation;
    
    //transport method specified in the binding
    private String transportUri;
    
    //target endpoint (the URI the service is deployed in)
    private String targetEndpointURI;
    
    //private target name space of the wsdl file 
    private String targetNameSpaceOfWSDL;

    public WrapperInfo(String wrapperStyle, 
                       String wrapperLanguage,
                       String targetOutputLocation,
                       String targetEngine,
                       String transportUri,
                       String targetEndpointURI,
                       String targetNameSpaceOfWSDL)
    {
        this.wrapperStyle = wrapperStyle;
        this.wrapperLanguage = wrapperLanguage;
        this.targetOutputLocation = targetOutputLocation;

        //validate the data
        if (this.wrapperLanguage == null)
            this.wrapperLanguage = WrapperConstants.LANGUAGE_CPP;
        else
            this.wrapperLanguage = wrapperLanguage.toLowerCase();
        
        if (this.wrapperStyle == null
                || this.wrapperStyle.toLowerCase().equals(WrapperConstants.STYLE_RPC))
            this.wrapperStyle = WrapperConstants.STYLE_RPC;
        else
            this.wrapperStyle = this.wrapperStyle.toLowerCase();

        if (targetOutputLocation == null)
            targetOutputLocation = ".";

        if (targetEngine == null
                || !WrapperConstants.CLIENT.equalsIgnoreCase(targetEngine))
            this.targetEngine = WrapperConstants.SERVER;
        else
            this.targetEngine = WrapperConstants.CLIENT;

        if (transportUri == null)
            this.transportUri = WrapperConstants.TRANSPORT_HTTP;
        else
            this.transportUri = transportUri;

        if (targetEndpointURI == null)
            this.targetEndpointURI = WrapperConstants.DEFAULT_TARGET_ENDPOINT_URI;
        else
            this.targetEndpointURI = targetEndpointURI;

        this.targetNameSpaceOfWSDL = (targetNameSpaceOfWSDL == null) ? "" : targetNameSpaceOfWSDL;
    }

    /**
     * @return int
     */
    public String getWrapperLanguage()
    {
        return wrapperLanguage;
    }

    /**
     * @return int
     */
    public String getWrapperStyle()
    {
        return wrapperStyle;
    }

    /**
     * Sets the wrapperLanguage.
     * @param wrapperLanguage The wrapperLanguage to set
     */
    public void setWrapperLanguage(String wrapperLanguage)
    {
        this.wrapperLanguage = wrapperLanguage;
    }

    /**
     * Sets the wrapperStyle.
     * @param wrapperStyle The wrapperStyle to set
     */
    public void setWrapperStyle(String wrapperStyle)
    {
        this.wrapperStyle = wrapperStyle;
    }

    /**
     * @return String
     */
    public String getTargetOutputLocation()
    {
        return targetOutputLocation;
    }

    /**
     * @return String
     */

    public String getTargetEngine()
    {
        return targetEngine;
    }

    public void setTargetEngine(String targetEngine)
    {
        this.targetEngine = targetEngine;
    }
    /**
     * @return String
     */
    public String getTargetEndpointURI()
    {
        return targetEndpointURI;
    }
    /**
     * @return String
     */
    public String getTargetNameSpaceOfWSDL()
    {
        return targetNameSpaceOfWSDL;
    }

    /**
     * @return String
     */
    public String getTransportUri()
    {
        return transportUri;
    }

}
