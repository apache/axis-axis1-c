package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ProductInfo  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String TotalResults;
	private java.lang.String TotalPages;
	private java.lang.String ListName;
	private com.bookshop.soap.Details[] Details;

	public ProductInfo(){
	}
	public ProductInfo(java.lang.String TotalResults,java.lang.String TotalPages,java.lang.String ListName,com.bookshop.soap.Details[] Details){
		this.TotalResults = TotalResults;
		this.TotalPages = TotalPages;
		this.ListName = ListName;
		this.Details = Details;
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
				if(localName.equalsIgnoreCase("TotalResults")) {
					this.TotalResults= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("TotalPages")) {
					this.TotalPages= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ListName")) {
					this.ListName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Details")) {
					com.bookshop.soap.DetailsArray arrayT3 = (new com.bookshop.soap.DetailsArray());
					arrayT3.desierialize(msgdata);
					this.Details = arrayT3.getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "ProductInfo";
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

		context.writeString("<TotalResults>");
		if(this.TotalResults!=null){
			context.writeString(String.valueOf(TotalResults));
		}
		context.writeString("</TotalResults>\n");

		context.writeString("<TotalPages>");
		if(this.TotalPages!=null){
			context.writeString(String.valueOf(TotalPages));
		}
		context.writeString("</TotalPages>\n");

		context.writeString("<ListName>");
		if(this.ListName!=null){
			context.writeString(String.valueOf(ListName));
		}
		context.writeString("</ListName>\n");

		context.writeString("<Details xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:Details[]\" xmlns:ns2 = \"http://soap.bookshop.com\">");
		if(this.Details!=null){
			context.writeString("\n");
			com.bookshop.soap.DetailsArray item3 = new com.bookshop.soap.DetailsArray();
			item3.setParam(Details);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item3.serialize(context);
		}
		context.writeString("</Details>\n");

		//write the end tag
		if(writeOutTag){
		context.writeString("</prf:");		context.writeString(type_name);
		context.writeString(">\n");
		}
	}

	public void setTotalResults(java.lang.String TotalResults){
		this.TotalResults = TotalResults;
	}
	public java.lang.String getTotalResults(){
		return TotalResults;
	}
	public void setTotalPages(java.lang.String TotalPages){
		this.TotalPages = TotalPages;
	}
	public java.lang.String getTotalPages(){
		return TotalPages;
	}
	public void setListName(java.lang.String ListName){
		this.ListName = ListName;
	}
	public java.lang.String getListName(){
		return ListName;
	}
	public void setDetails(com.bookshop.soap.Details[] Details){
		this.Details = Details;
	}
	public com.bookshop.soap.Details[] getDetails(){
		return Details;
	}
}
