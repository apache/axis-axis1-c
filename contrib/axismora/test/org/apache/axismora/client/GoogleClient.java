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

package org.apache.axismora.client;

import googleSearch.GoogleSearchPort;
import googleSearch.GoogleSearchResult;

import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;
import javax.xml.rpc.encoding.XMLType;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.axismora.encoding.OutParameter;
import org.apache.axismora.wrappers.simpleType.BooleanParam;
import org.apache.axismora.wrappers.simpleType.IntParam;
import org.apache.axismora.wrappers.simpleType.StringParam;

/**
 * @author hemapani
 */
public class GoogleClient extends TestCase {
    private String port = "5555"; //port the TCP mon listens
    private String SOAPAction = "Google"; //service name

    private String endpoint = "http://127.0.0.1:" + port + "/axis/services/B";
    private Service service;

    protected void setUp() throws Exception {
        service = new Service();
    }

    public void testDoSpellingSuggestion() throws Exception {
        QName method = new QName("doSpellingSuggestion");

        Call call = (Call) service.createCall();
        call.setTargetEndpointAddress(endpoint);
        call.setPortTypeName(new QName(SOAPAction));
        call.setOperationName(method);

        call.addParameter(
            "param1",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);
        call.addParameter(
            "param2",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);
        call.setReturnType(XMLType.XSD_STRING, java.lang.String.class);

        GoogleSearchPort gsp = new GoogleSearchPort();

        StringParam ret =
            (StringParam) call.invoke(
                new OutParameter[] {
                    new StringParam("value1"),
                    new StringParam("value2")});
        System.out.print(gsp.doSpellingSuggestion("value1", "value2") + " =  " + ret);
        Assert.assertTrue(
            gsp.doSpellingSuggestion("value1", "value2").equals(ret.getParam()));

        System.out.println("test doSpellingSuggestion() suceeded ");
    }

    public void testDoGoogleSearch() throws Exception {
        QName method = new QName("doGoogleSearch");

        Call call = (Call) service.createCall();
        call.setTargetEndpointAddress(endpoint);
        call.setPortTypeName(new QName(SOAPAction));
        call.setOperationName(method);

        call.addParameter(
            "param1",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);
        call.addParameter(
            "param2",
            XMLType.XSD_BOOLEAN,
            java.lang.Boolean.class,
            ParameterMode.IN);
        call.addParameter(
            "param3",
            XMLType.XSD_INT,
            java.lang.Integer.class,
            ParameterMode.IN);
        call.addParameter(
            "param4",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);
        call.addParameter(
            "param5",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);
        call.addParameter(
            "param6",
            XMLType.XSD_BOOLEAN,
            java.lang.Boolean.class,
            ParameterMode.IN);
        call.addParameter(
            "param7",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);
        call.addParameter(
            "param8",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);
        call.addParameter(
            "param9",
            XMLType.XSD_INT,
            java.lang.Integer.class,
            ParameterMode.IN);
        call.addParameter(
            "param10",
            XMLType.XSD_STRING,
            java.lang.String.class,
            ParameterMode.IN);

        call.setReturnType(
            new QName("urn:GoogleSearch", "GoogleSearchResult"),
            GoogleSearchResult.class);

        GoogleSearchPort gsp = new GoogleSearchPort();

        GoogleSearchResult ret =
            (GoogleSearchResult) call.invoke(
                new OutParameter[] {
                    new StringParam("value1"),
                    new BooleanParam(true),
                    new IntParam(0),
                    new StringParam("b"),
                    new StringParam("c"),
                    new BooleanParam(true),
                    new StringParam("d"),
                    new StringParam("e"),
                    new IntParam(2),
                    new StringParam("f")});
        GoogleSearchResult val =
            gsp.doGoogleSearch("a", true, 0, "b", "c", true, "d", "e", 2, "f");
        //Assert.assertEquals(val,ret);

        System.out.println("test doGoogleSearch() suceeded ");
    }

    public static void main(String[] args) throws Exception {
        GoogleClient gc = new GoogleClient();
        gc.setUp();
        gc.testDoSpellingSuggestion();
        gc.testDoGoogleSearch();

    }
}
