package com.jwsbook.jaxrpc;
import java.rmi.RemoteException;
import java.util.Properties;

import javax.ejb.EJBException;
import javax.ejb.SessionBean;
import javax.ejb.SessionContext;
import javax.naming.Context;


/**
 * This set of class represents statelss SessionBean.
 * for remote acsess you need (if bean name is <X>)
 * 
 * 1) Remote interface extends EJBObject 	<X>
 * 2) Home interface extends EJBHome 		<X>Home
 * 3) Bean class implements SessionBean  	<X>Bean
 * 		** bean class should have default constructor and at least one 
 *			public void ejbCreate() {} method
 *
 * for local acsess u need
 * 1) local Home							Local<X>Home
 * 2) local interface						<X>
 * 3) Bean class implements SessionBean  	<X>Bean
 * 
 * the EJB is called <x>EJB
 * 
 * to deploy the EJB
 * 	you create JAR called <X>JAR
 * 
 * the EJB implemetation object 
 * @author hemapani
 */
public class BookQuoteBean implements SessionBean{
	
	public float getBookPrice(java.lang.String isbn) throws java.rmi.RemoteException{
		return 100;
	}
	
	public javax.naming.Context getInitialContext()throws javax.naming.NamingException{
		Properties env = new Properties();
		env.put(Context.INITIAL_CONTEXT_FACTORY,"org.jnp.interfaces.NamingContextFactory");
		env.put(Context.PROVIDER_URL, "127.0.0.1:1099");
		return new javax.naming.InitialContext(env);
            
	}

	public BookQuoteBean() {}
	public void ejbCreate() {}
	public void ejbActivate() throws EJBException, RemoteException {}
	public void ejbPassivate() throws EJBException, RemoteException {}
	public void ejbRemove() throws EJBException, RemoteException {}
	public void setSessionContext(SessionContext arg0)
		throws EJBException, RemoteException {}
}
