package org.apache.axismora.wsdl4ws;

import org.apache.axismora.wsdl2ws.WSDL2Ws;

import junit.framework.TestCase;

/**
 * @author hemapani
 */
public class WSDL2WsTest extends TestCase{
	private static final String OUT_PUT_LOCATION = "../GenaratedService/src";
	
	public WSDL2WsTest() {
		super();
	}

	public WSDL2WsTest(String arg0) {
		super(arg0);
	}
	
	public void testAllWSDLs()throws Exception{
		String[] filelist = new String[]{"samples/wsdls/general/echo.wsdl",
										"samples/wsdls/general/google.wsdl",
										"samples/wsdls/general/heavy.wsdl",
										"samples/wsdls/general/kumaran.wsdl",
										"samples/wsdls/general/shop.wsdl",
										"samples/wsdls/general/arrwrapper.wsdl",
										"samples/wsdls/general/HelloWorld.wsdl",
										"samples/wsdls/general/GetQuote.wsdl",
										"samples/wsdls/general/InteropTest.wsdl",
										"samples/wsdls/general/typeTest.wsdl",
										"samples/wsdls/general/Address.wsdl",
										"samples/wsdls/general/AddressBook.wsdl"};
		for(int i = 0; i<filelist.length;i++){
			System.out.println("!!!!!!!!!!!!!!!!!!testing "+filelist[i]);										
			WSDL2Ws.main(new String[]{filelist[i],"-o"+OUT_PUT_LOCATION,"-sboth","-ljava"});
		}											
	}
}
