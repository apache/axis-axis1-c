package userguide.example3;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class ArrayCalcService extends org.apache.axismora.handlers.BasicHandler {
	private userguide.example3.ArrayCalcImpl service;

	public ArrayCalcService(){
			service = new userguide.example3.ArrayCalcImpl();
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
		userguide.example3.Point[] in0;
		userguide.example3.ArrayOf_tns2_Point arrayT0 = (new userguide.example3.ArrayOf_tns2_Point());
		arrayT0.desierialize(msgdata);
		in0 = arrayT0.getParam();
		userguide.example3.Point[] in1;
		userguide.example3.ArrayOf_tns2_Point arrayT1 = (new userguide.example3.ArrayOf_tns2_Point());
		arrayT1.desierialize(msgdata);
		in1 = arrayT1.getParam();
		userguide.example3.Point[] result = service.addArray(in0,in1);
		userguide.example3.ArrayOf_tns2_Point ar = new userguide.example3.ArrayOf_tns2_Point();		ar.setParam(result);
		msgdata.setSoapBodyContent(ar);
	}

	public void addStringArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		userguide.example3.Point[] in0;
		userguide.example3.ArrayOf_tns2_Point arrayT0 = (new userguide.example3.ArrayOf_tns2_Point());
		arrayT0.desierialize(msgdata);
		in0 = arrayT0.getParam();
		userguide.example3.Point[] in1;
		userguide.example3.ArrayOf_tns2_Point arrayT1 = (new userguide.example3.ArrayOf_tns2_Point());
		arrayT1.desierialize(msgdata);
		in1 = arrayT1.getParam();
		userguide.example3.Point[] result = service.addStringArray(in0,in1);
		userguide.example3.ArrayOf_tns2_Point ar = new userguide.example3.ArrayOf_tns2_Point();		ar.setParam(result);
		msgdata.setSoapBodyContent(ar);
	}

	public void echoArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		userguide.example3.Point[] in0;
		userguide.example3.ArrayOf_tns2_Point arrayT0 = (new userguide.example3.ArrayOf_tns2_Point());
		arrayT0.desierialize(msgdata);
		in0 = arrayT0.getParam();
		userguide.example3.Point[] result = service.echoArray(in0);
		userguide.example3.ArrayOf_tns2_Point ar = new userguide.example3.ArrayOf_tns2_Point();		ar.setParam(result);
		msgdata.setSoapBodyContent(ar);
	}

}
