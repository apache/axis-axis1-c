/**
 * InteropTestServiceLocator.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package org.soapinterop;

public class InteropTestServiceLocator extends org.apache.axis.client.Service implements org.soapinterop.InteropTestService {

    // Use to get a proxy class for echo
    private final java.lang.String echo_address = "http://nagoya.apache.org:5049/axis/services/echo";

    public java.lang.String getechoAddress() {
        return echo_address;
    }

    // The WSDD service name defaults to the port name.
    private java.lang.String echoWSDDServiceName = "echo";

    public java.lang.String getechoWSDDServiceName() {
        return echoWSDDServiceName;
    }

    public void setechoWSDDServiceName(java.lang.String name) {
        echoWSDDServiceName = name;
    }

    public org.soapinterop.InteropTestPortType getecho() throws javax.xml.rpc.ServiceException {
       java.net.URL endpoint;
        try {
            endpoint = new java.net.URL(echo_address);
        }
        catch (java.net.MalformedURLException e) {
            throw new javax.xml.rpc.ServiceException(e);
        }
        return getecho(endpoint);
    }

    public org.soapinterop.InteropTestPortType getecho(java.net.URL portAddress) throws javax.xml.rpc.ServiceException {
        try {
            org.soapinterop.InteropTestSoapBindingStub _stub = new org.soapinterop.InteropTestSoapBindingStub(portAddress, this);
            _stub.setPortName(getechoWSDDServiceName());
            return _stub;
        }
        catch (org.apache.axis.AxisFault e) {
            return null;
        }
    }

    /**
     * For the given interface, get the stub implementation.
     * If this service has no port for the given interface,
     * then ServiceException is thrown.
     */
    public java.rmi.Remote getPort(Class serviceEndpointInterface) throws javax.xml.rpc.ServiceException {
        try {
            if (org.soapinterop.InteropTestPortType.class.isAssignableFrom(serviceEndpointInterface)) {
                org.soapinterop.InteropTestSoapBindingStub _stub = new org.soapinterop.InteropTestSoapBindingStub(new java.net.URL(echo_address), this);
                _stub.setPortName(getechoWSDDServiceName());
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
        if ("echo".equals(inputPortName)) {
            return getecho();
        }
        else  {
            java.rmi.Remote _stub = getPort(serviceEndpointInterface);
            ((org.apache.axis.client.Stub) _stub).setPortName(portName);
            return _stub;
        }
    }

    public javax.xml.namespace.QName getServiceName() {
        return new javax.xml.namespace.QName("http://soapinterop.org/", "InteropTestService");
    }

    private java.util.HashSet ports = null;

    public java.util.Iterator getPorts() {
        if (ports == null) {
            ports = new java.util.HashSet();
            ports.add(new javax.xml.namespace.QName("echo"));
        }
        return ports.iterator();
    }

}
