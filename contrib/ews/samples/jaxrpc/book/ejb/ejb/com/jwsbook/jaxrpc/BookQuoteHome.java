package com.jwsbook.jaxrpc;
import java.rmi.RemoteException;

import javax.ejb.CreateException;
import javax.ejb.EJBHome;

/**
 * EJB home class need to implement the Service LifeCycle mehtods
 * @author hemapani
 */
public interface BookQuoteHome extends EJBHome{
	public BookQuoteEJB create()throws RemoteException,CreateException;
}
