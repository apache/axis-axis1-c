package addressFetcher2;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Address  implements org.apache.axismora.encoding.InOutParameter{
	private int streetNum;
	private java.lang.String streetName;
	private java.lang.String city;
	private addressFetcher2.StateType state;
	private int zip;
	private addressFetcher2.Phone phoneNumber;

	public Address(){
	}
	public Address(int streetNum,java.lang.String streetName,java.lang.String city,addressFetcher2.StateType state,int zip,addressFetcher2.Phone phoneNumber){
		this.streetNum = streetNum;
		this.streetName = streetName;
		this.city = city;
		this.state = state;
		this.zip = zip;
		this.phoneNumber = phoneNumber;
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
				if(localName.equalsIgnoreCase("streetNum")) {
					this.streetNum= new org.apache.axismora.wrappers.simpleType.IntParam(msgdata).getParam();
				}else if (localName.equalsIgnoreCase("streetName")) {
					this.streetName= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("city")) {
					this.city= (new org.apache.axismora.wrappers.simpleType.StringParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("state")) {
					this.state= (new addressFetcher2.StateType());
					this.state.desierialize(msgdata);
				}else if (localName.equalsIgnoreCase("zip")) {
					this.zip= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("phoneNumber")) {
					this.phoneNumber= (new addressFetcher2.Phone());
					this.phoneNumber.desierialize(msgdata);
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="urn:AddressFetcher2";
		String type_name = "address";
		//write start tag
		boolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;
		if(writeOutTag){
			//write the start tag
			context.writeString("<prf:");
			context.writeString(type_name);
			context.writeString("  xmlns:prf =\"");
			context.writeString(m_URI);
			context.writeString("\">\n");

		}
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<streetNum>");
			context.writeString(String.valueOf(streetNum));
		context.writeString("</streetNum>\n");

		context.writeString("<streetName>");
		if(this.streetName!=null){
			context.writeString(String.valueOf(streetName));
		}
		context.writeString("</streetName>\n");

		context.writeString("<city>");
		if(this.city!=null){
			context.writeString(String.valueOf(city));
		}
		context.writeString("</city>\n");

		context.writeString("<state>");
		if(this.state!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			state.serialize(context);
		}
		context.writeString("</state>\n");

		context.writeString("<zip>");
			context.writeString(String.valueOf(zip));
		context.writeString("</zip>\n");

		context.writeString("<phoneNumber>");
		if(this.phoneNumber!=null){
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			phoneNumber.serialize(context);
		}
		context.writeString("</phoneNumber>\n");

		//write the end tag
		if(writeOutTag){
		context.writeString("</prf:");		context.writeString(type_name);
		context.writeString(">\n");
		}
	}

	public void setStreetNum(int streetNum){
		this.streetNum = streetNum;
	}
	public int getStreetNum(){
		return streetNum;
	}
	public void setStreetName(java.lang.String streetName){
		this.streetName = streetName;
	}
	public java.lang.String getStreetName(){
		return streetName;
	}
	public void setCity(java.lang.String city){
		this.city = city;
	}
	public java.lang.String getCity(){
		return city;
	}
	public void setState(addressFetcher2.StateType state){
		this.state = state;
	}
	public addressFetcher2.StateType getState(){
		return state;
	}
	public void setZip(int zip){
		this.zip = zip;
	}
	public int getZip(){
		return zip;
	}
	public void setPhoneNumber(addressFetcher2.Phone phoneNumber){
		this.phoneNumber = phoneNumber;
	}
	public addressFetcher2.Phone getPhoneNumber(){
		return phoneNumber;
	}
}
