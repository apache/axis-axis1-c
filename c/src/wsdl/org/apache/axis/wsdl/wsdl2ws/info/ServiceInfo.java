/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 2003 The Apache Software Foundation.  All rights
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
/**
 * This class have the info about the class that is going to be published as WS.
 * @author Srinath Perera (hemapani@opensource.lk)
 * @author Dimuthu Leelarathne (muthulee@opensource.lk)
 */
package org.apache.axis.wsdl.wsdl2ws.info;

import java.util.ArrayList;

import org.apache.axis.wsdl.wsdl2ws.WrapperFault;
import org.apache.axis.wsdl.wsdl2ws.WrapperUtils;

public class ServiceInfo {
    private String servicename;
    private String qualifiedServiceName;
    private ArrayList methods;
    private String[][] parameters;

    public ServiceInfo(String servicename,
                       String qualifiedServiceName, ArrayList methods) throws WrapperFault {
        this.methods = methods;
        this.qualifiedServiceName = qualifiedServiceName;
        this.servicename = servicename;

        //validate the infomormation
        if (this.qualifiedServiceName == null) throw new WrapperFault("The fully qualified parameter name can't be null");
        if (servicename == null) servicename = WrapperUtils.getClassNameFromFullyQualifiedName(qualifiedServiceName);
        if (this.methods == null || this.methods.size() == 0)
            throw new WrapperFault("service with no methods no point writing a wrapper");
        if (this.parameters == null)
            this.parameters = new String[0][0];

    }

    /**
     * @return String[]
     */
    public ArrayList getMethods() {
        return methods;
    }


    public String getQualifiedServiceName() {
        return qualifiedServiceName;
    }

    /**
     * @return String
     */
    public String getServicename() {
        return servicename;
    }

    /**
     * return true if qualifiedname is a direct return type in the
     * service
     * @param qualifiedname
     * @return weather gvien qu. name is a direct return type ...
     */
    public boolean isDirectReturn(String qualifiedname) {
        for (int i = 0; i < this.methods.size(); i++)
            if (((MethodInfo) this.methods.get(i)).getReturnType().getLangName().equals(qualifiedname)) return true;
        return false;
    }
}
