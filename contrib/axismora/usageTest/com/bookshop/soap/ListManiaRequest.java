package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ListManiaRequest  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String lm_id;
	private java.lang.String page;
	private java.lang.String tag;
	private java.lang.String type;
	private java.lang.String devtag;
	private java.lang.String locale;

	public ListManiaRequest(){
	}
	public ListManiaRequest(java.lang.String lm_id,java.lang.String page,java.lang.String tag,java.lang.String type,java.lang.String devtag,java.lang.String locale){
		this.lm_id = lm_id;
		this.page = page;
		this.tag = tag;
		this.type = type;
		this.devtag = devtag;
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
				if(localName.equalsIgnoreCase("lm_id")) {
					this.lm_id= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("page")) {
					this.page= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("tag")) {
					this.tag= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("type")) {
					this.type= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("devtag")) {
					this.devtag= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
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
		String type_name = "ListManiaRequest";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<lm_id>");
		if(this.lm_id!=null){
			context.writeString(String.valueOf(lm_id));
		}
		context.writeString("</lm_id>\n");

		context.writeString("<page>");
		if(this.page!=null){
			context.writeString(String.valueOf(page));
		}
		context.writeString("</page>\n");

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

		context.writeString("<locale>");
		if(this.locale!=null){
			context.writeString(String.valueOf(locale));
		}
		context.writeString("</locale>\n");

	}

	public void setLm_id(java.lang.String lm_id){
		this.lm_id = lm_id;
	}
	public java.lang.String getLm_id(){
		return lm_id;
	}
	public void setPage(java.lang.String page){
		this.page = page;
	}
	public java.lang.String getPage(){
		return page;
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
	public void setLocale(java.lang.String locale){
		this.locale = locale;
	}
	public java.lang.String getLocale(){
		return locale;
	}
}
