/*
 * Created on May 29, 2004
 *
 *
 */
package org.apache.geronimo.ews.ws4j2ee.context.security;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Random;
import java.util.TimeZone;

import javax.security.auth.callback.Callback;
import javax.security.auth.callback.CallbackHandler;
import javax.xml.soap.Name;
import javax.xml.soap.SOAPElement;
import javax.xml.soap.SOAPFactory;
import javax.xml.soap.SOAPHeader;
import javax.xml.soap.SOAPHeaderElement;

import org.apache.axis.AxisFault;
import org.apache.axis.Message;
import org.apache.axis.MessageContext;
import org.apache.axis.handlers.BasicHandler;
import org.apache.ws.axis.security.WSDoAllConstants;
import org.apache.ws.security.WSConstants;
import org.apache.ws.security.WSPasswordCallback;
import org.apache.ws.security.message.token.UsernameToken;

/**
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date May 29, 2004 
 * 
 */
public class SimpleWSS4J2EESender extends BasicHandler {

	MessageContext cntxt = null;
		
	/**
	 * Adds the username-password information to the SOAP header
	 * within the UsernameToken, as requested by the user. 
	 * @see org.apache.axis.Handler#invoke(org.apache.axis.MessageContext)
	 */	
	public void invoke(MessageContext msgCntxt) throws AxisFault {
		this.cntxt = msgCntxt;
		String action = (String)cntxt.getProperty(WSDoAllConstants.ACTION);
		if(action==null)
			return;
			
		String[] actions = action.split(" ");
		
		boolean utAction = false;		
		//Check whether UsernameToken action is requested. Otherwise no more processing.
		for(int i=0; i<actions.length; i++){
			utAction = actions[i].equalsIgnoreCase(WSDoAllConstants.USERNAME_TOKEN);
			if(utAction)
				break;
		}
		if(!utAction)
			return;		
		//Get the username from the msg context. 
		String username = this.cntxt.getUsername();
		
		//If the username property is not in the message context,
		if(username==null)
			username = (String)cntxt.getProperty(WSDoAllConstants.USER);
		if(username==null)
			throw AxisFault.makeFault(new Exception("No username specified!"));
		
		//Get the password type. If it is not defined, the deault is PasswardText.
		String pwdType = (String)cntxt.getProperty(WSDoAllConstants.PASSWORD_TYPE);			
		if(pwdType==null)
			pwdType = WSConstants.PASSWORD_TEXT;		
		addUsernameToken(username, pwdType);
	}

	
	/**
	 * Creates and adds the Security-UsernameToken to the SOAP message.
	 * @param username
	 * @param passwordType
	 * @throws AxisFault
	 */
	private void addUsernameToken(String username, String passwordType) throws AxisFault{ 
		Message m = cntxt.getCurrentMessage();
		try{
			SOAPHeader h =  m.getSOAPPart().getEnvelope().getHeader();
			
			SOAPFactory sf = SOAPFactory.newInstance();		
							
			m.getSOAPEnvelope().addNamespaceDeclaration(WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS);	

			Name secN = sf.createName(WSConstants.WSSE_LN, WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS);			
			SOAPHeaderElement secElem = h.addHeaderElement(secN);								
			
			
			//Add the Username Token.			
			SOAPElement utElem = sf.createElement(WSConstants.WSSE_PREFIX+ ":" + WSConstants.USERNAME_TOKEN_LN);						
			secElem.addChildElement(utElem);		
					
			//Add the Username element.			
			SOAPElement unElem = sf.createElement(WSConstants.WSSE_PREFIX+ ":" + WSConstants.USERNAME_LN);			
			unElem.addTextNode(username);
			utElem.addChildElement(unElem);
						
			//Create the Password element.						
			SOAPElement pwdElem = sf.createElement(WSConstants.WSSE_PREFIX+ ":" + WSConstants.PASSWORD_LN);
																		
			Name pwdType = sf.createName(WSConstants.PASSWORD_TYPE_ATTR, WSConstants.WSSE_PREFIX, WSConstants.WSSE_NS);
			//Add password element.		
			if(passwordType.equalsIgnoreCase(WSConstants.PASSWORD_TEXT)){
				pwdElem.addAttribute(pwdType,WSConstants.PASSWORD_TEXT);
				pwdElem.addTextNode(fetchPWD(username));				
				utElem.addChildElement(pwdElem);	
			}
			else if(passwordType.equalsIgnoreCase(WSConstants.PASSWORD_DIGEST)){				
				m.getSOAPEnvelope().addNamespaceDeclaration(WSConstants.WSU_PREFIX, WSConstants.WSU_NS);	
				pwdElem.addAttribute(pwdType,WSConstants.PASSWORD_DIGEST);

				String nonce = getNonce();
				String created = getCreated();
				String digest = UsernameToken.doPasswordDigest(nonce, created, fetchPWD(username));
				
				SOAPElement nonceElem = sf.createElement(WSConstants.WSSE_PREFIX+":"+WSConstants.NONCE_LN);
				SOAPElement createdElem = sf.createElement(WSConstants.WSU_PREFIX+":"+WSConstants.CREATED_LN);
				
				nonceElem.addTextNode(nonce);
				createdElem.addTextNode(created);
				pwdElem.addTextNode(digest);
								
				utElem.addChildElement(pwdElem);								
				utElem.addChildElement(nonceElem);
				utElem.addChildElement(createdElem);
			}
			else{
				throw AxisFault.makeFault(new Exception("Unsupported PasswordType"));
			}						 						
		}
		catch(Exception ex){
			throw AxisFault.makeFault(ex);
		}	
	}
	
	/*
	 * Generates nonce.
	 */
	private String getNonce(){
		Random rand = new Random();
		byte[] nonce = new byte[16];
		rand.nextBytes(nonce);
		String nonceStr = org.apache.xml.security.utils.Base64.encode(nonce);		
		return nonceStr;
	}
	
	
	/**
	 * Generates created as per specification.
	 * @return
	 */
	private String getCreated(){
		SimpleDateFormat sd = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss'Z'");
		sd.setTimeZone(TimeZone.getTimeZone("GMT"));
		Calendar now = Calendar.getInstance();		
		return sd.format(now.getTime());		
	}


	/**
	 * Fetch the password of the user from the specified PasswordCallbak class. 
	 * @param username
	 * @return
	 * @throws Exception
	 */
	private String fetchPWD(String username) throws Exception{
		WSPasswordCallback pwcb = new WSPasswordCallback(username, WSPasswordCallback.USERNAME_TOKEN);
		Callback[] cb = new Callback[1];
		cb[0] = pwcb;
		
		CallbackHandler cbh = (CallbackHandler)this.cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_REF);
		if(cbh == null){
			String cbhClass = (String)this.cntxt.getProperty(WSDoAllConstants.PW_CALLBACK_CLASS);			
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
			throw new Exception("Password is not provided! Can't create UsernameToken.");
		return  pwd;
	}
	

}

