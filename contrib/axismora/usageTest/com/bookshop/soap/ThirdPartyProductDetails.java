package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ThirdPartyProductDetails  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String OfferingType;
	private java.lang.String SellerId;
	private java.lang.String SellerNickname;
	private java.lang.String ExchangeId;
	private java.lang.String OfferingPrice;
	private java.lang.String Condition;
	private java.lang.String ConditionType;
	private java.lang.String ExchangeAvailability;
	private java.lang.String SellerCountry;
	private java.lang.String SellerState;
	private java.lang.String ShipComments;
	private java.lang.String SellerRating;

	public ThirdPartyProductDetails(){
	}
	public ThirdPartyProductDetails(java.lang.String OfferingType,java.lang.String SellerId,java.lang.String SellerNickname,java.lang.String ExchangeId,java.lang.String OfferingPrice,java.lang.String Condition,java.lang.String ConditionType,java.lang.String ExchangeAvailability,java.lang.String SellerCountry,java.lang.String SellerState,java.lang.String ShipComments,java.lang.String SellerRating){
		this.OfferingType = OfferingType;
		this.SellerId = SellerId;
		this.SellerNickname = SellerNickname;
		this.ExchangeId = ExchangeId;
		this.OfferingPrice = OfferingPrice;
		this.Condition = Condition;
		this.ConditionType = ConditionType;
		this.ExchangeAvailability = ExchangeAvailability;
		this.SellerCountry = SellerCountry;
		this.SellerState = SellerState;
		this.ShipComments = ShipComments;
		this.SellerRating = SellerRating;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 12;
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
				if(localName.equalsIgnoreCase("OfferingType")) {
					this.OfferingType= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("SellerId")) {
					this.SellerId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("SellerNickname")) {
					this.SellerNickname= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeId")) {
					this.ExchangeId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("OfferingPrice")) {
					this.OfferingPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Condition")) {
					this.Condition= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ConditionType")) {
					this.ConditionType= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeAvailability")) {
					this.ExchangeAvailability= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("SellerCountry")) {
					this.SellerCountry= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("SellerState")) {
					this.SellerState= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ShipComments")) {
					this.ShipComments= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("SellerRating")) {
					this.SellerRating= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "ThirdPartyProductDetails";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<OfferingType>");
		if(this.OfferingType!=null){
			context.writeString(String.valueOf(OfferingType));
		}
		context.writeString("</OfferingType>\n");

		context.writeString("<SellerId>");
		if(this.SellerId!=null){
			context.writeString(String.valueOf(SellerId));
		}
		context.writeString("</SellerId>\n");

		context.writeString("<SellerNickname>");
		if(this.SellerNickname!=null){
			context.writeString(String.valueOf(SellerNickname));
		}
		context.writeString("</SellerNickname>\n");

		context.writeString("<ExchangeId>");
		if(this.ExchangeId!=null){
			context.writeString(String.valueOf(ExchangeId));
		}
		context.writeString("</ExchangeId>\n");

		context.writeString("<OfferingPrice>");
		if(this.OfferingPrice!=null){
			context.writeString(String.valueOf(OfferingPrice));
		}
		context.writeString("</OfferingPrice>\n");

		context.writeString("<Condition>");
		if(this.Condition!=null){
			context.writeString(String.valueOf(Condition));
		}
		context.writeString("</Condition>\n");

		context.writeString("<ConditionType>");
		if(this.ConditionType!=null){
			context.writeString(String.valueOf(ConditionType));
		}
		context.writeString("</ConditionType>\n");

		context.writeString("<ExchangeAvailability>");
		if(this.ExchangeAvailability!=null){
			context.writeString(String.valueOf(ExchangeAvailability));
		}
		context.writeString("</ExchangeAvailability>\n");

		context.writeString("<SellerCountry>");
		if(this.SellerCountry!=null){
			context.writeString(String.valueOf(SellerCountry));
		}
		context.writeString("</SellerCountry>\n");

		context.writeString("<SellerState>");
		if(this.SellerState!=null){
			context.writeString(String.valueOf(SellerState));
		}
		context.writeString("</SellerState>\n");

		context.writeString("<ShipComments>");
		if(this.ShipComments!=null){
			context.writeString(String.valueOf(ShipComments));
		}
		context.writeString("</ShipComments>\n");

		context.writeString("<SellerRating>");
		if(this.SellerRating!=null){
			context.writeString(String.valueOf(SellerRating));
		}
		context.writeString("</SellerRating>\n");

	}

	public void setOfferingType(java.lang.String OfferingType){
		this.OfferingType = OfferingType;
	}
	public java.lang.String getOfferingType(){
		return OfferingType;
	}
	public void setSellerId(java.lang.String SellerId){
		this.SellerId = SellerId;
	}
	public java.lang.String getSellerId(){
		return SellerId;
	}
	public void setSellerNickname(java.lang.String SellerNickname){
		this.SellerNickname = SellerNickname;
	}
	public java.lang.String getSellerNickname(){
		return SellerNickname;
	}
	public void setExchangeId(java.lang.String ExchangeId){
		this.ExchangeId = ExchangeId;
	}
	public java.lang.String getExchangeId(){
		return ExchangeId;
	}
	public void setOfferingPrice(java.lang.String OfferingPrice){
		this.OfferingPrice = OfferingPrice;
	}
	public java.lang.String getOfferingPrice(){
		return OfferingPrice;
	}
	public void setCondition(java.lang.String Condition){
		this.Condition = Condition;
	}
	public java.lang.String getCondition(){
		return Condition;
	}
	public void setConditionType(java.lang.String ConditionType){
		this.ConditionType = ConditionType;
	}
	public java.lang.String getConditionType(){
		return ConditionType;
	}
	public void setExchangeAvailability(java.lang.String ExchangeAvailability){
		this.ExchangeAvailability = ExchangeAvailability;
	}
	public java.lang.String getExchangeAvailability(){
		return ExchangeAvailability;
	}
	public void setSellerCountry(java.lang.String SellerCountry){
		this.SellerCountry = SellerCountry;
	}
	public java.lang.String getSellerCountry(){
		return SellerCountry;
	}
	public void setSellerState(java.lang.String SellerState){
		this.SellerState = SellerState;
	}
	public java.lang.String getSellerState(){
		return SellerState;
	}
	public void setShipComments(java.lang.String ShipComments){
		this.ShipComments = ShipComments;
	}
	public java.lang.String getShipComments(){
		return ShipComments;
	}
	public void setSellerRating(java.lang.String SellerRating){
		this.SellerRating = SellerRating;
	}
	public java.lang.String getSellerRating(){
		return SellerRating;
	}
}
