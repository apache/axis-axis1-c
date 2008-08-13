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

package org.apache.axis.wsdl.wsdl2ws.info;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;

/**
 * Contains information of a global nature regarding how to generate
 * the stubs.
 * 
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
public class WrapperInfo
{
    // binding style
    private String c_bindingStyle;
    
    // programming language
    private String c_wrapperLanguage;

    // server side or client side
    private String c_targetEngine;
    
    // output location
    private String c_targetOutputLocation;
    
    // private target name space of the wsdl file 
    private String c_targetNameSpaceOfWSDL;

    /**
     * Constructor 
     * 
     * @param style                 binding style (e.g. "rpc", "document").
     * @param wrapperLanguage       what language to generate (e.g. "c", "c++").
     * @param targetOutputLocation  where stubs will be generated.
     * @param targetEngine          generate "client" or "server" stubs?
     * @param targetNameSpaceOfWSDL target name space of WSDL.
     */
    public WrapperInfo(String style, 
                       String wrapperLanguage,
                       String targetOutputLocation,
                       String targetEngine,
                       String targetNameSpaceOfWSDL)
    {
        c_bindingStyle = style;
        c_wrapperLanguage = wrapperLanguage;
        c_targetOutputLocation = targetOutputLocation;

        // validate the data
        if (c_wrapperLanguage == null)
            c_wrapperLanguage = WrapperConstants.LANGUAGE_CPP;
        else
            c_wrapperLanguage = wrapperLanguage.toLowerCase();
        
        if (c_bindingStyle == null
                || c_bindingStyle.toLowerCase().equals(WrapperConstants.STYLE_RPC))
            c_bindingStyle = WrapperConstants.STYLE_RPC;
        else
            c_bindingStyle = c_bindingStyle.toLowerCase();

        if (targetOutputLocation == null)
            targetOutputLocation = ".";

        if (targetEngine == null
                || !WrapperConstants.CLIENT.equalsIgnoreCase(targetEngine))
            c_targetEngine = WrapperConstants.SERVER;
        else
            c_targetEngine = WrapperConstants.CLIENT;

        c_targetNameSpaceOfWSDL = (targetNameSpaceOfWSDL == null) ? "" : targetNameSpaceOfWSDL;
    }

    /**
     * Returns the programming language to use when generating stubs.
     * 
     * @return String representing programming language (e.g. "c", "c++").  
     */
    public String getWrapperLanguage()
    {
        return c_wrapperLanguage;
    }

    /**
     * Returns the binding style that will be used when generated the stubs.
     * 
     * @return String representing the binding style (e.g. "rpc", "document").
     */
    public String getBindingStyle()
    {
        return c_bindingStyle;
    }

    /**
     * Returns the location in which the stub code will be located.
     * 
     * @return String
     */
    public String getTargetOutputLocation()
    {
        return c_targetOutputLocation;
    }

    /**
     * Returns whether server or client artifacts are to be produced.
     * 
     * @return String
     */
    public String getTargetEngine()
    {
        return c_targetEngine;
    }

    /**
     * Returns the target name space of WSDL.
     * 
     * @return String
     */
    public String getTargetNameSpaceOfWSDL()
    {
        return c_targetNameSpaceOfWSDL;
    }
}
