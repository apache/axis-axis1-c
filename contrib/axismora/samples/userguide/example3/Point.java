package userguide.example3;
/**
 * <p>This class is genarated by the tool WSDL2Ws.
 * It take care of the serialization and the desirialization of
 * the parameter types.
 * except for the serialize(), desirialize() methods it it a bean class.
 * We are specially concerned about the alogorithem used in the desirialize method.
 * If you have any suggestions to improve, your comments are welcome.</p>
 */ 
public class Point  implements org.apache.axismora.encoding.InOutParameter{
	private int x;
	private int z;
	private int y;

	public Point(){
	}
	public Point(int x,int z,int y){
		this.x = x;
		this.z = z;
		this.y = y;
	}


	public org.apache.axismora.encoding.InParameter desierialize(org.apache.axismora.MessageContext msgdata)throws org.apache.axis.AxisFault{
		org.apache.axismora.encoding.AxisPullParser psr = msgdata.getAxisParser();
		int count = 3;
		//come to first start tag
		while(!(psr.getState() == org.xmlpull.v1.XmlPullParser.START_TAG))
			psr.next();
		//skip it says the type
		psr.next();
		//if the type of the next tag is end tag that means the content of element is null
		if(psr.getState() == org.xmlpull.v1.XmlPullParser.END_TAG)
			return null;

		for(int i = 0;i<count;i++) {
			while(!(psr.getState() == org.xmlpull.v1.XmlPullParser.START_TAG))
		psr.next();
				java.lang.String localName = psr.getName();
				if(localName.equalsIgnoreCase("x")) {
					this.x = (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("z")) {
					this.z = (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				}else if (localName.equalsIgnoreCase("y")) {
					this.y = (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata)).getParam();
				}else
					throw new org.apache.axis.AxisFault("unknown tag find "+ localName);
		psr.next();
		}//end of for loop
		return this;

	}

	public void serialize(org.apache.axis.encoding.SerializationContext context)throws java.io.IOException{
		java.lang.String m_URI ="http://example3.userguide";
		java.lang.String type_name = "Point";
		//write the parameters

		context.writeString("<x>");
			context.writeSafeString(java.lang.String.valueOf(x));
		context.writeString("</x>\n");

		context.writeString("<z>");
			context.writeSafeString(java.lang.String.valueOf(z));
		context.writeString("</z>\n");

		context.writeString("<y>");
			context.writeSafeString(java.lang.String.valueOf(y));
		context.writeString("</y>\n");

	}

	public void setX(int x){
		this.x = x;
	}
	public int getX(){
		return x;
	}
	public void setZ(int z){
		this.z = z;
	}
	public int getZ(){
		return z;
	}
	public void setY(int y){
		this.y = y;
	}
	public int getY(){
		return y;
	}
	public void init(){
		org.apache.axismora.wrappers.simpleType.IntParam tparam0 = new org.apache.axismora.wrappers.simpleType.IntParam();
		tparam0.init();
		x = tparam0.getParam();
		org.apache.axismora.wrappers.simpleType.IntParam tparam1 = new org.apache.axismora.wrappers.simpleType.IntParam();
		tparam1.init();
		z = tparam1.getParam();
		org.apache.axismora.wrappers.simpleType.IntParam tparam2 = new org.apache.axismora.wrappers.simpleType.IntParam();
		tparam2.init();
		y = tparam2.getParam();
	}
}
