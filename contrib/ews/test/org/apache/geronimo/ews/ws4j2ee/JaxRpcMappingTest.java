/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002-2003 The Apache Software Foundation.  All rights
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
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "The Jakarta Project", "Commons", and "Apache Software
 *    Foundation" must not be used to endorse or promote products derived
 *    from this software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
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
 *
 */
 
 package org.apache.geronimo.ews.ws4j2ee;

import java.util.List;

import javax.wsdl.Operation;
import javax.xml.namespace.QName;

import junit.framework.Assert;

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.jaxrpcmapping.J2eeEmitter;
import org.apache.geronimo.ews.jaxrpcmapping.JaxRpcMapper;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;

/**
 * @author hemapani
 */
public class JaxRpcMappingTest extends AbstractTestCase{
    /**
     * @param testName
     */
    public JaxRpcMappingTest(String testName) {
        super(testName);
    }

	public void testGoogleTypeMapping() throws Exception{
	    try {
	    	   J2EEWebServiceContext context = ContextFactory.getJ2EEWsContext(true);
	    	   context.setMiscInfo(ContextFactory.createMiscInfo());
	           String mappingfile = sampleDir +"mapper/google/GoogleSearch.xml";
	           String wsdlfile = sampleDir +"mapper/google/GoogleSearch.wsdl";
	           J2eeEmitter j2ee = new J2eeEmitter();
	           j2ee.setMappingFilePath(getTestFile(mappingfile));
	           j2ee.setOutputDir(outDir);
	           j2ee.setServerSide(true);
	           j2ee.setVerbose(false);
	           j2ee.setHelperWanted(true);
	           System.out.println();
	           j2ee.runServerSide(getTestFile(wsdlfile));
	           WSDLContext wscontext = ContextFactory.createWSDLContext(j2ee.getSymbolTable());
			   context.setWSDLContext(wscontext);
	           PortEntry port = wscontext.getPort(new QName("GoogleSearchPort"));
	           BindingEntry be = wscontext.getBinding(new QName("urn:GoogleSearch","GoogleSearchBinding"));
	           PortTypeEntry pe = wscontext.getPortType(new QName("urn:GoogleSearch","GoogleSearchPort"));
	           JaxRpcMapper mapper = j2ee.getJaxRpcMapper();
	           JaxRpcMapperContext mc =ContextFactory.createJaxRpcMapperContext(new Object[]{mapper,j2ee});
	           context.setJAXRPCMappingContext(mc);
	           Assert.assertNotNull(port);
	           Assert.assertNotNull(be);
	           Assert.assertNotNull(pe);
	           Assert.assertEquals(mc.getJavaType(new QName("urn:GoogleSearch","GoogleSearchResult")),"org.objectweb.wssample.gen.google.MyGoogleSearchResult");
	           Assert.assertEquals(mc.getJavaType(new QName("urn:GoogleSearch","ResultElementArray")),"org.objectweb.wssample.gen.google.ResultElement[]");
	    } catch (Exception e) {
	        e.printStackTrace();
	        throw e;
	    }
	}
	public void testBookTypeMapping() throws Exception{
	    try {
			   J2EEWebServiceContext context = ContextFactory.getJ2EEWsContext(true);
			   context.setMiscInfo(ContextFactory.createMiscInfo());
	           String mappingfile = sampleDir +"jaxrpc/book/BookQuote.xml";
	           String wsdlfile = sampleDir +"jaxrpc/book/BookQuote.wsdl";
	           J2eeEmitter j2ee = new J2eeEmitter();
	           j2ee.setMappingFilePath(getTestFile(mappingfile));
	           j2ee.setOutputDir(outDir);
	           j2ee.setServerSide(true);
	           j2ee.setVerbose(false);
	           j2ee.setHelperWanted(true);
	           System.out.println();
	           j2ee.runServerSide(getTestFile(wsdlfile));
	           WSDLContext wscontext = ContextFactory.createWSDLContext(j2ee.getSymbolTable());
	           PortEntry port = wscontext.getPort(new QName("BookQuotePort"));
	           BindingEntry be = wscontext.getBinding(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","BookQuoteBinding"));
	           PortTypeEntry pe = wscontext.getPortType(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","BookQuote"));
	           ServiceEntry se = wscontext.getService(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","BookQuoteService"));
	           JaxRpcMapper mapper = j2ee.getJaxRpcMapper();
	           JaxRpcMapperContext mc =ContextFactory.createJaxRpcMapperContext(new Object[]{mapper,j2ee});
	           Assert.assertNotNull(port);
	           Assert.assertNotNull(be);
	           Assert.assertNotNull(pe);
	           Assert.assertEquals(mc.getExceptionType(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","InvalidIsbnFault")),"com.jwsbook.jaxrpc.InvalidIsbnException");
	        
	           String sei = mc.getServiceEndpointInterfaceName(pe,be);
	           Assert.assertEquals(sei,"com.jwsbook.jaxrpc.BookQuote");
	           String si = mc.getServiceInterfaceName(se);
	           Assert.assertEquals(si,"com.jwsbook.jaxrpc.BookQuoteService");
	           List l = pe.getPortType().getOperations();
	           Operation op = (Operation)l.get(0);
	           Assert.assertEquals(mc.getJavaMethodName(be,op),"getBookPrice");
	           Assert.assertEquals(mc.getJavaMethodParamType(be,op,0,null),"java.lang.String");
	           Assert.assertEquals(mc.getJavaMethodReturnType(be,op),"float");  
	    } catch (Exception e) {
	        e.printStackTrace();
	        throw e;
	    }
	}

}
