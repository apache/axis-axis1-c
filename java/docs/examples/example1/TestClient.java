import org.apache.axis.client.ServiceClient;

public class TestClient
{
   public static void main(String [] args) throws Exception {
       String endpoint = "http://localhost:8080/axis/servlet/AxisServlet";
                //"http://nagoya.apache.org:5049/axis/servlet/AxisServlet";
     
     ServiceClient client = new ServiceClient(endpoint);
     String ret = (String)client.invoke("http://soapinterop.org/",
                                        "echoString",
                                        new Object [] { "Hello!" });
  
     System.out.println("Sent 'Hello!', got '" + ret + "'");
   }
}
