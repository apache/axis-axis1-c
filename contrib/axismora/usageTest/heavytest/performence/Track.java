package heavytest.performence;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Track  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String TrackName;
	private java.lang.String ByArtist;

	public Track(){
	}
	public Track(java.lang.String TrackName,java.lang.String ByArtist){
		this.TrackName = TrackName;
		this.ByArtist = ByArtist;
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
				if(localName.equalsIgnoreCase("TrackName")) {
					this.TrackName= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("ByArtist")) {
					this.ByArtist= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://performence.heavytest";
		String type_name = "Track";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<TrackName>");
		if(this.TrackName!=null){
			context.writeString(String.valueOf(TrackName));
		}
		context.writeString("</TrackName>\n");

		context.writeString("<ByArtist>");
		if(this.ByArtist!=null){
			context.writeString(String.valueOf(ByArtist));
		}
		context.writeString("</ByArtist>\n");

	}

	public void setTrackName(java.lang.String TrackName){
		this.TrackName = TrackName;
	}
	public java.lang.String getTrackName(){
		return TrackName;
	}
	public void setByArtist(java.lang.String ByArtist){
		this.ByArtist = ByArtist;
	}
	public java.lang.String getByArtist(){
		return ByArtist;
	}
}
