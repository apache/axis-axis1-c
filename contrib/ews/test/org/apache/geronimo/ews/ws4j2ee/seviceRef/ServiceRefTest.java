package org.apache.geronimo.ews.ws4j2ee.seviceRef;

import java.io.FileInputStream;

import junit.framework.Assert;

import org.apache.geronimo.ews.AbstractTestCase;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferance;
import org.apache.geronimo.ews.ws4j2ee.parsers.ServiceReferanceParser;

/**
 * @author hemapani
 */
public class ServiceRefTest extends AbstractTestCase{
	/**
	 * @param testName
	 */
	public ServiceRefTest(String testName) {
		super(testName);
	}

	public void testRefFile1() throws Exception{
		try {
			ServiceReferanceParser parser 
				= new ServiceReferanceParser(new FileInputStream(
					getTestFile(testDir+"org/apache/geronimo/ews/" +
						"ws4j2ee/seviceRef/service-ref1.xml")));
			ServiceReferance ref = 	parser.getRef();
			Assert.assertEquals("service/Joe",ref.getServicerefName());
			Assert.assertEquals("javax.xml.rpc.Service",ref.getServiceInterface());
			Assert.assertEquals("WEB-INF/joe.xml",ref.getJaxrpcmappingFile());
			//System.out.println(ref.getJaxrpcmappingFile());
			Assert.assertEquals("WEB-INF/joe.wsdl",ref.getWsdlFile());
		} catch (Exception e) {
			e.printStackTrace();
		   throw e;
		}
	}
	public void testRefFile2() throws Exception{
		try {
			ServiceReferanceParser parser 
				= new ServiceReferanceParser(new FileInputStream(
					getTestFile(testDir+"org/apache/geronimo/ews/ws4j2ee/" +
						"seviceRef/service-ref2.xml")));
			ServiceReferance ref = 	parser.getRef();
			Assert.assertEquals("service/Joe",ref.getServicerefName());
			Assert.assertEquals("javax.xml.rpc.Service",ref.getServiceInterface());
			//System.out.println(ref.getJaxrpcmappingFile());
			Assert.assertEquals("WEB-INF/joe.xml",ref.getJaxrpcmappingFile());
			Assert.assertEquals("WEB-INF/joe.wsdl",ref.getWsdlFile());
		} catch (Exception e) {
			e.printStackTrace();
			throw e;
		}
	}
}
