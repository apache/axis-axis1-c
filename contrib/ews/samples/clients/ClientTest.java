
import java.io.File;
import java.net.MalformedURLException;
import java.net.URL;
import java.rmi.RemoteException;

import javax.xml.rpc.ServiceException;

import junit.framework.TestCase;

import org.apache.ws.echosample.Echo;
import org.apache.ws.echosample.EchoServiceLocator;
import org.apache.ws.echosample.EchoStruct;

import com.jwsbook.jaxrpc.BookQuote;
import com.jwsbook.jaxrpc.BookQuoteServiceLocator;


public class ClientTest extends TestCase{
	public void testClients() throws Exception{
		try{
//			File file = new File("./conf/wsdd/client/secuirty-client-config.wsdd");
//			if(!file.exists())
//				throw new RuntimeException();
			System.setProperty("axis.ClientConfigFile",file.getAbsolutePath());
			BookQuoteServiceLocator locater = new BookQuoteServiceLocator();
			BookQuote port = locater.getBookQuotePort(new URL("http://127.0.0.1:5555/axis/services/BookQuotePort"));
			System.out.println("return value is "+port.getBookPrice("hello"));
			
			EchoServiceLocator elocator = new EchoServiceLocator();
			Echo eport = elocator.getechoPort(new URL("http://127.0.0.1:5555/axis/services/echoPort"));
			
			boolean booleanValue = true;
			double doubleValue = 124565;
			byte[] bytes = "hello".getBytes();
			float floatValue = 245235f;
			int intValue = 234;
			long longValue = 23453536;
			short shortvalue = new Short("23").shortValue();
			EchoStruct struct = new EchoStruct();
			struct.setStrVal("Hi");  
			
			assertEquals(eport.echoBoolean(true),true);
			assertEquals(eport.echoDouble(doubleValue),doubleValue,2);
			System.out.println(eport.echoBytes(bytes));
			assertTrue(eport.echoFloat(floatValue) == floatValue);
			assertEquals(eport.echoInt(intValue),intValue);
			assertEquals(eport.echoLong(longValue),longValue);
			assertEquals(eport.echoStruct(struct),struct);
			assertEquals(eport.echoShort(shortvalue),shortvalue);
		}catch(Exception e){
			e.printStackTrace();
			throw e;
		}	
	}
}
