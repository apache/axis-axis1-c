package samples.jaxrpc.address;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class AddressServiceService extends org.apache.axismora.handlers.BasicHandler {
	private samples.jaxrpc.address.AddressServiceImpl service;

	public AddressServiceService(){
			service = new samples.jaxrpc.address.AddressServiceImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("updateAddress".equals(methodToCall))
				this.updateAddress(msgdata);
		
			else  throw new AxisFault("method not found");
		}catch(AxisFault e){
			e.printStackTrace();
				msgdata.setSoapFault(new SOAPFault(e));
		}
		catch(Exception e){
			e.printStackTrace();
				msgdata.setSoapFault(new SOAPFault(new AxisFault("error at wrapper invoke",e)));
		}
	}

	public void updateAddress(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		samples.jaxrpc.address.AddressBean paramIn0 =  new  samples.jaxrpc.address.AddressBean();
		paramIn0.desierialize(msgdata);
		int paramIn1 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.StringParam(service.updateAddress(paramIn0,paramIn1)));
	}

}
