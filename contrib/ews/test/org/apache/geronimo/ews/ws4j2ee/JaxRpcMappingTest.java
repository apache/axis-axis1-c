package org.apache.geronimo.ews.ws4j2ee;

import java.util.List;

import javax.wsdl.Operation;
import javax.xml.namespace.QName;

import junit.framework.Assert;
import junit.framework.TestCase;

import org.apache.axis.wsdl.symbolTable.BindingEntry;
import org.apache.axis.wsdl.symbolTable.PortEntry;
import org.apache.axis.wsdl.symbolTable.PortTypeEntry;
import org.apache.axis.wsdl.symbolTable.ServiceEntry;
import org.apache.geronimo.ews.jaxrpcmapping.J2eeEmitter;
import org.apache.geronimo.ews.jaxrpcmapping.JaxRpcMapper;
import org.apache.geronimo.ews.ws4j2ee.context.ContextFactory;
import org.apache.geronimo.ews.ws4j2ee.context.JaxRpcMapperContext;
import org.apache.geronimo.ews.ws4j2ee.context.wsdl.WSDLContext;

/**
 * @author hemapani
 */
public class JaxRpcMappingTest extends TestCase{
	public void testGoogleTypeMapping() throws Exception{
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
	   PortTypeEntry pe = wscontext.getPortType(new QName("urn:GoogleSearch","GoogleSearchPort"));
	   JaxRpcMapper mapper = j2ee.getJaxRpcMapper();
	   JaxRpcMapperContext mc =ContextFactory.createJaxRpcMapperContext(new Object[]{mapper,j2ee});
	   Assert.assertNotNull(port);
	   Assert.assertNotNull(be);
	   Assert.assertNotNull(pe);
	   Assert.assertEquals(mc.getJavaType(new QName("urn:GoogleSearch","GoogleSearchResult")),"org.objectweb.wssample.gen.google.MyGoogleSearchResult");
	   Assert.assertEquals(mc.getJavaType(new QName("urn:GoogleSearch","ResultElementArray")),"org.objectweb.wssample.gen.google.ResultElement[]");
	}
	public void testBookTypeMapping() throws Exception{
	   String mappingfile = "src/samples/jaxrpc/book/BookQuote.xml";
	   String wsdlfile = "src/samples/jaxrpc/book/BookQuote.wsdl";
	   J2eeEmitter j2ee = new J2eeEmitter();
	   j2ee.setMappingFilePath(mappingfile);
	   j2ee.setOutputDir("temp");
	   j2ee.setServerSide(true);
	   j2ee.setVerbose(true);
	   j2ee.setHelperWanted(true);
	   System.out.println();
	   j2ee.runServerSide(wsdlfile);
	   WSDLContext wscontext = ContextFactory.createWSDLContext(j2ee.getSymbolTable());
	   PortEntry port = wscontext.getPort(new QName("BookQuotePort"));
	   BindingEntry be = wscontext.getBinding(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","BookQuoteBinding"));
	   PortTypeEntry pe = wscontext.getPortType(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","BookQuote"));
	   ServiceEntry se = wscontext.getService(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","BookQuoteService"));
	   JaxRpcMapper mapper = j2ee.getJaxRpcMapper();
	   JaxRpcMapperContext mc =ContextFactory.createJaxRpcMapperContext(new Object[]{mapper,j2ee});
	   Assert.assertNotNull(port);
	   Assert.assertNotNull(be);
	   Assert.assertNotNull(pe);
	   Assert.assertEquals(mc.getExceptionType(new QName("http://www.Monson-Haefel.com/jwsbook/BookQuote","InvalidIsbnFault")),"com.jwsbook.jaxrpc.InvalidIsbnException");
	   
	   String sei = mc.getServiceEndpointInterfaceName(pe,be);
	   Assert.assertEquals(sei,"com.jwsbook.jaxrpc.BookQuote");
	   String si = mc.getServiceInterfaceName(se);
	   Assert.assertEquals(si,"com.jwsbook.jaxrpc.BookQuoteService");
	   List l = pe.getPortType().getOperations();
	   Operation op = (Operation)l.get(0);
	   Assert.assertEquals(mc.getJavaMethodName(be,op),"getBookPrice");
	   Assert.assertEquals(mc.getJavaMethodParamType(be,op,0,null),"java.lang.String");
	   Assert.assertEquals(mc.getJavaMethodReturnType(be,op),"float");  
	}

}
