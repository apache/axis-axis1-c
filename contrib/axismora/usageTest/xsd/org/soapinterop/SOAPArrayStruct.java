package xsd.org.soapinterop;
/* parameter class */ 
public class SOAPArrayStruct  implements org.apache.axismora.encoding.InOutParameter{
private java.lang.String varString;
private int varInt;
private float varFloat;
private java.lang.String[] varArray;
public SOAPArrayStruct(){
this.varString ="string0";
this.varInt =1;
this.varFloat =2;
this.varArray = new java.lang.String[]{"string3"};
}
	public SOAPArrayStruct(java.lang.String varString,int varInt,float varFloat,java.lang.String[] varArray){
		this.varString = varString;
		this.varInt = varInt;
		this.varFloat = varFloat;
		this.varArray = varArray;
	}
	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		int count = 4;
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
				  }else if (localName.equalsIgnoreCase("varArray")) {
				     xsd.org.soapinterop.ArrayOfstring arrayT3 = (new xsd.org.soapinterop.ArrayOfstring());
				      arrayT3.desierialize(msgdata);
				      this.varArray = arrayT3.getParam();
				    }else
					    throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
				     org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				}//end of while
	return this;

	}
	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://soapinterop.org/xsd";
		String type_name = "SOAPArrayStruct";
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
			context.writeString("<varArray xsi:type=\"soapenc:Array\" soapenc:arrayType=\"ns2:string[]\" xmlns:ns2 = \"http://www.w3.org/2001/XMLSchema\">");
			if(this.varArray!=null){
				context.writeString("\n");
				xsd.org.soapinterop.ArrayOfstring item3 = new xsd.org.soapinterop.ArrayOfstring();
				item3.setParam(varArray);
				org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
				item3.serialize(context);
				}
				context.writeString("</varArray>\n");
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
	public void setVarArray(java.lang.String[] varArray){
		this.varArray = varArray;
	}
	public java.lang.String[] getVarArray(){
		return varArray;
	}
	public boolean equals(Object obj) {
		if(!(obj instanceof xsd.org.soapinterop.SOAPArrayStruct))
			return false;
		xsd.org.soapinterop.SOAPArrayStruct value = (xsd.org.soapinterop.SOAPArrayStruct)obj;
		if(!varString.equals(value.getVarString()))
			return false;
		if(varInt != value.getVarInt())
			return false;
		if(varFloat != value.getVarFloat())
			return false;
		if(varArray!=null && varArray.length !=0){
		if(!varArray[0].equals(value.getVarArray()[0]))
			return false;
		}
		return false;	}
}
