
package org.apache.axismora.provider.result;

import java.io.IOException;

import org.apache.axismora.encoding.OutParameter;
import org.apache.axismora.encoding.Serializable;

import org.apache.axis.encoding.SerializationContext;

/**
 * @author Dimuthu Leelarathne.
 *
 */
public class DocLiteralResult implements Serializable {
	private OutParameter parm;
	   

	   public DocLiteralResult(OutParameter param) {
		   this.parm = param;
		 
	   }
	
	  /**
		* this method is called by the SOAPHeaderElement when serializing
		*/
	   public void serialize(SerializationContext sc) throws IOException {
            if(parm != null){ 		 
               	   parm.serialize(sc);
			} else System.out.println("DEBUG - The param is null");
	   }

}
