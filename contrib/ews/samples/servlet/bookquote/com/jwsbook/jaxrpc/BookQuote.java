package com.jwsbook.jaxrpc;

public interface BookQuote extends java.rmi.Remote {
    public float getBookPrice(java.lang.String isbn) throws java.rmi.RemoteException;
}
