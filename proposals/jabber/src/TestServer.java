
public class TestServer {

  public String echo(String arg) {

    StringBuffer buf = new StringBuffer(arg);
    return buf.reverse().toString();
    
  }

}
