/*
 * Created on May 28, 2004
 *
 *
 */
package org.apache.ws.axis.security;

import org.apache.ws.axis.security.WSDoAllConstants;


/**
 * Defines the Constants used or WS-J2EE security Mapping implementation.
 * 
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date May 28, 2004 
 * 
 */
public class WSS4J2EEConstants extends WSDoAllConstants {
	
	/**
	 * This property contains the security information required to authenticate 
	 * the user to the J2EE server, plus some more information. Represents 
	 * a SecurityContext4J2EE object.
	 *
	 */
	public static final String SEC_CONTEXT_4J2EE = "SEC_CONTEXT_4J2EE";
	
	
	public static final String AUTH_AT_AXIS = "AuthenticationAtAxis";
}
