/**
 * BookQuoteService.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2dev Nov 22, 2003 (10:36:07 GMT+06:00) WSDL2Java emitter.
 */

package com.jwsbook.jaxrpc;

public interface BookQuoteService extends javax.xml.rpc.Service {
    public java.lang.String getBookQuotePortAddress();

    public com.jwsbook.jaxrpc.BookQuote getBookQuotePort() throws javax.xml.rpc.ServiceException;

    public com.jwsbook.jaxrpc.BookQuote getBookQuotePort(java.net.URL portAddress) throws javax.xml.rpc.ServiceException;
}
