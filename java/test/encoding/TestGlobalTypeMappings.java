/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
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

package test.encoding;

import org.apache.axis.client.Call;
import org.apache.axis.encoding.TypeMapping;
import org.apache.axis.encoding.ser.BeanDeserializerFactory;
import org.apache.axis.encoding.ser.BeanSerializerFactory;
import org.apache.axis.enum.Style;
import test.GenericLocalTest;

import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;

/**
 * Confirm that global type mappings work in both RPC and Document
 * contexts.
 *
 * @author Glen Daniels (gdaniels@apache.org)
 */
public class TestGlobalTypeMappings extends GenericLocalTest {
    private QName TYPE_QNAME = new QName("ns", "dataType");

    public TestGlobalTypeMappings() {
        super("service");
    }

    public TestGlobalTypeMappings(String s) {
        super(s);
    }

    protected void setUp() throws Exception {
        super.setUp(false); // don't deploy here
        TypeMapping tm = (TypeMapping)config.getTypeMappingRegistry().
                getDefaultTypeMapping();
        tm.register(Data.class, TYPE_QNAME,
                    new BeanSerializerFactory(Data.class, TYPE_QNAME),
                    new BeanDeserializerFactory(Data.class, TYPE_QNAME));
    }

    public void testDocLit() throws Exception {
        deploy("service", this.getClass(), Style.WRAPPED);
        Call call = getCall();
        call.setOperationStyle("wrapped");
        call.setOperationUse("literal");
        call.setEncodingStyle("");
        call.registerTypeMapping(Data.class, TYPE_QNAME,
                    new BeanSerializerFactory(Data.class, TYPE_QNAME),
                    new BeanDeserializerFactory(Data.class, TYPE_QNAME));
        call.setReturnClass(Data.class);
        call.addParameter("arg0", TYPE_QNAME, ParameterMode.IN);
        Data data = new Data();
        data.stringMember = "doc lit test";
        data.floatMember = new Float(451.0F);
        call.invoke("echoData", new Object [] { data });
    }

    /**
     * Our service method.  We'll deploy this several ways.
     *
     * @param data
     * @return
     */
    public Data echoData(Data data) {
        return data;
    }
}
