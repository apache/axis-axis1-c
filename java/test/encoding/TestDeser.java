package test.encoding;

import java.lang.reflect.Array;
import org.apache.axis.Constants;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.message.*;
import org.apache.axis.encoding.*;
import org.apache.axis.server.AxisServer;
import org.apache.axis.utils.QName;
import org.xml.sax.InputSource;
import java.io.*;
import java.util.*;

import junit.framework.TestCase;

/** 
 * Test deserialization of SOAP responses
 */
public class TestDeser extends TestCase {

    private String header;
    private String footer;
    private AxisServer server = new AxisServer();

    public TestDeser(String name) {
        this(name, Constants.URI_CURRENT_SCHEMA_XSI, 
                   Constants.URI_CURRENT_SCHEMA_XSD);
    }

    public TestDeser(String name, String NS_XSI, String NS_XSD) {
        super(name);

        header =
            "<?xml version=\"1.0\"?>\n" +
            "<soap:Envelope " +
              "xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\" " +
              "xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\" " +
              "xmlns:xsi=\"" + NS_XSI + "\" " +
              "xmlns:xsd=\"" + NS_XSD + "\">\n" +
              "<soap:Body>\n" +
                "<methodResult xmlns=\"http://tempuri.org/\">\n";

        footer =
                "</methodResult>\n" +
              "</soap:Body>\n" +
            "</soap:Envelope>\n";
    }

    /**
     * Verify that two objects have the same value, handling arrays...
     */
    private static boolean equals(Object obj1, Object obj2) {
       if (obj1 == null) return (obj2 == null);
       if (obj1.equals(obj2)) return true;
       if (obj2.getClass().isArray() && obj1.getClass().isArray()) {
           if (Array.getLength(obj1) != Array.getLength(obj2)) return false;
           for (int i=0; i<Array.getLength(obj1); i++)
               if (!equals(Array.get(obj1,i),Array.get(obj2,i))) return false;
           return true;
       }
       if ((obj1 instanceof List) && (obj2 instanceof List)) {
           List list1 = (List)obj1;
           List list2 = (List)obj2;
           if (list1.size() != list2.size()) return false;
           for (int i=0; i < list1.size(); i++) {
               if (!equals(list1.get(i), list2.get(i))) return false;
           }
           return true;
       }
       if ((obj1 instanceof Map) && (obj2 instanceof Map)) {
           Map map1 = (Map)obj1;
           Map map2 = (Map)obj2;
           Set keys1 = map1.keySet();
           Set keys2 = map2.keySet();
           if (!(keys1.equals(keys2))) return false;
           Iterator i = keys1.iterator();
           while (i.hasNext()) {
               Object key = i.next();
               if (!map1.get(key).equals(map2.get(key)))
                   return false;
           }
           return true;
       }
       
       return false;
    }

    /**
     * Verify that a given XML deserialized produces the expected result
     */
    protected void deserialize(String data, Object expected)
       throws Exception
    {
       Message message = new Message(header + data + footer);
       message.setMessageContext(new MessageContext(server));

       SOAPEnvelope envelope = (SOAPEnvelope)message.getAsSOAPEnvelope();
       assertNotNull("SOAP envelope should not be null", envelope);

       RPCElement body = (RPCElement)envelope.getFirstBody();
       assertNotNull("SOAP body should not be null", body);

       Vector arglist = body.getParams();
       assertNotNull("arglist", arglist);
       assertTrue("param.size()<=0 {Should be > 0}", arglist.size()>0);

       RPCParam param = (RPCParam) arglist.get(0);
       assertNotNull("SOAP param should not be null", param);

       Object result = param.getValue();
       if (!equals(result, expected)) assertEquals("The result is not what is expected.", expected, result);
    }

    public void testString() throws Exception {
        deserialize("<result xsi:type=\"xsd:string\">abc</result>",
                    "abc");
    }

    public void testBoolean() throws Exception {
        deserialize("<result xsi:type=\"xsd:boolean\">true</result>",
                    new Boolean(true));
    }

    public void testDouble() throws Exception {
        deserialize("<result xsi:type=\"xsd:double\">3.14</result>",
                    new Double(3.14));
    }

    public void testFloat() throws Exception {
        deserialize("<result xsi:type=\"xsd:float\">3.14</result>",
                    new Float(3.14F));
    }

    public void testInt() throws Exception {
        deserialize("<result xsi:type=\"xsd:int\">10</result>",
                    new Integer(10));
    }

    public void testLong() throws Exception {
        deserialize("<result xsi:type=\"xsd:long\">17</result>",
                    new Long(17));
    }

    public void testShort() throws Exception {
        deserialize("<result xsi:type=\"xsd:short\">3</result>",
                    new Short((short)3));
    }

    public void testArray() throws Exception {
        Vector v = new Vector();
        v.addElement("abc");
        v.addElement("def");
        deserialize("<result xsi:type=\"soapenc:Array\" " +
                            "soapenc:arrayType=\"xsd:string[2]\"> " +
                       "<item xsi:type=\"xsd:string\">abc</item>" + 
                       "<item xsi:type=\"xsd:string\">def</item>" +
                    "</result>",
                    v);
    }
    
    public void testSparseArray1() throws Exception {
        ArrayList list = new ArrayList(4);
        list.add(null);
        list.add(null);
        list.add("abc");
        list.add("def");
        deserialize("<result xsi:type=\"soapenc:Array\" " +
                            "soapenc:arrayType=\"xsd:string[4]\" " +
                            "soapenc:offset=\"[2]\"> " +
                       "<item xsi:type=\"xsd:string\">abc</item>" + 
                       "<item xsi:type=\"xsd:string\">def</item>" +
                    "</result>",
                    list);
    }
    
    public void testSparseArray2() throws Exception {
        ArrayList list = new ArrayList(4);
        list.add("abc");
        list.add(null);
        list.add("def");
        list.add(null);
        deserialize("<result xsi:type=\"soapenc:Array\" " +
                            "soapenc:arrayType=\"xsd:string[4]\"> " +
      "<item soapenc:position=\"[0]\" xsi:type=\"xsd:string\">abc</item>" + 
      "<item soapenc:position=\"[2]\" xsi:type=\"xsd:string\">def</item>" + 
                    "</result>",
                    list);
    }
    
    public void testMap() throws Exception {
        HashMap m = new HashMap();
        m.put("abcKey", "abcVal");
        m.put("defKey", "defVal");
        deserialize("<result xsi:type=\"xmlsoap:Map\" " +
                    "xmlns:xmlsoap=\"http://xml.apache.org/xml-soap\"> " +
                      "<item>" +
                       "<key xsi:type=\"xsd:string\">abcKey</key>" + 
                       "<value xsi:type=\"xsd:string\">abcVal</value>" + 
                      "</item><item>" +
                       "<key xsi:type=\"xsd:string\">defKey</key>" +
                       "<value xsi:type=\"xsd:string\">defVal</value>" +
                      "</item>" +
                    "</result>",
                    m);
    }

    public void testUntyped() throws Exception {
         deserialize("<result>10</result>", "10");
    }
    
    public static void main(String [] args) throws Exception
    {
        TestDeser tester = new TestDeser("test");
        tester.testUntyped();
    }
}
