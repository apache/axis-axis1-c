package org.objectweb.jonas.jtests.beans.time;
public class TimeBeanBean  implements javax.ejb.SessionBean{
	public java.util.Calendar getDate(){
			return null;
	}
	public long getDateAsLong(){
			return 1123L;
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
