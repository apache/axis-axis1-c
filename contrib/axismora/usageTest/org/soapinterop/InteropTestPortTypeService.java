package org.soapinterop;
import org.apache.axis.AxisFault;
import org.apache.axis.message.SOAPFault;
/**
 * This Code is Genarated by the Wrapper Genarator. 
 * This Class act as the Wrapper to invoke the Webservice methods
*/
public class InteropTestPortTypeService extends org.apache.axismora.handlers.BasicHandler {
	private org.soapinterop.InteropTestPortTypeImpl service;

	public InteropTestPortTypeService(){
			service = new org.soapinterop.InteropTestPortTypeImpl();
	}

/*
	This method is called by the Wrapper. 
*/
	public void invoke(org.apache.axismora.MessageContext msgdata){
		 try{
			String methodToCall = msgdata.getMethodName().getLocalPart();
			if("echoString".equals(methodToCall))
				this.echoString(msgdata);
		
			else if("echoStringArray".equals(methodToCall))
				this.echoStringArray(msgdata);
		
			else if("echoInteger".equals(methodToCall))
				this.echoInteger(msgdata);
		
			else if("echoIntegerArray".equals(methodToCall))
				this.echoIntegerArray(msgdata);
		
			else if("echoFloat".equals(methodToCall))
				this.echoFloat(msgdata);
		
			else if("echoFloatArray".equals(methodToCall))
				this.echoFloatArray(msgdata);
		
			else if("echoStruct".equals(methodToCall))
				this.echoStruct(msgdata);
		
			else if("echoStructArray".equals(methodToCall))
				this.echoStructArray(msgdata);
		
			else if("echoVoid".equals(methodToCall))
				this.echoVoid(msgdata);
		
			else if("echoBase64".equals(methodToCall))
				this.echoBase64(msgdata);
		
			else if("echoHexBinary".equals(methodToCall))
				this.echoHexBinary(msgdata);
		
			else if("echoDecimal".equals(methodToCall))
				this.echoDecimal(msgdata);
		
			else if("echoBoolean".equals(methodToCall))
				this.echoBoolean(msgdata);
		
			else if("echoStructAsSimpleTypes".equals(methodToCall))
				this.echoStructAsSimpleTypes(msgdata);
		
			else if("echoSimpleTypesAsStruct".equals(methodToCall))
				this.echoSimpleTypesAsStruct(msgdata);
		
			else if("echo2DStringArray".equals(methodToCall))
				this.echo2DStringArray(msgdata);
		
			else if("echoNestedStruct".equals(methodToCall))
				this.echoNestedStruct(msgdata);
		
			else if("echoNestedArray".equals(methodToCall))
				this.echoNestedArray(msgdata);
		
			else if("echoToken".equals(methodToCall))
				this.echoToken(msgdata);
		
			else if("echoNormalizedString".equals(methodToCall))
				this.echoNormalizedString(msgdata);
		
			else if("echoUnsignedLong".equals(methodToCall))
				this.echoUnsignedLong(msgdata);
		
			else if("echoUnsignedInt".equals(methodToCall))
				this.echoUnsignedInt(msgdata);
		
			else if("echoUnsignedShort".equals(methodToCall))
				this.echoUnsignedShort(msgdata);
		
			else if("echoUnsignedByte".equals(methodToCall))
				this.echoUnsignedByte(msgdata);
		
			else if("echoNonNegativeInteger".equals(methodToCall))
				this.echoNonNegativeInteger(msgdata);
		
			else if("echoPositiveInteger".equals(methodToCall))
				this.echoPositiveInteger(msgdata);
		
			else if("echoNonPositiveInteger".equals(methodToCall))
				this.echoNonPositiveInteger(msgdata);
		
			else if("echoNegativeInteger".equals(methodToCall))
				this.echoNegativeInteger(msgdata);
		
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

	public void echoString(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.StringParam(service.echoString(paramIn0)));
	}

	public void echoStringArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.ArrayOfstring temp0 =  new  xsd.org.soapinterop.ArrayOfstring();
		temp0.desierialize(msgdata);
		java.lang.String[] paramIn0= temp0.getParam();
		xsd.org.soapinterop.ArrayOfstring ar = new xsd.org.soapinterop.ArrayOfstring();		ar.setParam(service.echoStringArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoInteger(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoInteger(paramIn0)));
	}

	public void echoIntegerArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.ArrayOfint temp0 =  new  xsd.org.soapinterop.ArrayOfint();
		temp0.desierialize(msgdata);
		int[] paramIn0= temp0.getParam();
		xsd.org.soapinterop.ArrayOfint ar = new xsd.org.soapinterop.ArrayOfint();		ar.setParam(service.echoIntegerArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoFloat(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		float paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.FloatParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.FloatParam(service.echoFloat(paramIn0)));
	}

	public void echoFloatArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.ArrayOffloat temp0 =  new  xsd.org.soapinterop.ArrayOffloat();
		temp0.desierialize(msgdata);
		float[] paramIn0= temp0.getParam();
		xsd.org.soapinterop.ArrayOffloat ar = new xsd.org.soapinterop.ArrayOffloat();		ar.setParam(service.echoFloatArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoStruct(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.SOAPStruct paramIn0 =  new  xsd.org.soapinterop.SOAPStruct();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.echoStruct(paramIn0));
	}

	public void echoStructArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.ArrayOfSOAPStruct temp0 =  new  xsd.org.soapinterop.ArrayOfSOAPStruct();
		temp0.desierialize(msgdata);
		xsd.org.soapinterop.SOAPStruct[] paramIn0= temp0.getParam();
		xsd.org.soapinterop.ArrayOfSOAPStruct ar = new xsd.org.soapinterop.ArrayOfSOAPStruct();		ar.setParam(service.echoStructArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoVoid(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		 service.echoVoid();
	}

	public void echoBase64(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam paramIn0 =  new  org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam(msgdata);		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam(service.echoBase64(paramIn0)));
	}

	public void echoHexBinary(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		org.apache.axismora.wrappers.simpleType.HexBinaryParam paramIn0 =  new  org.apache.axismora.wrappers.simpleType.HexBinaryParam(msgdata);		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.HexBinaryParam(service.echoHexBinary(paramIn0)));
	}

	public void echoDecimal(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.math.BigDecimal paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.BigDecimalParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.BigDecimalParam(service.echoDecimal(paramIn0)));
	}

	public void echoBoolean(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		boolean paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.BooleanParam(service.echoBoolean(paramIn0)));
	}

	public void echoStructAsSimpleTypes(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.SOAPStruct paramIn0 =  new  xsd.org.soapinterop.SOAPStruct();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoStructAsSimpleTypes(paramIn0)));
	}

	public void echoSimpleTypesAsStruct(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		int paramIn1 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		float paramIn2 =  (new  org.apache.axismora.wrappers.simpleType.FloatParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(service.echoSimpleTypesAsStruct(paramIn0,paramIn1,paramIn2));
	}

	public void echo2DStringArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.ArrayOfString2D temp0 =  new  xsd.org.soapinterop.ArrayOfString2D();
		temp0.desierialize(msgdata);
		java.lang.String[] paramIn0= temp0.getParam();
		xsd.org.soapinterop.ArrayOfString2D ar = new xsd.org.soapinterop.ArrayOfString2D();		ar.setParam(service.echo2DStringArray(paramIn0));
		msgdata.setSoapBodyContent(ar);	}

	public void echoNestedStruct(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.SOAPStructStruct paramIn0 =  new  xsd.org.soapinterop.SOAPStructStruct();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.echoNestedStruct(paramIn0));
	}

	public void echoNestedArray(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		xsd.org.soapinterop.SOAPArrayStruct paramIn0 =  new  xsd.org.soapinterop.SOAPArrayStruct();
		paramIn0.desierialize(msgdata);
		msgdata.setSoapBodyContent(service.echoNestedArray(paramIn0));
	}

	public void echoToken(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.StringParam(service.echoToken(paramIn0)));
	}

	public void echoNormalizedString(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.lang.String paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.StringParam(service.echoNormalizedString(paramIn0)));
	}

	public void echoUnsignedLong(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		long paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.LongParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.LongParam(service.echoUnsignedLong(paramIn0)));
	}

	public void echoUnsignedInt(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoUnsignedInt(paramIn0)));
	}

	public void echoUnsignedShort(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		short paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.ShortParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.ShortParam(service.echoUnsignedShort(paramIn0)));
	}

	public void echoUnsignedByte(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		byte paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.ByteParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.ByteParam(service.echoUnsignedByte(paramIn0)));
	}

	public void echoNonNegativeInteger(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoNonNegativeInteger(paramIn0)));
	}

	public void echoPositiveInteger(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoPositiveInteger(paramIn0)));
	}

	public void echoNonPositiveInteger(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoNonPositiveInteger(paramIn0)));
	}

	public void echoNegativeInteger(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int paramIn0 =  (new  org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
		msgdata.setSoapBodyContent(new org.apache.axismora.wrappers.simpleType.IntParam(service.echoNegativeInteger(paramIn0)));
	}

}
