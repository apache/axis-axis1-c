package googleSearch;
/* parameter class */ 
public class DirectoryCategory  implements org.apache.axismora.encoding.InOutParameter{
private java.lang.String specialEncoding;
private java.lang.String fullViewableName;
public DirectoryCategory(){
this.specialEncoding ="string0";
this.fullViewableName ="string1";
}
	public DirectoryCategory(java.lang.String specialEncoding,java.lang.String fullViewableName){
		this.specialEncoding = specialEncoding;
		this.fullViewableName = fullViewableName;
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
		for(int i = 0;i<count;i++) {
			while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				String localName = org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart();
				if(localName.equalsIgnoreCase("specialEncoding")) {
				      this.specialEncoding= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("fullViewableName")) {
				      this.fullViewableName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				    }else
					    throw new org.apache.axis.AxisFault("unknown tag find "+ localName);				     org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				}//end of while
			return this;	

	}
	public void serialize(org.apache.axis.encoding.SerializationContext context){
		try{
		String m_URI ="urn:GoogleSearch";
		String type_name = "DirectoryCategory";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
			//write the parameters
			context.writeString("<specialEncoding>");
			context.writeString(String.valueOf(specialEncoding));
			context.writeString("</specialEncoding>\n");
			context.writeString("<fullViewableName>");
			context.writeString(String.valueOf(fullViewableName));
			context.writeString("</fullViewableName>\n");
	}catch(java.io.IOException e){
	     e.printStackTrace();
	 }
	}

	public void setSpecialEncoding(java.lang.String specialEncoding){
		this.specialEncoding = specialEncoding;
	}
	public java.lang.String getSpecialEncoding(){
		return specialEncoding;
	}
	public void setFullViewableName(java.lang.String fullViewableName){
		this.fullViewableName = fullViewableName;
	}
	public java.lang.String getFullViewableName(){
		return fullViewableName;
	}
}
