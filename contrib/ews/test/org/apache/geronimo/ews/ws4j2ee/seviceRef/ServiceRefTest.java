package org.apache.geronimo.ews.ws4j2ee.seviceRef;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import junit.framework.Assert;
import junit.framework.TestCase;

import org.apache.geronimo.ews.ws4j2ee.context.webservices.client.interfaces.ServiceReferance;
import org.apache.geronimo.ews.ws4j2ee.parsers.ServiceReferanceParser;
import org.apache.geronimo.ews.ws4j2ee.toWs.GenerationFault;

/**
 * @author hemapani
 */
public class ServiceRefTest extends TestCase{
	public void testRefFile1() throws FileNotFoundException, GenerationFault{
		ServiceReferanceParser parser 
			= new ServiceReferanceParser(new FileInputStream("src/test/org/apache/geronimo/ews/ws4j2ee/seviceRef/service-ref1.xml"));
		ServiceReferance ref = 	parser.getRef();
		Assert.assertEquals("service/Joe",ref.getServicerefName());
		Assert.assertEquals("javax.xml.rpc.Service",ref.getServiceInterface());
		Assert.assertEquals("WEB-INF/joe.xml",ref.getJaxrpcmappingFile());
		System.out.println(ref.getJaxrpcmappingFile());
		Assert.assertEquals("WEB-INF/joe.wsdl",ref.getWsdlFile());
	}
	public void testRefFile2() throws FileNotFoundException, GenerationFault{
		ServiceReferanceParser parser 
			= new ServiceReferanceParser(new FileInputStream("src/test/org/apache/geronimo/ews/ws4j2ee/seviceRef/service-ref2.xml"));
		ServiceReferance ref = 	parser.getRef();
		Assert.assertEquals("service/Joe",ref.getServicerefName());
		Assert.assertEquals("javax.xml.rpc.Service",ref.getServiceInterface());
		Assert.assertEquals("WEB-INF/joe.xml",ref.getJaxrpcmappingFile());
		System.out.println(ref.getJaxrpcmappingFile());
		Assert.assertEquals("WEB-INF/joe.wsdl",ref.getWsdlFile());
	}
}
