package org.soapinterop;
/**
* This is the service class build with the information given
 * by the wsdl file the user should fill the logic here 
 */
public class InteropTestPortTypeImpl  {
	public java.lang.String echoString(java.lang.String param0){return param0;}
	public java.lang.String[] echoStringArray(java.lang.String[] param0){return param0;}
	public int echoInteger(int param0){return param0;}
	public int[] echoIntegerArray(int[] param0){return param0;}
	public float echoFloat(float param0){return param0;}
	public float[] echoFloatArray(float[] param0){return param0;}
	public xsd.org.soapinterop.SOAPStruct echoStruct(xsd.org.soapinterop.SOAPStruct param0){return param0;}
	public xsd.org.soapinterop.SOAPStruct[] echoStructArray(xsd.org.soapinterop.SOAPStruct[] param0){return param0;}
	public void echoVoid(){}
	public org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam echoBase64(org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam param0){return param0;}
	public org.apache.axismora.wrappers.simpleType.HexBinaryParam echoHexBinary(org.apache.axismora.wrappers.simpleType.HexBinaryParam param0){return param0;}
	public java.math.BigDecimal echoDecimal(java.math.BigDecimal param0){return param0;}
	public boolean echoBoolean(boolean param0){return param0;}
	public int echoStructAsSimpleTypes(xsd.org.soapinterop.SOAPStruct param0){return param0.getVarInt();}
	public xsd.org.soapinterop.SOAPStruct echoSimpleTypesAsStruct(java.lang.String param0,int param1,float param2){return new xsd.org.soapinterop.SOAPStruct();}
	public java.lang.String[] echo2DStringArray(java.lang.String[] param0){return param0;}
	public xsd.org.soapinterop.SOAPStructStruct echoNestedStruct(xsd.org.soapinterop.SOAPStructStruct param0){return param0;}
	public xsd.org.soapinterop.SOAPArrayStruct echoNestedArray(xsd.org.soapinterop.SOAPArrayStruct param0){return param0;}
	public java.lang.String echoToken(java.lang.String param0){return param0;}
	public java.lang.String echoNormalizedString(java.lang.String param0){return param0;}
	public long echoUnsignedLong(long param0){return param0;}
	public int echoUnsignedInt(int param0){return param0;}
	public short echoUnsignedShort(short param0){return param0;}
	public byte echoUnsignedByte(byte param0){return param0;}
	public int echoNonNegativeInteger(int param0){return param0;}
	public int echoPositiveInteger(int param0){return param0;}
	public int echoNonPositiveInteger(int param0){return param0;}
	public int echoNegativeInteger(int param0){return param0;}
}
