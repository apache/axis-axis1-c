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

package org.apache.axismora.encoding;

import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.StringBufferInputStream;
import java.io.Writer;
import java.util.Vector;

import javax.xml.namespace.QName;

import junit.framework.TestCase;

import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPHeaderElement;
import org.apache.axismora.deployment.wsdd.WSDDDeployment;
import org.apache.axismora.engine.SimpleServicePool;
import org.apache.axismora.soap.BasicMessageContext;
import org.apache.axismora.soap.SOAPNodeInfo;

import testData.TestParameter;

/**
 * This Test case tests most basic logic of message processing except Wrappers.
 * @author Srianth Perea(hemapani@opensource.lk) 
 * Dimuthu Leelarathne(muthulee@opensource.lk)
 */

public class DesirializationContextTest extends TestCase {
    private DesirializationContext se;
    private WSDDDeployment dep;

    public DesirializationContextTest(){
        super();
    }

    public DesirializationContextTest(String arg0) {
        super(arg0);
    }

    protected void setUp() throws Exception {
        if (dep == null)
            dep = WSDDDeployment.getInstance("mora-server.wsdd");
    }


    public void testBasicFlow() throws Exception {
		String file = "./samples/rq/rq4.xml";
        //create message data
        InputStream in = new FileInputStream(file);
        OutputStream out = System.out;
        BasicMessageContext md =
            new BasicMessageContext(
                in,
                out,
                new SOAPNodeInfo(dep),
                dep.getService(new QName("LogTestService")),
                new SimpleServicePool(),
                null,
                null);
        md.setSoapEnvelope(new SOAPEnvelope());        
		md.setMethodName(new QName("value"));
        // since no wrapper involved create a imaginary  result
        md.setSoapBodyContent(new TestParameter());

        // print it back
        md.serialize();
        System.out.flush();
    }

    public void testCreateEnvelope() throws Exception {
        String[] testdata =
            { "<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"> <SOAP-ENV:Header></SOAP-ENV:Header><SOAP-ENV:Body></SOAP-ENV:Body></SOAP-ENV:Envelope>" };
        for (int i = 0; i < testdata.length; i++) {
            ftestCreateEnvelope(new StringBufferInputStream(testdata[i]));
        }
		InputStream in2 = new FileInputStream("test/org/apache/axismora/encoding/headertest.xml");
		ftestCreateEnvelope(in2);
 
    }

    public void testCreateHeaders() throws Exception {
        //ftestCreateHeaders(new StringBufferInputStream("<SOAP-ENV:Header><t:Transaction xmlns:t=\"some-URI\" xsi:type=\"xsd:int\" mustUnderstand=\"1\"></SOAP-ENV:Header> <SOAP-ENV:Body></SOAP-ENV:Body></SOAP-ENV:Envelope>"));
        
        
		InputStream in2 =
			new FileInputStream("test/org/apache/axismora/encoding/headertest.xml");		 
		ftestCreateHeaders(in2);
    }

    public void ftestCreateEnvelope(InputStream in) throws Exception {
        //create message data
        OutputStream out = System.out;
        BasicMessageContext md =
            new BasicMessageContext(
                in,
                out,
                new SOAPNodeInfo(dep),
                dep.getService(new QName("LogTestService")),
                new SimpleServicePool(),
                null,
                null);
        md.parseAndValidateKnownTags();
        SOAPEnvelope env = md.getEnvelope();
        Writer w = new OutputStreamWriter(out);
        SerializationContext sc = new SerializationContextImpl(w);
        w.write(
            "############################ TEST MARGIN ###############################");
        env.output(sc);

    }
    public void ftestCreateHeaders(InputStream in) throws Exception {
		OutputStream out = System.out;
		 BasicMessageContext md =
			 new BasicMessageContext(
				 in,
				 out,
				 new SOAPNodeInfo(dep),
				 dep.getService(new QName("LogTestService")),
				 new SimpleServicePool(),
				 null,
				 null);
		 md.parseAndValidateKnownTags();
     	Vector headers = md.getDeserializer().getHeaders();
		System.out.println("inside 3");
        Writer w = new OutputStreamWriter(out);
        
        
        SerializationContext sc = new SerializationContextImpl(w);
        w.write("############################ TEST MARGIN ###############################");
        
        for (int i=0;i<headers.size();i++) {
          ((SOAPHeaderElement)headers.get(i)).output(sc);
        }
    }

    public void testBlindReading() {
        try {

            System.out.println(se.getValueOREnd());
            while (true) {
                System.out.println(se.getValueOREnd());
            }
        } catch (Exception e) {
            System.out.println("Lala   ::" + e.getMessage());
        }
    }

    public void testBlindReadingTillAQName() {
        try {
            System.out.println(
                se.getValue("http://vajira.entc/table", "op3") + "end !!!");
            while (true) {
                String val = se.getValue("http://vajira.entc/table", "op5");
                if (val == null) {
                    System.out.println("sss :: null");
                    break;
                } else {
                    System.out.println(val);
                }

            } // end of while
            se.getValue("http://vajira.entc/table", "op7");
        } catch (Exception e) {
            System.out.println("Lala   ::" + e.getMessage());
        }

    }

    /* (non-Javadoc)
     * @see junit.framework.TestCase#tearDown()
     */
    protected void tearDown() throws Exception {
    }
}
