package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class SellerProfile  implements org.apache.axismora.encoding.InOutParameter{
	private com.bookshop.soap.SellerProfileDetails[] SellerProfileDetails;

	public SellerProfile(){
	}
	public SellerProfile(com.bookshop.soap.SellerProfileDetails[] SellerProfileDetails){
		this.SellerProfileDetails = SellerProfileDetails;
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
				if(localName.equalsIgnoreCase("SellerProfileDetails")) {
					com.bookshop.soap.SellerProfileDetailsArray arrayT0 = (new com.bookshop.soap.SellerProfileDetailsArray());
					arrayT0.desierialize(msgdata);
					this.SellerProfileDetails = arrayT0.getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "SellerProfile";
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

		context.writeString("<SellerProfileDetails xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:SellerProfileDetails[]\" xmlns:ns2 = \"http://soap.bookshop.com\">");
		if(this.SellerProfileDetails!=null){
			context.writeString("\n");
			com.bookshop.soap.SellerProfileDetailsArray item0 = new com.bookshop.soap.SellerProfileDetailsArray();
			item0.setParam(SellerProfileDetails);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item0.serialize(context);
		}
		context.writeString("</SellerProfileDetails>\n");

		//write the end tag
		if(writeOutTag){
		context.writeString("</prf:");		context.writeString(type_name);
		context.writeString(">\n");
		}
	}

	public void setSellerProfileDetails(com.bookshop.soap.SellerProfileDetails[] SellerProfileDetails){
		this.SellerProfileDetails = SellerProfileDetails;
	}
	public com.bookshop.soap.SellerProfileDetails[] getSellerProfileDetails(){
		return SellerProfileDetails;
	}
}
