package org.apache.geronimo.ews.ws4j2ee;

import javax.xml.namespace.QName;

import junit.framework.Assert;

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortEntry;
import org.apache.geronimo.ews.jaxrpcmapping.J2eeEmitter;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;

/**
 * @author hemapani
 */
public class WSDLTest {
	public void testGoogleWSDL() throws Exception{
		   String mappingfile = "src/samples/mapper/google/GoogleSearch.xml";
		   String wsdlfile = "src/samples/mapper/google/GoogleSearch.wsdl";
		   J2eeEmitter j2ee = new J2eeEmitter();
		   j2ee.setMappingFilePath(mappingfile);
		   j2ee.setOutputDir("temp");
		   j2ee.setServerSide(true);
		   j2ee.setVerbose(true);
		   j2ee.setHelperWanted(true);
		   System.out.println();
		   j2ee.runServerSide(wsdlfile);
		   WSDLContext wscontext = ContextFactory.createWSDLContext(j2ee.getSymbolTable());
		   PortEntry port = wscontext.getPort(new QName("GoogleSearchPort"));
		   BindingEntry be = wscontext.getBinding(new QName("urn:GoogleSearch","GoogleSearchBinding"));
		   
		   Assert.assertEquals(wscontext.getTargetNSURI(),"urn:GoogleSearch");
		   Assert.assertNotNull(port);
		   Assert.assertNotNull(be);
		   Assert.assertNotNull(wscontext.getService(
				new QName("urn:GoogleSearch","GoogleSearchService")));
	}
}
