package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ShoppingCart  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String CartId;
	private java.lang.String HMAC;
	private java.lang.String PurchaseUrl;
	private com.bookshop.soap.Item[] Items;

	public ShoppingCart(){
	}
	public ShoppingCart(java.lang.String CartId,java.lang.String HMAC,java.lang.String PurchaseUrl,com.bookshop.soap.Item[] Items){
		this.CartId = CartId;
		this.HMAC = HMAC;
		this.PurchaseUrl = PurchaseUrl;
		this.Items = Items;
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
				if(localName.equalsIgnoreCase("CartId")) {
					this.CartId= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("HMAC")) {
					this.HMAC= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("PurchaseUrl")) {
					this.PurchaseUrl= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Items")) {
					com.bookshop.soap.ItemArray arrayT3 = (new com.bookshop.soap.ItemArray());
					arrayT3.desierialize(msgdata);
					this.Items = arrayT3.getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "ShoppingCart";
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

		context.writeString("<PurchaseUrl>");
		if(this.PurchaseUrl!=null){
			context.writeString(String.valueOf(PurchaseUrl));
		}
		context.writeString("</PurchaseUrl>\n");

		context.writeString("<Items xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:Item[]\" xmlns:ns2 = \"http://soap.bookshop.com\">");
		if(this.Items!=null){
			context.writeString("\n");
			com.bookshop.soap.ItemArray item3 = new com.bookshop.soap.ItemArray();
			item3.setParam(Items);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item3.serialize(context);
		}
		context.writeString("</Items>\n");

		//write the end tag
		if(writeOutTag){
		context.writeString("</prf:");		context.writeString(type_name);
		context.writeString(">\n");
		}
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
	public void setPurchaseUrl(java.lang.String PurchaseUrl){
		this.PurchaseUrl = PurchaseUrl;
	}
	public java.lang.String getPurchaseUrl(){
		return PurchaseUrl;
	}
	public void setItems(com.bookshop.soap.Item[] Items){
		this.Items = Items;
	}
	public com.bookshop.soap.Item[] getItems(){
		return Items;
	}
}
