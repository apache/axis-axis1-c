package types.usageTests;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ArrayOf_xsd_long  implements org.apache.axismora.encoding.InOutParameter{
	public ArrayOf_xsd_long(){
	}

	private long[] param;
	public long[] getParam(){
		return this.param;
	}
	public void setParam(long[] param){
		this.param = param;
	}

	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
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
		if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG)
			return null;

		while(!((org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG) && 
					 arrayname.equals(new javax.xml.namespace.QName(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getUri(),org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart())))){
			if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() != org.xmlpull.v1.XmlPullParser.START_TAG){
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				continue;
			}
			org.apache.axismora.wrappers.simpleType.LongParam item =(new org.apache.axismora.wrappers.simpleType.LongParam(msgdata));
					obj.add(item);
			org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}

		int length = obj.size();
		long[] arr = new long[length];
		for(int i = 0;i<length;i++)
			arr[i] = ((org.apache.axismora.wrappers.simpleType.LongParam)obj.get(i)).getParam();
		 this.param = arr;
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		String m_URI ="http://usageTests/types";
		String type_name = "ArrayOf_xsd_long";
		boolean writeOutTag = !org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten;
		if(writeOutTag){
			context.writeString("<prf:");
			context.writeString(type_name);
			context.writeString(" xmlns:prf =\"");
			context.writeString(m_URI);
			context.writeString("\" >");
		}
		org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		for (int i = 0; i < param.length; i++) {
			context.writeString("<item"+i+ "  xsi:type=\"ns49:long\"  xmlns:ns49 = \"http://www.w3.org/2001/XMLSchema\">");
				context.writeString(String.valueOf(param[i]));
			context.writeString("</item"+i+ ">");
		}
		//name of parameter will be written by upper level
		//write the end tag
		if(writeOutTag){
			context.writeString("</prf:");
			context.writeString(type_name);
			context.writeString(">");
		}
	}

}
