package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ListingProductDetails  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String ExchangeId;
	private java.lang.String ListingId;
	private java.lang.String ExchangeTitle;
	private java.lang.String ExchangePrice;
	private java.lang.String ExchangeAsin;
	private java.lang.String ExchangeEndDate;
	private java.lang.String ExchangeTinyImage;
	private java.lang.String ExchangeSellerId;
	private java.lang.String ExchangeSellerNickname;
	private java.lang.String ExchangeStartDate;
	private java.lang.String ExchangeStatus;
	private java.lang.String ExchangeQuantity;
	private java.lang.String ExchangeQuantityAllocated;
	private java.lang.String ExchangeFeaturedCategory;
	private java.lang.String ExchangeCondition;
	private java.lang.String ExchangeConditionType;
	private java.lang.String ExchangeAvailability;
	private java.lang.String ExchangeOfferingType;
	private java.lang.String ExchangeSellerState;
	private java.lang.String ExchangeSellerCountry;
	private java.lang.String ExchangeSellerRating;

	public ListingProductDetails(){
	}
	public ListingProductDetails(java.lang.String ExchangeId,java.lang.String ListingId,java.lang.String ExchangeTitle,java.lang.String ExchangePrice,java.lang.String ExchangeAsin,java.lang.String ExchangeEndDate,java.lang.String ExchangeTinyImage,java.lang.String ExchangeSellerId,java.lang.String ExchangeSellerNickname,java.lang.String ExchangeStartDate,java.lang.String ExchangeStatus,java.lang.String ExchangeQuantity,java.lang.String ExchangeQuantityAllocated,java.lang.String ExchangeFeaturedCategory,java.lang.String ExchangeCondition,java.lang.String ExchangeConditionType,java.lang.String ExchangeAvailability,java.lang.String ExchangeOfferingType,java.lang.String ExchangeSellerState,java.lang.String ExchangeSellerCountry,java.lang.String ExchangeSellerRating){
		this.ExchangeId = ExchangeId;
		this.ListingId = ListingId;
		this.ExchangeTitle = ExchangeTitle;
		this.ExchangePrice = ExchangePrice;
		this.ExchangeAsin = ExchangeAsin;
		this.ExchangeEndDate = ExchangeEndDate;
		this.ExchangeTinyImage = ExchangeTinyImage;
		this.ExchangeSellerId = ExchangeSellerId;
		this.ExchangeSellerNickname = ExchangeSellerNickname;
		this.ExchangeStartDate = ExchangeStartDate;
		this.ExchangeStatus = ExchangeStatus;
		this.ExchangeQuantity = ExchangeQuantity;
		this.ExchangeQuantityAllocated = ExchangeQuantityAllocated;
		this.ExchangeFeaturedCategory = ExchangeFeaturedCategory;
		this.ExchangeCondition = ExchangeCondition;
		this.ExchangeConditionType = ExchangeConditionType;
		this.ExchangeAvailability = ExchangeAvailability;
		this.ExchangeOfferingType = ExchangeOfferingType;
		this.ExchangeSellerState = ExchangeSellerState;
		this.ExchangeSellerCountry = ExchangeSellerCountry;
		this.ExchangeSellerRating = ExchangeSellerRating;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 21;
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
				if(localName.equalsIgnoreCase("ExchangeId")) {
					this.ExchangeId= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("ListingId")) {
					this.ListingId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeTitle")) {
					this.ExchangeTitle= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangePrice")) {
					this.ExchangePrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeAsin")) {
					this.ExchangeAsin= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeEndDate")) {
					this.ExchangeEndDate= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeTinyImage")) {
					this.ExchangeTinyImage= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeSellerId")) {
					this.ExchangeSellerId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeSellerNickname")) {
					this.ExchangeSellerNickname= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeStartDate")) {
					this.ExchangeStartDate= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeStatus")) {
					this.ExchangeStatus= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeQuantity")) {
					this.ExchangeQuantity= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeQuantityAllocated")) {
					this.ExchangeQuantityAllocated= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeFeaturedCategory")) {
					this.ExchangeFeaturedCategory= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeCondition")) {
					this.ExchangeCondition= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeConditionType")) {
					this.ExchangeConditionType= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeAvailability")) {
					this.ExchangeAvailability= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeOfferingType")) {
					this.ExchangeOfferingType= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeSellerState")) {
					this.ExchangeSellerState= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeSellerCountry")) {
					this.ExchangeSellerCountry= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeSellerRating")) {
					this.ExchangeSellerRating= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "ListingProductDetails";
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

		context.writeString("<ExchangeId>");
		if(this.ExchangeId!=null){
			context.writeString(String.valueOf(ExchangeId));
		}
		context.writeString("</ExchangeId>\n");

		context.writeString("<ListingId>");
		if(this.ListingId!=null){
			context.writeString(String.valueOf(ListingId));
		}
		context.writeString("</ListingId>\n");

		context.writeString("<ExchangeTitle>");
		if(this.ExchangeTitle!=null){
			context.writeString(String.valueOf(ExchangeTitle));
		}
		context.writeString("</ExchangeTitle>\n");

		context.writeString("<ExchangePrice>");
		if(this.ExchangePrice!=null){
			context.writeString(String.valueOf(ExchangePrice));
		}
		context.writeString("</ExchangePrice>\n");

		context.writeString("<ExchangeAsin>");
		if(this.ExchangeAsin!=null){
			context.writeString(String.valueOf(ExchangeAsin));
		}
		context.writeString("</ExchangeAsin>\n");

		context.writeString("<ExchangeEndDate>");
		if(this.ExchangeEndDate!=null){
			context.writeString(String.valueOf(ExchangeEndDate));
		}
		context.writeString("</ExchangeEndDate>\n");

		context.writeString("<ExchangeTinyImage>");
		if(this.ExchangeTinyImage!=null){
			context.writeString(String.valueOf(ExchangeTinyImage));
		}
		context.writeString("</ExchangeTinyImage>\n");

		context.writeString("<ExchangeSellerId>");
		if(this.ExchangeSellerId!=null){
			context.writeString(String.valueOf(ExchangeSellerId));
		}
		context.writeString("</ExchangeSellerId>\n");

		context.writeString("<ExchangeSellerNickname>");
		if(this.ExchangeSellerNickname!=null){
			context.writeString(String.valueOf(ExchangeSellerNickname));
		}
		context.writeString("</ExchangeSellerNickname>\n");

		context.writeString("<ExchangeStartDate>");
		if(this.ExchangeStartDate!=null){
			context.writeString(String.valueOf(ExchangeStartDate));
		}
		context.writeString("</ExchangeStartDate>\n");

		context.writeString("<ExchangeStatus>");
		if(this.ExchangeStatus!=null){
			context.writeString(String.valueOf(ExchangeStatus));
		}
		context.writeString("</ExchangeStatus>\n");

		context.writeString("<ExchangeQuantity>");
		if(this.ExchangeQuantity!=null){
			context.writeString(String.valueOf(ExchangeQuantity));
		}
		context.writeString("</ExchangeQuantity>\n");

		context.writeString("<ExchangeQuantityAllocated>");
		if(this.ExchangeQuantityAllocated!=null){
			context.writeString(String.valueOf(ExchangeQuantityAllocated));
		}
		context.writeString("</ExchangeQuantityAllocated>\n");

		context.writeString("<ExchangeFeaturedCategory>");
		if(this.ExchangeFeaturedCategory!=null){
			context.writeString(String.valueOf(ExchangeFeaturedCategory));
		}
		context.writeString("</ExchangeFeaturedCategory>\n");

		context.writeString("<ExchangeCondition>");
		if(this.ExchangeCondition!=null){
			context.writeString(String.valueOf(ExchangeCondition));
		}
		context.writeString("</ExchangeCondition>\n");

		context.writeString("<ExchangeConditionType>");
		if(this.ExchangeConditionType!=null){
			context.writeString(String.valueOf(ExchangeConditionType));
		}
		context.writeString("</ExchangeConditionType>\n");

		context.writeString("<ExchangeAvailability>");
		if(this.ExchangeAvailability!=null){
			context.writeString(String.valueOf(ExchangeAvailability));
		}
		context.writeString("</ExchangeAvailability>\n");

		context.writeString("<ExchangeOfferingType>");
		if(this.ExchangeOfferingType!=null){
			context.writeString(String.valueOf(ExchangeOfferingType));
		}
		context.writeString("</ExchangeOfferingType>\n");

		context.writeString("<ExchangeSellerState>");
		if(this.ExchangeSellerState!=null){
			context.writeString(String.valueOf(ExchangeSellerState));
		}
		context.writeString("</ExchangeSellerState>\n");

		context.writeString("<ExchangeSellerCountry>");
		if(this.ExchangeSellerCountry!=null){
			context.writeString(String.valueOf(ExchangeSellerCountry));
		}
		context.writeString("</ExchangeSellerCountry>\n");

		context.writeString("<ExchangeSellerRating>");
		if(this.ExchangeSellerRating!=null){
			context.writeString(String.valueOf(ExchangeSellerRating));
		}
		context.writeString("</ExchangeSellerRating>\n");

		//write the end tag
		if(writeOutTag){
		context.writeString("</prf:");		context.writeString(type_name);
		context.writeString(">\n");
		}
	}

	public void setExchangeId(java.lang.String ExchangeId){
		this.ExchangeId = ExchangeId;
	}
	public java.lang.String getExchangeId(){
		return ExchangeId;
	}
	public void setListingId(java.lang.String ListingId){
		this.ListingId = ListingId;
	}
	public java.lang.String getListingId(){
		return ListingId;
	}
	public void setExchangeTitle(java.lang.String ExchangeTitle){
		this.ExchangeTitle = ExchangeTitle;
	}
	public java.lang.String getExchangeTitle(){
		return ExchangeTitle;
	}
	public void setExchangePrice(java.lang.String ExchangePrice){
		this.ExchangePrice = ExchangePrice;
	}
	public java.lang.String getExchangePrice(){
		return ExchangePrice;
	}
	public void setExchangeAsin(java.lang.String ExchangeAsin){
		this.ExchangeAsin = ExchangeAsin;
	}
	public java.lang.String getExchangeAsin(){
		return ExchangeAsin;
	}
	public void setExchangeEndDate(java.lang.String ExchangeEndDate){
		this.ExchangeEndDate = ExchangeEndDate;
	}
	public java.lang.String getExchangeEndDate(){
		return ExchangeEndDate;
	}
	public void setExchangeTinyImage(java.lang.String ExchangeTinyImage){
		this.ExchangeTinyImage = ExchangeTinyImage;
	}
	public java.lang.String getExchangeTinyImage(){
		return ExchangeTinyImage;
	}
	public void setExchangeSellerId(java.lang.String ExchangeSellerId){
		this.ExchangeSellerId = ExchangeSellerId;
	}
	public java.lang.String getExchangeSellerId(){
		return ExchangeSellerId;
	}
	public void setExchangeSellerNickname(java.lang.String ExchangeSellerNickname){
		this.ExchangeSellerNickname = ExchangeSellerNickname;
	}
	public java.lang.String getExchangeSellerNickname(){
		return ExchangeSellerNickname;
	}
	public void setExchangeStartDate(java.lang.String ExchangeStartDate){
		this.ExchangeStartDate = ExchangeStartDate;
	}
	public java.lang.String getExchangeStartDate(){
		return ExchangeStartDate;
	}
	public void setExchangeStatus(java.lang.String ExchangeStatus){
		this.ExchangeStatus = ExchangeStatus;
	}
	public java.lang.String getExchangeStatus(){
		return ExchangeStatus;
	}
	public void setExchangeQuantity(java.lang.String ExchangeQuantity){
		this.ExchangeQuantity = ExchangeQuantity;
	}
	public java.lang.String getExchangeQuantity(){
		return ExchangeQuantity;
	}
	public void setExchangeQuantityAllocated(java.lang.String ExchangeQuantityAllocated){
		this.ExchangeQuantityAllocated = ExchangeQuantityAllocated;
	}
	public java.lang.String getExchangeQuantityAllocated(){
		return ExchangeQuantityAllocated;
	}
	public void setExchangeFeaturedCategory(java.lang.String ExchangeFeaturedCategory){
		this.ExchangeFeaturedCategory = ExchangeFeaturedCategory;
	}
	public java.lang.String getExchangeFeaturedCategory(){
		return ExchangeFeaturedCategory;
	}
	public void setExchangeCondition(java.lang.String ExchangeCondition){
		this.ExchangeCondition = ExchangeCondition;
	}
	public java.lang.String getExchangeCondition(){
		return ExchangeCondition;
	}
	public void setExchangeConditionType(java.lang.String ExchangeConditionType){
		this.ExchangeConditionType = ExchangeConditionType;
	}
	public java.lang.String getExchangeConditionType(){
		return ExchangeConditionType;
	}
	public void setExchangeAvailability(java.lang.String ExchangeAvailability){
		this.ExchangeAvailability = ExchangeAvailability;
	}
	public java.lang.String getExchangeAvailability(){
		return ExchangeAvailability;
	}
	public void setExchangeOfferingType(java.lang.String ExchangeOfferingType){
		this.ExchangeOfferingType = ExchangeOfferingType;
	}
	public java.lang.String getExchangeOfferingType(){
		return ExchangeOfferingType;
	}
	public void setExchangeSellerState(java.lang.String ExchangeSellerState){
		this.ExchangeSellerState = ExchangeSellerState;
	}
	public java.lang.String getExchangeSellerState(){
		return ExchangeSellerState;
	}
	public void setExchangeSellerCountry(java.lang.String ExchangeSellerCountry){
		this.ExchangeSellerCountry = ExchangeSellerCountry;
	}
	public java.lang.String getExchangeSellerCountry(){
		return ExchangeSellerCountry;
	}
	public void setExchangeSellerRating(java.lang.String ExchangeSellerRating){
		this.ExchangeSellerRating = ExchangeSellerRating;
	}
	public java.lang.String getExchangeSellerRating(){
		return ExchangeSellerRating;
	}
}
