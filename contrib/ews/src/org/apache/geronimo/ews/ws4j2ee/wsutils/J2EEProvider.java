package org.apache.geronimo.ews.ws4j2ee.wsutils;

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
		JaxRpcRuntime.setMessageContext(msgContext);
		return super.makeNewServiceObject(msgContext, clsName);
	}

}
