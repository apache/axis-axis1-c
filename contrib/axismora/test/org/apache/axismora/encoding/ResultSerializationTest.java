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

import java.io.PrintWriter;
import java.io.Writer;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import junit.framework.TestCase;

import org.apache.axis.encoding.SerializationContext;
import org.apache.axis.encoding.SerializationContextImpl;
import org.apache.axis.message.SOAPEnvelope;
import org.apache.axis.message.SOAPHeaderElement;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * This TestCase descriabes how to create a SOAPHeaderElement and add org.w3c.Elements to the
 * element and how to serialize it.
 * @author Srianth Perera(hemapani@opensource.lk) and Dimuthu Leelarathe (muthulee@opensource.lk)
 */

public class ResultSerializationTest extends TestCase {
    public void testHeaderSerialization() throws Exception {
        DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
        DocumentBuilder db = dbf.newDocumentBuilder();
        Document doc = db.newDocument();

        SOAPHeaderElementContent hec = new SOAPHeaderElementContent();

        //create the header element
        Element e = doc.createElement("auth");
        Element e1 = doc.createElement("user");
        e1.appendChild(doc.createTextNode("Sha"));
        Element e2 = doc.createElement("passwd");
        e2.appendChild(doc.createTextNode("123"));
        e.appendChild(e1);
        e.appendChild(e2);
        hec.addElement(e);

        //create header element
        Element v = doc.createElement("meta");
        Element v1 = doc.createElement("version");
        v1.appendChild(doc.createTextNode("1.0"));
        v1.setAttributeNS("www.opensource.lk/axis-encode", "enc:stb", "w3c");
        v.appendChild(v1);
        hec.addElement(v);

        //create envelope
        SOAPEnvelope env = new SOAPEnvelope();
        SOAPHeaderElement h =
            new SOAPHeaderElement("www.opensource.lk/axis", "user", "hemapani");
        h.setActor("10.8.101.131:8080/test");
        h.setMustUnderstand(true);
        h.setObjectValue(hec);
        env.addHeader(h);

        Writer w = new PrintWriter(System.out, true);
        SerializationContext serializer = new SerializationContextImpl(w);
        //this part is a design test need not to worry about it  
        /* register serializer for more info @see SerializationTest#testSerialize() */
        //serializer.getTypeMapping().register(
        //                            SOAPHeaderElementContent.class,
        //                            org.apache.axismora.Constants.SOAP_BODY_ELEMENT_CONTENT,
        //                            new SOAPHeaderElementContentSerializerFactory(),
        //                            null);
        /* Elements are printed using SerializationContext#printDomElement() */

        env.output(serializer);
        System.out.println("test suceed");
        w.flush();
    }

    public static void main(String[] args) throws Exception {
        ResultSerializationTest r = new ResultSerializationTest();
        r.testHeaderSerialization();
    }
}
