package org.apache.geronimo.ews.ws4j2ee.wsutils;

import org.apache.axis.MessageContext;

/**
 * @author Srinath Perera(hemapani@opensource.lk)
 */
public interface ContextAccssible {
	public void setMessageContext(MessageContext context);
}
