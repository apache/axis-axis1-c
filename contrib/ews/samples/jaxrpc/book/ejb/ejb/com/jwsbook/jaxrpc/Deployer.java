package com.jwsbook.jaxrpc;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.util.Properties;

import javax.ejb.deployment.ControlDescriptor;
import javax.ejb.deployment.SessionDescriptor;
import javax.naming.CompoundName;

/**
 * @author hemapani
 */
public class Deployer {
	public static void main(String[] args)throws Exception{
		String remote = "com.jwsbook.jaxrpc.BookQuoteEJB";
		String home = "com.jwsbook.jaxrpc.BookQuoteHOME";
		String bean = "com.jwsbook.jaxrpc.BookQuoteBean";
		
		SessionDescriptor sd = new SessionDescriptor();
		sd.setEnterpriseBeanClassName(bean);
		sd.setHomeInterfaceClassName(home);
		sd.setRemoteInterfaceClassName(remote);
		
		sd.setSessionTimeout(60);
		sd.setStateManagementType(SessionDescriptor.STATELESS_SESSION);
		
		ControlDescriptor cd = new ControlDescriptor();
		cd.setIsolationLevel(ControlDescriptor.TRANSACTION_READ_COMMITTED);
		cd.setMethod(null);
		cd.setRunAsMode(ControlDescriptor.CLIENT_IDENTITY);
		cd.setTransactionAttribute(ControlDescriptor.TX_REQUIRED);
		sd.setControlDescriptors(new ControlDescriptor[]{cd});
		
		CompoundName jndiname = new CompoundName("BookHome",new Properties());
		sd.setBeanHomeName(jndiname);
		
		FileOutputStream fis = new FileOutputStream("samples/book/ejb/book.ser");
		ObjectOutputStream oos = new ObjectOutputStream(fis);
		oos.writeObject(sd);
		
		
		
		System.out.println(sd.toString());
		oos.flush();
		oos.close();
		fis.close();
	}
}
