package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Feedback  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String FeedbackRating;
	private java.lang.String FeedbackComments;
	private java.lang.String FeedbackDate;
	private java.lang.String FeedbackRater;

	public Feedback(){
	}
	public Feedback(java.lang.String FeedbackRating,java.lang.String FeedbackComments,java.lang.String FeedbackDate,java.lang.String FeedbackRater){
		this.FeedbackRating = FeedbackRating;
		this.FeedbackComments = FeedbackComments;
		this.FeedbackDate = FeedbackDate;
		this.FeedbackRater = FeedbackRater;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 4;
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
				if(localName.equalsIgnoreCase("FeedbackRating")) {
					this.FeedbackRating= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("FeedbackComments")) {
					this.FeedbackComments= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("FeedbackDate")) {
					this.FeedbackDate= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("FeedbackRater")) {
					this.FeedbackRater= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "Feedback";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<FeedbackRating>");
		if(this.FeedbackRating!=null){
			context.writeString(String.valueOf(FeedbackRating));
		}
		context.writeString("</FeedbackRating>\n");

		context.writeString("<FeedbackComments>");
		if(this.FeedbackComments!=null){
			context.writeString(String.valueOf(FeedbackComments));
		}
		context.writeString("</FeedbackComments>\n");

		context.writeString("<FeedbackDate>");
		if(this.FeedbackDate!=null){
			context.writeString(String.valueOf(FeedbackDate));
		}
		context.writeString("</FeedbackDate>\n");

		context.writeString("<FeedbackRater>");
		if(this.FeedbackRater!=null){
			context.writeString(String.valueOf(FeedbackRater));
		}
		context.writeString("</FeedbackRater>\n");

	}

	public void setFeedbackRating(java.lang.String FeedbackRating){
		this.FeedbackRating = FeedbackRating;
	}
	public java.lang.String getFeedbackRating(){
		return FeedbackRating;
	}
	public void setFeedbackComments(java.lang.String FeedbackComments){
		this.FeedbackComments = FeedbackComments;
	}
	public java.lang.String getFeedbackComments(){
		return FeedbackComments;
	}
	public void setFeedbackDate(java.lang.String FeedbackDate){
		this.FeedbackDate = FeedbackDate;
	}
	public java.lang.String getFeedbackDate(){
		return FeedbackDate;
	}
	public void setFeedbackRater(java.lang.String FeedbackRater){
		this.FeedbackRater = FeedbackRater;
	}
	public java.lang.String getFeedbackRater(){
		return FeedbackRater;
	}
}
