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
