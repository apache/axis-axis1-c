package org.apache.axismora.client;

import org.apache.axis.AxisFault;
import org.apache.axis.enum.Style;
import org.apache.axismora.provider.result.DocLiteralSerializer;

/**
 * 
 * @author Dimuthu
 * @author Srinath
 *
 * To change the template for this generated type comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
public class SOAPBodyContentFactory {
	public static Object getSOAPBodyContent(ClientRequestContext requestContext)throws AxisFault{
		if(Style.DOCUMENT.equals(requestContext.getStyle())){
			System.out.println("I am in document");
			InputParameterInfo[] info = requestContext.getInparams();
			InputParameterInfo param = info[0];
			return new DocLiteralSerializer(param.getOutParamter(),param.getQname());
		}else{
			return new RequestBodyContent(requestContext.getInparams(),requestContext.getMethodName());
		}		
	}
}
