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

package org.apache.axismora.service;

import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.StringBufferInputStream;

import junit.framework.TestCase;

import org.apache.axismora.Constants;
import org.apache.axismora.engine.AxisEngine;

/**
 * This Class test the deployment and undeployment through a inbuild service  called AdminService
 * @author Srianth Perera(hemapani@opensource.lk)
 */
public class AdminServiceTest extends TestCase {
    public void testDeployment() throws Exception {
        String depStr =
            "<deployment xmlns=\"http://xml.apache.org/axis/wsdd/\""
                + "xmlns:java=\"http://xml.apache.org/axis/wsdd/providers/java\">"
                + "<service name=\"AdminServiceTest\" provider=\"java:RPC\">"
                + "<parameter name=\"className\" value=\"samples.userguide.example3.MyService\"/>"
                + "<parameter name=\"allowedMethods\" value=\"*\"/>"
                + "</service>"
                + "</deployment>";
        String undepStr =
            "<undeployment xmlns=\"http://xml.apache.org/axis/wsdd/\""
                + "xmlns:java=\"http://xml.apache.org/axis/wsdd/providers/java\">"
                + "<service name=\"AdminServiceTest\" provider=\"java:RPC\">"
                + "<parameter name=\"className\" value=\"samples.userguide.example3.MyService\"/>"
                + "<parameter name=\"allowedMethods\" value=\"*\"/>"
                + "</service>"
                + "</undeployment>";
        String depmessage =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
                + "<SOAP-ENV:Body>\n"
                + depStr
                + "\n"
                + "</SOAP-ENV:Body>\n</SOAP-ENV:Envelope>";
        String undepmessage =
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n <SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">"
                + "<SOAP-ENV:Body>\n"
                + undepStr
                + "\n"
                + "</SOAP-ENV:Body>\n</SOAP-ENV:Envelope>";
        StringBufferInputStream buf = new StringBufferInputStream(depmessage);
        FileOutputStream out = new FileOutputStream("junittest.log");
        AxisEngine engine = new AxisEngine(Constants.SERVER_CONFIG_FILE);

        //deploy the service 
        engine.process("AdminService", buf, out, null, null, null, null);

        System.out.println(
            "------------------------- The wsdd with service deployed -------------------");
        BufferedReader r = new BufferedReader(new FileReader("mora-server.wsdd"));
        String line;
        while ((line = r.readLine()) != null) {
            System.out.println(line);
        }
        buf = new StringBufferInputStream(undepmessage);

        //undeploy the service		
        engine.process("AdminService", buf, out, null, null, null, null);
        System.out.println(
            "------------------------- The wsdd with service undeployed -----------------");
        r.close();
        r = new BufferedReader(new FileReader("mora-server.wsdd"));

        while ((line = r.readLine()) != null) {
            System.out.println(line);
        }
        r.close();
    }
    public static void main(String[] args) throws Exception {
        AdminServiceTest at = new AdminServiceTest();
        at.testDeployment();
    }
}
