/*
 * Created on Jun 20, 2004
 *
 *
 */
package org.apache.ws.axis.security;

import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;

import org.apache.axis.AxisFault;
import org.apache.axis.MessageContext;
import org.apache.axis.handlers.BasicHandler;
import org.apache.geronimo.ews.ws4j2ee.context.security.impl.SecurityContext4J2EEImpl;
import org.apache.ws.axis.security.WSDoAllConstants;
import org.apache.ws.security.WSPasswordCallback;

/** 
 * If the client is using BasicHTTP Authentication, this class can be used
 * as a server side Axis handler, which retreives the credentials available in
 * the HTTP header and populate the SecurityContext4J2EE property.
 * 
 * Only if the <code>WSS4J2EEConstants.AUTH_AT_AXIS</code> property is set to true,
 * this does the authentication at the Axis. For that at the DD the <code>passwordCallbackClass</code>
 * should be available. 
 * 
 * @author Rajith Priyanga
 * @date Jun 20, 2004 
 * 
 */
public class BasicAuth4J2EEReceiver extends BasicHandler {

	private boolean doAuthentication = false;
	/**
	 * @see org.apache.axis.Handler#invoke(org.apache.axis.MessageContext)
	 */
	public void invoke(MessageContext cntxt) throws AxisFault {
		doAuthentication = false;
		String username = cntxt.getUsername();
		String password = cntxt.getPassword();
		if(username==null|| password==null){
			throw AxisFault.makeFault(new Exception("null values for username or/and password."));	
		}

		//Decides whether to do authentication at Axis or not.
		if(cntxt.containsProperty(WSS4J2EEConstants.AUTH_AT_AXIS)){
			String check = (String)cntxt.getProperty(WSS4J2EEConstants.AUTH_AT_AXIS);
			if(check!=null && check.equalsIgnoreCase("true"))
				this.doAuthentication = true;
		}
		
		if(this.doAuthentication){
			try{			
				this.veryfyPWD(username, password, cntxt);			
			}
			catch(Exception e){
				throw AxisFault.makeFault(e);
			}
		}
		
		populateSecurityContext4J2EE(username, password, cntxt);
	}
	
	
	/**
	 * Populates the SecurityContext4J2EE property with the given credentials.
	 * Also this adds a PWDCallbackHandler4J2EE to the SecurityContext4J2EE. 
	 * @param username
	 * @param password
	 * @param cntxt
	 */
	private void populateSecurityContext4J2EE(String username, String password, MessageContext cntxt){
		SecurityContext4J2EEImpl sc4j2ee = 
			(SecurityContext4J2EEImpl)cntxt.getProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE);
				
		if(sc4j2ee==null){
			sc4j2ee = new SecurityContext4J2EEImpl();
			cntxt.setProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE, sc4j2ee);
		}
							
		//Populate the SecurityContext4J2EE with the auth data.
		sc4j2ee.setUsername(username);
		sc4j2ee.setPassword(password.toCharArray());		
		sc4j2ee.setPasswordDigested(false);
		
		PWDCallbackHandler4J2EE pwdcbh = new PWDCallbackHandler4J2EE(username, password.toCharArray());
		sc4j2ee.setPWDCallbackHandler4J2EE(pwdcbh);		
	}


	private boolean veryfyPWD(String username, String password, MessageContext cntxt) throws Exception{		
		if(password.equals(this.fetchActualPWD(username, cntxt))){			
			return true;
		}
		else{			
			return false;
		}		
	}


	private String fetchActualPWD(String username, MessageContext cntxt) throws Exception{
		WSPasswordCallback pwcb = new WSPasswordCallback(username, WSPasswordCallback.USERNAME_TOKEN);
		Callback[] cb = new Callback[1];

		cb[0] = pwcb;
				
		CallbackHandler cbh = (CallbackHandler)cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_REF);
		
		if(cbh == null){
			String cbhClass = (String)cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_CLASS);
			cbh = (CallbackHandler)Class.forName(cbhClass).newInstance();
		}
								
		if(cbh==null){
			throw new Exception("PasswordCallbackHandler not found!");
		} 

		cbh.handle(cb);		 
		String pwd = ((WSPasswordCallback)(cb[0])).getPassword();

		if(pwd==null)
			throw new Exception("Password is not provided.");

		return  pwd;
				
	}

}
