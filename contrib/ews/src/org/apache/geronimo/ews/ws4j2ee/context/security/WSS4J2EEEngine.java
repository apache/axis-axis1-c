/*
 * Created on May 28, 2004
 *
 *
 */
package org.apache.geronimo.ews.ws4j2ee.context.security;

import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;

import org.apache.axis.MessageContext;
import org.apache.geronimo.ews.ws4j2ee.context.security.impl.SecurityContext4J2EEImpl;
import org.apache.ws.security.WSPasswordCallback;
import org.apache.ws.security.WSSecurityEngine;
import org.apache.ws.security.WSSecurityException;
import org.apache.ws.security.WSUsernameTokenPrincipal;
import org.apache.ws.security.message.token.UsernameToken;
import org.w3c.dom.Element;
/**
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
	
	
	public WSUsernameTokenPrincipal handleUsernameToken(Element token, CallbackHandler cb) throws Exception {
			UsernameToken ut = new UsernameToken(token);
			String user = ut.getName();
			/*if (doDebug) {
				log.debug("UsernameToken user " + user);
			}*/
			WSPasswordCallback pwCb = new WSPasswordCallback(user, WSPasswordCallback.USERNAME_TOKEN);
			Callback[] callbacks = new Callback[1];
			callbacks[0] = pwCb;
			cb.handle(callbacks);
			String origPassword = pwCb.getPassword();
			/*if (doDebug) {
				log.debug("UsernameToken password " + origPassword);
			}*/
			if (origPassword == null) {
				throw new WSSecurityException(WSSecurityException.FAILURE,
						"noPassword", new Object[]{user});
			}
			String password = ut.getPassword();
			boolean result = false;
			WSUsernameTokenPrincipal principal = new WSUsernameTokenPrincipal(user, ut.isHashed());
			String nonce = ut.getNonce();
			String createdTime = ut.getCreated();
			principal.setNonce(nonce);
			principal.setCreatedTime(createdTime);
			if (ut.isHashed()) {
				if (nonce != null && createdTime != null) {
					String passDigest = UsernameToken.doPasswordDigest(nonce, createdTime, origPassword);
					if (passDigest.equals(password)) {
						result = true;
					}
				}
			} else {
				if (origPassword.equals(password)) {
					result = true;
				}
			}
			if (!result) {
				throw new WSSecurityException(WSSecurityException.FAILED_AUTHENTICATION);
			}
			populateSecurityContext4J2EE(ut);			
			return principal;
		}

	
	
		/**
		 * Register a SecurityContext4J2EE object with the MessageContext as
		 * WSS4J2EEConstants.SEC_CONTEXT_4J2EE property.
		 * Populates the SEC_CONTEXT_4J2EE property with the security information
		 * avatilable in the UsernameToken. 
		 * @param ut
		 */
		private void populateSecurityContext4J2EE(UsernameToken ut){
			SecurityContext4J2EEImpl sc4j2ee = 
				(SecurityContext4J2EEImpl)this.msgCntxt.getProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE);
			
			if(this.msgCntxt==null){
				sc4j2ee = new SecurityContext4J2EEImpl();
				this.msgCntxt.setProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE, sc4j2ee);
			}
			
			//Populate the SecurityContext4J2EE with the user name token data.
			sc4j2ee.setUsername(ut.getName());
			if(ut.isHashed()){
				sc4j2ee.setPasswordDigested(true);
				sc4j2ee.setNonce(ut.getNonce());
				sc4j2ee.setCreated(ut.getCreated());
			}							
			else
				sc4j2ee.setPasswordDigested(false);
				
			sc4j2ee.setPassword(ut.getPassword().toCharArray());

		}
		

}
