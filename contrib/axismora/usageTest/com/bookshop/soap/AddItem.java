package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class AddItem  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String Asin;
	private java.lang.String ExchangeId;
	private java.lang.String Quantity;

	public AddItem(){
	}
	public AddItem(java.lang.String Asin,java.lang.String ExchangeId,java.lang.String Quantity){
		this.Asin = Asin;
		this.ExchangeId = ExchangeId;
		this.Quantity = Quantity;
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
				if(localName.equalsIgnoreCase("Asin")) {
					this.Asin= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeId")) {
					this.ExchangeId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Quantity")) {
					this.Quantity= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "AddItem";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<Asin>");
		if(this.Asin!=null){
			context.writeString(String.valueOf(Asin));
		}
		context.writeString("</Asin>\n");

		context.writeString("<ExchangeId>");
		if(this.ExchangeId!=null){
			context.writeString(String.valueOf(ExchangeId));
		}
		context.writeString("</ExchangeId>\n");

		context.writeString("<Quantity>");
		if(this.Quantity!=null){
			context.writeString(String.valueOf(Quantity));
		}
		context.writeString("</Quantity>\n");

	}

	public void setAsin(java.lang.String Asin){
		this.Asin = Asin;
	}
	public java.lang.String getAsin(){
		return Asin;
	}
	public void setExchangeId(java.lang.String ExchangeId){
		this.ExchangeId = ExchangeId;
	}
	public java.lang.String getExchangeId(){
		return ExchangeId;
	}
	public void setQuantity(java.lang.String Quantity){
		this.Quantity = Quantity;
	}
	public java.lang.String getQuantity(){
		return Quantity;
	}
}
