package com.bookshop.soap;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class KeyPhrase  implements org.apache.axismora.encoding.InOutParameter{
	private java.lang.String KeyPhrase;
	private java.lang.String Type;

	public KeyPhrase(){
	}
	public KeyPhrase(java.lang.String KeyPhrase,java.lang.String Type){
		this.KeyPhrase = KeyPhrase;
		this.Type = Type;
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
				if(localName.equalsIgnoreCase("KeyPhrase")) {
					this.KeyPhrase= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("Type")) {
					this.Type= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soap.bookshop.com";
		String type_name = "KeyPhrase";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<KeyPhrase>");
		if(this.KeyPhrase!=null){
			context.writeString(String.valueOf(KeyPhrase));
		}
		context.writeString("</KeyPhrase>\n");

		context.writeString("<Type>");
		if(this.Type!=null){
			context.writeString(String.valueOf(Type));
		}
		context.writeString("</Type>\n");

	}

	public void setKeyPhrase(java.lang.String KeyPhrase){
		this.KeyPhrase = KeyPhrase;
	}
	public java.lang.String getKeyPhrase(){
		return KeyPhrase;
	}
	public void setType(java.lang.String Type){
		this.Type = Type;
	}
	public java.lang.String getType(){
		return Type;
	}
}
