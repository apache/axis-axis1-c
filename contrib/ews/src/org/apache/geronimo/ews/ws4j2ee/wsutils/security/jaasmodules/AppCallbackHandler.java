/*
 * Created on Mar 12, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.apache.geronimo.ews.ws4j2ee.wsutils.security.jaasmodules;


import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.callback.NameCallback;
import javax.security.auth.callback.PasswordCallback;
import javax.security.auth.callback.UnsupportedCallbackException;

/**
 * @author Chathura Herath
 *
 */
public class AppCallbackHandler implements CallbackHandler
{
   private String username;
   private char[] password;

   public AppCallbackHandler(String username, char[] password)
   {
	  this.username = username;
	  this.password = password;
   }

   public void handle(Callback[] callbacks) throws
	  java.io.IOException, UnsupportedCallbackException
   {
	  for (int i = 0; i < callbacks.length; i++)
	  {
		 if (callbacks[i] instanceof NameCallback)
		 {
			NameCallback nc = (NameCallback) callbacks[i];
			nc.setName(username);
		 }
		 else if (callbacks[i] instanceof PasswordCallback)
		 {
			PasswordCallback pc = (PasswordCallback) callbacks[i];
			pc.setPassword(password);
		 }
		 else
		 {
			throw new UnsupportedCallbackException(callbacks[i], "Unrecognized Callback");
		 }
	  }
   }
}