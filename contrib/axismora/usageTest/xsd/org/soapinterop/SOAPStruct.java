package xsd.org.soapinterop;
/* parameter class */ 
public class SOAPStruct  implements org.apache.axismora.encoding.InOutParameter{
private java.lang.String varString;
private int varInt;
private float varFloat;
public SOAPStruct(){
this.varString ="string0";
this.varInt =1;
this.varFloat =2;
}
	public SOAPStruct(java.lang.String varString,int varInt,float varFloat){
		this.varString = varString;
		this.varInt = varInt;
		this.varFloat = varFloat;
	}
	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 3;
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
				if(localName.equalsIgnoreCase("varString")) {
				      this.varString= new org.apache.axismora.wrappers.simpleType.StringParam(msgdata).getParam();
				  }else if (localName.equalsIgnoreCase("varInt")) {
				      this.varInt= (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				  }else if (localName.equalsIgnoreCase("varFloat")) {
				      this.varFloat= (new org.apache.axismora.wrappers.simpleType.FloatParam(msgdata)).getParam();
				    }else
					    throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				     org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				}//end of while
	return this;

	}
	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soapinterop.org/xsd";
		String type_name = "SOAPStruct";
			//write start tag
		boolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;
		if(writeOutTag)
			context.writeString("<prf:" + type_name + "  xmlns:prf =\""+m_URI +"\">\n");
			org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
			//write the parameters
			context.writeString("<varString>");
			if(this.varString!=null){
				context.writeString(String.valueOf(varString));
				}
				context.writeString("</varString>\n");
			context.writeString("<varInt>");
				context.writeString(String.valueOf(varInt));
				context.writeString("</varInt>\n");
			context.writeString("<varFloat>");
				context.writeString(String.valueOf(varFloat));
				context.writeString("</varFloat>\n");
			//write the end tag
		if(writeOutTag)
			context.writeString("</prf:" + type_name + ">\n");
	}

	public void setVarString(java.lang.String varString){
		this.varString = varString;
	}
	public java.lang.String getVarString(){
		return varString;
	}
	public void setVarInt(int varInt){
		this.varInt = varInt;
	}
	public int getVarInt(){
		return varInt;
	}
	public void setVarFloat(float varFloat){
		this.varFloat = varFloat;
	}
	public float getVarFloat(){
		return varFloat;
	}
	public boolean equals(Object obj) {
		if(!(obj instanceof xsd.org.soapinterop.SOAPStruct))
			return false;
		xsd.org.soapinterop.SOAPStruct value = (xsd.org.soapinterop.SOAPStruct)obj;
		if(!varString.equals(value.getVarString()))
			return false;
		if(varInt != value.getVarInt())
			return false;
		if(varFloat != value.getVarFloat())
			return false;
		return false;	}
}
