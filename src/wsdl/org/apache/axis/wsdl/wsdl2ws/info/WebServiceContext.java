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

import java.util.HashSet;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;

/**
 * This class has all the information needed to generate the stubs representing 
 * Web services.   
 *  
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
public class WebServiceContext
{
    private WrapperInfo wrapInfo;
    private ServiceInfo serInfo;
    private TypeMap typemap;

    private HashSet generatedFileList = new HashSet();

    /**
     * Constructor. 
     * 
     * @param wrapInfo
     * @param serInfo
     * @param typemap
     * @throws WrapperFault
     */
    public WebServiceContext(WrapperInfo wrapInfo, 
                             ServiceInfo serInfo,
                             TypeMap typemap) throws WrapperFault
    {
        this.wrapInfo = wrapInfo;
        this.serInfo = serInfo;
        this.typemap = typemap;

        if (wrapInfo == null || this.serInfo == null || this.typemap == null)
        {
            throw new WrapperFault("Insufficient Info");
        }
    }

    /**
     * Returns ServiceInfo object. 
     * 
     * @return ServiceInfo
     */
    public ServiceInfo getServiceInfo()
    {
        return serInfo;
    }

    /**
     * Adds a name of the generated file 
     * 
     * @param filename
     */
    public void addGeneratedFile(String filename)
    {
        generatedFileList.add(filename);
    }

    /**
     * Returns set of all files that have been generated.
     * 
     * @return Set of strings representing file names.
     */
    public HashSet getGeneratedFileList()
    {
        return generatedFileList;
    }
    
    /**
     * Returns the map the contains the types to be generated.
     * 
     * @return TypeMap
     */
    public TypeMap getTypemap()
    {
        return typemap;
    }

    /**
     * Returns the WrapperInfo object. 
     * 
     * @return WrapperInfo
     */
    public WrapperInfo getWrapperInfo()
    {
        return wrapInfo;
    }

}
