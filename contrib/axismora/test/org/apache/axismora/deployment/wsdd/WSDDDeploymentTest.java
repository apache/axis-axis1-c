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

package org.apache.axismora.deployment.wsdd;
import java.util.Vector;

import javax.xml.namespace.QName;

import junit.framework.Assert;
import junit.framework.TestCase;
import junit.framework.TestSuite;

import org.apache.axis.deployment.wsdd.WSDDGlobalConfiguration;
import org.apache.axis.deployment.wsdd.WSDDHandler;
import org.apache.axis.deployment.wsdd.WSDDService;

/**
 * @author Srianth (hemapani@cse.mrt.ac.lk)
 */

public class WSDDDeploymentTest extends TestCase {
    private WSDDDeployment d;
    
	public  WSDDDeploymentTest(String name){
		super(name);	
	}	

    protected void setUp() throws Exception {
        this.d = WSDDDeployment.getInstance("mora-server.wsdd");
    }

	public static junit.framework.Test suite(){
		TestSuite suite = new TestSuite("All tests");		     
		suite.addTestSuite(WSDDDeploymentTest.class);
		return suite;
	}

    public void testHandlerChainExtraction() throws Exception {
        Vector hf = d.getGlobelRequestFlowHandlers();
        System.out.println("GLOBAL # REQUEST");
        for (int i = 0; i < hf.size(); i++) {
            QName q = ((WSDDHandler) hf.get(i)).getType();
            System.out.println("@" + q.getNamespaceURI() + ":" + q.getLocalPart());
        }
        hf = d.getGlobelResponseFlowHandlers();
        System.out.println("GLOBAL # RESPONSE");
        for (int i = 0; i < hf.size(); i++) {
            QName q = ((WSDDHandler) hf.get(i)).getType();
            System.out.println("@" + q.getNamespaceURI() + ":" + q.getLocalPart());
        }
        hf = d.getTransportRequestFlowHandlers("http");
        System.out.println("TRANSPORT # REQUEST");
        for (int i = 0; i < hf.size(); i++) {
            QName q = ((WSDDHandler) hf.get(i)).getType();
            System.out.println("@" + q.getNamespaceURI() + ":" + q.getLocalPart());
        }
        hf = d.getTransportResponseFlowHandlers("http");
        System.out.println("TRANSPORT # RESPONSE");
        for (int i = 0; i < hf.size(); i++) {
            QName q = ((WSDDHandler) hf.get(i)).getType();
            System.out.println("@" + q.getNamespaceURI() + ":" + q.getLocalPart());
        }
        System.out.println(
            "-----------------------------GET WEB SERVICE ---------------------");
        System.out.println(
            "######################### Printing Service Information #########################");
        WSDDService ws = d.getService(new QName("LogTestService"));

        //System.out.println(ws.getProvider());
        System.out.println(ws.getQName());
        System.out.println(ws.getJavaClass());
        System.out.println("Class Name is =" + ws.getParameter("className"));
        hf = ws.getRequestFlow().getHandlers();
        for (int i = 0; i < hf.size(); i++) {
            System.out.println("@" + ((WSDDHandler) hf.get(i)));
        }
        hf = ws.getResponseFlow().getHandlers();
        for (int i = 0; i < hf.size(); i++) {
            System.out.println("@" + ((WSDDHandler) hf.get(i)));
        }
        System.out.println("TestPassed");
    }

	public void testGlobalConfigaration(){
		WSDDGlobalConfiguration gconf = this.d.getGlobalInfo();
		Assert.assertEquals(gconf.getParameter("adminPassword"),"admin");
		Assert.assertEquals(gconf.getParameter("sendXMLDeclaration"),"true");
		Assert.assertEquals(gconf.getParameter("attachments.implementation"),"org.apache.axis.attachments.AttachmentsImpl");
		Assert.assertEquals(gconf.getParameter("sendMultiRefs"),"false");
		
		Vector greqfh = this.d.getGlobelRequestFlowHandlers();
		Vector greffh = this.d.getGlobelRequestFlowHandlers();
		Assert.assertTrue(greqfh != null && greffh != null && greqfh.size() == 0 && greffh.size() == 0);
	}
	
	public void testServiceConfigaration()throws Exception{
		WSDDService sconf = this.d.getService(new QName("LogTestService"));
		Assert.assertEquals(sconf.getParameter("allowedMethods"),"*");
		Assert.assertEquals(sconf.getParameter("className"),"services.logtest.Service");
		Assert.assertNull(sconf.getParameter("scope"));
	}


    protected void tearDown() throws Exception {
    }

}
