package org.objectweb.jonas.zip;
public class ZipBean  implements javax.ejb.SessionBean{
	public java.lang.String getDepartmentForCode(java.lang.String DepCode){
			return null;
	}
	public java.lang.String getDepartmentAdminCenterForCode(java.lang.String DepCode){
			return null;
	}
	public java.lang.String getDepartmentList(java.lang.String Separator){
			return null;
	}
	public java.lang.String getTownForZip(java.lang.String ZipCode,java.lang.String Separator){
			return null;
	}
	public java.lang.String getZipForTown(java.lang.String Town,java.lang.String Separator,boolean ExactMatch){
			return null;
	}
	public java.lang.String getTownsForSoundex(java.lang.String SearchFor,java.lang.String Separator){
			return null;
	}
	public void reportErrorInFile(java.lang.String YourName,java.lang.String YourMail,java.lang.String YourMessage){
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
