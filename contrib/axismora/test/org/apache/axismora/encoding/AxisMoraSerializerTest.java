package org.apache.axismora.encoding;

import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import javax.xml.parsers.DocumentBuilderFactory;

import junit.framework.TestCase;

import org.apache.axismora.encoding.ser.EnhancedWriter;
import org.apache.axismora.encoding.ser.SerializationContext;
import org.w3c.dom.Document;

/**
 * @author hemapani
 */
public class AxisMoraSerializerTest extends TestCase{
	public void testSerializeDom() throws Exception{
		DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
		dbf.setNamespaceAware(true);
		Document commonDoc = dbf.newDocumentBuilder().parse("mora-server.wsdd");
		
		EnhancedWriter er = new EnhancedWriter(new BufferedOutputStream(new FileOutputStream("temp.txt")));
		
		SerializationContext sc = new SerializationContext(er);
		sc.writeDOMElement(commonDoc.getDocumentElement());
		er.flush();
		er.close();
		//try and parse the valied XML has written
		dbf.newDocumentBuilder().parse("temp.txt");
		System.out.println("SUCSESSFUL");
	}
	
	public void testWriteSafeString() throws Exception{
		EnhancedWriter er = new EnhancedWriter(new BufferedOutputStream(System.out));
		SerializationContext sc = new SerializationContext(er);
		String value = "Hello We are testing write safe String ";
		sc.writeSafeString(value);
		er.flush();
		System.out.println("DONE");
		for(int i = 0;i<256;i++){
			System.out.println(i + " = "+(char)i);
		}
	}
}
