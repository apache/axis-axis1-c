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

import junit.framework.TestCase;
import junit.framework.TestSuite;

import org.apache.axismora.deployment.wsdd.WSDDDeploymentTest;
import org.apache.axismora.encoding.DeserializationMethodsTest;
import org.apache.axismora.encoding.DesirializationContextTest;
import org.apache.axismora.encoding.ElementSerializerTest;
import org.apache.axismora.encoding.ResultSerializationTest;
import org.apache.axismora.encoding.SerializingTest;
import org.apache.axismora.encoding.XMLPullTest;
import org.apache.axismora.engine.AxisEngineTest;
import org.apache.axismora.engine.SOAPFaultTest;
import org.apache.axismora.soap.MeassageDataTest;
import org.apache.axismora.utils.CLArgPArserTest;
import org.apache.axismora.utils.UtilsTest;
import org.apache.axismora.wsdl4ws.Node2AttibutesTest;

/**
 * @author hemapani
 */

public class AllTests extends TestCase{
	public static void main (String[] args) {
			junit.textui.TestRunner.run (suite());
	}

	public AllTests(String name){
		super(name);	
	}	
	
	public static junit.framework.Test suite(){
		   TestSuite suite = new TestSuite("All tests");		     
		   //suite.addTestSuite(ServicePoolTest.class);
		   suite.addTestSuite(WSDDDeploymentTest.class);
		   suite.addTestSuite(DeserializationMethodsTest.class);
		   suite.addTestSuite(DesirializationContextTest.class);
		   suite.addTestSuite(ElementSerializerTest.class);
		   suite.addTestSuite(ResultSerializationTest.class);
		   suite.addTestSuite(XMLPullTest.class);
		   suite.addTestSuite(SerializingTest.class);
		   suite.addTestSuite(AxisEngineTest.class);
		   //suite.addTestSuite(BasicHandlerPoolTest.class);
		   suite.addTestSuite(SOAPFaultTest.class);
		   //suite.addTestSuite(AdminServiceTest.class);
		   suite.addTestSuite(MeassageDataTest.class);
		   suite.addTestSuite(CLArgPArserTest.class);
		   suite.addTestSuite(UtilsTest.class);
		   suite.addTestSuite(Node2AttibutesTest.class);
		   suite.addTestSuite(Node2AttibutesTest.class);

		   return suite;
	}   
}
