package com.jwsbook.jaxrpc;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.rmi.PortableRemoteObject;


/**
 * @author hemapani
 */
public class BookQuoteClient {
	public static void main(String[] args)throws Exception{
		Properties env = new Properties();
		env.put(Context.INITIAL_CONTEXT_FACTORY,"org.jnp.interfaces.NamingContextFactory");
		env.put(Context.PROVIDER_URL, "127.0.0.1:1099");
		
		Context initial = new javax.naming.InitialContext(env);		
		Object objref = initial.lookup("BookHome");

					 BookQuoteHome home = 
						(BookQuoteHome)PortableRemoteObject.narrow(objref, 
													  BookQuoteHome.class);
		BookQuoteEJB ejb = home.create();
		System.out.println("value 2 + 3 is "+ejb.getBookPrice("isbn-3465654y"));
	}
}
