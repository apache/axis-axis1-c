/**
 * BookQuoteBindingImpl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2dev Nov 22, 2003 (10:36:07 GMT+06:00) WSDL2Java emitter.
 */

package com.jwsbook.jaxrpc;

import org.apache.axis.AxisFault;
import org.apache.x.ws4j2ee.wsutils.GeneralUtils;

public class BookQuoteBindingImpl implements com.jwsbook.jaxrpc.BookQuote{
	private BookQuoteEJB ejb = null;
	
	public BookQuoteBindingImpl(){
		Properties env = new Properties();
		env.put(Context.INITIAL_CONTEXT_FACTORY,"org.jnp.interfaces.NamingContextFactory");
		env.put(Context.PROVIDER_URL, "127.0.0.1:1099");
		
		Context initial = new javax.naming.InitialContext(env);		
		Object objref = initial.lookup("BookHome");

		BookQuoteHome home = 
					(BookQuoteHome)PortableRemoteObject.narrow(objref, 
												  BookQuoteHome.class);
		ejb = home.create();
	}

    public float getBookPrice(java.lang.String isbn) throws java.rmi.RemoteException, com.jwsbook.jaxrpc.InvalidIsbnFault {
		try{
			return ejb.getBookPrice(isbn);
		}catch(Exception e){
			throw AxisFault.makeFault(e);
		}	
    }

}
