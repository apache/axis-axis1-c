package heavytest.performence;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class HeavyTestService extends org.apache.axismora.handlers.BasicHandler {
	private heavytest.performence.HeavyTestImpl service;

	public HeavyTestService(){
			service = new heavytest.performence.HeavyTestImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("test".equals(methodToCall))
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

	public void test(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		heavytest.performence.DetailsArray temp0 =  new  heavytest.performence.DetailsArray();
		temp0.desierialize(msgdata);
		heavytest.performence.Details[] paramIn0= temp0.getParam();
		heavytest.performence.DetailsArray ar = new heavytest.performence.DetailsArray();		ar.setParam(service.test(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

}
