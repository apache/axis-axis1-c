package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Reviews  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String AvgCustomerRating;
	private java.lang.String TotalCustomerReviews;
	private com.bookshop.soap.CustomerReview[] CustomerReviews;

	public Reviews(){
	}
	public Reviews(java.lang.String AvgCustomerRating,java.lang.String TotalCustomerReviews,com.bookshop.soap.CustomerReview[] CustomerReviews){
		this.AvgCustomerRating = AvgCustomerRating;
		this.TotalCustomerReviews = TotalCustomerReviews;
		this.CustomerReviews = CustomerReviews;
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
				if(localName.equalsIgnoreCase("AvgCustomerRating")) {
					this.AvgCustomerRating= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("TotalCustomerReviews")) {
					this.TotalCustomerReviews= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("CustomerReviews")) {
					com.bookshop.soap.CustomerReviewArray arrayT2 = (new com.bookshop.soap.CustomerReviewArray());
					arrayT2.desierialize(msgdata);
					this.CustomerReviews = arrayT2.getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "Reviews";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<AvgCustomerRating>");
		if(this.AvgCustomerRating!=null){
			context.writeString(String.valueOf(AvgCustomerRating));
		}
		context.writeString("</AvgCustomerRating>\n");

		context.writeString("<TotalCustomerReviews>");
		if(this.TotalCustomerReviews!=null){
			context.writeString(String.valueOf(TotalCustomerReviews));
		}
		context.writeString("</TotalCustomerReviews>\n");

		context.writeString("<CustomerReviews xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:CustomerReview[]\" xmlns:ns2 = \"http://soap.bookshop.com\">");
		if(this.CustomerReviews!=null){
			context.writeString("\n");
			com.bookshop.soap.CustomerReviewArray item2 = new com.bookshop.soap.CustomerReviewArray();
			item2.setParam(CustomerReviews);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item2.serialize(context);
		}
		context.writeString("</CustomerReviews>\n");

	}

	public void setAvgCustomerRating(java.lang.String AvgCustomerRating){
		this.AvgCustomerRating = AvgCustomerRating;
	}
	public java.lang.String getAvgCustomerRating(){
		return AvgCustomerRating;
	}
	public void setTotalCustomerReviews(java.lang.String TotalCustomerReviews){
		this.TotalCustomerReviews = TotalCustomerReviews;
	}
	public java.lang.String getTotalCustomerReviews(){
		return TotalCustomerReviews;
	}
	public void setCustomerReviews(com.bookshop.soap.CustomerReview[] CustomerReviews){
		this.CustomerReviews = CustomerReviews;
	}
	public com.bookshop.soap.CustomerReview[] getCustomerReviews(){
		return CustomerReviews;
	}
}
