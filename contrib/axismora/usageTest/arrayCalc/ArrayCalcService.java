package arrayCalc;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class ArrayCalcService extends org.apache.axismora.handlers.BasicHandler {
	private arrayCalc.ArrayCalcImpl service;

	public ArrayCalcService(){
			service = new arrayCalc.ArrayCalcImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("addArray".equals(methodToCall))
				this.addArray(msgdata);
		
			else if("addStringArray".equals(methodToCall))
				this.addStringArray(msgdata);
		
			else if("echoArray".equals(methodToCall))
				this.echoArray(msgdata);
		
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

	public void addArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		arrayCalc.ArrayOf_tns2_Point temp0 =  new  arrayCalc.ArrayOf_tns2_Point();
		temp0.desierialize(msgdata);
		defaultNamespace.Point[] paramIn0= temp0.getParam();
		arrayCalc.ArrayOf_tns2_Point temp1 =  new  arrayCalc.ArrayOf_tns2_Point();
		temp1.desierialize(msgdata);
		defaultNamespace.Point[] paramIn1= temp1.getParam();
		arrayCalc.ArrayOf_tns2_Point ar = new arrayCalc.ArrayOf_tns2_Point();		ar.setParam(service.addArray(paramIn0,paramIn1));
		msgdata.setSoapBodyContent(ar);	}

	public void addStringArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		arrayCalc.ArrayOf_tns2_Point temp0 =  new  arrayCalc.ArrayOf_tns2_Point();
		temp0.desierialize(msgdata);
		defaultNamespace.Point[] paramIn0= temp0.getParam();
		arrayCalc.ArrayOf_tns2_Point temp1 =  new  arrayCalc.ArrayOf_tns2_Point();
		temp1.desierialize(msgdata);
		defaultNamespace.Point[] paramIn1= temp1.getParam();
		arrayCalc.ArrayOf_tns2_Point ar = new arrayCalc.ArrayOf_tns2_Point();		ar.setParam(service.addStringArray(paramIn0,paramIn1));
		msgdata.setSoapBodyContent(ar);	}

	public void echoArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		arrayCalc.ArrayOf_tns2_Point temp0 =  new  arrayCalc.ArrayOf_tns2_Point();
		temp0.desierialize(msgdata);
		defaultNamespace.Point[] paramIn0= temp0.getParam();
		arrayCalc.ArrayOf_tns2_Point ar = new arrayCalc.ArrayOf_tns2_Point();		ar.setParam(service.echoArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

}
