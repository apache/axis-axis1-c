package org.objectweb.wssample.gen.google;
public class GoogleSearchPortBean  implements javax.ejb.SessionBean{
	public byte[] doGetCachedPage(java.lang.String key,java.lang.String url){
			return null;
	}
	public java.lang.String doSpellingSuggestion(java.lang.String key,java.lang.String phrase){
			return null;
	}
	public org.objectweb.wssample.gen.google.MyGoogleSearchResult doGoogleSearch(java.lang.String key,java.lang.String q,int start,int maxResults,boolean filter,java.lang.String restrict,boolean safeSearch,java.lang.String lr,java.lang.String ie,java.lang.String oe){
			return null;
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
