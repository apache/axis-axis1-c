package org.apache.axismora.provider.result;

import java.io.IOException;

import javax.xml.namespace.QName;

import org.apache.axismora.encoding.OutParameter;
import org.apache.axismora.encoding.Serializable;

/**
 * Manages serialization of the body.
 * Serialization at both client and server side should be taken care of by this.
 * @author Dimuthu Leelarathne.
 *
 */
public class DocLiteralSerializer implements Serializable {
	private OutParameter parm;
	private boolean clientSide=false;
	private QName eleQName;   

	   public DocLiteralSerializer(OutParameter param,QName qName) {
		   this.parm = param;
		   this.eleQName=qName;
	   }
	
	  /**
		* this method is called by the SOAPHeaderElement when serializing
		*/
	   public void serialize(org.apache.axis.encoding.SerializationContext sc) throws IOException {
           
			if(parm != null){ 		 
			   //writing start tag
				StringBuffer buf = new StringBuffer();
				String uri = eleQName.getNamespaceURI();
				if (uri != null && !("".equals(uri))) {
					buf.append("<pre:").append(this.eleQName.getLocalPart());
					buf.append(" xmlns:pre=\"").append(uri);
					buf.append("\">\n");
				} else {
					buf.append("<").append(this.eleQName.getLocalPart());
					buf.append(">\n");
				}
				sc.writeString(buf.toString());
				parm.serialize(sc);
               	
				//writing end tag
				buf = new StringBuffer();
				if (uri != null && !("".equals(uri))) {
					buf.append("\n</pre:").append(this.eleQName.getLocalPart());
					buf.append(">\n");
				} else {
					buf.append("\n</").append(this.eleQName.getLocalPart());
					buf.append(">\n");
				}
				sc.writeString(buf.toString());
			} else System.out.println("DEBUG - The param is null");
	   }

          
}
