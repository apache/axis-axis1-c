package org.apache.axismora.provider.serializer;

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
	   

	   public DocLiteralSerializer(OutParameter param,QName qName) {
		   this.parm = param;
		 
	   }
	
	  /**
		* this method is called by the SOAPHeaderElement when serializing
		*/
	   public void serialize(org.apache.axis.encoding.SerializationContext sc) throws IOException {
			if(parm != null){ 		 
				   parm.serialize(sc);
			} else System.out.println("DEBUG - The param is null");
	   }

}
