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
 * This class have the info about the class that is going to be published as WS.
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.ArrayList;

import org.apache.axis.wsdl.wsdl2ws.WrapperConstants;
import org.apache.axis.wsdl.wsdl2ws.WrapperFault;

public class ServiceInfo
{
    private String c_servicename;
    private ArrayList c_methods;
    private String c_targetEndpointURI;

    public ServiceInfo(String servicename, 
                       ArrayList methods,
                       String targetEndpointURI)
        throws WrapperFault
    {
        c_methods = methods;
        c_servicename = servicename;

        //validate the information
        if (servicename == null)
            throw new WrapperFault("Service name can't be null.");

        if (c_methods == null || c_methods.size() == 0)
            throw new WrapperFault("Service with no methods.");
        
        if (targetEndpointURI == null)
            c_targetEndpointURI = WrapperConstants.DEFAULT_TARGET_ENDPOINT_URI;
        else
            c_targetEndpointURI = targetEndpointURI;
    }

    /**
     * @return String[]
     */
    public ArrayList getMethods()
    {
        return c_methods;
    }

    /**
     * @return String
     */
    public String getServicename()
    {
        return c_servicename;
    }
    
    /**
     * @return String
     */
    public String getTargetEndpointURI()
    {
        return c_targetEndpointURI;
    }
}