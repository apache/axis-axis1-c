package org.apache.geronimo.ews.ws4j2ee;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.AppTest;
import org.apache.geronimo.ews.ws4j2ee.toWs.Ws4J2EEwithWSDL;

/**
 * Unit test for simple App.
 *
 * @author <a href="mailto:jason@zenplex.com">Jason van Zyl</a>
 */
public class GenerateTest 
	extends AbstractTestCase
{
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
									 "-o" + getTestFile("target/generated/gencode/server/book")};
		Ws4J2EEwithWSDL.main(args);
		//server side
		String args1[] = new String[]{getTestFile("src/samples/jaxrpc/book/webservice.xml"),
									 "-o" + getTestFile("target/generated/gencode/server/book"),"--server-side"};
		Ws4J2EEwithWSDL.main(args);
		
		//genarate the code when WSDL is not avalible, this do not work with the new
			  //axis code ... still do not get what is the problem.
//			  java.lang.NullPointerException
//				  at org.apache.axis.wsdl.fromJava.Types.getTypeQName(Types.java:688)
//				  at org.apache.axis.wsdl.fromJava.Types.writeTypeForPart(Types.java:420)
//				  at org.apache.axis.wsdl.fromJava.Emitter.writePartToMessage(Emitter.java:1854)
//				  at org.apache.axis.wsdl.fromJava.Emitter.writeFaultMessage(Emitter.java:1783)
//				  at org.apache.axis.wsdl.fromJava.Emitter.writeMessages(Emitter.java:1130)
//				  at org.apache.axis.wsdl.fromJava.Emitter.writePortType(Emitter.java:1066)
//				  at org.apache.axis.wsdl.fromJava.Emitter.getWSDL(Emitter.java:499)
//				  at org.apache.axis.wsdl.fromJava.Emitter.emit(Emitter.java:350)
//				  at org.apache.axis.wsdl.fromJava.Emitter.emit(Emitter.java:445)
//		 nothing to do with ws4j2ee as the run with the java2WSDL gives the same error.
//		have to check with new checkout ... or this a bug at Axis 
        
//				String[] args2 = new String[]{"-otarget/generated/withoutWSDL/server/META-INF/book1.wsdl" ,"-l" ,"http://127.0.0.1/ws4j2ee/","com.jwsbook.jaxrpc.BookQuote"};
//			  Ws4J2EEwithoutWSDL.main(args2);
	}

	public void testTimeSample() throws Exception
	{
		String args[] = new String[]{getTestFile("src/samples/jaxrpc/time/webservices.xml"),
									 "-o" + getTestFile("target/generated/gencode/server/time")};
		Ws4J2EEwithWSDL.main(args);
	}
}
