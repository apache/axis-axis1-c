/*
 * Created on May 28, 2004
 *
 *
 */
package org.apache.ws.security;

import javax.security.auth.callback.CallbackHandler;

import org.apache.axis.MessageContext;

import org.apache.geronimo.ews.ws4j2ee.context.security.impl.SecurityContext4J2EEImpl;
import org.apache.ws.axis.security.PWDCallbackHandler4J2EE;
import org.apache.ws.axis.security.WSS4J2EEConstants;
import org.apache.ws.security.message.token.UsernameToken;
import org.w3c.dom.Element;
/**
 * This class is used in <code>AllSecurityReceiver</code<> to process the secuirty
 * headers in the SOAP message. This works slightly different from the
 * WSSecurityEngine of wss4j project. 
 * i.e 
 * This processes the UsernameToken element in a different way.
 * The credentials available in the token are retrieved and the
 * SecurityContext4J2EE is populated using them.
 * No authentication is done at Axis. Therefore no principal 
 * is created, instead this replace it with null.
 * 
 * Before using the above service, the MessageContext should be set.
 *   
 * @author Davanum Srinivas (dims@yahoo.com).
 * @author Werner Dittmann (Werner.Dittmann@siemens.com).
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date May 28, 2004 
 * 
 */
public class WSS4J2EEEngine extends WSSecurityEngine{
	
	private MessageContext msgCntxt = null;
	
		
	public void setMessageContext(MessageContext msgContext) throws Exception{
		if(msgContext==null){
			throw new Exception("Mssage Context is null!");
		}
		else{
			this.msgCntxt = msgContext;
		}	
	}	
 

	/**
	 * Processes the UsernameToken element and populate the SecurityContext4J2EE prperty
	 * with the credentials available in it.
	 * No authentication is done here.
	 * Always returns null
	 */
	public WSUsernameTokenPrincipal handleUsernameToken(Element token, CallbackHandler cb) throws WSSecurityException {
	
			UsernameToken ut = new UsernameToken(token);
			try{				
				this.populateSecurityContext4J2EE(ut.getName(), 
												  ut.getPassword().toCharArray(), 
												  ut.isHashed(), 
												  ut.getNonce(), 
												  ut.getCreated());				  
			}
			catch(Exception e){
				throw new WSSecurityException(WSSecurityException.FAILURE, "Invalid Username Token found!"); 		
			}
		
		return null;
	}


		
	/**
	 * Register a SecurityContext4J2EE object with the MessageContext as
	 * WSS4J2EEConstants.SEC_CONTEXT_4J2EE property.
	 * Populates the SEC_CONTEXT_4J2EE property with the security information
	 * avatilable in the UsernameToken. 
	 * @param ut
	 */
	private void populateSecurityContext4J2EE(String user, char[] pwd, boolean isDigested, String nonce, String created){
		SecurityContext4J2EEImpl sc4j2ee = 
			(SecurityContext4J2EEImpl)this.msgCntxt.getProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE);
		
		if(sc4j2ee==null){
			sc4j2ee = new SecurityContext4J2EEImpl();
			this.msgCntxt.setProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE, sc4j2ee);
		}
		
		//Populate the SecurityContext4J2EE with the user name token data.
		sc4j2ee.setUsername(user);
		if(isDigested){
			sc4j2ee.setPasswordDigested(true);
			sc4j2ee.setNonce(nonce);
			sc4j2ee.setCreated(created);
		}							
		else
			sc4j2ee.setPasswordDigested(false);
			
		sc4j2ee.setPassword(pwd);
		PWDCallbackHandler4J2EE cbh = new PWDCallbackHandler4J2EE(user, pwd);
		sc4j2ee.setPWDCallbackHandler4J2EE(cbh);
	}
		

}
