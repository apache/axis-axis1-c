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

package org.apache.axismora.handlers;

import java.io.File;

import javax.xml.namespace.QName;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.rpc.ParameterMode;

import junit.framework.TestCase;

import org.apache.axis.client.Call;
import org.apache.axis.client.Service;
import org.apache.axis.encoding.XMLType;
import org.apache.axis.message.SOAPHeaderElement;
import org.w3c.dom.Document;

public class HeaderTest extends TestCase {
    protected void setUp() throws Exception {
        super.setUp();
    }
    /**
     * To run this test the SOAPEngine should be listening on the port 4444. (run the simple axis Server)
     * It will print the Header at the server.
     * @throws Exception
     */
    public void testBigHeader() throws Exception {
        String port = "4444"; //port the TCP mon listens
        String SOAPAction = "CalculatorC"; //service name

        String endpoint = "http://127.0.0.1:" + port + "/axismora/servlet/AxisServlet";
        //String endpoint = "http://127.0.0.1:" +  port + "/axis/services/Calculator";

        QName method = new QName("someuri", "add");

        String value1 = "9";
        String value2 = "2";

        Integer i1 = new Integer(value1);
        Integer i2 = new Integer(value2);

        Service service = new Service();
        Call call = (Call) service.createCall();

        call.setTargetEndpointAddress(new java.net.URL(endpoint));
        call.setSOAPActionURI(SOAPAction);
        call.setOperationName(method);
        call.addParameter("op1", XMLType.XSD_INT, ParameterMode.IN);
        call.addParameter("op2", XMLType.XSD_INT, ParameterMode.IN);
        call.setReturnType(XMLType.XSD_INT);

        SOAPHeaderElement header = new SOAPHeaderElement("opensource.lk", "bigHeader");
        Document doc =
            DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(
                new File("./test/lk/opensource/axis2/handlers/header1.xml"));
        header.setObjectValue(doc.getDocumentElement());
        header.setActor("http://www.w3.org/2002/12/soap-envelope/role/echoHandler");
        call.addHeader(header);

        header = new SOAPHeaderElement("opensource.lk", "bigHeader1");
        doc =
            DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(
                new File("./test/lk/opensource/axis2/handlers/header2.xml"));
        header.setObjectValue(doc.getDocumentElement());
        header.setActor("http://www.w3.org/2002/12/soap-envelope/role/echoHandler");
        call.addHeader(header);

        header = new SOAPHeaderElement("opensource.lk", "bigHeader2");
        doc =
            DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(
                new File("./test/lk/opensource/axis2/handlers/header3.xml"));
        header.setObjectValue(doc.getDocumentElement());
        header.setActor("http://www.w3.org/2002/12/soap-envelope/role/echoHandler");
        header.setMustUnderstand(true);
        call.addHeader(header);

        long st = System.currentTimeMillis();
        Integer ret = (Integer) call.invoke(new Object[] { i1, i2 });
        long end = System.currentTimeMillis();
        ret = (Integer) call.invoke(new Object[] { i1, i2 });

        System.out.println("Got result : " + ret);
        System.out.println("It takes " + (end - st) + " miliseconds");

    }

    /**
     * this test check the must understood fault. The method must fail 
     * @throws Exception
     */
    public void testMustUnderstandFault() throws Exception {
        String port = "4444"; //port the TCP mon listens
        String SOAPAction = "CalculatorC"; //service name

        String endpoint = "http://127.0.0.1:" + port + "/service/servlet/AxisServlet";
        //String endpoint = "http://127.0.0.1:" +  port + "/axis/services/Calculator";

        QName method = new QName("someuri", "add");

        String value1 = "9";
        String value2 = "2";

        Integer i1 = new Integer(value1);
        Integer i2 = new Integer(value2);

        Service service = new Service();
        Call call = (Call) service.createCall();

        call.setTargetEndpointAddress(new java.net.URL(endpoint));
        call.setSOAPActionURI(SOAPAction);
        call.setOperationName(method);
        call.addParameter("op1", XMLType.XSD_INT, ParameterMode.IN);
        call.addParameter("op2", XMLType.XSD_INT, ParameterMode.IN);
        call.setReturnType(XMLType.XSD_INT);

        SOAPHeaderElement header =
            new SOAPHeaderElement("opensource.lk", "MustUnderStandFail");
        Document doc =
            DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(
                new File("./test/lk/opensource/axis2/handlers/header1.xml"));
        header.setObjectValue(doc.getDocumentElement());
        header.setActor("http://www.w3.org/2002/12/soap-envelope/role/echoHandler");
        header.setMustUnderstand(true);
        call.addHeader(header);
        Integer ret;

        try {
            ret = (Integer) call.invoke(new Object[] { i1, i2 });
        } catch (java.rmi.RemoteException e) {
            e.printStackTrace();
            System.out.println("The invocation failed as expected");

            return;
        }
        throw new Exception("Method must fail");
    }
    public static void main(String[] args) throws Exception {
        HeaderTest ht = new HeaderTest();
        ht.setUp();
        ht.testBigHeader();
        ht.testMustUnderstandFault();
    }
}
