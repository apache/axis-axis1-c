/*
 * Created on Apr 6, 2004
 *
 *
 */
package org.apache.geronimo.ews.ws4j2ee.context.security;

import org.apache.axis.AxisFault;
import org.apache.axis.MessageContext;
import org.apache.axis.handlers.BasicHandler;
/**
 * @author Rajith Priyanga (rpriyanga@yahoo.com)
 * @date Apr 6, 2004 
 * 
 */
public abstract class CheckPoint4J2EEHandler extends BasicHandler {
	
	/**
	 * @see org.apache.axis.Handler#invoke(org.apache.axis.MessageContext)
	 */
	public void invoke(MessageContext cntxt) throws AxisFault{
		SecurityContext4J2EE sc4j2ee;
		//TODO
		//Populate the SecurityContext4J2EE object with available info.
		//Other info will be dynamically calculated rom MessageCOntext.		 
	}
	
	/**
	 * Decides whether the message integrity is sufficiently varifiable. 
	 * @param cntxt Message context.
	 * @return true if the test is passed.
	 */
	public abstract boolean integrityTest(MessageContext cntxt);
	
	
	/**
	 * Decides whether the message privacy is sufficiently protected.
	 * @param cntxt Message context
	 * @return true if the test is passed.
	 */
	public abstract boolean privacyTest(MessageContext cntxt); 
	
	
	/**
	 * Returns the password of the gicen user. This should be retrieved 
	 * from a password store.
	 * @param username
	 * @return The actual password.
	 */
	public abstract char[] getPassword(String username);
	
}
