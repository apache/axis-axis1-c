package userguide.example3;
/* parameter class */
public class Point implements org.apache.axismora.encoding.InOutParameter {
    private int x;
    private int y;
    private int z;
    public Point() {
        this.x = 0;
        this.y = 1;
        this.z = 2;
    }
    public Point(int x, int y, int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    public org.apache.axismora.encoding.InParameter desierialize(
        org.apache.axismora.MessageContext msgdata)
        throws org.apache.axis.AxisFault {
        int count = 3;
        if (org.apache.axismora.wsdl2ws.java.ParmWriter.tag == null)
            org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
        //come to first start tag
        while (!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType()
            == org.xmlpull.v1.XmlPullParser.START_TAG))
            org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
        //skip it says the type
        org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
        //if the type of the next tag is end tag that means the content of element is null
        if (org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType()
            == org.xmlpull.v1.XmlPullParser.END_TAG)
            return null;
        for (int i = 0; i < count; i++) {
            while (!(org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getType()
                == org.xmlpull.v1.XmlPullParser.START_TAG))
                org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
            String localName =
                org.apache.axismora.wsdl2ws.java.ParmWriter.tag.getLocalpart();
            if (localName.equalsIgnoreCase("x")) {
                this.x =
                    new org
                        .apache
                        .axismora
                        .wrappers
                        .simpleType
                        .IntParam(msgdata)
                        .getParam();
            } else if (localName.equalsIgnoreCase("y")) {
                this.y =
                    (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata))
                        .getParam();
            } else if (localName.equalsIgnoreCase("z")) {
                this.z =
                    (new org.apache.axismora.wrappers.simpleType.IntParam(msgdata))
                        .getParam();
            } else
                throw new org.apache.axis.AxisFault("unknown tag find " + localName);
            org.apache.axismora.wsdl2ws.java.ParmWriter.tag = msgdata.getTag();
        } //end of while
        return this;

    }
    public void serialize(org.apache.axis.encoding.SerializationContext context)
        throws java.io.IOException {
        String m_URI = "http://example3.userguide";
        String type_name = "Point";
        org.apache.axismora.wsdl2ws.java.ParmWriter.tagWritten = false;
        //write the parameters
        context.writeString("<x>");
        context.writeString(String.valueOf(x));
        context.writeString("</x>\n");
        context.writeString("<y>");
        context.writeString(String.valueOf(y));
        context.writeString("</y>\n");
        context.writeString("<z>");
        context.writeString(String.valueOf(z));
        context.writeString("</z>\n");
    }

    public void setX(int x) {
        this.x = x;
    }
    public int getX() {
        return x;
    }
    public void setY(int y) {
        this.y = y;
    }
    public int getY() {
        return y;
    }
    public void setZ(int z) {
        this.z = z;
    }
    public int getZ() {
        return z;
    }
    public boolean equals(Object obj) {
        if (!(obj instanceof userguide.example3.Point))
            return false;
        userguide.example3.Point value = (userguide.example3.Point) obj;
        if (x != value.getX())
            return false;
        if (y != value.getY())
            return false;
        if (z != value.getZ())
            return false;
        return false;
    }
}
