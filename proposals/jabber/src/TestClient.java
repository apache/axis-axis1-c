import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;
import javax.xml.rpc.encoding.XMLType;

import org.apache.axis.client.Call;
import org.apache.axis.client.Service;
import org.apache.axis.configuration.XMLStringProvider;

import com.snellspace.axis.jabber.JabberConnection;
import com.snellspace.axis.jabber.JabberTransport;

/**
 * @author James M Snell <jasnell@us.ibm.com>
 */
public class TestClient {

  private static final String dep = 
    "<deployment name=\"defaultClientConfig\"" +
    "            xmlns=\"http://xml.apache.org/axis/wsdd/\"" +
    "            xmlns:java=\"http://xml.apache.org/axis/wsdd/providers/java\">" +
    " <transport name=\"JabberSender\" pivot=\"java:com.snellspace.axis.jabber.JabberSender\" />" +
    "</deployment>";
    
  private static void client() throws Exception {
    JabberTransport transport = new JabberTransport();
    transport.setTo("JamesMSnell@jabber.org/service1");    
    Service service = new Service(new XMLStringProvider(dep));
    Call call = (Call)service.createCall();
    call.setOperationName(new QName("urn:test", "echo"));
    call.addParameter("a", XMLType.XSD_STRING, ParameterMode.IN);
    call.setReturnType(XMLType.XSD_STRING);
    call.setTransport(transport);
    call.setUsername("JamesMSnell2@jabber.org/service2");
    call.setPassword("knight12");
    String s = (String)call.invoke(new String[] {"test"});
    System.out.println(s);
  }

  public static void main(
    String[] args) 
      throws Exception {
        //JabberConnection.DEBUG = true;
        client();
  }
}
