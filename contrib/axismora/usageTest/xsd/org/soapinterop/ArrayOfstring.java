package xsd.org.soapinterop;
/* parameter class */ 
public class ArrayOfstring  implements org.apache.axismora.encoding.InOutParameter{
public ArrayOfstring(){
}
	private java.lang.String[] param;
	public java.lang.String[] getParam(){
		return this.param;	
}
	public void setParam(java.lang.String[] param){
		this.param = param;	
}
	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
	try{
		java.util.Vector obj = new java.util.Vector();
		javax.xml.namespace.QName arrayname = null;
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag == null)
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();

		while(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() != org.xmlpull.v1.XmlPullParser.START_TAG) {
			if (org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_DOCUMENT) {
			throw new org.apache.axis.AxisFault("end of the document");
			}
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}
		arrayname = new javax.xml.namespace.QName(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getUri(),org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart());
		org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		//if the type of the next tag is end tag that means the content of element is null
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG)			return null;
		while(!((org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG) && 
					 arrayname.equals(new javax.xml.namespace.QName(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getUri(),org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart())))){
			if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() != org.xmlpull.v1.XmlPullParser.START_TAG){
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				continue;
			}
			org.apache.axismora.wrappers.simpleType.StringParam item =(new org.apache.axismora.wrappers.simpleType.StringParam(msgdata));
					obj.add(item);
			 org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}
		int length = obj.size();
		java.lang.String[] arr = new java.lang.String[length];
		for(int i = 0;i<length;i++)
			arr[i] = ((org.apache.axismora.wrappers.simpleType.StringParam)obj.get(i)).getParam();
		 this.param = arr;
	} catch (java.io.IOException e) {
		msgdata.setSoapFault(new org.apache.axis.message.SOAPFault(	new org.apache.axis.AxisFault("error", e)));
	}	return this;

	}
	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		try{
				String m_URI ="http://soapinterop.org/xsd";
				String type_name = "ArrayOfstring";
		boolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;
		if(writeOutTag)
			context.writeString("<prf:" + type_name + " xmlns:prf =\"" + m_URI + "\" >");
		org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		for (int i = 0; i < param.length; i++) {
			context.writeString("<item"+i+ "  xsi:type=\"ns3:string\"  xmlns:ns3 = \"http://www.w3.org/2001/XMLSchema\">");
			if(param[i]!=null){
				context.writeString(String.valueOf(param[i]));
				}		context.writeString("</item"+i+ ">");
		}
		//otherwise name of parameter written by upper level
		//write the end tag
		if(writeOutTag)
		context.writeString("</prf:" + type_name + ">");
	} catch (java.io.IOException e) {
		e.printStackTrace();
	}
	}

}
