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

import junit.framework.Test;
import junit.framework.TestSuite;

import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2EEwithWSDL;

/**
 * Unit test for simple App.
 *
 * @author <a href="mailto:jason@zenplex.com">Jason van Zyl</a>
 */
public class GenerateTest 
	extends AbstractTestCase
{
	private String outDir = "target/generated/samples/";
	/**
	 * Create the test case
	 *
	 * @param testName name of the test case
	 */
	public GenerateTest( String testName )
	{
		super( testName );
	}

	/**
	 * @return the suite of tests being tested
	 */
	public static Test suite()
	{
		return new TestSuite( GenerateTest.class );
	}


	public void testBookSample() throws Exception
	{
		//client side
		String args[] = new String[]{getTestFile("src/samples/jaxrpc/book/webservice.xml"),
									 "-o" + getTestFile(outDir+"withWSDL/client/book"),"-R"};
		Ws4J2EEwithWSDL.main(args);
		//server side
		String args1[] = new String[]{getTestFile("src/samples/jaxrpc/book/webservice.xml"),
									 "-o" + getTestFile(outDir+"withWSDL/server/book"),"--server-side","-R"};
		Ws4J2EEwithWSDL.main(args1);
        
//			String[] args2 = new String[]{"-o"+outDir+"withoutWSDL/server/META-INF/book1.wsdl" ,"-l" ,"http://127.0.0.1/ws4j2ee/","com.jwsbook.jaxrpc.BookQuote"};
//			Ws4J2EEwithoutWSDL.main(args2);
	}

	public void testTimeSample() throws Exception{
		String args[] = new String[]{getTestFile("src/samples/jaxrpc/time/webservices.xml"),
									 "-o" + getTestFile(outDir+"withWSDL/client/time"),"-R"};
		Ws4J2EEwithWSDL.main(args);
		
		args = new String[]{getTestFile("src/samples/jaxrpc/time/webservices.xml"),
											 "-o" + getTestFile(outDir+"withWSDL/server/time"),"--server-side","-R"};
		Ws4J2EEwithWSDL.main(args);
	}
	
	public void testZipSample() throws Exception{
			String args[] = new String[]{getTestFile("src/samples/mapper/frenchzip/webservices.xml"),
										 "-o" + getTestFile(outDir+"withWSDL/client/zip"),"-R"};
			Ws4J2EEwithWSDL.main(args);
		
			args = new String[]{getTestFile("src/samples/mapper/frenchzip/webservices.xml"),
												 "-o" + getTestFile(outDir+"withWSDL/server/zip"),"--server-side","-R"};
			Ws4J2EEwithWSDL.main(args);
	}
	public void testGoogleSample() throws Exception{
				String args[] = new String[]{getTestFile("src/samples/mapper/google/webservices.xml"),
											 "-o" + getTestFile(outDir+"withWSDL/client/google"),"-R"};
				Ws4J2EEwithWSDL.main(args);
		
				args = new String[]{getTestFile("src/samples/mapper/google/webservices.xml"),
													 "-o" + getTestFile(outDir+"withWSDL/server/google"),"--server-side","-R"};
				Ws4J2EEwithWSDL.main(args);
	}	
	
	
}
