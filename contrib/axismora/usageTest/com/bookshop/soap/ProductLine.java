package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ProductLine  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String Mode;
	private com.bookshop.soap.ProductInfo ProductInfo;

	public ProductLine(){
	}
	public ProductLine(java.lang.String Mode,com.bookshop.soap.ProductInfo ProductInfo){
		this.Mode = Mode;
		this.ProductInfo = ProductInfo;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 2;
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
				if(localName.equalsIgnoreCase("Mode")) {
					this.Mode= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("ProductInfo")) {
					this.ProductInfo= (new com.bookshop.soap.ProductInfo());
					this.ProductInfo.desierialize(msgdata);
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "ProductLine";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<Mode>");
		if(this.Mode!=null){
			context.writeString(String.valueOf(Mode));
		}
		context.writeString("</Mode>\n");

		context.writeString("<ProductInfo>");
		if(this.ProductInfo!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			ProductInfo.serialize(context);
		}
		context.writeString("</ProductInfo>\n");

	}

	public void setMode(java.lang.String Mode){
		this.Mode = Mode;
	}
	public java.lang.String getMode(){
		return Mode;
	}
	public void setProductInfo(com.bookshop.soap.ProductInfo ProductInfo){
		this.ProductInfo = ProductInfo;
	}
	public com.bookshop.soap.ProductInfo getProductInfo(){
		return ProductInfo;
	}
}
