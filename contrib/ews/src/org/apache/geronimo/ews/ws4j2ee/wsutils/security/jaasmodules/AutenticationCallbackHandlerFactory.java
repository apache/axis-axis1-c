package org.apache.geronimo.ews.ws4j2ee.wsutils.security.jaasmodules;

import javax.security.auth.callback.CallbackHandler;

import org.apache.axis.MessageContext;

/**
 * @author hemapani
 */
public class AutenticationCallbackHandlerFactory {
	public static CallbackHandler createCallbackHandler(MessageContext msgconxt){
//		char[] password = "password".toCharArray();
//		String name = "axis";
//		
//		CallbackHandler handler = new AppCallbackHandler(name, password);
//		return handler;
		return null;
	}
}
