import java.io.ByteArrayInputStream;

import javax.xml.namespace.QName;
import javax.xml.rpc.ParameterMode;
import javax.xml.rpc.encoding.XMLType;

import org.apache.axis.client.AdminClient;
import org.apache.axis.client.Call;
import org.apache.axis.client.Service;
import org.apache.axis.configuration.XMLStringProvider;
import org.apache.axis.server.AxisServer;
import org.apache.axis.transport.local.LocalTransport;

import com.snellspace.axis.jabber.*;


public class Test {

  private static final String dep = 
    "<deployment name=\"defaultClientConfig\"" +
    "            xmlns=\"http://xml.apache.org/axis/wsdd/\"" +
    "            xmlns:java=\"http://xml.apache.org/axis/wsdd/providers/java\">" +
    " <transport name=\"JabberSender\" pivot=\"java:com.snellspace.axis.jabber.JabberSender\" />" +
    "</deployment>";
  private static final String serv =
    "<deployment xmlns=\"http://xml.apache.org/axis/wsdd/\""+
    "  xmlns:java=\"http://xml.apache.org/axis/wsdd/providers/java\">"+
    "  <service name=\"service1\" provider=\"java:RPC\">"+
    "    <namespace>urn:test</namespace>" +
    "    <parameter name=\"className\" value=\"TestServer\"/>"+
    "    <parameter name=\"allowedMethods\" value=\"*\"/>"+
    "  </service>"+
    "</deployment>";
  private static final String userv =
    "<undeployment xmlns=\"http://xml.apache.org/axis/wsdd/\">"+
    "  <service name=\"service1\" />"+
    "</undeployment>";

  public static void main(String[] args) throws Exception {
    JabberConnection.DEBUG = true;
    deploy();
    JabberServer service1 = server();
    client();
    undeploy();
    service1.disconnect();
  }

  public static JabberServer server() {
    return 
      new JabberServer(
        "JamesMSnell@jabber.org/service1", "knight12");
  }

  public static void deploy() 
    throws Exception {
      AxisServer server = (AxisServer)JabberServer.getAxisEngine();
      LocalTransport transport = new LocalTransport(server);
      transport.setRemoteService("AdminService");
      AdminClient client = new AdminClient();
      Call call = client.getCall();
      call.setTransport(transport);
      client.process(new ByteArrayInputStream(serv.getBytes()));
      server.refreshGlobalOptions();
  }

  public static void undeploy() 
    throws Exception {
      AxisServer server = (AxisServer)JabberServer.getAxisEngine();
      LocalTransport transport = new LocalTransport(server);
      transport.setRemoteService("AdminService");
      AdminClient client = new AdminClient();
      Call call = client.getCall();
      call.setTransport(transport);
      client.process(new ByteArrayInputStream(userv.getBytes()));
      server.refreshGlobalOptions();
  }

  private static void client() throws Exception {
    
    JabberTransport transport = new JabberTransport();
    transport.setTo("JamesMSnell@jabber.org/service1");
    
    Service service = new Service(new XMLStringProvider(dep));
    Call call = (Call)service.createCall();
    call.setOperationName(new QName("urn:test", "echo"));
    call.addParameter("a", XMLType.XSD_STRING, ParameterMode.IN);
    call.setReturnType(XMLType.XSD_STRING);
    //call.setReturnQName(new QName("arg", "urn:test"));
    call.setTransport(transport);
    call.setUsername("JamesMSnell2@jabber.org/service2");
    call.setPassword("knight12");
    
    String s = (String)call.invoke(new String[] {"test"});
    System.out.println(s);
  }
}
