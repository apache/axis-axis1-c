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

package org.apache.axismora.soap;

import java.util.ArrayList;

import javax.xml.namespace.QName;

import org.apache.axismora.deployment.AxisDeployment;
/**
 * This class represnt the information about an SOAP node. The SOAP node is 
 * defined in the same context as by the SOAP specification 1.2 . The roles and the 
 * headers this soap node understood are as the same context of the above spec.    
 * @author Srinath Perera(hemapani@opensource.lk)
 */

public class SOAPNodeInfo {
    /* all the roles olayed by this soapnode*/
    private ArrayList roles;
    /* all the headers understood by the soap node */
    private ArrayList understandHeaders;
    /* deployment information of this soap node */
    private AxisDeployment deployment;

    public SOAPNodeInfo(AxisDeployment deployment) {
        this.deployment = deployment;
        this.roles = new ArrayList();
        this.understandHeaders = new ArrayList();
    }

    public ArrayList getAllRoles() {
        return roles;
    }

    public ArrayList getAllUnderstandHeaders() {
        return understandHeaders;
    }

    public AxisDeployment getDeployment() {
        return deployment;
    }
    public void addRole(String role) {
        if (role != null && !this.roles.contains(role))
            roles.add(role);
    }
    public void addUnderstandHeader(QName header) {
        if (header != null && !this.understandHeaders.contains(header))
            understandHeaders.add(header);
    }
}
