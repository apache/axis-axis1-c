/**
 * BookQuoteServiceLocator.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2dev Nov 22, 2003 (10:36:07 GMT+06:00) WSDL2Java emitter.
 */

package com.jwsbook.jaxrpc;

public class BookQuoteServiceLocator extends org.apache.axis.client.Service implements com.jwsbook.jaxrpc.BookQuoteService {

    // Use to get a proxy class for BookQuotePort
    private java.lang.String BookQuotePort_address = "http://www.Monson-Haefel.com/jwsbook/BookQuoteService";

    public java.lang.String getBookQuotePortAddress() {
        return BookQuotePort_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String BookQuotePortWSDDServiceName = "BookQuotePort";

    public java.lang.String getBookQuotePortWSDDServiceName() {
        return BookQuotePortWSDDServiceName;
    }

    public void setBookQuotePortWSDDServiceName(java.lang.String name) {
        BookQuotePortWSDDServiceName = name;
    }

    public com.jwsbook.jaxrpc.BookQuote getBookQuotePort() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(BookQuotePort_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getBookQuotePort(endpoint);
    }

    public com.jwsbook.jaxrpc.BookQuote getBookQuotePort(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            com.jwsbook.jaxrpc.BookQuoteBindingStub _stub = new com.jwsbook.jaxrpc.BookQuoteBindingStub(portAddress, this);
            _stub.setPortName(getBookQuotePortWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    public void setBookQuotePortEndpointAddress(java.lang.String address) {
        BookQuotePort_address = address;
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        try {
            if (com.jwsbook.jaxrpc.BookQuote.class.isAssignableFrom(serviceEndpointInterface)) {
                com.jwsbook.jaxrpc.BookQuoteBindingStub _stub = new com.jwsbook.jaxrpc.BookQuoteBindingStub(new java.net.URL(BookQuotePort_address), this);
                _stub.setPortName(getBookQuotePortWSDDServiceName());
                return _stub;
            }
        }
        catch (java.lang.Throwable t) {
            throw new javax.xml.rpc.ServiceException(t);
        }
        throw new javax.xml.rpc.ServiceException("There is no stub implementation for the interface:  " + (serviceEndpointInterface == null ? "null" : serviceEndpointInterface.getName()));
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(javax.xml.namespace.QName portName, Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        if (portName == null) {
            return getPort(serviceEndpointInterface);
        }
        String inputPortName = portName.getLocalPart();
        if ("BookQuotePort".equals(inputPortName)) {
            return getBookQuotePort();
        }
        else  {
            java.rmi.Remote _stub = getPort(serviceEndpointInterface);
            ((org.apache.axis.client.Stub) _stub).setPortName(portName);
            return _stub;
        }
    }

    public javax.xml.namespace.QName getServiceName() {
        return new javax.xml.namespace.QName("http://www.Monson-Haefel.com/jwsbook/BookQuote", "BookQuoteService");
    }

    private java.util.HashSet ports = null;

    public java.util.Iterator getPorts() {
        if (ports == null) {
            ports = new java.util.HashSet();
            ports.add(new javax.xml.namespace.QName("BookQuotePort"));
        }
        return ports.iterator();
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(java.lang.String portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        if ("BookQuotePort".equals(portName)) {
            setBookQuotePortEndpointAddress(address);
        }
        else { // Unknown Port Name
            throw new javax.xml.rpc.ServiceException(" Cannot set Endpoint Address for Unknown Port" + portName);
        }
    }

    /**
    * Set the endpoint address for the specified port name.
    */
    public void setEndpointAddress(javax.xml.namespace.QName portName, java.lang.String address) throws javax.xml.rpc.ServiceException {
        setEndpointAddress(portName.getLocalPart(), address);
    }

}
