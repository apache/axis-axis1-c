package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class AddShoppingCartItemsRequest  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String tag;
	private java.lang.String devtag;
	private java.lang.String CartId;
	private java.lang.String HMAC;
	private com.bookshop.soap.AddItem[] Items;
	private java.lang.String locale;

	public AddShoppingCartItemsRequest(){
	}
	public AddShoppingCartItemsRequest(java.lang.String tag,java.lang.String devtag,java.lang.String CartId,java.lang.String HMAC,com.bookshop.soap.AddItem[] Items,java.lang.String locale){
		this.tag = tag;
		this.devtag = devtag;
		this.CartId = CartId;
		this.HMAC = HMAC;
		this.Items = Items;
		this.locale = locale;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 6;
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
				if(localName.equalsIgnoreCase("tag")) {
					this.tag= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("devtag")) {
					this.devtag= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("CartId")) {
					this.CartId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("HMAC")) {
					this.HMAC= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Items")) {
					com.bookshop.soap.AddItemArray arrayT4 = (new com.bookshop.soap.AddItemArray());
					arrayT4.desierialize(msgdata);
					this.Items = arrayT4.getParam();
				}else if (localName.equalsIgnoreCase("locale")) {
					this.locale= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "AddShoppingCartItemsRequest";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<tag>");
		if(this.tag!=null){
			context.writeString(String.valueOf(tag));
		}
		context.writeString("</tag>\n");

		context.writeString("<devtag>");
		if(this.devtag!=null){
			context.writeString(String.valueOf(devtag));
		}
		context.writeString("</devtag>\n");

		context.writeString("<CartId>");
		if(this.CartId!=null){
			context.writeString(String.valueOf(CartId));
		}
		context.writeString("</CartId>\n");

		context.writeString("<HMAC>");
		if(this.HMAC!=null){
			context.writeString(String.valueOf(HMAC));
		}
		context.writeString("</HMAC>\n");

		context.writeString("<Items xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:AddItem[]\" xmlns:ns2 = \"http://soap.bookshop.com\">");
		if(this.Items!=null){
			context.writeString("\n");
			com.bookshop.soap.AddItemArray item4 = new com.bookshop.soap.AddItemArray();
			item4.setParam(Items);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item4.serialize(context);
		}
		context.writeString("</Items>\n");

		context.writeString("<locale>");
		if(this.locale!=null){
			context.writeString(String.valueOf(locale));
		}
		context.writeString("</locale>\n");

	}

	public void setTag(java.lang.String tag){
		this.tag = tag;
	}
	public java.lang.String getTag(){
		return tag;
	}
	public void setDevtag(java.lang.String devtag){
		this.devtag = devtag;
	}
	public java.lang.String getDevtag(){
		return devtag;
	}
	public void setCartId(java.lang.String CartId){
		this.CartId = CartId;
	}
	public java.lang.String getCartId(){
		return CartId;
	}
	public void setHMAC(java.lang.String HMAC){
		this.HMAC = HMAC;
	}
	public java.lang.String getHMAC(){
		return HMAC;
	}
	public void setItems(com.bookshop.soap.AddItem[] Items){
		this.Items = Items;
	}
	public com.bookshop.soap.AddItem[] getItems(){
		return Items;
	}
	public void setLocale(java.lang.String locale){
		this.locale = locale;
	}
	public java.lang.String getLocale(){
		return locale;
	}
}
