package org.apache.geronimo.ews.ws4j2ee.wsutils;

import org.apache.axis.AxisFault;
import org.apache.axis.MessageContext;
import org.apache.axis.providers.java.RPCProvider;

/**
 * register the MessageContext in the jax-rpc runtime of the JSR109 
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public class J2EEProvider extends RPCProvider{
	protected Object makeNewServiceObject(
		MessageContext msgContext,
		String clsName)
		throws Exception {
			ContextAccssible webservice =  
				(ContextAccssible)super.makeNewServiceObject(msgContext, clsName);
			webservice.setMessageContext(msgContext);
			System.out.println("message Context set");
			return webservice;
	}

	/* (non-Javadoc)
	 * @see org.apache.axis.Handler#invoke(org.apache.axis.MessageContext)
	 */
	public void invoke(MessageContext msgContext) throws AxisFault {
		super.invoke(msgContext);
	}

}
