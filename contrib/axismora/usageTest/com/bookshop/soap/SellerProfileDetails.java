package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class SellerProfileDetails  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String SellerNickname;
	private java.lang.String OverallFeedbackRating;
	private java.lang.String NumberOfFeedback;
	private java.lang.String NumberOfCanceledBids;
	private java.lang.String NumberOfCanceledAuctions;
	private java.lang.String StoreId;
	private java.lang.String StoreName;
	private com.bookshop.soap.SellerFeedback SellerFeedback;

	public SellerProfileDetails(){
	}
	public SellerProfileDetails(java.lang.String SellerNickname,java.lang.String OverallFeedbackRating,java.lang.String NumberOfFeedback,java.lang.String NumberOfCanceledBids,java.lang.String NumberOfCanceledAuctions,java.lang.String StoreId,java.lang.String StoreName,com.bookshop.soap.SellerFeedback SellerFeedback){
		this.SellerNickname = SellerNickname;
		this.OverallFeedbackRating = OverallFeedbackRating;
		this.NumberOfFeedback = NumberOfFeedback;
		this.NumberOfCanceledBids = NumberOfCanceledBids;
		this.NumberOfCanceledAuctions = NumberOfCanceledAuctions;
		this.StoreId = StoreId;
		this.StoreName = StoreName;
		this.SellerFeedback = SellerFeedback;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 8;
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
				if(localName.equalsIgnoreCase("SellerNickname")) {
					this.SellerNickname= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("OverallFeedbackRating")) {
					this.OverallFeedbackRating= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("NumberOfFeedback")) {
					this.NumberOfFeedback= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("NumberOfCanceledBids")) {
					this.NumberOfCanceledBids= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("NumberOfCanceledAuctions")) {
					this.NumberOfCanceledAuctions= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("StoreId")) {
					this.StoreId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("StoreName")) {
					this.StoreName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("SellerFeedback")) {
					this.SellerFeedback= (new com.bookshop.soap.SellerFeedback());
					this.SellerFeedback.desierialize(msgdata);
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "SellerProfileDetails";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<SellerNickname>");
		if(this.SellerNickname!=null){
			context.writeString(String.valueOf(SellerNickname));
		}
		context.writeString("</SellerNickname>\n");

		context.writeString("<OverallFeedbackRating>");
		if(this.OverallFeedbackRating!=null){
			context.writeString(String.valueOf(OverallFeedbackRating));
		}
		context.writeString("</OverallFeedbackRating>\n");

		context.writeString("<NumberOfFeedback>");
		if(this.NumberOfFeedback!=null){
			context.writeString(String.valueOf(NumberOfFeedback));
		}
		context.writeString("</NumberOfFeedback>\n");

		context.writeString("<NumberOfCanceledBids>");
		if(this.NumberOfCanceledBids!=null){
			context.writeString(String.valueOf(NumberOfCanceledBids));
		}
		context.writeString("</NumberOfCanceledBids>\n");

		context.writeString("<NumberOfCanceledAuctions>");
		if(this.NumberOfCanceledAuctions!=null){
			context.writeString(String.valueOf(NumberOfCanceledAuctions));
		}
		context.writeString("</NumberOfCanceledAuctions>\n");

		context.writeString("<StoreId>");
		if(this.StoreId!=null){
			context.writeString(String.valueOf(StoreId));
		}
		context.writeString("</StoreId>\n");

		context.writeString("<StoreName>");
		if(this.StoreName!=null){
			context.writeString(String.valueOf(StoreName));
		}
		context.writeString("</StoreName>\n");

		context.writeString("<SellerFeedback>");
		if(this.SellerFeedback!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			SellerFeedback.serialize(context);
		}
		context.writeString("</SellerFeedback>\n");

	}

	public void setSellerNickname(java.lang.String SellerNickname){
		this.SellerNickname = SellerNickname;
	}
	public java.lang.String getSellerNickname(){
		return SellerNickname;
	}
	public void setOverallFeedbackRating(java.lang.String OverallFeedbackRating){
		this.OverallFeedbackRating = OverallFeedbackRating;
	}
	public java.lang.String getOverallFeedbackRating(){
		return OverallFeedbackRating;
	}
	public void setNumberOfFeedback(java.lang.String NumberOfFeedback){
		this.NumberOfFeedback = NumberOfFeedback;
	}
	public java.lang.String getNumberOfFeedback(){
		return NumberOfFeedback;
	}
	public void setNumberOfCanceledBids(java.lang.String NumberOfCanceledBids){
		this.NumberOfCanceledBids = NumberOfCanceledBids;
	}
	public java.lang.String getNumberOfCanceledBids(){
		return NumberOfCanceledBids;
	}
	public void setNumberOfCanceledAuctions(java.lang.String NumberOfCanceledAuctions){
		this.NumberOfCanceledAuctions = NumberOfCanceledAuctions;
	}
	public java.lang.String getNumberOfCanceledAuctions(){
		return NumberOfCanceledAuctions;
	}
	public void setStoreId(java.lang.String StoreId){
		this.StoreId = StoreId;
	}
	public java.lang.String getStoreId(){
		return StoreId;
	}
	public void setStoreName(java.lang.String StoreName){
		this.StoreName = StoreName;
	}
	public java.lang.String getStoreName(){
		return StoreName;
	}
	public void setSellerFeedback(com.bookshop.soap.SellerFeedback SellerFeedback){
		this.SellerFeedback = SellerFeedback;
	}
	public com.bookshop.soap.SellerFeedback getSellerFeedback(){
		return SellerFeedback;
	}
}
