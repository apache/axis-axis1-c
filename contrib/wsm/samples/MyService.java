import javax.jws.*;
import javax.jws.soap.*;

@WebService(
        targetNamespace="http://ws.apache.org/axis/"
            )
@SOAPBinding(
        style=SOAPBinding.Style.RPC,
        use = SOAPBinding.Use.ENCODED
        )
public class MyService {
	@WebMethod
	public void doSomething() {
		
	}
	
	public void doNotSomething() {
		
	}
}
