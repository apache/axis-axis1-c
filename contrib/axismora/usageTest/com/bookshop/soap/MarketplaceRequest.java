package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class MarketplaceRequest  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String marketplace_search;
	private java.lang.String tag;
	private java.lang.String type;
	private java.lang.String devtag;
	private java.lang.String page;
	private java.lang.String keyword;
	private java.lang.String keyword_search;
	private java.lang.String browse_id;
	private java.lang.String zipcode;
	private java.lang.String area_id;
	private java.lang.String geo;
	private java.lang.String rank;
	private java.lang.String listing_id;
	private java.lang.String locale;
	private java.lang.String index;

	public MarketplaceRequest(){
	}
	public MarketplaceRequest(java.lang.String marketplace_search,java.lang.String tag,java.lang.String type,java.lang.String devtag,java.lang.String page,java.lang.String keyword,java.lang.String keyword_search,java.lang.String browse_id,java.lang.String zipcode,java.lang.String area_id,java.lang.String geo,java.lang.String rank,java.lang.String listing_id,java.lang.String locale,java.lang.String index){
		this.marketplace_search = marketplace_search;
		this.tag = tag;
		this.type = type;
		this.devtag = devtag;
		this.page = page;
		this.keyword = keyword;
		this.keyword_search = keyword_search;
		this.browse_id = browse_id;
		this.zipcode = zipcode;
		this.area_id = area_id;
		this.geo = geo;
		this.rank = rank;
		this.listing_id = listing_id;
		this.locale = locale;
		this.index = index;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 15;
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
				if(localName.equalsIgnoreCase("marketplace_search")) {
					this.marketplace_search= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("tag")) {
					this.tag= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("type")) {
					this.type= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("devtag")) {
					this.devtag= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("page")) {
					this.page= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("keyword")) {
					this.keyword= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("keyword_search")) {
					this.keyword_search= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("browse_id")) {
					this.browse_id= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("zipcode")) {
					this.zipcode= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("area_id")) {
					this.area_id= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("geo")) {
					this.geo= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("rank")) {
					this.rank= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("listing_id")) {
					this.listing_id= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
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
		String type_name = "MarketplaceRequest";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<marketplace_search>");
		if(this.marketplace_search!=null){
			context.writeString(String.valueOf(marketplace_search));
		}
		context.writeString("</marketplace_search>\n");

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

		context.writeString("<page>");
		if(this.page!=null){
			context.writeString(String.valueOf(page));
		}
		context.writeString("</page>\n");

		context.writeString("<keyword>");
		if(this.keyword!=null){
			context.writeString(String.valueOf(keyword));
		}
		context.writeString("</keyword>\n");

		context.writeString("<keyword_search>");
		if(this.keyword_search!=null){
			context.writeString(String.valueOf(keyword_search));
		}
		context.writeString("</keyword_search>\n");

		context.writeString("<browse_id>");
		if(this.browse_id!=null){
			context.writeString(String.valueOf(browse_id));
		}
		context.writeString("</browse_id>\n");

		context.writeString("<zipcode>");
		if(this.zipcode!=null){
			context.writeString(String.valueOf(zipcode));
		}
		context.writeString("</zipcode>\n");

		context.writeString("<area_id>");
		if(this.area_id!=null){
			context.writeString(String.valueOf(area_id));
		}
		context.writeString("</area_id>\n");

		context.writeString("<geo>");
		if(this.geo!=null){
			context.writeString(String.valueOf(geo));
		}
		context.writeString("</geo>\n");

		context.writeString("<rank>");
		if(this.rank!=null){
			context.writeString(String.valueOf(rank));
		}
		context.writeString("</rank>\n");

		context.writeString("<listing_id>");
		if(this.listing_id!=null){
			context.writeString(String.valueOf(listing_id));
		}
		context.writeString("</listing_id>\n");

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

	public void setMarketplace_search(java.lang.String marketplace_search){
		this.marketplace_search = marketplace_search;
	}
	public java.lang.String getMarketplace_search(){
		return marketplace_search;
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
	public void setPage(java.lang.String page){
		this.page = page;
	}
	public java.lang.String getPage(){
		return page;
	}
	public void setKeyword(java.lang.String keyword){
		this.keyword = keyword;
	}
	public java.lang.String getKeyword(){
		return keyword;
	}
	public void setKeyword_search(java.lang.String keyword_search){
		this.keyword_search = keyword_search;
	}
	public java.lang.String getKeyword_search(){
		return keyword_search;
	}
	public void setBrowse_id(java.lang.String browse_id){
		this.browse_id = browse_id;
	}
	public java.lang.String getBrowse_id(){
		return browse_id;
	}
	public void setZipcode(java.lang.String zipcode){
		this.zipcode = zipcode;
	}
	public java.lang.String getZipcode(){
		return zipcode;
	}
	public void setArea_id(java.lang.String area_id){
		this.area_id = area_id;
	}
	public java.lang.String getArea_id(){
		return area_id;
	}
	public void setGeo(java.lang.String geo){
		this.geo = geo;
	}
	public java.lang.String getGeo(){
		return geo;
	}
	public void setRank(java.lang.String rank){
		this.rank = rank;
	}
	public java.lang.String getRank(){
		return rank;
	}
	public void setListing_id(java.lang.String listing_id){
		this.listing_id = listing_id;
	}
	public java.lang.String getListing_id(){
		return listing_id;
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
