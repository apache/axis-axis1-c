package heavytest.performence;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ThirdPartyProductInfo  implements org.apache.axismora.encoding.InOutParameter{
	private heavytest.performence.ThirdPartyProductDetails[] ThirdPartyProductDetails;

	public ThirdPartyProductInfo(){
	}
	public ThirdPartyProductInfo(heavytest.performence.ThirdPartyProductDetails[] ThirdPartyProductDetails){
		this.ThirdPartyProductDetails = ThirdPartyProductDetails;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 1;
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
				if(localName.equalsIgnoreCase("ThirdPartyProductDetails")) {
					heavytest.performence.ArrayOfThirdPartyProductDetails arrayT0 = (new heavytest.performence.ArrayOfThirdPartyProductDetails());
					arrayT0.desierialize(msgdata);
					this.ThirdPartyProductDetails = arrayT0.getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://performence.heavytest";
		String type_name = "ThirdPartyProductInfo";
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		//write the parameters

		context.writeString("<ThirdPartyProductDetails xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:ThirdPartyProductDetails[]\" xmlns:ns2 = \"http://performence.heavytest\">");
		if(this.ThirdPartyProductDetails!=null){
			context.writeString("\n");
			heavytest.performence.ArrayOfThirdPartyProductDetails item0 = new heavytest.performence.ArrayOfThirdPartyProductDetails();
			item0.setParam(ThirdPartyProductDetails);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
			item0.serialize(context);
		}
		context.writeString("</ThirdPartyProductDetails>\n");

	}

	public void setThirdPartyProductDetails(heavytest.performence.ThirdPartyProductDetails[] ThirdPartyProductDetails){
		this.ThirdPartyProductDetails = ThirdPartyProductDetails;
	}
	public heavytest.performence.ThirdPartyProductDetails[] getThirdPartyProductDetails(){
		return ThirdPartyProductDetails;
	}
}
