package test;

import org.apache.axis.metadata.annotation.*;

@Protocol(soapStyle=EncodingType.DOCUMENT_LITERAL)
@TargetNamespace("http://ws.apache.org/axis/")
@ServiceLocation("http://localhost:8080/axis/services/MyService")
@WsdlFile("YourService.wsdl")
public class YourService {
	@Operation
	public void doSomething() {
		
	}
	
	public void doNotSomething() {
		
	}
}
