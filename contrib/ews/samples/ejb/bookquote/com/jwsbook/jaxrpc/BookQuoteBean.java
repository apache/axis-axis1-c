package com.jwsbook.jaxrpc;
public class BookQuoteBean  implements javax.ejb.SessionBean{
	public float getBookPrice(java.lang.String isbn){
			return 0.0f;
	}
	public javax.naming.Context getInitialContext()throws javax.naming.NamingException{
		java.util.Properties env = new java.util.Properties();
		env.put(javax.naming.Context.INITIAL_CONTEXT_FACTORY,"org.jnp.interfaces.NamingContextFactory");
		env.put(javax.naming.Context.PROVIDER_URL, "127.0.0.1:1099");
		return new javax.naming.InitialContext(env);
	}
	public void ejbCreate() {}
	public void ejbActivate() throws javax.ejb.EJBException, java.rmi.RemoteException {}
	public void ejbPassivate() throws javax.ejb.EJBException, java.rmi.RemoteException {}
	public void ejbRemove() throws javax.ejb.EJBException, java.rmi.RemoteException {}
	public void setSessionContext(javax.ejb.SessionContext arg0)throws javax.ejb.EJBException, java.rmi.RemoteException {}
}
