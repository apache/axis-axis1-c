package googleSearch;
/* parameter class */ 
public class GoogleSearchResult  implements org.apache.axismora.encoding.InOutParameter{
private googleSearch.DirectoryCategory[] directoryCategories;
private int estimatedTotalResultsCount;
private boolean documentFiltering;
private double searchTime;
private googleSearch.ResultElement[] resultElements;
private int endIndex;
private java.lang.String searchTips;
private java.lang.String searchComments;
private int startIndex;
private java.lang.String searchQuery;
private boolean estimateIsExact;
public GoogleSearchResult(){
this.directoryCategories = new googleSearch.DirectoryCategory[]{new googleSearch.DirectoryCategory()};
this.estimatedTotalResultsCount =1;
this.documentFiltering =false;
this.searchTime =3;
this.resultElements = new googleSearch.ResultElement[]{new googleSearch.ResultElement()};
this.endIndex =5;
this.searchTips ="string6";
this.searchComments ="string7";
this.startIndex =8;
this.searchQuery ="string9";
this.estimateIsExact =false;
}
	public GoogleSearchResult(googleSearch.DirectoryCategory[] directoryCategories,int estimatedTotalResultsCount,boolean documentFiltering,double searchTime,googleSearch.ResultElement[] resultElements,int endIndex,java.lang.String searchTips,java.lang.String searchComments,int startIndex,java.lang.String searchQuery,boolean estimateIsExact){
		this.directoryCategories = directoryCategories;
		this.estimatedTotalResultsCount = estimatedTotalResultsCount;
		this.documentFiltering = documentFiltering;
		this.searchTime = searchTime;
		this.resultElements = resultElements;
		this.endIndex = endIndex;
		this.searchTips = searchTips;
		this.searchComments = searchComments;
		this.startIndex = startIndex;
		this.searchQuery = searchQuery;
		this.estimateIsExact = estimateIsExact;
	}
	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 11;
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
				if(localName.equalsIgnoreCase("directoryCategories")) {
				     googleSearch.DirectoryCategoryArray arrayT0 = (new googleSearch.DirectoryCategoryArray());
				      arrayT0.desierialize(msgdata);
				      this.directoryCategories = arrayT0.getParam();
				  }else if (localName.equalsIgnoreCase("estimatedTotalResultsCount")) {
				      this.estimatedTotalResultsCount= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("documentFiltering")) {
				      this.documentFiltering= (new org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("searchTime")) {
				      this.searchTime= (new org.apache.axismora.wrappers.simpleType.DoubleParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("resultElements")) {
				     googleSearch.ResultElementArray arrayT4 = (new googleSearch.ResultElementArray());
				      arrayT4.desierialize(msgdata);
				      this.resultElements = arrayT4.getParam();
				  }else if (localName.equalsIgnoreCase("endIndex")) {
				      this.endIndex= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("searchTips")) {
				      this.searchTips= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("searchComments")) {
				      this.searchComments= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("startIndex")) {
				      this.startIndex= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("searchQuery")) {
				      this.searchQuery= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("estimateIsExact")) {
				      this.estimateIsExact= (new org.apache.axismora.wrappers.simpleType.BooleanParam(msgdata)).getParam();
				    }else
					    throw new org.apache.axis.AxisFault("unknown tag find "+ localName);				     org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				}//end of while
		return this;
	}
	public void serialize(org.apache.axis.encoding.SerializationContext context){
		try{
		String m_URI ="urn:GoogleSearch";
		String type_name = "GoogleSearchResult";
			//write start tag
		boolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;
		if(writeOutTag)
			context.writeString("<prf:" + type_name + "  xmlns:prf =\""+m_URI +"\">\n");
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
			//write the parameters
			context.writeString("<directoryCategories>");
			context.writeString("\n");
googleSearch.DirectoryCategoryArray item0 = new googleSearch.DirectoryCategoryArray();
item0.setParam(directoryCategories);
		org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
item0.serialize(context);
			context.writeString("</directoryCategories>\n");
			context.writeString("<estimatedTotalResultsCount>");
			context.writeString(String.valueOf(estimatedTotalResultsCount));
			context.writeString("</estimatedTotalResultsCount>\n");
			context.writeString("<documentFiltering>");
			context.writeString(String.valueOf(documentFiltering));
			context.writeString("</documentFiltering>\n");
			context.writeString("<searchTime>");
			context.writeString(String.valueOf(searchTime));
			context.writeString("</searchTime>\n");
			context.writeString("<resultElements>");
			context.writeString("\n");
googleSearch.ResultElementArray item4 = new googleSearch.ResultElementArray();
item4.setParam(resultElements);
		org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
item4.serialize(context);
			context.writeString("</resultElements>\n");
			context.writeString("<endIndex>");
			context.writeString(String.valueOf(endIndex));
			context.writeString("</endIndex>\n");
			context.writeString("<searchTips>");
			context.writeString(String.valueOf(searchTips));
			context.writeString("</searchTips>\n");
			context.writeString("<searchComments>");
			context.writeString(String.valueOf(searchComments));
			context.writeString("</searchComments>\n");
			context.writeString("<startIndex>");
			context.writeString(String.valueOf(startIndex));
			context.writeString("</startIndex>\n");
			context.writeString("<searchQuery>");
			context.writeString(String.valueOf(searchQuery));
			context.writeString("</searchQuery>\n");
			context.writeString("<estimateIsExact>");
			context.writeString(String.valueOf(estimateIsExact));
			context.writeString("</estimateIsExact>\n");
			//write the end tag
		if(writeOutTag)
			context.writeString("</prf:" + type_name + ">\n");
	}catch(java.io.IOException e){
	     e.printStackTrace();
	 }
	}

	public void setDirectoryCategories(googleSearch.DirectoryCategory[] directoryCategories){
		this.directoryCategories = directoryCategories;
	}
	public googleSearch.DirectoryCategory[] getDirectoryCategories(){
		return directoryCategories;
	}
	public void setEstimatedTotalResultsCount(int estimatedTotalResultsCount){
		this.estimatedTotalResultsCount = estimatedTotalResultsCount;
	}
	public int getEstimatedTotalResultsCount(){
		return estimatedTotalResultsCount;
	}
	public void setDocumentFiltering(boolean documentFiltering){
		this.documentFiltering = documentFiltering;
	}
	public boolean getDocumentFiltering(){
		return documentFiltering;
	}
	public void setSearchTime(double searchTime){
		this.searchTime = searchTime;
	}
	public double getSearchTime(){
		return searchTime;
	}
	public void setResultElements(googleSearch.ResultElement[] resultElements){
		this.resultElements = resultElements;
	}
	public googleSearch.ResultElement[] getResultElements(){
		return resultElements;
	}
	public void setEndIndex(int endIndex){
		this.endIndex = endIndex;
	}
	public int getEndIndex(){
		return endIndex;
	}
	public void setSearchTips(java.lang.String searchTips){
		this.searchTips = searchTips;
	}
	public java.lang.String getSearchTips(){
		return searchTips;
	}
	public void setSearchComments(java.lang.String searchComments){
		this.searchComments = searchComments;
	}
	public java.lang.String getSearchComments(){
		return searchComments;
	}
	public void setStartIndex(int startIndex){
		this.startIndex = startIndex;
	}
	public int getStartIndex(){
		return startIndex;
	}
	public void setSearchQuery(java.lang.String searchQuery){
		this.searchQuery = searchQuery;
	}
	public java.lang.String getSearchQuery(){
		return searchQuery;
	}
	public void setEstimateIsExact(boolean estimateIsExact){
		this.estimateIsExact = estimateIsExact;
	}
	public boolean getEstimateIsExact(){
		return estimateIsExact;
	}
	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	/*public boolean equals(Object obj) {
			if(!(obj instanceof GoogleSearchResult))
			return false;
		GoogleSearchResult value = (GoogleSearchResult)obj;	
		if(this.directoryCategories.equals(value.directoryCategories)
			&& (this.documentFiltering == value.documentFiltering)
			&& (this.estimateIsExact == value.getEstimateIsExact())
			&& (this.endIndex == value.endIndex)
			&& (this.estimatedTotalResultsCount == value.estimatedTotalResultsCount)
			&& (this.)
	}*/

}
