package googleSearch;
/* parameter class */ 
public class DirectoryCategoryArray  implements org.apache.axismora.encoding.InOutParameter{
public DirectoryCategoryArray(){
}
	private googleSearch.DirectoryCategory[] param;
	public googleSearch.DirectoryCategory[] getParam(){
		return this.param;	
}
	public void setParam(googleSearch.DirectoryCategory[] param){
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
		while(!((org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() == org.xmlpull.v1.XmlPullParser.END_TAG) && 
					 arrayname.equals(new javax.xml.namespace.QName(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getUri(),org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart())))){
			if(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType() != org.xmlpull.v1.XmlPullParser.START_TAG){
				org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
				continue;
			}
			googleSearch.DirectoryCategory  item =(new googleSearch.DirectoryCategory());
			item.desierialize(msgdata);
			obj.add(item);
			 org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
		}
		int length = obj.size();
		googleSearch.DirectoryCategory[] arr = new googleSearch.DirectoryCategory[length];
		for(int i = 0;i<length;i++)
			arr[i] = (googleSearch.DirectoryCategory)obj.get(i);
		 this.param = arr;
		return this;
	}
	public void serialize(org.apache.axis.encoding.SerializationContext context){
		try{
				String m_URI ="urn:GoogleSearch";
				String type_name = "DirectoryCategoryArray";
		org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
		for (int i = 0; i < param.length; i++) {
			context.writeString("<item"+i+ "  xsi:type=\"ns2:DirectoryCategory\"  xmlns:ns2 = \"urn:GoogleSearch\">");
		org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = true;
				param[i].serialize(context);
		context.writeString("</item"+i+ ">");
		}
		//otherwise name of parameter written by upper level
	} catch (java.io.IOException e) {
		e.printStackTrace();
	}
	}

}
