package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class SellerFeedback  implements org.apache.axismora.encoding.InOutParameter{
	private com.bookshop.soap.Feedback[] Feedback;

	public SellerFeedback(){
	}
	public SellerFeedback(com.bookshop.soap.Feedback[] Feedback){
		this.Feedback = Feedback;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 1;
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
				if(localName.equalsIgnoreCase("Feedback")) {
					com.bookshop.soap.FeedbackArray arrayT0 = (new com.bookshop.soap.FeedbackArray());
					arrayT0.desierialize(msgdata);
					this.Feedback = arrayT0.getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "SellerFeedback";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<Feedback xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:Feedback[]\" xmlns:ns2 = \"http://soap.bookshop.com\">");
		if(this.Feedback!=null){
			context.writeString("\n");
			com.bookshop.soap.FeedbackArray item0 = new com.bookshop.soap.FeedbackArray();
			item0.setParam(Feedback);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item0.serialize(context);
		}
		context.writeString("</Feedback>\n");

	}

	public void setFeedback(com.bookshop.soap.Feedback[] Feedback){
		this.Feedback = Feedback;
	}
	public com.bookshop.soap.Feedback[] getFeedback(){
		return Feedback;
	}
}
