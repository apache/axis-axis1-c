package userguide.example3;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class ArrayOf_tns2_Point  implements org.apache.axismora.encoding.InOutParameter{
	public ArrayOf_tns2_Point(){
	}

	private userguide.example3.Point[] param;
	public userguide.example3.Point[] getParam(){
		return this.param;
	}
	public void setParam(userguide.example3.Point[] param){
		this.param = param;
	}

	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		java.util.Vector obj = new java.util.Vector();
		org.apache.axismora.encoding.AxisPullParser psr = msgdata.getAxisParser();
		javax.xml.namespace.QName arrayname = null;
		while(psr.getState() != org.xmlpull.v1.XmlPullParser.START_TAG) {
			if (psr.getState() == org.xmlpull.v1.XmlPullParser.END_DOCUMENT) {
				throw new org.apache.axis.AxisFault("end of the document");
			}
		psr.next();
		}
		arrayname = new javax.xml.namespace.QName(psr.getNamespace(),psr.getName());
		psr.next();
		//if the type of the next tag is end tag that means the content of element is null
		if(psr.getState() == org.xmlpull.v1.XmlPullParser.END_TAG)
			return null;

		while(!((psr.getState() == org.xmlpull.v1.XmlPullParser.END_TAG) && 
					 arrayname.equals(new javax.xml.namespace.QName(psr.getNamespace(),psr.getName())))){
			if(psr.getState() != org.xmlpull.v1.XmlPullParser.START_TAG){
		psr.next();
				continue;
			}
			userguide.example3.Point  item =(new userguide.example3.Point());
			item.desierialize(msgdata);
			obj.add(item);
		psr.next();
		}

		int length = obj.size();
		userguide.example3.Point[] arr = new userguide.example3.Point[length];
		for(int i = 0;i<length;i++)
			arr[i] = (userguide.example3.Point)obj.get(i);
		 this.param = arr;
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		for (int i = 0; i < param.length; i++) {
			context.writeString("<item"+i+ "  xsi:type=\"ns1:Point\"  xmlns:ns1 = \"http://example3.userguide\">");
			if(param[i]!=null){
				param[i].serialize(context);
			}
			context.writeString("</item"+i+ ">");
		}
	}

}
