package googleSearch;
/* parameter class */ 
public class ResultElement  implements org.apache.axismora.encoding.InOutParameter{
private java.lang.String cachedSize;
private java.lang.String hostName;
private java.lang.String snippet;
private googleSearch.DirectoryCategory directoryCategory;
private boolean relatedInformationPresent;
private java.lang.String directoryTitle;
private java.lang.String summary;
private java.lang.String URL;
private java.lang.String title;
public ResultElement(){
this.cachedSize ="string0";
this.hostName ="string1";
this.snippet ="string2";
this.directoryCategory =new googleSearch.DirectoryCategory();
this.relatedInformationPresent =false;
this.directoryTitle ="string5";
this.summary ="string6";
this.URL ="string7";
this.title ="string8";
}
	public ResultElement(java.lang.String cachedSize,java.lang.String hostName,java.lang.String snippet,googleSearch.DirectoryCategory directoryCategory,boolean relatedInformationPresent,java.lang.String directoryTitle,java.lang.String summary,java.lang.String URL,java.lang.String title){
		this.cachedSize = cachedSize;
		this.hostName = hostName;
		this.snippet = snippet;
		this.directoryCategory = directoryCategory;
		this.relatedInformationPresent = relatedInformationPresent;
		this.directoryTitle = directoryTitle;
		this.summary = summary;
		this.URL = URL;
		this.title = title;
	}
	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 9;
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag == null)
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag= msgdata.getTag();
		//come to first start tag
		while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		//skip it says the type
org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		for(int i = 0;i<count;i++) {
			while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				String localName = org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart();
				if(localName.equalsIgnoreCase("cachedSize")) {
				      this.cachedSize= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("hostName")) {
				      this.hostName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("snippet")) {
				      this.snippet= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("directoryCategory")) {
				      this.directoryCategory= (new googleSearch.DirectoryCategory());
				      this.directoryCategory.desierialize(msgdata);
				  }else if (localName.equalsIgnoreCase("relatedInformationPresent")) {
				      this.relatedInformationPresent= (new org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("directoryTitle")) {
				      this.directoryTitle= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("summary")) {
				      this.summary= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("URL")) {
				      this.URL= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("title")) {
				      this.title= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				    }else
					    throw new org.apache.axis.AxisFault("unknown tag find "+ localName);				     org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				}//end of while
			return this;	

	}
	public void serialize(org.apache.axis.encoding.SerializationContext context){
		try{
		String m_URI ="urn:GoogleSearch";
		String type_name = "ResultElement";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
			//write the parameters
			context.writeString("<cachedSize>");
			context.writeString(String.valueOf(cachedSize));
			context.writeString("</cachedSize>\n");
			context.writeString("<hostName>");
			context.writeString(String.valueOf(hostName));
			context.writeString("</hostName>\n");
			context.writeString("<snippet>");
			context.writeString(String.valueOf(snippet));
			context.writeString("</snippet>\n");
			context.writeString("<directoryCategory>");
		org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			directoryCategory.serialize(context);
			context.writeString("</directoryCategory>\n");
			context.writeString("<relatedInformationPresent>");
			context.writeString(String.valueOf(relatedInformationPresent));
			context.writeString("</relatedInformationPresent>\n");
			context.writeString("<directoryTitle>");
			context.writeString(String.valueOf(directoryTitle));
			context.writeString("</directoryTitle>\n");
			context.writeString("<summary>");
			context.writeString(String.valueOf(summary));
			context.writeString("</summary>\n");
			context.writeString("<URL>");
			context.writeString(String.valueOf(URL));
			context.writeString("</URL>\n");
			context.writeString("<title>");
			context.writeString(String.valueOf(title));
			context.writeString("</title>\n");
	}catch(java.io.IOException e){
	     e.printStackTrace();
	 }
	}

	public void setCachedSize(java.lang.String cachedSize){
		this.cachedSize = cachedSize;
	}
	public java.lang.String getCachedSize(){
		return cachedSize;
	}
	public void setHostName(java.lang.String hostName){
		this.hostName = hostName;
	}
	public java.lang.String getHostName(){
		return hostName;
	}
	public void setSnippet(java.lang.String snippet){
		this.snippet = snippet;
	}
	public java.lang.String getSnippet(){
		return snippet;
	}
	public void setDirectoryCategory(googleSearch.DirectoryCategory directoryCategory){
		this.directoryCategory = directoryCategory;
	}
	public googleSearch.DirectoryCategory getDirectoryCategory(){
		return directoryCategory;
	}
	public void setRelatedInformationPresent(boolean relatedInformationPresent){
		this.relatedInformationPresent = relatedInformationPresent;
	}
	public boolean getRelatedInformationPresent(){
		return relatedInformationPresent;
	}
	public void setDirectoryTitle(java.lang.String directoryTitle){
		this.directoryTitle = directoryTitle;
	}
	public java.lang.String getDirectoryTitle(){
		return directoryTitle;
	}
	public void setSummary(java.lang.String summary){
		this.summary = summary;
	}
	public java.lang.String getSummary(){
		return summary;
	}
	public void setURL(java.lang.String URL){
		this.URL = URL;
	}
	public java.lang.String getURL(){
		return URL;
	}
	public void setTitle(java.lang.String title){
		this.title = title;
	}
	public java.lang.String getTitle(){
		return title;
	}
}
