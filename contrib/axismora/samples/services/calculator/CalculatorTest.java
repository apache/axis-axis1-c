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

package services.calculator;
import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;

import junit.framework.Assert;
import junit.framework.TestCase;

import org.apache.axis.client.Call;
import org.apache.axis.client.Service;
import org.apache.axis.encoding.XMLType;

public class CalculatorTest extends TestCase {
    private Call call = null;
    protected void setUp() throws Exception {
        String port = "4444"; //port the TCP mon listens
        String SOAPAction = "Calculator"; //service name

        String endpoint = "http://127.0.0.1:" + port + "/service/servlet/AxisServlet";

        Service service = new Service();
        call = (Call) service.createCall();

        call.setTargetEndpointAddress(new java.net.URL(endpoint));
        call.setSOAPActionURI(SOAPAction);
    }

    public void testAdd() throws Exception {
        QName method = new QName("someuri", "add");
        call.setOperationName(method);

        call.removeAllParameters();

        call.addParameter("op1", XMLType.XSD_INT, ParameterMode.IN);
        call.addParameter("op2", XMLType.XSD_INT, ParameterMode.IN);
        call.setReturnType(XMLType.XSD_INT);

        Integer i1 = new Integer(9);
        Integer i2 = new Integer(2);

        Integer ret = (Integer) call.invoke(new Object[] { i1, i2 });

        Assert.assertEquals(i1.intValue() + i2.intValue(), ret.intValue());

        Integer i3 = new Integer(900);
        Integer i4 = new Integer(2578);

        ret = (Integer) call.invoke(new Object[] { i3, i4 });

        Assert.assertEquals(i3.intValue() + i4.intValue(), ret.intValue());

        System.out.println("Test suceeded testAdd()");
    }

    public void testSustract() throws Exception {
        QName method = new QName("someuri", "sub");
        call.setOperationName(method);

        call.removeAllParameters();

        call.addParameter("op1", XMLType.XSD_INT, ParameterMode.IN);
        call.addParameter("op2", XMLType.XSD_INT, ParameterMode.IN);
        call.setReturnType(XMLType.XSD_INT);

        Integer i1 = new Integer(9);
        Integer i2 = new Integer(2);

        Integer ret = (Integer) call.invoke(new Object[] { i1, i2 });

        Assert.assertEquals(i1.intValue() - i2.intValue(), ret.intValue());
        System.out.println("Test suceeded testSustract()");
    }

    public void testDivision() throws Exception {
        QName method = new QName("someuri", "div");
        call.setOperationName(method);

        call.removeAllParameters();

        call.addParameter("op1", XMLType.XSD_FLOAT, ParameterMode.IN);
        call.addParameter("op2", XMLType.XSD_FLOAT, ParameterMode.IN);
        call.setReturnType(XMLType.XSD_FLOAT);

        Float i1 = new Float(9);
        Float i2 = new Float(2);

        Float ret = (Float) call.invoke(new Object[] { i1, i2 });

        Assert.assertEquals(i1.intValue() / i2.intValue(), ret.intValue());
        System.out.println("Test suceeded testDivision()");
    }

    public void testMultiply() throws Exception {
        QName method = new QName("someuri", "mul");
        call.setOperationName(method);

        call.removeAllParameters();

        call.addParameter("op1", XMLType.XSD_INT, ParameterMode.IN);
        call.addParameter("op2", XMLType.XSD_INT, ParameterMode.IN);
        call.setReturnType(XMLType.XSD_INT);

        Integer i1 = new Integer(9);
        Integer i2 = new Integer(2);

        Integer ret = (Integer) call.invoke(new Object[] { i1, i2 });

        Assert.assertTrue(i1.floatValue() * i2.floatValue() == ret.floatValue());
        System.out.println("Test suceeded testMultiply()");
    }

    public static void main(String[] args) throws Exception {
        CalculatorTest test = new CalculatorTest();
        test.setUp();
        test.testAdd();
        test.testSustract();
        test.testMultiply();
        test.testDivision();
        test.tearDown();
    }
}
