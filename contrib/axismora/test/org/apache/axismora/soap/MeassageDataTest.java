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

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;

import javax.xml.namespace.QName;

import junit.framework.TestCase;
import org.apache.axismora.deployment.wsdd.WSDDDeployment;
import org.apache.axismora.encoding.DesirializationContext;
import org.apache.axismora.engine.SimpleServicePool;
import services.point.PointService;

/**
 * This TestCase descriabes the flow of message data, (in addition to DesiarializationContext
 * test this includes testing acts of wrappers as well.)
 * @author Srianth Perera (hemapani@opensource.lk)
 */

public class MeassageDataTest extends TestCase {
    private DesirializationContext se;

    public void testBasicFlow() throws Exception {
        atestBasicFlow("./samples/rq/rqw1.xml");
    }

    public void atestBasicFlow(String file) throws Exception {
        //create message data
        InputStream in = new FileInputStream(file);
        OutputStream out = System.out;
        WSDDDeployment dep = WSDDDeployment.getInstance("mora-server.wsdd");
        BasicMessageContext md =
            new BasicMessageContext(
                in,
                out,
                new SOAPNodeInfo(dep),
                dep.getService(new QName("Point")),
                new SimpleServicePool(),
                null,
                null);
        md.parseAndValidateKnownTags();
        md.startParseSOAPBody();
        // we will create the service manually
        PointService ps = new PointService();
        //invoke the result
        ps.invoke(md);
        //print the response
        md.serialize();
        System.out.flush();
    }
    public static void main(String[] args) throws Exception {
        MeassageDataTest t = new MeassageDataTest();
        t.atestBasicFlow(".\\samples\\rq\\rqw1.xml");
    }
}
