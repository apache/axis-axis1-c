package org.apache.geronimo.ews.ws4j2ee;

import org.apache.geronimo.ews.ws4j2ee.context.J2EEWebServiceContext;
import org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.context.MiscInfo;
import org.apache.geronimo.ews.ws4j2ee.context.impl.MiscInfoImpl;
import org.apache.geronimo.ews.ws4j2ee.context.webservices.server.interfaces.WSCFContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;
import org.apache.geronimo.ews.ws4j2ee.parsers.EJBDDParser;

/**
 * @author hemapani
 */
public class EJBDDTest {
	public void testGoogleSample(){
		J2EEWebServiceContext con = new J2EEWebServiceContext() {
			public WSDLContext getWSDLContext() {return null;}
			public void setWSDLContext(WSDLContext wsdlcontext) {}
			public WSCFContext getWSCFContext() {return null;}
			public void setWSCFContext(WSCFContext wscfcontext) {}
			public JaxRpcMapperContext getJAXRPCMappingContext() {return null;}
			public void setJAXRPCMappingContext(JaxRpcMapperContext context) {}
			public MiscInfo getMiscInfo() {return new MiscInfoImpl();}
			public void setMiscInfo(MiscInfo info) {}
			public void validate() {
			}
		};
	   EJBDDParser pars = new EJBDDParser(con);
	   //pars.parse("a file");
	   //Assert.assertEquals(con.getMiscInfo().getEjbName(),"Assert this for X"); 
	}
}
