/*
 * Created on May 29, 2004
 *
 *
 */
package org.apache.geronimo.ews.ws4j2ee.context.security;

import java.util.Iterator;
import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;

import org.apache.axis.AxisFault;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.handlers.BasicHandler;
import org.apache.geronimo.ews.ws4j2ee.context.security.impl.SecurityContext4J2EEImpl;
import org.apache.ws.axis.security.WSDoAllConstants;
import org.apache.ws.security.WSConstants;
import org.apache.ws.security.WSPasswordCallback;
import org.apache.ws.security.message.token.UsernameToken;

import javax.xml.soap.SOAPHeader;
import javax.xml.soap.SOAPHeaderElement;
import javax.xml.soap.Name;
import javax.xml.soap.SOAPElement;
import javax.xml.soap.SOAPFactory;

/**
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date May 29, 2004 
 * 
 */
public class SimpleWSS4J2EEReceiver extends BasicHandler {

	MessageContext cntxt = null;	

	/**
	 * Retrieve the username-password information and perform a verification. 
	 * @see org.apache.axis.Handler#invoke(org.apache.axis.MessageContext)
	 */
	public void invoke(MessageContext msgCntxt) throws AxisFault {
		this.cntxt = msgCntxt;			
		try{
			//Get the SOAP header.
			Message m = msgCntxt.getCurrentMessage();
			SOAPHeader sh = m.getSOAPPart().getEnvelope().getHeader();
			
			//Retrieve the action property.
			String action = null;
			if((action = (String) getOption(WSDoAllConstants.ACTION))==null)
				action = (String)cntxt.getProperty(WSDoAllConstants.ACTION);
				
			if(action==null){				
				return;		
			}	
			
			String[] actions = action.split(" ");
			if(actions==null)
				return;
				
			boolean utAction = false;		
			
			//Check whether UsernameToken action property is available. Otherwise no more processing.
			for(int i=0; i<actions.length; i++){
				utAction = actions[i].equalsIgnoreCase(WSDoAllConstants.USERNAME_TOKEN);
				if(utAction)
					break;
			}
			if(!utAction)
				return;		
			
			//Get all the headers.
			Iterator headers = sh.getChildElements();
			SOAPHeaderElement headerElem = null;
						
			if(headers==null){			
				throw AxisFault.makeFault(new Exception("No Security Headers found"));				
			}
			//Find the security header.			
			while (headers.hasNext()) {
				headerElem = (SOAPHeaderElement) headers.next();
				if (headerElem.getLocalName().equals(WSConstants.WSSE_LN)
					&& headerElem.getNamespaceURI().equals(WSConstants.WSSE_NS)) {
					break;
				}				
			}
			//Hand over the security header to process it's UsernameToken.			
			processUsernameToken(headerElem);						
		}
		catch(Exception ex){			
			throw AxisFault.makeFault(ex);
		}		
				 
	}
	
	/**
	 * Processes the UsernameToken element of the security header.
	 * It populates the SecurityContext4J2EE property of the MessageContext too.	 
	 * @param secHeader SOAP Security Header. 
	 * @throws Exception
	 */
	private void processUsernameToken(SOAPHeaderElement secHeader) throws Exception{		
		SOAPFactory sf = SOAPFactory.newInstance(); 
		Name utName = sf.createName(WSConstants.USERNAME_TOKEN_LN, WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS);
		 
		Iterator toks = secHeader.getChildElements(utName);
		if(toks==null){
			throw new Exception("No Security tokens found!");
		}
		//Get the UsernameToken element
		SOAPElement utElem = null;
		if(toks.hasNext()){
			utElem = (SOAPElement)toks.next();
		}
		else{
			throw new Exception("No UsernameToken found!");
		}
		
		Name unName = sf.createName(WSConstants.USERNAME_LN, WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS);
		Name pwdName = sf.createName(WSConstants.PASSWORD_LN, WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS);
		
		//Get the user name
		String username = ((SOAPElement)(utElem.getChildElements(unName).next())).getValue();
		
		//Get the password element
		SOAPElement pwdElem = (SOAPElement)utElem.getChildElements(pwdName).next();
		
		//Get the password type
		String pwdType = pwdElem.getAttributeValue(sf.createName(WSConstants.PASSWORD_TYPE_ATTR,  WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS));
		//Get the password
		String pwd = pwdElem.getValue();
		
		//If the password type is not speciied take it as PASSWORD_TEXT type.
		if(pwdType==null)			
			pwdType = WSConstants.PASSWORD_TEXT;			
		
		if(pwdType.equalsIgnoreCase(WSConstants.PASSWORD_TEXT)){
			if(!veryfyPWD(username, pwd)){
				throw new Exception("Password Verification failed!");
			}
			this.populateSecurityContext4J2EE(username, pwd, pwdType, null, null);
		}	
		else if(pwdType.equalsIgnoreCase(WSConstants.PASSWORD_DIGEST)){
			Name nonceName = sf.createName(WSConstants.NONCE_LN, WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS);
			Name createdName = sf.createName(WSConstants.CREATED_LN, WSConstants.WSU_PREFIX, WSConstants.WSU_NS);
			
			Iterator elems = utElem.getChildElements(nonceName);			
			String nonce = this.extractNonce(elems);
			 
			elems = utElem.getChildElements(createdName);			
			String created = this.extractCreated(elems);  
			
			if(!veryfyPWD(username, pwd, nonce, created)){
				throw new Exception("Password Verification failed!");
			}
			
			this.populateSecurityContext4J2EE(username, pwd, pwdType, nonce, created);
		}
		else{
			throw new Exception("Unsupported Password Type!");
		}		 
	}


	/**
	 * Extracts the nonce value from the given set of elements.
	 * (It is given as a iteratorf o elements)
	 * @param elements
	 * @return
	 * @throws Exception
	 */
	private String extractNonce(Iterator elements) throws Exception{
		boolean noNonce = false;
		String nonce = null;
			
		if(elements==null){		
			noNonce = true;
		}										
		if(!noNonce && elements.hasNext()){			
			nonce = ((SOAPElement)(elements.next())).getValue();
		}			
		else{			
			noNonce = true;	
		}						
		if(nonce == null){
			noNonce = true;		
		}						
		if(noNonce)
			throw new Exception("Nonce is not specified!");
						
		return nonce;
	}

	/**
	 * Extracts the created value from the given set of elements.
	 * (It is given as a iteratorf o elements)
	 * @param elements
	 * @return
	 * @throws Exception
	 */
	private String extractCreated(Iterator elements) throws Exception{
		boolean noCreated = false;
		String created = null;
			
		if(elements==null)
		noCreated = true;
							
		if(!noCreated && elements.hasNext())	
			created = ((SOAPElement)(elements.next())).getValue();
		else	
			noCreated = true;
			
		if(created == null)
			noCreated = true;
			
		if(noCreated)
			throw new Exception("Created is not specified!");
			
		return created;
	}


	/**
	 * Verifies the PASSWORD_TEXT type passwords.
	 */
	private boolean veryfyPWD(String username, String password) throws Exception{		
		if(password.equals(this.fetchActualPWD(username))){			
			return true;
		}
		else{			
			return false;
		}		
	}
	
	/**
	 * Verifies the PASSWORD_DIGEST type passwords.
	 */
	private boolean veryfyPWD(String username, 
							  String password, 
							  String nonce, 
							  String created) throws Exception{		
		
		//TODO
		//Check whether (created > currentTime - 5 minutes).
		//Cache the nonce for the user and check it before verification.
		
		String digest = UsernameToken.doPasswordDigest(nonce, created, this.fetchActualPWD(username));	
		
		if(password.equals(digest)){				
			return true;
		}
		else{			
			return false;
		}			
	}
	
	/**}
	 * Detches the actual password using the CallbackHandler specified 
	 * in the deployment descripter. 
	 * @param username username
	 * @return the actual password of the user.
	 * @throws Exception
	 */
	 
	private String fetchActualPWD(String username) throws Exception{
		WSPasswordCallback pwcb = new WSPasswordCallback(username, WSPasswordCallback.USERNAME_TOKEN);
		Callback[] cb = new Callback[1];
		
		cb[0] = pwcb;
		
		CallbackHandler cbh = (CallbackHandler)this.cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_REF);
		if(cbh == null){
			String cbhClass = (String)this.cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_CLASS);			
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
	
	
	/**
	 * Populates the SecurityContext4J2EE property with the given 
	 * security information.
	 * @param username
	 * @param password
	 * @param passwordType
	 * @param nonce
	 * @param created
	 */
	private void populateSecurityContext4J2EE(String username, String password, String passwordType, String nonce, String created){
		SecurityContext4J2EEImpl sc4j2ee = 
			(SecurityContext4J2EEImpl)this.cntxt.getProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE);
				
		if(sc4j2ee==null){
			sc4j2ee = new SecurityContext4J2EEImpl();
			this.cntxt.setProperty(WSS4J2EEConstants.SEC_CONTEXT_4J2EE, sc4j2ee);
		}
							
		//Populate the SecurityContext4J2EE with the user name token data.
		sc4j2ee.setUsername(username);
		sc4j2ee.setPassword(password.toCharArray());
		
		if(passwordType.equalsIgnoreCase(WSConstants.PASSWORD_DIGEST)){
			sc4j2ee.setPasswordDigested(true);
			sc4j2ee.setNonce(nonce);
			sc4j2ee.setCreated(created);			
		}			
		else
			sc4j2ee.setPasswordDigested(false);	

	}
	
}
