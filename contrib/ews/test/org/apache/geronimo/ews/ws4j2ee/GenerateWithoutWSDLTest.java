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

import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2ee;

/**
 * this test case with wsdl does not exists .. but the information is get by the 
 * SEI. This should be the prefered way for the J2EE developer. User can give a 
 * packaged application as explained by the JSR109 specification to the tool.
 * the arguments are 
 * 	GenerateWithoutWSDL &lt;webservice.xml-file&gt; -o&lt;targetoutput&gt; &lt;additionl argument that are given toJava2WSDL&gt;   
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class GenerateWithoutWSDLTest extends AbstractTestCase {
	private String outDir = "target/generated/samples/";
    /**
     * @param testName
     */
    public GenerateWithoutWSDLTest(String testName) {
        super(testName);
    }

	public void testMathSample() throws Exception{
		try{
			String[] args2 = new String[]{
				getTestFile(testDir+"testData/math/webservice.xml"),"-o",
				outDir+"withoutWSDL/math/server" ,"-l" ,
				"http://127.0.0.1/aixs/math"};
			Ws4J2ee.main(args2);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
	public void testServletBasedMathSample() throws Exception{
		String[] args2 = new String[]{
			getTestFile(testDir + "testData/math/webservice-ServletBased.xml"),"-o",
			outDir+"withoutWSDL/math/server-servlet" ,"-l" ,
			"http://127.0.0.1/aixs/math"};
		Ws4J2ee.main(args2);
	}
	public void testMathSampleWithHandlers() throws Exception{
		try{
			String[] args2 = new String[]{
				getTestFile(testDir + "testData/math/webservice-withHandler.xml"),"-o",
				outDir+"withoutWSDL/math-withHandlers/server" ,"-l" ,
				"http://127.0.0.1/aixs/math"};
			Ws4J2ee.main(args2);
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	public void testBookSampleJar() throws Exception{
		String[] args2 = new String[]{
			getTestFile("target/generated/samples/bookquote.jar"),"-o"
			,outDir+"withoutWSDL/bookquote-jar/"};
		Ws4J2ee.main(args2);
	}
	public void testGoogleSampleJar() throws Exception{
		String[] args2 = new String[]{
			getTestFile("target/generated/samples/google.jar"),"-o",
			outDir+"withoutWSDL/google-jar/"};
		Ws4J2ee.main(args2);
	}
	public void testTimeSampleJar() throws Exception{
		String[] args2 = new String[]{getTestFile("target/generated/samples/time.jar"),"-o",
			outDir+"withoutWSDL/time-jar/"};
		Ws4J2ee.main(args2);
	}
	public void testZipampleJar() throws Exception{
		String[] args2 = new String[]{getTestFile("target/generated/samples/zip.jar"),"-o",
			outDir+"withoutWSDL/zip-jar/"};
		Ws4J2ee.main(args2);
	}
	
	public void testBookSampleWar() throws Exception{
		String[] args2 = new String[]{getTestFile("target/generated/samples/simple.war"),"-o",
			outDir+"withoutWSDL/bookquote-war/"};
		Ws4J2ee.main(args2);
	}
	public void testBookSampleEar() throws Exception{
		String[] args2 = new String[]{
				getTestFile("target/generated/samples/bookquote.ear"),"-o",
				outDir+"withoutWSDL/bookquote-ear/"};
		Ws4J2ee.main(args2);
	}
	
	public void testEchoJar() throws Exception{
			String[] args2 = new String[]{
					getTestFile("target/generated/samples/echo.jar"),"-o",
					outDir+"withoutWSDL/echo-jar/"};
			Ws4J2ee.main(args2);
		}
}
