/**
 * BookQuote.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2dev Nov 22, 2003 (10:36:07 GMT+06:00) WSDL2Java emitter.
 */

package com.jwsbook.jaxrpc;

public interface BookQuote extends java.rmi.Remote {
    public float getBookPrice(java.lang.String isbn) throws java.rmi.RemoteException, com.jwsbook.jaxrpc.InvalidIsbnFault;
}
