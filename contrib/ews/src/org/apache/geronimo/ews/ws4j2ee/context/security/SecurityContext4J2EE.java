/*
 * Created on Apr 5, 2004
 *
 *
 */
package org.apache.geronimo.ews.ws4j2ee.context.security;

import javax.security.cert.X509Certificate;

/**
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date Apr 5, 2004 
 * 
 * Note: When implementing this should have a reference to the MessageContext
 * 
 */
public interface SecurityContext4J2EE {
	/**
	 * If the integrity of the important elements in the SOAP message is 
	 * verified, this will return true. Otherwise false. This is a deployer 
	 * dependent test. 
	 * If the SOAP request pass this test at the check point this will return true. 
	 */
	public boolean sufficientIntegrity();

	/**
	 * If the privacy of the important elements in the SOAP message is
	 * kept, this will return true. Otherwise false. This is a deployer 
	 * dependent test.  
	 * If the SOAP request pass this test at the check point this will return true. 
	 */	 	
	public boolean sufficientPrivacy();
	
	/**
	 * Returns the nonce if speciied at the username token.
	 * @return nonce. null if it is not mentioned.
	 */
	public String getNonce();
	
	/**
	 * Returns the created time if speciied in the username token.
	 * @return created time. null if it is not mentioned.
	 */
	public String getCreated();
	
	/**
	 * Returns true if the password is hashed. 
	 * @return is Password Digested?
	 */
	public boolean isPasswordDigested();
	
	/**
	 * Returns the digest value of the password as it appears in the 
	 * SOAP message's username token.
	 * @return password digest.
	 */
	public char[] getPasswordDigest();
	
	/**
	 * Returns the password. This is retrieved from the password store
	 * by comparing the username.
	 *   
	 * @return actual password of the user.
	 */
	public char[] getPasswordText();
	
	/**
	 * Returns the username as appears in the SOAP header.
	 * @return username.
	 */
	public String getUsername();
	
	/**
	 * Returns the X509 certificate. If it is not available in the 
	 * SOAP message	returns null. 
	 * @return the X509 Certificate.
	 */
	public X509Certificate getX509Certificate();
	
	/**
	 * Returns the Kerberose ticket. If it is not available in the 
	 * SOAP message	returns null. 
	 * @return the X509 Certificate.
	 */
	public byte[] getKerberoseTicket(); 
}
