package heavytest.performence;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class BrowseNode  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String BrowseId;
	private java.lang.String BrowseName;

	public BrowseNode(){
	}
	public BrowseNode(java.lang.String BrowseId,java.lang.String BrowseName){
		this.BrowseId = BrowseId;
		this.BrowseName = BrowseName;
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
				if(localName.equalsIgnoreCase("BrowseId")) {
					this.BrowseId= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("BrowseName")) {
					this.BrowseName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://performence.heavytest";
		String type_name = "BrowseNode";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<BrowseId>");
		if(this.BrowseId!=null){
			context.writeString(String.valueOf(BrowseId));
		}
		context.writeString("</BrowseId>\n");

		context.writeString("<BrowseName>");
		if(this.BrowseName!=null){
			context.writeString(String.valueOf(BrowseName));
		}
		context.writeString("</BrowseName>\n");

	}

	public void setBrowseId(java.lang.String BrowseId){
		this.BrowseId = BrowseId;
	}
	public java.lang.String getBrowseId(){
		return BrowseId;
	}
	public void setBrowseName(java.lang.String BrowseName){
		this.BrowseName = BrowseName;
	}
	public java.lang.String getBrowseName(){
		return BrowseName;
	}
}
