/*
 * Created on Jun 20, 2004
 *
 *
 */
package org.apache.ws.axis.security;

import javax.security.auth.callback.CallbackHandler;
import javax.security.auth.callback.Callback;

import org.apache.axis.AxisFault;
import org.apache.axis.MessageContext;
import org.apache.axis.handlers.BasicHandler;

import org.apache.ws.axis.security.WSDoAllConstants;
import org.apache.ws.security.WSPasswordCallback;

/**
 * This class can be used as a client side Axis handler which can insert 
 * BasicHTTPAuthentication data to the request. This class uses the 
 * PasswordCallbackHandler specified by the client in the DD or Call object,
 * to obtain the credentials of the client to add to the HTTP header.    
 * (i.e. <code>passwordCallbackClass</code> property.)
 * 
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date Jun 20, 2004 
 * 
 */
public class BasicAuth4J2EESender extends BasicHandler {

	/**
	 * @see org.apache.axis.Handler#invoke(org.apache.axis.MessageContext)
	 */
	public void invoke(MessageContext cntxt) throws AxisFault {
		String username = cntxt.getUsername();		
		try{			
			cntxt.setPassword(fetchPWD(username, cntxt));
		}
		catch(Exception e){
			throw AxisFault.makeFault(e);
		}
	}


	/**
	 * Fetches the password to be sent, using the given Password Callback 
	 * class.
	 * @param username
	 * @param cntxt
	 * @return
	 * @throws Exception
	 */
	private String fetchPWD(String username, MessageContext cntxt) throws Exception{
		if(username==null){
			throw new Exception("No username provided!");	
		}
		
		WSPasswordCallback pwcb = new WSPasswordCallback(username, WSPasswordCallback.USERNAME_TOKEN);
		Callback[] cb = new Callback[1];
		cb[0] = pwcb;
		
		CallbackHandler cbh = (CallbackHandler)cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_REF);
		if(cbh == null){
			String cbhClass = (String)cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_CLASS);			
			cbh = (CallbackHandler)Class.forName(cbhClass).newInstance();			
		}
		if(cbh == null){
			throw new Exception("No PasswordCallbackHandler class found.");
		}
		else{
			cbh.handle(cb);
		}
		String pwd = ((WSPasswordCallback)(cb[0])).getPassword();		
		if(pwd==null)
			throw new Exception("No password provided!");
		return  pwd;
	} 
	
}
