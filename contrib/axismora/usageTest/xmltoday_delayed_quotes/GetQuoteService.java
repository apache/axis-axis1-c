package xmltoday_delayed_quotes;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class GetQuoteService extends org.apache.axismora.handlers.BasicHandler {
	private xmltoday_delayed_quotes.GetQuoteImpl service;

	public GetQuoteService(){
			service = new xmltoday_delayed_quotes.GetQuoteImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("getQuote".equals(methodToCall))
				this.getQuote(msgdata);
		
			else if("test".equals(methodToCall))
				this.test(msgdata);
		
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

	public void getQuote(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.FloatParam(service.getQuote(paramIn0)));
	}

	public void test(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.StringParam(service.test()));
	}

}
