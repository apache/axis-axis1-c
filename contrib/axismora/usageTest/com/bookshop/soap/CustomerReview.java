package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class CustomerReview  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String Rating;
	private java.lang.String Summary;
	private java.lang.String Comment;

	public CustomerReview(){
	}
	public CustomerReview(java.lang.String Rating,java.lang.String Summary,java.lang.String Comment){
		this.Rating = Rating;
		this.Summary = Summary;
		this.Comment = Comment;
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
				if(localName.equalsIgnoreCase("Rating")) {
					this.Rating= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("Summary")) {
					this.Summary= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Comment")) {
					this.Comment= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "CustomerReview";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<Rating>");
		if(this.Rating!=null){
			context.writeString(String.valueOf(Rating));
		}
		context.writeString("</Rating>\n");

		context.writeString("<Summary>");
		if(this.Summary!=null){
			context.writeString(String.valueOf(Summary));
		}
		context.writeString("</Summary>\n");

		context.writeString("<Comment>");
		if(this.Comment!=null){
			context.writeString(String.valueOf(Comment));
		}
		context.writeString("</Comment>\n");

	}

	public void setRating(java.lang.String Rating){
		this.Rating = Rating;
	}
	public java.lang.String getRating(){
		return Rating;
	}
	public void setSummary(java.lang.String Summary){
		this.Summary = Summary;
	}
	public java.lang.String getSummary(){
		return Summary;
	}
	public void setComment(java.lang.String Comment){
		this.Comment = Comment;
	}
	public java.lang.String getComment(){
		return Comment;
	}
}
