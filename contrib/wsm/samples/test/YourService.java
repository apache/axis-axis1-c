package test;

import javax.jws.*;
import javax.jws.soap.*;

@WebService(
        targetNamespace="http://ws.apache.org/axis/"
            )
@SOAPBinding
public class YourService {
	@WebMethod
	public void doSomething() {
		
	}
	
	public void doNotSomething() {
		
	}
}
