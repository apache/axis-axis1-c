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
