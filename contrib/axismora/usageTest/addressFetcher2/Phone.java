package addressFetcher2;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Phone  implements org.apache.axismora.encoding.InOutParameter{
	private int areaCode;
	private java.lang.String exchange;
	private java.lang.String number;

	public Phone(){
	}
	public Phone(int areaCode,java.lang.String exchange,java.lang.String number){
		this.areaCode = areaCode;
		this.exchange = exchange;
		this.number = number;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 3;
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
				if(localName.equalsIgnoreCase("areaCode")) {
					this.areaCode= new org.apache.axismora.wrappers.simpleType.IntParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("exchange")) {
					this.exchange= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("number")) {
					this.number= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="urn:AddressFetcher2";
		String type_name = "phone";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<areaCode>");
			context.writeString(String.valueOf(areaCode));
		context.writeString("</areaCode>\n");

		context.writeString("<exchange>");
		if(this.exchange!=null){
			context.writeString(String.valueOf(exchange));
		}
		context.writeString("</exchange>\n");

		context.writeString("<number>");
		if(this.number!=null){
			context.writeString(String.valueOf(number));
		}
		context.writeString("</number>\n");

	}

	public void setAreaCode(int areaCode){
		this.areaCode = areaCode;
	}
	public int getAreaCode(){
		return areaCode;
	}
	public void setExchange(java.lang.String exchange){
		this.exchange = exchange;
	}
	public java.lang.String getExchange(){
		return exchange;
	}
	public void setNumber(java.lang.String number){
		this.number = number;
	}
	public java.lang.String getNumber(){
		return number;
	}
}
