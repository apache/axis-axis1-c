/*
 * Created on Jun 27, 2004
 *
 *
 */
package org.apache.ws.axis.security;

import java.io.IOException;

import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.callback.NameCallback;
import javax.security.auth.callback.PasswordCallback;
import javax.security.auth.callback.UnsupportedCallbackException;
/**
 * This is a simple PasswordCallback Handler that can be used by 
 * Wrapper web service, before invoking the EJB, to authenticate
 * the client using JAAS. 
 * 
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date Jun 27, 2004 
 * 
 */
public class PWDCallbackHandler4J2EE implements CallbackHandler{

	String username = null;
	char[] password = null;

	/**
	 * @see javax.security.auth.callback.CallbackHandler#handle(javax.security.auth.callback.Callback[])
	 */	
	public PWDCallbackHandler4J2EE(String username, char[] password){
		this.username = username;
		this.password = password;
	}

	
	public void handle(Callback[] callbacks) throws IOException, UnsupportedCallbackException {
		boolean recognized = false;
		//Callback handler which implements both the following interfaces 
		//can also be handled.		
		for (int i = 0; i < callbacks.length; i++){
			if (callbacks[i] instanceof NameCallback){
				NameCallback ncb = (NameCallback) callbacks[i];
				ncb.setName(username);
				recognized = true;
			}
			if (callbacks[i] instanceof PasswordCallback){
				PasswordCallback pcb = (PasswordCallback) callbacks[i];				
				pcb.setPassword(password);
				recognized = true;
			}
			if(!recognized){
				throw new UnsupportedCallbackException(callbacks[i], "Callback Type is not supported.");
			}
		}
	}

 

}
