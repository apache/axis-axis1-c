package types.usageTests;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class SOAPStruct  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String val1;
	private java.lang.String[] val10;
	private int[] val11;
	private short[] val12;
	private double[] val13;
	private float[] val14;
	private long[] val15;
	private org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam val17;
	private boolean[] val18;
	private types.usageTests.BasicStruct val19;
	private int val2;
	private types.usageTests.BasicStruct[] val20;
	private types.usageTests.BasicStruct val21;
	private short val3;
	private double val4;
	private float val5;
	private long val6;
	private byte val8;
	private boolean val9;

	public SOAPStruct(){
	}
	public SOAPStruct(java.lang.String val1,java.lang.String[] val10,int[] val11,short[] val12,double[] val13,float[] val14,long[] val15,org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam val17,boolean[] val18,types.usageTests.BasicStruct val19,int val2,types.usageTests.BasicStruct[] val20,types.usageTests.BasicStruct val21,short val3,double val4,float val5,long val6,byte val8,boolean val9){
		this.val1 = val1;
		this.val10 = val10;
		this.val11 = val11;
		this.val12 = val12;
		this.val13 = val13;
		this.val14 = val14;
		this.val15 = val15;
		this.val17 = val17;
		this.val18 = val18;
		this.val19 = val19;
		this.val2 = val2;
		this.val20 = val20;
		this.val21 = val21;
		this.val3 = val3;
		this.val4 = val4;
		this.val5 = val5;
		this.val6 = val6;
		this.val8 = val8;
		this.val9 = val9;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 19;
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag == null)
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag= msgdata.getTag();
		//come to first start tag
		while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		//skip it says the type
		org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		//if the type of the next tag is end tag that means the content of element is null
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG)			return null;

		for(int i = 0;i<count;i++) {
			while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				String localName = org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart();
				if(localName.equalsIgnoreCase("val1")) {
					this.val1= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("val10")) {
					types.usageTests.ArrayOf_xsd_string arrayT1 = (new types.usageTests.ArrayOf_xsd_string());
					arrayT1.desierialize(msgdata);
					this.val10 = arrayT1.getParam();
				}else if (localName.equalsIgnoreCase("val11")) {
					types.usageTests.ArrayOf_xsd_int arrayT2 = (new types.usageTests.ArrayOf_xsd_int());
					arrayT2.desierialize(msgdata);
					this.val11 = arrayT2.getParam();
				}else if (localName.equalsIgnoreCase("val12")) {
					types.usageTests.ArrayOf_xsd_short arrayT3 = (new types.usageTests.ArrayOf_xsd_short());
					arrayT3.desierialize(msgdata);
					this.val12 = arrayT3.getParam();
				}else if (localName.equalsIgnoreCase("val13")) {
					types.usageTests.ArrayOf_xsd_double arrayT4 = (new types.usageTests.ArrayOf_xsd_double());
					arrayT4.desierialize(msgdata);
					this.val13 = arrayT4.getParam();
				}else if (localName.equalsIgnoreCase("val14")) {
					types.usageTests.ArrayOf_xsd_float arrayT5 = (new types.usageTests.ArrayOf_xsd_float());
					arrayT5.desierialize(msgdata);
					this.val14 = arrayT5.getParam();
				}else if (localName.equalsIgnoreCase("val15")) {
					types.usageTests.ArrayOf_xsd_long arrayT6 = (new types.usageTests.ArrayOf_xsd_long());
					arrayT6.desierialize(msgdata);
					this.val15 = arrayT6.getParam();
				}else if (localName.equalsIgnoreCase("val17")) {
					this.val17= new org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam(msgdata);
				}else if (localName.equalsIgnoreCase("val18")) {
					types.usageTests.ArrayOf_xsd_boolean arrayT8 = (new types.usageTests.ArrayOf_xsd_boolean());
					arrayT8.desierialize(msgdata);
					this.val18 = arrayT8.getParam();
				}else if (localName.equalsIgnoreCase("val19")) {
					this.val19= (new types.usageTests.BasicStruct());
					this.val19.desierialize(msgdata);
				}else if (localName.equalsIgnoreCase("val2")) {
					this.val2= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("val20")) {
					types.usageTests.ArrayOfBasicStruct arrayT11 = (new types.usageTests.ArrayOfBasicStruct());
					arrayT11.desierialize(msgdata);
					this.val20 = arrayT11.getParam();
				}else if (localName.equalsIgnoreCase("val21")) {
					this.val21= (new types.usageTests.BasicStruct());
					this.val21.desierialize(msgdata);
				}else if (localName.equalsIgnoreCase("val3")) {
					this.val3= (new org.apache.axismora.wrappers.simpleType.ShortParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("val4")) {
					this.val4= (new org.apache.axismora.wrappers.simpleType.DoubleParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("val5")) {
					this.val5= (new org.apache.axismora.wrappers.simpleType.FloatParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("val6")) {
					this.val6= (new org.apache.axismora.wrappers.simpleType.LongParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("val8")) {
					this.val8= (new org.apache.axismora.wrappers.simpleType.ByteParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("val9")) {
					this.val9= (new org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://usageTests/types";
		String type_name = "SOAPStruct";
		//write start tag
		boolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;
		if(writeOutTag){
			//write the start tag
			context.writeString("<prf:");
			context.writeString(type_name);
			context.writeString("  xmlns:prf =\"");
			context.writeString(m_URI);
			context.writeString("\">\n");

		}
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<val1>");
		if(this.val1!=null){
			context.writeString(String.valueOf(val1));
		}
		context.writeString("</val1>\n");

		context.writeString("<val10 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.val10!=null){
			context.writeString("\n");
			types.usageTests.ArrayOf_xsd_string item1 = new types.usageTests.ArrayOf_xsd_string();
			item1.setParam(val10);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item1.serialize(context);
		}
		context.writeString("</val10>\n");

		context.writeString("<val11 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:int[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.val11!=null){
			context.writeString("\n");
			types.usageTests.ArrayOf_xsd_int item2 = new types.usageTests.ArrayOf_xsd_int();
			item2.setParam(val11);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item2.serialize(context);
		}
		context.writeString("</val11>\n");

		context.writeString("<val12 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:short[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.val12!=null){
			context.writeString("\n");
			types.usageTests.ArrayOf_xsd_short item3 = new types.usageTests.ArrayOf_xsd_short();
			item3.setParam(val12);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item3.serialize(context);
		}
		context.writeString("</val12>\n");

		context.writeString("<val13 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:double[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.val13!=null){
			context.writeString("\n");
			types.usageTests.ArrayOf_xsd_double item4 = new types.usageTests.ArrayOf_xsd_double();
			item4.setParam(val13);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item4.serialize(context);
		}
		context.writeString("</val13>\n");

		context.writeString("<val14 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:float[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.val14!=null){
			context.writeString("\n");
			types.usageTests.ArrayOf_xsd_float item5 = new types.usageTests.ArrayOf_xsd_float();
			item5.setParam(val14);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item5.serialize(context);
		}
		context.writeString("</val14>\n");

		context.writeString("<val15 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:long[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.val15!=null){
			context.writeString("\n");
			types.usageTests.ArrayOf_xsd_long item6 = new types.usageTests.ArrayOf_xsd_long();
			item6.setParam(val15);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item6.serialize(context);
		}
		context.writeString("</val15>\n");

		context.writeString("<val17>");
		if(this.val17!=null){
			context.writeString(String.valueOf(val17.getParam()));
		}
		context.writeString("</val17>\n");

		context.writeString("<val18 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:boolean[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
		if(this.val18!=null){
			context.writeString("\n");
			types.usageTests.ArrayOf_xsd_boolean item8 = new types.usageTests.ArrayOf_xsd_boolean();
			item8.setParam(val18);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item8.serialize(context);
		}
		context.writeString("</val18>\n");

		context.writeString("<val19>");
		if(this.val19!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			val19.serialize(context);
		}
		context.writeString("</val19>\n");

		context.writeString("<val2>");
			context.writeString(String.valueOf(val2));
		context.writeString("</val2>\n");

		context.writeString("<val20 xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:BasicStruct[]\" xmlns:ns2 = \"http://usageTests/types\">");
		if(this.val20!=null){
			context.writeString("\n");
			types.usageTests.ArrayOfBasicStruct item11 = new types.usageTests.ArrayOfBasicStruct();
			item11.setParam(val20);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item11.serialize(context);
		}
		context.writeString("</val20>\n");

		context.writeString("<val21>");
		if(this.val21!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			val21.serialize(context);
		}
		context.writeString("</val21>\n");

		context.writeString("<val3>");
			context.writeString(String.valueOf(val3));
		context.writeString("</val3>\n");

		context.writeString("<val4>");
			context.writeString(String.valueOf(val4));
		context.writeString("</val4>\n");

		context.writeString("<val5>");
			context.writeString(String.valueOf(val5));
		context.writeString("</val5>\n");

		context.writeString("<val6>");
			context.writeString(String.valueOf(val6));
		context.writeString("</val6>\n");

		context.writeString("<val8>");
			context.writeString(String.valueOf(val8));
		context.writeString("</val8>\n");

		context.writeString("<val9>");
			context.writeString(String.valueOf(val9));
		context.writeString("</val9>\n");

		//write the end tag
		if(writeOutTag){
		context.writeString("</prf:");		context.writeString(type_name);
		context.writeString(">\n");
		}
	}

	public void setVal1(java.lang.String val1){
		this.val1 = val1;
	}
	public java.lang.String getVal1(){
		return val1;
	}
	public void setVal10(java.lang.String[] val10){
		this.val10 = val10;
	}
	public java.lang.String[] getVal10(){
		return val10;
	}
	public void setVal11(int[] val11){
		this.val11 = val11;
	}
	public int[] getVal11(){
		return val11;
	}
	public void setVal12(short[] val12){
		this.val12 = val12;
	}
	public short[] getVal12(){
		return val12;
	}
	public void setVal13(double[] val13){
		this.val13 = val13;
	}
	public double[] getVal13(){
		return val13;
	}
	public void setVal14(float[] val14){
		this.val14 = val14;
	}
	public float[] getVal14(){
		return val14;
	}
	public void setVal15(long[] val15){
		this.val15 = val15;
	}
	public long[] getVal15(){
		return val15;
	}
	public void setVal17(org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam val17){
		this.val17 = val17;
	}
	public org.apache.axismora.wrappers.simpleType.Base64ByteArrayParam getVal17(){
		return val17;
	}
	public void setVal18(boolean[] val18){
		this.val18 = val18;
	}
	public boolean[] getVal18(){
		return val18;
	}
	public void setVal19(types.usageTests.BasicStruct val19){
		this.val19 = val19;
	}
	public types.usageTests.BasicStruct getVal19(){
		return val19;
	}
	public void setVal2(int val2){
		this.val2 = val2;
	}
	public int getVal2(){
		return val2;
	}
	public void setVal20(types.usageTests.BasicStruct[] val20){
		this.val20 = val20;
	}
	public types.usageTests.BasicStruct[] getVal20(){
		return val20;
	}
	public void setVal21(types.usageTests.BasicStruct val21){
		this.val21 = val21;
	}
	public types.usageTests.BasicStruct getVal21(){
		return val21;
	}
	public void setVal3(short val3){
		this.val3 = val3;
	}
	public short getVal3(){
		return val3;
	}
	public void setVal4(double val4){
		this.val4 = val4;
	}
	public double getVal4(){
		return val4;
	}
	public void setVal5(float val5){
		this.val5 = val5;
	}
	public float getVal5(){
		return val5;
	}
	public void setVal6(long val6){
		this.val6 = val6;
	}
	public long getVal6(){
		return val6;
	}
	public void setVal8(byte val8){
		this.val8 = val8;
	}
	public byte getVal8(){
		return val8;
	}
	public void setVal9(boolean val9){
		this.val9 = val9;
	}
	public boolean getVal9(){
		return val9;
	}
}
