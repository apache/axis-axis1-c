/*
 * Created on Jul 8, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.geronimo.ews.ws4j2ee.wsutils.security;

import java.io.IOException;

import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.callback.UnsupportedCallbackException;

import org.apache.ws.security.WSPasswordCallback;

/**
 * @author srinath
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class SimpleClientPasswordCallbackHandler implements  CallbackHandler {
		
		public SimpleClientPasswordCallbackHandler(){
		}
		
		public void handle(Callback[] callbacks) throws IOException, UnsupportedCallbackException { 
			
			for (int i = 0; i < callbacks.length; i++) {
				if (callbacks[i] instanceof WSPasswordCallback) {
					WSPasswordCallback pc = (WSPasswordCallback) callbacks[i];

					///////////////////////////// Temp //////////////////////////////
					if(pc.getIdentifer().equals("jsr109-group"))					
						pc.setPassword("moratuwa");
					else if(pc.getIdentifer().equals("priyanga"))
						pc.setPassword("password");	
					else
						pc.setPassword(null);
					/////////////////////////////////////////////////////////////////	
					
				} else {
					throw new UnsupportedCallbackException(callbacks[i],
							"Unrecognized Callback");
				}
			}
		} 
		
	
}