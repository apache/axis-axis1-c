package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class SellerRequest  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String seller_id;
	private java.lang.String tag;
	private java.lang.String type;
	private java.lang.String devtag;
	private java.lang.String offerstatus;
	private java.lang.String page;
	private java.lang.String seller_browse_id;
	private java.lang.String keyword;
	private java.lang.String locale;
	private java.lang.String index;

	public SellerRequest(){
	}
	public SellerRequest(java.lang.String seller_id,java.lang.String tag,java.lang.String type,java.lang.String devtag,java.lang.String offerstatus,java.lang.String page,java.lang.String seller_browse_id,java.lang.String keyword,java.lang.String locale,java.lang.String index){
		this.seller_id = seller_id;
		this.tag = tag;
		this.type = type;
		this.devtag = devtag;
		this.offerstatus = offerstatus;
		this.page = page;
		this.seller_browse_id = seller_browse_id;
		this.keyword = keyword;
		this.locale = locale;
		this.index = index;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 10;
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
				if(localName.equalsIgnoreCase("seller_id")) {
					this.seller_id= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("tag")) {
					this.tag= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("type")) {
					this.type= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("devtag")) {
					this.devtag= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("offerstatus")) {
					this.offerstatus= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("page")) {
					this.page= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("seller_browse_id")) {
					this.seller_browse_id= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("keyword")) {
					this.keyword= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("locale")) {
					this.locale= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("index")) {
					this.index= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "SellerRequest";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<seller_id>");
		if(this.seller_id!=null){
			context.writeString(String.valueOf(seller_id));
		}
		context.writeString("</seller_id>\n");

		context.writeString("<tag>");
		if(this.tag!=null){
			context.writeString(String.valueOf(tag));
		}
		context.writeString("</tag>\n");

		context.writeString("<type>");
		if(this.type!=null){
			context.writeString(String.valueOf(type));
		}
		context.writeString("</type>\n");

		context.writeString("<devtag>");
		if(this.devtag!=null){
			context.writeString(String.valueOf(devtag));
		}
		context.writeString("</devtag>\n");

		context.writeString("<offerstatus>");
		if(this.offerstatus!=null){
			context.writeString(String.valueOf(offerstatus));
		}
		context.writeString("</offerstatus>\n");

		context.writeString("<page>");
		if(this.page!=null){
			context.writeString(String.valueOf(page));
		}
		context.writeString("</page>\n");

		context.writeString("<seller_browse_id>");
		if(this.seller_browse_id!=null){
			context.writeString(String.valueOf(seller_browse_id));
		}
		context.writeString("</seller_browse_id>\n");

		context.writeString("<keyword>");
		if(this.keyword!=null){
			context.writeString(String.valueOf(keyword));
		}
		context.writeString("</keyword>\n");

		context.writeString("<locale>");
		if(this.locale!=null){
			context.writeString(String.valueOf(locale));
		}
		context.writeString("</locale>\n");

		context.writeString("<index>");
		if(this.index!=null){
			context.writeString(String.valueOf(index));
		}
		context.writeString("</index>\n");

	}

	public void setSeller_id(java.lang.String seller_id){
		this.seller_id = seller_id;
	}
	public java.lang.String getSeller_id(){
		return seller_id;
	}
	public void setTag(java.lang.String tag){
		this.tag = tag;
	}
	public java.lang.String getTag(){
		return tag;
	}
	public void setType(java.lang.String type){
		this.type = type;
	}
	public java.lang.String getType(){
		return type;
	}
	public void setDevtag(java.lang.String devtag){
		this.devtag = devtag;
	}
	public java.lang.String getDevtag(){
		return devtag;
	}
	public void setOfferstatus(java.lang.String offerstatus){
		this.offerstatus = offerstatus;
	}
	public java.lang.String getOfferstatus(){
		return offerstatus;
	}
	public void setPage(java.lang.String page){
		this.page = page;
	}
	public java.lang.String getPage(){
		return page;
	}
	public void setSeller_browse_id(java.lang.String seller_browse_id){
		this.seller_browse_id = seller_browse_id;
	}
	public java.lang.String getSeller_browse_id(){
		return seller_browse_id;
	}
	public void setKeyword(java.lang.String keyword){
		this.keyword = keyword;
	}
	public java.lang.String getKeyword(){
		return keyword;
	}
	public void setLocale(java.lang.String locale){
		this.locale = locale;
	}
	public java.lang.String getLocale(){
		return locale;
	}
	public void setIndex(java.lang.String index){
		this.index = index;
	}
	public java.lang.String getIndex(){
		return index;
	}
}
