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

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import junit.framework.Assert;

import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFPortComponent;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFWebserviceDescription;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani
 */
public class WebServiceDDTest {
	public void testGoogleDD() throws FileNotFoundException, GenerationFault{
		WSCFContext wscfcontext 
			= ContextFactory.createWSCFContext(
				new FileInputStream("src/samples/mapper/google/webservice.xml"));
		Assert.assertNull(wscfcontext.getDescription());
		Assert.assertNull(wscfcontext.getLargeIcon());
		Assert.assertNull(wscfcontext.getSmallIcon());
		Assert.assertEquals(wscfcontext.getDisplayName(),"Google Serach");	
		WSCFWebserviceDescription[] wsarray = wscfcontext.getWebServicesDescription();
		Assert.assertNotNull(wsarray);	
		Assert.assertTrue(wsarray.length > 0);
		WSCFWebserviceDescription wsdes = wsarray[0];
		Assert.assertEquals(wsdes.getWebserviceDescriptionName(),"Google Serach WebService");
		Assert.assertEquals(wsdes.getWsdlFile(),"GoogleSearch.wsdl");
		Assert.assertNull(wsdes.getDisplayName());
		Assert.assertNull(wsdes.getLargeIcon());
		Assert.assertNull(wsdes.getSmallIcon());
		Assert.assertNull(wsdes.getDescription());
		Assert.assertEquals(wsdes.getJaxrpcMappingFile(),"GoogleSearch.xml");
		WSCFPortComponent[] pc = wsdes.getPortComponent();
		Assert.assertNotNull(pc);
		Assert.assertTrue(pc.length > 0);
		WSCFPortComponent tpc = pc[0];
		Assert.assertEquals(tpc.getDescription(),"port component description");
		Assert.assertEquals(tpc.getPortComponentName(),"GoogleSearchPort");
		Assert.assertNull(tpc.getDisplayName());
		Assert.assertNull(tpc.getLargeIcon());
		Assert.assertNull(tpc.getSmallIcon());
		Assert.assertNull(tpc.getDisplayName());
		Assert.assertEquals(tpc.getServiceEndpointInterface(),"org.objectweb.wssample.gen.google.GoogleSearchPort");
		Assert.assertEquals(tpc.getServiceImplBean().getEjblink(),"GoogleBean");
		Assert.assertEquals(tpc.getWsdlPort().getNamespaceURI(),"urn:GoogleSearch");
		Assert.assertEquals(tpc.getWsdlPort().getNamespaceURI(),"GoogleSearchPort");
		
	}
}
