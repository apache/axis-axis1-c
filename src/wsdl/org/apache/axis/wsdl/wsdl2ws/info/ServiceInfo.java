/*
 *   Copyright 2003-2004 The Apache Software Foundation.
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

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;

public class ServiceInfo
{
    private String servicename;
    private String qualifiedServiceName;
    private ArrayList methods;
    private String[][] parameters;

    public ServiceInfo(
        String servicename,
        String qualifiedServiceName,
        ArrayList methods)
        throws WrapperFault
    {
        this.methods = methods;
        this.qualifiedServiceName = qualifiedServiceName;
        this.servicename = servicename;

        //validate the infomormation
        if (this.qualifiedServiceName == null)
        {
            throw new WrapperFault("The fully qualified parameter name can't be null");
        }
        if (servicename == null)
        {
            servicename =
                WrapperUtils.getClassNameFromFullyQualifiedName(
                    qualifiedServiceName);
        }
        if (this.methods == null || this.methods.size() == 0)
        {
            throw new WrapperFault("service with no methods no point writing a wrapper");
        }
        if (this.parameters == null)
        {
            this.parameters = new String[0][0];
        }

    }

    /**
     * @return String[]
     */
    public ArrayList getMethods()
    {
        return methods;
    }

    public String getQualifiedServiceName()
    {
        return qualifiedServiceName;
    }

    /**
     * @return String
     */
    public String getServicename()
    {
        return servicename;
    }
}
