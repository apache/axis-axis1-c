package types.usageTests;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class SupportedTypesTestService extends org.apache.axismora.handlers.BasicHandler {
	private types.usageTests.SupportedTypesTestImpl service;

	public SupportedTypesTestService(){
			service = new types.usageTests.SupportedTypesTestImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("echoSOAPStruct".equals(methodToCall))
				this.echoSOAPStruct(msgdata);
		
			else if("echoSOAPStructArray".equals(methodToCall))
				this.echoSOAPStructArray(msgdata);
		
			else if("echoInt".equals(methodToCall))
				this.echoInt(msgdata);
		
			else if("echoDouble".equals(methodToCall))
				this.echoDouble(msgdata);
		
			else if("echoLong".equals(methodToCall))
				this.echoLong(msgdata);
		
			else if("echoShort".equals(methodToCall))
				this.echoShort(msgdata);
		
			else if("echoFloat".equals(methodToCall))
				this.echoFloat(msgdata);
		
			else if("echoByte".equals(methodToCall))
				this.echoByte(msgdata);
		
			else if("echoBoolean".equals(methodToCall))
				this.echoBoolean(msgdata);
		
			else if("echoIntArray".equals(methodToCall))
				this.echoIntArray(msgdata);
		
			else if("echoDoubleArray".equals(methodToCall))
				this.echoDoubleArray(msgdata);
		
			else if("echoLongArray".equals(methodToCall))
				this.echoLongArray(msgdata);
		
			else if("echoShortArray".equals(methodToCall))
				this.echoShortArray(msgdata);
		
			else if("echoFloatArray".equals(methodToCall))
				this.echoFloatArray(msgdata);
		
			else if("echoByteArray".equals(methodToCall))
				this.echoByteArray(msgdata);
		
			else if("echoBooleanArray".equals(methodToCall))
				this.echoBooleanArray(msgdata);
		
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

	public void echoSOAPStruct(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.SOAPStruct paramIn0 =  new  types.usageTests.SOAPStruct();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.echoSOAPStruct(paramIn0));
	}

	public void echoSOAPStructArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.ArrayOfSOAPStruct temp0 =  new  types.usageTests.ArrayOfSOAPStruct();
		temp0.desierialize(msgdata);
		types.usageTests.SOAPStruct[] paramIn0= temp0.getParam();
		types.usageTests.ArrayOfSOAPStruct ar = new types.usageTests.ArrayOfSOAPStruct();		ar.setParam(service.echoSOAPStructArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoInt(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoInt(paramIn0)));
	}

	public void echoDouble(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		double paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.DoubleParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.DoubleParam(service.echoDouble(paramIn0)));
	}

	public void echoLong(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		long paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.LongParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.LongParam(service.echoLong(paramIn0)));
	}

	public void echoShort(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		short paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.ShortParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.ShortParam(service.echoShort(paramIn0)));
	}

	public void echoFloat(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		float paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.FloatParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.FloatParam(service.echoFloat(paramIn0)));
	}

	public void echoByte(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		byte paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.ByteParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.ByteParam(service.echoByte(paramIn0)));
	}

	public void echoBoolean(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		boolean paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.BooleanParam(service.echoBoolean(paramIn0)));
	}

	public void echoIntArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.ArrayOf_xsd_int temp0 =  new  types.usageTests.ArrayOf_xsd_int();
		temp0.desierialize(msgdata);
		int[] paramIn0= temp0.getParam();
		types.usageTests.ArrayOf_xsd_int ar = new types.usageTests.ArrayOf_xsd_int();		ar.setParam(service.echoIntArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoDoubleArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.ArrayOf_xsd_double temp0 =  new  types.usageTests.ArrayOf_xsd_double();
		temp0.desierialize(msgdata);
		double[] paramIn0= temp0.getParam();
		types.usageTests.ArrayOf_xsd_double ar = new types.usageTests.ArrayOf_xsd_double();		ar.setParam(service.echoDoubleArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoLongArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.ArrayOf_xsd_long temp0 =  new  types.usageTests.ArrayOf_xsd_long();
		temp0.desierialize(msgdata);
		long[] paramIn0= temp0.getParam();
		types.usageTests.ArrayOf_xsd_long ar = new types.usageTests.ArrayOf_xsd_long();		ar.setParam(service.echoLongArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoShortArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.ArrayOf_xsd_short temp0 =  new  types.usageTests.ArrayOf_xsd_short();
		temp0.desierialize(msgdata);
		short[] paramIn0= temp0.getParam();
		types.usageTests.ArrayOf_xsd_short ar = new types.usageTests.ArrayOf_xsd_short();		ar.setParam(service.echoShortArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoFloatArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.ArrayOf_xsd_float temp0 =  new  types.usageTests.ArrayOf_xsd_float();
		temp0.desierialize(msgdata);
		float[] paramIn0= temp0.getParam();
		types.usageTests.ArrayOf_xsd_float ar = new types.usageTests.ArrayOf_xsd_float();		ar.setParam(service.echoFloatArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoByteArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam paramIn0 =  new  org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam(msgdata);		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam(service.echoByteArray(paramIn0)));
	}

	public void echoBooleanArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		types.usageTests.ArrayOf_xsd_boolean temp0 =  new  types.usageTests.ArrayOf_xsd_boolean();
		temp0.desierialize(msgdata);
		boolean[] paramIn0= temp0.getParam();
		types.usageTests.ArrayOf_xsd_boolean ar = new types.usageTests.ArrayOf_xsd_boolean();		ar.setParam(service.echoBooleanArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

}
