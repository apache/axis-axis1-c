package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Item  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String ItemId;
	private java.lang.String ProductName;
	private java.lang.String Catalog;
	private java.lang.String Asin;
	private java.lang.String ExchangeId;
	private java.lang.String Quantity;
	private java.lang.String ListPrice;
	private java.lang.String OurPrice;

	public Item(){
	}
	public Item(java.lang.String ItemId,java.lang.String ProductName,java.lang.String Catalog,java.lang.String Asin,java.lang.String ExchangeId,java.lang.String Quantity,java.lang.String ListPrice,java.lang.String OurPrice){
		this.ItemId = ItemId;
		this.ProductName = ProductName;
		this.Catalog = Catalog;
		this.Asin = Asin;
		this.ExchangeId = ExchangeId;
		this.Quantity = Quantity;
		this.ListPrice = ListPrice;
		this.OurPrice = OurPrice;
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
				if(localName.equalsIgnoreCase("ItemId")) {
					this.ItemId= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("ProductName")) {
					this.ProductName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Catalog")) {
					this.Catalog= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Asin")) {
					this.Asin= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ExchangeId")) {
					this.ExchangeId= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("Quantity")) {
					this.Quantity= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("ListPrice")) {
					this.ListPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("OurPrice")) {
					this.OurPrice= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "Item";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<ItemId>");
		if(this.ItemId!=null){
			context.writeString(String.valueOf(ItemId));
		}
		context.writeString("</ItemId>\n");

		context.writeString("<ProductName>");
		if(this.ProductName!=null){
			context.writeString(String.valueOf(ProductName));
		}
		context.writeString("</ProductName>\n");

		context.writeString("<Catalog>");
		if(this.Catalog!=null){
			context.writeString(String.valueOf(Catalog));
		}
		context.writeString("</Catalog>\n");

		context.writeString("<Asin>");
		if(this.Asin!=null){
			context.writeString(String.valueOf(Asin));
		}
		context.writeString("</Asin>\n");

		context.writeString("<ExchangeId>");
		if(this.ExchangeId!=null){
			context.writeString(String.valueOf(ExchangeId));
		}
		context.writeString("</ExchangeId>\n");

		context.writeString("<Quantity>");
		if(this.Quantity!=null){
			context.writeString(String.valueOf(Quantity));
		}
		context.writeString("</Quantity>\n");

		context.writeString("<ListPrice>");
		if(this.ListPrice!=null){
			context.writeString(String.valueOf(ListPrice));
		}
		context.writeString("</ListPrice>\n");

		context.writeString("<OurPrice>");
		if(this.OurPrice!=null){
			context.writeString(String.valueOf(OurPrice));
		}
		context.writeString("</OurPrice>\n");

	}

	public void setItemId(java.lang.String ItemId){
		this.ItemId = ItemId;
	}
	public java.lang.String getItemId(){
		return ItemId;
	}
	public void setProductName(java.lang.String ProductName){
		this.ProductName = ProductName;
	}
	public java.lang.String getProductName(){
		return ProductName;
	}
	public void setCatalog(java.lang.String Catalog){
		this.Catalog = Catalog;
	}
	public java.lang.String getCatalog(){
		return Catalog;
	}
	public void setAsin(java.lang.String Asin){
		this.Asin = Asin;
	}
	public java.lang.String getAsin(){
		return Asin;
	}
	public void setExchangeId(java.lang.String ExchangeId){
		this.ExchangeId = ExchangeId;
	}
	public java.lang.String getExchangeId(){
		return ExchangeId;
	}
	public void setQuantity(java.lang.String Quantity){
		this.Quantity = Quantity;
	}
	public java.lang.String getQuantity(){
		return Quantity;
	}
	public void setListPrice(java.lang.String ListPrice){
		this.ListPrice = ListPrice;
	}
	public java.lang.String getListPrice(){
		return ListPrice;
	}
	public void setOurPrice(java.lang.String OurPrice){
		this.OurPrice = OurPrice;
	}
	public java.lang.String getOurPrice(){
		return OurPrice;
	}
}
