package com.jwsbook.jaxrpc;

import javax.ejb.EJBObject;

public interface BookQuoteEJB extends EJBObject {
	public float getBookPrice(java.lang.String isbn) throws java.rmi.RemoteException;
}
