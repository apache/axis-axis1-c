import org.apache.axis.metadata.annotation.*;

@Protocol(soapStyle=EncodingType.DOCUMENT_LITERAL)
@TargetNamespace("http://ws.apache.org/axis/")
@ServiceLocation("http://localhost:8080/axis/services/MyService")
@WsdlFile("MyService.wsdl")
public class MyService {
	@Operation
	public void doSomething() {
		
	}
	
	public void doNotSomething() {
		
	}
}
