package types.usageTests;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class BasicStruct  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String valA1;
	private int valA2;
	private long valA3;
	private java.lang.String valA4;
	private java.lang.String valA5;

	public BasicStruct(){
	}
	public BasicStruct(java.lang.String valA1,int valA2,long valA3,java.lang.String valA4,java.lang.String valA5){
		this.valA1 = valA1;
		this.valA2 = valA2;
		this.valA3 = valA3;
		this.valA4 = valA4;
		this.valA5 = valA5;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 5;
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
				if(localName.equalsIgnoreCase("valA1")) {
					this.valA1= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("valA2")) {
					this.valA2= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("valA3")) {
					this.valA3= (new org.apache.axismora.wrappers.simpleType.LongParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("valA4")) {
					this.valA4= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("valA5")) {
					this.valA5= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://usageTests/types";
		String type_name = "BasicStruct";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<valA1>");
		if(this.valA1!=null){
			context.writeString(String.valueOf(valA1));
		}
		context.writeString("</valA1>\n");

		context.writeString("<valA2>");
			context.writeString(String.valueOf(valA2));
		context.writeString("</valA2>\n");

		context.writeString("<valA3>");
			context.writeString(String.valueOf(valA3));
		context.writeString("</valA3>\n");

		context.writeString("<valA4>");
		if(this.valA4!=null){
			context.writeString(String.valueOf(valA4));
		}
		context.writeString("</valA4>\n");

		context.writeString("<valA5>");
		if(this.valA5!=null){
			context.writeString(String.valueOf(valA5));
		}
		context.writeString("</valA5>\n");

	}

	public void setValA1(java.lang.String valA1){
		this.valA1 = valA1;
	}
	public java.lang.String getValA1(){
		return valA1;
	}
	public void setValA2(int valA2){
		this.valA2 = valA2;
	}
	public int getValA2(){
		return valA2;
	}
	public void setValA3(long valA3){
		this.valA3 = valA3;
	}
	public long getValA3(){
		return valA3;
	}
	public void setValA4(java.lang.String valA4){
		this.valA4 = valA4;
	}
	public java.lang.String getValA4(){
		return valA4;
	}
	public void setValA5(java.lang.String valA5){
		this.valA5 = valA5;
	}
	public java.lang.String getValA5(){
		return valA5;
	}
}
