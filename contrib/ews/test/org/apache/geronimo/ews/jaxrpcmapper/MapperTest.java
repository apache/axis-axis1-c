package org.apache.geronimo.ews.jaxrpcmapper;

import junit.framework.Test;
import junit.framework.TestSuite;

import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.jaxrpcmapping.WsdlToJ2ee;

/**
 * Unit test for simple App.
 *
 * @author <a href="mailto:jason@zenplex.com">Jason van Zyl</a>
 */
public class MapperTest 
	extends AbstractTestCase
{
	/**
	 * Create the test case
	 *
	 * @param testName name of the test case
	 */
	public MapperTest( String testName )
	{
		super( testName );
	}

	/**
	 * @return the suite of tests being tested
	 */
	public static Test suite()
	{
		TestSuite sute = new TestSuite(); 
		sute.addTest(TestSuite.createTest(MapperTest.class,"testHeavyWeight"));
		sute.addTest(TestSuite.createTest(MapperTest.class,"testLightWeight"));
		sute.addTest(TestSuite.createTest(MapperTest.class,"testGoogle"));
		sute.addTest(TestSuite.createTest(MapperTest.class,"testFrenchZip"));
		//sute.addTest(TestSuite.createTest(MapperTest.class,"testAnonymousTypes"));
		return sute;
	}


	/**
	 * Rigourous Test :-)
	 */
	public void testHeavyWeight() throws Exception {
		String args[] = new String[]{"-m", getTestFile(sampleDir +"mapper/heavyweight/BookQuote.xml"),
									 "-o", getTestFile("target/generated/samples/mapper/heavyweight"),
									 getTestFile(sampleDir +"mapper/heavyweight/BookQuote.wsdl")};
		WsdlToJ2ee.main(args);
	}

	public void testLightWeight() throws Exception {
		String args[] = new String[]{"-m", getTestFile(sampleDir +"mapper/lightweight/BookQuote.xml"),
									 "-o", getTestFile("target/generated/samples/mapper/lightweight"),
									 getTestFile(sampleDir +"mapper/lightweight/BookQuote.wsdl")};
		WsdlToJ2ee.main(args);
	}

	public void testGoogle() throws Exception {
		String args[] = new String[]{"-m",getTestFile(sampleDir +"mapper/google/GoogleSearch.xml"),
									 "-o", getTestFile("target/generated/samples/mapper/google"),
									 getTestFile(sampleDir +"mapper/google/GoogleSearch.wsdl")};
		WsdlToJ2ee.main(args);
	}

	public void testFrenchZip() throws Exception {
		String args[] = new String[]{"-m",getTestFile(sampleDir +"mapper/frenchzip/FrenchZipMapping.xml"),
									 "-o", getTestFile("target/generated/samples/mapper/frenchzip"),
									 getTestFile(sampleDir +"mapper/frenchzip/FrenchZip.wsdl")};
		WsdlToJ2ee.main(args);
	}

	  public void testAnonymousTypes() throws Exception {
		  String args[] = new String[]{"-m",getTestFile(sampleDir +"mapper/anonymous/mapping.xml"),
									   "-o", getTestFile("target/generated/samples/mapper/anonymous"),
									   getTestFile(sampleDir +"mapper/anonymous/anonymous.wsdl")};
		  WsdlToJ2ee.main(args);
	  }
}
