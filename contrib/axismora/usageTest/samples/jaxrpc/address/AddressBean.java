package samples.jaxrpc.address;
/* parameter class */ 
public class AddressBean  implements org.apache.axismora.encoding.InOutParameter{
private java.lang.String street;
private int postcode;
public AddressBean(){
this.street ="string0";
this.postcode =1;
}
	public AddressBean(java.lang.String street,int postcode){
		this.street = street;
		this.postcode = postcode;
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
		//if the type of the next tag is end tag that means the content of element is null		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag == org.xmlpull.v1.XmlPullParser.END_TAG)			return null;
		for(int i = 0;i<count;i++) {
			while(!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.START_TAG))
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				String localName = org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart();
				if(localName.equalsIgnoreCase("street")) {
				      this.street= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("postcode")) {
				      this.postcode= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				    }else
					    throw new org.apache.axis.AxisFault("unknown tag find "+ localName);				     org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				}//end of while
	return this;

	}
	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://address.jaxrpc.samples";
		String type_name = "AddressBean";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
			//write the parameters
			context.writeString("<street>");
			if(this.street!=null){
				context.writeString(String.valueOf(street));
				}
				context.writeString("</street>\n");
			context.writeString("<postcode>");
				context.writeString(String.valueOf(postcode));
				context.writeString("</postcode>\n");
	}

	public void setStreet(java.lang.String street){
		this.street = street;
	}
	public java.lang.String getStreet(){
		return street;
	}
	public void setPostcode(int postcode){
		this.postcode = postcode;
	}
	public int getPostcode(){
		return postcode;
	}
	public boolean equals(Object obj) {
		if(!(obj instanceof samples.jaxrpc.address.AddressBean))
			return false;
		samples.jaxrpc.address.AddressBean value = (samples.jaxrpc.address.AddressBean)obj;
		if(street.equals(value.getStreet()))
			return false;
		if(postcode != value.getPostcode())
			return false;
		return false;	}
}
