package addressFetcher2;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class AddressBookService extends org.apache.axismora.handlers.BasicHandler {
	private addressFetcher2.AddressBookImpl service;

	public AddressBookService(){
			service = new addressFetcher2.AddressBookImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("addEntry".equals(methodToCall))
				this.addEntry(msgdata);
		
			else if("getAddressFromName".equals(methodToCall))
				this.getAddressFromName(msgdata);
		
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

	public void addEntry(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		addressFetcher2.Address paramIn1 =  new  addressFetcher2.Address();
		paramIn1.desierialize(msgdata);
		 service.addEntry(paramIn0,paramIn1);
	}

	public void getAddressFromName(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(service.getAddressFromName(paramIn0));
	}

}
