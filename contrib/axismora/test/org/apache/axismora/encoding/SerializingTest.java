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

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;

import javax.xml.parsers.DocumentBuilderFactory;

import junit.framework.TestCase;

import org.apache.axis.AxisFault;
import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.axis.message.SOAPBodyElement;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPFault;
import org.apache.axis.message.SOAPHeaderElement;
import org.w3c.dom.Document;

import testData.TestResult;

/**
 * This TestCase discribes how the SOAPElements (inbuild to the axis) can be use in the implementation
 * and how to use SerializationContext to serialize them.
 * @author Srianth Perera (hemapani@opensource.lk)
 */

public class SerializingTest extends TestCase {
    Writer w = new OutputStreamWriter(System.out);
    ;

    public SerializingTest() throws IOException {
        w = new FileWriter("./samples/rs.xml");
    }

    public SerializingTest(String arg0) {
        super(arg0);
    }

    protected void setUp() throws Exception {

    }

    protected void tearDown() throws Exception {

    }

    /**
     * Test a Envelope with a body element
     */
    public void testSerialize() throws Exception {
        //create a envelope
        SOAPEnvelope env = new SOAPEnvelope();
        SOAPHeaderElement h =
            new SOAPHeaderElement("www.opensource.lk/axis", "user", "hemapani");
        h.setActor("10.8.101.131:8080/test");
        h.setMustUnderstand(true);
        env.addHeader(h);

        //create body and
        TestResult r = new TestResult();
        SOAPBodyElement bo = new SOAPBodyElement();
        bo.setName("method name");
        bo.setNamespaceURI("www.opensource.lk/axis");
        bo.setObjectValue(r);
        env.addBodyElement(bo);

        SerializationContext sc = new SerializationContextImpl(w);
        /*
           Add the Seralizer which can serialize a instance of result.
           The serializer added to the default type mapping
           1) used value is enable adding to default type mapping  edit the DefaultTypeMappingImpl ** used here **
           2) Add the Serializer as a default type mapping
           3) add dymnamically Still DONOT WORKING (Serialier not found exception) we might able to find a way !!!
                   TypeMappingRegistry reg = new TypeMappingRegistryImpl();
                   javax.xml.rpc.encoding.TypeMapping t = reg.getOrMakeTypeMapping("www.opensurce.lk/axis/encoding");
                   sc.getTypeMapping().register(Result.class , Constants.SOAP_RESULT,  new ResultSerializerFactory(),null);
                   t.register(Parameter.class , Constants.SOAP_RESULT,  new ResultSerializerFactory(),null);
         
        
        sc.getTypeMapping().register(Serializable.class, org.apache.axismora.Constants.SOAP_RESULT, new SerializableSerializerFactory(), null);
        */
        env.output(sc);
        System.out.println(" Test suceeded");
        w.flush();
        w.close();

    }
    public void testDomNodeSerialization() throws Exception {
        SerializationContext sc = new SerializationContextImpl(w);
        Document doc =
            DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(
                new File("./test/org/apache/axismora/encoding/domele.xml"));
        sc.writeDOMElement(doc.getDocumentElement());
        w.flush();
    }

    public void testFault() throws Exception {
        //create the soap envelope
        SOAPEnvelope env = new SOAPEnvelope();

        SOAPHeaderElement h =
            new SOAPHeaderElement("www.opensource.lk/axis", "user", "hemapani");
        h.setActor("10.8.101.131:8080/test");
        h.setMustUnderstand(true);
        env.addHeader(h);

        System.out.println("create a fault");
        ///the serialize will print a stacktrace start form the genaration of axis Fault
        SOAPFault f = new SOAPFault(new AxisFault("Error"));
        env.getBody().addChildElement(f);

        w = new OutputStreamWriter(System.out);
        SerializationContext sc = new SerializationContextImpl(w);
        env.output(sc);
        System.out.println(" Test suceeded");
        w.flush();
    }

    public static void main(String[] args) throws Exception {
        SerializingTest sr = new SerializingTest();
        sr.testSerialize();
        sr.testFault();
        sr.testDomNodeSerialization();
        sr.tearDown();
    }
}
